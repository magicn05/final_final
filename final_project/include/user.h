#ifndef _USER_H
#define _USER_H

#include <string>
using namespace std;

class user {
  string user_id;
  string user_pin;
  string user_name;
  string phone_number;

public:
  user();
  user(string user_id, string user_pin, string user_name, string phone_number);
  ~user();
  string get_userid();
  string get_userpin();
  string get_userName();
  string get_userPhone();
};

#endif