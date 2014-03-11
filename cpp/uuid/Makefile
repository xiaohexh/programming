obj = my_uuid.o main.o
CXX = g++

my_uuid : $(obj)
	$(CXX) -o my_uuid $(obj) -luuid
my_uuid.o : my_uuid.cpp my_uuid.h
	$(CXX) -c -g my_uuid.cpp
main.o : main.cpp my_uuid.h
	$(CXX) -c -g main.cpp

.PHONY : clean
clean:
	-rm my_uuid *.o
