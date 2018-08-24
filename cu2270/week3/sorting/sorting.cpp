/*

  sorting.cpp

  Please refer to sorting.h for documentation on each function.

   + ------ N O T E: -- Big scary warning! -----------------------------\
   |                                                                    |
   |    We clearly can't use unit testing to ensure that you're         |
   |    actually implementing the correct algorithm. I suppose we could |
   |    write some complicated static analysis checker. But it is       |
   |    easier to just look at it with our eyeballs.                    |
   |                                                                    |
   |    After the assignment is due, we will look at the most recent    |
   |    version of your implementation that got the highest score and   |
   |    make sure you're not doing something sneaky like using a        |
   |    standard library call to sort a vector.                         |
   |                                                                    |
   |    Anyone caught doing this (even though it is kinda funny) will   |
   |    be given 0 points on the assignment.                            |
   |                                                                    |
   `--------------------------------------------------------------------/ 

 */

#include "sorting.h"
#include <iostream>

using namespace std;

void swapper(int* x, int* y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

int quicksort_partition(vector<int> &data, int low_idx, int high_idx) {
    int pivot = data[high_idx]; 
    int i = (low_idx - 1);
 
    for (int j = low_idx; j <= high_idx- 1; j++) {
        if (data[j] <= pivot) {
            i++;
            swapper(&data[i], &data[j]);
        }
    }
    swapper(&data[i + 1], &data[high_idx]);
    return (i+1);
}
 

void quicksort(vector<int> &data, int low_idx, int high_idx) {
    if (low_idx < high_idx) {
        int part = quicksort_partition(data, low_idx, high_idx);
        quicksort(data, low_idx, part - 1);
        quicksort(data, part + 1, high_idx);
    }
}

void bubblesort(vector<int> &data) {
  int a = 0;
  int temp;
  for(int i=0; i < data.size()-1; i++) {
    if (data[i] > data[i+1]) {
      temp = data[i];
      data[i] = data[i+1];
      data[i+1] = temp;
      a++;
    }
  }
  if (a == 0) return;
  else return bubblesort(data);
}

vector<int> myMerge(vector<int> l, vector<int> r) {
  vector<int>ret; 
  int left = 0, right = 0;
  while (left < l.size() && right < r.size()) {
    if (l[left] <= r[right]) {
      ret.push_back(l[left]);
      left++;
    }
    else {
      ret.push_back(r[right]);
      right++;
    }
  }
  while (left < l.size()) {
    ret.push_back(l[left]);
    left++;
  }
  while (right < r.size()) {
    ret.push_back(r[right]);
    right++;
  }
  return ret;
}

void mergesort(vector<int> &data) {
  if(data.size() <= 1) return; 
  int mid = data.size() / 2;
  vector<int> left = vector<int>(data.begin(), data.begin() + mid);
  vector<int> right = vector<int>(data.begin()+ mid, data.end());
  mergesort(left);
  mergesort(right);
  data = myMerge(left, right);
}

vector<int> merge(vector<int> &left, vector<int> &right) {
  int l = 0;
  int r = 0;
  vector<int> ret;
  while (l<left.size() && r<right.size()) {
    if (left[l] <= right[r]) {
      ret.push_back(left[l]);
      l++;
    }
    else {
      ret.push_back(right[r]);
      r++;
    }
  }
  for (int i=0; i<ret.size(); i++) {
    cout << ret[i] << endl;
  }
  cout << endl << endl;
  return ret;
}

int findMin(vector<int> data) {
  int min = data[0];
  int index = 0;
  for (int i=0; i < data.size(); i++) {
    if (data[i] < min) {
      min = data[i];
      index = i;
    } 
  }
  return index;
}

void mystery_sort(vector<int> &data) {
  /* Selection Sort Attempt
  Uses a helper function defined above, findMin()*/
  vector<int> final;
  while (data.size() != 0) {
    int min = findMin(data);
    final.push_back(data[min]);
    data.erase(data.begin() + min);
  }
  data = final;
}


