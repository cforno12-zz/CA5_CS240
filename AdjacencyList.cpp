#include "AdjacencyList.h"
#include <unordered_map>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;

AdjacencyList::AdjacencyList(){
    required_classes = 0;
    available_courses = 0;
    required_credits = 0;
    credits_taken = 0;
    choose_course_indexes = 0;
}

/*void AdjacencyList::test_input(string offerings, string requirements, string schedule){
    string build_return = build_list(offerings, requirements, schedule);
    if(build_return.find("Bad") != string::npos){
        cout << build_return << endl;
        return;
    }
    string is_schedule_valid_return = is_schedule_valid();
    cout << is_schedule_valid_return << endl;
}*/

void AdjacencyList::build_list(string offerings, string requirements, string schedule){
    //string fill_return = fill_list(offerings, requirements, schedule);
    //if(fill_return.find("Bad") != string::npos)
       // return fill_return;
    for(int i = 0; i < available_courses; i++)
        if(is_cs_course_offered_and_not_in_reqs(all_courses[i].course_name))
            required_classes++;
    nodes = new AdjNode[required_classes];
    int j = 0;
    for(int i = 0; i < available_courses; i++)
        if(all_courses[i].course_type == "M" || all_courses[i].course_type == "R" || all_courses[i].course_type == "O" || is_cs_course_offered_and_not_in_reqs(all_courses[i].course_name)){
            AdjNode * t_adj = new AdjNode;
            t_adj -> course = all_courses[i];
            if(is_cs_course_offered_and_not_in_reqs(all_courses[i].course_name))
                t_adj -> course.course_type = "Y";
            nodes[j] = *t_adj;
            j++;
        }

    for(int i = 0; i < required_classes; i++){
        if(nodes[i].course.course_type == "Y"){
            for(int j = 0; j < required_classes; j++){
                if(nodes[j].course.course_name[0] != 'C' || nodes[j].course.course_name[1] != 'S')
                    continue;
                if(nodes[i].course.course_name == nodes[j].course.course_name)
                    continue;
                if(nodes[j].course.course_type == "M")
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
    ifstream input_stream;
    input_stream.open(schedule.c_str());
    string c_line;
    if(input_stream.is_open()){
        int total_sems_added = 0;
        while(getline(input_stream, c_line)){
            vector<string> vector = split(c_line);
            if(vector.size() != 5){
				cout << "Bad plan. Here's why: Semester " << to_string(total_sems_added + 1) << 				" does not have 4 classes." << endl;
				return;
               /* string bad_return = "Bad plan. Here's why: Semester ";
                bad_return.append(to_string(total_sems_added + 1));
                bad_return.append(" does not have 4 classes.");
                return bad_return;*/
            }
            Semester * t_sem = new Semester();
            t_sem -> semester_name = modify_semester_name_for_sorting(vector[0]);
            for(int i = 1; i < 5; i++)
                if(is_course_in_schedule(vector[i])){
                    cout << "Bad plan. Here's why: Duplicate course in schedule." << endl;
					return;
				}
            t_sem -> courses[0] = vector[1];
            t_sem -> courses[1] = vector[2];
            t_sem -> courses[2] = vector[3];
            t_sem -> courses[3] = vector[4];
            semesters[total_sems_added] = *t_sem;
            total_sems_added++;
        }
        if(total_sems_added != 8){
            cout << "Bad plan. Here's why: Schedule does not have 8 semesters." << endl;
			return;
		}
    }
    sort_schedule();
    cout << "Good plan. Get to work." << endl;
	return;
}

void AdjacencyList::fill_list(string offerings, string requirements, string schedule){
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
            if(vector.size() < 3){
                cout << "Bad plan. Here's why: Course offering format is incorrect." << endl;
				return;
			}
            else if(is_course_name_valid(vector[0]))
                total_lines++;
        }
        available_courses = total_lines;
        input_stream.clear();
        input_stream.seekg(0, ios::beg);
        all_courses = new Course[total_lines];
        while(getline(input_stream, c_line, '\n')){
            vector<string> vector = split(c_line);
            if(vector.size() < 3 || !is_course_name_valid(vector[0]))
                continue;

            Course * c_course = new Course;
            c_course -> course_name = vector[0];
            c_course -> num_credits = atoi(vector[1].c_str());
            c_course -> when_offered = vector[2];
            c_course -> course_type = "X";
            c_course -> requirements_type = "N";

            //HASH MAP ADDITION
            hashMap.insert({ vector[0], course_index });
            //cout << "Course: " << vector[0] << " Index: " << course_index << endl;
            course_index++;

            /*if(vector.size>3){
              if (strlen(vector[3]) != 1){
              char[] type = vector[3].c_str();
              }
              for(int i = 0; i < strlen(type); i++){
              requirements_type[i] = type[i];
              }
              }*/

            if(vector.size() > 3)
                c_course -> requirements_type = vector[3];
            all_courses[current_line_num] = *c_course;
            current_line_num++;
        }
    }

    //REQUIREMENTS
    total_lines = 0;
    current_line_num = 0;
    int choose_indexes_added = 0;
    ifstream t_input_stream;
    t_input_stream.open(requirements);
    if(input_stream.is_open()){
        while(getline(t_input_stream, c_line)){
            vector<string> vector = split(c_line);
            if(vector.size() > 0 && vector[0] == "COURSE")
                total_lines++;
            if(vector.size() > 0 && vector[0] == "CHOOSE")
                choose_course_indexes++;
        }
        if(choose_course_indexes > 0)
            choose_courses = new Choose[choose_course_indexes];
        t_input_stream.clear();
        t_input_stream.seekg(0, ios::beg);
        while(getline(t_input_stream, c_line, '\n')){
            vector<string> vector = split(c_line);
            if(vector[0] == "TOTAL")
                required_credits = atoi(vector[1].c_str());
            else if(vector[0] == "CREDIT"){
                if(vector.size() != 3){
                    cout << "Bad plan. Here's why: Required class format incorrect." << endl;
					return;
				}
                /*int strLen = vector[1].length();

                  char * creditArray = vector[1].c_str();*/

                /*for(int i = 0; i < strLen; i++){*/
                credits.push_back(new Credit(*vector[1].c_str(), atoi(vector[2].c_str())));
                /*}*/

                /*if(vector[1] == "C")
                  total_c_credits_required = atoi(vector[2].c_str());
                  else if(vector[1] == "H")
                  total_h_credits_required = atoi(vector[2].c_str());
                  else if(vector[1] == "F")
                  total_f_credits_required = atoi(vector[2].c_str());*/
            }
            else if(vector[0] == ("COURSE")){
                int index_course = get_course_index_for_name(vector[1]);
                if(index_course == -1)
                    continue;
                char index_2_back = vector[2].back();
                if(index_2_back != 'R' && index_2_back != 'M' && index_2_back != 'O'){
                    cout << "Bad plan. Here's why: Required class format incorrect." << endl;
					return;
				}
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
                choose -> all_options = new string[vector.size() - 2];
                choose -> total_options = (int) vector.size() - 2;
                for(int i = 0; i < choose -> total_options; i++)
                    choose -> all_options[i] = vector[i + 2];
                choose_courses[choose_indexes_added] = *choose;
                choose_indexes_added++;
            }
        }
    }
    cout << "Good plan. Get to work." << endl;
	return;
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
    for(int i = 0; i < available_courses; i++)
        if((all_courses[i].course_type == "M" || all_courses[i].course_type == "R") && !all_courses[i].has_taken_class)
            return false;
    return true;
}


bool AdjacencyList::is_cs_course_offered_and_not_in_reqs(string course_name){
    if(course_name[0] != 'C' || course_name[1] != 'S')
        return false;
    for(int i = 0; i < available_courses; i++)
        if(all_courses[i].course_name == course_name && (all_courses[i].course_type == "M" || all_courses[i].course_type == "R" || all_courses[i].course_type == "O"))
            return false;
    return get_course_index_for_name(course_name) != -1;
}

AdjNode * AdjacencyList::get_node_for_name(string course_name){
    for(int i = 0; i < required_classes; i++)
        if(nodes[i].course.course_name == course_name)
            return &nodes[i];
    return nullptr;
}


int AdjacencyList::get_course_index_for_name(string name){
    unordered_map<string, int>::const_iterator hash_map_iterator = hashMap.find(name);

    if(hash_map_iterator == hashMap.end()){
        //cout << "Returns : " << hash_map_iterator->second << endl;
        return -1;
    } else {
        //cout << "Returns : " << hash_map_iterator->second << endl;
        return hash_map_iterator->second;
    }

    /*for(int i = 0; i < available_courses; i++){
      if(all_courses[i].course_name == name)
			return i;
      }
      return -1;*/
}


bool AdjacencyList::is_course_name_valid(string input){
    if(input.size() != 5)
        return false;
    int total_num = 0;
    int total_char = 0;

    for(int i = 0; i < 2; i++)
        if((input[i] >= 65 && input[i] < 91) || (input[i] >= 97 && input[i] <= 122))
            total_char++;
    for(int i = 2; i < 5; i++)
        if(input[i] >= 48 && input[i] < 58)
            total_num++;
    return total_num == 3 && total_char == 2;
}


vector<string> AdjacencyList::split(string input){
    bool in_word = false;
    int total_words = 0;

    for(unsigned int i = 0; i < input.size(); i++){
        if(input[i] != 32 && !in_word){
            in_word = true;
            total_words++;
        }
        if(input[i] == 32)
            in_word = false;
    }

    string * attr = new string[total_words];

    int i = 0;
    stringstream ssin(input);
    while (ssin.good() && i < total_words){
        ssin >> attr[i];
        ++i;
    }
    vector<string> vect (attr, attr + total_words);
    return vect;
}

bool AdjacencyList::is_course_available_in_registered_semester(string course_name, char semester){
    int index = get_course_index_for_name(course_name);
    if(index == -1)
        return false;
    if(all_courses[index].when_offered.back() == 'E')
        return true;
    return all_courses[index].when_offered.find(semester) != string::npos;
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
    for(int i = 0; i < available_courses; i++)
        if(all_courses[i].course_name == course_name){
            all_courses[i].has_taken_class = true;
            credits_taken += all_courses[i].num_credits;

            int strLen = all_courses[i].requirements_type.length();

            const char * creditArray = all_courses[i].requirements_type.c_str();

            for(int j = 0; j < strLen; j++){
                for(unsigned int k = 0; k < credits.size(); k++){
                    if(creditArray[j] == credits[k]->credit_type){	
                        credits[k]->num_credits_taken += all_courses[i].num_credits;
                    }
                } 
            }

            /*if(all_courses[i].requirements_type.find("C") != string::npos)
              total_c_credits_taken += all_courses[i].num_credits;
              if(all_courses[i].requirements_type.find("H") != string::npos)
              total_h_credits_taken += all_courses[i].num_credits;
              if(all_courses[i].requirements_type.find("F") != string::npos)
              total_f_credits_taken += all_courses[i].num_credits;*/
        }
}

bool AdjacencyList::is_required_class(string course_name){
    int index = get_course_index_for_name(course_name);
    if(index == -1)
        return false;
    return all_courses[index].course_type != "X";
}

bool AdjacencyList::has_taken_class(string course_name){
    for(int i = 0; i < available_courses; i++)
        if(all_courses[i].course_name == course_name)
            return all_courses[i].has_taken_class;
    return false;
}


bool AdjacencyList::is_course_in_schedule(string course_name){
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 4; j++)
            if(semesters[i].courses[j] == course_name)
                return true;
    return false;
}


