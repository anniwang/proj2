#ifndef _FIXEDCHAINHASHDICT_CPP
#define _FIXEDCHAINHASHDICT_CPP

//FixedChainHashDict.cpp
#include "FixedChainHashDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of the dictionary ADT as a fixed-size hash table with
// chaining


//    ChainNode **table; //double pointer, so you can reused this code for ResizeChainHashDict
//    int size; // size of the hash table array
//    int number; // how many items are currently in hash table


/*constructs hsh table of table_size */
FixedChainHashDict::FixedChainHashDict(int table_size) {
  size = table_size;
  table = new ChainNode*[size](); // Parentheses initialize to all NULL
  number = 0;

  // Initialize the array of counters for probe statistics
  probes_stats = new int[MAX_STATS]();
  numOfCallsToFind = -1;
}

// destructor
FixedChainHashDict::~FixedChainHashDict() {
  for (int i=0; i<size; i++) {
    // Delete the chains from each table entry...
    ChainNode *head = table[i];
    while (head!=NULL) {
      ChainNode *temp = head;
      head = head->next;
      delete temp->key;  // Each PuzzleState is a key exactly once.
      // Don't delete temp->data here, to avoid double deletions.
      delete temp;
    }
  }
  // Delete the table itself
  delete [] table;

  // It's not good style to put this into a destructor,
  // but it's convenient for this assignment...
  cout << "Total calls to find(): " << numOfCallsToFind+1 << endl;
  cout << "Probe Statistics for find():\n";
  for (int i=0; i<MAX_STATS; i++)
    cout << i << ": " << probes_stats[i] << endl;
  delete [] probes_stats;
}

// do not modify the hash function
int FixedChainHashDict::hash(string keyID) {
  int h=0;
  for (int i=keyID.length()-1; i>=0; i--) {
    h = (keyID[i] + 31*h) % size;
  }

// 221 Students:  DO NOT CHANGE OR DELETE THE NEXT FEW LINES!!!
// We will use this code when marking to be able to watch what
// your program is doing, so if you change things, we'll mark it wrong.
#ifdef MARKING_TRACE
std::cout << "Hashing " << keyID << " to " << h << std::endl;
#endif
// End of "DO NOT CHANGE" Block
  return h;
}

// search for a key in table
bool FixedChainHashDict::find(PuzzleState *key, PuzzleState *&pred) {
  // Returns true iff the key is found.
  // Returns the associated value in pred
  // Be sure not to keep calling getUniqId() over and over again!
  // TODO:  Put your code here!  

  //Remember to update probes_stats, too.
   //ie. count how many entries are checked in the collision chain 
   //on each call to find(), 
   //and to update the statistics in the probes_stats array.

  numOfCallsToFind++; // from 0 to 20
  return find_helper(key->getUniqId(), pred);
}


/*find node that match key, update pred = node.data, and return true*/
bool FixedChainHashDict::find_helper(string keyID, PuzzleState *&pred) {
 
  int h = hash(keyID);
  ChainNode* chainHead = table[h];
  int count = 0; // count checks in collision chain
                  // starts off with check at table[h]

  // keep going down the chain until we find node that matches keyID
  while(chainHead!= NULL && chainHead->keyID != keyID){
    chainHead = chainHead->next;
    count++;
  }

  // update stats
  probes_stats[numOfCallsToFind] = count;

  if(chainHead != NULL){
    pred = chainHead->data; 
    return true;
    }

  return false; // Never found it.
}

// You may assume that no duplicate PuzzleState is ever added.
void FixedChainHashDict::add(PuzzleState *key, PuzzleState *pred) {
  // TODO:  Put your code here!
  
  string myKeyID = key->getUniqId();  // call get id once

  int h = hash(myKeyID);
  ChainNode* chainHead = table[h];

  // create new node
  ChainNode * temp = new ChainNode();
  temp->key = key;
  temp->keyID = myKeyID;
  temp->data = pred;
  temp->next = NULL;

  // if table is empty, add node to slot
  // if table is nonempty, add node to last element
  if(chainHead == NULL){
    chainHead = temp;

  }  else{

    // search for last element, last->next=null
    while(chainHead->next != NULL){
      chainHead = chainHead->next;
    }

    //note: assume there will be no duplicates
    // let the next element of the last element be the new element
    chainHead->next = temp;

  }


  return;
}

#endif 
