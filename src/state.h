#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>
#include <iostream>
#include <sstream>

using namespace std;

class state{
  public:
    state();
    ~state();
    
    void set_name( string name_p );
    string get_name();

    void set_description( string description_p );
    string get_description();
  
  private:
    string name;
    string description;
};

#endif
