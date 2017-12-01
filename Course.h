#ifndef COURSE_H
#define COURSE_H

#include <iostream>
#include <stdlib.h>
#include <string.h>

using namespace std;

class Course {
public:
    Course(string c, char t, char o, string cred);
	Course(string c, char t);
    string course_name;
	char offer;
    char type;
    string cred;
};

#endif
