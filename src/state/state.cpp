#include "state.h"

state::state() { 
  this->inputPipes = {};
  this->outputPipes = {};
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

void set_is_final( bool isFinal ){
  this->isFinal = isFinal;
}

bool get_is_final(){
  return this->isFinal;
}
  
void set_is_start( bool isStart ){
  this->isStart = isStart;
}

bool get_is_start(){
  return this->isStart;
}
   
void set_sys_pipe_in( int sysPipeIn ){
  this->sysPipeIn = sysPipeIn;
}

void set_sys_pipe_out( int sysPipeOut ){
  this->sysPipeOut = sysPipeOut;
}
  
void append_input_pipe( int imputPipe ){
  this->inputPipes.push_back(inputPipe);
}

void append_output_pipe( int outputPipe ){
  this->outputPipes.push_back(outputPipe)
}
  
void get_pid(){
  return getpid();
}

void get_ppid(){
  return getppid();
}
