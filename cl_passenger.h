#ifndef __CL_PASSENGER__H
#define __CL_PASSENGER__H
#include <iostream>
#include <string>
#include <vector>
#include "cl_lift.h"
#include "cl_floor.h"
#include "cl_base.h"

using namespace std;

class cl_passenger : public cl_base {
	int num_floor_from;
	int num_floor_to;
	bool pressed_button_up;
	bool pressed_button_down;
	int num_tact;

	cl_lift* in_lift;
	cl_floor* on_floor;
public:
	cl_passenger(string name, cl_base * parent);
	void set_tact(int num);
	void set_button();
	void set_floor_from(int num);
	void set_floor_to(int num);

	void signal(string&);
	void handler(string);
};

#endif
