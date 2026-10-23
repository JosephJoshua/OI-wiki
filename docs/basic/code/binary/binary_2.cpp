#include <iostream>
using namespace std;

int a[1000005];
int n, m;

bool check(int k) {  // check feasibility; k is the blade height
  long long sum = 0;
  for (int i = 1; i <= n; i++)       // check every tree
    if (a[i] > k)                    // if the tree is taller than the blade
      sum += (long long)(a[i] - k);  // add up the wood cut off
  return sum >= m;                   // feasible if we get at least m
}

int find() {
  int l = 0, r = 1e9 + 1;   // the range is half-open, so add 1 to 10^9
                            // keep check(l) true and check(r) false
  while (l + 1 < r) {       // while l and r are not adjacent
    int mid = (l + r) / 2;  // take the midpoint
    if (check(mid))         // if feasible
      l = mid;              // raise the blade
    else
      r = mid;  // otherwise lower the blade
  }
  return l;  // return the left end
}

int main() {
  cin >> n >> m;
  for (int i = 1; i <= n; i++) cin >> a[i];
  cout << find();
  return 0;
}
