//
//Author:- Sharva Thakur
//Project 5 
//




#include "list.h"
#include <iostream>
#include <string>
#include <fstream>
#include <exception>
#include <stdexcept>

//
// Functions:
//

// 
// init_list
//
// Initializes list to empty; must be called before list can 
// be used with other functions.
//
void init_list(List& L){
	L.Head = nullptr;
	L.Count = 0; 
}


//
// print_list
//
// Outputs "List: " followed by each data element and a space. Output
// is directed to the console. The format of each data element is 
// (field1,field2,...), e.g. (ID,Priority).
//
void print_list(List L){
	Node* cur = L.Head; 
	
	
	
	cout << "List: ";
	
	if(L.Count!=0){
		Node* prev = nullptr; 
		prev = cur;
		cur = cur->Next;
		while(cur != nullptr){

			cout << "(" << prev->Data.ID<< "," << prev->Data.Priority << ") ";

			prev = prev->Next; 
		
			cur = cur->Next;
		}
	
		cout << "(" << prev->Data.ID<< "," << prev->Data.Priority << ") " << endl; 
	}
	else{
		cout << endl;
	}
	
}


//
// push_back_list
//
// Pushes the data onto the end of the list.
//
void push_back_list(List& L, NodeData d){
	
	Node* cur = L.Head; 
	 
	
	Node* newN = new Node();
		newN->Data = d;
		newN->Next = nullptr;
	
	
	if(L.Count == 0){
		L.Head = newN; 
		L.Count++;
		
	}
	else{
		Node* prev = nullptr;
		while(cur!=nullptr){
			prev = cur;

			cur = cur->Next; 

		}

		prev->Next = newN; 

		L.Count++; 
	}
	
	
	
	
}



//
// push_front_list
//
// Pushes the data onto the front of the list.
//
void push_front_list(List& L, NodeData d){
	Node* newN = new Node();
	newN->Data = d;
	newN->Next = L.Head; 
	
	L.Head = newN; 
	L.Count++; 
	
	
}


//
// free_list
//
// Deletes all nodes from the list, frees the memory, and resets
// the list to empty.
//
void free_list(List& L){
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
// search_list
//
// Search the list for the first occurrence of the given ID. If found,
// its position in the list is returned; positions are 0-based,
// meaning the first node is position 0. If not found, -1 is
// returned.
//
int search_list(List L, int ID){
	Node* cur = L.Head;
   
	for(int i = 0; i < L.Count; i++){
      
       int a = cur->Data.ID;
       if(a == ID){
         
          return i;
	   }
	   cur = cur->Next;
    }
   
    return -1 ;
}






//
// retrieve_from_list
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("retrieve_from_list: invalid position");
//

NodeData retrieve_from_list(List L, int pos){
	int i = 0;
   
   Node* cur = L.Head; 
   
   
   if(pos<0 || pos>=L.Count){
      throw invalid_argument("retrieve_from_list: invalid position");
   }
   
	
	if(pos == 0){
		NodeData g = cur->Data;
		return g;
	}
	
	
   while(i<pos){
      cur = cur->Next;
      i++;
   }
   
   NodeData g = cur->Data;
   
   return g; 
}


//
// remove_from_list
//
// Removes and frees the node at the given position, returning 
// the node's data. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("remove_from_list: invalid position");
//
NodeData remove_from_list(List& L, int pos){
	
	int i = 0;
   
   Node* cur = L.Head; 
   Node* prev = nullptr; 
   
   if(pos<0 || pos>(L.Count - 1)){
      throw invalid_argument("remove_from_list: invalid position");
   }
   else{
	   if(pos == 0){
		  NodeData d = cur->Data;
		  prev = cur; 

		   L.Head = cur->Next; 
		   L.Count--; 
		  delete prev;
		   return d; 
	   }
	   
	   while(i<pos){
		   prev = cur; 
		  cur = cur->Next;
		  i++;
	   }
	   
		NodeData g = cur->Data; 
		Node* temp = cur;
		prev->Next = cur->Next; 
		delete temp;
		L.Count--; 


	   return g;
   }
}


