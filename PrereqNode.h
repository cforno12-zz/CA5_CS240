#ifndef PREREQ_NODE_H
#define PREREQ_NODE_H
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "Course.h"
class PrereqNode{
public:
	Course * data;
	PrereqNode* next;
};
#endif
