#include "AdjacencyList.h"
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include <stdlib.h>
#include <iterator> 

using namespace std;

Choose::Choose(){
	total_options = 0;
	total_to_pick = 0;
	total_taken = 0;
}

	
Choose::~Choose(){
		
}

Credit::Credit(){
			credit_type = '0';
			num_credits_to_take = 0;
			num_credits_taken = 0;
}

Credit::Credit(char type, int toTake){
			credit_type = type;
			num_credits_to_take = toTake;
			num_credits_taken = 0;
}

Credit::~Credit(){
		
}

Semester::Semester(){
		
}
	
	
void Semester::print(){
		cout << semester_name << " ";
		for(int j = 0; j < 4; j++)
			cout << courses[j] << " ";
};
	
Semester::~Semester(){
		
}

	
void AdjNode::print(){
	AdjNode * temp = next;
	
	cout <<  course.course_name;
	while(temp != NULL){
		cout << "  :  " << temp -> course;
		temp = temp -> next;
	}
	cout << endl;
}
	
AdjNode::AdjNode(){
		next = NULL;
}
	
AdjNode::~AdjNode(){
	AdjNode * temp = next;
	AdjNode * to_delete;
	while(temp != NULL){
		to_delete = temp;
		temp = temp -> next;
		delete to_delete;
	}
}

AdjacencyList::AdjacencyList(){
    required_classes = 0;
    available_courses = 0;
    required_credits = 0;
    credits_taken = 0;
    choose_course_indexes = 0;
}

void AdjacencyList::test_input(string offerings, string requirements, string schedule){
    string build_return = build_graph(offerings, requirements, schedule);
    if(build_return.find("Bad") != string::npos){
        cout << build_return << endl;
    } else {
		cout << is_schedule_valid() << endl;
	}
}

string AdjacencyList::build_graph(string offerings, string requirements, string schedule){
    string fill_return = fill_graph(offerings, requirements, schedule);
    if(fill_return.find("Bad") != string::npos)
        return fill_return;
    for(int i = 0; i < available_courses; i++)
        if(is_cs_course_offered_and_not_in_reqs(all_courses[i].course_name))
            required_classes++;
    nodes = new AdjNode[required_classes];
    int j = 0;

	/*CREATING ADJACENCY LIST
	* Checks if node is either in requirements file or if it is CS not in requirements
	* Sets up first adjacency node for each of these classes because they may
	* potentially have prereqs
	*/
    for(int i = 0; i < available_courses; i++){
        if(all_courses[i].course_type == "M" || all_courses[i].course_type == "R" || all_courses[i].course_type == "O" || is_cs_course_offered_and_not_in_reqs(all_courses[i].course_name)){
            AdjNode * t_adj = new AdjNode;
            t_adj -> course = all_courses[i];
            if(is_cs_course_offered_and_not_in_reqs(all_courses[i].course_name))
                t_adj -> course.course_type = "Y"; // Special typ for unrequired CS
            nodes[j] = *t_adj;
            j++;
        }
	}
    for(int i = 0; i < required_classes; i++){
        if(nodes[i].course.course_type == "Y"){
//==========JUST ADDED
            for(int j = 0; j < required_classes && j!=i; j++){
                if(nodes[j].course.course_name[0] != 'C' || nodes[j].course.course_name[1] != 'S')
                    continue;
                //if(nodes[i].course.course_name == nodes[j].course.course_name)
                    //continue;
                if(nodes[j].course.course_type == "M")
                    continue;
//=========JUST ADDED
				if(nodes[j].course.course_type == "O")
					continue;
                AdjNode * temp_node = new AdjNode();
                temp_node -> course.course_name = nodes[j].course.course_name;
                if(nodes[i].next == NULL){
                    nodes[i].next  = temp_node;
                } else {
                    AdjNode * last = nodes[i].next;
                    while(last -> next)
                        last = last -> next;
                    last -> next = temp_node;
                }
            }
        }
        else if(nodes[i].course.total_prerequisites > 0){
            for(int j = 0; j < nodes[i].course.total_prerequisites; j++){
                AdjNode * temp_node = new AdjNode();
                temp_node -> course.course_name = nodes[i].course.prerequisites[j];
                if(nodes[i].next == NULL)
                    nodes[i].next = temp_node;
                else{
                    AdjNode * last = nodes[i].next;
                    while(last -> next)
                        last = last -> next;
                    last -> next = temp_node;
                }
            }
        }
    }
	//SCEHDULE	
    ifstream sched_stream;
    sched_stream.open(schedule.c_str());
    string c_line;
    if(sched_stream.is_open()){
        int total_sems_added = 0;
		int num_courses_in_semester = 0;
        while(getline(sched_stream, c_line)){
			total_sems = total_sems_added;
            vector<string> vector = split(c_line);
			num_courses_in_semester = vector.size() - 1;

            Semester * t_sem = new Semester();
            t_sem -> semester_name = modify_semester_name_for_sorting(vector[0]);
            for(int i = 1; i <= num_courses_in_semester; i++){
                if(is_course_in_schedule(vector[i])){
                    return "Bad plan. Here's why: Duplicate course in schedule.";
				}
			}

			t_sem -> num_courses_in_sem = num_courses_in_semester;

			for(int i = 1; i <= num_courses_in_semester; i++){

				t_sem -> courses.push_back(vector[i]);
			}


            semesters[total_sems_added] = *t_sem;
            total_sems_added++;
        }
		total_sems = total_sems_added;
    } else {
		return "Bad plan. Here's why: Planned Schedule file does not open";
	}
    sort_schedule();
    return "Good plan. Get to work.";
}

