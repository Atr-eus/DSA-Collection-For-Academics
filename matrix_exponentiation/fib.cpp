// QUESTION: Find the nth fibonacchi number modulo 10^9 + 7; where F0 = 0, F1 =
// 1 and 0 <= n <= 10^18

#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;

const ll mod = 1e9 + 7;

vector<vector<ll>> mul(const vector<vector<ll>> &a,
                       const vector<vector<ll>> &b) {
  vector<vector<ll>> res(2, vector<ll>(2));
  for (int i = 0; i < 2; ++i) {
    for (int j = 0; j < 2; ++j) {
      ll sum = 0;

      for (int k = 0; k < 2; ++k) {
        sum += a[i][k] * b[k][j];
      }
      res[i][j] = sum % mod;
    }
  }

  return res;
}

vector<vector<ll>> pow(vector<vector<ll>> &a, ll b) {
  vector<vector<ll>> res = {{1, 0}, {0, 1}};

  while (b > 0) {
    if (b & 1)
      res = mul(res, a);

    a = mul(a, a);
    b >>= 1;
  }

  return res;
}

void an() {
  ll n;
  cin >> n;
  if (n == 0) {
    cout << "0\n";
    return;
  }
  if (n == 1) {
    cout << "1\n";
    return;
  }

  vector<vector<ll>> mat = {{1, 1}, {1, 0}};
  cout << (pow(mat, n - 1)[0][0] % mod + mod) % mod << "\n";
}

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);

  an();
}
