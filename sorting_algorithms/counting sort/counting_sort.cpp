#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

vector<int> counting_sort(vector<int> &a, int n) {
  int m = *max_element(a.begin(), a.end());

  vector<int> rec(m + 1, 0);
  for (int i = 0; i < n; ++i) {
    rec[a[i]]++;
  }
  for (int i = 1; i < m + 1; ++i) {
    rec[i] += rec[i - 1];
  }

  vector<int> res(n);
  for (int i = n - 1; i >= 0; --i) {
    res[--rec[a[i]]] = a[i];
  }

  return res;
}

int main() {
  vector<int> a = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

  cout << "Unsorted:\n";
  for (auto &i : a)
    cout << i << " ";

  cout << "\nSorted:\n";
  auto res = counting_sort(a, a.size());
  for (auto &i : res)
    cout << i << " ";
  cout << "\n";
}
