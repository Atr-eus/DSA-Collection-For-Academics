#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> compute_z(const string &s) {
  int n = s.size();
  vector<int> z(n, 0);

  int l = 0, r = 0;
  for (int i = 1; i < n; ++i) {
    if (i < r) {
      z[i] = min(r - i, z[i - l]);
    }

    while (i + z[i] < n && s[z[i]] == s[i + z[i]])
      ++z[i];

    if (i + z[i] > r) {
      l = i;
      r = i + z[i];
    }
  }
  return z;
}

int main() {
  string s;
  if (!(cin >> s))
    return 0;

  auto z = compute_z(s);

  cout << "String: " << s << "\nZ-array:\n";
  for (int i = 0; i < (int)z.size(); ++i) {
    if (i)
      cout << ' ';
    cout << z[i];
  }
  cout << '\n';

  return 0;
}
