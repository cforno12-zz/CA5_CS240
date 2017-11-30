#ifndef COURSE_NODE
#define COURSE_NODE

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Course.h"
#include "PrereqLL.h"
class PrereqLL;

using namespace std;

class Course_Node {
public:
	Course* course;
	PrereqLL* prereqs;
	Course_Node();
	Course_Node(Course* c);
};

#endif
