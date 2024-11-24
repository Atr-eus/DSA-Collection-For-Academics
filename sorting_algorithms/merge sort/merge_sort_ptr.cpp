#include <iostream>
using namespace std;

void merge(int *a, int *l, int *r, int l_len, int r_len) {
  int *i = l, *j = r, *k = a;

  while (i < l + l_len && j < r + r_len) {
    if (*i <= *j) {
      *k++ = *i++;
    } else {
      *k++ = *j++;
    }
  }
  while (i < l + l_len) {
    *k++ = *i++;
  }
  while (j < r + r_len) {
    *k++ = *j++;
  }
}

void merge_sort(int *a, int n) {
  if (n <= 1)
    return;

  int m = n / 2;
  int *l = new int[m];
  int *r = new int[n - m];

  int *p_l = l;
  int *p_r = r;

  for (int i = 0; i < m; ++i) {
    *p_l++ = *a++;
  }
  for (int i = m; i < n; ++i) {
    *p_r++ = *a++;
  }

  merge_sort(l, m);
  merge_sort(r, n - m);
  merge(a - n, l, r, m, n - m);

  delete[] l;
  delete[] r;
}

void display_a(int *a, int n) {
  for (int *i = a; i < a + n; ++i)
    cout << *i << " ";
  cout << "\n";
}

int main() {
  int a[] = {10, 9, 8, 7, 6, 5, 4, 3, 2, 1};
  int n = sizeof(a) / sizeof(a[0]);

  display_a(a, n);
  merge_sort(a, n);
  display_a(a, n);

  return 0;
}
