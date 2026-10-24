// This is a DFS implementation of backtracking
#include <iostream>
using namespace std;
int ans[14], check[3][28] = {0}, sum = 0, n;

void eq(int line) {
  if (line > n) {  // if all n rows have been searched
    sum++;
    if (sum > 3)
      return;
    else {
      for (int i = 1; i <= n; i++) cout << ans[i] << ' ';
      cout << '\n';
      return;
    }
  }
  for (int i = 1; i <= n; i++) {
    if ((!check[0][i]) && (!check[1][line + i]) &&
        (!check[2][line - i + n])) {  // check whether placing a piece here is valid
      ans[line] = i;
      check[0][i] = 1;
      check[1][line + i] = 1;
      check[2][line - i + n] = 1;
      eq(line + 1);
      // backtrack after recursing down, ready for the next recursion
      check[0][i] = 0;
      check[1][line + i] = 0;
      check[2][line - i + n] = 0;
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n;
  eq(1);
  cout << sum;
  return 0;
}
