//
//Author:- Sharva Thakur
//Project 5 part 2 
//



#include "list.h"
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>






//
// pq_init
//
// Initializes list to empty; must be called before list can 
// be used with other queue functions.
//
void pq_init(List& L){
	L.Head = nullptr;
	L.Count = 0; 
}

//
// pq_print
// 
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void pq_print(List L){
	Node* cur = L.Head; 
	
	
	
	cout << "List: ";
	
	if(L.Count!=0){
		
		while(cur != nullptr){

			cout << "(" << cur->Data.ID<< "," << cur->Data.Priority << ") ";
		
			cur = cur->Next;
		}
	}
	cout << endl; 
}


//
// pq_front
//
// Returns the ID at the front of the priority queue. Throws 
// an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_front: queue empty");
//
int pq_front(List L){
	Node* cur = L.Head;
	
	if(L.Count == 0){
		throw invalid_argument("pq_front: queue empty");
	}
	else{
		int s = 0; 
		
		s = cur->Data.ID; 
		return s; 
	}
	
	
}

//
// pq_dequeue
//
// Removes the data element at the front of the queue, removing the
// node as well and freeing this memory. Nothing is returned.
// Throws an "invalid_argument" exception if the queue is empty, i.e.
// throw invalid_argument("pq_dequeue: queue empty");
//
void pq_dequeue(List& L){
	Node* cur = L.Head; 
	
	if(L.Count == 0){
		throw invalid_argument("pq_dequeue: queue empty");
	}
	
	L.Head = cur->Next; 
	
	delete cur;
	L.Count --; 
	
}


//
// pq_enqueue
//
// Inserts the given (ID,priority) pair into the queue based on
// the priority, ordered low to high. If elements already exist with
// the same priority, this new element comes after those elements.
// Example: suppose the queue currently contains the following 
// (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to enqueue (79,25) yields the following result:
//
//   (10,19) (84,25) (79,25) (21,50)
//
// If the ID is already in the queue, then the pair is repositioned 
// based on the new priority. For example, suppose the queue is as
// shown above, and we enqueue (84,50). The result is now
//
//   (10,19) (79,25) (21,50) (84,50)
//
void pq_enqueue(List& L, int ID, int priority){
	
	
	int j = search_list(L, ID); 
	
	if(j != -1){
		remove_from_list(L,j);
	}
	
    Node* cur = L.Head;
	Node* temp = new Node();
	temp->Data.ID = ID; 
	temp->Data.Priority = priority; 
	temp->Next = nullptr; 
	
	if(L.Count == 0){
		L.Head = temp;
		L.Count ++; 
		return ; 
	}
	
	int z = 0; 
	 
	
	Node* prev = nullptr; 
	while(cur != nullptr){
		
		int j = cur->Data.Priority; 
		
			
		if(priority < j){
			
			if(z == 0){
				L.Head = temp; 
				temp->Next = cur; 
				L.Count ++; 
			}
			else{
				temp->Next = cur; 
				prev->Next = temp ;
				L.Count++;
			}
			
			break; 
		}
	
		z ++; 
		prev = cur;
		cur = cur->Next; 
	}
	
	if (z == L.Count){
		temp->Next = cur; 
		prev->Next = temp ;
		L.Count++;  	
	}

}

//
// pq_nudge
// 
// Nudges the element with the given ID forward one element in the
// queue. The element takes on the same priority as the element
// that now follows it.  Example: suppose the queue currently contains
// the following (ID,Priority) pairs:
// 
//   (10,19) (84,25) (21,50)
//
// A call to "nudge" 21 forward produces this result:
//
//   (10,19) (21,25) (84,25)
//
// If the ID is already at the front of the queue, nothing happens.
// If the ID is not in the queue, throws "invalid_argument" exception, i.e.
// throw invalid_argument("pq_nudge: ID not found");
//
void pq_nudge(List& L, int ID){
	
	int s = search_list(L, ID); 
	
	if(s == -1){
		throw invalid_argument("pq_nudge: ID not found");
	}
	else if (s != 0){
		Node* cur = L.Head; 
		Node* prev = nullptr; 
		int i = 0; 
		
		
		while(i<s-1){
			prev = cur ;
			cur = cur->Next; 
			i++; 
		}
		
		if(prev == nullptr){
			Node* temp = cur->Next; 
			cur->Next = temp->Next;
			temp->Next = cur; 
			L.Head = temp;  
			temp->Data.Priority = cur->Data.Priority;
			
		}
		else{
			Node* temp = cur->Next; 
			cur->Next = temp->Next;
			temp->Next = cur; 
			prev->Next = temp; 
			temp->Data.Priority = cur->Data.Priority;
		
		}
		
	}

}

//
// pq_clear
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void pq_clear(List& L){
	Node* cur = L.Head; 

	while(cur != nullptr){
		
		Node* temp = cur;
		cur = cur->Next;
		
		delete temp; 
	}
	L.Count = 0; 
	L.Head = nullptr;	
}


//
// pq_duplicate
//
// Makes a complete copy of the given list L and returns this duplicate.
// A "deep" copy is made, meaning all nodes and data are duplicated in 
// the new, returned list.
//
List pq_duplicate(List L){
	List A;
	pq_init(A); 
	Node* cur = L.Head; 
	
	while(cur != nullptr){
        pq_enqueue(A, cur->Data.ID, cur->Data.Priority);
        
        cur = cur->Next;
	}

	return A; 
	
	
}
