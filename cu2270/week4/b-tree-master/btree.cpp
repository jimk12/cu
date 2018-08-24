// btree.cpp

#include <iostream>
#include "btree.h"

using namespace std;


btree* init_noder() {
  btree* ret = new btree;
  ret->num_keys = 0;
  ret->is_leaf = true;
  for (int i=0; i <= BTREE_ORDER; i++) {
    ret->children[i] = NULL;
  }
  return ret;
}

void insert(btree*& root, int key) {
  btree* cursor = find(root, key);
  btree* newRoot = init_noder();
  if (cursor->is_leaf) {
    if (cursor->num_keys == 0) {
      root->num_keys = 1;
      cursor->keys[0] = key;
      root = cursor;
    }
    else {
      for (int i=0; i <= cursor->num_keys-1; i++) {
        if (cursor->keys[i] == key) {
          return;
        }
        
        if (cursor->keys[i] > key) {
            cursor->num_keys += 1;
            int temp = cursor->keys[i];
            cursor->keys[i] = key;
            for (int j=i+1; j<= cursor->num_keys-1; j++) {
              int temp2 = cursor->keys[j];
              cursor->keys[j] = temp; 
              temp = temp2;
            }
            if (cursor->num_keys == BTREE_ORDER) {
              int temp = cursor->keys[BTREE_ORDER/2];
              int middleKey = BTREE_ORDER/2;
              insert(newRoot, temp);
              newRoot->children[0] = init_noder();
              newRoot->children[1] = init_noder();
              for (int i=0; i < middleKey; i++) {
                insert(newRoot->children[0], cursor->keys[i]);
                insert(newRoot->children[1], cursor->keys[i+3]);
              }
              root = newRoot;
              root->is_leaf = false;
              cursor = newRoot;
              /*
              for (int i=0; i <= cursor->num_keys; i++) {
                cout << cursor->children[0]->keys[i] << endl;
              }
              */
            }
            return;
          
        }
      }
      cursor->num_keys += 1;
      cursor->keys[cursor->num_keys-1] = key; 
    }
  }
  else {
    cout << "-------------here----------";
    for (int i=0; i < cursor->num_keys; i++) {
      if (cursor->keys[i] == key) {
        return;
      }
      if (cursor->keys[i] > key) {
        cursor->num_keys += 1;
        int temp = cursor->keys[i];
        cursor->keys[i] = key;
        for (int j=i+1; j<= cursor->num_keys-1; j++) {
          int temp2 = cursor->keys[j];
          cursor->keys[j] = temp; 
          temp = temp2;
        }
      }
    }
  }
}

void remove(btree*& root, int key) {
  btree* cursor = find(root, key);
  if (cursor->num_keys == 0) {
    return;
  }
  else {
    if (cursor->is_leaf) {
      for (int i=0; i < cursor->num_keys; i++) {
        if (cursor->keys[i] == key) {
          for (int j=i; j < cursor->num_keys-1; j++) {
            cursor->keys[j] = cursor->keys[j+1];
          }
        }
      }
    }
  }
}

btree* find(btree*& root, int key) {
  btree* cursor = root; 
  int i = 0;
  int j = 0;

  while (i == 0) {
    if (cursor->keys[j] != NULL) {
     	if (cursor->keys[j] == key) {
      		return cursor;
      	}

    	if (key < cursor->keys[j]) {
    		if (cursor->children[j] == NULL) {
    			return cursor;
    		}
      		if (cursor->children[j]->keys[0] != NULL) {
      			cursor = cursor->children[j];
      			return find(cursor, key);   	
      		}
      	}
      	j++;
    }
    else {
    	if (cursor->children[j] == NULL) {
    	    return cursor;
    	}
    	if (cursor->children[j]->keys[0] != NULL) {
			cursor = cursor->children[j];
		 	return find(cursor, key);
		  	i = 1;
		 }
    }
  }
}

int count_nodes(btree*& root) {
  btree* cursor = root;
  int temp = 1;
  if (cursor->is_leaf) {
    return 1;
  }
  for (int i =0; i <= BTREE_ORDER; i++) {
    if (cursor->children[i] != NULL) {
      temp += count_nodes(cursor->children[i]);
    }
  }
  return temp;
}

int count_keys(btree*& root) {
  btree* cursor = root;
  int temp = cursor->num_keys;
  if (cursor->is_leaf) {
    return cursor->num_keys;
  }
  for (int i =0; i <= BTREE_ORDER; i++) {
    if (cursor->children[i] != NULL) {
      temp += count_keys(cursor->children[i]);
    }
  }
  return temp;
}


