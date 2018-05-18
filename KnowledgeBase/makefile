#Sonal Unadkat 	
#Assignment 1				
#301110334
#sunadkat@sfu.ca
#CMPT 310  D100
#Instructor: James Delgrande
#
.SUFFIXES: .h .o .c

CCMAIN = assign3.cpp
CC = g++
CCOPTS = -g
LIBS = -lm
OBJS = assign3.o
CCEXEC = assign2


all:	$(CCEXEC)

$(CCEXEC):	$(OBJS) makefile 
	
	$(CC) $(CCOPTS) $(OBJS) -o $@ $(LIBS)

%.o:	%.c
	
	$(CC) -c $(CCOPTS)  $<

run:	all
	./$(CCEXEC)


