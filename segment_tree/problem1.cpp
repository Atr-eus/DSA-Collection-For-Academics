// QUESTION: Optimize the following loop:
// for (int i = L; i <= R; i++) data[i] += i;

#include <cstddef>
#include <iostream>
using namespace std;
typedef long long ll;

ll a[] = {-1, 8, 5, 6, 3, 4, 2, 1, 7};
constexpr size_t n = sizeof(a) / sizeof(a[0]);

ll sum[4 * n], lz[4 * n];

inline ll sum_range(ll l, ll r) {
  return (r * (r + 1) / 2) - ((l - 1) * l / 2);
}

// each node contains:
// starting point
// ending point
// sum of the elements in that range
// lazy value
void build(ll i, ll l, ll r) {
  lz[i] = 0;

  // leaf node
  if (l == r) {
    sum[i] = a[l];
    return;
  }

  ll mid = l + ((r - l) >> 1);
  ll l_cld = i << 1;
  ll r_cld = l_cld | 1;

  build(l_cld, l, mid);
  build(r_cld, mid + 1, r);

  sum[i] = sum[l_cld] + sum[r_cld];
}

void lazy_propagate(ll i, ll l, ll r) {
  if (lz[i] == 0)
    return;
  // leaf node
  if (l == r) {
    lz[i] = 0;
    return;
  }

  ll mid = l + ((r - l) >> 1);
  ll l_cld = i << 1;
  ll r_cld = l_cld | 1;

  sum[l_cld] += sum_range(l, mid) * lz[i];
  lz[l_cld] += lz[i];

  sum[r_cld] += sum_range(mid + 1, r) * lz[i];
  lz[r_cld] += lz[i];

  lz[i] = 0;
}

// [L, R] is the range of the original update operation
// [l, r] is the range of the current node in the recursion, starting from [1, n
// - 1]
void update(ll i, ll l, ll r, ll L, ll R) {
  // no overlap
  if (L > r || R < l)
    return;

  // total overlap
  if (L <= l && R >= r) {
    // O(1) calculation of arithmetic progression
    sum[i] += sum_range(l, r);
    lz[i] += 1;

    return;
  }

  // partial overlap
  lazy_propagate(i, l, r);

  ll mid = l + ((r - l) >> 1);
  ll l_cld = i << 1;
  ll r_cld = l_cld | 1;
  update(l_cld, l, mid, L, R);
  update(r_cld, mid + 1, r, L, R);

  sum[i] = sum[l_cld] + sum[r_cld];
}

ll query(ll i, ll l, ll r, ll L, ll R) {
  if (L > r || R < l)
    return 0;

  if (L <= l && R >= r) {
    return sum[i];
  }

  lazy_propagate(i, l, r);

  ll mid = l + ((r - l) >> 1);
  ll l_cld = i << 1;
  ll r_cld = l_cld | 1;
  return query(l_cld, l, mid, L, R) + query(r_cld, mid + 1, r, L, R);
}

void print() {
  cout << "IDX: ";
  for (ll i = 1; i < n; ++i) {
    cout << i << " ";
  }
  cout << "\n";

  cout << "ELM: ";
  for (ll i = 1; i < n; ++i) {
    cout << a[i] << " ";
  }
  cout << "\n";
}

int main() {
  build(1, 1, n - 1);
  cout << query(1, 1, n - 1, 1, 4) << "\n";
  update(1, 1, n - 1, 1, 4);
  cout << query(1, 1, n - 1, 1, 4) << "\n";
}
