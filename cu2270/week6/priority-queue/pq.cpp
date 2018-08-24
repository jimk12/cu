//
// pq.cpp
//
// Decide how you want to implement this: linked list? heap? array?
// magic pixie dust? The choice is yours.
//
// NOTE: You will need to edit pq_struct.h as appropriate, depending
// on your implementation strategy. You will turn in this file (your
// implementation of everything) and pq_struct.h (your definition of
// the pq structure and any helper functions you might create).

// Your Name:


#include <string>
#include "pq.h"

pq* init_priority_queue() {
  pq* ret = new pq;
  return ret;
}

pq* newPQ(string data, double priority) {
	pq* temp;
	pq*->data = data;
	pq*->priority = priority;
	pq*->next = null; 
	return temp;
}

void insert(pq* &queue, string text, float priority) {
  pq* front = queue;
  pq* temp = newPQ(text, priority);

  if (queue->priority >priority) {
  	temp->next = queue;
  	queue = temp;
  }
}

string remove(pq* &queue) {
  pq* temp = queue;
  free(temp);

}

string peek(pq* &queue) {
  return queue->data;
}
