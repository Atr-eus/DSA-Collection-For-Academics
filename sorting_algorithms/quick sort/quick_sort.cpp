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

void quick_sort(vector<int> &a, int l, int r) {
  if (l < r) {
    int j = partition(a, l, r);
    quick_sort(a, l, j - 1);
    quick_sort(a, j + 1, r);
  }
}

int main() {
  vector<int> a = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  cout << "Unsorted:\n";
  for (auto &i : a)
    cout << i << " ";

  cout << "\nSorted:\n";
  quick_sort(a, 0, a.size() - 1);
  for (auto &i : a)
    cout << i << " ";
  cout << "\n";
}
