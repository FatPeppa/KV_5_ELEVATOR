#ifndef __CL_CONTROLLER__H
#define __CL_CONTROLLER__H
#include <iostream>
#include <string>
#include "cl_passenger.h"
#include "cl_lift.h"
#include "cl_floor.h"
#include "cl_application.h"
#include "cl_base.h"

using namespace std;

class cl_controller : public cl_base {
public:
	cl_controller(string name, cl_base * parent);
	void signal(string&);
	void handler(string);
};

#endif
