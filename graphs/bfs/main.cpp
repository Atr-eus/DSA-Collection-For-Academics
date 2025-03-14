#include <queue>
#include <set>
#include <vector>
using namespace std;
typedef long long ll;

void bfs(vector<ll> &adj_list, ll n, ll src, ll *dists, ll *p) {
  dists[src] = 0;
  set<ll> visited;
  queue<ll> q;
  q.push(src);

  while (!q.empty()) {
    auto v = q.front();
    q.pop();

    for (auto u : adj_list) {
      if (visited.find(u) == visited.end()) {
        visited.insert(u);
        q.push(u);

        dists[u] = dists[v] + 1;
        p[u] = v;
      }
    }
  }
}

int main() {}
