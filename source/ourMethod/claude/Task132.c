
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <regex.h>
#include <sys/stat.h>
#include <errno.h>
#include <stdbool.h>

#define LOG_FILE "security_events.log"
#define MAX_MSG_LEN 1024
#define MAX_LOG_ENTRY 2048

typedef enum {
    INFO,
    WARNING,
    ERROR,
    CRITICAL
} Severity;

typedef struct {
    FILE* log_file;
    regex_t valid_msg_regex;
    regex_t email_regex;
    regex_t cc_regex;
    regex_t ssn_regex;
} Task132;

bool initialize_logger(Task132* logger) {
    if (!logger) return false;

    // Open log file with secure permissions
    logger->log_file = fopen(LOG_FILE, "a");
    if (!logger->log_file) {
        fprintf(stderr, "Failed to open log file: %s\\n", strerror(errno));
        return false;
    }

    // Set secure file permissions
    if (chmod(LOG_FILE, S_IRUSR | S_IWUSR) != 0) {
        fprintf(stderr, "Failed to set file permissions: %s\\n", strerror(errno));
        fclose(logger->log_file);
        return false;
    }

    // Compile regex patterns
    if (regcomp(&logger->valid_msg_regex, "^[[:alnum:][:space:]\\\\-.,!?()]+$", REG_EXTENDED) != 0 ||
        regcomp(&logger->email_regex, "[[:alnum:]._%+-]+@[[:alnum:].-]+\\\\.[[:alpha:]]{2,}", REG_EXTENDED) != 0 ||
        regcomp(&logger->cc_regex, "[0-9]{16}", REG_EXTENDED) != 0 ||
        regcomp(&logger->ssn_regex, "[0-9]{3}-[0-9]{2}-[0-9]{4}", REG_EXTENDED) != 0) {
        fprintf(stderr, "Failed to compile regex patterns\\n");
        fclose(logger->log_file);
        return false;
    }

    return true;
}

void cleanup_logger(Task132* logger) {
    if (!logger) return;

    if (logger->log_file) {
        fclose(logger->log_file);
    }
    regfree(&logger->valid_msg_regex);
    regfree(&logger->email_regex);
    regfree(&logger->cc_regex);
    regfree(&logger->ssn_regex);
}

bool is_valid_message(Task132* logger, const char* message) {
    if (!logger || !message) return false;
    return regexec(&logger->valid_msg_regex, message, 0, NULL, 0) == 0;
}

void sanitize_message(Task132* logger, const char* input, char* output, size_t output_size) {
    if (!logger || !input || !output || output_size == 0) return;

    strncpy(output, input, output_size - 1);
    output[output_size - 1] = '\\0';

    // Replace sensitive data patterns
    char* temp = malloc(output_size);
    if (temp) {
        // Replace email addresses
        while (regexec(&logger->email_regex, output, 0, NULL, 0) == 0) {
            strcpy(temp, output);
            char* email_start = strstr(temp, "@");
            if (email_start) {
                *email_start = '\\0';
                snprintf(output, output_size, "[EMAIL]%s", email_start + 1);
            }
        }

        // Replace credit card numbers
        while (regexec(&logger->cc_regex, output, 0, NULL, 0) == 0) {
            strcpy(temp, output);
            char* cc_start = strstr(temp, "****");
            if (cc_start) {
                *cc_start = '\\0';
                snprintf(output, output_size, "****%s", cc_start + 16);
            }
        }

        free(temp);
    }
}

bool log_security_event(', type='text')