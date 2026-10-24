#include <cstring>
#include <iostream>
using namespace std;

template <class T>
bool checkMax(T &a, const T b) {
  return a < b ? a = b, true : false;
}

constexpr int N = 8, M = 8;
constexpr int offset = 3, mask = (1 << offset) - 1;
int A[N + 1][M + 1];
int n, m;
int ans, d;
constexpr int MaxSZ = 16796, Prime = 9973;

struct hashTable {
  int head[Prime], next[MaxSZ], sz;
  int state[MaxSZ];
  int key[MaxSZ];

  void clear() {
    sz = 0;
    memset(head, -1, sizeof(head));
  }

  void push(int s) {
    int x = s % Prime;
    for (int i = head[x]; ~i; i = next[i]) {
      if (state[i] == s) {
        checkMax(key[i], d);
        return;
      }
    }
    state[sz] = s, key[sz] = d;
    next[sz] = head[x];
    head[x] = sz++;
  }

  void roll() {
    for (int i = 0; i < sz; i++) state[i] <<= offset;
  }
} H[2][3], *H0, *H1;

int b[M + 1], bb[M + 1];

int encode() {
  int s = 0;
  memset(bb, -1, sizeof(bb));
  int bn = 1;
  bb[0] = 0;
  for (int i = m; i >= 0; --i) {
    if (!~bb[b[i]]) bb[b[i]] = bn++;
    s <<= offset;
    s |= bb[b[i]];
  }
  return s;
}

void decode(int s) {
  for (int i = 0; i < m + 1; i++) {
    b[i] = s & mask;
    s >>= offset;
  }
}

void push(int c, int j, int dn, int rt) {
  b[j] = dn;
  b[j + 1] = rt;
  H1[c].push(encode());
}

void init() {
  cin >> n >> m;
  H0 = H[0], H1 = H[1];
  for (int c = 0; c < 3; c++) H1[c].clear();
  d = 0;
  H1[0].push(0);
  memset(A, 0, sizeof(A));
  for (int i = 0; i < n; i++)
    for (int j = 0; j < m; j++) cin >> A[i][j];
}

void solve() {
  ans = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      checkMax(ans, A[i][j]);  // the single-cell case needs separate handling
      if (!A[i][j]) continue;  // skip obstacles; note the state array does not need to roll here
      swap(H0, H1);
      for (int c = 0; c < 3; c++)
        H1[c].clear();  // c is the total number of creation and vanishing events, at most 2
      for (int c = 0; c < 3; c++)
        for (int ii = 0; ii < H0[c].sz; ii++) {
          decode(H0[c].state[ii]);
          d = H0[c].key[ii] + A[i][j];
          int lt = b[j], up = b[j + 1];
          bool dn = A[i + 1][j], rt = A[i][j + 1];
          if (lt && up) {
            if (lt == up) {  // in the single-path problem, we cannot merge the same pair of plugs.
              // Cannot deploy here...
            } else {  // one of the two merged plugs may be an independent plug, but the same code handles it
              for (int i = 0; i < m + 1; i++)
                if (b[i] == lt) b[i] = up;
              push(c, j, 0, 0);
            }
          } else if (lt || up) {
            int t = lt | up;
            if (dn) {
              push(c, j, t, 0);
            }
            if (rt) {
              push(c, j, 0, t);
            }
            // a plug vanishes: an independent plug simply disappears, while a paired plug turns its partner into an independent plug;
            // either way, c must be increased by 1.
            if (c < 2) {
              push(c + 1, j, 0, 0);
            }
          } else {
            d -= A[i][j];
            H1[c].push(H0[c].state[ii]);
            d += A[i][j];  // skip plug creation; this problem does not require covering every cell
            if (dn && rt) {  // create a pair of plugs
              push(c, j, m, m);
            }
            if (c < 2) {  // create an independent plug
              if (dn) {
                push(c + 1, j, m, 0);
              }
              if (rt) {
                push(c + 1, j, 0, m);
              }
            }
          }
        }
    }
    for (int c = 0; c < 3; c++) H1[c].roll();  // end of a row; shift the contour line
  }
  for (int ii = 0; ii < H1[2].sz; ii++) checkMax(ans, H1[2].key[ii]);
  cout << ans << endl;
}

int main() {
  int T;
  cin >> T;
  while (T--) {
    init();
    solve();
  }
}