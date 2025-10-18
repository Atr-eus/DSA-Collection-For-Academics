#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

void dfs1(int v, const vector<vector<int>> &adj, vector<bool> &vis,
          vector<int> &ord) {
  vis[v] = true;

  for (auto &u : adj[v]) {
    if (!vis[u])
      dfs1(u, adj, vis, ord);
  }

  ord.emplace_back(v);
}

void dfs2(int v, const vector<vector<int>> &adj, vector<bool> &vis,
          vector<int> &scc) {
  vis[v] = true;
  scc.emplace_back(v);

  for (auto &u : adj[v]) {
    if (!vis[u])
      dfs2(u, adj, vis, scc);
  }
}

int main() {
  // https://cp-algorithms.com/graph/strongly-connected-components-tikzpicture/graph.svg
  vector<vector<int>> adj = {{1, 7},    {2, 1}, {1, 5},    {2, 4}, {9},
                             {3, 6, 9}, {2},    {0, 6, 8}, {6, 9}, {4}};

  int n = adj.size();

  vector<bool> vis(n, false);
  vector<int> ord;
  for (int v = 0; v < n; ++v) {
    if (!vis[v])
      dfs1(v, adj, vis, ord);
  }

  vector<vector<int>> adjt(n);
  for (int v = 0; v < n; ++v) {
    for (auto &u : adj[v])
      adjt[u].emplace_back(v);
  }

  fill(vis.begin(), vis.end(), 0);
  reverse(ord.begin(), ord.end());

  vector<vector<int>> sccs;
  for (int v : ord) {
    if (!vis[v]) {
      vector<int> scc;

      dfs2(v, adjt, vis, scc);
      sccs.emplace_back(scc);
    }
  }

  cout << "Found " << sccs.size() << " strongly connected components:\n";
  for (size_t i = 0; i < sccs.size(); ++i) {
    cout << "SCC " << (i + 1) << ": ";

    for (int x : sccs[i])
      cout << x << " ";
    cout << "\n";
  }

  return 0;
}
