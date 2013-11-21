#ifndef NODE_H
#define NODE_H

#include <sys/types.h>
#include <string>
#include <vector>
#include <map>

#define MAX_BUFFER 250

using namespace std;

class Node{
    public:
        Node(string name, bool isStart, bool isFinal, vector <string> alpha, string autNam);
        string get_name();
        void set_delta(map <string, Node*> delta);
        Node *get_next(string input);
        void add_pipe (string direction, string node, int pipe);
        void run();

        //change to private whe test finishes
        map <string, map <string, int> > pipes;
        bool isStart, isFinal;
        string autNam;
        pid_t  pid;

    protected:
        string name;
        map <string, Node*> delta;
        vector <string> alpha;
        //map <string, map <string, int> > pipes;
};

#endif // NODE_H
