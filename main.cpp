/*main.cpp*/
//
// Author: Sharva Thakur
//
// An intro to ClassReg class, and project 06.
// 
// This project is an code which implements students into their classes
// There are 5 classes CS11 CS141 CS151 CS211 CS251
// This code adds students into the classes of their choice and if the class is full they are added to the waitlist 
// If the class does not exist then there is an error message
//
#include <iostream>
#include <string>
#include "classreg.h"
#include <fstream>

using namespace std;


//
//enroll
//
//This function takes input as ClassReg and istream
//then inputs the name capacity and enrolls students into the class and also wait lists the students waiting for the classreg
//
//
void enroll(ClassReg &A, istream& infile){
	
	string name;
	int capacity;
	
	infile >> name; 
	infile >> capacity;
	
	A.setName(name); 
	A.setCapacity(capacity); 
	
	string i; 
	infile >> i; 
	
	while(i != "#"){
		A.enrollStudent(i);
		infile >> i; 
	}
	
	string j; 
	int s; 
	infile >> j; 
	
	while(j != "#"){
		infile >> s;
		A.waitlistStudent(j, s); 
		infile >> j; 
		
	}
	
}


//
//sortbyname
//
//This takes input as ClassReg
//Then inputs the net id of the students into an array of string 
//Then sorts through the array by name and return array of string 
//
string* sortbyname(ClassReg A){
	
	string* T;
	T = new string[A.numEnrolled()]; 
	
	for (int s = 0; s < A.numEnrolled(); s ++){
		T[s] =  A.retrieveEnrolledStudent(s);
	}
		
	
	for (int i = 0; i < A.numEnrolled()-1; i++)
   {
      int minIndex = i; 
      for (int j = i+1; j < A.numEnrolled() ; j++){
         if ( T[j] <  T[minIndex])
         {
            minIndex = j;
         }
		  
       }
		
		string temp = T[i];
		T[i] = T[minIndex];
		T[minIndex] = temp; 
		}
	return T;
}



//
//help
//
//This function prints all the available commands
//
void help(){
	cout << "stats" << endl; 
	cout <<"list class" << endl;
	cout <<"increase class capacity" << endl;
	cout <<"enroll class netid" << endl;
	cout <<"waitlist class netid priority" << endl;
	cout <<"process filename"<< endl;
	cout <<"output filename" << endl;
	cout <<"quit" << endl;
}


//
//stats
//
//This function prints the all the class names and their number of students enrolled and waitlisted
//
void stats(ClassReg* classes){
	for(int i = 0; i <5 ; i++){
		cout << classes[i].getName() << ": enrolled=" << classes[i].numEnrolled() << ", waitlisted=" << classes[i].numWaitlisted() << endl; 
	}
}


//
//listclass
//
//This function inputs Array of ClassReg and istream 
//Then loops through the array of ClassReg to find listed class
//Once the class is found this prints the class name, capacity, students enrolled in alphabetical order and the students waitlisted
//if the class name is invalid it prints "**Invalid class name, try again..."
//
void listclass(ClassReg* classes, istream& input){
	string name; 
	// taking the input of class name 
	input >> name; 
	bool var = false;
	//loop to find listed class
	for(int i = 0; i <5 ; i++){
		if(classes[i].getName() == name){
			//printing name
			cout << classes[i].getName() << endl; 
			
			//printing capacity
			cout << "Capacity: " <<  classes[i].getCapacity() << endl; 
			
			
			//printing all enrolled students in alphabetical order
			int a = classes[i].numEnrolled();
			cout << "Enrolled (" << a << "): ";
			string* sorted = sortbyname(classes[i]); 
			for(int j = 0; j < a; j++){
				cout << sorted[j] << " "; 
			}
			cout << endl; 
			delete[] sorted; 
			
			//printing all waitlisted students in order of their prio
			a = classes[i].numWaitlisted();
			cout << "Waitlisted (" << a << "): ";

			for(int j = 0; j < a; j++){
				string name;
				int priority = 0; 
				classes[i].retrieveWaitlistedStudent(j, name, priority);

				cout << name << " (" << priority << ") ";  
			}
			cout << endl ;
			var = true;
		}
	}
	if(var == false){
		cout << "**Invalid class name, try again..." << endl; 
	}	
}

