#include "state.h"

state::state() { }

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
