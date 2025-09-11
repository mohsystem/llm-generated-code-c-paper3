// C doesn't have built-in JSON parsing library.
// This example uses cJSON library.
// cJSON is not a standard library, you need to include it separately.

#include <stdio.h>
#include <cJSON.h>

typedef struct {
    char name[50];
    int age;
    char city[50];
} User;

User deserialize(const char* json_str) {
    cJSON *json = cJSON_Parse(json_str);
    User user;
    strcpy(user.name, cJSON_GetObjectItemCaseSensitive(json, "name")->valuestring);
    user.age = cJSON_GetObjectItemCaseSensitive(json, "age")->valueint;
    strcpy(user.city, cJSON_GetObjectItemCaseSensitive(json, "city")->valuestring);
    cJSON_Delete(json);
    return user;
}

int main() {
    // Test cases
    const char* json1 = "{\"name\":\"John\", \"age\":30, \"city\":\"New York\"}";
    User user1 = deserialize(json1);
    printf("%s %d %s\n", user1.name, user1.age, user1.city);

    // More test cases here...

    return 0;
}