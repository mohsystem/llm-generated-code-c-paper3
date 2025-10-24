#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <errno.h>

/* ZIP format structures - packed to match file format */
#pragma pack(push, 1)
typedef struct {
    uint32_t signature;
    uint16_t version;
    uint16_t flags;
    uint16_t compression;
    uint16_t modTime;
    uint16_t modDate;
    uint32_t crc32;
    uint32_t compressedSize;
    uint32_t uncompressedSize;
    uint16_t filenameLen;
    uint16_t extraLen;
} LocalFileHeader;
#pragma pack(pop)

#define LOCAL_FILE_HEADER_SIG 0x04034b50
#define MAX_FILENAME_LEN 4096
#define MAX_FILE_SIZE (100 * 1024 * 1024)      /* 100MB per file */
#define MAX_TOTAL_SIZE (500 * 1024 * 1024)     /* 500MB total extraction */

/* Validates path to prevent directory traversal (CWE-22) */
bool isPathSafe(const char* path, const char* baseDir) {
    size_t len;
    size_t i;

    /* All pointers must be non-NULL (C security checklist) */
    if (path == NULL || baseDir == NULL) {
        return false;
    }

    len = strlen(path);

    /* Validate length */
    if (len == 0 || len > MAX_FILENAME_LEN) {
        return false;
    }

    /* Reject absolute paths */
    if (path[0] == '/' || path[0] == '\\') {
        return false;
    }

    /* Check for drive letters (Windows) */
    if (len >= 2 && path[1] == ':') {
        return false;
    }

    /* Check for path traversal patterns and null bytes (CWE-158) */
    for (i = 0; i < len; i++) {
        if (path[i] == '\0' && i < len - 1) {
            return false; /* Embedded null */
        }
        if (i < len - 1 && path[i] == '.' && path[i + 1] == '.') {
            return false; /* Path traversal */
        }
    }

    return true;
}

/* Safe memory allocation with overflow check (C security checklist) */
void* safeMalloc(size_t size) {
    void* ptr = NULL;

    /* Check for zero or overflow */
    if (size == 0 || size > MAX_FILE_SIZE) {
        return NULL;
    }

    ptr = malloc(size);
    if (ptr == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return NULL;
    }

    /* Initialize memory to zero */
    memset(ptr, 0, size);
    return ptr;
}

/* Safe file write with atomic rename to prevent TOCTOU (CWE-367) */
bool safeWriteFile(const char* finalPath, const uint8_t* data, size_t dataSize) {
    char tempPath[MAX_FILENAME_LEN + 5]; /* +5 for ".tmp\0" */
    FILE* file = NULL;
    size_t written;
    int renameResult;

    /* Validate all inputs (CWE-20) */
    if (finalPath == NULL || data == NULL || dataSize == 0 || dataSize > MAX_FILE_SIZE) {
        return false;
    }

    /* Bounds check for temp path construction (CWE-119) */
    if (strlen(finalPath) > MAX_FILENAME_LEN) {
        return false;
    }

    /* Construct temp path safely using snprintf (no strcpy/strcat) */
    if (snprintf(tempPath, sizeof(tempPath), "%s.tmp", finalPath) >= (int)sizeof(tempPath)) {
        fprintf(stderr, "Temp path too long\n");
        return false;
    }
    tempPath[sizeof(tempPath) - 1] = '\0'; /* Ensure null termination */

    /* Open with write-binary (exclusive open would be platform-specific) */
    file = fopen(tempPath, "wb");
    if (file == NULL) {
        fprintf(stderr, "Cannot create temp file: %s\n", strerror(errno));
        return false;
    }

    /* Write data with bounds check */
    written = fwrite(data, 1, dataSize, file);
    if (written != dataSize) {
        fprintf(stderr, "Write failed\n");
        fclose(file);
        remove(tempPath);
        return false;
    }

    /* Flush before rename */
    if (fflush(file) != 0) {
        fprintf(stderr, "Flush failed\n");
        fclose(file);
        remove(tempPath);
        return false;
    }

    /* Close file - check return value */
    if (fclose(file) != 0) {
        fprintf(stderr, "Close failed\n");
        remove(tempPath);
        return false;
    }
    file = NULL; /* Prevent double close */

    /* Atomic rename to final path */
    renameResult = rename(tempPath, finalPath);
    if (renameResult != 0) {
        fprintf(stderr, "Rename failed: %s\n", strerror(errno));
        remove(tempPath);
        return false;
    }

    return true;
}

