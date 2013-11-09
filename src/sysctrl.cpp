using namespace std;

#include "state/state.h"
#include "shared.h"
#include "parser/parser.h"

#include <fcntl.h>   
#include <unistd.h>
#include <typeinfo>


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
 
  for(int index = 0; index < str_names.size(); index ++){
    string name = str_names[index];
    ini = init[name];
    act = ini;

    vector <string> visited;
    visited.insert(visited.end(), act.get_name());
    cout << name << "\n";
   
    while(1){
      bool seted = false;
      state next; 
      for( map<string, state>::iterator stateIt = machines[name][act].begin(); stateIt != machines[name][act].end(); stateIt ++ ){
	for(int index = 0; index < visited.size(); index++){
	  bool isPresent = (find(visited.begin(), visited.end(), stateIt->second.get_name()) != visited.end());
	  if((! isPresent) && seted ){
                seted = true;
		next = stateIt->second;
                visited.insert(visited.end(), next.get_name());
          }
	}
        
        cout << stateIt->second.get_name() << "\n";
      }
       act = next;
    }
  } 
}


void usage(const char* name) {
  cerr << "Usage: " << name << " <yamlfile>.yaml" << endl;
  exit(0);
}

int main(int argc, char *argv[]) {
  if (argc != 2) 
    usage(argv[0]);
 
  build_graph(argv[1]);
  while(1){
    //Read comunication pipes
    //Write pipes to process
  }
  return 0;
}
