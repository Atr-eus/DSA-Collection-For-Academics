// Appropriate when there is no update operation on the nodes.
// O(2V) -> O(V)

#include <cstring>
#include <iostream>
using namespace std;

constexpr int n = 9;
int t[] = {-1, 3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4};
int st[n], ed[n], ft[2 * n], ps[2 * n];
int tim;

// O(V + E) -> O(V), as E <= 2V
void dfs(int i) {
  if (i >= sizeof(t) / sizeof(t[0]))
    return;

  int v = t[i];
  if (v == -1)
    return;

  int l = 2 * i;
  int r = 2 * i + 1;

  ft[tim] = v;
  st[v] = ++tim;

  if (l < sizeof(t) / sizeof(t[0]))
    dfs(l);
  if (r < sizeof(t) / sizeof(t[0]))
    dfs(r);

  ft[tim] = -v;
  ed[v] = tim++;
}

// O(1)
int subtree_sum(int v) { return ps[ed[v]] - ps[st[v] - 1] + v; }

int main() {
  memset(st, -1, sizeof(st));
  memset(ed, -1, sizeof(ed));
  memset(ft, -1, sizeof(ft));
  memset(ps, -1, sizeof(ps));
  tim = 0;

  dfs(1);

  // O(V);
  ps[0] = ft[0];
  for (int i = 1; i < 2 * n; ++i) {
    if (ft[i] < 0)
      ps[i] = ps[i - 1];
    else
      ps[i] = ps[i - 1] + ft[i];
  }

  for (int i = 0; i < n; ++i) {
    cout << "subtree_sum(" << i << ") = " << subtree_sum(i) << "\n";
  }
}
