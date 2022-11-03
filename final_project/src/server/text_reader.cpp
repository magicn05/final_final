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
#include <vector>
using namespace std;

int text_reader(int sd, int selection, data_Manager &d_manager, data* temp_data) {
  
  string temp;
  char buf[1024];
  char recv_buf[1024];
  int a;
  int end_flag = 0;
  sprintf(buf, "%s", "WINDOW");
  send(sd, buf, strlen(buf), 0);
  usleep(0.5);
  cout << "selection : " << selection << endl;

  int n ;
  for(int i=0; i<d_manager.get_data_cnt(); i++){
    if ((d_manager.get_data_postno(i)) == selection){
      n = i;
    }
  }

  cout << "n : " << n << endl;

  while (end_flag != 1) {

    sprintf(buf, "%s",
            "=================================================================="
            "===============\n");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));

    sprintf(buf, "%s",
            "Title : ");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));

    temp = "            " + d_manager.get_data_title(n);
    temp = temp + '\n';
    strcpy(buf, temp.c_str());
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s",
            "=================================================================="
            "===============\n");
    temp.clear();
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s",
            "Written by : ");
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    temp = "            " + d_manager.get_data_owner(n);
    temp = temp + '\n';
    strcpy(buf, temp.c_str());
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s",
            "=================================================================="
            "===============\n\n");
    send(sd, buf, strlen(buf), 0);
    temp.clear();

    temp = d_manager.get_data_contents(n);
    temp = temp + '\n';
    temp = temp + '\n';
    //buf[temp.size()] = '\n';
    //buf[temp.size()] = '\n';
    
    strcpy(buf, temp.c_str());
    send(sd, buf, strlen(buf), 0);
    memset(buf, 0, sizeof(buf));
    sprintf(buf, "%s",
            "=================================================================="
            "===============\n");
    send(sd, buf, strlen(buf), 0);
    temp.clear();
    d_manager.get_data_owner(n);

    sprintf(buf, "%s", "[1]. 추천하기\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "[2]. 댓글달기\n");
    send(sd, buf, strlen(buf), 0);
    sprintf(buf, "%s", "[3]. 돌아가기\n");
    send(sd, buf, strlen(buf), 0);
    usleep(0.5);
    n = recv(sd, recv_buf, sizeof(recv_buf), 0);
    a = atoi(recv_buf);
    switch (a) {
    case 1: //추천하기
      sprintf(buf, "%s", "추천하였습니다.");
      send(sd, buf, strlen(buf), 0);
      sleep(2);
      sprintf(buf, "%s", "WINDOW");
      send(sd, buf, strlen(buf), 0);
      usleep(0.5);
      break;

    case 2: //댓글 작성
      temp.clear();
      sprintf(buf, "%s", "댓글을 입력하세요 >> ");
      send(sd, buf, strlen(buf), 0);
      n = recv(sd, recv_buf, sizeof(recv_buf), 0);
      temp = recv_buf;
      cout << temp_data->get_contents() << endl;
      //d_manager.put_data_reply(n, temp);
      usleep(0.5);
      break;

    case 3: // 돌아가기
      end_flag = 1;
      sprintf(buf, "%s", "WINDOW");
      send(sd, buf, strlen(buf), 0);
      usleep(0.5);
      break;
    }
  }

  return 0;
}