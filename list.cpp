/*list.cpp*/

//
//Name = Sharva Thakur
//Project 6 part 2
//


//
// Author: Prof. Hummel, U. of I. Chicago, Spring 2021
// 
// Implements a one-way linked-list with optimized insertion at
// head and tail of list. The nodes contain 2 data values, a string
// and an integer.
//

#include <iostream>
#include <string>
#include <exception>
#include <stdexcept>

#include "list.h"

using namespace std;



//
// private member functions:
//

//
// inits this list then makes deep copy of other
//
// Time complexity: O(N)
//
void List::initAndDeepCopy(const List& other)
{
   //
   // TODO: init this list, then make copy of other
   //
	this->Head = nullptr;
    this->Tail = nullptr;
    this->Count = 0;
	
	//this->Count= other.Count;
	Node* cur = other.Head;
	while(cur != nullptr){
        this->push_back(cur->Data.Value1 , cur->Data.Value2); 
      
        cur = cur->Next; 
    }
// 	this->Tail = cur; 
}


// 
// free the nodes in the list and resets to empty
//
// Time complexity: O(N)
//
void List::freeAndReset()
{
   //
   // TODO: free this list, then reset to empty
   //
	Node* cur = this->Head; 

	while(cur != nullptr){
		
		Node* temp = cur;
		cur = cur->Next;
		
		delete temp; 
	}
	this->Count = 0; 
	this->Head = nullptr; 
	this->Tail = nullptr; 
}



//
// public member functions:
//

//
// default constructor
//
// Initializes the list to empty.
// 
// Time complexity: O(1)
//
List::List()
{
   this->Head = nullptr;
   this->Tail = nullptr;
   this->Count = 0;
}

//
// copy constructor
//
// Makes a deep copy of the other list into this list.
// 
// Time complexity: O(N)
//
List::List(const List& other)
{
   this->initAndDeepCopy(other);
}

//
// destructor
//
// Frees all memory related to this list, and then resets to empty.
// 
// Time complexity: O(N)
//
List::~List()
{
   this->freeAndReset();
}

//
// assignment operator (e.g. L2 = L;)
//
// Makes a deep copy of the other list into this list; since this
// list already exists, the existing elements of this list are freed
// before the copy is made.
// 
// Time complexity: O(N)
//
List& List::operator=(const List& other)
{
   if (this == &other)  // special case: check for L = L;
      return *this;     // do nothing and just return THIS object back

   //
   // This is different from a copy constructor, because "this" list
   // exists and contains nodes.  So we have to free "this" list before
   // we copy the "other" list:
   //
   this->freeAndReset();
   this->initAndDeepCopy(other);

   return *this;  // done, return THIS object back
}

//
// size
//
// Returns the # of elements in the list.
//
// Time complexity: O(1)
//
int List::size()
{
   //
   // TODO:
   //
	
	int i = this->Count; 
	
    return i;
}

//
// empty
//
// Returns true if empty, false if not.
//
// Time complexity: O(1)
//
bool List::empty()
{
   //
   // TODO:
   //
	if(this->Count !=0 ){
		return false; 
	}
   return true;
}

//
// search
//
// Search the list for the first occurence of the string value.
// If found, its position in the list is returned. Positions are 
// 0-based, meaning the first node is position 0. If the value is
// not found, -1 is returned.
//
// Time complexity: on average O(N)
//
int List::search(string value)
{
   //
   // TODO:
   //
	
	Node* cur = this->Head;
   int i = 0;
	while(cur != nullptr){
      
       string a = cur->Data.Value1;
       if(value == a){
         
          return i;
	   }
	   cur = cur->Next;
		i ++; 
    }
   
    return -1 ;
}

//
// retrieve
//
// Retrieve's the data from node at the given position; the list 
// remains unchanged. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::retrieve: invalid position");
//
// Time complexity: on average O(N)
//
void List::retrieve(int pos, string& value1, int& value2)
{
   if(pos<0 || pos>(this->Count - 1)){
	   throw invalid_argument("List::retrieve: invalid position");
   }
	
	Node* cur = this->Head; 
	
	int i = 0; 
	while(i < pos){
		i++;
		cur = cur->Next; 
	}
	
	value1 = cur->Data.Value1;
	value2 = cur->Data.Value2;
	
}

