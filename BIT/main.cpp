// NOTE: (i & (-i)) yields the binary value starting from the rightmost 1 bit
// Why: This happens because in two's complement, all the bits are copied from
// the original number starting from LSB upto the first 1 bit. The rest are
// flipped. Flipped bits will always yield 0 when AND operation is performed
// (A.A' = 0), and the ones that were copied will stay as they are (A.A = A),
// creating the binary value starting from the rightmost 1 bit of the original
// number.

#include <iostream>
#include <vector>
using namespace std;

class BIT {
  int n;
  vector<int> bit;

public:
  BIT(int n) : n(n), bit(n + 1, 0) {};
  BIT(const int a[], int n) : n(n), bit(n + 1, 0) {
    for (int i = 0; i < n; ++i) {
      update(i + 1, a[i]);
    }
  };

  void update(int i, int val) {
    while (i <= n) {
      bit[i] += val;
      i += i & (-i);
    }
  }

  int query(int i) {
    int s = 0;

    while (i > 0) {
      s += bit[i];
      i -= i & (-i);
    }
    return s;
  }

  int query_range(int l, int r) { return query(r) - query(l - 1); }
};

int main() {
  int a[] = {-2, 1, 2, 3, -1, 1, -2, 3, 2, 1, 1, 3};
  BIT bit(a, sizeof(a) / sizeof(a[0]));

  cout << bit.query_range(1, 12) << "\n";
  bit.update(4, 5);
  cout << bit.query_range(1, 12) << "\n";
}
