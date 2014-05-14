SRCEXTS = .c .C .cc .cpp .c++ .cxx .cp
HDREXTS = .h .H .hh .hpp .h++ .hxx .hp
LIBS =
CC = gcc
CXX = g++
CTAGS = ctags
INCLUDES=-I/usr/local/include -I/usr/include -I../include -I../../include

LDFLAGS=-L/usr/local/lib -L/usr/lib -L/usr/lib64 -L../../src
LIBS=-lgtest -lpthread
CFLAGS = -g -Wall -O2 -fPIC -c $(INCLUDES)
OFLAGS = -g -O2 -Wall $(LDFLAGS) $(LIBS) 
SRCDIR = .
SRCS = $(wildcard $(SRCDIR)/*.cc $(SRCDIR)/*.cpp)
OBJS = $(addsuffix .o, $(basename $(SRCS)))
HEADS = $(addsuffix .h, $(basename $(SRCS)))
SRCOBJS = ../../src/*.o

APP = log4cpp_test

all : $(APP)

show :
	@echo $(CFLAGS)
	@echo $(OFLAGS)

$(APP) : $(OBJS) $(SRCOBJS)
	$(CXX) -o $@ $^ $(OFLAGS)

%.o:%.cc
	$(CXX) $(CFLAGS) -o $@ $<

%.o:%.cpp
	$(CXX) $(CFLAGS) -o $@ $<

clean :
	rm -rf *.o $(APP)	
