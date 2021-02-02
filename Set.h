#pragma once
#include<iostream>
#include<string>
#include"Calculator.h"
using namespace std;


//================================================================================================
// Set class Header
//================================================================================================


class Set : public Calculator
{
private:
    int size;                             // class member variable to store size of array Set
    string* arr;                             // class member array to store values of Set
    int noOfElements;                     // class member to store number of elements of set in the array

    void reduce_size();                   // Reduce allocated memory by half
    void increase_size();                 // Increase allocated memory by twice
    bool isEmpty();                       // return true if the set is empty, else return false
    bool isFull();                        // return true if the set is full. Else return false.

public:
    Set();                                // default constructor
    Set(int size);                        // allocates the memory on heap and check if the size is invalid then set null
    Set(const Set& ref);                  // Copy constructor
    bool insertElement(string value);        /* This function should insert value at the most recent
                                             position. Add necessary checks and increase memory if
                                             required. Returns true if the value is inserted else returns false.*/
    bool removeElement(string value);        /* find the given value and remove the value from set. Decease
                                             the set size (if required). Return true if the value is
                                             removed else return false the value is not present in set. */
    int searchElementPosition(string value); /* if the element is present then return the index of
                                             that element else return -1 */
    bool searchElement(string value);        /* return true if the value is present in the set else
                                             returns false. */
    void displaySet();                    // display the contents of set. (in curly brakets and coma separated)
    Set intersection(Set);              // return the intersection of the sets.
    Set Union(Set);                    // return the union of the sets.
    Set operator+ (Set& first);           // You may call union function in this function.
    Set difference(Set a);                // return the difference of the sets.
    Set operator-(Set& first);            // You may call difference(Set a) function in this function.
    int isSubSet(Set a);                  // return 1 for proper subset, return 2 for improper subset return 0 if not a subset.
    ~Set();                               // destructor
    string& operator[](int);                 // Directly access element in the set. If element does not exist, return -1.
    Set operator=(const Set& a);          // overloading = operator
    void RunObject();
};

