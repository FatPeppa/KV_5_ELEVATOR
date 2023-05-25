#include <stdlib.h>
#include <stdio.h>
#include "cl_application.h"
#include <iostream>
using namespace std;

int main()
{
	cl_application  ob_cl_application(nullptr);
	ob_cl_application.bild_tree_objects();       // конструирование системы, построение дерева объектов
	return ob_cl_application.exec_app();         // запуск системы
}