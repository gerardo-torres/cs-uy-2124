
rec07: rec07.o Course.o Registrar.o Student.o
	g++ rec07.o Course.o Registrar.o Student.o -o rec07

rec07.o: rec07.cpp
	g++ -c rec07.cpp

Course.o: Course.cpp Course.h
	g++ -c Course.cpp

Registrar.o: Registrar.cpp Registrar.h
	g++ -c Registrar.cpp

Student.o: Student.cpp Student.h
	g++ -c Student.cpp

clean: 
	rm *.o rec07
