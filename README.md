# CPU-Scheduler-Simulator-C-
CPU simulator to mimic scheduling process in Operating System

Step 1.
Open the file Simulator
Step 2
Run the file
Step 3
Enter the time for which simulator is to be used
Enter the Scheduling Algo(fcfs or srtf)
FCFS: First Come First Serve
SRTF: Shortest remaining time first
Step 4
The Simulation runs.
Process.txt and Status.txt files are created in the same folder.

The simulator contains 5 classes:
1> Process 
	The data members of this class store process id, arrival time in the ready queue,
	CPU burst time, completion time, turn around time, waiting time, and response time. The member
	functions of this class assign values to the data members and prints them. A constructor
	is also used.
	Member function "initializing" is present to initialize the process 

2> Process_creator
	Created 200 processes dynamically.
	Assigns all process arrival and burst time randomly.

3> Scheduler
	Runs SRTF and FCFS using appropriate algorithms.
	Maintains a ready queue and a running queue for the same
	I/O file handling is also implemented
	
4> Simulator
	Creates an simulator object 
	Creates status.txt and process.txt

Main function asks for simulation time and desired algorithm

