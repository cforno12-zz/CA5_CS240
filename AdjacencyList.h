#ifndef AdjacencyList_h
#define AdjacencyList_h

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include "Course.h"

using namespace std;

class AdjacencyList;


class Choose {
	public:			
		string * all_options;
		int total_options;
		Choose();
		~Choose();
};

class Credit {
	public:
		char credit_type;
		int num_credits_to_take;
		int num_credits_taken;
		Credit();
		Credit(char type, int toTake);
		~Credit();
};

class Semester {
	public:
		string semester_name;
		string courses[4];
		Semester();
		void print();
		~Semester();
};


class AdjNode {
	public:
		Course course;	
		AdjNode * next;
		void print();
		AdjNode();	
		~AdjNode();	
};

class AdjacencyList {
	public:
		AdjacencyList();

		void test_input(string offerings, string requirements, string schedule);

		int available_courses;
		int required_classes;
		int choose_course_indexes;

		int required_credits;

		int credits_taken;

		vector<Credit*> credits;
		AdjNode * nodes;
		Course * all_courses;
		Choose * choose_courses;


		Semester semesters[8];

		//HASH MAP 
		unordered_map<string, int> hashMap;
	
		string build_graph(string offerings, string requirements, string schedule);
		string fill_graph(string offerings, string requirements, string schedule);
		string is_schedule_valid();
	
		void sort_schedule();
		void mark_class_taken(string course_name);
	
		vector<string> split(string input);
	
		string modify_semester_name_for_sorting(string name);
	
		bool is_required_class(string course_name);
		bool is_course_name_valid(string input);
		bool can_take_class(string course_name);
		bool is_cs_course_offered_and_not_in_reqs(string course_name);
		bool has_taken_class(string course_name);
		bool all_mandatory_and_required_classes_taken();
		bool is_course_available_in_registered_semester(string course_name, char semester);
		bool is_course_in_schedule(string course_name);
	

	
		int getHashIndex(string name);
	
		AdjNode * get_node_for_name(string course_name);
};


#endif 

