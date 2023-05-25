#ifndef __CL_OUTPUT__H
#define __CL_OUTPUT__H
#include <iostream>
#include <string>
#include "cl_application.h"
#include "cl_base.h"

using namespace std;

class cl_output : public cl_base {
public:
	cl_output(string name, cl_base * parent);
	void signal(string&);
	void handler(string);

};

#endif
