#include "parser.h"

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void operator >> (const YAML::Node& node, ParTransition &transition) {
    node["in"] >> transition.in;
    node["next"] >> transition.next;
}

void operator >> (const YAML::Node& node, ParNode &auNode){
    node["node"] >> auNode.node;
    const YAML::Node& transitions = node["trans"];
    for(unsigned i = 0; i < transitions.size(); i++) {
       ParTransition transition;
       transitions[i] >> transition;
       auNode.next.push_back(transition);
    }
}

void operator >> (const YAML::Node& node, ParAutomata &automata){
    node["automata"] >> automata.automata;
    node["description"] >> automata.description;
    node["start"] >> automata.start;

    const YAML::Node& alpha = node["alpha"];
    for(unsigned i = 0; i < alpha.size(); i++) {
        string nd;
        alpha[i] >> nd;
        automata.alpha.push_back(nd);
    }

    const YAML::Node& states = node["states"];
    for(unsigned i = 0; i < states.size(); i++) {
        string st;
        states[i] >> st;
        automata.states.push_back(st);
    }

    const YAML::Node& final = node["final"];
    for(unsigned i = 0; i < final.size(); i++) {
        string fin;
        final[i] >> fin;
        automata.final.push_back(fin);
    }

    const YAML::Node& delta = node["delta"];
    for(unsigned i = 0; i < delta.size(); i++) {
       ParNode node;
       delta[i] >> node;
       automata.delta.push_back(node);
    }
}

vector <ParAutomata> Parser::parse_automatas(string location){
    vector <ParAutomata> automatas;

    ifstream file(location.c_str());

    YAML::Parser parser(file);
    YAML::Node doc;

    parser.GetNextDocument(doc);
    for(unsigned i = 0; i < doc.size(); i++) {
       ParAutomata automata;
       doc[i] >> automata;
       automatas.push_back(automata);
    }

    return automatas;
}

string create_msg_to_node(string cadena, string restante){
    YAML::Emitter out;
    out.SetMapFormat(YAML::Flow);
    out << YAML::BeginMap;
    out << YAML::Key << "recog";
    out << YAML::Value << cadena.c_str();
    out << YAML::Key << "rest";
    out << YAML::Value << restante.c_str();
    out << YAML::EndMap;

    return string (out.c_str());
}

vector <string> parse_node_msg(string data){
    std::stringstream ss(data);
    YAML::Parser parser(ss);
    YAML::Node doc;

    string aux;
    vector <string> res;
    parser.GetNextDocument(doc);
    doc ["recog"] >> aux;
    res.push_back(aux);
    doc ["rest"] >> aux;
    res.push_back(aux);

    return res;
}

string create_acc_msg(int code, string cadena, string restante){
    YAML::Emitter out;
    out.SetMapFormat(YAML::Flow);
    out << YAML::BeginMap;
    out << YAML::Key << "codterm";
    out << YAML::Value << code;
    out << YAML::Key << "recog";
    out << YAML::Value << cadena.c_str();
    out << YAML::Key << "rest";
    out << YAML::Value << restante.c_str();
    out << YAML::EndMap;

    return string (out.c_str());
}


vector <string> parse_acc_msg(string data){
    std::stringstream ss(data);
    YAML::Parser parser(ss);
    YAML::Node doc;

    string aux;
    vector <string> res;
    parser.GetNextDocument(doc);
    doc ["codterm"] >> aux;
    res.push_back(aux);
    doc ["recog"] >> aux;
    res.push_back(aux);
    doc ["rest"] >> aux;
    res.push_back(aux);

    return res;
}


vector <string> parse_cmd(string data){
    std::stringstream ss(data);
    YAML::Parser parser(ss);
    YAML::Node doc;

    string aux;
    vector <string> res;
    parser.GetNextDocument(doc);
    doc ["cmd"] >> aux;
    res.push_back(aux);
    doc ["msg"] >> aux;
    res.push_back(aux);

    return res;
}

Parser::Parser(){}




