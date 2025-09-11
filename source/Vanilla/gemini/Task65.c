#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readFileData(const char* filename) {
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return "File not found."; // Return error message
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* data = (char*)malloc(fileSize + 1); // Allocate memory
    if (data == NULL) {
        fclose(file);
        return "Memory allocation failed.";
    }


    size_t bytesRead = fread(data, 1, fileSize, file);
    if(bytesRead != fileSize) {
        fclose(file);
        free(data);
        return "Error reading file";

    }

    data[fileSize] = '\0'; // Null-terminate
    fclose(file);
    return data;
}

int main() {
    char* data1 = readFileData("test1.txt");
     if (strcmp(data1, "File not found.") != 0 && strcmp(data1, "Memory allocation failed.") != 0  && strcmp(data1, "Error reading file") != 0 ) {
    printf("%s", data1);
        free(data1); 
     } else {
         printf("%s\n", data1);
     }
    

    char* data2 = readFileData("test2.txt");
 if (strcmp(data2, "File not found.") != 0 && strcmp(data2, "Memory allocation failed.") != 0  && strcmp(data2, "Error reading file") != 0 ) {
    printf("%s", data2);
        free(data2); 
     } else {
         printf("%s\n", data2);
     }

    char* data3 = readFileData("nonexistent.txt");
    printf("%s\n", data3);


    char* data4 = readFileData("test3.txt");
 if (strcmp(data4, "File not found.") != 0 && strcmp(data4, "Memory allocation failed.") != 0  && strcmp(data4, "Error reading file") != 0 ) {
    printf("%s", data4);
        free(data4); 
     } else {
         printf("%s\n", data4);
     }
    

    char* data5 = readFileData("test4.txt");
 if (strcmp(data5, "File not found.") != 0 && strcmp(data5, "Memory allocation failed.") != 0  && strcmp(data5, "Error reading file") != 0 ) {
    printf("%s", data5);
        free(data5); 
     } else {
         printf("%s\n", data5);
     }
    return 0;
}