//
//Author:- Sharva Thakur
//Project 5 
//




#include "pqueue.h"
#include "list.h"
#include <iostream>
#include <string>
#include <fstream>


using namespace std;


int main(){
	
	

	
	List S;
	pq_init(S);
	
	
	
	
	pq_enqueue(S, 66 , 44);
	pq_enqueue(S, 5 , 23);
	pq_enqueue(S, 6 , 22);
	pq_enqueue(S, 54 , 94);
	pq_enqueue(S, 632 , 43);
	
	int s = pq_front(S);
	cout << s << endl; 
	
	List Z = pq_duplicate(S); 
	
	pq_print(S); 
	
	pq_nudge(S, 54);// definitely an invalid position
	pq_nudge(S, 5);
	try
 {
 pq_nudge(S, 888);// definitely an invalid position
 cout << "**Error: no exception was thrown, why not?!" << endl;
 }
 catch (invalid_argument& e)
 {
 cout << "Correct, retrieve_from_list failed, msg=" << e.what() << endl;
 }
 catch (...)
 {
 cout << "**Error: wrong type of exception was thrown?!" << endl;
 }
	
	pq_print(S);
	pq_dequeue(S);
	
	cout << "Z"; 
	pq_print(Z);
	
	pq_print(S); 

	
	pq_clear(S);

	return 0; 
}
	
	
	