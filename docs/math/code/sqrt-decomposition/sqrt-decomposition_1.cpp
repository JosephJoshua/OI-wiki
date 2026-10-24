#include <iostream>

long long H(int n) {
  long long res = 0;  // stores the result
  int l = 1, r;       // left and right endpoints of the block
  while (l <= n) {
    r = n / (n / l);  // compute the right endpoint of the current block
    // add this block's contribution to the result. Multiplying by 1LL prevents overflow
    res += 1LL * (r - l + 1) * (n / l);
    l = r + 1;  // move the left endpoint to the next block
  }
  return res;
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t, n;
  std::cin >> t;
  while (t--) {
    std::cin >> n;
    std::cout << H(n) << '\n';
  }
  return 0;
}
