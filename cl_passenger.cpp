#include "cl_passenger.h"
#include <iostream>
#include <string>

using namespace std;

cl_passenger :: cl_passenger(string name, cl_base* parent) : cl_base(parent, name) {};

void cl_passenger :: set_tact(int num) {
	this->num_tact = num;
}
void cl_passenger :: set_button() {
	if (num_floor_to > num_floor_from) this->pressed_button_up = true;
	else this->pressed_button_down = true;
}
void cl_passenger :: set_floor_from(int num) {
	this->num_floor_from = num;
}
void cl_passenger :: set_floor_to(int num) {
	this->num_floor_to = num;
}