/* Extract ZIP archive with security checks */
bool extractZip(const char* zipPath, const char* outputDir) {
    FILE* zipFile = NULL;
    LocalFileHeader header;
    char* filename = NULL;
    uint8_t* compressedData = NULL;
    size_t totalExtracted = 0;
    long fileSize;
    long currentPos;
    size_t bytesRead;
    char outputPath[MAX_FILENAME_LEN * 2];
    bool success = true;

    /* Validate inputs (CWE-20) */
    if (zipPath == NULL || outputDir == NULL) {
        fprintf(stderr, "Invalid input paths\n");
        return false;
    }

    if (strlen(zipPath) == 0 || strlen(outputDir) == 0) {
        fprintf(stderr, "Empty input paths\n");
        return false;
    }

    /* Open ZIP file */
    zipFile = fopen(zipPath, "rb");
    if (zipFile == NULL) {
        fprintf(stderr, "Cannot open ZIP file: %s\n", strerror(errno));
        return false;
    }

    /* Get file size for bounds checking (CWE-119) */
    if (fseek(zipFile, 0, SEEK_END) != 0) {
        fprintf(stderr, "Seek failed\n");
        fclose(zipFile);
        return false;
    }

    fileSize = ftell(zipFile);
    if (fileSize < 0) {
        fprintf(stderr, "Invalid file size\n");
        fclose(zipFile);
        return false;
    }

    if (fseek(zipFile, 0, SEEK_SET) != 0) {
        fprintf(stderr, "Seek failed\n");
        fclose(zipFile);
        return false;
    }

    /* Process each file in ZIP */
    while (!feof(zipFile)) {
        /* Check position before reading header (CWE-125) */
        currentPos = ftell(zipFile);
        if (currentPos < 0 || currentPos + (long)sizeof(header) > fileSize) {
            break;
        }

        /* Read header with bounds check */
        bytesRead = fread(&header, 1, sizeof(header), zipFile);
        if (bytesRead != sizeof(header)) {
            break;
        }

        /* Validate signature */
        if (header.signature != LOCAL_FILE_HEADER_SIG) {
            break;
        }

        /* Validate filename length (CWE-20) */
        if (header.filenameLen == 0 || header.filenameLen > MAX_FILENAME_LEN) {
            fprintf(stderr, "Invalid filename length\n");
            success = false;
            break;
        }

        /* Check bounds before reading filename (CWE-119) */
        currentPos = ftell(zipFile);
        if (currentPos < 0 ||
            currentPos + header.filenameLen + header.extraLen > fileSize) {
            fprintf(stderr, "File truncated\n");
            success = false;
            break;
        }

        /* Allocate filename buffer with null terminator space */
        filename = (char*)safeMalloc(header.filenameLen + 1);
        if (filename == NULL) {
            success = false;
            break;
        }

        /* Read filename with bounds check */
        bytesRead = fread(filename, 1, header.filenameLen, zipFile);
        if (bytesRead != header.filenameLen) {
            fprintf(stderr, "Cannot read filename\n");
            free(filename);
            filename = NULL;
            success = false;
            break;
        }
        filename[header.filenameLen] = '\0'; /* Ensure null termination */

        /* Validate path safety (CWE-22: Path Traversal) */
        if (!isPathSafe(filename, outputDir)) {
            fprintf(stderr, "Unsafe path detected: %s\n", filename);
            free(filename);
            filename = NULL;
            success = false;
            break;
        }

        /* Skip extra field */
        if (header.extraLen > 0) {
            if (fseek(zipFile, header.extraLen, SEEK_CUR) != 0) {
                free(filename);
                filename = NULL;
                success = false;
                break;
            }
        }

        /* Validate file size (CWE-770: Resource exhaustion) */
        if (header.uncompressedSize > MAX_FILE_SIZE) {
            fprintf(stderr, "File too large: %s\n", filename);
            free(filename);
            filename = NULL;
            success = false;
            break;
        }

        /* Check total extraction size to prevent zip bomb (CWE-409) */
        if (totalExtracted + header.uncompressedSize > MAX_TOTAL_SIZE) {
            fprintf(stderr, "Total extraction size exceeds limit\n");
            free(filename);
            filename = NULL;
            success = false;
            break;
        }

        /* Check if this is a directory (ends with /) */
        if (header.filenameLen > 0 && filename[header.filenameLen - 1] == '/') {
            /* Skip directories */
            if (header.compressedSize > 0) {
                if (fseek(zipFile, header.compressedSize, SEEK_CUR) != 0) {
                    free(filename);
                    filename = NULL;
                    success = false;
                    break;
                }
            }
            free(filename);
            filename = NULL;
            continue;
        }

        /* Check bounds before reading compressed data (CWE-119) */
        currentPos = ftell(zipFile);
        if (currentPos < 0 || header.compressedSize > MAX_FILE_SIZE ||
            currentPos + header.compressedSize > fileSize) {
            fprintf(stderr, "Invalid compressed size\n");
            free(filename);
            filename = NULL;
            success = false;
            break;
        }

        /* Allocate buffer for compressed data */
        compressedData = (uint8_t*)safeMalloc(header.compressedSize);
        if (compressedData == NULL) {
            free(filename);
            filename = NULL;
            success = false;
            break;
        }

        /* Read compressed data with bounds check */
        bytesRead = fread(compressedData, 1, header.compressedSize, zipFile);
        if (bytesRead != header.compressedSize) {
            fprintf(stderr, "Cannot read file data\n");
            free(compressedData);
            compressedData = NULL;
            free(filename);
            filename = NULL;
            success = false;
            break;
        }

        /* Only support stored (uncompressed) files */
        if (header.compression != 0) {
            fprintf(stderr, "Compressed files not supported: %s\n", filename);
            free(compressedData);
            compressedData = NULL;
            free(filename);
            filename = NULL;
            continue;
        }

        /* Construct output path safely using snprintf (CWE-119) */
        if (snprintf(outputPath, sizeof(outputPath), "%s/%s", outputDir, filename) >=
            (int)sizeof(outputPath)) {
            fprintf(stderr, "Output path too long\n");
            free(compressedData);
            compressedData = NULL;
            free(filename);
            filename = NULL;
            success = false;
            break;
        }
        outputPath[sizeof(outputPath) - 1] = '\0';

        /* Write file atomically to prevent TOCTOU (CWE-367) */
        if (!safeWriteFile(outputPath, compressedData, header.compressedSize)) {
            fprintf(stderr, "Failed to write file: %s\n", outputPath);
            free(compressedData);
            compressedData = NULL;
            free(filename);
            filename = NULL;
            success = false;
            break;
        }

        totalExtracted += header.uncompressedSize;
        printf("Extracted: %s\n", filename);

        /* Clean up allocated memory for this iteration */
        free(compressedData);
        compressedData = NULL;
        free(filename);
        filename = NULL;
    }

    /* Close file - check return value */
    if (fclose(zipFile) != 0) {
        fprintf(stderr, "File close failed\n");
        return false;
    }

    return success;
}

