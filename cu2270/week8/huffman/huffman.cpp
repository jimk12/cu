// huffman.cpp
//

#include "huffman.h"

using namespace std;

string s;
map<char, string> ret;

freq_info* create_leaf(char symbol, int count) {
  freq_info* ret = new freq_info;
  ret->symbol = symbol;
  ret->count = count;
  ret->right = NULL;
  ret->left = NULL;
  return ret;
}

freq_info* combine_nodes(freq_info* left, freq_info* right) {
  freq_info* ret = new freq_info;
  ret->count = left->count + right->count;
  ret->symbol = '$';
  ret->left = left;
  ret->right = right;
  ret->is_leaf = false;
  return ret;
}

void increment_lookup(map<char, int>& lookup, char symbol) {
  lookup[symbol] += 1;
}

void load_queue(const map<char, int>& lookup, tree_queue& q) {
  for (x : lookup) {
    q.push(create_leaf(x.first, x.second));
  }
}

freq_info* build_tree(tree_queue& q) {
  freq_info* ret;
  while (q.size() != 1) {
    freq_info* left = q.top();
    q.pop();
    freq_info* right = q.top();
    q.pop();
    ret = combine_nodes(left, right);
    q.push(ret);
  }
  return ret;
}

map<char, string> build_encoding_table(freq_info* root) {
  if (root->symbol != '$') {
    ret.insert(make_pair(root->symbol, s));
  }
  if (root->left) {
   s += LEFT_CHAR;
   build_encoding_table(root->left);
  }
  if (root->right) {
    s+= RIGHT_CHAR;
   build_encoding_table(root->right);
  }
  s.pop_back();
  return ret;
}

string encode(map<char, string> enc_table, string input) {
  string ret = "";
  for (x : input) {
    ret += enc_table[x];
  }
  return ret;
}

string decode(freq_info* root, string input) {
  string ret = "";
  char l = '.';
  char r = '^';
  freq_info* curs = root;
  for (x : input) {
    if (curs->symbol != '$') {
      ret += curs->symbol;
      curs = root;
    }

      if (x == l) {
        curs = curs->left;
      }
      else {
        curs = curs->right;
      }
  }
  ret += curs->symbol;
  return ret;
}
