SOURCE= CA5.cpp
OBJECT= CA.o
CXX:= g++
CXXFLAGS:= -c -Wall -I=.

#---------------------------------

all: link

link: compile $(SOURCE) $(OBJECT)
	g++ -o schedule.exe $(OBJECT)

compile: $(SOURCE)
	$(CXX) $(CXXFLAGS) CA5.cpp


clean:
	rm -f *.o run

compress: clean
	tar -cvvf CA5.tar *.* Makefile
	gzip CA5.tar
