#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/select.h>
#include <time.h>

#define MAX_INPUT_LENGTH 256
#define MAX_OUTPUT_BYTES 100000
#define TIMEOUT_SECONDS 5

static int has_forbidden_chars(const char *s) {
    const char *forbidden = ";|&`$()<>\"'\\";
    for (; *s; ++s) {
        if (strchr(forbidden, *s) != NULL) return 1;
    }
    return 0;
}

static int safe_echo_token(const char *t) {
    size_t len = strlen(t);
    if (len == 0 || len > 64) return 0;
    for (size_t i = 0; i < len; ++i) {
        unsigned char c = (unsigned char)t[i];
        if (!(isalnum(c) || c == '.' || c == '_' || c == ',' || c == '@' || c == ':' || c == '+' || c == '-')) {
            return 0;
        }
    }
    return 1;
}

static char** split_ws(const char *s, int *count) {
    // Simple whitespace split; caller must free the vector and tokens
    int cap = 8;
    int n = 0;
    char **tokens = (char**)malloc(sizeof(char*) * cap);
    if (!tokens) return NULL;

    const char *p = s;
    while (*p) {
        while (*p && isspace((unsigned char)*p)) p++;
        if (!*p) break;
        const char *start = p;
        while (*p && !isspace((unsigned char)*p)) p++;
        size_t len = (size_t)(p - start);
        char *tok = (char*)malloc(len + 1);
        if (!tok) { // cleanup
            for (int i = 0; i < n; ++i) free(tokens[i]);
            free(tokens);
            return NULL;
        }
        memcpy(tok, start, len);
        tok[len] = '\0';
        if (n >= cap) {
            cap *= 2;
            char **tmp = (char**)realloc(tokens, sizeof(char*) * cap);
            if (!tmp) {
                for (int i = 0; i < n; ++i) free(tokens[i]);
                free(tokens);
                free(tok);
                return NULL;
            }
            tokens = tmp;
        }
        tokens[n++] = tok;
    }
    *count = n;
    return tokens;
}

static void free_tokens(char **tokens, int count) {
    if (!tokens) return;
    for (int i = 0; i < count; ++i) free(tokens[i]);
    free(tokens);
}

