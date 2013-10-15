using namespace std;

#include "state/state.h"
#include "shared.h"
#include "parser/parser.h"

void build_graph(char *file){
  parser p;

  map<string, states> machines = p.parser_yamfile(file);
  map<string, state> init = p.get_init();
  vector<string> str_names = p.get_automatas_names();
  map<string, is_final> final = p.get_final_states();

  // para el automata 1, (0 indexed)
  state act, ini;
  string name = str_names[0];
  
  ini = init[name];
  act = machines[name][ini]["a"];
  act = machines[name][act]["c"];
  cout << act.get_name() << endl;
  cout << "Es estado de fin: " << final[name][act] << endl;
  act.run();
}

void usage(const char* name) {
  cerr << "Usage: " << name << " <yamlfile>.yaml" << endl;
  exit(0);
}

int main(int argc, char *argv[]) {
  if (argc != 2) 
    usage(argv[0]);
 
  build_graph(argv[1]);
  //while(1){}
  return 0;
}
