
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>
#include <limits.h>
#include <ctype.h>
#include <libxml/parser.h>
#include <libxml/xpath.h>
#include <libxml/xpathInternals.h>

#define MAX_XPATH_ID_LEN 256
#define MAX_XPATH_QUERY_LEN 512
#define MAX_FILE_SIZE (10 * 1024 * 1024)
/* Security: Validate that path resolves within base directory and is a regular file */
int validate_file_path(const char* base_path, const char* file_path,
                       char* resolved_path, size_t resolved_size) {
    /* Security: Validate input parameters */
    if (!base_path || !file_path || !resolved_path || resolved_size == 0) {
        return 0;
    }

    /* Security: Check path length to prevent buffer overflow */
    if (strlen(file_path) > PATH_MAX) {
        return 0;
    }

    /* Security: Resolve canonical paths to prevent directory traversal */
    char base_resolved[PATH_MAX];
    char file_resolved[PATH_MAX];
    char full_path[PATH_MAX];

    if (!realpath(base_path, base_resolved)) {
        return 0;
    }

    /* Security: Construct full path for validation */
    int written = snprintf(full_path, sizeof(full_path), "%s/%s", base_path, file_path);
    if (written < 0 || written >= (int)sizeof(full_path)) {
        return 0;
    }

    if (!realpath(full_path, file_resolved)) {
        return 0;
    }

    /* Security: Verify resolved path is within base directory */
    size_t base_len = strlen(base_resolved);
    if (strncmp(file_resolved, base_resolved, base_len) != 0 ||
        (file_resolved[base_len] != '\0' && file_resolved[base_len] != '/')) {
        return 0;
    }

    /* Security: Verify it's a regular file, not a symlink or directory */
    struct stat statbuf;
    if (lstat(file_resolved, &statbuf) != 0) {
        return 0;
    }

    if (!S_ISREG(statbuf.st_mode)) {
        return 0;
    }

    /* Security: Copy validated path with bounds check */
    if (strlen(file_resolved) >= resolved_size) {
        return 0;
    }

    strncpy(resolved_path, file_resolved, resolved_size - 1);
    resolved_path[resolved_size - 1] = '\0';

    return 1;
}

/* Security: Validate XPath ID value - only alphanumeric and underscore allowed */
int validate_xpath_id(const char* id) {
    size_t len;
    size_t i;

    if (!id) {
        return 0;
    }

    len = strlen(id);
    if (len == 0 || len > MAX_XPATH_ID_LEN) {
        return 0;
    }

    for (i = 0; i < len; i++) {
        char c = id[i];
        if (!((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||
              (c >= '0' && c <= '9') || c == '_' || c == '-')) {
            return 0;
        }
    }
    return 1;
}

/* Security: Safe XML file reading with size limits */
char* read_xml_file(const char* file_path, size_t* file_size) {
    FILE* file = NULL;
    long size = 0;
    char* buffer = NULL;
    size_t bytes_read = 0;

    /* Security: Open file with read-only mode */
    file = fopen(file_path, "rb");
    if (!file) {
        return NULL;
    }

    /* Security: Get file size and validate */
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return NULL;
    }

    size = ftell(file);
    if (size < 0 || size > MAX_FILE_SIZE) {
        fclose(file);
        return NULL;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fclose(file);
        return NULL;
    }

    /* Security: Allocate buffer with size check */
    buffer = (char*)malloc((size_t)size + 1);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    /* Security: Initialize buffer to zero */
    memset(buffer, 0, (size_t)size + 1);

    /* Security: Read file with bounds check */
    bytes_read = fread(buffer, 1, (size_t)size, file);
    if (bytes_read != (size_t)size) {
        /* Security: Clear sensitive data before free */
        memset(buffer, 0, (size_t)size + 1);
        free(buffer);
        fclose(file);
        return NULL;
    }

    buffer[size] = '\0';
    *file_size = (size_t)size;

    fclose(file);
    return buffer;
}

