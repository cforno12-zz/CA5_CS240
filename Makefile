SOURCE= AdjacencyList.cpp Course.cpp main.cpp
OBJECT= AdjacencyList.o Course.o main.o
CXX:= g++
CXXFLAGS:= -c -Wall -I=.

#---------------------------------

all: link curr_test

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

curr_test:
	./schedule.exe ./more_test_cases/test9/requirements.txt ./more_test_cases/test9/offerings.txt ./more_test_cases/test9/schedule.txt
	echo duplicate courses

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
	./schedule.exe ./more_test_cases/test8/reqs.txt ./more_test_cases/test8/offers.txt ./more_test_cases/test8/schedule.txt
	echo It should say you did not take enough choose courses
	./schedule.exe ./more_test_cases/test9/requirements.txt ./more_test_cases/test9/offerings.txt ./more_test_cases/test9/schedule.txt
	echo duplicate courses
	./schedule.exe ./more_test_cases/test10/requirements.txt ./more_test_cases/test10/offerings.txt ./more_test_cases/test10/planned.txt
	echo prereqs were not taken OR unsorted
	./schedule.exe ./more_test_cases/test11/requirements.txt ./more_test_cases/test11/offerings.txt ./more_test_cases/test11/planned.txt
	echo H credits not taken OR unsorted
	./schedule.exe ./more_test_cases/test12/r.txt ./more_test_cases/test12/o.txt ./more_test_cases/test12/p.txt
	echo  did not take the mandatory and required classes CS900 and EN900
	./schedule.exe ./more_test_cases/test13/requirements.txt ./more_test_cases/test13/offerings.txt ./more_test_cases/test13/planned.txt
	echo attempting to take CS220 and CS240 in the same semester, even though CS220 is a prerequisite to CS240.
	./schedule.exe ./more_test_cases/test14/requirements.txt ./more_test_cases/test14/courseOffer.txt ./more_test_cases/test14/plannedSchedule.txt
	echo good
	./schedule.exe ./more_test_cases/test15/requirements.txt ./more_test_cases/test15/courseOffer.txt ./more_test_cases/test15/plannedSchedule.txt
	echo not offered course CS602
	./schedule.exe ./more_test_cases/test16/requirements.txt ./more_test_cases/test16/courseOffer.txt ./more_test_cases/test16/plannedSchedule.txt
	echo no prerequire course for CS506
	./schedule.exe ./more_test_cases/test17/requirements.txt ./more_test_cases/test17/courseOffer.txt ./more_test_cases/test17/plannedSchedule.txt
	echo lack of M or R course CS308
	./schedule.exe ./more_test_cases/test18/requirements.txt ./more_test_cases/test18/courseOffer.txt ./more_test_cases/test18/plannedSchedule.txt
	echo lack of CHOOSE 1 CS101 dont satisfy
	./schedule.exe ./more_test_cases/test19/requirements.txt ./more_test_cases/test19/course_offerings.txt ./more_test_cases/test19/planned_schedule.txt
	echo good
	./schedule.exe ./more_test_cases/test19/requirements.txt ./more_test_cases/test19/course_offerings.txt ./more_test_cases/test19/invalid_schedule.txt
	echo bad - we will find out why
	./schedule.exe ./more_test_cases/test20/requirements.txt ./more_test_cases/test20/offerings.txt ./more_test_cases/test20/plan_good.txt
	echo good
	./schedule.exe ./more_test_cases/test20/requirements.txt ./more_test_cases/test20/offerings.txt ./more_test_cases/test20/plan_bad.txt
	echo  there is a fall spring conflict with CH107/CH108
	./schedule.exe ./more_test_cases/test20/requirements.txt ./more_test_cases/test20/offerings.txt ./more_test_cases/test20/plan_bad2.txt
	echo  there is CS140 is not taken causing conflicts with prereqs and also required classes have not been taken