//
// insert
//
// Inserts the given data in the list such that after
// the insertion, the value is now at the given
// position.
//
// Positions are 0-based, which means a position of 0 
// denotes the data will end up at the head of the list,
// and a position of N (where N = the size of the list)
// denotes the data will end up at the tail of the list.
// If the position is invalid, throws an exception, i.e.
// throw invalid_argument("List::insert: invalid position");
//
// Time complexity: on average O(N)
//
void List::insert(int pos, string value1, int value2)
{
   
	if(pos == 0){
		
		Node* cur = this->Head; 
		Node* newN = new Node(); 
		newN->Data.Value1 = value1; 
		newN->Data.Value2 = value2; 
		newN->Next = cur;
		
		
		this->Head = newN;
		
		
		if(this->Count == 0){
			this->Tail = newN;
		}
		
		this->Count++;
		return; 
	}
	else if(pos == this->Count) {		
		Node* newN = new Node(); 
		newN->Data.Value1 = value1; 
		newN->Data.Value2 = value2; 
		newN->Next = nullptr;
		
		 
		Node* temp = this->Tail;
		Node* last = newN; 
		temp->Next = last; 
		this->Tail = newN;
		this->Count ++; 	
		return; 
	}
	if(pos < 0 || (this->Count-1) < pos ){
       throw invalid_argument("List::insert: invalid position");
    }
	
	Node* newN = new Node(); 
	newN->Data.Value1 = value1; 
	newN->Data.Value2 = value2; 
	newN->Next = nullptr;
	
	
	
		int i =0; 
		Node* cur = this->Head;
		Node* prev = nullptr; 
		while(i < pos){
			i ++; 
			prev = cur;
			cur = cur->Next; 
		}
		prev->Next = newN;
		newN->Next = cur; 
		this->Count ++;

   
}

//
// remove
//
// Removes and deletes the node at the given position; no data is
// returned. Positions are 0-based, meaning the first node
// is position 0. Throws an "invalid_argument" exception if the 
// position is invalid, i.e. 
// throw invalid_argument("List::remove: invalid position");
//
// Time complexity: on average O(N)
//
void List::remove(int pos)
{
   //
   // TODO:
   //
   int i = 0;
   
    Node* cur = this->Head; 
    Node* prev = nullptr; 
   
   if(pos<0 || pos>(this->Count - 1)){
      throw invalid_argument("List::remove: invalid position");
   }
   else{
	   if(pos == 0){
		  NodeData d = cur->Data;
		  prev = cur; 

		   this->Head = cur->Next; 
		   this->Count--; 
		  delete prev;
		   return; 
	   }
	   
	   
	   while(i<pos){
		   prev = cur; 
		  cur = cur->Next;
		  i++;
	   }
	   
	   if(pos == this->Count - 1){
		   this->Count--; 
		   Node* temp = cur;
		   prev->Next = cur->Next; 
		   delete temp;
		   
		   this->Tail = prev; 
		   return; 
		   
	   }
		NodeData g = cur->Data; 
		Node* temp = cur;
		prev->Next = cur->Next; 
		delete temp;
		this->Count--; 

   }
}


//
// front
//
// Returns the data from the first node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::front: empty list");
// 
// Time complexity: O(1)
//
void List::front(string& value1, int& value2)
{
   //
   // TODO:
   //
	if(this->Count == 0){
		throw runtime_error("List::front: empty list");
	}
	else{
		value1 = this->Head->Data.Value1;
		value2 = this->Head->Data.Value2;
	}
}

//
// back
//
// Returns the data from the last node in the list. Throws an 
// exception if the list is empty, i.e.
// throw runtime_error("List::back: empty list");
// 
// Time complexity: O(1)
//
void List::back(string& value1, int& value2)
{
   //
   // TODO:
   //
	
	if(this->Count == 0){
		throw runtime_error("List::back: empty list");
	}
	else{
		value1 = this->Tail->Data.Value1;
		value2 = this->Tail->Data.Value2;
	}
}

//
// push_front
//
// Inserts the given data at the front of the list.
// 
// Time complexity: O(1)
//
void List::push_front(string value1, int value2)
{
   
	Node* newN = new Node(); 
	newN->Data.Value1 = value1; 
	newN->Data.Value2 = value2; 
	newN->Next = this->Head;
	
	if(this->Count == 0){
		this->Head = newN;
		this->Tail = newN; 
		
	}
	else{
		this->Head = newN;
	}
	Count++; 
	
}

//
// push_back
//
// Inserts the given data at the back of the list.
// 
// Time complexity: O(1)
//
void List::push_back(string value1, int value2)
{
	
	
	
   //
   // TODO:
   //
	 Node* newN = new Node(); 
	 newN->Data.Value1 = value1; 
	 newN->Data.Value2 = value2; 
	 newN->Next = nullptr;
	
	if(this->Count == 0){
		this->Head = newN; 
		this->Count ++; 
		this->Tail = newN;
	}
	else{
		Node* temp = this->Tail; 
		Node* last = newN;
		temp->Next = last; 
		this->Tail = newN;
		this->Count ++; 
	}
}
