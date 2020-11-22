#include<iostream>
#include <fstream>
#include<iomanip>
#include <cstdlib>
#include<bits/stdc++.h> 
using namespace std;

/*************************Pinaki**Das*************************/
/*
The data members of this class should store process id, arrival time in the ready queue,
CPU burst time, completion time, turn around time, waiting time, and response time. The member
functions of this class should assign values to the data members and print them. A constructor
should also be used.
*/
class Process{
	public:
		int CT;//COMPLETION TIME
		int AT;//ARRIVAL TIME of the process 
		int BT;//Burst Time
		int Turn_Around_Time;//Turn Around Time
		int Response_Time;
		int wait_time;//WAIT TIME
		int pId;
		int executed_before;  //to indicate if the process has been executed_before completely . -1 for executed_before.int remaining_time;
		
		Process(){
			executed_before=0;
			pId=0;
			AT=0;
			Turn_Around_Time=0;
			BT=0;
			Response_Time=-1;
			wait_time=0;
			CT=0;
			cout << "process object created" << endl;
		}
		//Initializing arrival time , burst time and Pid of each process 
		void initializing(int pId,float AT, float BT){
			this->AT=AT;
			this->BT=BT;
			this->pId=pId;
			
		}

		/*function to set completion time
		calculate turnaround time = completion time - arrival time
		calculate waiting time = turnaroundtime - burst time
		*/
		void completion(float CT=0){
			this->CT=CT;
			Turn_Around_Time=CT-AT;
			wait_time=Turn_Around_Time-BT;
		}
		


		// function to calculate response time
		void response(int t){
			if(Response_Time==-1)Response_Time=t-AT;
		}
};


/*
This class will create an array of processes and assign a random arrival time
and burst time to each process. Data members, constructor and member functions can be written
accordingly.
*/
class Process_Creator{
	private:
		float AT;
		float BT;
		
	public:


		Process* arr = new Process[200];
		//class type pointer array(A pointer to a C++ class) 
		Process_Creator(){
		for(int i=0;i<200;i++){
			AT=rand()%200+1;//RANDOM ARR TIME
			BT=rand()%5+1;//RANDOM bURST tIME
			arr[i].initializing(i,AT,BT);//INITIALIZING the process
		}
		cout << "Processes initialised"<< endl;
	}
};



/*
This class will implement the scheduling algorithm. The class will maintain a ready
queue of fixed capacity. The ready queue is a queue in which only enqueue and dequeue operations
can be done. The process to be enqueued or dequeued will depend on the scheduling algorithm. The
queue should be implemented as a class where enqueue() and dequeue() are its member functions.
Since, the size of the queue is limited, possibilities of swap in and swap out of a process is there.
Students have to implement three scheduling algorithms, viz., First Come First Serve (FCFS),
Shortest Remaining Time First (SRTF), and Round Robin.*/
class Scheduler{
	private:
		int runQ[50]={0}; //running queue 
		int readyQ[200]={0};  //processes id which are ready to get executed
		int top=-1;  // indicate the top element of readyQ .just like front in runQ.
		int front;  //the top element in runQ
		int start_exec_time=-1;  //storeS the time when the runnning process started its execution 
		int min_burst=INT_MAX;   //minimum burst time required in SRTF 
		int min_burst_index=-1;  //index of minimum burst time process present in the readyQ
		
	public:
		ofstream out;
		Process_Creator myProcess;
		Scheduler(){
			cout << "scheduler running" << endl;
			front=-1;	
		}

