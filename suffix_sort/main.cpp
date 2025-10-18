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
      int bkt_b = (b + l < n) ? bkt[b + l] : -1;
      return bkt_a < bkt_b;
    });

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

bool cmp_sfx(const string &s, const string &p, int st) {
  int i, j;
  for (i = st, j = 0; i < s.size() && j < p.size(); ++i, ++j) {
    if (s[i] < p[j])
      return true;
    if (s[i] > p[j])
      return false;
  }

  if (j == p.size())
    return false;
  return (i == s.size() && j < p.size());
}

bool starts_with(const string &s, const string &p, int st) {
  if (st + p.size() > s.size())
    return false;

  for (int i = 0; i < p.size(); ++i)
    if (s[st + i] != p[i])
      return false;
  return true;
}

bool has_pattern(const string &s, const string &p) {
  auto sfx = build(s);
  int l = 0, r = sfx.size(), m;

  for (auto &i : sfx) {
    cout << (i + 1) << ": " << s.substr(i) << "\n";
  }

  while (l < r) {
    m = l + ((r - l) >> 1);

    if (cmp_sfx(s, p, sfx[m]))
      l = m + 1;
    else
      r = m;
  }

  if (l == sfx.size())
    return false;
  return starts_with(s, p, sfx[l]);
}

int main() {
  string s, p;
  cin >> s;
  cin >> p;

  if (has_pattern(s, p)) {
    cout << s << " has pattern " << p << ".\n";
  } else {
    cout << s << " doesn't have pattern " << p << ".\n";
  }
  return 0;
}
