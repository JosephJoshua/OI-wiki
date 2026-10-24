#include <iostream>

int p[16] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53};
unsigned long long n;
unsigned long long ans,
    ans_num;  // ans is the largest antiprime up to n (kept updated), ans_sum is
              // the number of divisors of ans.

// depth: which prime is currently being enumerated
// temp: the current value, whose number of divisors is num
// num: current number of divisors
// up: exponent of the previous prime, an upper bound on the current exponent
void dfs(int depth, unsigned long long temp, unsigned long long num, int up) {
  if (depth >= 16 || temp > n) return;
  if (num > ans_num) {  // update the answer
    ans = temp;
    ans_num = num;
  }
  if (num == ans_num && ans > temp) ans = temp;  // update the answer
  for (int i = 1; i <= up; i++) {
    if (temp * p[depth] > n)
      break;  // pruning: if multiplying by this factor makes it larger than ans, it cannot be optimal
    dfs(depth + 1, temp *= p[depth], num * (i + 1),
        i);  // take one of this factor and search the next factor
  }
  return;
}

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  while (cin >> n) {
    ans_num = 0;
    dfs(0, 1, 1, 60);
    cout << ans << '\n';
  }
  return 0;
}
