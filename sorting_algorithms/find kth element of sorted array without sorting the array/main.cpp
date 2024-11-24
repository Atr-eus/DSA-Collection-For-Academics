// ASSIGNMENT IV: Find the element of an array that would be at kth position
// without actually sorting the array and using the concept of quicksort.
//
// => Another way to read this problem is "Find the kth smallest element of a
// given unsorted list".
//
// => This can be easily achieved by using quicksort beacuse the pivot's correct
// position is determined each time the partition() function is called. We need
// only call it repeatedly until we find the element that would be in the
// desired position in the sorted array. For this, two pointer method can be
// used find the partition where the desired element is.

#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int> &a, int l, int r) {
  int pivot = a[l];
  int i = l + 1, j = r;

  while (i <= j) {
    while (i <= r && a[i] <= pivot)
      ++i;
    while (j >= l && a[j] > pivot)
      --j;

    if (i < j) {
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);

  return j;
}

int quickfind(vector<int> &a, int n, int k) {
  int pivot_pos, l = 0, r = n - 1;
  --k;
  while (l <= r) {
    pivot_pos = partition(a, l, r);

    if (pivot_pos == k) {
      return a[k];
    } else if (pivot_pos < k) {
      l = pivot_pos + 1;
    } else {
      r = pivot_pos - 1;
    }
  }

  return -1;
}

int main() {
  vector<int> a = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int k;
  cin >> k;
  cout << k << "th element in the list: " << quickfind(a, a.size(), k) << "\n";
}
