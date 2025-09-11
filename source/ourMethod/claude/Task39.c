
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <errno.h>

#ifdef _WIN32
    #include <windows.h>
    #define PATH_MAX MAX_PATH
#else
    #include <unistd.h>
    #include <sys/stat.h>
#endif

char* displayFileContents(const char* filename) {
    if (!filename || strlen(filename) == 0) {
        return strdup("Invalid filename");
    }

    // Allocate memory for the absolute path
    char* absolutePath = (char*)malloc(PATH_MAX);
    if (!absolutePath) {
        return strdup("Memory allocation error");
    }

    // Get absolute path
    #ifdef _WIN32
        if (_fullpath(absolutePath, filename, PATH_MAX) == NULL) {
            free(absolutePath);
            return strdup("Path resolution error");
        }
    #else
        if (realpath(filename, absolutePath) == NULL) {
            free(absolutePath);
            return strdup("Path resolution error");
        }
    #endif

    // Check if file exists and is regular file
    #ifdef _WIN32
        DWORD attrs = GetFileAttributesA(absolutePath);
        if (attrs == INVALID_FILE_ATTRIBUTES || (attrs & FILE_ATTRIBUTE_DIRECTORY)) {
            free(absolutePath);
            return strdup("Not a valid file");
        }
    #else
        struct stat st;
        if (stat(absolutePath, &st) != 0 || !S_ISREG(st.st_mode)) {
            free(absolutePath);
            return strdup("Not a valid file");
        }
    #endif

    // Construct command
    char* command = (char*)malloc(PATH_MAX + 10);
    if (!command) {
        free(absolutePath);
        return strdup("Memory allocation error");
    }

    #ifdef _WIN32
        snprintf(command, PATH_MAX + 10, "type \\"%s\\"", absolutePath);
    #else
        snprintf(command, PATH_MAX + 10, "cat \\"%s\\"", absolutePath);
    #endif

    // Execute command and read output
    FILE* pipe = 
    #ifdef _WIN32
        _popen(command, "r");
    #else
        popen(command, "r");
    #endif

    if (!pipe) {
        free(absolutePath);
        free(command);
        return strdup("Command execution failed");
    }

    // Read command output
    char* output = (char*)malloc(4096);
    char buffer[128];
    size_t outputSize = 4096;
    size_t currentSize = 0;

    if (!output) {
        #ifdef _WIN32
            _pclose(pipe);
        #else
            pclose(pipe);
        #endif
        free(absolutePath);
        free(command);
        return strdup("Memory allocation error");
    }

    output[0] = '\\0';

    while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
        size_t len = strlen(buffer);
        if (currentSize + len >= outputSize) {
            outputSize *= 2;
            char* temp = (char*)realloc(output, outputSize);
            if (!temp) {
                free(output);
                #ifdef _WIN32
                    _pclose(pipe);
                #else
                    pclose(pipe);
                #endif
                free(absolutePath);
                free(command);
                return strdup("Memory allocation error");
            }
            output = temp;
        }
        strcat(output, buffer);
        currentSize += len;
    }

    #ifdef _WIN32
        _pclose(pipe);
    #else
        pclose(pipe);
    #endif

    free(absolutePath);
    free(command);

    return output;
}

int main() {
    // Test cases
    const char* testFiles[] = {
        "test.txt",
        "/etc/passwd",  // should be blocked
        "../../test.txt", // should be normalized
        "",  // invalid
        "nonexistent.txt" // should show error
    };

    char input[PATH_MAX];
    printf("Enter filename or press Enter to run test cases: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        // Remove newline if present
        input[strcspn(input, "\\n")] = 0;

        if (strlen(input) > 0) {
            char* result = displayFileContents(input);
            if (result) {
                printf("%s\\n", result);
                free(result);
            }
        } else {
            // Run test cases
            for (size_t i = 0; i < sizeof(testFiles)/sizeof(testFiles[0]); i++) {
                printf("\\nTesting file: %s\\n", testFiles[i]);
                char* result = displayFileContents(testFiles[i]);
                if (result) {
                    printf("%s\\n", result);
                    free(result);
                }
            }
        }
    }

    return 0;
}
