SRCEXTS = .c .C .cc .cpp .c++ .cxx .cp
HDREXTS = .h .H .hh .hpp .h++ .hxx .hp
LIBS = 
CC = gcc
CXX = g++
CTAGS = ctags
INCLUDES=-I/usr/local/include -I/usr/include -I/usr/include/libxml2 -I../wiwo/common -I../message

LIBS=-L/usr/local/lib -L/usr/lib -L/usr/lib/mysql -L../wiwo/libs -lmessage -lwiwo_common
CFLAGS = -g -Wall -O2 -fPIC -c $(INCLUDES)
OFLAGS = -g -O2 -shared -Wall $(LIBS)

SRCDIR = .
SRCS = $(wildcard $(SRCDIR)/*.cc $(SRCDIR)/*.cpp)
OBJS = $(addsuffix .o, $(basename $(SRCS)))
HEADS = $(addsuffix .h, $(basename $(SRCS)))

APP = ListVmInstance.so

all : $(APP)

show :
	@echo $(CFLAGS)

$(APP) : $(OBJS)
	$(CXX) $(OFLAGS) -o $@ $^

%.o:%.cc
	$(CXX) $(CFLAGS) -o $@ $<

%.o:%.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean :
	rm -Rf *.o $(APP)

install :
	cp $(APP) ../../wiwo/libs/
