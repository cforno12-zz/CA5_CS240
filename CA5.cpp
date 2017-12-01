#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include <iterator>
#include "Req_graph.h"
using namespace std;

int main(int argc, char ** argv){
	Req_graph* graph = new Req_graph();
	fstream require, offering;
	string line;
	int total = 0;

	require.open(argv[1]); // requirements file
	if(!require){
		cout << "Unable to read the first file" << endl;
		//exit(0);
	}
	while(getline(require, line)){
		//store line into vector lineVect
		stringstream ss(line);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> lineVect(begin, end);

		if(lineVect[0] == "TOTAL"){
			total = atoi(lineVect[1].c_str());
		} else if (lineVect[0] == "CREDIT"){
				//Credit * cred = new Credit(lineVect[1], atoi(lineVect[2].c_str()));
				//we need to create credit class with name & num_credits
				//we also need to have some sort of array or vector of num_credits
				//so that later on we can keep track of how many weve taken
				//probably just subtract from num_credits each time they take
				//and make sure all the num_credits are 0 after finishing
		} else if(lineVect[0] == "COURSE"){
      string course = lineVect[1];
			//retrieve type of class
			char type = *lineVect[2].c_str();
      cout << type << endl;
			Course* curr_course = new Course(course, type);
			Course_Node* curr_course_node = new Course_Node(curr_course);
			graph->add_course(curr_course_node);

		} else if(lineVect[0] == "CHOOSE"){

		} else {
			cout << "Bad file." << endl;
			//exit(0);
		}
	}
	//now to load the prereqs
	require.clear();
	require.seekg(0, ios::beg);
	//these two lines reset the pointer of the file to the beginning
	for (unsigned int i = 0; i < graph->graph.size(); i++) {
		std::cout << graph->graph[i]->course->course_name << endl;
	}

	Course_Node * curr;
	Course_Node * prereq;
	while(getline(require, line)){
		stringstream ss(line);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> lineVect(begin, end);
		if(lineVect[0] == "COURSE"){
			for(unsigned int i = 0; i<graph->graph.size(); i++){
				if(graph->graph[i]->course->course_name == lineVect[1]){ // finding course we're on
					curr = graph->graph[i];
				}
				for(unsigned int j=3; j<lineVect.size(); j++){
					if(graph->graph[i]->course->course_name == lineVect[j]){ // to find the prereq, not sure how to know how many on the line
						prereq = graph->graph[i];
					}
				}
			}
			PrereqNode* prereq_node = new PrereqNode(prereq);
			curr->prereqs->add_prereq(prereq_node);
		}
	}
	int counter = 0;
	for(unsigned int i = 0; i < graph->graph.size(); i++){
		cout << "THIS IS THE " << counter << " COURSE." << endl;
		cout << "Actual Course: " << graph->graph[i]->course->course_name << " // It's prereqs: ";
		graph->graph[i]->prereqs->print_prereqs();
	}
	return 0;
}
