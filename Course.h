#ifndef Course_h
#define Course_h

#include <stdio.h>
#include <string>

using namespace std;

class Course {
	
	
public:
	Course();
	
	string course_name;
	int num_credits;
	string when_offered;
	string course_type;
	string gen_ed_requirements;
	//char [] gen_ed_requirements = {'Z', 'Z', 'Z'}; // To seperate requirement types, Z is filler
	string * prerequisites;
	long total_prerequisites;
	bool has_taken_class;
	
	friend ostream &operator<<(ostream &out, const Course &in);

};


#endif /* Course_h */