		/*
		A file named as status.txt which will print a table. For each millisecond, the file will show the
		process id of the processes arrived in the system, running by the processor and exiting from the
		system. The number of rows in the table will depend on the number of times the ‘for’ loop is
		running, i.e., the number of milliseconds in the simulation time. However, if in a particular
		millisecond, no process arrived or exited and the process being run by the processor is the same as
		that of previous
		millisecond then the current millisecond can be skipped from printing in the table.
		*/
		int enqueue(int pId,int t){
			if(front==49)return 0;
			else{
				cout<< "enqueued" << endl;
				front++;
				runQ[front]=pId;
				if(front==0){
					start_exec_time=t;
					out.open("status.txt",ios_base::app);
					out << setw(20) << t;
					out << setw(20) << myProcess.arr[runQ[0]].pId;
					out << setw(20) << "arrived";
					out << endl;
					out.close();
					myProcess.arr[runQ[0]].response(t);
				}
				return 1;
			}
		}
		/*
		A file named as processes.txt will be created which will 
		contain a table
		*/
		int dequeue(int t){
			if(front==-1)return 0;
			else{
				cout << "dequeued" << endl;
				
				int p_executed=runQ[0];
				myProcess.arr[runQ[0]].completion(t);
				start_exec_time=t;
				for(int i=0;i<front;i++)runQ[i]=runQ[i+1];
				runQ[front]=0;
				front--;
				out.open("Status.txt",ios_base::app);
				out << setw(20) << t;
				out << setw(20) << myProcess.arr[p_executed].pId;
				out << setw(20) << "Exit";
				out << endl;
				if(front!=-1){
					out << setw(20) << t;
					out << setw(20) << myProcess.arr[runQ[0]].pId;
					out << setw(20) << "Arrived";
					out << endl;
					out.close();
					myProcess.arr[runQ[0]].response(t);
				}		
				myProcess.arr[p_executed].executed_before=-1;
				return 1;
			}
		}
		//fCFS Algorith start
		int FCFS(int t){
				cout << t<<"Millisecond Number" << endl;
				for(int i=0;i<200;i++){
					if(myProcess.arr[i].executed_before!=-1 && myProcess.arr[i].AT==t){
						top++;
						readyQ[top]=myProcess.arr[i].pId;
					}
				}
				
				if(front!=-1 && t-start_exec_time==myProcess.arr[runQ[0]].BT){
					if(dequeue(t)==0){}
				}else if(front!=-1){
					out.open("Status.txt",ios_base::app);
					out << setw(20) << t;
					out << setw(20) << myProcess.arr[runQ[0]].pId;
					out << setw(20) << "Running";
					out << endl;
					out.close();
				}
				if(top!=-1 && enqueue(readyQ[0],t)){
					for(int j=0;j<top;j++){
						readyQ[j]=readyQ[j+1];
					}
					readyQ[top]=0;
					top--;
				}
				
				return 0;
			}
		//SRTF Algorithm Start
		int SRTF(int t){
			cout << t<<" Millisecond Number" << endl;
			int new_process=0;
			for(int i=0;i<200;i++){
				if(myProcess.arr[i].executed_before!=-1 && myProcess.arr[i].AT==t){
					new_process=1;
					top++;
					readyQ[top]=myProcess.arr[i].pId;
				}
			}
			if(new_process==1){
				for(int i=0;i<=top;i++){
					if(myProcess.arr[readyQ[i]].BT<min_burst){
						min_burst=myProcess.arr[readyQ[i]].BT;
						min_burst_index=i;
					}
				}
			}
			
			
			
			if(front!=-1 && t-start_exec_time==myProcess.arr[runQ[0]].BT){
				dequeue(t);
			}else if(front!=-1){
				out.open("Status.txt",ios_base::app);
				out << setw(20) << t;
				out << setw(20) << myProcess.arr[runQ[0]].pId;
				out << setw(20) << "Running";
				out << endl;
				out.close();
			}
			
			if(top!=-1 && enqueue(readyQ[min_burst_index],t)){
				for(int i=min_burst_index;i<top;i++)readyQ[i]=readyQ[i+1];
				readyQ[top]=0;
				top--;
				min_burst_index=-1;
				min_burst=INT_MAX;
				for(int i=0;i<=top;i++){
					if(myProcess.arr[readyQ[i]].BT<min_burst){
						min_burst=myProcess.arr[readyQ[i]].BT;
						min_burst_index=i;
					}
				}
			}
			return 0;
		}
};

/*
This class will start the simulation. If the simulation time is 1 second and arrival
time and burst time of a process are in terms of milliseconds then the class will run a ‘for’ loop from
t=0 to 1000. At each iteration, the class will execute all the necessary functions and capture the
required values.*/

class Simulator{
	Scheduler S;
	public:
		int timer=0,end=0;
		 
		void simulating(int sim_time,string sch_name){
			
			ofstream outf;
			outf.open("Status.txt");
			outf << setw(20) << "Millisecond" ;
			outf << setw(20) << "Process Id" ;
			outf << setw(20) << "Status" ;
			outf << endl;
			outf.close();
			for(timer=1;timer<=sim_time;timer++){
				if(sch_name=="fcfs")end=S.FCFS(timer);
				else if(sch_name=="srtf")end=S.SRTF(timer);
				if(end==1)break;
			}
			
			outf.open("Processes.txt");
			outf << setw(20) << "Process Id" ;
			outf << setw(20) << "Arrival Time";
			outf << setw(20) << "Burst Time";
			outf << setw(20) << "Comp Time";
			outf << setw(20) << "  Turnaround Time";
			outf << setw(20) << "Waiting Time";
			outf << setw(20) << "Response Time";
			outf << endl;
			for(int i=0;i<200;i++){
				outf << setw(20) << S.myProcess.arr[i].pId ;
				outf << setw(20) << S.myProcess.arr[i].AT;
				outf << setw(20) << S.myProcess.arr[i].BT;
				outf << setw(20) << S.myProcess.arr[i].CT;
				outf << setw(20) << S.myProcess.arr[i].Turn_Around_Time;
				outf << setw(20) << S.myProcess.arr[i].wait_time;
				outf << setw(20) << S.myProcess.arr[i].Response_Time;
				outf << endl;
			}
			outf.close();
		}
};


/*
The main() function should take the following input from the user: (i) Simulation time (ii) Name of
scheduling algorithm (iii) Time quantum in case of Round Robin.*/
int main(){
	int simulation_time;
	string myAlgo;
	int preempt_time;
	cout << "Enter Simulation time in Milli" << endl;
	cin >> simulation_time;
	cin.ignore();
	cout << "Enter the name of Algo" << endl;
	cout << "1. FCFS(First Come First Serve)" << endl;
	cout << "2. SRTF (Shortest Remaining Time First) " << endl;
	cout << "Enter FCFS or SRTF " << endl;
	getline(cin,myAlgo);
	transform(myAlgo.begin(), myAlgo.end(), myAlgo.begin(), ::tolower);
	
	if(myAlgo=="fcfs" || myAlgo=="first come first serve"){
		Simulator sim;
		sim.simulating(simulation_time,"fcfs");
	}else if(myAlgo=="srtf" || myAlgo=="shortest remainig time first"){
		Simulator sim;
		sim.simulating(simulation_time,"srtf");
	}
}


