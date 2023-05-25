#include "cl_lift.h"
#include <iostream>
#include <string>

using namespace std;

cl_lift::cl_lift(string name, cl_base* parent) : cl_base(parent, name) {};

void cl_lift::handler(string warning) {
	if (warning.length() > 0) {
		string str_n = warning.substr(0, warning.find(' '));
		string str_m = warning.substr(warning.find(' ') + 1, warning.length());
		bool flag = true;

		for (int i = 0; i < str_n.length(); i++)
			if (!isdigit(str_n[i])) { flag = false; break; }
		for (int i = 0; i < str_m.length(); i++)
			if (!isdigit(str_m[i])) { flag = false; break; }
		if (flag) {
			this->m = stoi(str_n);
		}
		else {

		}
	}
}