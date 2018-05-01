#include "hashNode.hpp"
#include <stdlib.h>

//constructor-initializes keyword to “” , values to 0, and array to NULL
hashNode::hashNode() : keyword(""), values(nullptr), valuesSize(0), currSize(0)
{

}

// initializes keyword to s, the arraysize to 100 (or
//whatever you like for starting), the currSize to 0, and the valuesSize to 100
hashNode::hashNode(string s) : keyword(s), values(nullptr), valuesSize(100), currSize(0)
{
    values = new string[valuesSize];   
}

// in addition, puts a value in the values
//array and initializes currSize to 1
hashNode::hashNode(string s, string v) : keyword(s), valuesSize(100), currSize(0)
{
    values = new string[valuesSize];  
    values[currSize] = v;
    currSize++;
}

// adds a new value to the end of the values array,
//increases currSize, checks to make sure there’s more space, and, if not, calls dblArray()
void hashNode::addValue(string v)
{
    if (currSize >= valuesSize)
    {
        dblArray();
    }
    
    values[currSize] = v;
    currSize++;
}

//creates a new array, double the length, and copies over the
//values. Sets the values array to be the newly allocated array.
void hashNode::dblArray()
{
   string* newValues = new string[valuesSize * 2];
   for (int i = 0; i < valuesSize; i++)
   {
       newValues[i] = values[i];
   }
   delete[] values;
   
   values = newValues;
   valuesSize *= 2;
}

// returns a random string from the values array. If
//there’s no values in the value array, then it returns an empty string.
string hashNode::getRandValue()
{
    if (currSize == 0)
    {
        return "";
    }
    else 
    {
        return values[rand() % currSize];
    }
}
