// C
// This is a very simplified version and should be expanded for a production environment
// This is the server part
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

#define MAX_CLIENTS 100
#define BUFFER_SZ 2048

static int uid = 10;

int client_count = 0;
int client_sockets[MAX_CLIENTS];
char client_names[MAX_CLIENTS][32];

pthread_mutex_t clients_mutex = PTHREAD_MUTEX_INITIALIZER;

void str_overwrite_stdout() {
  printf("\r%s", "> ");
  fflush(stdout);
}

void str_trim_lf (char* arr, int length) {
  int i;
  for (i = 0; i < length; i++) { // trim 

    if (arr[i] == '\n') {
      arr[i] = '\0';
      break;
    }
  }
}

void queue_add(int s) {
  pthread_mutex_lock(&clients_mutex);

  for(int i=0; i < MAX_CLIENTS; ++i){
    if(client_sockets[i] == 0){
      client_sockets[i] = s;
      break;
    }
  }

  ++client_count;
  pthread_mutex_unlock(&clients_mutex);
}

void queue_remove(int s) {
  pthread_mutex_lock(&clients_mutex);

  for(int i=0; i < MAX_CLIENTS; ++i){
    if(client_sockets[i] == s){
      client_sockets[i] = 0;
      break;
    }
  }

  --client_count;
  pthread_mutex_unlock(&clients_mutex);
}

void send_message(char *s, int uid) {
  pthread_mutex_lock(&clients_mutex);

  for(int i=0; i<MAX_CLIENTS; ++i){
    if(client_sockets[i] != 0){
      if(client_sockets[i] != uid) {
        if(send(client_sockets[i], s, strlen(s), 0) == -1){
          perror("Error sending message");
        }
      }
    }
  }

  pthread_mutex_unlock(&clients_mutex);
}

void *handle_client(void *arg){
  char name[32];
  char recv_buf[BUFFER_SZ];
  char send_buf[BUFFER_SZ];
  int leave_flag = 0;

  cli_count_mutex.lock();
  strcpy(name, client_names[client_count]);
  cli_count_mutex.unlock();

  int client_sock = *(int*)arg;

  if(recv(client_sock, name, 32, 0) <= 0 || strlen(name) <  2 || strlen(name) >= 32-1){
    printf("Didn't enter the name.\n");
    leave_flag = 1;
  } else{
    str_trim_lf(name, strlen(name));

    sprintf(send_buf, "%s has joined\n", name);
    printf("%s", send_buf);
    send_message(send_buf, client_sock);
  }

  bzero(send_buf, BUFFER_SZ);
  while(1){
    if (leave_flag) {
      break;
    }
    int receive = recv(client_sock, recv_buf, BUFFER_SZ, 0);
    if (receive > 0){
        if(strlen(recv_buf) > 0){
          send_buf[0] = 0;
          strcpy(send_buf, name);
          strcat(send_buf, ": ");
          strcat(send_buf, recv_buf);
          send_message(send_buf, client_sock);

          str_trim_lf(recv_buf, strlen(recv_buf));
          printf("%s -> %s\n", name, recv_buf);
        }
    } else if (receive == 0 || strcmp(recv_buf, "exit") == 0){
      sprintf(send_buf, "%s has left\n", name);
      printf("%s", send_buf);
      send_message(send_buf, client_sock);
      leave_flag = 1;
    } else {
      printf("ERROR: -1\n");
      leave_flag = 1;
    }

    bzero(recv_buf, BUFFER_SZ);
  }

  close(client_sock);
  queue_remove(client_sock);
  free(arg);
  return NULL;
}

int main(){
  int socket_desc, client_sock, c;
  struct sockaddr_in server, client;

  socket_desc = socket(AF_INET, SOCK_STREAM, 0);
  if (socket_desc == -1) {
    printf("Could not create socket");
  }
  puts("Socket created");

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(8888);

  if(bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0){
    perror("Bind failed. Error");
    return 1;
  }
  puts("Bind done");

  listen(socket_desc , 3);

  puts("Waiting for incoming connections...");
  c = sizeof(struct sockaddr_in);

  while(1){
    client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
    if (client_sock < 0){
      perror("Accept failed");
      return 1;
    }
    puts("Connection accepted");

    pthread_t sniffer_thread;
    int *new_sock;
    new_sock = (int*)malloc(1);
    *new_sock = client_sock;

    if( pthread_create( &sniffer_thread , NULL ,  handle_client , (void*) new_sock) < 0){
        perror("Could not create thread");
        return 1;
    }

    puts("Handler assigned");
  }

  return 0;
}