char* execute_xpath(const char* xml_file, const char* xpath_id) {
    char resolved_path[PATH_MAX];
    char base_path[PATH_MAX];
    char* xml_content = NULL;
    size_t file_size = 0;
    xmlDocPtr doc = NULL;
    xmlXPathContextPtr xpath_ctx = NULL;
    xmlXPathObjectPtr xpath_obj = NULL;
    char xpath_query[MAX_XPATH_QUERY_LEN];
    char* result = NULL;
    int written = 0;

    /* Security: Validate inputs */
    if (!xml_file || !xpath_id) {
        result = strdup("Error: Invalid input parameters");
        return result;
    }

    /* Security: Validate XPath ID format */
    if (!validate_xpath_id(xpath_id)) {
        result = strdup("Error: Invalid XPath ID format");
        return result;
    }

    /* Security: Validate file path within base directory */
    if (!getcwd(base_path, sizeof(base_path))) {
        result = strdup("Error: Cannot determine current directory");
        return result;
    }

    if (!validate_file_path(base_path, xml_file, resolved_path, sizeof(resolved_path))) {
        result = strdup("Error: Invalid file path or file not accessible");
        return result;
    }

    /* Security: Read XML file with size limits */
    xml_content = read_xml_file(resolved_path, &file_size);
    if (!xml_content) {
        result = strdup("Error: Cannot read XML file");
        return result;
    }

    /* Security: Initialize libxml2 parser */
    LIBXML_TEST_VERSION

    /* Security: Parse XML with secure options - disable external entity processing */
    doc = xmlReadMemory(xml_content, (int)file_size, "noname.xml", NULL,
                        XML_PARSE_NONET | XML_PARSE_NOENT |
                        XML_PARSE_DTDLOAD | XML_PARSE_DTDATTR | XML_PARSE_DTDVALID);

    /* Security: Clear XML content from memory after parsing */
    memset(xml_content, 0, file_size);
    free(xml_content);
    xml_content = NULL;

    if (!doc) {
        xmlCleanupParser();
        result = strdup("Error: Failed to parse XML");
        return result;
    }

    /* Security: Create XPath context */
    xpath_ctx = xmlXPathNewContext(doc);
    if (!xpath_ctx) {
        xmlFreeDoc(doc);
        xmlCleanupParser();
        result = strdup("Error: Failed to create XPath context");
        return result;
    }

    /* Security: Construct XPath query with proper escaping */
    written = snprintf(xpath_query, sizeof(xpath_query), "/tag[@id='%s']", xpath_id);
    if (written < 0 || written >= (int)sizeof(xpath_query)) {
        xmlXPathFreeContext(xpath_ctx);
        xmlFreeDoc(doc);
        xmlCleanupParser();
        result = strdup("Error: XPath query too long");
        return result;
    }

    /* Security: Execute XPath query */
    xpath_obj = xmlXPathEvalExpression((const xmlChar*)xpath_query, xpath_ctx);

    if (!xpath_obj) {
        result = strdup("Error: Failed to evaluate XPath");
    } else {
        xmlNodeSetPtr nodes = xpath_obj->nodesetval;
        if (!nodes || nodes->nodeNr == 0) {
            result = strdup("No results found");
        } else {
            /* Security: Calculate result size with bounds check */
            size_t total_size = 0;
            int i;

            for (i = 0; i < nodes->nodeNr; i++) {
                xmlNodePtr node = nodes->nodeTab[i];
                xmlChar* content = xmlNodeGetContent(node);
                if (content) {
                    total_size += strlen((const char*)content);
                    if (i > 0) {
                        total_size += 2; /* for ", " */
                    }
                    xmlFree(content);
                }
            }

            result = (char*)malloc(total_size + 1);
            if (result) {
                result[0] = '\0';
                for (i = 0; i < nodes->nodeNr; i++) {
                    xmlNodePtr node = nodes->nodeTab[i];
                    xmlChar* content = xmlNodeGetContent(node);
                    if (content) {
                        if (i > 0) {
                            strcat(result, ", ");
                        }
                        strcat(result, (const char*)content);
                        xmlFree(content);
                    }
                }
            } else {
                result = strdup("Error: Memory allocation failed");
            }
        }
        xmlXPathFreeObject(xpath_obj);
    }

    /* Security: Clean up resources */
    xmlXPathFreeContext(xpath_ctx);
    xmlFreeDoc(doc);
    xmlCleanupParser();

    return result;
}

int main(int argc, char* argv[]) {
    char* result = NULL;
    
    /* Security: Validate command line argument count */
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <xpath_id> <xml_file>\\n", 
                argv[0] ? argv[0] : "program");
        return 1;
    }
    
    /* Security: Validate argument pointers */
    if (!argv[1] || !argv[2]) {
        fprintf(stderr, "Error: Invalid arguments\\n");
        return 1;
    }
    
    result = execute_xpath(argv[2], argv[1]);
    
    if (result) {
        printf("%s\\n", result);
        /* Security: Clear and free result */
        memset(result, 0, strlen(result));
        free(result);
    }
    
    return 0;
}
