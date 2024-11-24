#include <iostream>
#include <string>
#include <vector>
using namespace std;

int first_pattern_matching_algorithm(const string &T, const string &P) {
  int K = 1, R = P.size(), S = T.size(), MAX = S - R + 1;

  while (K <= MAX) {
    int L;
    for (L = 1; L <= R && P[L - 1] == T[K + L - 2]; ++L)
      ;

    if (L > R)
      return K;
    K = K + 1;
  }

  return 0;
}

vector<int> get_pattern_table(const string &P) {
  int M = P.size(), len = 0;
  vector<int> TABLE(M, 0);

  for (int i = 1; i < M;) {
    if (P[i] == P[len]) {
      TABLE[i++] = ++len;
    } else {
      if (len == 0) {
        TABLE[i++] = 0;
      } else {
        len = TABLE[len - 1];
      }
    }
  }

  return TABLE;
}
int second_pattern_matching_algorithm(const string &T, const string &P) {
  int N = T.size(), M = P.size();
  auto TABLE = get_pattern_table(P);

  cout << "\nPATTERN TABLE\n";
  for (int i = 0; i < M; ++i) {
    cout << P[i] << " ";
  }
  cout << "\n";
  for (auto &i : TABLE) {
    cout << i << " ";
  }
  cout << "\n";

  int i = 0, j = 0;
  while (i < N) {
    if (T[i] == P[j]) {
      ++i, ++j;

      if (j == M) {
        return i - j + 1;
      }
    } else {
      if (j == 0) {
        ++i;
      } else {
        j = TABLE[j - 1];
      }
    }
  }

  return 0;
}

int main() {
  string s = "ababcabcabababdaaaabababa", sub = "aaaabababa";
  cout << "POS = " << first_pattern_matching_algorithm(s, sub) << "\n";
  cout << "POS = " << second_pattern_matching_algorithm(s, sub) << "\n";
}
