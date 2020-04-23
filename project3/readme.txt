# CSE5311 - Assignment 3

### Compiling Information and Instructions to run the code

##### Note: 

    g++ --version
    
outputs `g++ (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609`

The code can be compliled running

        g++ main.cpp -o project3.exe

Then run

    ./project3.exe <filename>
e.g. 

    ./project3.exe lab3spr20.a.dat

##### Note: if the executable cannot run check for execution permissions

The program should output similarly on the standard output:

    Console Output:
        Filename: lab3spr20.a.dat
        Number of Strings in file is 6
        abcdef
          cdefab
            efabcd  
                  012345
                    234501
                      450123
        Length of SCS 16
