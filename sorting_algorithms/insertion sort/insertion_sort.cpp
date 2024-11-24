#include <iostream>
using namespace std;

void insertion_sort(int *a, int n) {
  int key, j;

  for (int i = 1; i < n; ++i) {
    key = a[i];

    for (j = i - 1; j >= 0 && a[j] > key; --j) {
      a[j + 1] = a[j];
    }
    a[j + 1] = key;
  }
}

int main() {
  int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = sizeof(a) / sizeof(a[0]);

  cout << "Unsorted:\n";
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";

  cout << "\nSorted:\n";
  insertion_sort(a, n);
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\n";
}
