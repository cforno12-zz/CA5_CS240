#include <iostream>
#include "AdjacencyList.h"

using namespace std;

int main(int argc, const char * argv[]) {
	
  	if(argc != 4)
  		return 1;
	
	string offerings = argv[2];
	string requirements = argv[1];
	string schedule = argv[3];
	
	AdjacencyList temp1;
	temp1.build_list(offerings, requirements, schedule);
	
	//std::cout << (temp1.is_schedule_valid() ? "Good" : "Bad" ) << std::endl;
	
	
	/* for(int i = 0; i < temp1.total_required_classes; i++)
		temp1.nodes[i].print();*/
	
	/*for(int i = 0; i < temp1.total_required_classes; i++){
		std::cout << temp1.nodes[i].course << std::endl;
	}*/
	

    return 0;
}





