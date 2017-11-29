SOURCE= CA5.cpp Req_graph.h Req_graph.cpp Course_Node.h Course_Node.cpp PrereqLL.h PrereqLL.cpp PrereqNode.h PrereqNode.cpp Course.h Course.cpp
OBJECT= CA.o Req_graph.o Course_Node.o PrereqLL.o PrereqNode.o Course.o
CXX:= g++
CXXFLAGS:= -c -Wall -I=.

#---------------------------------

all: link

link: compile $(SOURCE) $(OBJECT)
	g++ -o schedule.exe $(OBJECT)

compile: $(SOURCE)
	$(CXX) $(CXXFLAGS) CA5.cpp
	$(CXX) $(CXXFLAGS) Req_graph.cpp
	$(CXX) $(CXXFLAGS) Course_Node.cpp
	$(CXX) $(CXXFLAGS) PrereqLL.cpp
	$(CXX) $(CXXFLAGS) PrereqNode.cpp
	$(CXX) $(CXXFLAGS) Course.cpp

clean:
	rm -f *.o run

compress: clean
	tar -cvvf CA5.tar *.* Makefile
	gzip CA5.tar
