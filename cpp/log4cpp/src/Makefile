SRCEXTS = .c .C .cc .cpp .c++ .cxx .cp
HDREXTS = .h .H .hh .hpp .h++ .hxx .hp
LIBS =
CC = gcc
CXX = g++
CTAGS = ctags
INCLUDES=-I/usr/local/include -I/usr/include -I../include

LIBS=-L/usr/local/lib -L/usr/lib
CFLAGS = -g -Wall -O2 -fPIC -c $(INCLUDES)
OFLAGS = -g -O2 -Wall $(LIBS)

SRCDIR = .
SRCS = $(wildcard $(SRCDIR)/*.cc $(SRCDIR)/*.cpp)
OBJS = $(addsuffix .o, $(basename $(SRCS)))
HEADS = $(addsuffix .h, $(basename $(SRCS)))

APP = log4cpp

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
	rm -rf *.o $(APP)	
