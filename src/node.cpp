#include "node.h"
#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/select.h>
#include <algorithm>
#include <numeric>
#include <vector>
#include <iterator>
#include <unistd.h>
#include "parser.h"
#include <sys/prctl.h>


Node::Node(string name, bool isStart, bool isFinal, vector <string> alpha, string autNam){
    this->name = name;
    this->isStart = isStart;
    this->isFinal = isFinal;
    this->autNam = autNam;
}

string Node::get_name(){
    return this->name;
}

void Node::set_delta(map<string, Node *> delta){
    this->delta = delta;
}

Node *Node::get_next(string input){
    return this->delta [input];
}

void Node::add_pipe(string direction, string node, int pipe){
    this->pipes[direction][node] = pipe;
}


void Node::run(){

    this->pid = fork();

    if (pid == -1){}//Broken piepe message
    if (pid ==  1){}//father process

    if (pid == 0){
        string procNam;
        procNam += this->autNam;
        procNam += this->name;
        prctl(PR_SET_NAME, (unsigned long)procNam.c_str(), 0, 0, 0);
        while(true){
            fd_set input;
            FD_ZERO(&input);

            map <string, int> inputPipes = this->pipes["read"];

            vector <int> pipesDescript;
            typedef map<string, int>::iterator it_type;
            for(it_type iterator = inputPipes.begin(); iterator != inputPipes.end(); iterator++) {
                FD_SET(iterator->second, &input);
                pipesDescript.push_back(iterator->second);
            }

            int max_fd = *( max_element( pipesDescript.begin(), pipesDescript.end() ) );

            bool isIn = false;
            char message[MAX_BUFFER];
            select(max_fd + 1, &input, NULL, NULL, NULL);
            for(unsigned i = 0; i < pipesDescript.size(); i++){
                if (FD_ISSET(pipesDescript[i], &input)){
                    read (pipesDescript[i], message, MAX_BUFFER);
                    vector <string> data = parse_node_msg(string(message));

                    typedef map<string, Node*>::iterator it_type;
                    for(it_type iterator = delta.begin(); iterator != delta.end(); iterator++) {
                        if(data[1].find(iterator->first) == 0){
                            isIn = true;
                            data[1].erase(0, iterator->first.size());
                            data[0] += iterator->first;
                            string msg = create_msg_to_node(string(data[0]), string(data[1]));
                            write(this->pipes["write"][this->delta[iterator->first]->get_name()], msg.c_str(), MAX_BUFFER);
                            break;
                        }
                    }

                    if(data[1] == "" && isFinal){
                        string msg = create_acc_msg(0, data[0], data[1]);
                        write(this->pipes["write"]["sysctrl"], msg.c_str(), MAX_BUFFER);
                    }else if(!isIn){
                        string msg = create_acc_msg(1, data[0], data[1]);
                        write(this->pipes["write"]["sysctrl"], msg.c_str(), MAX_BUFFER);
                    }
                }
            }
        }
    }
}
