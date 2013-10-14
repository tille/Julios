#include "state.h"

state::state() { 
  this->inputPipes = {};
  this->outputPipes = {};
  run();
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
  this->inputPipes.push_back(inputPipe);
}

void state::append_output_pipe( int outputPipe ){
  this->outputPipes.push_back(outputPipe);
}
  
pid_t state::get_pid(){
  return getpid();
}

pid_t state::get_ppid(){
  return getppid();
}

void state::run(){
  this->pid = fork();
  
  if (pid >= 0){
     if(pid == 0){
	cout << get_pid();
     }
  }
}
