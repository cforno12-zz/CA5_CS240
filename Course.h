#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Course {
public:
    Course(string c, char t);
    string course_name;
    char type;
};

#endif
