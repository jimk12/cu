//
// binary_search_tree.cpp
//
// Please refer to binary_search_tree.h for documentation.
//

#include "binary_search_tree.h"
using namespace std;

bt_node* get_parent(bt_node* t, bt_node* parent, int data) {
  if (t==NULL) return NULL;
  if (t->data==data) return parent;
  parent = t;
  if (data<t->data) return get_parent(t->left, parent, data);
  else return get_parent(t->right, parent, data);
}


bt_node* init_node(int data) {
  bt_node* ret = new bt_node;
  ret->data = data;
  ret->left = NULL;
  ret->right = NULL;
  return ret; // TODO
}

void insert(bt_node** top, bt_node* new_node) {
  if(new_node->data < (*top)->data
     && (*top)->left == NULL) {
    (*top)->left = new_node;
  }
  
  if(new_node->data > (*top)->data
     && (*top)->right == NULL) {
    (*top)->right = new_node;
  }

  if(new_node->data > (*top)->data
     && (*top)->right != NULL) {
    if(new_node->data > (*top)->right->data
       && (*top)->right->right == NULL) {
      (*top)->right->right = new_node; 
    }
  }
}

void insert_data(bt_node** top, int data) {
  bt_node* new_node = new bt_node;
  new_node->data = data;
  new_node->left = NULL;
  new_node->right = NULL;
    if(new_node->data < (*top)->data
     && (*top)->left == NULL) {
    (*top)->left = new_node;
  }
  
  if(new_node->data > (*top)->data
     && (*top)->right == NULL) {
    (*top)->right = new_node;
  }

  if(new_node->data > (*top)->data
     && (*top)->right != NULL) {
    if(new_node->data > (*top)->right->data
       && (*top)->right->right == NULL) {
      (*top)->right->right = new_node; 
    }
  }
}

void remove(bt_node** top, int data){
  bt_node* ret = new bt_node;
  ret = (*top); 
  bt_node* parent = new bt_node;
  parent = get_parent((*top), ret, data); 
  bt_node* t = get_node((*top), data);

  if (t->right == NULL && t->left == NULL) {
    if (t->data == parent->left->data) parent->left = NULL;
    if (t->data == parent->right->data) parent->right = NULL;
}

  if (t->left == NULL && t->right != NULL) {  
    parent->right = parent->right->right;
  }

  if (t->right == NULL && t->left != NULL) { 
    cout << "here" << endl;    
    parent->left = parent->left->left;
    }
 
  if ((*top)->data == data) {
    cout << (*top)->data << t->data << endl;
    cout << t->left->data << t->right->data;
    t->data = t->left->data;
    t->left = NULL;
    cout << "here now" << endl;
  }
}


bool contains(bt_node* t, int data) {
  if (t==NULL) return NULL;
  if (t->data==data) return true;
  if (data<t->data) return get_node(t->left, data);
  if (data>t->data) return get_node(t->right, data);
  return false;
}

bt_node* get_node(bt_node* t, int data) {
  if (t==NULL) return NULL;
  if (t->data==data) return t;
  if (data<t->data) return get_node(t->left, data);
  else return get_node(t->right, data);
}

int size(bt_node* t) {
  if (t != NULL )
  cout << t->data << endl; 
if (t==NULL) return 0;

  else return (size(t->left) + 1 + size(t->right)); 
}


void to_array(bt_node* t, int arr[]) {
   for(int i = 0; i < 6; i++) {
     arr[i] = i;
   }
}


