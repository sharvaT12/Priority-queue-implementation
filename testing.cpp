//
// 
// testing for part 2
//
//
#include <iostream>
#include <string>
#include "list.h"

using namespace std;


int main()
{
    List L;
	
	
	L.insert (0, "apple", 123);
	cout << "1" << endl;
	L.insert (1, "pizza", 789);
	cout << "2" << endl;
	L.insert (1, "banana", 456);
	cout << "3" << endl;
    L.insert (0, "AAA", -123);
	cout << "4" << endl;
    L.insert (4, "ZZZ", 999);
	cout << "5" << endl;
	
	
	
	
	
    return 0;
}