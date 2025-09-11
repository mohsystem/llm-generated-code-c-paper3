#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define LOG_FILE "security_events.log"
#define MAX_LINE_LENGTH 256


void log_event(const char *event_type, const char *event_details) {
    time_t now = time(NULL);
    struct tm *localtm = localtime(&now);

    FILE *outfile = fopen(LOG_FILE, "a");
    if (outfile == NULL) {
        fprintf(stderr, "Error writing to log file.\n");
        return;
    }

    char timestamp[20];
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", localtm);

    fprintf(outfile, "%s - %s: %s\n", timestamp, event_type, event_details);
    fclose(outfile);
}


char **monitor_events(int num_events, int *event_count) {

    FILE *infile = fopen(LOG_FILE, "r");
    if (infile == NULL) {
        fprintf(stderr, "Error reading log file.\n");
        *event_count = 0;
        return NULL;
    }

    char **events = NULL;
    char line[MAX_LINE_LENGTH];
    int count = 0;


    while (fgets(line, sizeof(line), infile) != NULL) {
        count++;
        events = realloc(events, count * sizeof(char *));
        if (events == NULL) {

            fclose(infile);
            *event_count = 0;

            for (int i = 0; i < count -1 ; i++) {
                free(events[i]);
            }
            free(events);
            return NULL;
        }
        events[count - 1] = strdup(line);
         if (events[count - 1] == NULL) {
             fclose(infile);
            *event_count = 0;
             for (int i = 0; i < count ; i++) {
                free(events[i]);
            }
            free(events);

             return NULL;
         }


    }
    fclose(infile);

    int start_index = (count > num_events) ? count- num_events: 0;
    *event_count = count >= num_events ? num_events : count;
     char **recent_events = malloc(*event_count * sizeof(char *));
      if (recent_events == NULL) {

            *event_count = 0;

            for (int i = 0; i < count ; i++) {
                free(events[i]);
            }
            free(events);
            return NULL;
        }
    for (int i = 0; i < *event_count; i++) {
         recent_events[i] = strdup(events[start_index + i]);
          if (recent_events[i] == NULL) {

             for (int j = 0; j < i; j++) {
                 free(recent_events[j]);
             }
             free(recent_events);
            *event_count = 0;

            for (int i = 0; i < count ; i++) {
                free(events[i]);
            }
            free(events);
            return NULL;
         }
    }


     for (int i = 0; i < count ; i++) {
         free(events[i]);
     }
     free(events);


    return recent_events;
}

int main() {
    log_event("Login Attempt", "User 'admin' logged in from IP 192.168.1.1");
    log_event("File Access", "User 'user1' accessed file '/etc/passwd'");
    log_event("Network Connection", "Outbound connection to 10.0.0.1:80");
    log_event("System Alert", "CPU usage exceeded 90%");
    log_event("Logout", "User 'admin' logged out.");

    int event_count;
    char **recent_events = monitor_events(3, &event_count);
    for (int i = 0; i < event_count; i++) {
        printf("%s", recent_events[i]);
        free(recent_events[i]);
    }
    free(recent_events);


    log_event("Unauthorized Access Attempt", "Failed login attempt for user 'root'");
    log_event("System Error", "Kernel panic");

     recent_events = monitor_events(2, &event_count);
    for (int i = 0; i < event_count; i++) {
        printf("%s", recent_events[i]);
        free(recent_events[i]);
    }
    free(recent_events);

    return 0;
}