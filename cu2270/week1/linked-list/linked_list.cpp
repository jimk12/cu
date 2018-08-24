/*

  linked_list.cpp

 */

// AUTHOR: TODO
// WHAT: CSCI 2270 Assignment 1
// COLLABORATORS: TODO

#include "linked_list.h"

using namespace std;

// create a new node structure that points to NULL and holds the
// provided integer. return a pointer to that new node.
node* init_node(int data) {
  node* ret = new node;
  ret->data = data;
  ret->next = NULL;
  return ret;
}

// create a space-separated string representing the contents of the
// list, in the same order they are found beginning from the head of
// the list. return that string object.  For example, this might
// return "" (the empty string) if the list is empty, or it might
// return "1 7 3" or "1 7 3 " (note the space at the end, you can have
// that there and it is OK).
string report(node* head) {
  string s = "";
  if(head != NULL){
    while(head != NULL) {
      s += to_string(head->data) + " ";
      head = head->next;
    }
  return s;
  }
  else{
  return s; 
  }
}

// insert an integer into the list pointed to by top. the resulting
// list is one element longer, and the newly appended node has the
// given data value. consider using the 'append' function to help.
void append_data(node** top, int data) {
  node *temp = new node;
  temp->data = data;
  temp->next = NULL;
  node* cursor = *top;
  while (cursor->next != NULL) {
  cursor=cursor->next;
  }
  cursor->next = temp;  

  /*
  I put it in the beginning instead of the end!!!
  cout << "appendStart" << endl;
  cout << (*top)->data << endl;
  cout << (*top)->next->data << endl;
  cout << (*top)->next->next->data << endl;
  node *temp = new node;
  temp->data = data;
  temp->next = NULL;
  if (*top!=NULL) temp->next=*top;
  *top = temp;
  cout << "appendend" << endl;
  cout << (*top)->data << endl;
  cout << (*top)->next->data << endl;
  cout << (*top)->next->next->data << endl;
  cout << (*top)->next->next->next->data << endl;
  */
}

// this is the same as append_data, except we're adding a node, rather
// than a value. 
void append(node** top, node* new_node) {
  node* cursor = *top;
  if (*top != NULL){
    while (cursor->next != NULL) {
      cursor=cursor->next;
    }
    cursor->next = new node();
    cursor->next = new_node; 
  }
  else {
  *top = new_node;
  }
}

// similar to append_data. insert a new node that contains the given
// data value, such that the new node occupies the offset
// indicated. Any nodes that were already in the list at that offset
// and beyond are shifted down by one. For example if the list
// contains 23, 74, 93, and we insert 42 at index 1, the resulting
// list should be 23, 42, 74, 93.
void insert_data(node** top, int offset, int data) {
  node* temp = new node();
  temp->data = data;
  if(offset==0){
    temp->next = *top;
    *top = temp;
  }
  else{
    node* cursor = *top;
    for (int i = 0; i < offset-1; i++) {
      cursor=cursor->next;
    }
    node* nn = new node();
    nn = cursor->next;
    cursor->next = temp;
    cursor->next->next = nn;    
  }
}

// this is the same as insert_data, except we're inserting a node,
// rather than a value.
void insert(node** top, int offset, node* new_node) {
  if(offset==0){
  new_node->next = *top;
  *top = new_node;
  }
  else{
    node* cursor = *top;
    for (int i = 0; i < offset-1; i++) {
      cursor=cursor->next;
    }
    node* nn = new node();
    nn = cursor->next;
    cursor->next = new_node;
    cursor->next->next = nn;    
  }
}

// remove the node indicated by the given offset. For example if our
// list contains 23, 74, 93, and we remove offset 1, the resulting
// list should then contain 23, 93.
void remove(node** top, int offset) {
  node* cursor = *top;  
  if(offset == 0) {
    *top = cursor->next;  
  }
  else{
    for (int i = 0; i < offset-1; i++) {
      cursor=cursor->next;
    }
    cursor->next = cursor->next->next;
  }
}

// report the number of nodes in the linked list pointed to by head.
int size(node* head) {
  if(head==NULL)return 0;
  else{
    int ret = 0;
    node* cursor = head;
    while (cursor->next != NULL) {
      cursor=cursor->next;
      ret += 1;
    }
  return ret+1; 
  }
}

// return true if the linked list pointed to by head contains a node
// with the specified value.
bool contains(node* head, int data) {
  if(head==NULL){
    return false;
  }
  if (head->data == data) {
    return true;
  }
  else{
    node* cursor = head;
    while (cursor->next != NULL) {
      if(cursor->data == data){
        return true;
      }      
      cursor=cursor->next;
    }
   if(cursor->data == data) {
     return true;
   } 
   return false;
   }
}  

