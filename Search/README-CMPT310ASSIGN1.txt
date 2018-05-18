Sonal Unadkat 	
Assignment 1				
301110334
sunadkat@sfu.ca
CMPT 310  D100
Instructor: James Delgrande



Assignment 1 Files Included in submit.zip
	assignment1.cpp											source code
	README-CMPT310ASSIGN1.txt
	Assignment1Report.pdf

	File : UNIX 											executable file for Linux/Mac Systems
		makefile (for UNIX compiling only)					
		assign1.exe

	File : Windows                             				executable files for Windows
		assign1.exe           

About:
	Assignment 1 is a program that is intended to take an input of two coordianates, and find the shortest distance between them. The user will also have a choice of using landmarks, which will make the program run more faster, or without landmarks, which would be more optimal. 

Source Code : 
	The source code has been written in C++ .  The difference between the UNIX executable and Windows executable is that System("Pause") has been added to the Windows Executable source code, for the convenience of the user. 


Program Requirments/ User Inputs:

User Inputs :
1. 	Initial Coordinates : Must be two numbers, within the range of (0 -17 inclusive) seperated with a space between them. 
2. 	Goal Outputs :  Must be two numbers, within the range of (0 -17 inclusive) seperated with a space between them. 
3.  If you would like to use Landmarks (Part 2 of the assignment), then you must submit Y or y as your input. 
4. 	There are blocked/inadmissable coordinates in this program, you cannot enter the following coordinates as your input. By doing so, this will cause an erroneous inputs and cause the program to terminate
	Blocked/ Inaccessible Coordinates :
		(7, 5),(7, 6),(7, 7),(7, 8),(7, 9) and
		(10, 13),(11, 13),(12, 13),(13, 13),(14, 13),(15, 13),(15, 12)

Any Wrong inputs will result in the program ending.  You must restart the program to try again.

Relevant Makefile Commands and Execution (For UNIX System - Linux/Mac) 

	They are many relevant commands that can be used due to the inclusion of a makefile when compiling Asssignment 1. The following compiling linux commands can be used to compile and build Asssignment 1, as well as clean and remove the older files decrypted tweets. The first step is to move into the directory that Asssignment 1 can be found on our terminal.

			
	1. Compiling Asssignment 1 : To use Asssignment 1, the user must compile Asssignment 1 on their UNIX terminal using the following command:

	   											Terminal Command:   	     $ make assign1                or            $ make all 

	2. Execution: 

		(a) After compilation, to run Asssignment 1, you can execute this program by typing into terminal connected to the directory where the executable file is located by

       											Terminal Command:          $ ./assign1 

       	(b) By Double-Clicking on the executable file named : assign1 will also start the program


Relevant Execution Commands (For Windows System) 

		(a). If you are using windows, to execute this program, you just need to choose the file that is named : Assign1.exe and it will start the progr


Thank you!

Sources and References:
	A* search :  https://en.wikipedia.org/wiki/A*_search_algorithm
	Heurisitcs : http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html

				



