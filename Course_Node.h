#ifndef COURSE_NODE
#define COURSE_NODE

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Course.h"
#include "PrereqLL.h"

using namespace std;

class Course_Node {
public:
	Course_Node();
	Course* course;
	PrereqLL* prereqs;
};

#endif
