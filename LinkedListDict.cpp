#ifndef _LINKEDLISTDICT_CPP
#define _LINKEDLISTDICT_CPP

//LinkedListDict.cpp
#include "LinkedListDict.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// An implementation of a dictionary ADT as an unsorted linked list.
//
LinkedListDict::LinkedListDict() {
  root = NULL;
}

LinkedListDict::~LinkedListDict() {
  // Clean up linked list.
  node * rest = root;
  while (rest != NULL) {
    node * temp = rest;
    rest = rest->next;
    delete temp->key;
    // delete temp->data; // Don't delete this here, to avoid multiple deletes.
    delete temp;
  }
}


/*go thru list and compare keys, if found, update pred and return true*/
bool LinkedListDict::find_helper(node *r, string keyID, PuzzleState *&pred) {
  while (r!=NULL) {
    if (keyID == r->keyID) {
      pred = r->data; // Got it!  Get the result.
      return true;
    }
    r = r->next;
  }
  return false; // Never found it.
}

// search:
bool LinkedListDict::find(PuzzleState *key, PuzzleState *&pred) {
  return find_helper(root, key->getUniqId(), pred);
}

// insert:
/*insert new node before root/head, then update new node as root*/
void LinkedListDict::add(PuzzleState *key, PuzzleState *pred) {
  node * temp = new node();
  temp->key = key;
  temp->keyID = key->getUniqId();
  temp->data = pred;
  temp->next = root;
  root = temp;
  return;
}

#endif 
