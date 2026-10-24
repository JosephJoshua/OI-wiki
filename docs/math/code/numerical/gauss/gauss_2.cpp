#include <bitset>
#include <iostream>
#include <utility>
#include <vector>

// --8<-- [start:core]
std::bitset<1010> matrix[2010];  // augmented matrix; position 0 holds the constant term

// n is the number of unknowns, m is the number of equations; returns the solution
// returns an empty vector if there are infinitely many solutions or none
std::vector<bool> GaussJordanElimination(int n, int m) {
  for (int i = 1; i <= n; i++) {
    int cur = i;
    while (cur <= m && !matrix[cur].test(i)) cur++;
    if (cur > m) return std::vector<bool>(0);
    if (cur != i) swap(matrix[cur], matrix[i]);
    for (int j = 1; j <= m; j++)
      if (i != j && matrix[j].test(i)) matrix[j] ^= matrix[i];
  }
  // the remaining rows have all coefficients 0; no solution if a constant term is 1
  for (int i = n + 1; i <= m; i++)
    if (matrix[i].test(0)) return std::vector<bool>(0);
  std::vector<bool> ans(n + 1);
  for (int i = 1; i <= n; i++) ans[i] = matrix[i].test(0);
  return ans;
}

// --8<-- [end:core]

int main() {
  int n, m;
  std::cin >> n >> m;
  for (int i = 1; i <= m; i++) {
    bool value;
    for (int j = 1; j <= n; j++) {
      std::cin >> value;
      matrix[i][j] = value;
    }
    std::cin >> value;
    matrix[i][0] = value;
  }
  auto ans = GaussJordanElimination(n, m);
  if (ans.empty()) {
    std::cout << "No unique solution\n";
  } else {
    for (int i = 1; i <= n; i++) {
      if (i > 1) std::cout << ' ';
      std::cout << ans[i];
    }
    std::cout << '\n';
  }
}
