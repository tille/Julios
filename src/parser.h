#ifndef PARSER_H
#define PARSER_H

#include <string>
#include <vector>
#include <fstream>
#include "yaml-cpp/yaml.h"

using namespace std;

struct ParTransition{
    string in;
    string next;
};

struct ParNode{
    string node;
    vector <ParTransition> next;
};

struct ParAutomata{
    string automata;
    string description;
    string start;
    vector <string> alpha;
    vector <string> states;
    vector <string> final;
    vector <ParNode> delta;
};

void operator >> (const YAML::Node& node, ParTransition &transition);
void operator >> (const YAML::Node& node, ParAutomata &automata);
void operator >> (const YAML::Node& node, ParNode &auNode);

string create_acc_msg(int code, string cadena, string restante);
string create_msg_to_node(string cadena, string restante);
vector <string> parse_node_msg(string data);
vector <string> parse_cmd(string data);
vector <string> parse_acc_msg(string data);

class Parser{

    public:
        Parser();
        vector <ParAutomata> parse_automatas(string location);


};

#endif // PARSER_H
