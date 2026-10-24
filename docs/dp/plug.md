## Definition

Some [bitmask DP](./state.md) problems require us to record connectivity information in the state. Such problems are vividly called plug DP, or connectivity-based bitmask DP. Examples include counting Hamiltonian paths in a grid graph, counting black-and-white colorings of a board where cells of the same color form one connected block, and counting spanning trees of certain graphs. These problems usually require us to encode the connectivity of the state and to work out how the connectivity changes during transitions.

## Introduction

### Domino tiling and contour line DP

Reviewing the old helps you learn the new. Before learning plug DP, let's look back at a classic problem.

???+ note "Example problem ['HDU 1400' Mondriaan’s Dream](https://acm.hdu.edu.cn/showproblem.php?pid=1400)"
    Summary: Tile an $N\times M$ board completely with $1\times 2$ or $2\times 1$ dominoes. Count the number of ways.

When $n$ or $m$ is small, this kind of problem can be solved with [bitmask DP](./state.md). Split the stages row by row: let $dp(i,s)$ be the number of ways when the first $i$ rows have been considered and the state of row $i$ is $s$. Here each bit of the state $s$ tells whether that position is already covered by the previous row.

![domino](./images/domino.svg)

Another way to split stages is cell-by-cell DP, also called contour line DP. $dp(i,j,s)$ is the number of ways when we have reached row $i$, column $j$, and the state on the current contour line is $s$.

Although cell-by-cell DP adds one dimension to the state, each transition now takes only $O(1)$ time, so the overall time complexity stays the same. Let $f_0$ be the states of the current stage, $f_1$ the states of the next stage, and $u = f_0(s)$ the value currently being enumerated. Then the transitions are:

```cpp
if (s >> j & 1) {       // if already covered
  f1[s ^ 1 << j] += u;  // place nothing
} else {                // if not covered
  if (j != m - 1 && (!(s >> j + 1 & 1))) f1[s ^ 1 << j + 1] += u;  // place horizontally
  f1[s ^ 1 << j] += u;                                             // place vertically
}
```

Notice that the "place nothing" and "place vertically" transitions can be merged.

??? note "Implementation"
    ```cpp
    #include <algorithm>
    #include <iostream>
    using namespace std;
    constexpr int N = 11;
    long long f[2][1 << N], *f0, *f1;
    int n, m;
    
    int main() {
      while (cin >> n >> m && n) {
        f0 = f[0];
        f1 = f[1];
        fill(f1, f1 + (1 << m), 0);
        f1[0] = 1;
        for (int i = 0; i < n; ++i) {
          for (int j = 0; j < m; ++j) {
            swap(f0, f1);
            fill(f1, f1 + (1 << m), 0);
    #define u f0[s]
            for (int s = 0; s < 1 << m; ++s)
              if (u) {
                if (j != m - 1 && (!(s >> j & 3))) f1[s ^ 1 << j + 1] += u;  // place horizontally
                f1[s ^ 1 << j] += u;  // place vertically or place nothing
              }
          }
        }
        cout << f1[0] << endl;
      }
    }
    ```

??? note "Exercise ['SRM 671. Div 1 900' BearDestroys](https://archive.topcoder.com/ProblemStatement/pm/14069)"
    Summary: You are given an $n\times m$ matrix where each cell contains `E` or `S`.
    Each matrix is scored as follows. Scan the cells in row-major order. If a cell is already covered by a domino, skip it.
    Otherwise, try to place a domino. If the domino would go outside the matrix or onto another domino, the placement fails; then try the other direction, or skip.
    If the cell is `E`, first try to place a $1\times 2$ domino;
    if it is `S`, first try to place a $2\times 1$ domino.
    The score of a matrix is the number of dominoes placed at the end.
    Find the sum of the scores over all $2^{nm}$ matrices.

### Terminology

Stage: the order in which the dynamic programming runs. The results of later stages depend only on the results of earlier stages (no aftereffects). Many DP problems can be split into stages in several ways. For example, in knapsack problems we can usually split stages either by item or by knapsack capacity (that is, which one the outer loop enumerates). In the domino problem, we can split stages by row, by column, by cell, by diagonal, and so on.

Contour line: the boundary between the cells already decided and the cells not yet decided.

![contour line](./images/contour_line.svg)

Plug: if a cell has a plug in some direction, the cell is connected to its neighbor in that direction.

![plug](./images/plug.svg)

## Path models

### Multiple loops

#### Example problem

???+ note "Example problem ['HDU 1693' Eat the Trees](https://acm.hdu.edu.cn/showproblem.php?pid=1693)"
    Summary: Count the ways to cover an $N\times M$ board with any number of closed loops. Some cells are blocked.

