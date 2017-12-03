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

test: schedule.exe requirements.txt course_offerings.txt planned_schedule.txt
	./schedule.exe requirements.txt course_offerings.txt planned_schedule.txt
