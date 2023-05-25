//#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
//#define HENDLER_D( hendler_f ) ( TYPE_HANDLER ) ( & hendler_f )

//typedef void (cl_base ::* TYPE_SIGNAL) (string&);
//typedef void (cl_base ::* TYPE_HANDLER) (string);

#include <stdlib.h>
#include <stdio.h>
#include "cl_application.h"
#include "cl_base.h"
#include <string>
#include <iostream>
#include <typeinfo>
using namespace std;

cl_base::cl_base(cl_base* parent, string obj_name) {
	change_objName(obj_name);

	this->parent_object = parent;
	//this->readiness = 1;
	if (parent) parent->children.push_back(this);
}

bool cl_base::change_objName(string name) {
	if (children.size() == 0) {
		this->obj_name = name;
		return true;
	}
	iter_child = children.begin();
	while (iter_child != children.end()) {
		if ((*iter_child)->get_objName() == name) return false;
		iter_child++;
	}

	obj_name = name;
	return true;
}

string cl_base::get_objName() {
	return obj_name;
}

cl_base* cl_base::get_parent() {
	return parent_object;
}

void cl_base::show_tree() {
	if (this->children.size() == 0) return;
	cout << endl << this->obj_name;
	iter_child = this->children.begin();
	while (iter_child != this->children.end()) {
		cout << "  " << (*iter_child)->obj_name;
		iter_child++;
	}

	iter_child = this->children.begin();

	while (iter_child != this->children.end()) {
		(*iter_child)->show_tree();
		iter_child++;
	}
}

cl_base* cl_base::get_child(string obj_name) {
	if (children.size() == 0) return nullptr;
	iter_child = children.begin();

	while (iter_child != children.end()) {
		if ((*iter_child)->get_objName() == obj_name) {
			return (*iter_child);
		}
		iter_child++;
	}
	return nullptr;
}

//NEW OPERATIONS. KV_2
void cl_base::set_readiness(int readiness) {
	if (readiness == 0) {
		this->readiness = 0;
		if (this->children.size() != 0) {
			iter_child = this->children.begin();
			while (iter_child != this->children.end()) {
				(*iter_child)->set_readiness(readiness);
				iter_child++;
			}
		}
	}
	else {
		//this->readiness = readiness;
		bool flag = true;
		cl_base* par = this->get_parent();

		if (par == nullptr) { this->readiness = readiness; return; }
		else
			while (par != nullptr) {
				if (par->readiness == 0) flag = false;
				par = par->get_parent();
			}
		if (flag) this->readiness = readiness;
	}
}

int cl_base::objects_counter(string o_name) {
	int counter = 0;

	if (this->children.size() != 0) {
		iter_child = this->children.begin();
		while (iter_child != this->children.end()) {
			if ((*iter_child)->get_objName() == o_name) {
				counter++;
			}

			iter_child++;
		}

		iter_child = this->children.begin();
		while (iter_child != this->children.end()) {
			if ((*iter_child)->children.size() != 0)
				counter += (*iter_child)->objects_counter(o_name);

			iter_child++;
		}
	}

	return counter;
}

cl_base* cl_base::getObj_inBranch(string o_name) {
	if (this->objects_counter(o_name) != 1) {
		return nullptr;
	}
	else {
		cl_base* cl_pointer = nullptr;
		cl_base* check_cl_pointer = nullptr;
		if (this->get_parent() == nullptr && this->get_objName() == o_name) { cl_pointer = this; }

		if (this->children.size() != 0) {
			iter_child = this->children.begin();
			while (iter_child != this->children.end()) {
				if ((*iter_child)->get_objName() == o_name) {
					if (cl_pointer == nullptr)
						cl_pointer = (*iter_child);
					else
						return nullptr;
				}

				iter_child++;
			}

			iter_child = this->children.begin();
			while (iter_child != this->children.end()) {
				if ((*iter_child)->children.size() != 0)
					if ((*iter_child)->getObj_inBranch(o_name) != nullptr) {
						check_cl_pointer = (*iter_child)->getObj_inBranch(o_name);

						if (cl_pointer == nullptr)
							cl_pointer = check_cl_pointer;
						else
							return nullptr;

					}

				iter_child++;
			}
		}

		//if (this->get_objName() == o_name && cl_pointer == nullptr) cl_pointer = this;
		if (check_cl_pointer) return check_cl_pointer;
		return cl_pointer;
	}
}

