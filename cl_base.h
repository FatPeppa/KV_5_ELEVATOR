#ifndef Cl_base_H
#define Cl_base_H
#define SIGNAL_D( signal_f ) ( TYPE_SIGNAL ) ( & signal_f )
#define HENDLER_D( hendler_f ) ( TYPE_HANDLER ) ( & hendler_f )

#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class cl_base {
	int readiness = 0;
	string obj_name;
	cl_base* parent_object;
	vector <cl_base* > children;
	vector <cl_base* > ::iterator iter_child;

public:
	cl_base(cl_base* parent, string obj_name);
	bool change_objName(string name);
	string get_objName();
	cl_base* get_parent();
	void show_tree();
	cl_base* get_child(string obj_name);

	//CHANGED IN KV_2
	cl_base* getObj(string obj_name); //Вызывается для корневого объекта

	//NEW OPERATIONS. KV_2
	void set_readiness(int readiness);
	void output_full_tree(string indent);
	void output_branch(string indent);
	cl_base* getObj_inBranch(string obj_name);

	//Operation for debug
	void set_parent(cl_base* new_parent);

	//NEW OPERATIONS. KV_3
	bool set_new_parent(cl_base* new_parent);
	void delete_object(string o_name);
	cl_base* get_obj_byCoord(string coordinate);
	~cl_base();

	int objects_counter(string o_name);

	//NEW OPERATIONS AND STRUCTURES. KV4
	unsigned int class_number = 1;

	typedef void (cl_base ::* TYPE_SIGNAL) (string&);
	typedef void (cl_base ::* TYPE_HANDLER) (string);

	struct o_sh {
		TYPE_SIGNAL p_signal;// = &cl_base::signal_meth;
		cl_base* p_cl_base;
		TYPE_HANDLER p_handler;// = &cl_base::handler_meth;
	};

	vector < o_sh* > connects;

	void set_connection(TYPE_SIGNAL p_signal,
		cl_base* p_object,
		TYPE_HANDLER p_ob_handler);
	void emit_signal(TYPE_SIGNAL p_signal, string& s_command);
	void delete_connection(TYPE_SIGNAL p_signal,
		cl_base* p_object,
		TYPE_HANDLER p_ob_handler);

	string get_absPath();

	void set_all_readiness(int new_readiness, bool direction); //Метод установки готовности всем объектам. 
	//В качестве параметров передаётся новое состояние для всех объектов в дереве, а также направление рекурсии 
	//(true - подъём наверх без установки состояния, false - спуск вниз от корневого с установкой значения new_readiness полям readiness всех объектов)

	//KV5 operations

	bool getStatus(); //метод получения готовности

};

#endif
