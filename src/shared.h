#ifndef SHARED_H
#define SHARED_H

using namespace std;

// runs by default in gcc >= 4.7, https://gist.github.com/eduarc/6022859
#include "../lib/stdc++.h"

typedef map<string, state > edges;
typedef map<state, edges > states;

#endif