cl_base* cl_base::getObj(string o_name) {
	cl_base* parent_pointer = this->get_parent();

	if (parent_pointer == nullptr) return this->getObj_inBranch(o_name);
	return this->parent_object->getObj(o_name);
}


//Operation for debug
//void cl_base :: set_parent(cl_base * new_parent) {
//	this->parent_object = new_parent;
//}
//Убрать этот метод 

void cl_base::output_full_tree(string indent) {
	int check_readiness = this->readiness;
	string readiness_warning =
		check_readiness == 0 ?
		" is not ready" : " is ready";

	if (this->get_parent() == nullptr) {
		cout << this->obj_name << readiness_warning;
		indent = "";
	}
	else {
		indent += "    ";
		cout << endl << indent << this->obj_name << readiness_warning;
	}
	if (this->children.size() == 0) return;

	iter_child = this->children.begin();
	while (iter_child != this->children.end()) {
		if ((*iter_child)->children.size() == 0) {
			check_readiness = (*iter_child)->readiness;
			readiness_warning =
				check_readiness == 0 ?
				" is not ready" : " is ready";
			cout << endl << indent + "    " << (*iter_child)->get_objName() << readiness_warning;
		}
		else
			(*iter_child)->output_full_tree(indent);

		iter_child++;
	}
}

void cl_base::output_branch(string indent) {
	if (this->get_parent() == nullptr) {
		cout << this->obj_name;
		indent = "";
	}
	else {
		indent += "    ";
		cout << endl << indent << this->obj_name;
	}
	if (this->children.size() == 0) return;

	iter_child = this->children.begin();
	while (iter_child != this->children.end()) {
		if ((*iter_child)->children.size() == 0)
			cout << endl << indent + "    " << (*iter_child)->get_objName();
		else
			(*iter_child)->output_branch(indent);

		iter_child++;
	}
}

//NEW OPERATIONS. KV_3
bool cl_base::set_new_parent(cl_base* new_parent) {
	if (this->get_parent() == nullptr || new_parent == nullptr) return false;
	if (new_parent->get_parent()) {
		if (new_parent->get_child(this->get_objName())) return false;
		if (this->getObj_inBranch(new_parent->get_objName())) return false;
	}

	cl_base* par = this->get_parent();
	if (par->children.size() > 0) {
		par->iter_child = par->children.begin();
		while (par->iter_child != par->children.end()) {
			if ((*par->iter_child)->get_objName() == this->get_objName()) {
				par->children.erase(par->iter_child);
				break;
			}

			par->iter_child++;
		}
	}

	this->parent_object = new_parent;
	this->parent_object->children.push_back(this);
	return true;
}

cl_base::~cl_base() {
	this->children.clear();
	this->obj_name.clear();
}

void cl_base::delete_object(string o_name) {
	cl_base* deleting_obj = this->get_child(o_name);
	if (deleting_obj) {
		cl_base* par = this;
		par->iter_child = par->children.begin();

		while (par->iter_child != par->children.end()) {
			if ((*par->iter_child)->get_objName() == o_name) {
				par->children.erase(par->iter_child);
				break;
			}

			par->iter_child++;
		}

		while (deleting_obj->children.size() > 0) {
			deleting_obj->delete_object(deleting_obj->children.at(0)->get_objName());
		}

		deleting_obj->children.clear();

		deleting_obj->~cl_base();
	}
}


