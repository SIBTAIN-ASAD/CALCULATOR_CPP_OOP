#include<iostream>
#include<string>
#include<cstdlib>
#include"Set.h"
using namespace std;


//================================================================================================
// Set class Implimentation
//================================================================================================


void Set::reduce_size() // Reduce allocated memory by half
{
    //reducing size to half 
    size = size / 2;
    //copy array to store old values
    string* copy = new string[size];
    //storing old values
    for (int i = 0; i < noOfElements; i++)
    {
        copy[i] = arr[i];
    }

    //deleting the array
    delete[]arr;
    //creating new array with half size
    arr = new string[size];

    //populating array with old data
    for (int i = 0; i < noOfElements; i++)
    {
        arr[i] = copy[i];
    }
    //deleting copy array
    delete[]copy;
}


void Set::increase_size() // Increase allocated memory by twice
{
    //increasing the size variable to double
    this->size = (this->size) * 2;
    //creating array to store old values
    string* copy = new string[this->size];
    //storing old data of array to copy array
    for (int i = 0; i < noOfElements; i++)
    {
        copy[i] = arr[i];
    }

    //deleting old array
    delete[]this->arr;
    //creating new array with double size
    this->arr = new string[this->size];

    //populating array with old data
    for (int i = 0; i < noOfElements; i++)
    {
        arr[i] = copy[i];
    }

    //deleting copy array to release memory
    delete[]copy;

}


