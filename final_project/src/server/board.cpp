#include "data.h"
#include "user_manager.h"
#include "data_manager.h"
#include "user.h"
#include <cstring>
#include <iostream>
#include <string>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
using namespace std;

int text_reader(int sd, int n, data_Manager &d_manager, data* temp_data);
int text_writer(int sd, data_Manager &d_manager);

int board(int sd, data_Manager &d_manager ) {
  data* temp_data;
  int end_flag = 0;
  string temp;
  char recv_buf[2048];
  while (end_flag != 1) {

    int a, b, n;
    char buf[1024];
    sprintf(buf, "%s", "게시판 접속 테스트!\n\n");
    send(sd, buf, strlen(buf), 0);
    usleep(0.5);
    sprintf(buf, "%s",
            "=================================================================="
            "===============\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s",
            " [Post No.]                 [TITLE]                    [WRITER]       "
            "[DATE]     [READ]\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s",
            "=================================================================="
            "===============\n");
    send(sd, buf, strlen(buf), 0);
    usleep(0.5);

    for (int i = 0; i < d_manager.get_data_cnt(); i++) {
      memset(buf, 0, sizeof(buf));
      temp = temp + "   ";
      temp = temp + to_string(d_manager.get_data_postno(i));
      temp = temp + "                  ";
      temp = temp + d_manager.get_data_title(i);
      temp = temp + "                       ";
      temp = temp + d_manager.get_data_owner(i);
      temp = temp + "        ";
      temp = temp + d_manager.get_data_date(i);
      cout << "temp : " << temp << endl;
      strcpy(buf, temp.c_str());
      buf[temp.size()] = '\n';
      send(sd, buf, strlen(buf), 0);
      usleep(0.5);
      temp.clear();
    }
    sprintf(buf, "%s",
            "=================================================================="
            "===============\n");
    send(sd, buf, strlen(buf), 0);
    usleep(0.5);
    sprintf(buf, "%s", "[0]. 새로고침\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "[1]. 글 읽기\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "[2]. 글 작성\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "[3]. 글 삭제\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "[4]. 글 검색\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "[5]. 나가기\n");
    send(sd, buf, strlen(buf), 0);
    usleep(0.5);
    n = recv(sd, recv_buf, sizeof(recv_buf), 0);
    //recv_buf[n] = '\0';
    a = atoi(recv_buf);
    switch (a) {
    case 0:
      sprintf(buf, "%s", "WINDOW");
      send(sd, buf, strlen(buf), 0);
      usleep(0.5);
      break;

    case 1: //긁 일기 + 댓글 작성
          int select;
          sprintf(buf, "%s", "조회하고 싶은 글의 번호를 입력하세요 >> ");
          send(sd, buf, strlen(buf), 0);
          n = recv(sd, recv_buf, sizeof(recv_buf), 0);
          a = atoi(recv_buf);

          for (int i = 0; i < d_manager.get_data_cnt(); i++) {
            if ((d_manager.get_data_postno(i)) == a) {
              select = i;
            }
          }

          temp_data = d_manager.data_list[select];
          text_reader(sd, a, d_manager, temp_data);
          memset(recv_buf, 0, sizeof(recv_buf));
      break;

    case 2: // 새글 작성
          sprintf(buf, "%s", "새글을 작성하시겠습니까? [Y/n] ");
          send(sd, buf, strlen(buf), 0);
          n = recv(sd, recv_buf, sizeof(recv_buf), 0);
          text_writer(sd, d_manager);
      break;

    case 3: //
        memset(recv_buf, 0, sizeof(recv_buf));
        sprintf(buf, "%s", "삭제하고 싶은 글의 번호를 입력하세요");
        send(sd, buf, strlen(buf), 0);
        // sprintf(buf, "%s", "남의글을 지울때는 비밀번호를 알아야 합니다.");
        // send(sd, buf, strlen(buf), 0);
        n = recv(sd, recv_buf, sizeof(recv_buf), 0);
        a = atoi(recv_buf);
        for (int i = 0; i < d_manager.get_data_cnt(); i++) {
          if ((d_manager.get_data_postno(i)) == a) {
            select = i;
          }
        }
        (d_manager.data_list).erase((d_manager.data_list).begin()+select);
        d_manager.down_data_cnt();
        
      break;

    case 4:
        sprintf(buf, "%s", "검색하고 싶은 글의 제목을 입력하세요");
        send(sd, buf, strlen(buf), 0);
      break;

    case 5:
      end_flag = 1;
      break;
    }
    usleep(0.5);
    memset(recv_buf, 0, sizeof(recv_buf));
  }

  return 0;
}

// #include <cstring>
// #include <iostream>
// #include <string>
// #include <sys/socket.h>
// #include <sys/types.h>
// #include <unistd.h>
// #include "data.h"
// #include "user.h"
// #include "manager.h"
// using namespace std;

// extern "C" {

// int board(int sd, data_Manager d_manager) {
// //s  d_manager
//   //d_mam.get_data_title(0);
//   char recv_buf[1024];

//   while(1){
//   int a, b, n;
//   char buf[1024];
//   sprintf(buf, "%s", "게시판 접속 테스트!\n\n");
//   send(sd, buf, strlen(buf), 0);
//   usleep(0.5);
//   sprintf(buf, "%s", "입력을 해보세요.\n\n");
//   send(sd, buf, strlen(buf), 0);
//   usleep(0.5);
//   d_manager.get_data_title(0);

//   n = recv(sd, recv_buf, sizeof(recv_buf), 0);
//   memset(recv_buf, 0, sizeof(recv_buf));
//   usleep(0.5);

//   }

//   return 0;
// }

// }
