## Instructions to run the code

Note: 

	g++ g++ --version
	
is `g++ (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609`

The code can be compliled running
		g++ main.cpp -std=gnu++11 -o project1.exe

Then run

	./project1.exe <path_to_data_files>/lab1.x.dat

e.g. 

	"./project1.exe ~/project1/lab1.a.dat"

Note: if the executable cannot run check for execution permissions

The program should output on the standard output:

	Console Output:
		Filename: lab1.a.dat
		Matrix LCS length: 6 LSIS LCS length: 6
		7
		8
		9
		8
		7
		9
		-1
		CPU Matrix LCS: 0.000041 sec CPU Matrix LCS: 0.000 sec