Strictly speaking, the multiple-loop problem is not really plug DP. As in the domino tiling problem above, we only need to record whether each plug exists, and then merge and create plugs in pairs.

Note that for a board of width $m$, the contour line has width $m+1$, because it contains $m$ up plugs and $1$ left plug. Also, after a row is finished, the rightmost left plug is usually an invalid state, and we need to add the first left plug of the next row. This requires adjusting the state of the current contour line, usually by shifting every state left. We call this operation rolling, `roll()`.

??? note "Example code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_1.cpp"
    ```

#### Exercises

??? note "Exercise ['ZOJ 3466' The Hive II](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?problemSetProblemId=91827368730)"
    Summary: Same as the previous problem, but the cells are hexagons.

### A single loop

#### Example problem

???+ note "Example problem ['Andrew Stankevich Contest 16 - Problem F' Pipe Layout](https://codeforces.com/gym/100220)"
    Summary: Count the ways to cover an $N\times M$ board with exactly one closed loop.

With the state representation above, every time we merge a pair of connected plugs, we create a separate closed loop. So in this problem we also need to tell which plugs are connected to each other (here it is!). This requires an extra encoding of the state.

#### State encoding

Common encodings are the bracket representation and the minimal representation. Here we focus on the minimal representation, which is more general. We use an integer array of length $m+1$ to record the state of each plug on the contour line. $0$ means there is no plug, and connected plugs are marked with the same number.

So the following two encodings represent the same state:

-   `0 3 1 0 1 3`
-   `0 1 2 0 2 1`

We map all equivalent states to the lexicographically smallest representation. For example, `0 1 2 0 2 1` above is a minimal representation.

We use the array `b[]` for the plug states on the contour line. `bb[]` records, during minimal-representation encoding, the smallest number each number is mapped to. Note that $0$ means no plug exists and cannot be mapped to any other value.

??? note "Implementation"
    ```cpp
    int b[M + 1], bb[M + 1];
    
    int encode() {
      int s = 0;
      memset(bb, -1, sizeof(bb));
      int bn = 1;
      bb[0] = 0;
      for (int i = m; i >= 0; --i) {
    #define bi bb[b[i]]
        if (!~bi) bi = bn++;
        s <<= offset;
        s |= bi;
      }
      return s;
    }
    
    void decode(int s) {
      REP(i, m + 1) {
        b[i] = s & mask;
        s >>= offset;
      }
    }
    ```

Notice that plugs always appear in pairs and disappear in pairs. So a state like `0 1 2 0 1 2` is invalid. Valid states form a bracket sequence, and in practice valid states may be very sparse.

#### Hand-written hash table

In some [bitmask DP](./state.md) problems, valid states may be sparse (as in this problem). To improve time and space complexity, we can store the valid DP states in a hash table. C++ users can use [std::unordered\_map](http://www.cplusplus.com/reference/unordered_map/unordered_map/), or write one by hand, which lets us conveniently put the transition function inside it too.

???+ note "Implementation"
    ```cpp
    constexpr int MaxSZ = 16796, Prime = 9973;
    
    struct hashTable {
      int head[Prime], next[MaxSZ], sz;
      int state[MaxSZ];
      long long key[MaxSZ];
    
      void clear() {
        sz = 0;
        memset(head, -1, sizeof(head));
      }
    
      void push(int s) {
        int x = s % Prime;
        for (int i = head[x]; ~i; i = next[i]) {
          if (state[i] == s) {
            key[i] += d;
            return;
          }
        }
        state[sz] = s, key[sz] = d;
        next[sz] = head[x];
        head[x] = sz++;
      }
    
      void roll() { REP(i, sz) state[i] <<= offset; }
    } H[2], *H0, *H1;
    ```

In the code above:

-   `MaxSZ` is an upper bound on the number of valid states. You can estimate it, or precompute a more precise value.
-   `Prime` is a large prime smaller than `MaxSZ`.
-   `head[]` holds pointers to the head nodes of the lists.
-   `next[]` holds pointers to the next states.
-   `state[]` holds the state of each node.
-   `key[]` holds the key of each node; in this problem it is the number of ways.
-   `clear()` is the initialization function. As with a hand-written adjacency list, we only need to reset the head pointers.
-   `push()` is the transition function, where `d` is a global variable (a shortcut) holding the increment of each transition. If the state is found, we do `+=`; otherwise we create a new node with state `s` and key `d`.
-   `roll()` rolls the contour line after a whole row has been processed.

For the complexity analysis of hash tables and the difference between open and closed hashing, see the chapter on hash tables in [Introduction to Algorithms](../contest/resources.md#books).

#### Transitions

???+ note "Implementation"
    ```cpp
    REP(ii, H0->sz) {
      decode(H0->state[ii]);                  // fetch the state and decode it
      d = H0->key[ii];                        // get the increment delta
      int lt = b[j], up = b[j + 1];           // left plug, up plug
      bool dn = i != n - 1, rt = j != m - 1;  // down plug, right plug
      if (lt && up) {                         // if both left and up plugs exist
        if (lt == up) {                       // they come from the same component
          if (i == n - 1 &&
              j == m - 1) {  // they may merge (closing the loop) only at the last cell.
            push(j, 0, 0);
          }
        } else {  // otherwise we must merge the two components, since the problem needs a loop cover
          REP(i, m + 1) if (b[i] == lt) b[i] = up;
          push(j, 0, 0);
        }
      } else if (lt || up) {  // if exactly one of left and up has a plug
        int t = lt | up;      // get that plug
        if (dn) {             // if we can extend downward
          push(j, t, 0);
        }
        if (rt) {  // if we can extend to the right
          push(j, 0, t);
        }
      } else {           // if neither left nor up has a plug
        if (dn && rt) {  // create a new pair of plugs
          push(j, m, m);
        }
      }
    }
    ```

??? note "Example code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_2.cpp"
    ```

