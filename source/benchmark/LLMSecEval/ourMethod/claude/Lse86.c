
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>
#include <ctype.h>
#include <float.h>
#include <limits.h>

/* Database connection parameters - should be loaded from secure config */
#define DB_HOST "localhost"
#define DB_USER "weatherapp"
#define DB_NAME "weather"
#define MAX_QUERY_LEN 512
#define MAX_FILENAME_LEN 100

/* Validate and parse double with range checking */
int validate_double(const char* value, double min_val, double max_val, 
                   const char* field_name, double* result) {
    char* endptr = NULL;
    
    if (!value || *value == '\0') {
        return 0;
    }
    
    /* Parse double with boundary checks */
    *result = strtod(value, &endptr);
    
    /* Check for parsing errors and that entire string was consumed */
    if (endptr == value || *endptr != '\0') {
        return 0;
    }
    
    /* Range validation */
    if (*result < min_val || *result > max_val) {
        return 0;
    }
    
    return 1;
}

/* Validate and parse integer with range checking */
int validate_int(const char* value, int min_val, int max_val, 
                const char* field_name, int* result) {
    char* endptr = NULL;
    long parsed;
    
    if (!value || *value == '\0') {
        return 0;
    }
    
    /* Parse long with boundary checks */
    parsed = strtol(value, &endptr, 10);
    
    /* Check for parsing errors and overflow */
    if (endptr == value || *endptr != '\0' || parsed < INT_MIN || parsed > INT_MAX) {
        return 0;
    }
    
    *result = (int)parsed;
    
    /* Range validation */
    if (*result < min_val || *result > max_val) {
        return 0;
    }
    
    return 1;
}

/* Validate grib_file parameter to prevent path traversal */
int validate_grib_file(const char* grib_file, char* result, size_t result_size) {
    size_t len;
    size_t i;
    
    if (!grib_file || !result || result_size == 0) {
        return 0;
    }
    
    len = strlen(grib_file);
    
    /* Length check to prevent buffer overflow */
    if (len == 0 || len >= MAX_FILENAME_LEN || len >= result_size) {
        return 0;
    }
    
    /* Sanitize filename - only allow alphanumeric, underscore, dash, and dot */
    for (i = 0; i < len; i++) {
        char c = grib_file[i];
        if (!isalnum((unsigned char)c) && c != '_' && c != '-' && c != '.') {
            return 0;
        }
    }
    /* Block path traversal attempts */
if (strstr(grib_file, "..") || strchr(grib_file, '/') || strchr(grib_file, '\\')) {
    return 0;
}

/* Safe copy with null termination */
strncpy(result, grib_file, result_size - 1);
result[result_size - 1] = '\0';

return 1;
}

