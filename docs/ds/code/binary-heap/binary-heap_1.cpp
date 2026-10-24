#include <iostream>
#include <queue>
using namespace std;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int t, x;
  cin >> t;
  while (t--) {
    // max-heap, holds the first half of the elements (the smaller values)
    priority_queue<int, vector<int>, less<int>> a;
    // min-heap, holds the second half of the elements (the larger values)
    priority_queue<int, vector<int>, greater<int>> b;
    while (cin >> x, x) {
      // for a query-and-delete operation, print and remove the top of the max-heap
      // because this problem asks for the smaller median (an even count has two median candidates)
      // this differs slightly from the k-th largest explanation above, but once you understand that, a small adjustment makes this clear
      if (x == -1) {
        cout << a.top() << '\n';
        a.pop();
      }
      // for an insert operation, pick the right heap based on the top of the max-heap
      else {
        if (a.empty() || x <= a.top())
          a.push(x);
        else
          b.push(x);
      }
      // rebalance the two heaps
      if (a.size() > (a.size() + b.size() + 1) / 2) {
        b.push(a.top());
        a.pop();
      } else if (a.size() < (a.size() + b.size() + 1) / 2) {
        a.push(b.top());
        b.pop();
      }
    }
  }
  return 0;
}
