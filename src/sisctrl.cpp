#include <iostream>
#include <fstream>
#include "parser.h"
#include "automata.h"
#include "yaml-cpp/yaml.h"
#include <unistd.h>
#include <algorithm>

#define MAX_BUFFER 250

using namespace std;

map <string, int> outputPipes;
map <string, int> inputPipes;
void create_pipes(Automata automata);
int getProcIdByName(string procName);

int main()
{
    Parser parser;
    vector <ParAutomata> parAutomatas = parser.parse_automatas("/home/francisco/Workspace/ST0257/example.yaml");
    vector <Automata> automatas;

    for (unsigned i = 0; i < parAutomatas.size(); i++){
        ParAutomata au = parAutomatas[i];
        Automata autom(au.automata, au.description, au.start, au.states, au.final, au.delta, au.alpha);
        automatas.push_back(autom);
        create_pipes(autom);
        autom.run();
    }

    //cout << "Size: " << inputPipes.size() << "\n";

    while(true){
        fd_set input;
        FD_ZERO(&input);
        vector <int> pipesDescript;
        typedef map<string, int>::iterator it_type;
        for(it_type iterator = inputPipes.begin(); iterator != inputPipes.end(); iterator++) {
            FD_SET(iterator->second, &input);
            pipesDescript.push_back(iterator->second);
        }

        FD_SET(0, &input);

        int max_fd = *( max_element( pipesDescript.begin(), pipesDescript.end() ) );

        char message[MAX_BUFFER];
        select(max_fd + 1, &input, NULL, NULL, NULL);

        for(unsigned i = 0; i < pipesDescript.size(); i++){
            if (FD_ISSET(pipesDescript[i], &input)){
                read (pipesDescript[i], message, MAX_BUFFER);
                cout << message << "\n";
                break;
            }else if(FD_ISSET(0, &input)){
                read (0, message, MAX_BUFFER);
                vector <string> data = parse_cmd(string(message));
                if(data[0] == "send"){
                    if(data[1] != ""){
                        for (unsigned i = 0; i < automatas.size(); i++){
                            const char *buffer = create_msg_to_node(string(""), string(data[1])).c_str();
                            int pipe = outputPipes[automatas[i].get_name()];
                            write(pipe, buffer, MAX_BUFFER);
                        }
                    }
                }if(data[0] == "info"){
                    for (unsigned i = 0; i < automatas.size(); i++){
                        for (unsigned j = 0; j < automatas[i].nodes.size(); j++){
                            string procNam;
                            procNam += automatas[i].get_name();
                            procNam += automatas[i].nodeMap[automatas[i].nodes[j].node]->get_name();
                            cout << "PID: " << automatas[i].nodeMap[automatas[i].nodes[j].node]->pid << " Name: " << procNam << "\n";

                        }
                    }
                }if(data[0] == "stop"){
                    return 0;
                }
                break;
            }
        }
    }
    return 0;
}

void create_pipes(Automata automata){
    int fd[2];
    pipe(fd);

    Node *nd = automata.get_start();
    nd->add_pipe(string("read"), string("sysctrl"), fd[0]);
    outputPipes.insert(make_pair(automata.get_name(), fd[1]));


    map <string, Node*> autMap = automata.nodeMap;

    //cout << "Size autMap: " << autMap.size() << "\n";

    typedef map<string, Node*>::iterator it_type;
    for(it_type iterator = autMap.begin(); iterator != autMap.end(); iterator++){
        int fd[2];
        pipe(fd);
        string name = iterator->first;
        Node *node = iterator->second;
        node->add_pipe(string("write"), string("sysctrl"), fd[1]);
        inputPipes.insert(make_pair(name+=automata.get_name(), fd[0]));
    }
}