string AdjacencyList::fill_graph(string offerings, string requirements, string schedule){
    int total_lines = 0;
    int current_line_num = 0;
    int course_index = 0;

    ifstream input_stream;
    //OFFERINGS
    input_stream.open(offerings.c_str());

    string c_line;
    if(input_stream.is_open()){
        while(getline(input_stream, c_line)){
            vector<string> vector = split(c_line);
            if(vector.size() < 3)
                return "Bad plan. Here's why: Course offering format is incorrect.";
            else if(is_course_name_valid(vector[0]))
                total_lines++;
			else 
				return "Bad plan. Here's why: Course offering format is incorrect.";
        }
        available_courses = total_lines;
        input_stream.clear();
        input_stream.seekg(0, ios::beg);
        all_courses = new Course[total_lines];
        while(getline(input_stream, c_line, '\n')){
            vector<string> vector = split(c_line);

            Course * c_course = new Course;
            c_course -> course_name = vector[0];
            c_course -> num_credits = atoi(vector[1].c_str());
            c_course -> when_offered = vector[2];
            c_course -> course_type = "X";
            c_course -> gen_ed_requirements = "N";

            //HASH MAP
            hashMap.insert({ vector[0], course_index });
            course_index++;

            if(vector.size() > 3)
                c_course -> gen_ed_requirements = vector[3];

            all_courses[current_line_num] = *c_course;
            current_line_num++;
        }
    } else {
		return "Bad plan. Here's why: Cannot open course offerings file.";	
	}	

    //REQUIREMENTS
    total_lines = 0;
    current_line_num = 0;
    int choose_indexes_added = 0;
    ifstream require_stream;
    require_stream.open(requirements);
    if(require_stream.is_open()){
        while(getline(require_stream, c_line)){
            vector<string> vector = split(c_line);
            if(vector.size() > 0 && vector[0] == "COURSE")
                total_lines++;
            if(vector.size() > 0 && vector[0] == "CHOOSE")
                choose_course_indexes++;
        }
       /* if(choose_course_indexes > 0){
            choose_courses = new Choose[choose_course_indexes];
			
		}*/

        require_stream.clear();
        require_stream.seekg(0, ios::beg);
		int totalIndicator = 0;
        while(getline(require_stream, c_line, '\n')){
            vector<string> vector = split(c_line);
            if(vector[0] == "TOTAL"){
                required_credits = atoi(vector[1].c_str());
				totalIndicator++;
				if(totalIndicator>1){
					return "Bad plan. Total required courses line appears more than once.";
				}
			}
            else if(vector[0] == "CREDIT"){
                if(vector.size() != 3)
                    return "Bad plan. Here's why: Credit requirements format is incorrect.";

                credits.push_back(new Credit(*vector[1].c_str(), atoi(vector[2].c_str())));
            }
            else if(vector[0] == ("COURSE")){
				if(vector.size() < 3){
					return "Bad plan. Here's why: Course in requirements file has incorrect format.";
				}
                int index_course = getHashIndex(vector[1]);
                if(index_course == -1){
                   	return "Bad plan. Here's why: Course in requirements file that is not in offerings file.";
				}

				if(vector[2].length() != 1){
					return "Bad plan. Here's why: Requirement type length incorrect";
				}
                char require_first_char = vector[2][0];
                if(require_first_char != 'R' && require_first_char != 'M' && require_first_char != 'O')
                    return "Bad plan. Here's why: Required type format incorrect.";
                required_classes++;
                all_courses[index_course].course_type = vector[2];
                all_courses[index_course].total_prerequisites = vector.size() - 3;
                long size = vector.size() - 3;
                if(size > 0){
                    all_courses[index_course].prerequisites = new string[size];
                }
                else
                    all_courses[index_course].prerequisites = nullptr;

                for(int i = 3; i < (all_courses[index_course].total_prerequisites + 3); i++)
                    all_courses[index_course].prerequisites[i - 3] = vector[i];
            }
            else if(vector[0] == "CHOOSE"){
                Choose * choose = new Choose();
              //  choose -> all_options = new string[vector.size() - 2];
                choose -> total_options = (int) vector.size() - 2;
				choose -> total_to_pick = atoi(vector[1].c_str());
               /* for(int i = 0; i < choose -> total_options; i++)
                    choose -> all_options[i] = vector[i + 2];*/
				for(int i = 0; i < choose -> total_options; i++)
                    choose -> all_options.push_back(vector[i + 2]);
				
               // choose_courses[choose_indexes_added] = *choose;
				choose_courses.push_back(choose);
                choose_indexes_added++;
            }
        }
    } else {
		return "Bad plan. Heres' why: Cannot open requirements file";
	}

    return "Good plan. Get to work.";
}