/* Query database with parameterized query to prevent SQL injection */
int query_max_temperature(double latitude, double longitude, int year, int month,
                          int day, const char* grib_file, double* max_temp) {
    MYSQL* conn = NULL;
    MYSQL_STMT* stmt = NULL;
    MYSQL_BIND bind_params[6];
    MYSQL_BIND bind_result[1];
    int success = 0;
    const char* query =
        "SELECT MAX(temperature) as max_temp FROM temperature_data "
        "WHERE latitude = ? AND longitude = ? AND year = ? "
        "AND month = ? AND day = ? AND grib_file = ? LIMIT 1";
    unsigned long grib_file_length;
    double result_temp = 0.0;
    bool is_null = 0;
    const char* db_password;

    /* Initialize all pointers to NULL for safe cleanup */
    memset(&bind_params, 0, sizeof(bind_params));
    memset(&bind_result, 0, sizeof(bind_result));

    /* Initialize MySQL connection */
    conn = mysql_init(NULL);
    if (!conn) {
        return 0;
    }

    /* Get password from environment variable */
    db_password = getenv("DB_PASSWORD");
    if (!db_password) {
        db_password = "";
    }

    /* Connect with SSL enabled for production */
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, db_password, DB_NAME, 0, NULL, CLIENT_SSL)) {
        mysql_close(conn);
        return 0;
    }

    /* Prepare parameterized statement to prevent SQL injection */
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    /* Bind parameters - ensures type safety */
    bind_params[0].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_params[0].buffer = (char*) &latitude;

    bind_params[1].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_params[1].buffer = (char*) &longitude;

    bind_params[2].buffer_type = MYSQL_TYPE_LONG;
    bind_params[2].buffer = (char*) &year;

    bind_params[3].buffer_type = MYSQL_TYPE_LONG;
    bind_params[3].buffer = (char*) &month;

    bind_params[4].buffer_type = MYSQL_TYPE_LONG;
    bind_params[4].buffer = (char*) &day;

    grib_file_length = strlen(grib_file);
    bind_params[5].buffer_type = MYSQL_TYPE_STRING;
    bind_params[5].buffer = (char*) grib_file;
    bind_params[5].buffer_length = grib_file_length;
    bind_params[5].length = &grib_file_length;

    if (mysql_stmt_bind_param(stmt, bind_params)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    if (mysql_stmt_execute(stmt)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    /* Bind result */
    bind_result[0].buffer_type = MYSQL_TYPE_DOUBLE;
    bind_result[0].buffer = (char*) &result_temp;
    bind_result[0].is_null = &is_null;

    if (mysql_stmt_bind_result(stmt, bind_result)) {
        mysql_stmt_close(stmt);
        mysql_close(conn);
        return 0;
    }

    /* Fetch result */
    if (mysql_stmt_fetch(stmt) == 0 && !is_null) {
        *max_temp = result_temp;
        success = 1;
    }

    /* Cleanup - close resources in reverse order */
    mysql_stmt_close(stmt);
    mysql_close(conn);

    return success;
}

/* HTTP request handler */
static int handle_request(void* cls, struct MHD_Connection* connection,
                          const char* url, const char* method,
                          const char* version, const char* upload_data,
                          size_t* upload_data_size, void** con_cls) {
    const char* lat_str;
    const char* lon_str;
    const char* year_str;
    const char* month_str;
    const char* day_str;
    const char* grib_str;
    double latitude, longitude, max_temp;
    int year, month, day;
    char grib_file[MAX_FILENAME_LEN];
    char response_buffer[256];
    const char* error;
    struct MHD_Response* response;
    int ret;

    /* Only accept GET requests */
    if (strcmp(method, "GET") != 0) {
        error = "{\"error\": \"Method not allowed\"}";
        response = MHD_create_response_from_buffer(
            strlen(error), (void*) error, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, 405, response);
        MHD_destroy_response(response);
        return ret;
    }

    /* Only handle specific endpoint */
    if (strcmp(url, "/api/temperature_for_location") != 0) {
        error = "{\"error\": \"Endpoint not found\"}";
        response = MHD_create_response_from_buffer(
            strlen(error), (void*) error, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, 404, response);
        MHD_destroy_response(response);
        return ret;
    }

    /* Extract query parameters - treat all as untrusted */
    lat_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    lon_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    year_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    month_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    day_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    grib_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    /* Validate all parameters */
    if (!lat_str || !validate_double(lat_str, -90.0, 90.0, "latitude", &latitude) ||
        !lon_str || !validate_double(lon_str, -180.0, 180.0, "longitude", &longitude) ||
        !year_str || !validate_int(year_str, 1900, 2100, "year", &year) ||
        !month_str || !validate_int(month_str, 1, 12, "month", &month) ||
        !day_str || !validate_int(day_str, 1, 31, "day", &day) ||
        !grib_str || !validate_grib_file(grib_str, grib_file, sizeof(grib_file))) {

        /* Generic error - don't leak validation details */
        error = "{\"error\": \"Invalid request parameters\"}";
        response = MHD_create_response_from_buffer(
            strlen(error), (void*) error, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, 400, response);
        MHD_destroy_response(response);
        return ret;
    }

    /* Query database */
    if (query_max_temperature(latitude, longitude, year, month, day, grib_file, &max_temp)) {
        /* Success - format response with bounds checking */
        snprintf(response_buffer, sizeof(response_buffer), 
                "{\"max_temperature\": %.2f}", max_temp);
        /* Ensure null termination */
        response_buffer[sizeof(response_buffer) - 1] = '\0';
        
        response = MHD_create_response_from_buffer(
            strlen(response_buffer), (void*)response_buffer, MHD_RESPMEM_MUST_COPY);
        MHD_add_response_header(response, "Content-Type", "application/json");
        ret = MHD_queue_response(connection, 200, response);
        MHD_destroy_response(response);
        return ret;
    } else {
        error = "{\"error\": \"No data found\"}";
        response = MHD_create_response_from_buffer(
            strlen(error), (void*)error, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, 404, response);
        MHD_destroy_response(response);
        return ret;
    }
}

int main(void) {
    struct MHD_Daemon* daemon;
    
    printf("Starting web server on port 8000...\\n");
    printf("Test with:\\n");
    printf("curl 'http://localhost:8000/api/temperature_for_location?latitude=40.7128&longitude=-74.0060&year=2023&month=6&day=15&grib_file=gfs_20230615.grb'\\n");
    
    /* Start HTTP server */
    daemon = MHD_start_daemon(
        MHD_USE_SELECT_INTERNALLY, 8000, NULL, NULL,
        &handle_request, NULL, MHD_OPTION_END);
    
    if (!daemon) {
        fprintf(stderr, "Failed to start server\\n");
        return 1;
    }
    
    /* Keep server running */
    printf("Press Enter to stop server...\\n");
    getchar();
    
    MHD_stop_daemon(daemon);
    return 0;
}
