#ifndef STATE_H
#define STATE_H

// runs by default in gcc >= 4.7, https://gist.github.com/eduarc/6022859
#include "../lib/stdc++.h"

using namespace std;

class state{
  public:
    state();
    ~state();
    
    void set_name( string name_p );
    string get_name();
    
    void set_description( string description_p );
    string get_description();
    
    bool operator < ( const state &that ) const {
      return false;
    }
    
  private:
    string name;
    string description;
};

#endif