void AdjacencyList::sort_schedule(){
    Semester key;
    int i, j;
    for (i = 1; i < 8; i++){
        key = semesters[i];
        j = i-1;
        while (j >= 0 && semesters[j].semester_name > key.semester_name) {
            semesters[j+1] = semesters[j];
            j = j-1;
        }
        semesters[j+1] = key;
    }
}

string AdjacencyList::modify_semester_name_for_sorting(string name){
   if(name.size() == 0)
        return name;
    char first = name[0];
    name.erase(name.begin());
    if(first == 'F')
        name.append(1, 'B');
    else
        name.append(1, 'A');
    name.append(1, first);
    return name;
}

bool AdjacencyList::all_mandatory_and_required_classes_taken(){
	for(int i =0;i <available_courses; i++){
		if(all_courses[i].course_type == "M" || all_courses[i].course_type == "R"){
			if(all_courses[i].has_taken_class == false){
				return false;
			}
		}
	}
	
	return true;
}


bool AdjacencyList::is_cs_course_offered_and_not_in_reqs(string course_name){
	int index = getHashIndex(course_name);

	if(index == -1){
		return false;	
	}

    if(course_name[0] != 'C' || course_name[1] != 'S'){
        return false;
	}

	if(all_courses[index].course_type != "M" && all_courses[index].course_type != "R" && 						all_courses[index].course_type != "O"){
		return true;
	}

	return false;
}

AdjNode * AdjacencyList::get_node_for_name(string course_name){
  int i = 0;
  while(i < required_classes){
    if(course_name == nodes[i].course.course_name){
      return &(nodes[i]);
    } else{
      i++;
    }
  }
  return nullptr;
}


int AdjacencyList::getHashIndex(string name){
    unordered_map<string, int>::const_iterator hash_map_iterator = hashMap.find(name);

    if(hash_map_iterator == hashMap.end()){
        return -1;
    } else {
        return hash_map_iterator->second;
    }
}


bool AdjacencyList::is_course_name_valid(string input){
  if(input.size()!=5){
    return false;
  }

  if(!((input[0]>64 && input[0]<91) || (input[0]>96 && input[0]<123))){
    return false;
  }
  if(!((input[1]>64 && input[1]<91) || (input[1]>96 && input[1]<123))){
    return false;
  }
  if(input[2]<48 || input[2]>57){
    return false;
  }
  if(input[3]<48 || input[3]>57){
    return false;
  }
  if(input[4]<48 || input[4]>57){
    return false;
  }

  return true;
}


vector<string> AdjacencyList::split(string line){
	stringstream ss(line);
	istream_iterator<string> begin(ss);
	istream_iterator<string> end;
	vector<string> lineVect(begin, end);
	return lineVect;
}

bool AdjacencyList::is_course_available_in_registered_semester(string course_name, char semester){
    int index = getHashIndex(course_name);
    if(index == -1){
        return false;
	}
    if(all_courses[index].when_offered.back() == 'E'){
        return true;
	}
	if(all_courses[index].when_offered.find(semester) == string::npos){
		return false;
	}
    return true;
}


bool AdjacencyList::can_take_class(string course_name){
    if(!is_required_class(course_name))
        return true;
    for(int i = 0; i < required_classes; i++){
        if(nodes[i].course.course_name == course_name){
            if(!nodes[i].next){
                return true;
            } else{
                int total_passed = 0;
                AdjNode * temp = nodes[i].next;
                while(temp != NULL){
                    if(has_taken_class(temp -> course.course_name))
                        total_passed++;
                    temp = temp -> next;
                }
                return (total_passed == nodes[i].course.total_prerequisites);
            }
        }
    }
    return false;
}

