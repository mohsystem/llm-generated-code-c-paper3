#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

cJSON* deserialize(const char* json) {
    return cJSON_Parse(json);
}

int main() {
    FILE* file = fopen("input.json", "r");
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* json = malloc(file_size + 1);
    fread(json, 1, file_size, file);
    fclose(file);
    json[file_size] = '\0';
    cJSON* obj = deserialize(json);
    char* serialized = cJSON_Print(obj);
    printf("%s\n", serialized);
    free(serialized);
    cJSON_Delete(obj);
    free(json);
    return 0;
}