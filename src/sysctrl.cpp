using namespace std;

#include "state/state.h"
#include "shared.h"
#include "parser/parser.h"

void manual_fill(char *file){
  parser p;
  map<string, states > machines = p.parser_yamfile(file);
  
  // string name_s = "A", name_m = "One";
  // state first_state; 
  // first_state.set_name(name_s);
  // 
  // edges alpha_1;
  // alpha_1["aa"] = first_state;
  // 
  // states automata_1;
  // automata_1[first_state] = alpha_1;
  // 
  // machines[name_m] = automata_1;
  // 
  // // next state of first_state with the edge aa in the automata name_m
  // state next_state = machines[name_m][first_state]["aa"];
  // cout << next_state.get_name() << endl;
}

void usage(const char* name) {
  cerr << "Usage: " << name << " <yamlfile>.yaml" << endl;
  exit(0);
}

int main(int argc, char *argv[]) {
  if (argc != 2) 
    usage(argv[0]);
  
  manual_fill(argv[1]);
  return 0;
}