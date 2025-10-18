#include <bits/stdc++.h>
using namespace std;

void dfs(int v, int p, vector<vector<int>> &adj, vector<int> &dt,
         vector<int> &lv, vector<bool> &is_artp, int &tim) {
  dt[v] = lv[v] = tim++;
  int cld = 0;

  for (auto &u : adj[v]) {
    if (u == p)
      continue;

    if (dt[u] == -1) {
      cld++;

      dfs(u, v, adj, dt, lv, is_artp, tim);
      lv[v] = min(lv[v], lv[u]);

      if (p != -1 && lv[u] >= dt[v])
        is_artp[v] = true;
    } else {
      lv[v] = min(lv[v], dt[u]);
    }
  }

  if (p == -1 && cld > 1)
    is_artp[v] = true;
}

int main() {
  vector<vector<int>> adj = {{1}, {0, 4}, {3, 4}, {2, 4}, {1, 2, 3}};

  int n = adj.size();

  vector<int> dt(n, -1), low(n);
  vector<bool> is_artp(n, false);
  int tim = 0;

  for (int i = 0; i < n; ++i) {
    if (dt[i] == -1)
      dfs(i, -1, adj, dt, low, is_artp, tim);
  }

  cout << "Articulation Points:\n";
  for (int i = 0; i < n; ++i)
    if (is_artp[i])
      cout << i << " ";
  cout << "\n";

  return 0;
}
