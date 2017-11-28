#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <fstream>

using namespace std;

int main(int argc, char ** argv){
	fstream stm;
	stm.open(argv[1]); // requirements file

	exit (0);
}