cl_base* cl_base::get_obj_byCoord(string coordinate) {
	if (coordinate.size() == 0) return nullptr;
	if (coordinate[0] == '/' && coordinate.size() == 1) {
		cl_base* par = this->get_parent();
		if (par) {
			while (par->get_parent()) { par = par->get_parent(); }
			return par;
		}
		else return this;
	}
	else if (coordinate.size() > 2 &&
		coordinate[0] == '/' && coordinate[1] == '/') {

		return this->getObj(coordinate.substr(2, coordinate.size() - 2));
	}
	else if (coordinate.size() == 1 && coordinate[0] == '.') {
		return this;
	}
	else if (coordinate.size() > 1 && coordinate[0] == '.') {
		return this->getObj_inBranch(coordinate.substr(1, coordinate.size() - 1));
	}
	else {
		if (coordinate.size() > 1 && coordinate[0] == '/' && coordinate[1] != '/') {
			//абсолютная координата от корневого объекта
			int i = 1;
			string o_name = "";
			cl_base* head_obj = this->get_obj_byCoord("/");
			if (!head_obj) return nullptr;

			while (i < coordinate.size()) {
				if (coordinate[i] == '/') {

					head_obj = head_obj->get_child(o_name);
					if (!head_obj) return nullptr;
					o_name = "";
					i++;
				}
				else {
					o_name += coordinate[i];
					i++;
				}
			}

			//if (head_obj == this->get_obj_byCoord("/")) return 
			return head_obj->get_child(o_name);
		}
		else {
			//относительная координата от текущего объекта
			int i = 0;
			string o_name = "";
			cl_base* head_obj = this;

			while (i < coordinate.size()) {
				if (coordinate[i] == '/') {
					head_obj = head_obj->get_child(o_name);

					o_name = "";
					i++;
				}
				else {
					o_name += coordinate[i];
					i++;
				}
			}

			cl_base* ll = head_obj->get_child(o_name);
			cl_base* l2 = ll;
			return l2;
		}
	}
}



//NEW OPERATIONS. KV_4
//Метод установки связи
void cl_base::set_connection(TYPE_SIGNAL p_signal,
	cl_base* p_object,
	TYPE_HANDLER p_ob_handler)
{
	o_sh* p_value;
	//--------------------------------------------------------
	// Цикл для исключения повторного установления связи
	for (unsigned int i = 0; i < connects.size(); i++)
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_cl_base == p_object &&
			connects[i]->p_handler == p_ob_handler)

			return;
	}

	p_value = new o_sh();                 // создание объекта структуры для
	// хранения информации о новой связи
	p_value->p_signal = p_signal;
	p_value->p_cl_base = p_object;
	p_value->p_handler = p_ob_handler;

	connects.push_back(p_value);          // добавление новой связи  
}

//Метод удаления связи
void cl_base::delete_connection(TYPE_SIGNAL p_signal,
	cl_base* p_object,
	TYPE_HANDLER p_ob_handler)
{
	unsigned int i;
	for (i = 0; i < connects.size(); i++)
	{
		if (connects[i]->p_signal == p_signal &&
			connects[i]->p_cl_base == p_object &&
			connects[i]->p_handler == p_ob_handler)
		{
			break;
		}
	}
	if (i != connects.size())
		connects.erase(connects.begin() + i);
}

//Метод выдачи сигнала
void cl_base::emit_signal(TYPE_SIGNAL p_signal, string& s_command) {
	if (this->readiness == 0) return;
	TYPE_HANDLER   p_handler;
	cl_base* p_object;
	(this->*p_signal) (s_command);  // вызов метода сигнала

	for (unsigned int i = 0; i < connects.size(); i++) // цикл по всем обработчикам
	{
		if (connects[i]->p_signal == p_signal)      // определение допустимого обработчика
		{
			if (connects[i]->p_cl_base->readiness != 0) {
				p_handler = connects[i]->p_handler;
				p_object = connects[i]->p_cl_base;

				(p_object->*p_handler) (s_command);      // вызов метода обработчика
			}
		}
	}

}

//Метод получения абсолютного пути к текущему объекту
string cl_base::get_absPath() {
	string abs_path;

	cl_base* par = this->get_parent();

	if (par) {
		abs_path = this->get_objName();

		while (par->get_parent()) {
			abs_path.insert(0, par->get_objName() + '/');
			par = par->get_parent();
		}
	}

	abs_path.insert(0, "/");

	return abs_path;
}

void cl_base::set_all_readiness(int new_readiness, bool direction) {
	if (direction) {
		cl_base* par = this->get_parent();

		if (par) {
			while (par->get_parent())
				par = par->get_parent();
		}
		else {
			set_all_readiness(new_readiness, false);
			return;
		}

		direction = false;
		par->set_all_readiness(new_readiness, direction);
	}
	else {
		this->set_readiness(new_readiness);

		if (children.size() > 0) {
			iter_child = children.begin();
			while (iter_child != children.end()) {
				(*iter_child)->set_all_readiness(new_readiness, direction);

				iter_child++;
			}
		}
	}
}