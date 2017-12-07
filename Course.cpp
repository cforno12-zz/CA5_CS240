#include "Course.h"
#include <string>

#include <istream>
#include <sstream>

using namespace std;

Course::Course(){
	has_taken_class = false;
}


std::ostream &operator<<(std::ostream &out, const Course &in){
	
	out << in.course_name << " " << in.num_credits << " " << in.when_offered << " " << in.gen_ed_requirements << " " << in.course_type << " ";
	for(int i = 0; i < in.total_prerequisites; i++)
		out << in.prerequisites[i] << " ";
	out << endl;
	
	return out;
		
}

