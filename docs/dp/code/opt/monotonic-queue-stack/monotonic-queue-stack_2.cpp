#include <array>
#include <deque>
#include <iostream>

constexpr int MAXV = 4e4 + 10;
constexpr int MAXN = 1e2 + 10;

using namespace std;

int n, W, last = 0, now = 1;
array<int, MAXN> v, w, k;
array<array<int, MAXV>, 2> f;
deque<int> q;

int main() {
  ios::sync_with_stdio(false);
  cin >> n >> W;
  for (int i = 1; i <= n; i++) {
    cin >> v[i] >> w[i] >> k[i];
  }
  for (int i = 1; i <= n; i++) {
    for (int y = 0; y < w[i]; y++) {
      // clear the queue
      deque<int>().swap(q);
      for (int x = 0; x * w[i] + y <= W; x++) {
        // pop elements that are out of range
        while (!q.empty() && q.front() < x - k[i]) {
          q.pop_front();
        }
        // keep the queue monotonic
        while (!q.empty() && f[last][q.back() * w[i] + y] - q.back() * v[i] <
                                 f[last][x * w[i] + y] - x * v[i]) {
          q.pop_back();
        }
        q.push_back(x);
        f[now][x * w[i] + y] =
            f[last][q.front() * w[i] + y] - q.front() * v[i] + x * v[i];
      }
    }
    swap(last, now);
  }
  cout << f[last][W] << endl;
  return 0;
}
