#include "parser.h"

parser::parser() { }

parser::~parser() { }

map<string, states > parser::parser_yamfile(char *filename) {
  ifstream fin(filename);
  YAML::Parser parser(fin);
  YAML::Node doc;
  parser.GetNextDocument(doc);

  map<string, states > machines;
  map<string, state > matches;

  for (int i = 0; i < doc.size(); i++) {
    matches.clear(); string name_m; states automata;
    doc[i]["automata"] >> name_m;

    const YAML::Node& states_yaml = doc[i]["states"];
    for (int k = 0; k < states_yaml.size(); k++) {
      string act_name; state act;

      states_yaml[k] >> act_name;
      act.set_name(act_name);
      matches[act_name] = act;
    }

    const YAML::Node& delta = doc[i]["delta"];
    for (int k = 0; k < delta.size(); k++) {
      string act_name; edges alpha;
      delta[k]["node"] >> act_name;
      state act = matches[act_name];

      const YAML::Node& trans = delta[k]["trans"];
      for (int j = 0; j < trans.size(); j++) {
        string symbol, next;
        trans[j]["in"] >> symbol;
        trans[j]["next"] >> next;
        alpha[symbol] = matches[next];
      }
      automata[act] = alpha;
    }

    machines[name_m] = automata;
  }

  return machines;
}

void parser::parser_IO(){
}

void parser::parser_sysctrl(){
}

void parser::parser_state(){
}