void AdjacencyList::mark_class_taken(string course_name){
//cout << course_name << " HAS BEEN TAKEN" << endl;
	int index = getHashIndex(course_name);
    all_courses[index].has_taken_class = true;
    credits_taken += all_courses[index].num_credits;

    int strLen = all_courses[index].gen_ed_requirements.length();

    const char * creditArray = all_courses[index].gen_ed_requirements.c_str();

    for(int j = 0; j < strLen; j++){
        for(unsigned int k = 0; k < credits.size(); k++){
            if(creditArray[j] == credits[k]->credit_type){	
                credits[k]->num_credits_taken += all_courses[index].num_credits;
            }
        } 
    }
}

bool AdjacencyList::is_required_class(string course_name){
  int i = getHashIndex(course_name);
  
  switch(i){
	  case -1:
		return false;
	  default:
		if(all_courses[i].course_type == "X"){
		  return false;
		} else { 
		  return true;
		}
  } 
}

bool AdjacencyList::has_taken_class(string course_name){
  int i = getHashIndex(course_name);
  if(i == -1){
    return false;
  }
  return all_courses[i].has_taken_class;
}


bool AdjacencyList::is_course_in_schedule(string course_name){
   for(int i = 0; i < total_sems; i++){
        for(int j = 0; j < semesters[i].num_courses_in_sem; j++){
            if(semesters[i].courses[j] == course_name)
                return true;
		}
	}
    return false;
}


string AdjacencyList::is_schedule_valid(){
    for(int i = 0; i < total_sems; i++){
        for(int j = 0; j < semesters[i].num_courses_in_sem; j++){
            if(getHashIndex(semesters[i].courses[j]) == -1){
                string reason = "Bad plan. Here's why: ";
                reason.append(semesters[i].courses[j]);
                reason.append(" does not exist.");
                return reason;
			}
		
		    if(can_take_class(semesters[i].courses[j])){
                mark_class_taken(semesters[i].courses[j]);
			} else {
                string reason = "Bad plan. Here's why: ";
                reason.append(semesters[i].courses[j]);
                reason.append(" cannot be taken due to requirements.");
                return reason;
            }

		   if(!is_course_available_in_registered_semester(semesters[i].courses[j], 							semesters[i].semester_name.back())){
                string bad_ret = "Bad plan. Here's why: ";
                bad_ret.append(semesters[i].courses[j]);
                bad_ret.append(" registered in semester it is not offered.");
                return bad_ret;
            }
        }
    }
    
   // int total_taken = 0;
    for(int i = 0; i < choose_course_indexes; i++){
        for(int j = 0; j < choose_courses[i]->total_options; j++){
//cout << "TOTAL options: " << choose_courses[i]->total_options << endl;
            int index = getHashIndex(choose_courses[i]->all_options[j]);
            if(index == -1){
                continue;
			}
	    //cout << choose_courses[i]->all_options[j] << endl;
            if(has_taken_class(choose_courses[i]->all_options[j])){
				//cout << "TOTAL TAKEN 1 = " << choose_courses[i]->total_taken << endl;
                choose_courses[i]->total_taken++;
                break;
            }
        }
    }

	for(int i = 0; i < choose_course_indexes; i++){
		if(choose_courses[i]->total_taken < choose_courses[i]->total_to_pick){
			//cout << "Total taken = " << choose_courses[i]->total_taken << endl;
			//cout << "Total needed = " << choose_courses[i]->total_to_pick << endl;
			//cout << i << endl;
		    return "Bad plan. Here's why: Not all choose classes have been taken.";
		}
	}
    if(!all_mandatory_and_required_classes_taken()){
        return "Bad plan. Here's why: Not all mandatory and required classes have been taken.";
    }
    if(credits_taken < required_credits){
        return "Bad plan. Here's why: Not enough credits taken.";
    }

    for(unsigned int i = 0; i < credits.size(); i++){
        if(credits[i]->num_credits_taken < credits[i]->num_credits_to_take){
            cout << credits[i]->credit_type << " Credits: " << credits[i]->num_credits_taken << endl;
            string ret = "Bad plan. Here's why: Not enough ";
            string gross(1 , credits[i]->credit_type);
            ret.append(gross);
            ret.append("credits taken.");
            return ret;
        }
    }

    return "Good plan. Get to work.";
}
