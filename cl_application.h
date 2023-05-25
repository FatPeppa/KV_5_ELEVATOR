#ifndef Cl_application_H
#define Cl_application_H

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "cl_base.h"
#include "cl_input.h"
#include "cl_controller.h"
#include "cl_floor.h"
#include "cl_passenger.h"
#include "cl_output.h"
using namespace std;

class cl_application : public cl_base {
	//KV5 data
	int n = NULL; //количество этажей
	int m = NULL; 
public:
	cl_application(cl_base* parent);
	void bild_tree_objects();
	int exec_app();

	void signal_meth(string& warning);
	void handler_meth(string warning);

	//KV5 operations

	void set_floor_num(int n);
};


#endif