#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Course.h"

using namespace std;

Course::Course(string c, char t, char o, string cred){
    course_name = c;
    type = t;
    offer = o;
    cred = cred;
}

Course::Course(string c, char t){
    course_name = c;
    type = t;
}
