#include <iostream>
using namespace std;

void selection_sort(int *a, int n) {
  int min_idx, i, j;

  for (i = 0; i < n - 1; ++i) {
    min_idx = i;

    for (j = i + 1; j < n; ++j) {
      if (a[j] < a[min_idx]) {
        min_idx = j;
      }
    }

    if (min_idx != i) {
      swap(a[i], a[min_idx]);
    }
  }
}

int main() {
  int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = sizeof(a) / sizeof(a[0]);

  cout << "Unsorted:\n";
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";

  cout << "\nSorted:\n";
  selection_sort(a, n);
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\n";
}