bool Set::isEmpty() // return true if the set is empty, else return false
{
    //if number of elements is zero then definantly the set is null or empty
    if (noOfElements == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}


bool Set::isFull() // return true if the set is full. Else return false.
{
    //if number of elements is equal to size then definantly the set is full
    if (noOfElements >= size)
    {
        return true;
    }
    else
    {
        return false;
    }
}


Set::Set() //default constructor
{
    this->size = 10;
    this->noOfElements = 0;
    this->arr = new string[size];
}


Set::Set(int size) // allocates the memory on heap and check if the size is invalid then set null
{
    //check for valid size of array
    if (size > 0)
    {
        this->size = size;
        this->noOfElements = 0;
        this->arr = new string[this->size];
    }
    else //store NULL in case of invalid input
    {
        cout << "\nInvalid size\n";
        this->noOfElements = 0;
        this->arr = NULL;
    }
}


Set::Set(const Set& ref) // Copy constructor
{
    this->size = ref.size;
    this->noOfElements = ref.noOfElements;
    this->arr = new string[size];
    for (int i = 0; i < size; i++)
    {
        this->arr[i] = ref.arr[i];
    }
}



bool Set::insertElement(string value) // This function should insert value at the most recent position.
{
    //as a set have disstict values , it would not insert element
    if (searchElement(value))
    {
        return false;
    }
    //if array is full it would increae the size of array 
    if (isFull())
    {
        increase_size();
    }

    //noOfElement is the most recent position so it would insert the value there
    this->arr[noOfElements] = value;
    //increment in number of element
    this->noOfElements++;
    return true;

}


bool Set::removeElement(string value) // find the given value and remove the value from set.
{
    int position = searchElementPosition(value);
    if (position != -1)
    {
        /* to remove an element we simply place last element at the
           position of that element and reduce the number of elements */
        this->arr[position] = this->arr[noOfElements - 1];
        noOfElements--;

        return true;
    }
    else
    {
        return false;
    }
}


int Set::searchElementPosition(string value) /* if the element is present then return the index of that element else return -1 */
{
    //matching every element of array and return position of it matched
    for (int i = 0; i < noOfElements; i++)
    {
        if (this->arr[i] == value)
        {
            return i;
        }
    }
    //if not matched it would return -1
    return -1;
}


bool Set::searchElement(string value) // return true if the value is present in the set else returns false. 
{
    //matching every element of array and return true of it matched else return false
    for (int i = 0; i < noOfElements; i++)
    {
        if (this->arr[i] == value)
        {
            return true;
        }
    }
    return false;
}


void Set::displaySet()// display the contents of set. (in curly brakets and coma separated)
{
    //if set is empty then print { } 
    if (isEmpty())
    {
        cout << "{ }";
    }
    else 
    {
        //printing set in correct formate
        cout << "{ ";
        for (int i = 0; i < noOfElements; i++)
        {
            cout << this->arr[i] << " , ";
        }
        cout << "\b\b}";
    }
}


Set Set::intersection(Set a) // return the intersection of the sets.
{
    //resultant set with size of first set
    Set resultset(size);

    /******   intersection logic   ********/
    for (int i = 0; i < this->noOfElements; i++) //pic every element of first set
    {
        for (int j = 0; j < a.noOfElements; j++) //match every element of second set with the respective element of fisrt set
        {
            if (this->arr[i] == a.arr[j]) //if element matched, it would store it into the resultant set
            {
                resultset.insertElement(arr[i]); //again element
            }
        }
    }

    //if the number of elemets become less then half of size of array, this check reduct the array to half
    if (resultset.noOfElements < (resultset.size / 2))
    {
        resultset.reduce_size();
    }


    return resultset; //return the resultant set having intersection
}



Set Set::Union(Set a) // return the union of the sets.
{
    int num = size + a.size;
    //creating resultant array to store union
    Set resultSet(num);

    //storing all elemets of first set in resultant
    for (int i = 0; i < noOfElements; i++)
    {
        resultSet.insertElement(arr[i]);
    }

    /*           Union Logic          */
    for (int i = 0; i < a.noOfElements; i++) //pic every element of second set
    {
        if (!(searchElement(a.arr[i]))) //if not matched then it would add that value to the resultant set
        {
            resultSet.insertElement(a.arr[i]);
        }
    }

    return resultSet;
}



Set Set::operator+(Set& first) // You may call union function in this function.
{
    Set resultSet = Union(first); //add the union of sets to resultant set using copy constructor
    return resultSet;
}


Set Set::difference(Set a) // return the difference of the sets.
{
    //set to store the difference of the sets
    Set resultSet(size);

    //storing all elements of fisrt set in the resultant set
    for (int i = 0; i < noOfElements; i++)
    {
        resultSet.insertElement(arr[i]);
    }

    /*           difernece Logic          */
    for (int i = 0; i < a.noOfElements; i++) //pic every element of second set
    {
        for (int j = 0; j < noOfElements; j++) //match every element of first set with the respective element of second set
        {
            if (a.arr[i] == this->arr[j]) //if not matched then it would remove that value from the resultant set
            {
                resultSet.removeElement(a.arr[i]);
            }
        }
    }

    //if the number of elemets become less then half of size of array, this check reduct the array to half
    if (resultSet.noOfElements < (resultSet.size / 2))
    {
        resultSet.reduce_size();
    }


    return resultSet;
}



Set Set::operator-(Set& first) // You may call difference(Set a) function in this function.
{
    Set resultSet = difference(first);  //add the union of sets to resultant set using copy constructor
    return resultSet;
}



int Set::isSubSet(Set a) // return 1 for proper subset, return 2 for improper subset return 0 if not a subset.
{
    /*The empty set is an improper subset of itself (since it is equal to itself)
      but it is a proper subset of any other set.*/
    if (a.isEmpty()) //check for empty subset
    {
        if (isEmpty())
        {
            return 2;
        }
        else
        {
            return 1;
        }
    }

    /************ Logic for proper subset, improper subset and not a subset **************/
    bool flag = true;
    //checking weither all elements of second set are present in first set or not
    for (int i = 0; i < a.noOfElements; i++)
    {
        if ((searchElement(a.arr[i])) == false) //if any element of 2nd set is not present in first set, the flag would false
        {
            flag = false;
        }
    }

    /* if flag is true mean the second set have all elements that are present in first set
       thus second set is the subset (proper/ improper) of fisrt set
       otherwise second set in not a subset and return 0 */
    if (flag)
    {
        //if second set has less number of elements than first set then it is proper subset , otherwise improper subset
        if (a.noOfElements < this->noOfElements)
        {
            return 1;
        }
        else
        {
            return 2;
        }
    }
    else
    {
        return 0;
    }

}




Set::~Set() //destructor
{
    delete[]this->arr;
    this->arr = NULL;
}



string& Set::operator[](int i)// Directly access element in the set. If element does not exist, return -1.
{
    if (i >= 0 && i < size)
        return arr[i];
    else
    {
        cout << "ERROR!Invalid Index." << endl;
        exit(0);
    }

}

Set Set::operator=(const Set& a) //overloading = operaator
{
    //delete old array
    if (arr != NULL)
    {
        delete[]arr;
        arr = NULL;
    }

    //create new array
    this->size = a.size;
    this->noOfElements = a.noOfElements;
    this->arr = new string[size];
    for (int i = 0; i < size; i++)
        this->arr[i] = a.arr[i];

    return *this;
}


//function to check double for templated class
void Set::RunObject()
{
    cout << "\n=================================================================================================== \n";
    cout << "*                                Sets                                                             * ";
    cout << "\n=================================================================================================== \n\n";
    int num1 = 0, num2 = 0;
    string input;
    //************************ SET A ******************************************
    cout << "**********************************\n";
    cout << "SET A\n";
    cout << "Enter the size: ";
    cin >> input;
    num1 = static_cast<int>(input[0]) - 48;

    //creating two sets
    Set a(num1);

    //variable to take input values from user
    string num;

    //getting values in Set a
    cout << "Enter the elements of set A \n";
    for (int i = 0; i < num1; i++)
    {
        cout << i + 1 << ": ";
        cin >> num;
        //check for invalid enter (if the values is already present , it would ask again to enter)
        while ((a.insertElement(num)) == false)
        {
            cout << "Sorry! this element is already present , Enter again: ";
            cin >> num;
        }
    }

    //************************ SET B ******************************************
    cout << "**********************************\n";
    cout << "SET B\n";
    cout << "Enter the size of Size B: ";
    cin >> input;
    num2 = static_cast<int>(input[0]) - 48;
    //creating set
    Set b(num2);
  
    //getting values in set b
    cout << "Enter the elements of set B \n";
    for (int i = 0; i < num2; i++)
    {
        cout << i + 1 << ": ";
        cin >> num;
        //check for invalid enter (if the values is already present , it would ask again to enter)
        while ((b.insertElement(num)) == false)
        {
            cout << "Sorry! this element is already present , Enter again: ";
            cin >> num;
        }
    }

    cout << "\n\n====================================================\n\n";
    cout << "                 Calculations \n";
    cout << "\n====================================================\n\n";

    cout << " Set A:  ";
    a.displaySet();
    cout << "\n\n";

    cout << " Set B:  ";
    b.displaySet();
    cout << "\n\n\n";

    //checking union function
    Set c = a.Union(b);
    cout << " Union of A & B =          ";
    c.displaySet();
    cout << "\n\n";

    //checking intersection function
    c = a.intersection(b);
    cout << " Intersection of A & B =   ";
    c.displaySet();
    cout << "\n\n";

    //checking - operator
    c = a - b;
    cout << " Difference of B from A = ";
    c.displaySet();
    cout << "\n\n";

    //checking - operator
    c = b - a;
    cout << " Difference of A from B = ";
    c.displaySet();
    cout << "\n\n";

    //checking isSubSet function 
    if (a.isSubSet(b) == 1)
    {
        cout << " \"B is proper subset of A\" \n";
    }

    if (a.isSubSet(b) == 2)
    {
        cout << " B is improper subset of A \n";
    }


    if (b.isSubSet(a) == 0)
    {
        cout << " A is not subset of B \n";
    }

    if (b.isSubSet(a) == 1)
    {
        cout << " \"A is proper subset of B\" \n";
    }

    if (b.isSubSet(a) == 2)
    {
        cout << " A is improper subset of B \n";
    }


    if (b.isSubSet(a) == 0)
    {
        cout << " A is not subset of B \n";
    }

    cout << "\n=================================================================================================== \n\n";
    system("pause");
}







//// *********************** MAIN FUNCTION ***********************
//int main()
//{
//    Set<string> S;
//    S.RunObject();
//
//    return 0;
//}