#### Exercises

??? note "Exercise ['Ural 1519' Formula 1](https://acm.timus.ru/problem.aspx?space=1&num=1519)"
    Summary: Count the ways to cover an $N\times M$ board with exactly one closed loop. Some cells are blocked.

??? note "Exercise ['USACO 5.4.4' Betsy's Tours](https://hydro.ac/d/USACO/p/USACO544)"
    Summary: Given an $N\times N$ grid ($N\le 7$), count the paths that start at the top-left corner, end at the bottom-left corner, and visit every cell. Although this is a single path, its start and end are fixed, so it can be turned into a single-loop problem.

??? note "Exercise ['POJ 1739' Tony's Tour](http://poj.org/problem?id=1739)"
    Summary: Given an $N\times M$ board, count the paths that start at the bottom-left corner, end at the bottom-right corner, and visit every cell. Some cells are blocked.

??? note "Exercise ['USACO 6.1.1' Postal Vans](https://vjudge.net/problem/UVALive-2738)"
    Summary: Count the ways to cover a $4\times N$ board with one directed closed loop. Big-integer arithmetic is required.

??? note "Exercise ['HNOI 2007' Magical Amusement Park](https://www.luogu.com.cn/problem/P3190)"
    Summary: Given an $n\times m$ grid graph with a weight in each cell, find any closed loop that maximizes the total weight of the cells it passes through.

??? note "Exercise ['ProjectEuler 393' Migrating ants](https://projecteuler.net/problem=393)"
    Summary: Cover an $n\times n$ grid with several closed loops. A cover with $m$ loops contributes $2^m$ to the answer. Find the total contribution of all covers.

### A single path

#### Example problem

???+ note "Example problem ['ZOJ 3213' Beautiful Meadow](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=22&problemSetProblemId=91827367895)"
    Summary: Given an $N\times M$ grid ($N,M\le 8$) where each cell has a weight, find a path that maximizes the total weight of the cells it covers.

This is a standard single-path problem. In single-path problems, the encoded state may also contain independent plugs that have no partner. The transition function must additionally handle creating, merging and removing independent plugs. Creating or removing an independent plug corresponds to an endpoint of the path, so such events can happen at most twice (one creation and one removal, or two creations and one merge). Otherwise the final result would always contain several connected components.

We need to record in the state the total number of times such events have happened. We can encode this into the state (note that extra information like this should not be rolled when the contour line is adjusted), or we can add an extra dimension outside the `hashTable` array. The sample program below does the latter.

#### Transitions

???+ note "Implementation"
    ```cpp
    REP(i, n) {
      REP(j, m) {
        checkMax(ans, A[i][j]);  // the single-cell case needs separate handling
        if (!A[i][j]) continue;  // skip obstacles; note the state array does not need to roll here
        swap(H0, H1);
        REP(c, 3)
        H1[c].clear();  // c is the total number of creation and vanishing events, at most 2
        REP(c, 3) REP(ii, H0[c].sz) {
          decode(H0[c].state[ii]);
          d = H0[c].key[ii] + A[i][j];
          int lt = b[j], up = b[j + 1];
          bool dn = A[i + 1][j], rt = A[i][j + 1];
          if (lt && up) {
            if (lt == up) {  // in the single-path problem, we cannot merge the same pair of plugs.
              // Cannot deploy here...
            } else {  // one of the two merged plugs may be an independent plug, but the same code handles it
              REP(i, m + 1) if (b[i] == lt) b[i] = up;
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
            d += A[i][j];    // skip plug creation; this problem does not require covering every cell
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
      REP(c, 3) H1[c].roll();  // end of a row; shift the contour line
    }
    ```

