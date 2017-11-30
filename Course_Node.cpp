#include <iostream>
#include <string.h>
#include <stdlib.h>

#include "Course_Node.h"

using namespace std;

Course_Node::Course_Node(){
    course = nullptr;
    prereqs = nullptr;
}

Course_Node::Course_Node(Course* c){
    course = c;
    prereqs = nullptr;
}
