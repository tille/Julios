#include "state.h"

#include <sys/types.h>
#include <signal.h>

using namespace std;

state::state() { 
  //cout << this->get_name() << "\n";
  //this->inputPipes = {};
  //this->outputPipes = {};
  //this->run();
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
  
void state::append_input_pipe( string from, int inputPipe ){

  map<string, int>::iterator it = this->inputPipes.find(from);
  
  if(it == this->inputPipes.end())
    this->inputPipes.insert( std::pair <string, int>( from, inputPipe ) );
}

void state::append_output_pipe( string to, int outputPipe ){

  map<string, int>::iterator it = this->outputPipes.find(to);
 
  if(it == this->outputPipes.end())
    this->outputPipes.insert( std::pair <string, int>( to, outputPipe ) );
}
  
pid_t state::get_pid(){
  return getpid();
}

pid_t state::get_ppid(){
  return getppid();
}

void state::run(){

  cout << this->get_name() << "\n";

  this->pid = fork();
 
  if (this->pid == -1){cout << "Did not work";}

  if (this->pid == 0){//Child Process
    cout << "meee....";
    int input_num = 0;
    char *data [MAX_BUFF];
    fd_set input;
    FD_ZERO(&input);
 
    for ( map<string, int>::iterator iter = this->inputPipes.begin(); iter != this->inputPipes.end(); iter ++){
      FD_SET(iter->second, &input);
    }

    map<string, int>::iterator it = this->inputPipes.begin();
    map<string, int>::iterator end = this->inputPipes.end();

    int max_value = it->second;
    string str = it->first;
    for( ; it != end; ++it) {
      if(it->second > max_value) {
        max_value = it->second;
        str = it->first;
      }
    }

    int max_fd = max_value + 1;

    while ( true ){
      input_num = select(max_fd, &input, NULL, NULL, NULL);
    
      for ( map<string, int>::iterator iter = this->inputPipes.begin(); iter != this->inputPipes.end(); iter ++){
        if ( FD_ISSET( iter->second, &input))
	  int c = read( iter->second, data, MAX_BUFF);
      }
    }
  }

  if (this->pid == 1){
    cout << "Well Fuck";
  }//Father Process, do nothing
}
