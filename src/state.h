// #ifndef STATE_H 
// #define STATE_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class state{

 public:
  state(){
    cout << "hola mundo" << endl;
  }
  
  void set_name();

 private:
  int name;
  string description;
};
// 
// #endif
