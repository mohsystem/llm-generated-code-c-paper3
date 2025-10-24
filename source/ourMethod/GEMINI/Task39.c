#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// POSIX-specific headers for fork, execvp, waitpid, and lstat
#if defined(__unix__) || defined(__APPLE__) || defined(__linux__)
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define IS_POSIX 1
#else
#define IS_POSIX 0
#endif

/**
 * @brief Displays the content of a file using a system command ('cat').
 * This implementation is POSIX-specific (Linux, macOS).
 * The filename is validated to prevent command injection and path traversal.
 *
 * @param filename The name of the file to display. It must be in the current directory.
 */
void displayFileContent(const char* filename) {
#if IS_POSIX
    if (filename == NULL || filename[0] == '\0') {
        fprintf(stderr, "Error: Filename cannot be null or empty.\n");
        return;
    }

    // Rule #1 & #5: Validate filename format to prevent injection.
    const char* allowed_chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789._-";
    if (strspn(filename, allowed_chars) != strlen(filename)) {
        fprintf(stderr, "Error: Invalid filename format. Only alphanumeric characters, dots, underscores, and hyphens are allowed.\n");
        return;
    }

    // Rule #5: Check for path separators.
    if (strchr(filename, '/') != NULL || strchr(filename, '\\') != NULL) {
        fprintf(stderr, "Error: Path traversal is not allowed. Please provide a simple filename.\n");
        return;
    }

    // Rule #5 & #6: Use lstat to check if it's a regular file before use.
    struct stat st;
    if (lstat(filename, &st) != 0) {
        fprintf(stderr, "Error: File '%s' does not exist or cannot be accessed.\n", filename);
        return;
    }
    if (!S_ISREG(st.st_mode)) {
        fprintf(stderr, "Error: '%s' is not a regular file.\n", filename);
        return;
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("fork");
        return;
    }

    if (pid == 0) { // Child process
        // Rule #2: Use execvp to avoid shell interpretation.
        // It takes the command and arguments as a separate array.
        char* const argv[] = {"cat", (char*)filename, NULL};
        execvp("cat", argv);
        
        // execvp only returns if an error occurred
        perror("execvp");
        _exit(127); // Use _exit in child process after fork
    } else { // Parent process
        int status = 0;
        waitpid(pid, &status, 0);
        int exit_code = WIFEXITED(status) ? WEXITSTATUS(status) : -1;
        printf("\n--- Command finished with exit code: %d ---\n", exit_code);
    }
#else
    fprintf(stderr, "Error: This function is only implemented for POSIX-compliant systems (Linux, macOS).\n");
    // On Windows, one would use the CreateProcess() API for a secure implementation.
    // Using system() is insecure and should be avoided.
#endif
}

void setup_test_environment() {
    FILE* fp = fopen("test_valid.txt", "w");
    if (fp) {
        fputs("This is a valid test file.", fp);
        fclose(fp);
    }
#if IS_POSIX
    mkdir("test_dir", 0755);
    symlink("test_valid.txt", "test_symlink.txt");
#endif
}

void cleanup_test_environment() {
    remove("test_valid.txt");
#if IS_POSIX
    remove("test_symlink.txt");
    remove("test_dir");
#endif
}

int main() {
    setup_test_environment();

    printf("--- Test Case 1: Valid file ---\n");
    displayFileContent("test_valid.txt");
    printf("\n");

    printf("--- Test Case 2: Non-existent file ---\n");
    displayFileContent("non_existent_file.txt");
    printf("\n");

    printf("--- Test Case 3: Invalid filename (command injection attempt) ---\n");
    displayFileContent("test_valid.txt; ls");
    printf("\n");

    printf("--- Test Case 4: Invalid filename (path traversal attempt) ---\n");
    displayFileContent("../another_file.txt");
    printf("\n");
    
#if IS_POSIX
    printf("--- Test Case 5: Directory instead of file ---\n");
    displayFileContent("test_dir");
    printf("\n");

    printf("--- Test Case 6: Symbolic link ---\n");
    displayFileContent("test_symlink.txt");
    printf("\n");
#endif

    cleanup_test_environment();
    return 0;
}