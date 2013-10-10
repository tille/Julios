using namespace std;

#include "state.h"
#include "shared.h"
#include <yaml-cpp/yaml.h>

// name_s = name state, name_m = name_machine
void manual_fill(){
  string name_s = "A", name_m = "One";
  state b; b.set_name(name_s);

  edges alpha_1;
  alpha_1["aa"] = b;

  states automata_1;
  automata_1[b] = alpha_1;
  
  machines[name_m] = automata_1;
  
  // next state of b with the edge aa
  state next_state = machines[name_m][b]["aa"];
  cout << next_state.get_name() << endl;
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