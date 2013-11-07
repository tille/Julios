#include "state.h"

#include <sys/types.h>
#include <signal.h>

state::state() { 
  this->inputPipes = {};
  this->outputPipes = {};
  //run();
}

state::~state() { }

void state::set_name( string name_p ){
  this->name = name_p;
}

string state::get_name(){
  return name;
}

void state::set_description( string description_p ){
  this->description = description_p;
}

string state::get_description(){
  return description;
}

void state::set_is_final( bool isFinal ){
  this->isFinal = isFinal;
}

bool state::state::get_is_final(){
  return this->isFinal;
}
  
void state::set_is_start( bool isStart ){
  this->isStart = isStart;
}

bool state::get_is_start(){
  return this->isStart;
}
   
void state::set_sys_pipe_in( int sysPipeIn ){
  this->sysPipeIn = sysPipeIn;
}

void state::set_sys_pipe_out( int sysPipeOut ){
  this->sysPipeOut = sysPipeOut;
}
  
void state::append_input_pipe( int inputPipe ){
  this->inputPipes.insert(this->inputPipes.end(), inputPipe);
}

void state::append_output_pipe( int outputPipe ){
  this->outputPipes.insert(this->outputPipes.end() , outputPipe);
}
  
pid_t state::get_pid(){
  return getpid();
}

pid_t state::get_ppid(){
  return getppid();
}

void state::run(){
  this->pid = fork();
 
  if (this->pid == -1){}

  if (this->pid == 0){//Child Process
    int input_num = 0;
    char *data [MAX_BUFF];
    fd_set input;
    FD_ZERO(&input);
 
    for ( int index = 0; index < this->inputPipes.size(); index ++){
      FD_SET(this->inputPipes[index], &input);
    }

    int max_fd = (*std::max_element(this->inputPipes.begin(), this->inputPipes.end())) + 1;

    while ( true ){
        input_num = select(max_fd, &input, NULL, NULL, NULL);

        for ( int index = 0; index < this->inputPipes.size(); index ++){
          if (FD_ISSET(this->inputPipes[ index ], &input))
            int c = read(this->inputPipes[ index ], data, MAX_BUFF);
        }

	//Parse data

	//Change data to remove char of state

	//Handle error if char is invalid

	//Parse data to pass on to the next state
    }
  }

  if (this->pid == 1){}//Father Process, do nothing
}
