
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdbool.h>
#include <limits.h>
#include <errno.h>
#include <stdint.h>

#define MAX_FILE_SIZE (10 * 1024 * 1024) // 10MB limit
#define MAX_PATH_LENGTH 4096
#define MAX_PATTERN_LENGTH 1024
#define BUFFER_SIZE 8192
#define MAX_MATCHES 1000

// Security: Validates that path doesn't contain traversal attempts or dangerous patterns
bool isValidPath(const char* path) {
    if (path == NULL) {
        return false;
    }

    size_t len = strnlen(path, MAX_PATH_LENGTH + 1);

    // Reject empty or too long paths
    if (len == 0 || len > MAX_PATH_LENGTH) {
        return false;
    }

    // Reject absolute paths
    if (path[0] == '/') {
        return false;
    }

    // Check for path traversal attempts
    if (strstr(path, "..") != NULL) {
        return false;
    }

    // Check for double slashes
    if (strstr(path, "//") != NULL) {
        return false;
    }

    // Check for null bytes within string (not at end)
    for (size_t i = 0; i < len; i++) {
        if (path[i] == '\0' && i < len - 1) {
            return false;
        }
    }

    return true;
}

// Security: Validates regex pattern to prevent issues
bool isValidRegexPattern(const char* pattern) {
    if (pattern == NULL) {
        return false;
    }

    size_t len = strnlen(pattern, MAX_PATTERN_LENGTH + 1);

    // Reject empty or too long patterns
    if (len == 0 || len > MAX_PATTERN_LENGTH) {
        return false;
    }

    // Check for null bytes within string
    for (size_t i = 0; i < len; i++) {
        if (pattern[i] == '\0' && i < len - 1) {
            return false;
        }
    }

    // Basic check for nested quantifiers (ReDoS prevention)
    int nestedQuantifiers = 0;
    for (size_t i = 0; i < len; i++) {
        if (pattern[i] == '*' || pattern[i] == '+' || pattern[i] == '{') {
            nestedQuantifiers++;
            if (nestedQuantifiers > 10) {
                return false;
            }
        }
    }

    return true;
}

