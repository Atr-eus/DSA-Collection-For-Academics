// NOTE: (i & (-i)) yields the binary value starting from the rightmost 1 bit
// Why: This happens because in two's complement, all the bits are copied from
// the original number starting from LSB upto the first 1 bit. The rest are
// flipped. Flipped bits will always yield 0 when AND operation is performed
// (A.A' = 0), and the ones that were copied will stay as they are (A.A = A),
// creating the binary value starting from the rightmost 1 bit of the original
// number.

#include <chrono>
#include <iostream>
#include <random>
#include <utility>
#include <vector>
using namespace std;
typedef chrono::high_resolution_clock clk;
typedef chrono::microseconds ms;

class BIT {
  int n;
  vector<int> bit;

public:
  BIT(int n) : n(n), bit(n + 1, 0) {};
  BIT(const int a[], int n) : n(n), bit(n + 1, 0) {
    for (int i = 0; i < n; ++i)
      bit[i + 1] = a[i];
    for (int i = 1; i <= n; ++i) {
      int j = i + (i & -i);
      if (j <= n)
        bit[j] += bit[i];
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

class SegmentTree {
  int n;
  vector<int> sum;

  void _build(const int a[], int i, int l, int r) {
    if (l == r) {
      sum[i] = a[l - 1];
      return;
    }

    int mid = l + ((r - l) >> 1);
    int lc = i << 1;
    int rc = lc | 1;
    _build(a, lc, l, mid);
    _build(a, rc, mid + 1, r);

    sum[i] = sum[lc] + sum[rc];
  }

  void _update(int i, int pos, int val, int l, int r) {
    if (l == r) {
      sum[i] += val;
      return;
    }

    int mid = l + ((r - l) >> 1);
    int lc = i << 1;
    int rc = lc | 1;
    if (pos <= mid) {
      _update(lc, pos, val, l, mid);
    } else {
      _update(rc, pos, val, mid + 1, r);
    }

    sum[i] = sum[lc] + sum[rc];
  }

  int _query(int i, int l, int r, int L, int R) {
    if (L > r || R < l)
      return 0;
    if (L <= l && R >= r)
      return sum[i];

    int mid = l + ((r - l) >> 1);
    int lc = i << 1;
    int rc = lc | 1;
    return _query(lc, l, mid, L, R) + _query(rc, mid + 1, r, L, R);
  }

public:
  SegmentTree(const int a[], int n) : n(n), sum(4 * n, 0) {
    _build(a, 1, 1, n);
  };

  void update(int pos, int val) { _update(1, pos, val, 1, n); }

  int query(int l, int r) { return _query(1, 1, n, l, r); }
};

int main() {
  const int N = 1e5, MAX_VAL = 1e3;

  mt19937_64 rng(123456789);
  uniform_int_distribution<int> val_dist(-MAX_VAL, MAX_VAL);
  uniform_int_distribution<int> idx_dist(1, N);

  int a[N];
  for (int i = 0; i < N; ++i) {
    a[i] = val_dist(rng);
  }

  pair<int, int> update_queries[N];
  for (int i = 0; i < N; ++i) {
    int pos = idx_dist(rng);
    int val = val_dist(rng);

    update_queries[i] = {pos, val};
  }

  pair<int, int> range_sum_queries[N];
  for (int i = 0; i < N; ++i) {
    int l = idx_dist(rng);
    int r = idx_dist(rng);
    if (l > r)
      swap(l, r);

    range_sum_queries[i] = {l, r};
  }

  {
    // BIT Benchmarking
    auto ts = clk::now();
    BIT bit(a, N);
    auto te = clk::now();
    auto dur = chrono::duration_cast<ms>(te - ts).count();
    cout << "[BIT] Build Time: " << dur << "µs\n";

    ts = clk::now();
    for (auto &u : update_queries) {
      auto [l, r] = u;
      bit.update(l, r);
    }
    te = clk::now();
    dur = chrono::duration_cast<ms>(te - ts).count();
    cout << "[BIT] Update Time: " << dur << "µs\n";

    ts = clk::now();
    for (auto &q : range_sum_queries) {
      auto [l, r] = q;
      bit.query_range(l, r);
    }
    te = clk::now();
    dur = chrono::duration_cast<ms>(te - ts).count();
    cout << "[BIT] Query Time: " << dur << "µs\n";
  }

  cout << "\n";

  {
    // Segment Tree Benchmarking
    auto ts = clk::now();
    SegmentTree st(a, N);
    auto te = clk::now();
    auto dur = chrono::duration_cast<ms>(te - ts).count();
    cout << "[Segment Tree] Build Time: " << dur << "µs\n";

    ts = clk::now();
    for (auto &u : update_queries) {
      auto [l, r] = u;
      st.update(l, r);
    }
    te = clk::now();
    dur = chrono::duration_cast<ms>(te - ts).count();
    cout << "[Segment Tree] Update Time: " << dur << "µs\n";

    ts = clk::now();
    for (auto &q : range_sum_queries) {
      auto [l, r] = q;
      st.query(l, r);
    }
    te = clk::now();
    dur = chrono::duration_cast<ms>(te - ts).count();
    cout << "[Segment Tree] Query Time: " << dur << "µs\n";
  }
}
