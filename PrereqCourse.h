#ifndef PREREQ_COURSE
#define PREREQ_COURSE

#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "PrereqNode.h"

using namespace std;

class PrereqCourse {
 public:
    PrereqCourse();
    string course_name;
    char type;
};

#endif
