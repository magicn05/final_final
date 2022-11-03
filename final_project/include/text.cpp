#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main()
{
  vector<string> a;
  while(1){
  string temp;
  cin >> temp;
  
  a.push_back(temp);
  for (auto i:a)
    cout << i << endl;
  }

}