??? note "Example code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_3.cpp"
    ```

#### Exercises

??? note "Exercise ['BZOJ 2310' ParkII](https://hydro.ac/p/bzoj-P2310)"
    Summary: Given an $m\times n$ board where each cell has a weight, find a path that maximizes the total weight of the cells it passes through.

??? note "Exercise ['NOI 2010 Day2' Travel Route](https://www.luogu.com.cn/problem/P1933)"
    Summary: Given an $n\times m$ board where each cell has a 0/1 weight T\[x]\[y], find a path covering the board such that:
    
    -   the i-th visited cell (x, y) satisfies T\[x]\[y]= L\[i];
    -   one end of the path is on the border of the board.
    
    Count the number of valid ways.

## Coloring models

Besides path models, another common kind of model asks us to color the board, where adjacent cells of the same color count as connected. In path problems, a transition enumerates the direction of the current path; in coloring problems, it enumerates which color the current cell gets. In coloring models, more than two cells in the state may belong to the same component. Overall, though, the ideas are much the same. Let's look at a classic example.

### Example problem 'UVa 10572' Black & White

???+ note "Example problem ['UVa 10572' Black & White](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1513)"
    Summary: On an $N\times M$ board, color the uncolored cells black or white so that all black cells are connected, all white cells are connected, and no $2\times 2$ subrectangle has all four cells the same color (for example, the case in the figure below is invalid). Count the valid colorings and construct one of them.
    
    ![black\_and\_white1](./images/black_and_white1.svg)

### State encoding

First consider the state encoding. Without connectivity, this is just [SGU 197. Nice Patterns Strike Back](https://codeforces.com/problemsets/acmsguru/problem/99999/197), which bitmask DP solves directly without much trouble (see [bitmask DP](./state.md)). Now the state must hold both color and connectivity information. Look at the state of each position on the contour line: every `Offset` bits of the binary number describe one position on the contour line. Since there are only two colors, black and white, we use the parity of the lowest bit for the color and the remaining bits for connectivity.

For the cells above the first row and to the left of the first column, we could introduce a third color to tell them apart and avoid special cases. Here we notice that the connectivity information of these boundary states is always 0, so the third color needs no extra encoding.

In path problems, the contour line consists of $m$ up plugs and $1$ left plug. In this problem, we also need to check whether the $2\times 2$ subrectangle whose bottom-right cell is the current cell is valid, so we need to record the color of the top-left cell. So the contour line still has length $m+1$.

This encoding still keeps a lot of redundant information (connected regions always have the same color, and the top-left cell only needs its color, not its connectivity). But since we already use a hash table and the minimal representation, this has little effect on the time complexity. To keep the code simple, we don't refine it further.

In the worst case (for example, when the first row alternates black and white), every plug has different connectivity information, so we need $4$ bits to record connectivity. Adding the color bit, `Offset` is $5$ bits in this problem.

???+ note "Implementation"
    ```cpp
    constexpr int Offset = 5, Mask = (1 << Offset) - 1;
    int c[N + 2];
    int b[N + 2], bb[N + 3];
    
    T_state encode() {
      T_state s = 0;
      memset(bb, -1, sizeof(bb));
      int bn = 1;
      bb[0] = 0;
      for (int i = m; i >= 0; --i) {
    #define bi bb[b[i]]
        if (!~bi) bi = bn++;
        s <<= Offset;
        s |= (bi << 1) | c[i];
      }
      return s;
    }
    
    void decode(T_state s) {
      REP(i, m + 1) {
        b[i] = s & Mask;
        c[i] = b[i] & 1;
        b[i] >>= 1;
        s >>= Offset;
      }
    }
    ```

### Hand-written hash table

Since we need to construct one valid coloring, the hash table needs an extra field `pre[]` that records, for each state, any one of its predecessors in the previous stage.

???+ note "Implementation"
    ```cpp
    constexpr int Prime = 9979, MaxSZ = 1 << 20;
    
    template <class T_state, class T_key>
    struct hashTable {
      int head[Prime];
      int next[MaxSZ], sz;
      T_state state[MaxSZ];
      T_key key[MaxSZ];
      int pre[MaxSZ];
    
      void clear() {
        sz = 0;
        memset(head, -1, sizeof(head));
      }
    
      void push(T_state s, T_key d, T_state u) {
        int x = s % Prime;
        for (int i = head[x]; ~i; i = next[i]) {
          if (state[i] == s) {
            key[i] += d;
            return;
          }
        }
        state[sz] = s, key[sz] = d, pre[sz] = u;
        next[sz] = head[x], head[x] = sz++;
      }
    
      void roll() { REP(ii, sz) state[ii] <<= Offset; }
    };
    
    hashTable<T_state, T_key> _H, H[N][N], *H0, *H1;
    ```

### Constructing a solution

With the information above, constructing a solution is easy. First go through the states in the current hash table, and add those with at most $2$ connected components to the count. If the count is not $0$, use the `pre` array to build a solution backward. Note that because we perform `Roll()` at the end of each row, the color there must be taken from `c[j+1]`.

???+ note "Implementation"
    ```cpp
    void print() {
      T_key z = 0;
      int u;
      REP(i, H1->sz) {
        decode(H1->state[i]);
        if (*max_element(b + 1, b + m + 1) <= 2) {
          z += H1->key[i];
          u = i;
        }
      }
      cout << z << endl;
      if (z) {
        DWN(i, n, 0) {
          B[i][m] = 0;
          DWN(j, m, 0) {
            decode(H[i][j].state[u]);
            int cc = j == m - 1 ? c[j + 1] : c[j];
            B[i][j] = cc ? 'o' : '#';
            u = H[i][j].pre[u];
          }
        }
        REP(i, n) puts(B[i]);
      }
      puts("");
    }
    ```

### Transitions

We write:

-   `cc` for the color of the cell being colored now;
-   `lf` for the color of the cell to the left;
-   `up` for the color of the cell above;
-   `lu` for the color of the top-left cell.

We use $-1$ to mean the color does not exist. Now consider the transitions. There are three cases: merge, inherit, and create:

???+ note "Transitions - code"
    ```cpp
    void trans(int i, int j, int u, int cc) {
      decode(H0->state[u]);
      int lf = j ? c[j - 1] : -1, lu = b[j] ? c[j] : -1,
          up = b[j + 1] ? c[j + 1] : -1;  // no color also counts as a color!
      if (lf == cc && up == cc) {         // merge
        if (lu == cc) return;             // the 2x2 subrectangle has a single color
        int lf_b = b[j - 1], up_b = b[j + 1];
        REP(i, m + 1) if (b[i] == up_b) { b[i] = lf_b; }
        b[j] = lf_b;
      } else if (lf == cc || up == cc) {  // inherit
        if (lf == cc)
          b[j] = b[j - 1];
        else
          b[j] = b[j + 1];
      } else {                                             // create
        if (i == n - 1 && j == m - 1 && lu == cc) return;  // special case
        b[j] = m + 2;
      }
      c[j] = cc;
      if (!ok(i, j, cc)) return;  // check whether forming a closed component makes it invalid
      H1->push(encode(), H0->key[u], u);
    }
    ```

For the last case, note that if a closed connected region has already been formed, we can no longer use its color, or that color would end up with two connected components. It seems we need to record such events separately; we could follow the approach in ['ZOJ 3213' Beautiful Meadow](#example-problem_2) and add another dimension to record this event. But using a special property of this problem, we can also handle it as a special case.

???+ note "Special case - code"
    ```cpp
    bool ok(int i, int j, int cc) {
      if (cc == c[j + 1]) return true;
      int up = b[j + 1];
      if (!up) return true;
      int c1 = 0, c2 = 0;
      REP(i, m + 1) if (i != j + 1) {
        if (b[i] == b[j + 1]) {  // same connected component, so the color must be the same
          assert(c[i] == c[j + 1]);
        }
        if (c[i] == c[j + 1] && b[i] == b[j + 1]) ++c1;
        if (c[i] == c[j + 1]) ++c2;
      }
      if (!c1) {               // if a new closed component would be formed
        if (c2) return false;  // if the contour line still has the same color
        if (i < n - 1 || j < m - 2) return false;
      }
      return true;
    }
    ```

Now consider in more detail when a connected component disappears. Each time we color a cell, if no other cell is connected to the cell above it, a closed connected component is formed. This can only happen in the last two columns of the last row. Otherwise, to avoid a $2\times 2$ block of one color later, this color must appear again, except in the following case:

    2 2
    o#
    #o

We handle this case specially. Then, in this problem, we can take the shortcut of not recording whether a closed component has already been formed.

??? note "Example code"
    ```cpp
    --8<-- "docs/dp/code/plug/plug_4.cpp"
    ```

### Exercises

??? note "Exercise ['Topcoder SRM 312. Div1 Hard' CheapestIsland](https://archive.topcoder.com/ProblemStatement/pm/6482)"
    Summary: Given a grid graph where each cell has a weight, find the connected component with the minimum total weight.

??? note "Exercise ['JLOI 2009' Mysterious Creature](https://www.luogu.com.cn/problem/P3886)"
    Summary: Given a grid graph where each cell has a weight, find the connected component with the maximum total weight.

??? note "Exercise ['AtCoder Beginner Contest 211. Problem E' Red Polyomino](https://atcoder.jp/contests/abc211/tasks/abc211_e)"
    Summary: Given an $N\times N$ grid where each cell starts black or white, you may choose exactly $K$ white cells and paint them red. Count the ways in which the red cells form one connected component.

## Graph theory models

???+ note "Example problem ['NOI 2007 Day2' Counting Spanning Trees](https://www.luogu.com.cn/problem/P2109)"
    Summary: Count the spanning trees of a special kind of graph, where each vertex is connected by an edge to exactly the $k$ vertices before it.

???+ note "Example problem ['2015 ACM-ICPC Asia Shenyang Regional Contest - Problem E' Efficient Tree](https://acm.hdu.edu.cn/showproblem.php?pid=5513)"
    Summary: You are given an $N\times M$ grid graph and the weights of the edges between 4-adjacent cells.
    For a spanning tree, the score of each vertex is 1+\[it has an edge going up]+\[it has an edge going left].
    The score of a spanning tree is the product of the scores of all its vertices.
    
    You need to find the total edge weight of a minimum spanning tree, and the sum of the scores of all minimum spanning trees.
    ($n\le 800,m\le 7$)

## In practice

### Example problem

???+ note "Example problem ['HDU 4113' Construct the Great Wall](https://acm.hdu.edu.cn/showproblem.php?pid=4113)"
    Summary: On an $N\times M$ board, build a closed loop that separates all the `x` cells from all the `o` cells.

Some plug DP problems ask us to build walls on the board to separate certain elements. Let's call them wall-building problems. They can be treated either as coloring models or as path models.

![greatwall](./images/greatwall.svg)

In this problem, if we treat it as a coloring model, we must not only handle the perimeter of the colored regions, but also detect invalid cases where regions touch at a corner (Figure 2). Also, unlike ['UVa 10572' Black & White](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1513), this problem requires the wall to be a simple polygon, so the ring-shaped case below is invalid here.

    3 3
    ooo
    oxo
    ooo

So we use the path model and turn it into a [single-loop](#a-single-loop) problem.

We run the DP over the grid points where the board lines cross (so the length and width each increase by $1$). In each transition, we must make sure every `x` is outside the loop and every `o` is inside it. So we also need to know whether the current position is inside the loop. We can add a dimension for this, or simply count the parity of the number of down plugs on the contour line before this position (the ray-casting method).

??? note "Example code"
    ```cpp
    #include <cstring>
    #include <iostream>
    using namespace std;
    #define REP(i, n) for (int i = 0; i < n; ++i)
    
    template <class T>
    bool checkMin(T &a, const T b) {
      return b < a ? a = b, true : false;
    }
    
    constexpr int N = 10, M = N;
    constexpr int offset = 3, mask = (1 << offset) - 1;
    int n, m;
    int d;
    constexpr int INF = 0x3f3f3f3f;
    int b[M + 1], bb[M + 1];
    
    int encode() {
      int s = 0;
      memset(bb, -1, sizeof(bb));
      int bn = 1;
      bb[0] = 0;
      for (int i = m; i >= 0; --i) {
    #define bi bb[b[i]]
        if (!~bi) bi = bn++;
        s <<= offset;
        s |= bi;
      }
      return s;
    }
    
    void decode(int s) {
      REP(i, m + 1) {
        b[i] = s & mask;
        s >>= offset;
      }
    }
    
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
            checkMin(key[i], d);
            return;
          }
        }
        state[sz] = s, key[sz] = d;
        next[sz] = head[x];
        head[x] = sz++;
      }
    
      void roll() { REP(i, sz) state[i] <<= offset; }
    } H[2], *H0, *H1;
    
    char A[N + 1][M + 1];
    
    void push(int i, int j, int dn, int rt) {
      b[j] = dn;
      b[j + 1] = rt;
      if (A[i][j] != '.') {
        bool bad = A[i][j] == 'o';
        REP(jj, j + 1) if (b[jj]) bad ^= 1;
        if (bad) return;
      }
      H1->push(encode());
    }
    
    int solve() {
      cin >> n >> m;
      int ti, tj;
      REP(i, n) {
        scanf("%s", A[i]);
        REP(j, m) if (A[i][j] == 'o') ti = i, tj = j;
        A[i][m] = '.';
      }
      REP(j, m + 1) A[n][j] = '.';
      ++n, ++m, ++ti, ++tj;
      H0 = H, H1 = H + 1;
      H1->clear();
      d = 0;
      H1->push(0);
      int z = INF;
      REP(i, n) {
        REP(j, m) {
          swap(H0, H1);
          H1->clear();
          REP(ii, H0->sz) {
            decode(H0->state[ii]);
            d = H0->key[ii] + 1;
            int lt = b[j], up = b[j + 1];
            bool dn = i != n - 1, rt = j != m - 1;
            if (lt && up) {
              if (lt == up) {
                int cnt = 0;
                REP(i, m + 1) if (b[i])++ cnt;
                if (cnt == 2 && i == ti && j == tj) {
                  checkMin(z, d);
                }
              } else {
                REP(i, m + 1) if (b[i] == lt) b[i] = up;
                push(i, j, 0, 0);
              }
            } else if (lt || up) {
              int t = lt | up;
              if (dn) {
                push(i, j, t, 0);
              }
              if (rt) {
                push(i, j, 0, t);
              }
            } else {
              --d;
              push(i, j, 0, 0);
              ++d;
              if (dn && rt) {
                push(i, j, m, m);
              }
            }
          }
        }
        H1->roll();
      }
      if (z == INF) z = -1;
      return z;
    }
    
    int main() {
      int T;
      cin >> T;
      for (int Case = 1; Case <= T; ++Case) {
        printf("Case #%d: %d\n", Case, solve());
      }
    }
    ```

### Exercises

??? note "Exercise ['SCOI 2011' Floor](https://www.luogu.com.cn/problem/P3272)"
    Summary: An $r\times c$ board has some blocked cells. Count the ways to cover all unblocked cells with L-shaped tiles.

??? note "Exercise ['HDU 4796' Winter's Coming](https://acm.hdu.edu.cn/showproblem.php?pid=4796)"
    Summary: On an $N\times M$ board, color the uncolored cells black, white or gray. All black cells must be connected and all white cells must be connected; the black region and the white region must each touch both the top and bottom borders of the board; and the black region and the white region must not be adjacent. Each cell has a cost. Find a coloring that minimizes the total cost of the gray cells.
    
    ![4796](./images/4796.jpg)

??? note "Exercise ['ZOJ 2125' Rocket Mania](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=11&problemSetProblemId=91827365624)"
    Summary: On a $9\times6$ map, each cell holds one kind of pipe (`-`, `T`, `L`, `+` shaped, or none). You may rotate each pipe by 0°, 90°, 180° or 270°. Find the maximum number of rows whose right border can be connected by pipes to the left border of row X.

??? note "Exercise ['ZOJ 2126' Rocket Mania Plus](https://pintia.cn/problem-sets/91827364500/exam/problems/type/7?page=11&problemSetProblemId=91827365625)"
    Summary: On a $9\times6$ map, each cell holds one kind of pipe (`-`, `T`, `L`, `+` shaped, or none). You may rotate each pipe by 0°, 90°, 180° or 270°. Find the maximum number of rows whose right border can be connected by pipes to the left border.

??? note "Exercise ['World Finals 2009/2010 Harbin' Channel](https://qoj.ac/problem/13134)"
    Summary: On a grid map, `.` is empty ground and `#` is rock. Find the longest path such that:
    
    1.  It starts at the top-left corner and ends at the bottom-right corner.
    2.  It does not pass through rock.
    3.  The path does not touch itself in the 8-connected sense (that is, it may not touch itself even at corners).

