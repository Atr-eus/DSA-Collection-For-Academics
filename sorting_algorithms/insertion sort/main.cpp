#include <iostream>
#include <vector>
using namespace std;

vector<int> insertion_sort(vector<int> a, int n) {
  for (int i = 1; i < n; ++i) {
    int j, key = a[i];
    for (j = i - 1; j >= 0 && a[j] > key; --j) {
      a[j + 1] = a[j];
    }
    a[j + 1] = key;
  }
  return a;
}
vector<int> insertion_sort_dec(vector<int> a, int n) {
  for (int i = n - 2; i >= 0; --i) {
    int j, key = a[i];
    for (j = i + 1; j < n && a[j] > key; ++j) {
      a[j - 1] = a[j];
    }
    a[j - 1] = key;
  }
  return a;
}

int main() {
  vector<int> a = {2, 5, 3, 10, 4, 7, 9, 8, 1, 6};
  // iter 1;
  // i = 1, key = a[i] = 5
  //      niter 1 (doesn't happen);
  //      j = i - 1 = 0, a[j] = 2
  //      j >= 0 yes, a[j] > key no
  // a[j + 1] = key
  // or, a[1] = 5
  // or, pos of 5 = 5
  // after iter 1, a = {2, 5, 3, 10, 4, 7, 9, 8, 1, 6}
  //
  // iter 2;
  // i = i + 1 = 2, key = a[i] = 3
  //      niter 1;
  //      j = i - 1 = 1, a[j] = 5
  //      j >= 0 yes, a[j] > key yes
  //      so, a[j + 1] = a[j]
  //      or, a[2] = 5
  //      or, pos of 3 = 5
  //      j = j - 1 = 0 (niter 2; j >= 0 yes, a[j] > key no)
  // a[j + 1] = key
  // or, a[1] = 3
  // or, pos of 5 = 3
  // after iter 2, a = {2, 3, 5, 10, 4, 7, 9, 8, 1, 6}
  //
  // iter 3;
  // i = i + 1 = 3, key = a[i] = 10
  //      niter 1 (doesn't happen);
  //      j = i - 1 = 2, a[j] = 5
  //      j >= 0 yes, a[j] > key no
  // a[j + 1] = key
  // or, a[3] = 10
  // or, pos of 10 = 10
  // after iter 3, a = {2, 3, 5, 10, 4, 7, 9, 8, 1, 6}
  //
  // iter 4;
  // i = i + 1 = 4, key = a[i] = 4
  //      niter 1;
  //      j = i - 1 = 3, a[j] = 10
  //      j >= 0 yes, a[j] > key yes
  //      so, a[j + 1] = a[j]
  //      or, a[4] = 10
  //      or, pos of 4 = 10
  //
  //      niter 2;
  //      j = j - 1 = 2, a[j] = 5
  //      j >= 0 yes, a[j] > key yes
  //      so, a[j + 1] = a[j]
  //      or, a[3] = 5
  //      or, pos of 10 = 5
  //      j = j - 1 = 1 (niter 3; j >= 0 yes, a[j] > key no)
  // a[j + 1] = key
  // or, a[2] = 4
  // or, pos of 5 = 4
  // after iter 2, a = {2, 3, 4, 5, 10, 7, 9, 8, 1, 6}
  //
  // ... and so on

  cout << "Unsorted list:\n";
  for (auto i : a) {
    cout << i << " ";
  }
  cout << "\n";
  a = insertion_sort(a, a.size());
  cout << "Sorted list:\n";
  for (auto i : a) {
    cout << i << " ";
  }
  cout << "\n";
  a = insertion_sort_dec(a, a.size());
  cout << "Sorted list (decreasing order):\n";
  for (auto i : a) {
    cout << i << " ";
  }
  cout << "\n";

  return 0;
}
