#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> build(const string &s) {
  int n = s.size();
  vector<int> res(n), bkt(n), tmp(n);

  // init
  for (int i = 0; i < n; ++i) {
    res[i] = i;
    bkt[i] = (unsigned char)s[i];
  }

  for (int l = 1; l < n; l <<= 1) {
    // sort the suffix array depending on rank of first half, or rank of
    // second half if the former is equal
    sort(res.begin(), res.end(), [&](int a, int b) {
      if (bkt[a] != bkt[b])
        return bkt[a] < bkt[b];

      int bkt_a = (a + l < n) ? bkt[a + l] : -1;
      int bck_b = (b + l < n) ? bkt[b + l] : -1;
      return bkt_a < bck_b;
    });
    for (auto &i : res)
      cout << i + 1 << " ";
    cout << "\n";

    // assign new ranks
    tmp[res[0]] = 0;
    for (int i = 1; i < n; ++i) {
      int ci = res[i];
      int pi = res[i - 1];
      int c_bkt = bkt[ci];
      int p_bkt = bkt[pi];
      int c_bktt = (ci + l < n) ? bkt[ci + l] : -1;
      int p_bktt = (pi + l < n) ? bkt[pi + l] : -1;

      tmp[ci] = tmp[pi] + ((c_bkt != p_bkt || c_bktt != p_bktt) ? 1 : 0);
    }
    bkt = tmp;

    // all ranks are distinct - it's done
    if (bkt[res.back()] == n - 1)
      break;
  }

  return res;
}

int main() {
  string s;
  cin >> s;
  auto res = build(s);

  for (auto &i : res) {
    cout << (i + 1) << ": " << s.substr(i) << "\n";
  }
  return 0;
}
