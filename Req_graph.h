#ifndef GRAPH
#define GRAPH

#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>

#include "Course_Node.h"

using namespace std;

class Req_graph {
 public:
    Req_graph();
    vector<Course_Node> graph;
    //other functions to traverse and manipulate the graph will go here.
    void add_course(Course_Node* cn);
};


#endif
