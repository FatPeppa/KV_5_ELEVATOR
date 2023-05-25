#ifndef __CL_INPUT__H
#define __CL_INPUT__H
#include <iostream>
#include <string>
#include "cl_application.h"
#include "cl_base.h"

using namespace std;
class cl_input : public cl_base {
public:
	cl_input(string name, cl_base* parent);
	void signal(string&);
	void handler(string);
	void signal_start(string&);
};

#endif
