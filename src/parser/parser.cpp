#include "parser.h"

parser::parser() { }

parser::~parser() { }

// void operator >> (const YAML::Node& node, invoice &invoice) {
//   string id;
//   //string id = node["invoice"];
//   node["invoice"] >> id;
//   string name;
//   node["client"] >> name;
//   invoice.setId(id);
//   invoice.setName(name);
//   //YAML::Node items;
// 
//   const YAML::Node& items = node["items"];
// 
//   for (unsigned i = 0; i < items.size(); i++) {
//     item it; 
//     items[i] >> it;
//     invoice.addItem(it);
//   }
// }

// name_s = name state, name_m = name_machine
map<string, states > parser::parser_yamfile(char *filename) {
  ifstream fin(filename);

  YAML::Parser parser(fin);
  YAML::Node doc;

  parser.GetNextDocument(doc);
  
  
  // fdsafdsaf
  map<string, states > machines;
  map<string, state > matches;
  edges alpha;

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

  for (unsigned i = 0; i < doc.size(); i++) {
    matches.clear();
    string name_m;
    doc[i]["automata"] >> name_m;
    states automata;
    
    const YAML::Node& states_yaml = doc[i]["states"];
    for (int i = 0; i < states_yaml.size(); i++) {
      string act_name;
      state act;

      states_yaml[i] >> act_name;
      act.set_name(act_name);
      matches[act_name] = act;
    }
    
    const YAML::Node& delta = doc[i]["delta"];
    for (int i = 0; i < delta.size(); i++) {
      string act_name; alpha.clear();
      delta[i]["node"] >> act_name;
      state act = matches[act_name];
      
      const YAML::Node& trans = delta[i]["trans"];
      for (int j = 0; j < trans.size(); j++) {
        string symbol, next;
        trans[i]["in"] >> symbol;
        trans[i]["next"] >> next;
        alpha[symbol] = matches[next];
      }
      
      automata[act] = alpha;
    }
    
    machines[name_m] = automata;
    
    if(i==0){
      state ini = matches["A"];
      state next_state = machines["One"][ini]["b"];
      cout << next_state.get_name() << endl;
    }
  }

  return machines;
}

void parser::parser_IO(){
}

void parser::parser_sysctrl(){
}

void parser::parser_state(){
}