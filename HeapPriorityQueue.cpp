//HeapPriorityQueue.cpp
#ifndef _HEAPPRIORITYQUEUE_CPP
#define _HEAPPRIORITYQUEUE_CPP

#include "HeapPriorityQueue.hpp"
#include <cassert>
#include <cstdlib>//for NULL
#include <iostream>

// note:   vector<PuzzleState *> heap;
// supported operations: 
//empty()
//size()
//front()
//push_back()
//pop_back()

/*constructor*/
HeapPriorityQueue::HeapPriorityQueue() {
}

/*destructor*/
HeapPriorityQueue::~HeapPriorityQueue() {
  // no clean-up to do, since the heap is not dynamically allocated
}

/*insert element in heap form*/
void HeapPriorityQueue::put_in(PuzzleState *elem) {
  // TODO:  Put your code here!
  // no need to check if heap is full->automatic resize
  heap.push_back(elem);
  swapUp();
}

/*
* remove the top element
* ie. the activeState with lowest badness-score
*/
PuzzleState * HeapPriorityQueue::take_out() {
  assert(!is_empty());

  // TODO:  Put your code here!

  // we want the value at front of the heap vector
  // and pop it, but we can only pop from the back
  PuzzleState* returnVal = heap.front();
  int newFront = (int)heap.size()-1;
  swap(newFront,0);
  heap.pop_back(); 

  swapDown();

  return returnVal;

}

/*swapping a parent and child*/
void HeapPriorityQueue::swap(int child, int parent){
  PuzzleState* temp = heap[child];
  heap[child] = heap[parent];
  heap[parent] = temp;
}

/*swap up from the back(bottom) to front(top)*/
void HeapPriorityQueue::swapUp(){

  int child = (int)heap.size()-1;  // back(bottom) = n-1
  int parent = get_parent(child); 

  // iterative solution:
  while(heap[child] < heap[parent] && child>=0 && parent >=0){
    swap(child, parent);
    child = parent; // go up a level
    parent = get_parent(child);
  }
  
}

/*swap down from the top to bottom*/
void HeapPriorityQueue::swapDown(){
  int parent = 0; // top

//iterative solution
  while(true){
    int m = parent; // m = min?
    int left = first_child(parent);
    int right = first_child(parent) + 1;
    int n = (int)heap.size();

    if (left < n && heap[left] < heap[m])
      m = left;

    if (right < n && heap[right] < heap[m])
      m = right;

    if (m != parent) {
      swap(m, parent);
      parent = m;
    }
    else  
      break;  

  }
  
}


bool HeapPriorityQueue::is_empty() {
  return (heap.size() == 0);
}

// return parent, given its child
int HeapPriorityQueue::get_parent(int index) {
  return (index - 1) / 2;
}

// return the left child
// note: right child = leftchild+1
int HeapPriorityQueue::first_child(int index) {
  return 2 * index + 1;
}

bool HeapPriorityQueue::is_root(int index) {
  return index == 0;
}

bool HeapPriorityQueue::is_leaf(int index) {
  return num_children(index) == 0;
}

int HeapPriorityQueue::num_children(int index) {
  int fchild = first_child(index);
  return max(0, min(2, (int)heap.size() - fchild));
}

#endif
