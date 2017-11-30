#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <sstream>
#include <vector>
#include "Req_graph.h"
using namespace std;

void total();

int main(int argc, char ** argv){
	Req_graph* graph = new Req_graph();
	fstream require, offering;
	string line;
	int total = 0;

	require.open(argv[1]); // requirements file
	if(!require){
		cout << "Unable to read the first file" << endl;
		exit(0);
	}

	while(!require.eof()){
		getline(require, line);

		//store line into vector lineVect
		stringstream ss(line);
		istream_iterator<string> begin(ss);
		istream_iterator<string> end;
		vector<string> lineVect(begin, end);

		if(lineVect[0] == "TOTAL"){
			total = atoi(lineVect[1].c_str());
		} else if (lineVect[0] == "CREDIT"){

		} else if(lineVect[0] == "COURSE"){
			//retrieve course
			string course = lineVect[1];

			//retrieve type of class
			char type = *lineVect[2].c_str();
			Course* curr_course = new Course(course, type, 'A');
			Course_Node* curr_course_node = new Course_Node(curr_course);
			//check if course has prereqs
			for(int i = 3; i < lineVect.size(); i++){
					PrereqNode* prereq_node = new PrereqNode(curr_course_node);
					curr_course_node->prereqs->add_prereq(prereq_node);
			}

		} else if(lineVect[0] == "CHOOSE"){

		} else {
			cout << "Bad file." << endl;
			exit(0);
		}

	}

	exit (0);
}


void total(){

}
