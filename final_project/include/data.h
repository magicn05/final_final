#ifndef _DATA_H_
#define _DATA_H_
#include <string>
#include <iostream>
#include <vector>
using namespace std;

class data{
  private:
  string data_title;
  string data_date;
  string data_owner;
  string data_passwd;
  string contents;
  int postno;
  vector<string> reply_list;
  int replyno;

  public:
  data();
  data(string data_title, string data_date, string data_owner, string data_passwd, string contents, int postno);
  ~data();
  string get_title();
  string get_date();
  string get_owner();
  string get_passwd();
  string get_contents();  
  int get_postno();
  void add_reply(string reply_text);
};

#endif