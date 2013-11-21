#include "automata.h"
#include "node.h"

#include <unistd.h>
#include <algorithm>

Automata::Automata(string name, string description, string start,
                   vector <string> states, vector <string> final, vector <ParNode> nodes, vector <string> alpha){
    this->name = name;
    this->description = description;
    this->start = start;
    this->states = states;
    this->final = final;
    this->nodes = nodes;
    this->alpha = alpha;

    for(unsigned i = 0; i < nodes.size(); i++){
        bool isStart = start == (nodes[i].node) ? true : false;
        bool isFinal = (find(final.begin(), final.end(), nodes[i].node) != final.end());
        Node *node = new Node(nodes[i].node, isStart, isFinal, this->alpha, this->name);
        this->nodeMap.insert(make_pair(nodes[i].node, node));
    }

    for(unsigned i = 0; i < nodes.size(); i++){
        map <string, Node*> delta;
        for(unsigned j = 0; j < nodes[i].next.size(); j++){
            delta.insert(make_pair(nodes[i].next[j].in, this->nodeMap[nodes[i].next[j].next]));
        }
        this->nodeMap[nodes[i].node]->set_delta(delta);
    }

    this->prepare_pipes();
}

string Automata::get_name(){
    return this->name;
}

Node *Automata::get_node(string name){
    return this->nodeMap[name];
}

Node *Automata::get_start(){
    for(unsigned i = 0; i < nodes.size(); i++){
        if (this->nodeMap[nodes[i].node]->isStart)
            return this->nodeMap[nodes[i].node];
    }
}

void Automata::prepare_pipes(){
    for(unsigned i = 0; i < nodes.size(); i++){
        Node *from = this->nodeMap[nodes[i].node];
        for(unsigned j = 0; j < nodes[i].next.size(); j++){
            int fd[2];
            pipe(fd);

            Node *to = this->nodeMap[nodes[i].next[j].next];
            from->add_pipe(string("write"), string(to->get_name()), fd[1]);
            to->add_pipe(string("read"), string(from->get_name()), fd[0]);
        }
    }
}

void Automata::run(){
    for(unsigned i = 0; i < nodes.size(); i++){        
        this->nodeMap[nodes[i].node]->run();
    }
}

