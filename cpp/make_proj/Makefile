CC = gcc
CFLAGS = -c
CFLAGS += -g
OBJ_FILE = hello.o

Name = "Chris"
Name += "Xiao"

define CMD_Package   # define command package, usage:$(package_name)
@echo "Enter command package"
@pwd
@echo $(Name)
@echo "Leave command package"
endef

hello : $(OBJ_FILE)
	$(CC) -o hello hello.o
	@echo $(SHELL)
hello.o : hello.c CommonDef.h   # this line and next line is optional
	@echo Compiling is running, pls wait ...
	@cd /home/admin;pwd         #'@' just execute cmd, donot display command
	$(CC) $(CFLAGS) hello.c
	$(CMD_Package)
ifneq (0, ${MAKELEVEL})
	@echo "Make level is not 0, level is $(MAKELEVEL)"
endif

ifeq ($(CC), gcc)
	@echo "CC variable is gcc"
else
	@echo "CC variable is not gcc, it's $(CC)"
endif

    ifdef ($(CFLAG))   # condition sentence can begin with space, but not tab
		@echo "CFLAG variable is defined"
    else
		@echo "CFLAG variable is not defined"
    endif

#    OrigStr = "on the street"
    RetStr = $(subst ee,EE,street)
#@echo "string after replacement:$(RetStr)"
	echo $(RetStr)
	echo Hello

.PHONY : clean
clean:
	-rm hello $(OBJ_FILE)
