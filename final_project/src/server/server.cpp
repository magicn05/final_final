#include <arpa/inet.h>
#include <cstring>
#include <iostream>
#include <netinet/in.h>
#include <stdio.h>
#include <string>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <thread>
#include <unistd.h>
#include <vector>
#include <pthread.h>
#include "menu.h"

#include "user.h"
#include "data.h"
#include "user_manager.h"
#include "data_manager.h"
#include "myfile.h"
#include "file_manager.h"

#define MAX_DATA_SIZE 1024
using namespace std;

int start_menu(int sd);
int board(int sd, data_Manager& d_manager);
int download(int sd, data_Manager& d_manager, file_Manager& f_manager, int &f_no);

int f_no = 0;
struct sockaddr_in clientaddr;

user_Manager u_manager;
data_Manager d_manager;
file_Manager f_manager;

class Server_Manager {
public:
  struct sockaddr_in server_addr;
  Server_Manager() {
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(60000);
    this->server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    memset(&(this->server_addr.sin_zero), '\0', 8);
  }
};

void thread_function(int sd) {
  // load users
  int n;
  int a;
  int res = start_menu(sd); // 1번 , 2번의 선택..
  int end_flag = 0;
  char buf[1024];
  char recv_buf[1024];
  if (res == 0) // 0 번 : 연결종료
    close(sd);
  else if (res == 1) { // 1번 : 게시판
    //여기서 게시판 , 자료실, 채팅방 선택
    //download(sd, d_manager, f_manager, f_no);
    while(end_flag != 1){
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", "WINDOW");
    send(sd, buf, strlen(buf), 0);
    
    usleep(0.5);
    
    sprintf(buf, "%s", "안녕하세요. 원하시는 메뉴를 선택해주세요 \n\n");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));

    sprintf(buf, "%s", " [1]. 게시판▦ \n\n");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", " [2]. 자료실♬\n\n");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", " [3]. 채팅방♥\n\n");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", " [4]. 로그아웃\n\n");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    n = recv(sd, recv_buf, sizeof(recv_buf), 0);
    a = atoi(recv_buf);
    switch(a)
    {
      case 1: //게시판
      board(sd, d_manager);
      break;  
      case 2: //자료실
      download(sd, d_manager, f_manager, f_no);

      break;
      case 3: //채팅방
      
      break;
      case 4: //로그아웃
      end_flag = 1;
      break;
    }

    }
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", "WINDOW");
    send(sd, buf, strlen(buf), 0);
    usleep(0.5);
    sprintf(buf, "%s ", "접속이 끊어집니다. 오늘도 좋은 하루 보내세요. ~ \n\n");
    send(sd, buf, strlen(buf), 0);
    sleep(2);
    close(sd);
  }
  return;
}


int main() {
  cout << "S E R V E R          O N" << endl;
  
  data a;
  
  u_manager.add_user(new user("apple","1234","kim","010-1111-2222"));
  u_manager.add_user(new user("banana","1234","park","010-2222-3333"));
  u_manager.add_user(new user("charles","1234","lee","010-2222-4444"));
  
  d_manager.add_data(new data("Book1", "2010-09-10", "apple", "1234", "hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n ",1));
  d_manager.add_data(new data("Book6", "2012-09-10", "apple", "1234", "hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n hello my name is yeppi-yeppi-yo\n ",2));
  d_manager.add_data(new data("Book3", "2011-09-10", "apple", "1234", "hello my name is yeppi-yeppi-yo",13));
  d_manager.add_data(new data("Book6", "2011-09-10", "banana", "1234", "hello my name is yeppi-yeppi-yo",4));
  d_manager.add_data(new data("Book3", "2011-09-10", "david", "1234", "hello my name is yeppi-yeppi-yo",55));
  d_manager.add_data(new data("Book6", "2011-09-10", "charles", "1234", "hello my name is yeppi-yeppi-yo",61));

  int choice;
  int sockfd, new_fd, state;
  socklen_t client_len;
  // struct sockaddr_in clientaddr;
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  Server_Manager Server_Set;
  int reuseAddress = 1;
  int option = 1;

  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));

  if (bind(sockfd, (struct sockaddr *)&(Server_Set.server_addr),
           sizeof(struct sockaddr)) == -1) {
    perror("bind");
    exit(1);
  }

  state = listen(sockfd, 5);
  if (state == -1) {
    perror("listen error : ");
    exit(0);
  }
  while (1) {

    new_fd = accept(sockfd, (struct sockaddr *)&clientaddr, &client_len);
    thread t1(thread_function, new_fd);
    
    t1.detach();
    
  }
}