??? note "Exercise ['HDU 3958' Tower Defence](https://acm.hdu.edu.cn/showproblem.php?pid=3958)"
    Summary: It can be turned into finding the longest non-touching path from $\mathit{S}$ to $\mathit{T}$, where touching at corners is allowed.

??? note "Exercise ['UVa 10531' Maze Statistics](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=24&page=show_problem&problem=1472)"
    Summary: There is an $N\times M$ grid, and each cell independently becomes an obstacle with probability $\mathit{p}$. You must walk from the top-left corner of the maze to the bottom-right corner. For each cell, find the probability that it is an obstacle in a **solvable maze (one where the start and end are 4-connected)**. ($N \le 5$, $M \le 6$)

??? note "Exercise ['Aizu 2452' Pipeline Plans](https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2452)"
    Summary: There are 12 tile patterns, and the number of tiles of each pattern is given. Tile a rectangular floor that can be viewed as an $R\times C$ grid, one tile per cell, so that the center of the top-left cell and the center of the bottom-right cell are connected by the lines on the tile patterns. $(2 \le R \times C \le 15)$
    
    ![plug2](./images/plug2.png)

??? note "Exercise ['SDOI 2014' Circuit Board](https://www.luogu.com.cn/problem/P3314)"
    Summary: An $N\times M$ circuit board has some cells that wires cannot pass through. Given $K$ pairs of cells, every pair must be connected by a wire, and wires must not cross each other (one wire may enter a cell through its top edge and leave through its left edge, while another wire enters through its bottom edge and leaves through its right edge). Treat wires as undirected edges. Find the minimum total wire length and the number of ways to achieve it.

