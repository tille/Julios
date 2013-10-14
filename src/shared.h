#ifndef SHARED_H
#define SHARED_H

using namespace std;

// runs by default in gcc >= 4.7, https://gist.github.com/eduarc/6022859
#include "../lib/stdc++.h"

struct classcomp {
  bool operator() (state that, state me){
    string name_1 = that.get_name();
    string name_2 = me.get_name();
    int comp = name_1.compare(name_2);
    bool res = (comp<0)?true:false;
    return res;
  }
};

typedef map<string, state > edges;
typedef map<state, edges, classcomp > states;
typedef map<state, bool, classcomp > is_final;

#endif