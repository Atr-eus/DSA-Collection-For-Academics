#include <iostream>
using namespace std;

void tower_of_hanoi(int n, char src = '1', char aux = '2', char dest = '3') {
  if (n == 1) {
    cout << src << " " << dest << "\n";
    return;
  }

  tower_of_hanoi(n - 1, src, dest, aux);
  cout << src << " " << dest << "\n";
  tower_of_hanoi(n - 1, aux, src, dest);
}

int main() {
  int n;
  cin >> n;
  cout << (1 << n) - 1 << "\n";
  tower_of_hanoi(n);

  return 0;
}
