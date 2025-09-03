// Problem: Construct the sparse table of a tree, and use binary lifting
// technique to find the LCA (Lowest Common Ancestor) or any two nodes.

#include <cstring>
#include <iostream>
#include <vector>
using namespace std;

constexpr int n = 13, log2n = 3;

vector<int> tree[n + 1] = {{},       {2, 3, 4}, {}, {5, 6, 7}, {}, {}, {8, 9},
                           {10, 11}, {},        {}, {12, 13},  {}, {}, {}};
int up[n + 1][log2n];
int lev[n + 1];

void dfs(int v, int p) {
  up[v][0] = p;

  for (int i = 1; i < log2n; ++i) {
    if (up[v][i - 1] == -1) {
      up[v][i] = -1;
    } else {
      up[v][i] = up[up[v][i - 1]][i - 1];
    }
  }

  for (int cld : tree[v]) {
    lev[cld] = lev[v] + 1;
    dfs(cld, v);
  }
}

int binary_lift(int v, int k) {
  for (int i = 0; i < log2n && v != -1; ++i) {
    if (k & (1 << i)) {
      v = up[v][i];
    }
  }

  return v;
}

int lca(int u, int v) {
  if (lev[u] > lev[v])
    swap(u, v);

  v = binary_lift(v, lev[v] - lev[u]);
  if (u == v)
    return u;

  for (int i = log2n - 1; i >= 0; --i) {
    if (up[v][i] == up[u][i])
      continue;

    u = up[u][i];
    v = up[v][i];
  }

  return up[u][0];
}

int main() {
  memset(up, -1, sizeof(up));
  lev[1] = 0;
  dfs(1, -1);

  int q;
  cin >> q;
  while (q--) {
    int u, v;
    cin >> u >> v;
    cout << lca(u, v) << "\n";
  }
}
