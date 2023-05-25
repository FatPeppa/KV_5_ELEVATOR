#include <stdlib.h>
#include <stdio.h>
#include "cl_application.h"
#include "cl_base.h"
#include <iostream>
#include <typeinfo>
#include <string>
#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HENDLER_D( hendler_f ) ( TYPE_HANDLER ) ( & hendler_f )

using namespace std;

cl_application::cl_application(cl_base* parent) : cl_base(parent, "root") {}

void cl_application::bild_tree_objects() {
	cl_floor * new_floor;
	//sdcsdcsc
	//sdiwjeofjweofij
	cl_floor* wefhwoefhoeho;


	cl_input * input_obj = new cl_input("INPUT_OBJECT", this);
	cl_controller * controller_obj = new cl_controller("CONTROLLER_OBJECT", this);
	cl_output * output_obj = new cl_output("OUTPUT_OBJECT", this);

	cl_lift * b_lift = new cl_lift("LIFT_OBJECT", controller_obj);
	set_all_readiness(1, false);

	input_obj->set_connection(SIGNAL_D(cl_input::signal),
		this, HENDLER_D(cl_application::handler_meth));
	input_obj->set_connection(SIGNAL_D(cl_input::signal),
		b_lift, HENDLER_D(cl_lift::handler));
	string command_str;

	while (true) {
		command_str = "";
		//getline(cin, command_str);

		input_obj->emit_signal(SIGNAL_D(cl_input::signal_start), command_str);

		if (command_str == "End of settings") break;
		if (this->n != NULL) {
			for (int i = 0; i < this->n; i++)
			{
				new_floor = new cl_floor("FLOOR " + (i + 1), this);
				new_floor->set_floor_num(i + 1);
				new_floor->set_readiness(1);

				this->set_connection(SIGNAL_D(cl_application::signal_meth),
					new_floor, HENDLER_D(cl_floor::handler));
				input_obj->set_connection(SIGNAL_D(cl_input::signal),
					new_floor, HENDLER_D(cl_floor::handler));
				new_floor->set_connection(SIGNAL_D(cl_floor::signal),
					output_obj, HENDLER_D(cl_output::handler));
				new_floor->set_connection(SIGNAL_D(cl_floor::signal),
					controller_obj, HENDLER_D(cl_controller::handler));
			}
		}
	}

	set_connection(SIGNAL_D(cl_application::signal_meth),
		input_obj, HENDLER_D(cl_input::handler));
	set_connection(SIGNAL_D(cl_application::signal_meth),
		controller_obj, HENDLER_D(cl_controller::handler));
	set_connection(SIGNAL_D(cl_application::signal_meth),
		output_obj, HENDLER_D(cl_output::handler));
	set_connection(SIGNAL_D(cl_application::signal_meth),
		b_lift, HENDLER_D(cl_lift::handler));
	
	//input
	input_obj->set_connection(SIGNAL_D(cl_input::signal),
		output_obj, HENDLER_D(cl_output::handler));
	input_obj->set_connection(SIGNAL_D(cl_input::signal),
		controller_obj, HENDLER_D(cl_controller::handler));

	//controller
	controller_obj->set_connection(SIGNAL_D(cl_controller::signal),
		output_obj, HENDLER_D(cl_output::handler));
	
	
	cout << "Ready to work";
	/*cl_input * input_obj;
	cl_controller * controller_obj;
	vector <cl_floor*> floor_objs;
	cl_output * output_obj;*/


	/*string parent_name, child_name, root_name;
	int class_affiliation = 0;
	cl_base* child = this;

	cin >> root_name;
	this->change_objName(root_name);

	while (true) {
		cin >> parent_name;
		if (parent_name == "endtree") break;
		cin >> child_name >> class_affiliation;

		if (get_obj_byCoord(parent_name) == nullptr) {
			cout << "Object tree" << endl;
			this->output_branch("");
			cout << endl << "The head object " << parent_name << " is not found";
			exit(1);
		}

		if (get_obj_byCoord(parent_name)->get_objName() == root_name) {
			if (get_obj_byCoord(parent_name)->get_child(child_name) == nullptr && child_name != root_name) {
				switch (class_affiliation) {
				case 2:
					child = new cl_2(this, child_name);
					child->class_number = 2;
					break;
				case 3:
					child = new cl_3(this, child_name);
					child->class_number = 3;
					break;
				case 4:
					child = new cl_4(this, child_name);
					child->class_number = 4;
					break;
				case 5:
					child = new cl_5(this, child_name);
					child->class_number = 5;
					break;
				case 6:
					child = new cl_6(this, child_name);
					child->class_number = 6;
					break;
				default:
					break;
				}
			}
			else cout << parent_name << "     Dubbing the names of subordinate objects" << endl;
		}
		else {
			if ((this->get_obj_byCoord(parent_name))->get_child(child_name) == nullptr) {
				switch (class_affiliation) {
				case 2:
					child = new cl_2(this->get_obj_byCoord(parent_name), child_name);
					child->class_number = 2;
					break;
				case 3:
					child = new cl_3(this->get_obj_byCoord(parent_name), child_name);
					child->class_number = 3;
					break;
				case 4:
					child = new cl_4(this->get_obj_byCoord(parent_name), child_name);
					child->class_number = 4;
					break;
				case 5:
					child = new cl_5(this->get_obj_byCoord(parent_name), child_name);
					child->class_number = 5;
					break;
				case 6:
					child = new cl_6(this->get_obj_byCoord(parent_name), child_name);
					child->class_number = 6;
					break;
				default:
					break;
				}
			}
			else cout << parent_name << "     Dubbing the names of subordinate objects" << endl;
		}
	}

	vector <TYPE_SIGNAL> signals = { SIGNAL_D(cl_application::signal_meth), SIGNAL_D(cl_2::signal_meth),
						SIGNAL_D(cl_3::signal_meth), SIGNAL_D(cl_4::signal_meth), SIGNAL_D(cl_5::signal_meth),
						SIGNAL_D(cl_6::signal_meth) };
	vector <TYPE_HANDLER> handlers = { HENDLER_D(cl_application::handler_meth), HENDLER_D(cl_2::handler_meth),
						HENDLER_D(cl_3::handler_meth), HENDLER_D(cl_4::handler_meth), HENDLER_D(cl_5::handler_meth),
						HENDLER_D(cl_6::handler_meth)};
	while (true) {
		cin >> parent_name;
		if (parent_name == "end_of_connections") break;
		cin >> child_name;

		cl_base* from_object = this->get_obj_byCoord(parent_name);
		cl_base* to_object = this->get_obj_byCoord(child_name);

		if (from_object)
			if (to_object)
				from_object->set_connection(signals[from_object->class_number - 1],
											to_object, handlers[to_object->class_number - 1]);
			else cout << "Handler object " << child_name << " not found";
		else cout << endl << "Object " << parent_name << " not found";
	}*/
}



