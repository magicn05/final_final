#include "data.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

data::data(){
  this->data_title = "";
  this->data_date = "";
  this->data_owner = "";
  this->data_passwd = "";
  this->contents = "";
  this->postno = 0;
  this->replyno = 0;
}

data::~data(){
}

data::data(string data_title, string data_date, string data_owner, string data_passwd, string contents, int postno){
  this->data_title = data_title;
  this->data_date = data_date;
  this->data_owner = data_owner;
  this->data_passwd = data_passwd;
  this->contents = contents;
  this->postno = postno;
  this->replyno = 0;
}

string data::get_title(){
  return this->data_title;
}

string data::get_date(){
  return this->data_date;
}

string data::get_owner(){
  return this->data_owner;
}

string data::get_passwd(){
  return this->data_passwd;
}

string data::get_contents(){
  return this->contents;
}

int data::get_postno(){
  return this->postno;
}

void data::add_reply(string reply_text){
  reply_list.push_back(reply_text);
  replyno++;
}

