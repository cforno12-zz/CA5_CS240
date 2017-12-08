SOURCE= AdjacencyList.cpp Course.cpp main.cpp
OBJECT= AdjacencyList.o Course.o main.o
CXX:= g++
CXXFLAGS:= -c -Wall -I=.

#---------------------------------

all: link test02

link: compile $(SOURCE) $(OBJECT)
	g++ -o schedule.exe $(OBJECT)

compile: $(SOURCE)
	$(CXX) $(CXXFLAGS) AdjacencyList.cpp
	$(CXX) $(CXXFLAGS) Course.cpp
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	rm -f *.o schedule.exe

compress: clean
	tar -cvvf CA5.tar *.* Makefile ./test_cases
	gzip CA5.tar

test02:
	./schedule.exe ./more_test_cases/test8/reqs.txt ./more_test_cases/test8/offers.txt ./more_test_cases/test8/schedule.txt
	echo It should say you did not take enough choose courses

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
	./schedule.exe ./more_test_cases/test1_pass/requirementFile.txt ./more_test_cases/test1_pass/offeringsFile.txt ./more_test_cases/test1_pass/unorderedSchedule.txt
	echo good
	./schedule.exe ./more_test_cases/test2/requirementFile.txt ./more_test_cases/test2/offeringsFile.txt ./more_test_cases/test2/schedule.txt
	echo not enough C credits
	./schedule.exe ./more_test_cases/test3/reqs.txt ./more_test_cases/test3/offers.txt ./more_test_cases/test3/schedule.txt
	echo It should say you dont have enough X credits to graduate.
	./schedule.exe ./more_test_cases/test4/reqs.txt ./more_test_cases/test4/offers.txt ./more_test_cases/test4/schedule.txt
	echo prereqs are not coreqs
	./schedule.exe ./more_test_cases/test5/R1.txt ./more_test_cases/test5/O1.txt ./more_test_cases/test5/P1.txt
	echo eng125
	./schedule.exe ./more_test_cases/test6/R1.txt ./more_test_cases/test6/O1.txt ./more_test_cases/test6/P1.txt
	echo 110 or 210
	./schedule.exe ./more_test_cases/test7/R1.txt ./more_test_cases/test7/O1.txt ./more_test_cases/test7/P1.txt
	echo good
