#include <iomanip>
#include <iostream>
using namespace std;
int n;
bool vis[50];  // visited array
int a[50];     // permutation array, stores the current result in order

void dfs(int step) {
  if (step == n + 1) {  // base case
    for (int i = 1; i <= n; i++) {
      cout << setw(5) << a[i];  // field width of 5
    }
    cout << endl;
    return;
  }
  for (int i = 1; i <= n; i++) {
    if (!vis[i]) {  // check whether number i is already in the current permutation
      vis[i] = true;
      a[step] = i;
      dfs(step + 1);
      vis[i] = false;  // not using this number at this step; reset to 0 so later steps can use it
    }
  }
  return;
}

int main() {
  cin >> n;
  dfs(1);
  return 0;
}
