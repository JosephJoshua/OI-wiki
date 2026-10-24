#include <algorithm>
#include <cstdio>
#include <iostream>
#include <map>
#include <unordered_map>
using namespace std;

const int N = 100, M = 400, mod = 998244353;

int n, m, a[N + 5], fact[M + 5], inv[M + 5];

inline int C(int x, int y) {
  return 1LL * fact[x] * inv[y] % mod * inv[x - y] % mod;
}

class HuAutomation {  // winning-hand automaton
 private:
  class Mat {
   private:
    int f[3][3];

   public:
    Mat() {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++) f[i][j] = -1;
    }

    int* operator[](const int& x) { return f[x]; }

    inline bool operator==(Mat x) const {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] != x[i][j]) return 0;
      return 1;
    }

    inline bool operator<(Mat x) const {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] != x[i][j]) return f[i][j] < x[i][j];
      return 0;
    }

    inline bool Check() {
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (f[i][j] > 3) return 1;
      return 0;
    }

    inline void Upd(Mat x, int t) {
      // update the current matrix from matrix x, simulating adding t tiles of the current rank
      for (int i = 0; i <= 2; i++)
        for (int j = 0; j <= 2; j++)
          if (x[i][j] != -1)
            for (int k = 0; k < 3 && i + j + k <= t; k++)
              f[j][k] = max(f[j][k], min(i + x[i][j] + (t - i - j - k) / 3, 4));
      // i,j,k,(t-i-j-k)
      // enumerate tiles used for chows, kept as (i-1,i), kept as i, and used directly for melds
      //  cap at 4 melds when updating
    }
  };

  struct node {
    int t, state[5];
    Mat F[2];

    node() {
      for (int i = 0; i <= 4; i++) state[i] = 0;
      t = 0;
      for (int i = 0; i <= 1; i++) F[i] = Mat();
    }

    inline bool Check() { return t == -1 || t >= 7 || F[1].Check(); }

    node Hu() {
      node x;
      x.t = -1;
      return x;
    }

    bool operator<(const node& x) const {
      if (t == x.t) {
        if (F[0] == x.F[0]) return F[1] < x.F[1];
        return F[0] < x.F[0];
      }
      return t < x.t;
    }

    node operator+(int x) {      // add x new tiles
      if (Check()) return Hu();  // already winning, return directly
      node res;
      res.F[0].Upd(F[0], x), res.F[1].Upd(F[1], x);  // update
      res.t = t;
      if (x > 1) res.F[1].Upd(F[0], x - 2), ++res.t;
      if (res.Check()) res = Hu();  // check whether it is winning
      return res;
    }
  } A[2100];

  map<node, int> mp;

  inline int Get(node x) {
    if (mp.count(x)) return mp[x];
    mp[x] = ++tot;
    A[tot] = x;
    return tot;
  }

  inline void Expand(int x) {
    // build the state transition graph:
    // for the current state A[x], try adding 0~4 tiles of one rank, giving 5 new states
    for (int i = 0; i <= 4; i++) A[x].state[i] = Get(A[x] + i);
  }

  inline node Hu() {
    node x;
    x.t = -1;
    return x;
  }

  inline node Emp() {
    node x;
    x.F[0][0][0] = 0;
    return x;
  }

 public:
  int tot, f[N + 5][M + 5][2100];

  inline void Build() {
    A[1] = Emp(), A[2] = Hu();  // state 1 is the initial valid state, 2 is the winning state
    mp[A[1]] = 1, mp[A[2]] = 2;
    tot = 2;
    Expand(1);
    for (int i = 3; i <= tot; i++)
      Expand(i);  // enumerate all reachable states to build the graph (since 2
                  // is the winning state it needs no expansion)
  }

  void DP() {
    f[0][0][1] = 1;
    for (int i = 1; i <= n; i++)
      for (int j = m; j >= 0; j--)
        for (int k = 1; k <= tot; k++)
          if (f[i - 1][j][k])
            for (int t = 0; t <= 4 - a[i]; t++)
              // enumerate how many of this rank to add (at most 4 in total, a[i] already held), combinatorial transition
              (f[i][j + t][A[k].state[a[i] + t]] +=
               1LL * f[i - 1][j][k] * C(4 - a[i], t) % mod) %= mod;
  }
} Hfu;

inline long long qpow(long long x, int y) {
  long long res = 1;
  while (y) {
    if (y & 1) res = res * x % mod;
    x = x * x % mod;
    y >>= 1;
  }
  return res;
}

void init(int n) {
  fact[0] = 1;
  for (int i = 1; i <= n; i++) fact[i] = 1LL * fact[i - 1] * i % mod;
  inv[n] = qpow(fact[n], mod - 2);
  for (int i = n - 1; i >= 0; i--) inv[i] = 1LL * inv[i + 1] * (i + 1) % mod;
}

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);

  int ans = 0;
  Hfu.Build();  // build the state graph
  cin >> n;
  for (int i = 1; i <= 13; i++) {
    int x, y;
    cin >> x;
    cin >> y;
    ++a[x];
  }
  m = (n << 2) - 13;
  init(m);
  Hfu.DP();

  for (int i = 1; i <= m; i++) {
    (ans += 1LL * Hfu.f[n][i][1] * fact[i] % mod * fact[m - i] % mod) %= mod;
    for (int j = 3; j <= Hfu.tot; j++)  // node 2 is the winning node, so skip it
      (ans += 1LL * Hfu.f[n][i][j] * fact[i] % mod * fact[m - i] % mod) %= mod;
    // f[i][j][k]: number of ways after the first i ranks, j tiles drawn in total, at node k
    // of the winning-hand automaton. Here we sum f[n][i][j],
    // multiplying each by i! (to order these i tiles) × (m - i)!
    // (to order the remaining tiles), and take the sum modulo
  }

  cout << (1LL * ans * inv[m] + 1) % mod;
  // multiplying by inv[m] divides by m!, the total number of orders; the final +1 is because dp counts having drawn i
  // tiles without winning yet
  return 0;
}
