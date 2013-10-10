using namespace std;
#include <yaml-cpp/yaml.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <cstdlib>
#include "state.h"

// map<string, map<state, map<string,state> > > machines;

void manual_fill(){
  state node;
  node_1.set_name();
  // machines[name_1][node_1]["aa"] = node_1;
}

void usage(const char* name) {
  cerr << "Usage: " << name << " <yamlfile>.yaml" << endl;
  exit(0);
}

int main(int argc, char *argv[]) {
  // if (argc != 2) 
  //   usage(argv[0]);
  
  manual_fill();
  return 0;
}