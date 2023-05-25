#ifndef __CL_LIFT__H
#define __CL_LIFT__H
#include <iostream>
#include <string>
#include <vector>
#include "cl_passenger.h"
#include "cl_controller.h"
#include "cl_base.h"

using namespace std;

class cl_lift : public cl_base {
	int m; //Вместимость лифта
	vector<bool> buttons;
public:
	cl_lift(string name, cl_base * parent); //через конструктор cl_base
	void set_capacity(int m);
	void signal(string&);
	void handler(string);
};


#endif