//
// increaseCapacity 
// 
// This function takes input as an array of ClassReg and istream
// First this function loops through the array of ClassReg to find the desired class
// Then this checks if the class capacity is more than the new capacity
// if the class capacity is more than new capacity an error message is outputted "**Error, cannot decrease class capacity, ignored..."
// if the class capaity is same as the newcapacity then do changes are made
// if the class capacity is less then the newcapacity the class capacity is changed 
// IF the class is not found then an error message is outputted "**Invalid class name, try again..."
//
void incraeseCapacity(ClassReg* classes, istream& input){
	string name; 
	int newcapacity = 0; 
			
	input >> name;
	input >> newcapacity; 
			
	bool A = false; 
			
	for(int i = 0; i < 5; i++){
		//checking if class capacity is less than equal to the newcapacity
		if(classes[i].getName() == name){
					
			if(classes[i].getCapacity() <= newcapacity){
						
				classes[i].setCapacity(newcapacity);
						
				cout << classes[i].getName() << endl;  
				cout << "Capacity: " << classes[i].getCapacity() << endl; 
						
			}
			else{
				cout << "**Error, cannot decrease class capacity, ignored..." << endl; 
			}
			A = true;
		}
	}
	if(A == false){
		cout << "**Invalid class name, try again..." << endl; 
	}	
}



//
//enrollNetid
//
// This function takes input as an array of ClassReg and istream
// First this function loops through the array of ClassReg to find the desired class
// When the desired class is found this check wheter the student exits in the class
// if yes then no changes are made just the program tells that the student is enrolled
// if the student is not in the class the function finds if there is space in the class
// if there is no space the student is waitlisted
// if there is space the student is enrolled
// if the class is not found then an error message is outputted "**Invalid class name, try again..."
//
void enrollNetid(ClassReg* classes, istream& input){
	string class_name, student; 
	input >> class_name;
	input >> student; 
	
	bool A = true; 
	
	
	
	for(int i = 0; i < 5; i++){
		if(classes[i].getName() == class_name){
			
			//checking if the student enrolled in the class
			int j = classes[i].searchEnrolled(student); 
			if (j != -1){
				cout << "Student '" << student<< "' enrolled in " << classes[i].getName() <<  endl; 
			}
			else if(classes[i].getCapacity () > classes[i].numEnrolled ()){
				
				
				//checking is in the waitlist if yes then the student gets deleted
				int k = classes[i].searchWaitlisted(student);
				if (k != -1){
					classes[i].removeWaitlistedStudent(k);
				}
				
				//enrolls the students 
				classes[i].enrollStudent(student);
				cout << "Student '" << student<< "' enrolled in " << classes[i].getName() <<  endl; 
			}
			else{
				
				int priority = 0; 
				if(classes[i].numWaitlisted() == 0){
					priority = 1; 
				}
				else{
					string name_1; 
					classes[i].retrieveWaitlistedStudent(classes[i].numWaitlisted() - 1, name_1, priority); 
				}
				
				if (classes[i].searchWaitlisted(student) == -1){
					classes[i].waitlistStudent(student, priority);
					
				}
				cout << "Class full, '" << student << "' waitlisted for " << classes[i].getName() << endl;
			}
			A = false; 
		}
	}
	
	if (A == true){
		cout << "**Invalid class name, try again..." << endl; 
	}
}


//
// This function takes input as an array of ClassReg and istream
// First this function loops through the array of ClassReg to find the desired class
// When the desired class is found this check wheter the student exits in the class
// if the student is not enrolled in the class then the student is waitlisted
// if the student already exits in waiting list then the position is readjusted according to the priority
// if the studet exits in enrolled then this outputs that the student exits in the class
// if the class is not found then an error message is outputted "**Invalid class name, try again..."
//
void AddToWaitlist(ClassReg* classes, istream& input){
	string class_name, student; 
	input >> class_name;
	input >> student;
	int priority = 0; 
	
	bool t = false;
	input >> priority;
		for(int i = 0; i < 5; i++){
			
			if(classes[i].getName() == class_name){
				//checking if the student exists in the class
				if(classes[i].searchEnrolled(student) == -1){
					classes[i].waitlistStudent(student, priority);
					cout << "Student '" << student << "' waitlisted for " << classes[i].getName() << endl; 
				}
				else{
					cout << "Student '" << student << "' enrolled in " << classes[i].getName() << endl; 
				}
				t = true; 
			}
		}
	if (t == false){
		cout << "**Invalid class name, try again..." << endl; 
	}
}


