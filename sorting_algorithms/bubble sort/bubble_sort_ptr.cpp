#include <iostream>
using namespace std;

void bubble_sort(int *a, int n) {
  for (int i = 0; i < n - 1; ++i) {
    for (int j = 0; j < n - i - 1; ++j) {
      if (*(a + j) > *(a + j + 1)) {
        *(a + j) ^= *(a + j + 1);
        *(a + j + 1) ^= *(a + j);
        *(a + j) ^= *(a + j + 1);
      }
    }
  }
}

int main() {
  int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = 10;
  cout << "Unsorted:\n";
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\n";
  cout << "Sorted:\n";
  bubble_sort(a, n);
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
}
