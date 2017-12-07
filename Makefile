SOURCE= AdjacencyList.cpp Course.cpp main.cpp
OBJECT= AdjacencyList.o Course.o main.o
CXX:= g++
CXXFLAGS:= -c -Wall -I=.

#---------------------------------

all: link test

link: compile $(SOURCE) $(OBJECT)
	g++ -o schedule.exe $(OBJECT)

compile: $(SOURCE)
	$(CXX) $(CXXFLAGS) AdjacencyList.cpp
	$(CXX) $(CXXFLAGS) Course.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm -f *.o schedule.exe

compress: clean
	tar -cvvf CA5.tar *.* Makefile
	gzip CA5.tar

test: schedule.exe
	./schedule.exe ./test_cases/requirements.txt ./test_cases/course_offerings.txt ./test_cases/planned_schedule.txt
	echo good
	./schedule.exe ./test_cases/test1/requirements.txt ./test_cases/test1/course_offerings.txt ./test_cases/test1/planned_schedule.txt
	echo good
	./schedule.exe ./test_cases/test2/requirements.txt ./test_cases/test2/course_offerings.txt ./test_cases/test2/planned_schedule.txt
	echo prereq for 350
	./schedule.exe ./test_cases/test3/requirements.txt ./test_cases/test3/course_offerings.txt ./test_cases/test3/planned_schedule.txt
	echo fails doesnt meet credit requirement
	./schedule.exe ./test_cases/test4/requirements.txt ./test_cases/test4/course_offerings.txt ./test_cases/test4/planned_schedule.txt
	echo fails retaking a class
	./schedule.exe ./test_cases/test5/requirements.txt ./test_cases/test5/course_offerings.txt ./test_cases/test5/planned_schedule.txt
	echo fails not taking one/enough of the choice classes
