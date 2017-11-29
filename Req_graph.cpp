#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <vector>

#include "Req_graph.h"

Req_graph::Req_graph(){
    graph.clear();
}

void Req_graph::add_course(Course_Node* cn) {
    graph.push_back(cn);
}
