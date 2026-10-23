#include <iostream>

int main() {
  int n = 0, u = 0, d = 0;
  std::cin >> u >> d >> n;
  int time = 0, dist = 0;
  while (true) {  // enumerate with an infinite loop
    dist += u;
    time++;
    if (dist >= n) break;  // leave the loop once the condition holds
    dist -= d;
  }
  std::cout << time << '\n';  // print the result
  return 0;
}
