// Submission: https://loj.ac/s/2464496
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

// update problem i using decision j
void check(int j, int i) {
  if (w(j, i) < f[i]) {
    f[i] = w(j, i);
    opt[i] = j;
  }
}

// recursively solve the problems in (l, r]
void calc(int l, int r) {
  int mid = (l + r + 1) / 2;
  for (int j = opt[l]; j <= opt[r]; ++j) check(j, mid);
  if (mid < r) calc(l, mid);
  for (int j = l + 1; j <= mid; ++j) check(j, r);
  if (mid > l) calc(mid, r);
}

// solve the problems in the whole range [1, n]
void solve(int n) {
  // clear array f
  std::fill(f + 1, f + n + 1, inf);
  // initialize
  check(1, 1);
  check(1, n);
  // recursively solve the problems in (1, n]
  calc(1, n);
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
