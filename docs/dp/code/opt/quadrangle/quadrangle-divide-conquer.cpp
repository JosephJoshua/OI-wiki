// Submission: https://loj.ac/s/2464464
#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

constexpr int N = 500010;
using val_t = long double;
constexpr val_t inf = 1e18;

// --8<-- [start:core]
val_t w(int j, int i);  // cost function
val_t f[N];             // optimal values
int opt[N];             // smallest optimal decision

// recursively solve the problems in [l,r]
// we know their smallest optimal decision points must lie in [opt_l, opt_r]
void calc(int l, int r, int opt_l, int opt_r) {
  int mid = (l + r) / 2;
  // find the optimal decision point of problem mid
  for (int j = opt_l; j <= std::min(opt_r, mid); ++j) {
    if (w(j, mid) < f[mid]) {
      f[mid] = w(j, mid);
      opt[mid] = j;
    }
  }
  // by decision monotonicity, get the decision ranges of the left and right halves, then recurse
  if (l < mid) calc(l, mid - 1, opt_l, opt[mid]);
  if (r > mid) calc(mid + 1, r, opt[mid], opt_r);
}

// solve the problems over the whole range [1,n]
void solve(int n) {
  // clear array f before each call to the recursive function
  std::fill(f + 1, f + n + 1, inf);
  // at the start, we only know that all decision points of problems [1,n] lie in [1,n]
  calc(1, n, 1, n);
}

// --8<-- [end:core]
std::function<val_t(int, int)> impl;

val_t w(int j, int i) { return impl(j, i); }

int main() {
  std::ios::sync_with_stdio(false), std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> a(n + 1), ans(n + 1);
  for (int i = 1; i <= n; ++i) std::cin >> a[i];
  impl = [&](int j, int i) -> long double {
    return a[i] - a[j] - std::sqrt((long double)(i - j));
  };
  solve(n);
  for (int i = 1; i <= n; ++i) ans[i] = std::ceil(-f[i]);
  std::reverse(a.begin() + 1, a.end());
  solve(n);
  for (int i = 1; i <= n; ++i)
    std::cout << std::max(ans[i], (int)std::ceil(-f[n + 1 - i])) << '\n';
  return 0;
}