static char* exec_argv(const char *baseDir, char **argv) {
    int pipefd[2];
    if (pipe(pipefd) == -1) {
        char *res = strdup("ERROR: pipe failed.");
        return res ? res : NULL;
    }

    pid_t pid = fork();
    if (pid < 0) {
        close(pipefd[0]); close(pipefd[1]);
        char *res = strdup("ERROR: fork failed.");
        return res ? res : NULL;
    }

    if (pid == 0) {
        // Child
        dup2(pipefd[1], STDOUT_FILENO);
        dup2(pipefd[1], STDERR_FILENO);
        close(pipefd[0]);
        close(pipefd[1]);

        if (baseDir && baseDir[0]) {
            if (chdir(baseDir) != 0) {
                const char *msg = "chdir failed\n";
                write(STDERR_FILENO, msg, strlen(msg));
                _exit(127);
            }
        }
        execvp(argv[0], argv);
        const char *msg = "exec failed\n";
        write(STDERR_FILENO, msg, strlen(msg));
        _exit(127);
    }

    // Parent
    close(pipefd[1]);
    int flags = fcntl(pipefd[0], F_GETFL, 0);
    fcntl(pipefd[0], F_SETFL, flags | O_NONBLOCK);

    size_t cap = 2048;
    size_t len = 0;
    char *output = (char*)malloc(cap);
    if (!output) {
        close(pipefd[0]);
        int status;
        waitpid(pid, &status, 0);
        return strdup("ERROR: memory allocation failed.");
    }

    int status = 0;
    time_t start = time(NULL);
    int child_exited = 0;

    while (1) {
        char buf[4096];
        ssize_t r = read(pipefd[0], buf, sizeof(buf));
        if (r > 0) {
            size_t toWrite = (size_t)r;
            if (len + toWrite > MAX_OUTPUT_BYTES) {
                toWrite = (len + toWrite > MAX_OUTPUT_BYTES) ? (MAX_OUTPUT_BYTES - len) : toWrite;
            }
            if (toWrite > 0) {
                if (len + toWrite + 1 > cap) {
                    size_t newcap = cap;
                    while (len + toWrite + 1 > newcap) newcap *= 2;
                    char *tmp = (char*)realloc(output, newcap);
                    if (!tmp) {
                        free(output);
                        close(pipefd[0]);
                        kill(pid, SIGKILL);
                        waitpid(pid, &status, 0);
                        return strdup("ERROR: memory allocation failed.");
                    }
                    output = tmp;
                    cap = newcap;
                }
                memcpy(output + len, buf, toWrite);
                len += toWrite;
                output[len] = '\0';
            }
        }

        int w = waitpid(pid, &status, WNOHANG);
        if (w == pid) {
            child_exited = 1;
            // Drain rest
            while ((r = read(pipefd[0], buf, sizeof(buf))) > 0) {
                size_t toWrite = (size_t)r;
                if (len + toWrite > MAX_OUTPUT_BYTES) {
                    toWrite = (len + toWrite > MAX_OUTPUT_BYTES) ? (MAX_OUTPUT_BYTES - len) : toWrite;
                }
                if (toWrite == 0) break;
                if (len + toWrite + 1 > cap) {
                    size_t newcap = cap;
                    while (len + toWrite + 1 > newcap) newcap *= 2;
                    char *tmp = (char*)realloc(output, newcap);
                    if (!tmp) {
                        free(output);
                        close(pipefd[0]);
                        return strdup("ERROR: memory allocation failed.");
                    }
                    output = tmp;
                    cap = newcap;
                }
                memcpy(output + len, buf, toWrite);
                len += toWrite;
                output[len] = '\0';
            }
            break;
        }

        if (difftime(time(NULL), start) >= TIMEOUT_SECONDS) {
            kill(pid, SIGKILL);
            waitpid(pid, &status, 0);
            close(pipefd[0]);
            free(output);
            return strdup("ERROR: execution timed out.");
        }

        fd_set rfds;
        FD_ZERO(&rfds);
        FD_SET(pipefd[0], &rfds);
        struct timeval tv;
        tv.tv_sec = 0;
        tv.tv_usec = 100 * 1000;
        select(pipefd[0] + 1, &rfds, NULL, NULL, &tv);
    }

    close(pipefd[0]);

    int exit_code = 0;
    if (child_exited) {
        if (WIFEXITED(status)) exit_code = WEXITSTATUS(status);
        else if (WIFSIGNALED(status)) exit_code = 128 + WTERMSIG(status);
        else exit_code = 1;
    }

    // Build final result string: "exit=X\n" + output
    char header[64];
    snprintf(header, sizeof(header), "exit=%d\n", exit_code);
    size_t header_len = strlen(header);
    size_t total_len = header_len + len;
    char *result = (char*)malloc(total_len + 1);
    if (!result) {
        free(output);
        return strdup("ERROR: memory allocation failed.");
    }
    memcpy(result, header, header_len);
    if (len > 0) memcpy(result + header_len, output, len);
    result[total_len] = '\0';
    free(output);
    return result;
}

