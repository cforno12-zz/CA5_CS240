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


