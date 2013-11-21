#ifndef AUTOMATA_H
#define AUTOMATA_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "node.h"
#include "parser.h"

using namespace std;

class Automata{
    public:
        Automata(string name, string description, string start,
        vector <string> states, vector <string> final, vector <ParNode> nodes, vector <string> alpha);
        string get_name();
        Node* get_node(string name);
        Node* get_start();
        void prepare_pipes();
        void run();

        //change to private
        map <string, Node*> nodeMap;
        vector <ParNode> nodes;

    protected:
        string name;
        string start;
        string description;
        vector <string> states;
        vector <string> final;
        vector <string> alpha;

};

#endif // AUTOMATA_H
