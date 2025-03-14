// QUESTION: Optimize the following loop:
// for (int i = L; i <= R; i++) data[i] += i;

#include <cstddef>
#include <iostream>
using namespace std;
typedef long long ll;

ll a[] = {-1, 8, 5, 6, 3, 4, 2, 1, 7};
constexpr size_t n = sizeof(a) / sizeof(a[0]);

ll st[4 * n], ed[4 * n], sum[4 * n], lz[4 * n];

inline ll sum_range(ll l, ll r) {
  return (r * (r + 1) / 2) - ((l - 1) * l / 2);
}

// each node contains:
// starting point
// ending point
// sum of the elements in that range
// lazy value
void build(ll i, ll l, ll r) {
  st[i] = l;
  ed[i] = r;
  lz[i] = 0;

  // leaf node
  if (l == r) {
    sum[i] = a[l];
    return;
  }

  ll l_cld = 2 * i;
  ll r_cld = 2 * i + 1;
  ll mid = l + (r - l) / 2;

  build(l_cld, l, mid);
  build(r_cld, mid + 1, r);

  sum[i] = sum[l_cld] + sum[r_cld];
}

void lazy_propagate(ll i) {
  if (lz[i] == 0)
    return;

  ll l_cld = 2 * i;
  ll r_cld = 2 * i + 1;

  sum[l_cld] += sum_range(st[l_cld], ed[l_cld]) * lz[i];
  sum[r_cld] += sum_range(st[r_cld], ed[r_cld]) * lz[i];

  lz[l_cld] += lz[i];
  lz[r_cld] += lz[i];

  lz[i] = 0;
}

void update(ll i, ll l, ll r) {
  // no overlap
  if (l > ed[i] || r < st[i])
    return;

  // total overlap
  if (l <= st[i] && r >= ed[i]) {
    // O(1) calculation of arithmetic progression
    sum[i] += sum_range(st[i], ed[i]);
    lz[i] += 1;

    return;
  }

  // partial overlap
  lazy_propagate(i);

  ll l_cld = 2 * i;
  ll r_cld = 2 * i + 1;
  update(l_cld, l, r);
  update(r_cld, l, r);

  sum[i] = sum[l_cld] + sum[r_cld];
}

ll query(ll i, ll l, ll r) {
  if (l > ed[i] || r < st[i])
    return 0;

  if (l <= st[i] && r >= ed[i])
    return sum[i];

  lazy_propagate(i);

  ll l_cld = 2 * i;
  ll r_cld = 2 * i + 1;
  return query(l_cld, l, r) + query(r_cld, l, r);
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
  cout << query(1, 1, 4) << "\n";
  update(1, 1, 4);
  cout << query(1, 1, 4) << "\n";
}