int start_menu(int sd) {
  string id, name, pin, phone_num;

  char buf[1024];
  char recv_buf[1024];
  int n, a, b;
  int end_flag = 0;
  int out_flag = 0;

  while (end_flag != 1) {
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s", "WINDOW");
    send(sd, buf, strlen(buf), 0);
    sleep(1);
    sprintf(buf, "%s", "S T A R T --- M E N U \n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "메뉴를 선택하세요\n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "1번. 로그인\n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "2번. 회원 가입\n\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "3번. 연결 끊기\n\n");
    send(sd, buf, strlen(buf), 0);
    n = recv(sd, buf, sizeof(buf), 0);
    buf[n] = '\0';
    a = atoi(buf);

    switch (a) {
    case 1:
      sprintf(buf, "%s", "WINDOW");
      send(sd, buf, strlen(buf), 0);
      usleep(0.5);
      sprintf(buf, "%s", "로그인 페이지 입니다. \n\n");
      send(sd, buf, strlen(buf), 0);

      sprintf(buf, "%s", "ID  >> ");
      send(sd, buf, strlen(buf), 0);
      usleep(0.5);
      memset(recv_buf, 0, sizeof(recv_buf));
      n = recv(sd, recv_buf, sizeof(recv_buf), 0);
      usleep(0.5);
      id = recv_buf;
      memset(recv_buf, 0, sizeof(recv_buf));
      usleep(0.5);
      sprintf(buf, "%s", "PIN >> ");
      send(sd, buf, strlen(buf), 0);
      usleep(0.5);
      n = recv(sd, recv_buf, sizeof(recv_buf), 0);
      pin = recv_buf;
      memset(recv_buf, 0, sizeof(recv_buf));

      if (u_manager.check_login(id, pin) == 0) {
        sprintf(buf, "%s", "Log-in Succeed \n\n");
        send(sd, buf, strlen(buf), 0);
        usleep(0.5);
        end_flag = 1;
        out_flag = 1;
        
      } else {
        sprintf(buf, "%s", "Impossible to login \n\n");
        send(sd, buf, strlen(buf), 0);
        usleep(0.5);
        
      }

      memset(buf, 0, sizeof(buf));
      break;

    case 2:
      sprintf(buf, "%s", "WINDOW");
      send(sd, buf, strlen(buf), 0);
      sleep(1);
      sprintf(buf, "%s", "회원가입 페이지 입니다. \n\n");
      send(sd, buf, strlen(buf), 0);

      sprintf(buf, "%s", "New ID  >> ");
      send(sd, buf, strlen(buf), 0);

      n = recv(sd, recv_buf, sizeof(recv_buf), 0);
      id = recv_buf;
      memset(recv_buf, 0, sizeof(recv_buf));

      sprintf(buf, "%s", "New PIN >> ");
      send(sd, buf, strlen(buf), 0);

      n = recv(sd, recv_buf, sizeof(recv_buf), 0);
      pin = recv_buf;
      memset(recv_buf, 0, sizeof(recv_buf));

      sprintf(buf, "%s", "User Name >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, recv_buf, sizeof(recv_buf), 0);
      name = recv_buf;
      memset(recv_buf, 0, sizeof(recv_buf));
      
      sprintf(buf, "%s", "Phone_number >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, recv_buf, sizeof(recv_buf), 0);
      phone_num = recv_buf;
      
      u_manager.add_user(new user(id, pin, name, phone_num));

      sprintf(buf, "%s", "성공적으로 생성되었습니다. 잠시대기");
      send(sd, buf, strlen(buf), 0);
      sleep(1);

      memset(buf, 0, sizeof(buf));
      memset(recv_buf, 0, sizeof(recv_buf));
      break;

    case 3:
      sprintf(buf, "%s", "");
      send(sd, buf, 0, 0);
      end_flag = 1;
      break;

    case 4:

      for (int i = 0; i < u_manager.get_user_cnt(); i++) {
        u_manager.get_user_id(i);
        u_manager.get_user_pin(i);
        u_manager.get_user_name(i);
        u_manager.get_user_phoneNum(i);
        cout << endl;
      }

      break;
    } //switch end
  } // while end

  if (out_flag == 1)
    return 1;
  else 
    return 0;
}
