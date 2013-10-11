#ifndef PARSER_H
#define PARSER_H

// runs by default in gcc >= 4.7, https://gist.github.com/eduarc/6022859
#include "../../lib/stdc++.h"
#include <yaml-cpp/yaml.h>

#include "../state/state.h"
#include "../shared.h"

using namespace std;

class parser {
  public:
    parser();
    ~parser();

    map<string, states > parser_yamfile(char *filename);
        
    void parser_IO();
    void parser_sysctrl();
    void parser_state();
};

#endif
