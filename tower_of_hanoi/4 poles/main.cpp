#include <iostream>
using namespace std;

void tower_of_hanoi_4_poles(int n, char src = '1', char aux1 = '2',
                            char aux2 = '3', char dest = '4') {
  if (n == 1) {
    cout << src << " " << dest << "\n";
    return;
  }

  int k = n / 2;

  tower_of_hanoi_4_poles(k, src, aux2, dest, aux1);
  tower_of_hanoi_4_poles(n - k, src, aux2, aux1, dest);
  tower_of_hanoi_4_poles(k, aux1, src, aux2, dest);
}

int main() {
  int n;
  cin >> n;
  // cout << (1 << n) - 1 << "\n";
  tower_of_hanoi_4_poles(n);

  return 0;
}
