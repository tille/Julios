#ifndef STATE_H
#define STATE_H

// runs by default in gcc >= 4.7, https://gist.github.com/eduarc/6022859
#include "../../lib/stdc++.h"
#include <unistd.h>
#include <sys/types.h>
#include <unistd.h>

using namespace std;

class state{
  public:
    state();
    ~state();
    
    void set_name( string name_p );
    string get_name();
    
    void set_description( string description_p );
    string get_description();

    void set_is_final( bool isFinal );
    bool get_is_final();

    void set_is_start( bool isStart );
    bool get_is_start();

    void set_sys_pipe_in( int sysPipeIn );
    void set_sys_pipe_out( int sysPipeOut );

    void append_input_pipe( int imputPipe );
    void append_output_pipe( int outputPipe );

    pid_t get_pid();
    pid_t get_ppid(); 

    void run();

  private:
    pid_t pid;
    string name;
    string description;
    vector <int> inputPipes;
    vector <int> outputPipes;
    int sysPipeOut, sysPipeIn;
    bool isStart, isFinal;
};

#endif