void AdjacencyList::is_schedule_valid(){
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++){
            if(get_course_index_for_name(semesters[i].courses[j]) == -1){
				cout << "Bad plan. Here's why: " << semesters[i].courses[j] << " does not exist." 					<< endl;
               /* string reason = "Bad plan. Here's why: ";
                reason.append(semesters[i].courses[j]);
                reason.append(" does not exist.");*/
                return;
            }
        }
    }

    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++){
            if(can_take_class(semesters[i].courses[j]))
                mark_class_taken(semesters[i].courses[j]);
            else{
				cout << "Bad plan. Here's why: " << semesters[i].courses[j] 							<< " cannot be taken due to requirements." << endl;
                /*string reason = "Bad plan. Here's why: ";
                reason.append(semesters[i].courses[j]);
                reason.append(" cannot be taken due to requirements.");*/
                return;
            }
        }
    }
    for(int i = 0; i < 8; i++){
        for(int j = 0; j < 4; j++){
            if(!is_course_available_in_registered_semester(semesters[i].courses[j], semesters[i].semester_name.back())){
				cout << "Bad plan. Here's why: " << semesters[i].courses[j] 								<< " registered in semester it is not offered." << endl;
              /*  string bad_ret = "Bad plan. Here's why: ";
                bad_ret.append(semesters[i].courses[j]);
                bad_ret.append(" registered in semester it is not offered."); */
                return;
            }
        }
    }
    int total_taken = 0;
    for(int i = 0; i < choose_course_indexes; i++){
        for(int j = 0; j < choose_courses[i].total_options; j++){
            int index = get_course_index_for_name(choose_courses[i].all_options[j]);
            if(index == -1)
                continue;
            if(has_taken_class(choose_courses[i].all_options[j])){
                total_taken++;
                break;
            }
        }
    }

    if(total_taken < choose_course_indexes){
        cout << "Bad plan. Here's why: Not all choose classes have been taken." << endl;
		return;
    }
    if(!all_mandatory_and_required_classes_taken()){
        cout << "Bad plan. Here's why: Not all mandatory or required classes have been taken." 			<< endl;
		return;
    }
    if(credits_taken < required_credits){
        cout << "Bad plan. Here's why: Not enough credits taken." << endl;
		return;
    }

    for(unsigned int i = 0; i < credits.size(); i++){
        if(credits[i]->num_credits_taken < credits[i]->num_credits_to_take){
            cout << credits[i]->credit_type << " Credits: " << credits[i]->num_credits_taken << endl;
            cout << "Bad plan. Here's why: Not enough " << credits[i]->credit_type 						<< "credits taken." << endl;
			/*string ret = "Bad plan. Here's why: Not enough ";
            string gross(1 , credits[i]->credit_type);
            ret.append(gross);
            ret.append("credits taken.");*/
            return;
        }
    }

    /*if(total_c_credits_taken < total_c_credits_required){
      cout << "C Credits: " << total_c_credits_taken << endl;
      return "Bad plan. Here's why: Not enough C credits taken.";
      }
      if(total_h_credits_taken < total_h_credits_required){
      cout << "h Credits: " << total_h_credits_taken << endl;
      return "Bad plan. Here's why: Not enough H credits taken.";
      }
      if(total_f_credits_taken < total_f_credits_required){
      cout << "f Credits: " << total_f_credits_taken << endl;
      return "Bad plan. Here's why: Not enough F credits taken.";
      }*/
    cout << "Good plan. Get to work." << endl;
	return;
}
