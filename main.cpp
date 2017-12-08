#include <iostream>
#include "AdjacencyList.h"

using namespace std;

int main(int argc, const char * argv[]) {
  	if(argc != 4)
        return 1;
    string offerings = argv[2];
    string requirements = argv[1];
    string schedule = argv[3];
    AdjacencyList main;
    main.test_input(offerings, requirements, schedule);

    std::cout << (main.is_schedule_valid() ? "Good" : "Bad" ) << std::endl;


    for(int i = 0; i < main.required_classes; i++)
      main.nodes[i].print();

    for(int i = 0; i < main.required_classes; i++){
      std::cout << main.nodes[i].course << std::endl;
    }
    exit(0);
}





