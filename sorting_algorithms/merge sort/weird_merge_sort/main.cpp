// ASSIGNMENT V: Write a modified version of merge sort where the given array is
// split into 2 subarrays, then 3, then 2 again, and so on. It is different from
// the original version where the array is always divided into two subarrays
// recursively.

#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int> &a, int left, int mid, int right) {
  int left_len = mid - left + 1;
  int right_len = right - mid;
  int l[left_len], r[right_len];
  int i, j, k = left;

  for (i = 0; i < left_len; ++i) {
    l[i] = a[left + i];
  }
  for (i = 0; i < right_len; ++i) {
    r[i] = a[mid + 1 + i];
  }

  for (i = 0, j = 0; i < left_len && j < right_len;) {
    if (l[i] <= r[j]) {
      a[k++] = l[i++];
    } else {
      a[k++] = r[j++];
    }
  }
  while (i < left_len) {
    a[k++] = l[i++];
  }
  while (j < right_len) {
    a[k++] = r[j++];
  }
}

void merge_sort(vector<int> &a, int left, int right, int turn = 2) {
  if (left >= right)
    return;

  if (turn == 2) {
    int mid = left + (right - left) / 2;

    merge_sort(a, left, mid, 3);
    merge_sort(a, mid + 1, right, 3);
    merge(a, left, mid, right);
  } else {
    int mid1 = left + (right - left) / 3;
    int mid2 = left + 2 * (right - left) / 3;

    merge_sort(a, left, mid1, 2);
    merge_sort(a, mid1 + 1, mid2, 2);
    merge_sort(a, mid2 + 1, right, 2);

    vector<int> tmp(a.begin() + left, a.begin() + right + 1);
    merge(tmp, 0, mid1 - left, mid2 - left);
    merge(tmp, 0, mid2 - left, right - left);
    for (int i = 0; i < right - left + 1; ++i) {
      a[left + i] = tmp[i];
    }
  }
}

int main() {
  vector<int> a = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = a.size();

  cout << "Unsorted:\n";
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\n";

  cout << "Sorted:\n";
  merge_sort(a, 0, n - 1);
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\n";

  return 0;
}
