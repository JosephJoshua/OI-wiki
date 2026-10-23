#include <cstring>
constexpr int MAXN = 100000;  // MAXN bounds the values in the array

int solve(int n, int a[]) {
  bool met[MAXN * 2 + 1];  // a bucket that covers [-MAXN, MAXN]
  memset(met, 0, sizeof(met));
  int ans = 0;
  for (int i = 0; i < n; ++i) {
    if (met[MAXN - a[i]]) ++ans;  // if the wanted value is in the bucket, add one to the answer
    met[MAXN + a[i]] = true;  // always put the current element into the bucket
  }
  return ans * 2;
}