int cl_application::exec_app() {
	/*cout << "Object tree" << endl;
	this->output_branch("");

	set_all_readiness(1, true);
	string command_name;
	cin >> command_name;

	vector <TYPE_SIGNAL> signals = { SIGNAL_D(cl_application::signal_meth), SIGNAL_D(cl_2::signal_meth),
						SIGNAL_D(cl_3::signal_meth), SIGNAL_D(cl_4::signal_meth), SIGNAL_D(cl_5::signal_meth),
						SIGNAL_D(cl_6::signal_meth) };
	vector <TYPE_HANDLER> handlers = { HENDLER_D(cl_application::handler_meth), HENDLER_D(cl_2::handler_meth),
						HENDLER_D(cl_3::handler_meth), HENDLER_D(cl_4::handler_meth), HENDLER_D(cl_5::handler_meth),
						HENDLER_D(cl_6::handler_meth) };

	while (command_name != "END") {
		if (command_name == "EMIT") {
			string obj_coord, text;
			cin >> obj_coord;
			getline(cin, text, '\n');
			text.erase(text.begin());

			cl_base* obj = this->get_obj_byCoord(obj_coord);
			if (obj)
				obj->emit_signal(signals[obj->class_number - 1], text);
			else cout << endl << "Object " << obj_coord << "not found";
		}
		else if (command_name == "SET_CONNECT") {
			string from_obj_coord, to_obj_coord;
			cin >> from_obj_coord >> to_obj_coord;

			cl_base* from_object = get_obj_byCoord(from_obj_coord);
			cl_base* to_object = get_obj_byCoord(to_obj_coord);
			if (from_object)
				if (to_object)
					from_object->set_connection(signals[from_object->class_number - 1],
						to_object, handlers[to_object->class_number - 1]);
				else cout << "Handler object " << to_obj_coord << " not found";
			else cout << endl << "Object " << from_obj_coord << " not found";
		}
		else if (command_name == "DELETE_CONNECT") {
			string from_obj_coord, to_obj_coord;
			cin >> from_obj_coord >> to_obj_coord;

			cl_base* from_object = get_obj_byCoord(from_obj_coord);
			cl_base* to_object = get_obj_byCoord(to_obj_coord);
			if (from_object)
				if (to_object)
					from_object->delete_connection(signals[from_object->class_number - 1],
						to_object, handlers[to_object->class_number - 1]);
				else cout << "Handler object " << to_obj_coord << " not found";
			else cout << endl << "Object " << from_obj_coord << " not found";
		}
		else if (command_name == "SET_CONDITION") {
			string obj_coord;
			int condition;
			cin >> obj_coord >> condition;

			cl_base* obj = this->get_obj_byCoord(obj_coord);
			if (obj)
				obj->set_readiness(condition);
			else cout << endl << "Object " << obj_coord << " not found";
		}

		cin >> command_name;
	}

	return 0;*/
	string command;

	while (true) {
		command = "";
		get_obj_byCoord("/INPUT_OBJECT")->emit_signal(SIGNAL_D(cl_input::signal_start),
			command);
		if (command == "Turn off the system") break;
		
	}
	









	return 0;
}

void cl_application::signal_meth(string& warning) {
	cout << endl << "Signal from " << this->get_absPath();
	warning += " (class: 1)";
}
void cl_application::handler_meth(string warning) {
	if (warning.length() > 0) {
		string str_n = warning.substr(0, warning.find(' '));
		string str_m = warning.substr(warning.find(' ') + 1, warning.length());
		bool flag = true;

		for (int i = 0; i < str_n.length(); i++)
			if (!isdigit(str_n[i])) { flag = false; break; }
		for (int i = 0; i < str_m.length(); i++)
			if (!isdigit(str_m[i])) { flag = false; break; }
		if (flag) {
			this->n = stoi(str_n);
		}

	}
	else if (warning == "End of settings" ||
		warning == "Turn off the system") return;
}

void cl_application::set_floor_num(int n) {
	this->n = n;
}