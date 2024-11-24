#include <iostream>
using namespace std;

void selection_sort(int *a, int n) {
  int *min_element;
  for (int i = 0; i < n - 1; ++i) {
    min_element = a + i;

    for (int j = i + 1; j < n; ++j) {
      if (*(a + j) < *min_element) {
        min_element = a + j;
      }
    }

    if (*min_element != *(a + i)) {
      *min_element ^= *(a + i);
      *(a + i) ^= *min_element;
      *min_element ^= *(a + i);
    }
  }
}

int main() {
  int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = 10;
  cout << "Unsorted:\n";
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\nSorted:\n";
  selection_sort(a, n);
  for (int i = 0; i < n; ++i)
    cout << a[i] << " ";
  cout << "\n";
}
