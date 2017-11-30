#ifndef PREREQ_NODE_H
#define PREREQ_NODE_H

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Course_Node.h"
class Course_Node;

class PrereqNode{
 public:
	Course_Node* data;
    PrereqNode* next;
    PrereqNode();
    PrereqNode(Course_Node* c);
};

#endif
