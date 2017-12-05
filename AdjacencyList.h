#ifndef AdjacencyList_h
#define AdjacencyList_h

#include <unordered_map>
#include <iostream>
#include <string>
#include <vector>
#include "Course.h"

using namespace std;

class AdjacencyList;


struct Choose {
	
	Choose(){
		total_options = 0;
	}
	
	string * all_options;
	
	int total_options;
	
	~Choose(){
		
	}
	
};

struct Credit {
	Credit(){
		credit_type = '0';
		num_credits_to_take = 0;
		num_credits_taken = 0;
	}

	Credit(char type, int toTake){
		credit_type = type;
		num_credits_to_take = toTake;
		num_credits_taken = 0;
	}

	char credit_type;
	int num_credits_to_take;
	int num_credits_taken;

	~Credit(){
		
	}
};

struct Semester {
	
	Semester(){
		
	}
	
	string semester_name;
	
	string courses[4];
	
	void print(){
		cout << semester_name << " ";
		for(int j = 0; j < 4; j++)
			cout << courses[j] << " ";
	};
	
	~Semester(){
		
	}
};


struct AdjNode {
	
	Course course;
	
	struct AdjNode * next;
	
	void print(){
		AdjNode * temp = next;
		
		cout <<  course.course_name;
		while(temp != NULL){
			cout << "  :  " << temp -> course;
			temp = temp -> next;
		}
		cout << endl;
	}
	
	AdjNode(){
		next = NULL;
	}
	
	~AdjNode(){
		AdjNode * temp = next;
		AdjNode * to_delete;
		while(temp != NULL){
			to_delete = temp;
			temp = temp -> next;
			delete to_delete;
		}
	}
	
};




class AdjacencyList {

public:
	AdjacencyList();
	
	void test_input(string offerings, string requirements, string schedule);
	
//private:
	int total_available_courses;
	int total_required_classes;
	int total_choose_course_indexes;
	
	int total_required_credits;
	int total_c_credits_required;
	int total_h_credits_required;
	int total_f_credits_required;
	
	int total_credits_taken;
	/*int total_c_credits_taken;
	int total_h_credits_taken;
	int total_f_credits_taken;*/

	
	vector<Credit*> credits;	
	AdjNode * nodes;
	Course * all_courses;
	Choose * choose_courses;
	
	
	Semester semesters[8];

	//HASH MAP ADDITION
	unordered_map<string, int> hashMap;
	
	string build_list(string offerings, string requirements, string schedule);
	string fill_list(string offerings, string requirements, string schedule);
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
	

	
	int get_course_index_for_name(string name);
	
	AdjNode * get_node_for_name(string course_name);
};


#endif /* AdjacencyList_h */

