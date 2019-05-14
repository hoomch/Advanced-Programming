all: a.out

a.out: main.o interface.o class_LinkedIn.o company.o request.o job.o user.o skill.o experience.o date.o
	g++ main.o interface.o class_LinkedIn.o company.o request.o job.o user.o skill.o experience.o date.o 

main.o: main.cpp 
	g++ -c main.cpp interface.hpp

interface.o: interface.cpp
	g++ -c interface.cpp

class_LinkedIn.o: class_LinkedIn.cpp
	g++ -c class_LinkedIn.cpp

company.o: class_company.cpp
	g++ -c class_company.cpp

request.o: class_request.cpp
	g++ -c class_request.cpp

job.o: class_job.cpp
	g++ -c class_job.cpp

user.o: class_user.cpp
	g++ -c class_user.cpp

skill.o: class_skill.cpp
	g++ -c class_skill.cpp

experience.o : class_experience.cpp
	g++ -c class_experience.cpp

date.o: class_date.cpp class_date.hpp libraries.hpp
	g++ -c class_date.cpp

clean:
	rm *.o
	rm a.out				