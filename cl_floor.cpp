#include "cl_floor.h"
#include <iostream>
#include <string>

using namespace std;

cl_floor::cl_floor(string name, cl_base* parent) : cl_base(parent, name) {};

void cl_floor::set_floor_num(int floor_num) {
	this->floor_num = floor_num;
}

void cl_floor::handler(string command) {
	string str_first = command.substr(0, command.find(' '));
	string str_second = command.substr(command.find(' ') + 1, command.length());
	bool flag = true;
	cl_passenger* passenger;

	if (str_first == "Passenger") {
		if (str_second.substr(0, str_second.find(' ')) == "condition") {
			return;
		}
		else {
			bool flag = true;
			for (int i = 0; i < str_second.substr(0, str_second.find(' ')).length(); i++)
				if (!isdigit(str_second.substr(0, str_second.find(' '))[i])) { flag = false; break; }
			if (flag) {
				int fl_num = stoi(str_second.substr(0, str_second.find(' ')));
				string str_third = str_second.substr(str_second.find(' ') + 1, str_second.length());
				int fl_to_num = stoi(str_third.substr(0, str_third.find(' ')));
				string P_name = str_third.substr(str_third.find_first_of(' ') + 1, str_third.length());

				if (fl_num == floor_num) {
					passenger = new cl_passenger(P_name, this);
					passenger->set_floor_to(fl_to_num);
					passenger->set_floor_from(fl_num);
					passenger->set_button();
				}
			}
		}
	}
	else if (str_first == "Condition") {
		string fl_num_str = command.substr(command.find_last_of(' '), command.length());
		int fl_num = stoi(fl_num_str);
		if (fl_num == floor_num) {
		
		}
	}
}