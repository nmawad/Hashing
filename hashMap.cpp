/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "hashMap.hpp"

// when creating the map, make sure you initialize the values to
//NULL so you know whether that index has a key in it or not already
hashMap::hashMap() : map(nullptr), first(""), numKeys(0), mapSize(0) 
{
    
}

 // adds a node to the map at the correct index based on the key string, and
 //then inserts the value into the value field of the hashNode
 // Must check to see whether there's already a node at that location. If
 //there's nothing there (it's NULL), add the hashNode with the keyword and value.
 // If the node has the same keyword, just add the value to the list of values.
 //If the node has a different keyword, keep calculating a new hash index until
 //either the keyword matches the node at that index's keyword, or until the
 // map at that index is NULL, in which case you'll add the node there.
 //This method also checks for load, and if the load is over 70%, it calls the
 //reHash method to create a new longer map array and rehash the values
void hashMap::addKeyValue(string k, string v)
{
    if (isMaxLoad())
    {
        reHash();
    }
    
    int index = getIndex(k);
    
    if (map[index] == nullptr)
    {
        hashNode *node = new hashNode(k,v);
        map[index] = node;
    }
    else if (map[index]->keyword == k)
    {
        map[index]->addValue(v);
    }
    else
    {
        for (int i = 1; ; i = (i + 1) % mapSize)
        {
           int index2 = dblHash(index, i, k);
           if (map[index2] == nullptr)
           {
               hashNode *node = new hashNode(k,v);
               map[index2] = node;
               break;
           }
           else if (map[index2]->keyword == k)
           {
               map[index2]->addValue(v);
               break;
           }
       }   
    }
}

// uses calcHash and reHash to calculate and return
//the index of where the keyword k should be inserted into the map array
int hashMap::getIndex(string k)
{
    
    return calcHash(k);
    
} 

int hashMap::calcHash(string k)
{
    // hash function
    int sum = 0;
    for (int i = 0; i < k.size(); i++)
    {
        sum += k[i];
    }
    
    int index = sum % mapSize;
    return index;
}

// I used a binary search on an array of prime
//numbers to find the closest prime to double the map Size, and then set mapSize to
//that new prime. You can include as one of the fields an array of prime numbers, or
//you can write a function that calculates the next prime number. Whichever you
//prefer.
void hashMap::getClosestPrime()
{
    int newMapSize = mapSize * 2;
    while (!isPrime(newMapSize))
    {
        newMapSize++;
    }
    
    mapSize = newMapSize;
}

bool hashMap::isPrime(int n)
{
    if (n == 1)
    {
        return false;
    }
    
    for (int i = 2; i * i <= n; i++)
    {
       if (n % i == 0)
       {
           return false;
       }
    }
    
    return true;
}


// when size of array is at 70%, double array size and rehash keys
void hashMap::reHash()
{
    if (isMaxLoad())
    {
        int oldMapSize = mapSize;
        getClosestPrime();
        hashNode **newMap = new hashNode*[mapSize];
        
        for (int i = 0; i < mapSize; i++)
        {
            newMap[i] = nullptr;
        }
        
        for (int i = 0; i < oldMapSize; i++)
        {
            if (map[i] != nullptr)
            {
               int index = getIndex(map[i]->keyword);
               newMap[index] = map[i];
            }
        }
        
        delete[] map;
        map = newMap;
    }
}  

// for hashing when index is already full
int hashMap::dblHash(int h, int i, string k)
{
    int m = mapSize - 1;
    
    while (!isPrime(m))
    {
        m--;
    }
    
    int h2 = 1 + (calcHash(k) % m);
    
    return h + i * h2;;
}   

//finds the key in the array and returns its index. If it's not in the array, returns -1
int hashMap::findKey(string k)
{
    for (int i = 0; i < mapSize; i++)
    {
        if (map[i]->keyword == k)
        {
            return i;
        }
    }
    return -1;
}   
 
//I wrote this solely to check if everything was working.
void hashMap::printMap()
{
    for (int i = 0; i < mapSize; i++)
    {
        hashNode *node = map[i];
        cout << node->keyword << ":" << endl;
        for (int j = 0; j < node->currSize; j++)
        {
            cout << node->values[j] << ", ";
        }
        cout << endl;
    }
}

bool hashMap::isMaxLoad()
{
    return numKeys >= 0.7 * mapSize;
}