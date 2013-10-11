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

void parser::parser_yamfile(char *filename) {
  ifstream fin(filename);

  YAML::Parser parser(fin);
  YAML::Node doc;

  parser.GetNextDocument(doc);
  // cout << doc.size() << endl;

  // for (unsigned i = 0; i < doc.size(); i++) {
  //   invoice ivc;
  //   doc[i] >> ivc;
  //   ivcs->push_back(ivc);
  // }
  // 
  // return *ivcs;
}

void parser::parser_IO(){
}

void parser::parser_sysctrl(){
}

void parser::parser_state(){
}