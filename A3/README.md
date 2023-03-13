# COSC 315 ASSIGNMENT 3 - Producer Consumer Problem

## Part 1 - Java Implementation

### Build Instructions:

Import the provided .java files into IDE of your choice. Execute A3.java to run the program. Use the IDE to terminate when satisfied.

The program will prompt you for the values for number of servant threads, the maximum duration of a request and how long the producer sleeps before producing new request. 

The maximum size of the buffer is set to 5 inside the main function in A3. In order to change it you must edit the source code. Simply modify the value of global variable buffer_size.

## Part 2 - C Implementation

### Build Instructions:

On your Linux terminal or inside your Docker container, type the following into the terminal

```gcc A3.c -lpthread -o A3 && ./A3 number_of_servant_threads maximum_duration_of_request sleep_time_of_producer```

where number_of_servant_threads, maximum_duration_of_request, sleep_time_of_producer are the argument values.

When satisfied with the execution, manually kill the process.
If you wish to modify the size of the buffer, you must edit the global variable in the source code ```SIZE```.

