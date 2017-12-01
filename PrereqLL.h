#ifndef PREREQLL_H
#define PREREQLL_H
#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "PrereqNode.h"
class PrereqNode;

class PrereqLL{
public:
    PrereqNode* head;
    PrereqLL();
    void add_prereq(PrereqNode* pn);
	void print_prereqs();
};
#endif
