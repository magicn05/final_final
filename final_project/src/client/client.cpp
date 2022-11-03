// #include "macro.h"
// #include <arpa/inet.h>
// #include <dirent.h>
// #include <errno.h>
// #include <linux/unistd.h>
// #include <netdb.h>
// #include <netinet/in.h>
// #include <pthread.h>
// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <unistd.h>

// #define BUFFER_SIZE 1024

// void *writer_thread(void *arg);
// void *reader_thread(void *arg);
// pthread_t tid1, tid2;

// int main(int argc, char *argv[]) {
//   int sockfd, new_fd;
//   struct sockaddr_in serv_addr;
//   int sin_size;

//   if (argc != 2) {
//     fprintf(stderr, "Usage : ./client IP_ADDRESS\n");
//     return 1;
//   }
//   if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
//     perror("socket");
//     exit(1);
//   }

//   serv_addr.sin_family = AF_INET;
//   serv_addr.sin_port = htons(60000);
//   serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
//   memset(&(serv_addr.sin_zero), '\0', 8);

//   if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == -1) {
//     perror("CONNECT");
//     return 1;
//   }

//   system("clear");

//   if (pthread_create(&tid1, NULL, writer_thread, &sockfd) != 0) {
//     perror("pthread_create");
//   }
//   if (pthread_create(&tid2, NULL, reader_thread, &sockfd) != 0) {
//     perror("pthread_create");
//   }

//   pthread_join(tid1, NULL);

//   close(sockfd);

//   return 0;
// }

// void *reader_thread(void *arg) {
//   int sock = *((int *)arg);

//   int n;
//   char buffer[1024];

//   while (1) {
//     n = recv(sock, buffer, 512, 0);
//     if (n <= 0) {
//       printf("\n서버 연결 끊김\n");
//       break;
//     }
//     buffer[n] = '\0';

//     printf("%s", buffer);
//     fflush(stdout);
//   }
//   pthread_cancel(tid1);
//   pthread_exit(NULL);
// }

// void *writer_thread(void *arg) {
//   int sock = *((int *)arg);

//   int n;
//   char buffer[1024];

//   while (1) {
//     fgets(buffer, 1024, stdin);
//     n = strlen(buffer);
//     buffer[n - 1] = '\0';
//     if (!strcmp(buffer, "/q"))
//       break;
//     send(sock, buffer, n, 0);
//   }
//   pthread_cancel(tid2);
//   pthread_exit(NULL);
// }
// Client
#include <arpa/inet.h>
#include <error.h>
#include <iostream>
#include <netdb.h>
#include <netinet/in.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <pthread.h>
#include <cstring>

#define MAX_DATA_SIZE 2048

using namespace std;

pthread_t tid1, tid2;


void *recv_thread(void *arg) {
  int new_fd = *((int *)arg);
  char recv_msg[MAX_DATA_SIZE];
  int n;
  while (1) {
    n = recv(new_fd, recv_msg, MAX_DATA_SIZE, 0);
    if (n<=0){
    cout << "Disconnected from server" << endl;
    break;
    }
    recv_msg[n] = '\0';
    if (strcmp(recv_msg, "WINDOW")==0){
      cout << endl;
      system("clear");
      
    }
    else 
      cout << recv_msg;
    fflush(stdout);
  }
  pthread_cancel(tid2);
  pthread_cancel(tid1);
  pthread_exit(NULL);
  
}

void *send_thread(void *arg) {
  int new_fd = *((int *) arg);
  int n;
  string s;
  char send_msg[MAX_DATA_SIZE];
  while (1) {
    getline(cin, s);    
    if(s == "quit"){
       break;}
    s = s+'\0';
    s.copy(send_msg,s.length());
    n = strlen(send_msg);
    send(new_fd, send_msg, n, 0);
  }
  pthread_cancel(tid1);
  pthread_cancel(tid2);
  pthread_exit(NULL);
  
}

int main(int argc, char *argv[]) {
  int sockfd;
  socklen_t addr_len;
  struct sockaddr_in client_addr;
  struct sockaddr_in server_addr;
  struct hostent *he;
  he = gethostbyname(argv[1]);
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(60000);
  server_addr.sin_addr = *((struct in_addr *)he->h_addr);
  inet_ntoa(server_addr.sin_addr);
  memset(&(server_addr.sin_zero), '\0', 8);
  if (connect(sockfd, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) == -1){
    perror("connet");
    exit(1);
  }
  system("clear");
  cout << "Client Start-------" << endl;

  if (pthread_create(&tid1, NULL, recv_thread, &sockfd) != 0) {
    perror("pthread_create");
  }
  if (pthread_create(&tid2, NULL, send_thread, &sockfd) != 0) {
    perror("pthread_create");
  }
  pthread_join(tid1, NULL);
  pthread_join(tid2, NULL);
  close(sockfd);
  return 0;
}