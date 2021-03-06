/*
 * File: pqueue.cpp (array version)
 * --------------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file implements the pqueue.h interface using a dynamic array as
 * the underlying representation.  Most of the code is already in place.
 * The only thing that is missing is the implementation of the actual
 * commands.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <string>
#include "error.h"
#include "pqueue.h"
#include "vector.h"
using namespace std;


PriorityQueue::PriorityQueue() {
    priorityqueue = new Vector<Entry*>();
    pqueueSize = 0;
}

PriorityQueue::~PriorityQueue() {
    if(size() != 0) {
        for(Entry *currEntry : *priorityqueue) {
            delete currEntry;
            currEntry = NULL;
        }
    }
    delete priorityqueue;
    priorityqueue = NULL;
}

int PriorityQueue::size() const {
   return pqueueSize;
}

bool PriorityQueue::isEmpty() const {
   return pqueueSize == 0;
}

void PriorityQueue::clear() {
    for(Entry *currEntry : *priorityqueue) {
        delete currEntry;
        currEntry = NULL;
    }
    pqueueSize = 0;
}

void PriorityQueue::enqueue(string value, double priority) {
    Entry* entry = new Entry {priority, value};
    //Don't bother looping in empty
    if(!priorityqueue->isEmpty()) {
      for(int i = 0; i < pqueueSize; i++) {
          //If their is a priority higher than passed, EG. 1 is higher than 2 in priority
          if(priority > priorityqueue->get(i)->priority) {
              //If we haven't reached the max index, then their is still a possibility this priority is "higher" than another. See above example
              if(i != pqueueSize - 1) continue;
              //every other entry in list has a higher priority, so append new entry
              else priorityqueue->add(entry);
          }
          //We found a priority lower than the one passed, so insert it before said priority/ then break
          else {
              priorityqueue->insert(i, entry);
              break;
          }
      }
  }
  //No existing entries, so just add the new one
  else {
      priorityqueue->add(entry);
  }
    pqueueSize++;
}

string PriorityQueue::dequeue() {
   if(isEmpty()) error ("Cannot dequeue from an empty PriorityQueue!");
   string value = priorityqueue->get(0)->value;
   Entry* ent = priorityqueue->get(0);
   priorityqueue->remove(0);
   delete ent;
   ent = NULL;
   pqueueSize--;
   return value;
}

string PriorityQueue::peek() const {
    if(isEmpty()) {
        error("Cannot retrieve value from an empty PriorityQueue!");
    }
    return priorityqueue->get(0)->value;;
}

double PriorityQueue::peekPriority() const {
   if(isEmpty()) error("Cannot retrieve priority from an empty PriorityQueue!");
   return priorityqueue->get(0)->priority;
}

/*
 * Implementation notes: copy constructor and assignment operator
 * --------------------------------------------------------------
 * The constructor and assignment operators follow the standard
 * paradigm described in the textbook.
 */

PriorityQueue::PriorityQueue(const PriorityQueue & src) {
   priorityqueue = new Vector<Entry*>();
   pqueueSize = 0;
   copyDeep(src);
}

PriorityQueue & PriorityQueue::operator=(const PriorityQueue & src) {
   if (this != &src) {
      if (array != NULL) delete[] array;
      deepCopy(src);
   }
   return *this;
}
