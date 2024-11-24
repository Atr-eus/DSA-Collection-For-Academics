#include <iostream>
using namespace std;

void merge(int *a, int left, int right, int mid) {
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

void merge_sort(int *a, int left, int right) {
  if (left >= right)
    return;
  int mid = left + (right - left) / 2;

  merge_sort(a, left, mid);
  merge_sort(a, mid + 1, right);
  merge(a, left, right, mid);
}

int main() {
  int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = sizeof(a) / sizeof(a[0]);

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
