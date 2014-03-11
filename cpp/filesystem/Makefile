obj = file_sys.o main.o
CXX = g++

filesys : $(obj)
	$(CXX) -o filesys $(obj)
file_sys.o : file_sys.cpp file_sys.h
	$(CXX) -c file_sys.cpp
main.o : main.cpp file_sys.h
	$(CXX) -c main.cpp

.PHONY : clean
clean:
	-rm filesys *.o