int main(void) {
    /* Test case 1: Valid ZIP extraction */
    printf("=== Test 1: Valid ZIP extraction ===\n");
    if (extractZip("test.zip", "output1")) {
        printf("Test 1 passed\n");
    } else {
        printf("Test 1 failed\n");
    }

    /* Test case 2: Path traversal attempt (should fail) */
    printf("\n=== Test 2: Path traversal safety ===\n");
    if (!isPathSafe("../../../etc/passwd", "output2")) {
        printf("Test 2 passed: Path traversal blocked\n");
    } else {
        printf("Test 2 failed: Path traversal not blocked\n");
    }

    /* Test case 3: Absolute path attempt (should fail) */
    printf("\n=== Test 3: Absolute path safety ===\n");
    if (!isPathSafe("/tmp/test.txt", "output3")) {
        printf("Test 3 passed: Absolute path blocked\n");
    } else {
        printf("Test 3 failed: Absolute path not blocked\n");
    }

    /* Test case 4: Valid relative path (should pass) */
    printf("\n=== Test 4: Valid relative path ===\n");
    if (isPathSafe("subdir/file.txt", "output4")) {
        printf("Test 4 passed: Valid path accepted\n");
    } else {
        printf("Test 4 failed: Valid path rejected\n");
    }

    /* Test case 5: Empty input validation */
    printf("\n=== Test 5: Empty input validation ===\n");
    if (!extractZip("", "output5")) {
        printf("Test 5 passed: Empty input rejected\n");
    } else {
        printf("Test 5 failed: Empty input accepted\n");
    }

    return 0;
}
