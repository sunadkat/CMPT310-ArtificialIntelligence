Sonal Unadkat 	
Assignment 2				
301110334
sunadkat@sfu.ca
CMPT 310  D100
Instructor: James Delgrande


GRADING NOTES: Please do not double click on the executable, please grade on the terminal by running on a LINUX/UNIX(MAC OKAY) ENVIRONMENT
		
Terminal : 				./assign2

 Please ensure that the text file to evaluate is in the same directory. 

Thank you


Assignment 2 Files Included in code.zip
	assign2.cpp							source code
	README.txt					
	makefile (for UNIX compiling only)					//  	
	assign2.exe
      

About:
		Assignment 2 is a program that is intended to take in a file, that containts the number of states and colors and neighbours of each state, and find if a colouring solution exists to the map.  

Source Code : 
		The source code has been written in C++ .  It is intended it run on UNIX/LINUX machines, and will not work on an Windows Envioronment.

Program Requirments/ User Inputs:
		Once the program is executed(see below for instructions), the user will be prompted to type in the file name that contains the data.  The makefile has been provided but is not necessary as the executable file is ready to use.  

Text Format : 
		This program is intended to read the format that has been provided by the test.data.txt provided by the professor.  If the text file is not in the same directory or the text input is not as specified, then the program will fail. 

		Example Format : 
				(#numberofstates  #numberofcolors
					(state_number neighbour_list)
					(state_number neighbour_list)
					.
					.
					.
				) 

Relevant Makefile Commands and Execution (For UNIX System - Linux/Mac) 

		They are many relevant commands that can be used due to the inclusion of a makefile when compiling Assignment 1. The following compiling linux commands can be used to compile and build Assignment 1, as well as clean and remove the older files decrypted tweets. The first step is to move into the directory that Assignment 1 can be found on our terminal.

			
	1. Compiling Assignment 1: To use Assignment 2, the user must compile Assignment 1 on their UNIX terminal using the following command:

	   											Terminal Command:   	     $ make assign1                or            $ make all 

	2. Execution: 

		(a) After compilation, to run Assignment 2, you can execute this program by typing into terminal connected to the directory where the executable file is located by

     			Terminal Command:          $ ./assign2

      
       	(c) After the program is started, the user will be prompted in entering the text file name in the format : filename.txt. Please note that the file must be in the same directory as the program to ensure that success. 


Thank you!

	

				



