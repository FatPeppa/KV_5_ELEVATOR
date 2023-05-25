#include "cl_input.h"
#include <iostream>
#include <string>

using namespace std;

cl_input :: cl_input(string name, cl_base* parent) : cl_base(parent, name) {};

void cl_input::signal(string& command) {
	getline(cin, command);

	if (command == "Turn off the system") {
		return;
	}
	else if (command == "End of settings") {
		return;
	}
	else if (command == "System status") {
		return;
	}
	else if (command == "Elevator condition") {
		return;
	}
	else {
		string str_first = command.substr(0, command.find(' '));
		string str_second = command.substr(command.find(' ') + 1, command.length());
		bool flag = true;
		
		for (int i = 0; i < str_first.length(); i++)
			if (!isdigit(str_first[i])) { flag = false; break; }
		for (int i = 0; i < str_second.length(); i++)
			if (!isdigit(str_second[i])) { flag = false; break; }
		if (!flag) command = "";
		else if (str_first == "Passenger") {
			if (str_second.substr(0, str_second.find(' ')) == "condition") {
				command = "FIO " +
					str_second.substr(str_second.find(' ') + 1, str_second.length());
			}
			else return;
		}
		else if (str_first == "Condition") {
		
		}
	}
}

void cl_input::signal_start(string& command) {

}