Sonal Unadkat 	
Assignment 3				
301110334
sunadkat@sfu.ca
CMPT 310  D100
Instructor: James Delgrande

GRADING NOTES: Please do not double click on the executable, please grade on the terminal by running on a LINUX/UNIX(MAC OKAY) ENVIRONMENT
		

				Terminal : 				./assign3


 
		Please ensure that the text file to evaluate is in the same directory. 

Thank you



Assignment 1 Files Included in submit.zip
	assignment3.cpp											source code
	README-CMPT310ASSIGN3.txt
	Assignment1Report.pdf

	File : UNIX 											executable file for Linux/Mac Systems
		makefile (for UNIX compiling only)					// provided but not needed, as executable file has bee provided. 	
		assign1.exe
      

About:
		Assignment 3 is a program that is intended to take in a file, that the Knowledge Base Agent can read it, that will specify the goal query and information for the KB can use to test for entailment. 
Source Code : 
		The source code has been written in C++ .  It is intended it run on UNIX/LINUX machines, and will not work on an Windowns Envioronment.

Program Requirments/ User Inputs:
		Once the program is executed(see below for instructions), the user will be prompted to type in the file name that contains the data.  The makefile has been provided but is not necessary as the executable file is ready to use.  

Text Format : 
		This program is intended to read the format that has been provided by the text provided by the professor.  If the text file is not in the same directory or the text input is not as specified, then the program will fail. 

		Text Format : 
				Goal Query
				Relevant Queries and Facts 
					.
					.
					.
		Query Format
		Query : q ? j ? g  
			- Correct format should be : g q j. 
			- Atoms must have a space between them. 

Relevant Makefile Commands and Execution (For UNIX System - Linux/Mac) 

		They are many relevant commands that can be used due to the inclusion of a makefile when compiling Asssignment 1. The following compiling linux commands can be used to compile and build Asssignment 1, as well as clean and remove the older files decrypted tweets. The first step is to move into the directory that Asssignment 1 can be found on our terminal.

			
	1. Compiling Asssignment 3: To use Asssignment 3, the user must compile Asssignment 1 on their UNIX terminal using the following command:

	   											Terminal Command:   	     $ make assign3               or            $ make all 

	2. Execution: 

		(a) After compilation, to run Asssignment 2, you can execute this program by typing into terminal connected to the directory where the executable file is located by

       											Terminal Command:          $ ./assign3

       	(c) After the program is started, the user will be prompted in entering the text file name in the format : filename.txt. Please note that the file must be in the same directory as the program to ensure that success. 


Thank you!

	

				



