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
	
	/*
	//TEST1
	AdjacencyList temp1;
	temp1.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule1.txt");
	//TEST2
	AdjacencyList temp2;
	temp2.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule2.txt");
	//TEST3
	AdjacencyList temp3;
	temp3.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule3_prereq.txt");
	
	//TEST4
		AdjacencyList temp4;
	temp4.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule4_prereq.txt");
	
	//TEST5
		AdjacencyList temp5;
	temp5.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule5_required.txt");
	
	//TEST6
		AdjacencyList temp6;
	temp6.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule6_required.txt");
	
	//TEST7
		AdjacencyList temp7;
	temp7.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule7_choose.txt");
	
	//TEST8
		AdjacencyList temp8;
	temp8.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule8_choose.txt");
	
	//TEST9
		AdjacencyList temp9;
	temp9.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule9_Hcredits.txt");
		//TEST10
		AdjacencyList temp10;
	temp10.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule10_Ccredits.txt");
		//TEST11
		AdjacencyList temp11;
	temp11.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule11_mandatory.txt");
		//TEST12
		AdjacencyList temp12;
	temp12.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule12_semester.txt");
	
	//TEST13
		AdjacencyList temp13;
	temp13.test_input("/Prog3_Test_Cases/Offered1.txt", "/Prog3_Test_Cases/Requirements1.txt", "/Prog3_Test_Cases/Schedule13_unoffered.txt");
	
	
	*/
    return 0;
}





