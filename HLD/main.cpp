#include <iostream>
#include <vector>
using namespace std;

// https://cp-algorithms.com/graph/hld.png
vector<vector<int>> adj = {{1, 2, 3},
                           {0, 4, 5},
                           {0, 6, 7},
                           {0},
                           {1},
                           {1, 8, 9},
                           {2, 10},
                           {2, 11},
                           {5},
                           {5},
                           {6, 12, 13, 14},
                           {7},
                           {10},
                           {10, 15},
                           {10},
                           {13}};
int n = adj.size();
vector<int> st_size(n, 0), parent(n, -1), depth(n, 0), heavy(n, -1),
    head(n, -1), pos(n, -1);

// NOTE: A heavy edge is defined by:
// edge (u, v) is heavy iff st_size[u] >= st_size[v] / 2 holds such that v is
// the parent of u. Each vertex can have at most 1 heavy edge going
// downward. Otherwise, st_size[v] >= 1 + 2 * st_size[v] > s[v], which leads to
// a contradiction. Therefore, the selection can be simplified to "the child of
// vectex v that has the largest subtree size".

// The following function does two things:
// 1. Find the subtree sum of each node
// 2. Find the maximum subtree sum of every child of any given vertex v, and
// find the maximum. If the child with maximum subtree size is u, edge (u, v)
// is the only heavy edge emanating from v.

void find_heavy_edges(int v, int p = -1) {
  parent[v] = p;
  st_size[v] = 1;
  int max_st_size = 0;

  for (auto &u : adj[v]) {
    if (u == p)
      continue;

    depth[u] = depth[v] + 1;
    find_heavy_edges(u, v);
    st_size[v] += st_size[u];

    if (st_size[u] > max_st_size) {
      max_st_size = st_size[u];
      heavy[v] = u;
    }
  }
}

// The following function assigns each vertex to a chian. A chain is essentially
// a path that goes through heavy edges. Each chain has a head node which has
// the highest level out of any node in that particular chain. We'd also like to
// flatten the tree to an array, so we can later use Segment/Fenwick tree.

int cpos = 0;
void decompose(int v, int h = 0) {
  head[v] = h;
  pos[v] = cpos++;

  if (heavy[v] != -1) {
    decompose(heavy[v], h);
  }

  for (auto &u : adj[v]) {
    if (u == parent[v] || u == heavy[v])
      continue;

    decompose(u, u);
  }
}

class SegmentTree {
  int n;
  vector<int> st, lz;

  void build(int i, int l, int r, const vector<int> &a) {
    if (l == r) {
      st[i] = a[l];
      return;
    }

    int m = l + ((r - l) >> 1);
    build(i << 1, l, m, a);
    build(i << 1 | 1, m + 1, r, a);
    st[i] = st[i << 1] + st[i << 1 | 1];
  }

  void lazy_propagate(int i, int l, int r) {
    if (lz[i] == 0)
      return;

    st[i] += (r - l + 1) * lz[i];
    if (l != r) {
      lz[i << 1] += lz[i];
      lz[i << 1 | 1] += lz[i];
    }

    lz[i] = 0;
  }

  void _update(int i, int l, int r, int L, int R, int val) {
    if (R < l || L > r)
      return;
    if (L <= l && r <= R) {
      lz[i] += val;
      lazy_propagate(i, l, r);
      return;
    }

    int m = l + ((r - l) >> 1);
    _update(i << 1, l, m, L, R, val);
    _update(i << 1 | 1, m + 1, r, L, R, val);
    st[i] = st[i << 1] + st[i << 1 | 1];
  }

  int _query(int i, int l, int r, int L, int R) {
    if (R < l || L > r)
      return 0;
    if (L <= l && r <= R)
      return st[i];

    int m = l + ((r - l) >> 1);
    return _query(i << 1, l, m, L, R) + _query(i << 1 | 1, m + 1, r, L, R);
  }

public:
  SegmentTree(const vector<int> &a) : n(a.size()), st(4 * n, 0), lz(4 * n, 0) {
    if (n > 0)
      build(1, 0, n - 1, a);
  }

  void update(int l, int r, int val) { _update(1, 0, n - 1, l, r, val); }

  int query(int l, int r) { return _query(1, 0, n - 1, l, r); }
};

void path_update(SegmentTree &st, int u, int v, int val) {
  while (head[u] != head[v]) {
    if (depth[head[u]] < depth[head[v]]) {
      swap(u, v);
    }

    st.update(pos[head[u]], pos[u], val);
    u = parent[head[u]];
  }

  if (depth[u] > depth[v]) {
    swap(u, v);
  }

  st.update(pos[u] + 1, pos[v], val);
}

long long path_query(SegmentTree &st, int u, int v) {
  long long res = 0;

  while (head[u] != head[v]) {
    if (depth[head[u]] < depth[head[v]]) {
      swap(u, v);
    }

    res += st.query(pos[head[u]], pos[u]);
    u = parent[head[u]];
  }

  if (depth[u] > depth[v]) {
    swap(u, v);
  }
  res += st.query(pos[u] + 1, pos[v]);

  return res;
}

int main() {
  find_heavy_edges(0);
  decompose(0, 0);

  vector<int> a(n, 0);
  for (int v = 1; v < n; ++v) {
    a[pos[v]] = 2 + v;
  }

  SegmentTree seg(a);

  cout << path_query(seg, 8, 14) << "\n";
  path_update(seg, 8, 14, 5);
  cout << path_query(seg, 8, 14) << "\n";

  return 0;
}
