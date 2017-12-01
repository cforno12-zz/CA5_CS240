#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "PrereqLL.h"

PrereqLL::PrereqLL(){
    head = nullptr;
}

void PrereqLL::add_prereq(PrereqNode* pn){
    if(head == nullptr){
        head = pn;
    } else {
        PrereqNode* temp = head;
        head = pn;
        head->next = temp;
    }
}

void PrereqLL::print_prereqs(){
    if(!head){
        if(!head->next){
            cout << head->data->course->course_name << endl;
        } else {
            PrereqNode* curr = head;
            while(curr){
                cout << curr->data->course->course_name << endl;
                curr = curr->next;
            }
        }
    }
}