char* executeValidatedCommand(const char *baseDir, const char *userInput) {
    if (!baseDir || baseDir[0] == '\0') return strdup("ERROR: invalid base directory.");
    if (!userInput) return strdup("ERROR: null input.");

    // Trim
    const char *start = userInput;
    while (*start && isspace((unsigned char)*start)) start++;
    const char *end = userInput + strlen(userInput);
    while (end > start && isspace((unsigned char)*(end - 1))) end--;
    size_t in_len = (size_t)(end - start);
    if (in_len == 0 || in_len > MAX_INPUT_LENGTH) return strdup("ERROR: input length invalid.");

    char *input = (char*)malloc(in_len + 1);
    if (!input) return strdup("ERROR: memory allocation failed.");
    memcpy(input, start, in_len);
    input[in_len] = '\0';

    if (has_forbidden_chars(input)) {
        free(input);
        return strdup("ERROR: input contains forbidden characters.");
    }

    int count = 0;
    char **tokens = split_ws(input, &count);
    free(input);
    if (!tokens) return strdup("ERROR: tokenization failed.");
    if (count == 0) {
        free_tokens(tokens, count);
        return strdup("ERROR: empty command.");
    }

    const char *cmd = tokens[0];
    int allowed = 0;
    const char *allowed_cmds[] = {"echo","date","uname","whoami","pwd","ls"};
    for (size_t i = 0; i < sizeof(allowed_cmds)/sizeof(allowed_cmds[0]); ++i) {
        if (strcmp(cmd, allowed_cmds[i]) == 0) { allowed = 1; break; }
    }
    if (!allowed) {
        free_tokens(tokens, count);
        return strdup("ERROR: command not allowed.");
    }

    // Build argv based on validation rules
    // Maximum args small; allocate dynamically
    char **argv = NULL;
    int argc = 0;
    int cap = 0;

    #define PUSH_ARG(s) do { \
        if (argc >= cap) { \
            cap = cap ? cap*2 : 8; \
            char **tmp = (char**)realloc(argv, sizeof(char*)*cap); \
            if (!tmp) { \
                if (argv) free(argv); \
                free_tokens(tokens, count); \
                return strdup("ERROR: memory allocation failed."); \
            } \
            argv = tmp; \
        } \
        argv[argc++] = (char*)(s); \
    } while(0)

    if (strcmp(cmd, "echo") == 0) {
        PUSH_ARG("echo");
        for (int i = 1; i < count; ++i) {
            if (!safe_echo_token(tokens[i])) {
                if (argv) free(argv);
                free_tokens(tokens, count);
                return strdup("ERROR: echo argument contains invalid characters or length.");
            }
            PUSH_ARG(tokens[i]);
        }
    } else if (strcmp(cmd, "date") == 0) {
        if (count != 1) {
            if (argv) free(argv);
            free_tokens(tokens, count);
            return strdup("ERROR: 'date' takes no arguments.");
        }
        PUSH_ARG("date");
    } else if (strcmp(cmd, "whoami") == 0) {
        if (count != 1) {
            if (argv) free(argv);
            free_tokens(tokens, count);
            return strdup("ERROR: 'whoami' takes no arguments.");
        }
        PUSH_ARG("whoami");
    } else if (strcmp(cmd, "pwd") == 0) {
        if (count != 1) {
            if (argv) free(argv);
            free_tokens(tokens, count);
            return strdup("ERROR: 'pwd' takes no arguments.");
        }
        PUSH_ARG("pwd");
    } else if (strcmp(cmd, "uname") == 0) {
        if (count == 1) {
            PUSH_ARG("uname");
        } else if (count == 2 &&
                   (strcmp(tokens[1], "-a") == 0 || strcmp(tokens[1], "-s") == 0 ||
                    strcmp(tokens[1], "-r") == 0 || strcmp(tokens[1], "-m") == 0)) {
            PUSH_ARG("uname");
            PUSH_ARG(tokens[1]);
        } else {
            if (argv) free(argv);
            free_tokens(tokens, count);
            return strdup("ERROR: invalid 'uname' usage.");
        }
    } else if (strcmp(cmd, "ls") == 0) {
        if (count == 1) {
            PUSH_ARG("ls");
        } else if (count == 2 &&
                   (strcmp(tokens[1], "-l") == 0 || strcmp(tokens[1], "-a") == 0 ||
                    strcmp(tokens[1], "-la") == 0 || strcmp(tokens[1], "-al") == 0)) {
            PUSH_ARG("ls");
            PUSH_ARG(tokens[1]);
        } else {
            if (argv) free(argv);
            free_tokens(tokens, count);
            return strdup("ERROR: only simple 'ls' flags allowed (no paths).");
        }
    } else {
        if (argv) free(argv);
        free_tokens(tokens, count);
        return strdup("ERROR: command not allowed.");
    }

    PUSH_ARG(NULL); // null-terminate argv for execvp

    char *result = exec_argv(baseDir, argv);

    // argv uses pointers to tokens; do not free individual strings
    if (argv) free(argv);
    free_tokens(tokens, count);
    return result;
}

int main(void) {
    char cwd[4096];
    const char *baseDir = getcwd(cwd, sizeof(cwd)) ? cwd : ".";

    const char *tests[] = {
        "echo Hello_World",
        "date",
        "uname -s",
        "ls -a",
        "ls /" // should be rejected
    };
    for (size_t i = 0; i < sizeof(tests)/sizeof(tests[0]); ++i) {
        char *res = executeValidatedCommand(baseDir, tests[i]);
        printf("TEST> %s\n", tests[i]);
        if (res) {
            printf("%s\n", res);
            free(res);
        } else {
            printf("ERROR: execution failure.\n");
        }
        printf("----\n");
    }

    printf("Enter a command:\n");
    char line[512];
    if (fgets(line, sizeof(line), stdin) != NULL) {
        // strip newline
        size_t L = strlen(line);
        if (L > 0 && (line[L-1] == '\n' || line[L-1] == '\r')) line[L-1] = '\0';
        char *res = executeValidatedCommand(baseDir, line);
        if (res) {
            printf("%s\n", res);
            free(res);
        } else {
            printf("ERROR: execution failure.\n");
        }
    } else {
        printf("ERROR: failed to read input.\n");
    }
    return 0;
}