??? note "Exercise ['SPOJ CAKE3' Delicious Cake](https://www.spoj.com/problems/CAKE3)"
    Summary: A cake can be viewed as an $N\times M$ grid. Cut it along the grid lines into several pieces. Count the different ways to cut it. Two ways are the same if and only if every resulting piece has the same shape and is in the same position. ($\min(N,M) \le 5, \max(N,M) \le 130$)

## Chapter notes

Plug DP problems are usually hard to code and involve many cases, so they are a relatively [niche area](https://github.com/OI-wiki/libs/blob/master/topic/7-%E7%8E%8B%E5%A4%A9%E6%87%BF-%E8%AE%BA%E5%81%8F%E9%A2%98%E7%9A%84%E5%8D%B1%E5%AE%B3.ppt) in OI/ACM. The most classic material on the subject is the 2008 national training team paper by [Danqi Chen](https://www.cs.princeton.edu/~danqic/), [Dynamic programming problems based on connectivity state compression](https://github.com/AngelKitty/review_the_national_post-graduate_entrance_examination/tree/master/books_and_notes/professional_courses/data_structures_and_algorithms/sources/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2008%E8%AE%BA%E6%96%87%E9%9B%86/%E9%99%88%E4%B8%B9%E7%90%A6%E3%80%8A%E5%9F%BA%E4%BA%8E%E8%BF%9E%E9%80%9A%E6%80%A7%E7%8A%B6%E6%80%81%E5%8E%8B%E7%BC%A9%E7%9A%84%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E9%97%AE%E9%A2%98%E3%80%8B) (Chinese). Next, notonlysuccess of HDU wrote two blog posts in 2011 that cover the topic step by step from easy to hard. They are also rare and valuable, but today you have to dig them up in the Web Archive.

-   [notonlysuccess, [Collection] Plug DP (Chinese)](https://web.archive.org/web/20110815044829/http://www.notonlysuccess.com/?p=625)
-   [notonlysuccess, [Complete edition] Plug DP (Chinese)](https://web.archive.org/web/20111007185146/http://www.notonlysuccess.com/?p=931)

### Domino tiling

['HDU 1400' Mondriaan’s Dream](https://acm.hdu.edu.cn/showproblem.php?pid=1400) also appears in [Training Guide for Algorithm Competitions](../contest/resources.md#books), as an example problem in the section "Dynamic programming on contour lines". [Domino tiling](https://en.wikipedia.org/wiki/Domino_tiling) is a family of classic math problems. Changing the constraints slightly gives subproblems of different difficulty that need different algorithms.

When $m=2$, domino tiling is equivalent to the Fibonacci sequence. [Concrete Mathematics](https://www.csie.ntu.edu.tw/~r97002/temp/Concrete%20Mathematics%202e.pdf) uses this problem to introduce the Fibonacci numbers and derives their closed form in several ways.

When $m\le 10,n\le 10^9$, we can precompute the transitions as a matrix and [speed them up with matrix multiplication](http://www.matrix67.com/blog/archives/276).

![domino\_v2\_transform\_matrix](./images/domino_v2_transform_matrix.svg)

When $n,m\le 100$, we can use the [FKT Algorithm](https://en.wikipedia.org/wiki/FKT_algorithm) to count the perfect matchings of the corresponding planar graph.

-   ['51nod 1031' Domino Tiling](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1031)
-   ['51nod 1033' Domino Tiling V2](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1033)|['Vijos 1194' Domino](https://vijos.org/p/1194)
-   ['51nod 1034' Domino Tiling V3](https://www.51nod.com/Html/Challenge/Problem.html#problemId=1034)|['Ural 1594' Aztec Treasure](https://acm.timus.ru/problem.aspx?space=1&num=1594)
-   [Wolfram MathWorld, Chebyshev Polynomial of the Second Kind](https://mathworld.wolfram.com/ChebyshevPolynomialoftheSecondKind.html)

### A single path

The "single path" problem is a special case of the [Hamiltonian path](https://en.wikipedia.org/wiki/Hamiltonian_path) problem on a [grid graph](https://mathworld.wolfram.com/GridGraph.html). The decision version of the Hamiltonian path problem is an important member of the [NP-complete](https://en.wikipedia.org/wiki/NP-completeness) family.
