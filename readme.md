Run program using make in terminal.

Make commands:
	clean: removes all .o files and main.exe executable

	main.exe: links libraries and objects to make executable

	run: executes the main.exe executable



*driver.cpp stores the main method for running the application 
*PGMFileprocessor.h stores the method declarations for the PGMFileprocessor.cpp file
*PGMFileprocessor.cpp stores the implementation code for the application
*ConnectedComponent.h stores the method declarations for the ConnectedComponent.cpp file
*ConnectedComponent.cpp is helper class that stores the implementation code for the methods declared in ConnectedComponent.h file

note: use a threshold of 178 on chess.pgm image to obtain the exact same black and white image as was provided in vula resources

-example of execution of program:
    make clean
    make
    make run
    ./main -t 200 -p chess.pgm

