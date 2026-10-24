author: countercurrent-time, StudyingFather

Interactive problems already appeared at the IOI in the last century. In recent years they had not appeared in contests below the provincial selection level, but in 2019 two interactive problems appeared back to back in NOI-series contests: "P5208\[WC2019] Mr. I's Shop" and "P5473\[NOI2019] Mr. I's Adventure". This may mean that interactive problems are returning to NOI-series contests.

Interactive problems don't require much advanced algorithmic background, and they usually don't have strict time limits; how good a program is often depends only on the limit on the number of interactions. So when learning interactive problems, it's best to progress gradually by difficulty. If you want to train your algorithmic thinking rather than just learn algorithms, solving interactive problems is a very good way to do it. Although interactive problems usually don't demand much knowledge of algorithms, it's still recommended to learn a fair amount of Senior-level and provincial-selection-level algorithms before trying them, because by then your algorithmic thinking and breadth of knowledge will have reached a certain level. For a basic introduction to interactive problems, see **OI Wiki**'s [Problem types - Interactive problems](./problems.md#interactive-problems).

Errors specific to interactive problems:

-   The contestant must flush the output buffer after every output, otherwise the program gets an Idleness limit exceeded error. Also, if the problem has multiple test cases and the program can know the answer before reading all the data, it must still read all of the data; otherwise the input gets out of sync and it again causes ILE (you can send several queries at once and receive all of their answers at once). Also, try not to use fast input.
-   If the program makes too many queries, Codeforces gives a Wrong Answer verdict (though the judge explains the reason for the Wrong Answer), while UVa gives a Protocol Limit Exceeded (PLE) verdict.
-   If the program's interaction format is wrong, UVa gives a Protocol Violation (PV) verdict.

Since input and output in interactive problems are fairly tedious, it's a good idea to wrap input and output in separate functions.

During a contest, if the problem setter provides a grader header file (for debugging grader-style interactive problems) or a checker program (for debugging stdio-style interactive problems), debugging is fairly easy. Otherwise it's hard, because stress testing interactive problems is much harder than stress testing ordinary problems. Without `testlib.h`, a stdio interaction library for a problem with many interaction details is usually about 3k of code, plus a 3k stress tester, which takes at least an hour to write. But whether or not you have a debugging program, debugging interactive code usually requires you to simulate the interaction with the program by hand. So interactive problems require contestants to design high-quality programs, try hard to get them right the first time, and be good at finding bugs by reading code.

Example problems:

-   [CF679A Bear and Prime 100](https://codeforces.com/problemset/problem/679/A)
-   [CF843B Interactive LowerBound](https://codeforces.com/problemset/problem/843/B)
-   [UOJ206\[APIO2016\]Gap](http://uoj.ac/problem/206)
-   [CF750F New Year and Finding Roots](https://codeforces.com/problemset/problem/750/F)
-   [UVa12731 Mysterious Space Station](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=823&page=show_problem&problem=4584)

## CF679A Bear and Prime 100

Every prime has exactly two divisors, so we directly enumerate divisors of the hidden number. We may ask at most 20 queries, and when trying to factor larger numbers (such as 92), we find that we need to try primes up to $\lfloor\frac{n}{2}\rfloor$. So we first sieve the primes below 50 and query each of them in turn.

Since stress testing this problem is easy, we can simply try every number in the range. We find that the program can't handle squares of primes correctly. So we also add the squares of 2, 3, 5, 7, namely 4, 9, 25, 49, for 19 numbers in total, which fits the limit.

??? note "Reference code"
    ```cpp
    #include <cstdio>
    constexpr int prime[] = {2,  3,  4,  5,  7,  9,  11, 13, 17, 19,
                             23, 25, 29, 31, 37, 41, 43, 47, 49};
    int cnt = 0;
    char res[5];
    
    int main() {
      for (int i : prime) {
        printf("%d\n", i);
        fflush(stdout);
        scanf("%s", res);
        if (res[0] == 'y' && ++cnt == 2) return printf("composite"), 0;
      }
      printf("prime");
      return 0;
    }
    ```

## CF843B Interactive LowerBound

The linked list has up to $5 \times 10 ^ 4$ elements, but we can only ask $1999$ queries, and each query only tells us the next element, so the usual method of walking the whole list won't work. There is only one way to get close to the target element directly: pick random points.

For $n < 2000$, just enumerate. For $n \ge 2000$, we query 1000 random points. The expected distance between these points is then small, so we can start from the largest value less than $x$ and walk forward; one can prove that we will find the answer before reaching the next sampled point. As soon as we find an element greater than or equal to $x$ while walking, we can stop.

Although the overall idea is simple, in practice it may be harder to come up with if you haven't learned non-exact randomized algorithms such as simulated annealing.

Also, because Codeforces has hacks, many people deliberately break code that doesn't initialize the random seed, so you need `srand((size_t)new char)` before calling `random_shuffle()`.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstdlib>
    constexpr int N = 50005;
    int n, start, x;
    int a[N];
    
    int main() {
      scanf("%d%d%d", &n, &start, &x);
      if (n < 2000) {
        int ans = 2e9;
        for (int i = 1; i <= n; i++) {
          printf("? %d\n", i), fflush(stdout);
          int val, next;
          scanf("%d%d", &val, &next);
          if (val >= x) ans = std::min(ans, val);
        }
        if (ans == 2e9) ans = -1;
        printf("! %d", ans), fflush(stdout);
      } else {
        srand((size_t) new char);
        int p = start, ans = 0;
        for (int i = 1; i <= n; i++) a[i] = i;
        std::random_shuffle(a + 1, a + n + 1);
        for (int i = 1; i <= 1000; i++) {
          printf("? %d\n", a[i]), fflush(stdout);
          int val, next;
          scanf("%d%d", &val, &next);
          if (val < x && val > ans) p = a[i], ans = val;
        }
        while (p != -1 && ans < x) {
          printf("? %d\n", p), fflush(stdout);
          int val, next;
          scanf("%d%d", &val, &next);
          ans = val;
          p = next;
        }
        if (ans < x) ans = -1;
        printf("! %d", ans), fflush(stdout);
      }
      return 0;
    }
    ```

## UOJ206\[APIO2016]Gap

We consider the two subtasks separately:

1.  Limit on the number of queries.

    Consider the first query. Since we don't know any numbers at first, we need to query the range $[1, 10 ^ {18}]$ to get the minimum and maximum.

    Since the query limit is exactly $\frac{N + 1}{2}$, we want every query to give us values we haven't seen before; that way we can get all the numbers in the sequence within the limit. The method is simple: after querying $[s, t]$ and getting the values $mn, mx$, query $[mn + 1, mx - 1]$ next.

2.  Limit on the size of the query ranges.

    The problem requires the total number of elements inside all queried ranges to be at most $3N$, so we want to minimize the query ranges. The method above no longer works, because the total number of elements in its query ranges is $O(N ^ 2)$. We could try binary search over the value range, but that isn't reliable; in the worst case it can be forced to $O(N ^ 2)$. So we need a more effective way to split the value range that avoids querying the same points repeatedly and wasting queries.

    The answer can't be smaller than $\lfloor\frac{a_n - a_1}{N - 1}\rfloor$, so we can split the value range by this value. Let $i$ start at 0 and $ans$ start at the value above. Each time, query $[i, i + ans]$ and update $ans$, then increase $i$ with $ans$ as the step size.

    However, this method doesn't work well for subtask 1, because in the worst case many queried ranges may not contain any number at all.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    
    #include "gap.h"
    
    long long findGap(int T, int N) {
      static long long a[100005] = {}, ans = 0;
      long long s = 0, t = 1e18, s1, t1;
      if (T == 1) {
        int l = 1, r = N;
        while (l <= r) {
          MinMax(s, t, &s1, &t1);
          a[l++] = s1, a[r--] = t1;
          s = s1 + 1, t = t1 - 1;
        }
        for (int i = 2; i <= N; i++) ans = std::max(ans, a[i] - a[i - 1]);
      } else if (T == 2) {
        MinMax(s, t, &s1, &t1);
        ans = (t1 - s1) / (N - 1);
        long long l = s1 + 1, r = t1, last = s1;
        for (long long i = l; i <= r;) {
          MinMax(i, i + ans, &s1, &t1);
          i += ans + 1;
          if (s1 != -1) ans = std::max(ans, s1 - last), last = t1;
        }
      }
      return ans;
    }
    ```

## CF750F New Year and Finding Roots

With the strict limits $h \le 7$ and number of queries $\le 16$, we need to make the most of the information each query gives us.

For $h \le 4$ we can just brute force. But for $h > 4$ we need a very efficient traversal algorithm.

Picking random nodes is not a good method, because we can't tell whether we are close enough to the root. Also, with purely random picks, the probability of hitting the root at least once is $1 - (\frac{2 ^ h - 2}{2 ^ h - 1})$; even after excluding repeated picks, the probability of hitting the root is still very small.

Since $1 \le k \le 3$ and we don't know which side is closer to the root, we consider the worst case: when $k = 3$, our first two traversal directions both lead away from the root, and only the third leads toward the root. So we must traverse in all three directions.

Consider the two traversal methods BFS and DFS. Since the BFS search tree may be large, we prefer DFS. Of course, if we know the current depth, and it is small enough that the search tree within that depth is no larger than the number of remaining queries, we can just BFS.

Knowing the depth of the current node and the direction we are going gives a big advantage. However, it's very hard to know whether we are moving toward the root or toward a leaf. With DFS, we only learn the direction when we reach the root ($k = 2$) or a leaf ($k = 1$). So we need to learn the depth of the current node whenever possible, and we can't use methods like iterative deepening that stop partway through a traversal.

Consider picking a random starting node; starting from it, we may run into the worst case above.

If $k = 1$, we immediately know the depth of the current node.

If $k = 2$, the current node is the root.

If $k = 3$, we just DFS in all three directions. Two of the directions lead straight toward leaves, and their paths have the same length; the other direction leads toward the root, but it may accidentally turn toward a leaf partway, so its path is longer. At this point we can compute the depth of the current node.

When $k = 1$ or $k = 3$, we need to consider the longer path. We can find the node with the smallest depth on that path (it must be shallower than the starting node). If we mark visited nodes and don't visit them again, there is only one path to follow from that node. This path may still lead toward a leaf, but it must also contain a node shallower than the starting point, so we can repeat the steps above from that node.

Of course, in the worst case for $h = 7$ (each time we move only one step toward the root and then go straight toward a leaf), we find that using DFS alone takes up to $\frac{(1 + 7) \times 7}{2} = 28$ queries in the worst case. But we already know the depth of the starting node, so we can compute the depths of all visited nodes, and, following our earlier discussion of BFS, decide whether we can BFS directly from the shallowest node.

Now we can compute that the worst case needs 17 queries. So we try to remove one node from the search tree (since DFS can only traverse blindly, we look at BFS): when doing a BFS of depth $k$, the search tree has up to $2 ^ k - 1$ nodes, and we may need $2 ^ k - 1$ queries to determine which node has exactly 2 neighbors. But once we have queried $2 ^ k - 2$ of these nodes, we know the last one must be the root.

The optimal plan in the worst case is then: for $h = 7$, DFS from a leaf, each time moving only one step toward the root and then going straight toward a leaf. After 10 queries, the shallowest known node has depth 4. Since we know its parent, we BFS directly from its parent (the search tree has depth 3 and $2 ^ 3 - 1 = 7$ nodes). After asking $2 ^ 3 - 2 = 6$ queries in the BFS, we know the last node of the BFS search tree is the root.

So our algorithm needs exactly 16 queries in the worst case.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <queue>
    #include <vector>
    using namespace std;
    constexpr int N = 256 + 5;
    int T, h, chance;
    bool ok;
    vector<int> to[N], path;
    
    bool read(int x) {
      if (to[x].empty()) {
        printf("? %d\n", x), fflush(stdout);
        int k, t;
        scanf("%d", &k);
        if (k == 0) exit(0);
        for (int i = 0; i < k; i++) {
          scanf("%d", &t);
          to[x].push_back(t);
        }
        if (k == 2) {
          printf("! %d\n", x), fflush(stdout);
          return ok = true;
        }
        chance--;
      }
      return false;
    }
    
    bool dfs(int x) {
      if (to[x].empty()) path.push_back(x);
      if (read(x)) return true;
      for (int i : to[x])
        if (to[i].empty()) return dfs(i);
      return false;
    }
    
    void bfs(int s, int k) {
      queue<int> q;
      for (int i : to[s])
        if (to[i].empty()) q.push(i);
      for (int i = 1; i < k; i++) {
        int x = q.front();
        q.pop();
        if (read(x)) return;
        for (int j : to[x])
          if (to[j].empty()) q.push(j);
      }
      for (int i = 1; i < k; i++) {
        int x = q.front();
        q.pop();
        if (read(x)) return;
      }
      printf("! %d\n", q.front()), fflush(stdout);
    }
    
    int main() {
      for (scanf("%d", &T); T--;) {
        ok = false;
        for (int i = 0; i < N; i++) to[i].clear();
        chance = 16;
        scanf("%d", &h);
        if (h == 0) exit(0);
        vector<int> long_path;
        if (read(1)) continue;
        int root, dep;
        if (to[1].size() == 1)
          root = 1, dep = h;
        else {
          for (int i : to[1]) {
            path.clear();
            if (dfs(i)) break;
            if (path.size() > long_path.size()) swap(path, long_path);
          }
          if (ok) continue;
          dep = h - (path.size() + long_path.size()) / 2;
          root = long_path.at((long_path.size() - (h - dep)) - 1);
        }
        while ((1 << (dep - 1)) - 2 > chance) {
          path.clear();
          if (dfs(root)) break;
          dep = h - (h - dep + path.size()) / 2;
          root = path.at((path.size() - (h - dep)) - 1);
        }
        if (!ok) bfs(root, 1 << (dep - 2));
      }
      return 0;
    }
    ```

## UVa12731 Mysterious Space Station

Since the only feedback is whether a move hits a wall, we should try to walk close to the walls without letting the robot get lost. This has several benefits:

-   When walking along a wall, it's easy to know whether we will hit it, so we get as much information as possible.
-   Squares next to the walls never contain portals, so the robot can't get lost there.

So if we know the robot may be at some position next to a wall, we can check whether it really is there using the ["wall follower" (one-hand-on-the-wall) method](https://en.wikipedia.org/wiki/Maze_solving_algorithm). By a topological argument, in a maze with walls on both sides, if you enter from the entrance and always keep one hand on the same wall, you are guaranteed to find the exit. Since the walls in this problem are closed, walking along the path next to the wall is guaranteed to bring us back to the starting point without hitting the wall. Also, since the path along the wall is the largest closed loop on the map, the actual code doesn't need to bump into walls on purpose to make sure the robot is next to a wall; it can mark the wall-side path on the map instead. And once we do hit a wall, we should quickly go back the way we came, which keeps the robot from getting lost and also saves steps.

From this we get a trial-and-error method to check whether the robot is on a particular square: move the robot onto the wall-side path without stepping on unknown squares or known portals, then walk once around the wall-side path. If we never hit a wall along the way, the robot really is on that particular square.

Using the method above, we first mark all unknown squares on the map, then check each unknown square from top to bottom and left to right to see whether it is a portal. We can first walk to the square above the unknown square, then move down and then left. Then we use the method above to check whether the robot is to the left of the unknown square. If it isn't, the robot is not where it should be, which means the unknown square is a portal.

After finding the unknown squares, we need to determine how the 2k unknown squares are paired. The method is simple: just try all pairings by brute force. Since $k \le 5$, we need at most $9 + 7 + 5 + 3$ trials. For comparison, checking every unknown square on the map takes at most $121 - 40$ trials.

Currently the code below only passes the UOJ mirror of the problem, [#247. [Rujia Liu's Present 7] Mysterious Space Station](http://uoj.ac/problem/247), and doesn't pass the original problem on UVa. Even after modifying Rujia Liu's reference solution on UOJ it still didn't pass, and we haven't been able to contact Rujia Liu for now. So the code below follows the UOJ version.

Still, Rujia Liu's reference solution is of much higher quality than the code below. You can view the [reference solution that passes the UOJ mirror](http://uoj.ac/submission/105789) on UOJ. On the same data, the reference solution uses very few moves.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <iostream>
    #include <queue>
    #include <stack>
    
    #define Wall 0
    #define Unknown 1
    #define Space 2
    #define Gate 3
    #define Path 4
    
    const int N = 20;
    const int dir[8][2] = {{0, 1},  {1, 0}, {0, -1}, {-1, 0},
                           {-1, 1}, {1, 1}, {1, -1}, {-1, -1}};
    const char dirs[5] = "ESWN";
    int n, m, k;
    int a[N][N], id[N][N];
    
    struct point {
      int x, y;
    
      point(int x = 0, int y = 0) : x(x), y(y) {}
    
      bool operator==(const point& tmp) const { return x == tmp.x && y == tmp.y; }
    
      bool operator!=(const point& tmp) const { return !(*this == tmp); }
    
      point side(int d) const { return point(x + dir[d][0], y + dir[d][1]); }
    
      int check(int d) { return a[x + dir[d][0]][y + dir[d][1]]; }
    
      int id() { return ::id[x][y]; }
    } start;
    
    std::vector<std::pair<point, int>> path;
    std::pair<point, point> ans[N];
    std::pair<point, bool> vis[N];
    
    bool walk(int d) {
      printf("MoveRobot %c\n", dirs[d]);
      fflush(stdout);
      int ret;
      scanf("%d", &ret);
      return ret;
    }
    
    bool walk(int d, std::stack<int>& st) {
      if (walk(d)) {
        st.push(d);
        return true;
      }
      return false;
    }
    
    bool read() {
      if (scanf("%d%d%d", &n, &m, &k) != 3) return false;
      if (n == 0) return false;
      memset(a, 0, sizeof(a));
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
          char c;
          std::cin >> c;
          if (c == 'S') start = point(i, j);
          if (c == '*')
            a[i][j] = Wall;
          else
            a[i][j] = Unknown;
        }
      return true;
    }
    
    void answer() {
      for (int i = 0; i < k; i++)
        printf("Answer %d %d\n", ans[i].first.id(), ans[i].second.id());
      fflush(stdout);
    }
    
    // wall follower method: since the Path along the wall is a maximal closed loop, we only
    // need to make sure we hit no obstacle while walking along the Path
    void wall_follower_init(point x, int last, int wallside, point s) {
      if (x == s && !path.empty()) return;
      if (x.check(wallside) == Path) {
        path.push_back(std::make_pair(x, wallside));
        wall_follower_init(x.side(wallside), wallside, last ^ 2, s);
      } else if (x.check(last) == Wall) {
        for (int i = 0; i < 4; i++)
          if (i != (last ^ 2) && x.check(i) != Wall) {
            path.push_back(std::make_pair(x, i));
            wall_follower_init(x.side(i), i, last, s);
            return;
          }
      } else {
        path.push_back(std::make_pair(x, last));
        wall_follower_init(x.side(last), last, wallside, s);
      }
    }
    
    void init() {
      int cnt = 1;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++) {
          if (a[i][j] == Unknown) {
            id[i][j] = cnt++;
            for (int k = 0; k < 8; k++)
              if (point(i, j).check(k) == Wall) {
                a[i][j] = Path;
                break;
              }
          } else
            id[i][j] = 0;
        }
      path.clear();
      int wallside = 0, last = 0;
      for (int i = 0; i < 4; i++)
        if (start.check(i) == Wall) {
          wallside = i;
          break;
        }
      for (int i = 0; i < 4; i++)
        if (start.check(i) == Path && i != (wallside ^ 2)) {
          last = i;
          break;
        }
      wall_follower_init(start, last, wallside, start);
    }
    
    void undo(std::stack<int>& st) {
      while (!st.empty()) walk(st.top() ^ 2), st.pop();
    }
    
    bool wall_follower(point x) {
      std::stack<int> st;
      bool ok = true;
      int i = 0;
      while (i < path.size() && path[i].first != x) i++;
      for (int j = i; ok && j < path.size(); j++) {
        if (walk(path[j].second))
          st.push(path[j].second);
        else
          ok = false;
      }
      for (int j = 0; ok && j < i; j++) {
        if (walk(path[j].second))
          st.push(path[j].second);
        else
          ok = false;
      }
      if (!ok) undo(st);
      return ok;
    }
    
    // Determine that we are currently at
    // x, by "crossing the river by feeling the stones": just walk to the Path in directions that avoid obstacles, unknown squares and portals
    // Used when finding portals and pairing portals
    void bfs(point s, point t, std::vector<int>& v) {
      static int map[N][N] = {};
      memset(map, -1, sizeof(map));
      std::queue<point> q;
      map[s.x][s.y] = 4;
      q.push(s);
      while (!q.empty()) {
        point x = q.front();
        q.pop();
        if (x == t) break;
        for (int i = 0; i < 4; i++) {
          point y = x.side(i);
          if ((x.check(i) == Path || x.check(i) == Space) && map[y.x][y.y] == -1) {
            map[y.x][y.y] = i;
            q.push(y);
          }
        }
      }
      for (point x = t; x != s; x = x.side(map[x.x][x.y] ^ 2)) {
        v.push_back(map[x.x][x.y]);
      }
      std::reverse(v.begin(), v.end());
    }
    
    bool move(point s, point t, std::stack<int>& st) {  // used when close to a portal
      static std::vector<int> v;
      v.clear();
      bfs(s, t, v);
      for (int i : v)
        if (!walk(i, st)) return false;
      return true;
    }
    
    // move toward the wall as quickly as possible
    bool make_sure(point x, int last) {
      if (a[x.x][x.y] == Path) return wall_follower(x);
      for (int i = 0; i < 4; i++)
        if ((x.check(i) == Path || x.check(i) == Space) && i != (last ^ 2)) {
          if (!walk(i)) return false;
          bool ret = make_sure(x.side(i), i);
          walk(i ^ 2);
          return ret;
        }
      return false;
    }
    
    void find_gate() {
      int cnt = 0;
      std::stack<int> st;
      for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
          if (cnt == k * 2 && a[i][j] == Unknown)
            a[i][j] = Space;
          else if (a[i][j] == Unknown) {
            bool ok = true;
            if (!move(start, point(i - 1, j), st))
              ok = false;
            else if (!walk(1, st))
              ok = false;
            else if (!walk(2, st))
              ok = false;
            else if (!make_sure(point(i, j - 1), -1))
              ok = false;
            if (!ok) {
              vis[cnt++] = std::make_pair(point(i, j), false);
              a[i][j] = Gate;
              for (int k = 0; k < 8; k++) {
                point y = point(i, j).side(k);
                if (point(i, j).check(k) == Unknown) a[y.x][y.y] = Space;
              }
            } else
              a[i][j] = Space;
            undo(st);
          }
    }
    
    void make_gate_pair() {
      int cnt = 0;
      std::stack<int> st;
      for (int i = 0; i < k * 2; i++)
        if (!vis[i].second)
          for (int j = 0; !vis[i].second && j < k * 2; j++)
            if (j != i && !vis[j].second) {
              bool ok = true;
              if (!move(start, vis[i].first.side(2), st))
                ok = false;
              else if (!walk(0, st))
                ok = false;
              else if (!make_sure(vis[j].first.side(0), -1))
                ok = false;
              if (ok) {
                ans[cnt++] = std::make_pair(vis[i].first, vis[j].first);
                vis[i].second = vis[j].second = true;
              }
              undo(st);
            }
    }
    
    int main() {
      while (read()) {
        init();
        find_gate();
        make_gate_pair();
        answer();
      }
      return 0;
    }
    ```

## Exercises

-   [Rujia Liu's interactive problem contest, Rujia Liu's Present 7, has very high-quality problems and is highly recommended.](https://onlinejudge.org/contests/328-9976a2e2/)
-   [P5473\[NOI2019\] Mr. I's Adventure](https://www.luogu.com.cn/problem/P5473)
-   [P5208\[WC2019\] Mr. I's Shop](https://www.luogu.com.cn/problem/P5208)

## References and further reading

-   [Implementing interactive problems in an online judge with Linux pipes](https://www.cnblogs.com/tsreaper/p/pipe-interactive.html)
