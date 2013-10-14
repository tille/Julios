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

    map<string, states> parser_yamfile(char *filename);
    map<string, state> get_init();
    vector<string> get_automatas_names();
    map<string, is_final> get_final_states();

    void parser_IO();
    void parser_sysctrl();
    void parser_state();
    

  private:
    map<string, state> init_states;
    map<string, is_final> final_states;
    vector<string> names;
};

#endif