// Security: Safe file reading with bounds checking and size limits
char* readFileContent(const char* filename, size_t* contentSize) {
    FILE* file = NULL;
    char* content = NULL;
    char* tempBuffer = NULL;
    size_t totalRead = 0;
    size_t currentCapacity = 0;

    // Security: Initialize output parameter
    if (contentSize != NULL) {
        *contentSize = 0;
    } else {
        return NULL;
    }

    // Security: Validate path before opening
    if (!isValidPath(filename)) {
        fprintf(stderr, "Error: Invalid file path\n");
        return NULL;
    }

    // Security: Open file with explicit read mode, use "r" not "rb" for text, but "rb" is safer for regex
    file = fopen(filename, "rb");
    if (file == NULL) {
        fprintf(stderr, "Error: Cannot open file: %s\n", filename);
        return NULL;
    }

    // Security: Get file size with error checking
    if (fseek(file, 0, SEEK_END) != 0) {
        fprintf(stderr, "Error: Cannot seek file\n");
        fclose(file);
        return NULL;
    }

    long fileSize = ftell(file);
    if (fileSize < 0 || (size_t)fileSize > MAX_FILE_SIZE) {
        fprintf(stderr, "Error: File size invalid or exceeds limit\n");
        fclose(file);
        return NULL;
    }

    if (fseek(file, 0, SEEK_SET) != 0) {
        fprintf(stderr, "Error: Cannot seek to beginning\n");
        fclose(file);
        return NULL;
    }

    // Security: Allocate initial buffer with size check
    currentCapacity = (size_t)fileSize + 1; // +1 for null terminator
    content = (char*)calloc(currentCapacity, sizeof(char));
    if (content == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    // Security: Read file with bounds checking
    char buffer[BUFFER_SIZE];
    size_t bytesRead;

    while ((bytesRead = fread(buffer, 1, BUFFER_SIZE, file)) > 0) {
        // Security: Check for overflow before addition
        if (totalRead > SIZE_MAX - bytesRead || totalRead + bytesRead >= MAX_FILE_SIZE) {
            fprintf(stderr, "Error: File size limit exceeded\n");
            free(content);
            fclose(file);
            return NULL;
        }

        // Security: Ensure buffer has space (including null terminator)
        if (totalRead + bytesRead >= currentCapacity) {
            size_t newCapacity = currentCapacity * 2;
            if (newCapacity > MAX_FILE_SIZE + 1) {
                newCapacity = MAX_FILE_SIZE + 1;
            }

            // Security: Check realloc return value
            tempBuffer = (char*)realloc(content, newCapacity);
            if (tempBuffer == NULL) {
                fprintf(stderr, "Error: Memory reallocation failed\n");
                free(content);
                fclose(file);
                return NULL;
            }
            content = tempBuffer;
            currentCapacity = newCapacity;
        }

        // Security: Bounds-checked copy
        memcpy(content + totalRead, buffer, bytesRead);
        totalRead += bytesRead;
    }

    // Security: Check for read errors
    if (ferror(file)) {
        fprintf(stderr, "Error: File read error\n");
        free(content);
        fclose(file);
        return NULL;
    }

    fclose(file);

    // Security: Null terminate the content
    content[totalRead] = '\0';
    *contentSize = totalRead;

    return content;
}

void searchWithRegex(const char* pattern, const char* filename) {
    regex_t regex;
    regmatch_t match;
    char* content = NULL;
    size_t contentSize = 0;
    int reti;
    
    // Security: Validate inputs
    if (!isValidRegexPattern(pattern)) {
        fprintf(stderr, "Error: Invalid regex pattern\n");
        return;
    }
    
    // Security: Read file with bounds checking
    content = readFileContent(filename, &contentSize);
    if (content == NULL) {
        return;
    }
    
    // Security: Compile regex with error handling
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti != 0) {
        char errorBuffer[256];
        regerror(reti, &regex, errorBuffer, sizeof(errorBuffer));
        fprintf(stderr, "Error: Could not compile regex: %s\n", errorBuffer);
        // Security: Free content before returning
        free(content);
        return;
    }
    
    // Search for matches
    int matchCount = 0;
    const char* searchPtr = content;
    size_t remainingSize = contentSize;
    
    while (matchCount < MAX_MATCHES && remainingSize > 0) {
        reti = regexec(&regex, searchPtr, 1, &match, 0);
        
        if (reti == 0) {
            // Match found
            // Security: Validate match offsets
            if (match.rm_so >= 0 && match.rm_eo >= match.rm_so && 
                (size_t)match.rm_eo <= remainingSize) {
                
                int matchLen = match.rm_eo - match.rm_so;
                printf("Match found: %.*s\n", matchLen, searchPtr + match.rm_so);
                matchCount++;
                
                // Move search pointer past this match
                size_t offset = (size_t)match.rm_eo;
                if (offset == 0) offset = 1; // Prevent infinite loop on zero-length matches
                
                // Security: Check bounds before pointer arithmetic
                if (offset > remainingSize) {
                    break;
                }
                searchPtr += offset;
                remainingSize -= offset;
            } else {
                break;
            }
        } else if (reti == REG_NOMATCH) {
            break;
        } else {
            char errorBuffer[256];
            regerror(reti, &regex, errorBuffer, sizeof(errorBuffer));
            fprintf(stderr, "Error: Regex match failed: %s\n", errorBuffer);
            break;
        }
    }
    
    if (matchCount == 0) {
        printf("No matches found.\n");
    } else {
        printf("Total matches: %d\n", matchCount);
    }
    
    // Security: Clean up resources
    regfree(&regex);
    free(content);
}

int main(int argc, char* argv[]) {
    // Security: Validate argument count
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <regex_pattern> <filename>\n",
                argv[0] != NULL ? argv[0] : "program");
        return 1;
    }
    
    // Security: Validate argv pointers
    if (argv[1] == NULL || argv[2] == NULL) {
        fprintf(stderr, "Error: Invalid arguments\n");
        return 1;
    }
    
    // Security: Validate argument lengths
    size_t patternLen = strnlen(argv[1], MAX_PATTERN_LENGTH + 1);
    size_t filenameLen = strnlen(argv[2], MAX_PATH_LENGTH + 1);
    
    if (patternLen == 0 || patternLen > MAX_PATTERN_LENGTH ||
        filenameLen == 0 || filenameLen > MAX_PATH_LENGTH) {
        fprintf(stderr, "Error: Argument length invalid\n");
        return 1;
    }
    
    printf("=== Test Case: User provided arguments ===\n");
    searchWithRegex(argv[1], argv[2]);
    
    return 0;
}
