// This is a BFS implementation of backtracking
#include <cstring>
#include <iostream>
#include <queue>
using namespace std;
int n, m, k, x, y, a, b, ans;
int dx[4] = {0, 0, 1, -1}, dy[4] = {1, -1, 0, 0};  // four directions
bool vis[6][6];

struct oo {
  int x, y, used[6][6];
};

oo sa;

void bfs() {
  queue<oo> q;
  sa.x = x;
  sa.y = y;
  sa.used[x][y] = 1;
  q.push(sa);
  while (!q.empty()) {  // BFS queue
    oo now = q.front();
    q.pop();
    for (int i = 0; i < 4; i++) {  // try moving in each of the four directions
      int sx = now.x + dx[i];
      int sy = now.y + dy[i];
      if (now.used[sx][sy] || vis[sx][sy] || sx == 0 || sy == 0 || sx > n ||
          sy > m)
        continue;
      if (sx == a && sy == b) {
        ans++;
        continue;
      }
      sa.x = sx;
      sa.y = sy;
      memcpy(sa.used, now.used, sizeof(now.used));
      sa.used[sx][sy] = 1;
      q.push(sa);  // suppose we move this way; push into the BFS queue
    }
  }
}

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  cin >> n >> m >> k;
  cin >> x >> y >> a >> b;
  for (int i = 1, aa, bb; i <= k; i++) {
    cin >> aa >> bb;
    vis[aa][bb] = true;  // obstacle cells cannot be passed
  }
  bfs();
  cout << ans;
  return 0;
}
