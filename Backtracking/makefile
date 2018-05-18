#Sonal Unadkat 	
#Assignment 1				
#301110334
#sunadkat@sfu.ca
#CMPT 310  D100
#Instructor: James Delgrande
#
.SUFFIXES: .h .o .c

CCMAIN = assign2.cpp
CC = g++
CCOPTS = -g
LIBS = -lm
OBJS = assign2.o
CCEXEC = assign2


all:	$(CCEXEC)

$(CCEXEC):	$(OBJS) makefile 
	
	$(CC) $(CCOPTS) $(OBJS) -o $@ $(LIBS)

%.o:	%.c
	
	$(CC) -c $(CCOPTS)  $<

run:	all
	./$(CCEXEC)


