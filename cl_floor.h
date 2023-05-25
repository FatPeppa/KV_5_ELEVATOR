#ifndef __CL_FLOOR__H
#define __CL_FLOOR__H
#include <iostream>
#include <string>
#include "cl_passenger.h"
#include "cl_application.h"
#include "cl_base.h"

using namespace std;

class cl_floor : public cl_base {
	int floor_num;
	bool button_up = false;
	bool button_down = false;

public:
	cl_floor(string name, cl_base * parent);
	void set_floor_num(int floor_num);
	void signal(string&);
	void handler(string);
};

#endif
