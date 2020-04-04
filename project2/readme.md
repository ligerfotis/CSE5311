# CSE5311 - Assignment 2

### Compiling Information and Instructions to run the code

##### Note: 

    g++ --version
    
outputs `g++ (Ubuntu 5.4.0-6ubuntu1~16.04.12) 5.4.0 20160609`

The code can be compliled running

        g++ main.cpp -o project2.exe

Then run

    ./project2.exe 
e.g. 

    "./project1.exe 

##### Note: if the executable cannot run check for execution permissions

The program should output similarly on the standard output:

    Console Output:
        qsort CPU 0.032693
        set inverses CPU 0.023620
        Scaling Parameter is: 512
        499<-0 adds 821 incremental flow
        499<-73<-0 adds 964 incremental flow
        499<-94<-0 adds 594 incremental flow
        499<-144<-0 adds 613 incremental flow
        499<-158<-0 adds 700 incremental flow
        ...
        499<-53<-347<-0 adds 2 incremental flow
        Scaling Parameter is: 1
        499<-159<-47<-0 adds 1 incremental flow
        499<-4<-84<-0 adds 1 incremental flow
        499<-149<-112<-0 adds 1 incremental flow
        499<-483<-112<-0 adds 1 incremental flow
        499<-138<-121<-0 adds 1 incremental flow
        499<-156<-121<-0 adds 1 incremental flow
        499<-341<-125<-0 adds 1 incremental flow
        499<-77<-130<-0 adds 1 incremental flow
        499<-378<-131<-0 adds 1 incremental flow
        499<-179<-188<-0 adds 1 incremental flow
        499<-14<-197<-0 adds 1 incremental flow
        499<-339<-213<-0 adds 1 incremental flow
        499<-36<-219<-0 adds 1 incremental flow
        460 augmenting paths
        total flow is 113241
        Ford-Fulkerson time 0.159812
