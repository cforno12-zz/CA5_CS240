#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "PrereqNode.h"

PrereqNode::PrereqNode(){
    data = nullptr;
    next = nullptr;
}

PrereqNode::PrereqNode(Course_Node* c){
    data = c;
    next = nullptr;
}
