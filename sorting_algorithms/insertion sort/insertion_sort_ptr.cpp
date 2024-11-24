#include <iostream>
using namespace std;

void insertion_sort(int *a, int n) {
  int key, j;

  for (int i = 1; i < n; ++i) {
    key = *(a + i);
    j = i - 1;

    while (j >= 0 && *(a + j) > key) {
      *(a + j + 1) = *(a + j);
      --j;
    }
    *(a + j + 1) = key;
  }
}

int main() {
  int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = 10;
  cout << "Unsorted:\n";
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\nSorted:\n";
  insertion_sort(a, n);
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\n";
}