//
//output_com
//
// This function takes input as an array of ClassReg and istream
// First this function asks the user for a filename 
// Then opens the file if the file doesnot exits it makes a new file
// Then clears the file 
// And outputs the classes, capacity , enrolled and waitlisted in the format as the original file
// Then closes the file
//
void output_com(ClassReg* classes, istream& input){
	string filename_1; 
	input >> filename_1;
	
	//opens the file
	ofstream outputFile;
	outputFile.open(filename_1);
			
	outputFile.clear();
	
	for(int i =0; i <5 ; i++){
		
		
		outputFile << classes[i].getName() << endl; 
		outputFile << classes[i].getCapacity() << endl; 
		
		int n = 0; 
		
		while (n < classes[i].numEnrolled()){
			string s = classes[i].retrieveEnrolledStudent(n);
			outputFile << s << " " ;
			n++;
		}
		outputFile << "#" << endl; 
		
		int j = 0;
		while (j < classes[i].numWaitlisted()){
			string s;
			int t = 0; 
			classes[i].retrieveWaitlistedStudent(j, s, t);
			outputFile << s << " " << t << " ";
			j++;
		}
		outputFile << "#" << endl; 
	}
	cout << "Enrollment data output to '" << filename_1 << "'" << endl; 
	outputFile.close();
}

//
//processcom
//
//This function takes input as istream, array of ClassReg and a bool
//if the bool is true this asks the user for input
//if the bool is false this uses the command file mentioned  as inputs
//
void processcom(istream& input, ClassReg* classes,bool a ){
	
	
	if(a == true){
		cout << "Enter a command (help for more info, quit to stop)>" << endl; 
	}
	
	string command;
	
	
	input >> command; 
	

	while (command != "quit" && command != "q"){
		
		if(command == "help" || command == "h" ){//help command 
			help(); 
		}
		else if(command == "stats" || command == "s"){//stats command
			stats(classes); 
		}
		else if(command == "list" || command == "l"){//list command
			listclass(classes, input);
		}
		else if(command == "i" || command == "increase"){//increaseCapacity command
			incraeseCapacity(classes,input);
		}
		else if(command == "e" || command == "enroll"){// enroll net id command
			enrollNetid (classes,input);
		}
		else if(command == "w" || command == "waitlist"){// waitlist students command
			AddToWaitlist(classes,input); 
		} 
		//this command opens the file name from input
		//if the filename is incorrect it outputs "** Error, unable to open enrollments file '" 
		//if the filename is correct this again calls the processcom function with the bool value as false
		else if(command == "p" || command == "process"){
			string filename_1; 
			input >> filename_1; 
			
			ifstream inputfile;
			inputfile.open(filename_1);
			if (!inputfile.good()) // file couldn't be opened:
			{
			  cout << "** Error, unable to open couldn file '" << filename_1  << "'" << endl; 
			   
			}
			else{
				cout << "**Processing commands from '" << filename_1 << "'" << endl;
				
				bool s = false;

				processcom(inputfile,classes,s );

				cout << "**Done processing '" << filename_1 << "'" << endl; 
			}
		}
		else if(command == "o" || command == "output"){//output command
			
			output_com(classes,input); 
		}
		else{
			cout << "**Invalid command, please try again..." << endl; 
		}
		
		
		if(a == true){
			cout << endl;
			cout << "Enter a command (help for more info, quit to stop)>" << endl; 
		}
		input >> command;
	}
	if (a == true){
		cout << "**Done**" << endl;
	}
}


//main 
int main(){
	cout << "**CS Enrollment System**" << endl; 
	cout << "Enter enrollments filename>" << endl; 
	string filename;
	cin >> filename;
	
	
	ifstream infile;
    infile.open(filename);
	
	if (!infile.good()) // file couldn't be opened:
    {
      cout << "** Error, unable to open enrollments file '" << filename << "'" << endl; 
	  return 0; 
    }
	 
	
	ClassReg classes[5];
	
	int i = 0; 
	while (i < 5){
		enroll(classes[i],infile);  
		i++; 
	}
	cout << endl; 
	bool a = true; 
	 
	processcom(cin, classes,a);
	
	
	
	return 0;
}
	
	
	