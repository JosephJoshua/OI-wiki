## A problem about segments

Let's start with a neat little problem:

> For a permutation of $1-n$, call a range whose values form a contiguous set of integers a segment. Count the segments of a permutation. For example, the segments of $\{5 ,3 ,4, 1 ,2\}$ are: $[1,1],[2,2],[3,3],[4,4],[5,5],[2,3],[4,5],[1,3],[2,5],[1,5]$.

At first glance, it seems we need to maintain the set of values in each range, which does not look friendly in terms of complexity. A segment tree can check whether a given range is a segment, but it cannot easily count the segments.

So here we introduce a magical data structure: the permutation tree (divide-combine tree)!

## Continuous segments

Before introducing the permutation tree, let's set up some prerequisites. The definitions in the slides by LCA (Liu Cheng'ao) are not easy to understand, so to make things easier for the reader, we give some less rigorous (but easier to understand) definitions here.

### Permutations and continuous segments

**Permutation**: a permutation $P$ of order $n$ is a sequence of size $n$ in which $P_i$ takes every value in $1,2,\cdots,n$. More formally, a permutation $P$ of order $n$ is an ordered collection that satisfies:

1.  $|P|=n$.
2.  $\forall i,P_i\in[1,n]$.
3.  $\nexists i,j\in[1,n],P_i=P_j$.

    **Continuous segment**: for a permutation $P$, a continuous segment $(P,[l,r])$ is a range $[l,r]$ such that the values of $P_{l\sim r}$ are contiguous. More formally, for a permutation $P$, a continuous segment is a range $[l,r]$ that satisfies:

$$
(\nexists\ x,z\in[l,r],y\notin[l,r],\ P_x<P_y<P_z)
$$

In particular, when $l>r$, we treat it as an empty continuous segment, written $(P,\varnothing)$.

Let $I_P$ be the set of all continuous segments of permutation $P$. We consider $(P,\varnothing)\in I_P$.

### Operations on continuous segments

Continuous segments are defined in terms of ranges and values, so we can define intersection, union and difference of continuous segments.

Let $A=(P,[a,b]),B=(P,[x,y])$ with $A,B\in I_P$. Then the relations and operations on continuous segments can be written as:

1.  $A\subseteq B\iff x\le a\wedge b\le y$.
2.  $A=B\iff a=x\wedge b=y$.
3.  $A\cap B=(P,[\max(a,x),\min(b,y)])$.
4.  $A\cup B=(P,[\min(a,x),\max(b,y)])$.
5.  $A\setminus B=(P,\{i|i\in[a,b]\wedge i\notin[x,y]\})$.

These operations are really just ordinary set intersection, union and difference applied to ranges.

### Properties of continuous segments

Some obvious properties of continuous segments: let $A,B\in I_P,A \cap B \neq \varnothing,A \notin B,B \notin A$. Then $A\cup B,A\cap B,A\setminus B,B\setminus A\in I_P$.

Proof? The proof is essentially just set intersection, union and difference.

## Permutation tree

OK, now we get to the main part. As you might have guessed, the permutation tree is a tree made of continuous segments. But a permutation can have as many as $O(n^2)$ continuous segments, so we need to pick out the more basic ones to build the tree.

### Primitive segments

The full name of this concept is **primitive continuous segment**, but the author thinks "primitive segment" is more concise.

For a permutation $P$, a primitive segment $M$ is one such that no continuous segment in $I_P$ partially overlaps it (intersects it without one containing the other). Formally, $X\in I_P$ and $\forall A\in I_P,\ X\cap A= (P,\varnothing)\vee X\subseteq A\vee A\subseteq X$.

Let $M_P$ be the set of all primitive segments. Obviously, $(P,\varnothing)\in M_P$.

Clearly, any two primitive segments are either disjoint or one contains the other. You may also notice that **a continuous segment can be made of several pairwise disjoint primitive segments**. The largest primitive segment is the whole permutation itself, which contains all the other primitive segments. So the primitive segments form a tree structure, which we call the **permutation tree**. More strictly, the permutation tree of $P$ consists of **all primitive segments** of $P$.

We have given a lot of dry definitions, so let's look at a picture. Consider the permutation $P=\{9,1,10,3,2,5,7,6,8,4\}$. The permutation tree formed by its primitive segments is:

![p1](./images/div-com1.png)

The figure does not label the primitive segments themselves, but **each node in the figure represents a primitive segment**. We only label the value range of each primitive segment. For example, the primitive segment represented by node $[5,8]$ is $(P,[6,9])=\{5,7,6,8\}$. This raises a question: **what are prime nodes and linear nodes?**

### Prime nodes and linear nodes

We give the definitions directly here and discuss why they are correct later.

1.  **Value range**: for a node $u$, let $[u_l,u_r]$ be the range of values of the node.
2.  **Child sequence**: for a node $u$ in the permutation tree, its children form an **ordered** sequence whose elements are value ranges (a single number $x$ can be viewed as the range $[x,x]$). We call this sequence the child sequence and write it as $S_u$.
3.  **Child permutation**: for a child sequence $S_u$, the permutation obtained by compressing its elements to positive integers is called the child permutation. For example, node $[5,8]$ has child sequence $\{[5,5],[6,7],[8,8]\}$; sorting and numbering the ranges gives the child permutation $\{1,2,3\}$. Similarly, the child permutation of node $[4,8]$ is $\{2,1\}$. The child permutation of node $u$ is written $P_u$.
4.  **Linear node**: a node whose child permutation is in increasing or decreasing order is a linear node. Formally, a node with $P_u=\{1,2,\cdots,|S_u|\}$ or $P_u=\{|S_u|,|S_u-1|,\cdots,1\}$ is called a linear node. **A leaf has no child permutation, and we also consider it a linear node**.
5.  **Prime node**: any node that is not a linear node is a prime node.

From the figure we can see that only $[1,10]$ is not a linear node, because the child permutation of $[1,10]$ is $\{3,1,4,2\}$.

### Properties of prime nodes and linear nodes

Prime nodes and linear nodes are named after their properties. First, a very obvious property: for any node $u$ in the permutation tree, the union of the ranges in its child sequence is the value range of $u$. That is, $\bigcup_{i=1}^{|S_u|}S_u[i]=[u_l,u_r]$.

For a linear node $u$: any **subrange** of its child sequence forms a **continuous segment**. Formally, $\forall S_u[l\sim r]$, $\bigcup_{i=l}^rS_u[i]\in I_P$.

For a prime node $u$: **no** subrange of its child sequence of **length greater than 1 (here length means the number of elements in the child sequence, not the length of an index range)** forms a **continuous segment**. Formally, $\forall S_u[l\sim r],l<r$, $\bigcup_{i=l}^rS_u[i]\notin I_P$.

The property of linear nodes is easy to prove. The child permutation of a linear node is either increasing or decreasing, and the value ranges are joined end to end, so any contiguous subsequence (range) is a continuous segment.

Many readers may find the property of prime nodes harder to understand: why does **no** subrange of length greater than $1$ form a continuous segment?

We use proof by contradiction. Suppose that for a node $u$, there is a **longest** range $S_u[l\sim r]$ in its child sequence that forms a continuous segment. Then $A=\bigcup_{i=l}^rS_u[i]\in I_P$, which means $A$ is a primitive segment! (Since $A$ is the longest in the child sequence, there is no continuous segment that partially overlaps it.) So you did not use all the primitive segments to build the permutation tree. Contradiction.

### Building the permutation tree

For building the permutation tree, LCA gives a linear-time algorithm[^ref1]. Below is an easier-to-understand $O(n\log n)$ algorithm.

#### Incremental method

We use an incremental method. A stack maintains the permutation forest formed by the first $i-1$ elements. We must **emphasize** here what a permutation forest means: at any time, every node in the stack is either a prime node or a linear node. Now consider the current node $P_i$.

1.  First check whether it can become a child of the node at the top of the stack. If it can, make it a child of the top, then pop the top and make it the current node. Repeat until the stack is empty or the current node cannot become a child of the top.
2.  If it cannot become a child of the top, check whether several consecutive nodes at the top of the stack can be merged with it into one node (how to check this is explained later), and make the merged node the current node.
3.  Repeat the steps above until nothing more can be done. Then this increment ends, and we push the current node onto the stack.

Now let's explain in detail.

#### The specific strategy

If the current node can become a child of the top node, then the top node must be a linear node. If it were a prime node, then after merging, the prime node would contain a sub-continuous segment, which violates the property of prime nodes. So it must be a linear node.

If it cannot become a child of the top node, we check whether several consecutive nodes at the top of the stack can be merged together with the current node. Let $l$ be the left endpoint of the range of the current node. Let $L_i$ be the largest left endpoint $< l$ among the continuous segments whose right endpoint is at index $i$. The current node is $P_i$, and the top node is $t$.

1.  If $L_i$ does not exist, the current node clearly cannot be merged;
2.  If $t_l=L_i$, then two nodes are merged, and the result is a **linear node**;
3.  Otherwise, there must be a node $t'$ in the stack whose left endpoint is ${t'}_l=L_i$, and we can always merge from the current node down to $t'$ to form a **prime node**;

#### Checking whether we can merge

Finally, let's see how to compute $L_i$. In fact, $(P,[l,r])$ is a continuous segment if and only if the difference between the maximum and minimum in the range equals the length of the range minus 1. That is,

$$
\max_{l\le i\le r}P_i-\min_{l\le i\le r}P_i=r-l
$$

And since P is a permutation, for any range $[l,r]$ we have

$$
\max_{l\le i\le r}P_i-\min_{l\le i\le r}P_i\ge r-l
$$

So we maintain $\max_{l\le i\le r}P_i-\min_{l\le i\le r}P_i-(r-l)$, and finding a continuous segment becomes a minimum query!

With this idea, the following algorithm is natural. For the current $i$ in the incremental process, we maintain an array $Q$ that stores the max-minus-min difference of the range $[j,i]$ minus its length. That is,

$$
Q_j=\max_{j\le k\le i}P_k-\min_{j\le k\le i}P_k-(i-j),\ \ 0<j<i
$$

Now we want to know whether there is a smallest $j$ in $1\sim i-1$ with $Q_j=0$. This is the same as finding the minimum of $Q_{1\sim i-1}$. The smallest such $j$ is $L_i$. If there is none, then $L_i=i$.

But when the $i$-th increment ends, we need to quickly update the array $Q$ for i+1. The range changes from $[j,i]$ to $[j,i+1]$, and $Q_j$ changes if $P_{i+1}>\max$ or $P_{i+1}<\min$. How does it change? If $P_{i+1}>\max$, we subtract $\max$ from $Q_j$ and then add $P_{i+1}$, which updates $Q_j$. The case $P_{i+1}<\min$ is similar: $Q_j=Q_j+\min-P_{i+1}$.

Now what if, for a range $[x,y]$, the range $\max$ of $P_{x\sim i},P_{x+1\sim i},P_{x+2\sim i},\cdots,P_{y\sim i}$ are all the same? As you have noticed, this amounts to a range add. Similarly, when the range $\min$ of $P_{x\sim i},P_{x+1\sim i},\cdots,P_{y\sim i}$ are all the same, it is also a range add. Also, the updates for $\max$ and $\min$ are independent, so they can be done separately.

So the maintenance of $Q$ can be described as follows:

1.  Find the largest $j$ with $P_{j}>P_{i+1}$. Clearly all the numbers in $P_{j+1\sim i}$ are less than $P_{i+1}$, so we need to update the maximum part of $Q_{j+1\sim i}$. Since $P_{i},\max(P_i,P_{i-1}),\max(P_i,P_{i-1},P_{i-2}),\cdots,\max(P_i,P_{i-1},\cdots,P_{j+1})$ is (non-strictly) increasing, we can apply the same update to each run with the same $\max$, which is a range add.
2.  Updating $\min$ is similar.
3.  Subtract $1$ from every $Q_j$, because the range length increases by $1$.
4.  Query $L_i$: that is, query the **index** of the minimum of $Q$.

That's right, we can maintain $Q$ with a segment tree! One problem remains: how do we find the runs that share the same $\max/\min$? Use monotonic stacks! Maintain two monotonic stacks, one for $\max$ and one for $\min$. Clearly, the ranges whose endpoints are two adjacent elements in a stack share the same $\max/\min$, so we just update the segment tree while maintaining the monotonic stacks.

See the code for the exact way to maintain it.

After so much dry explanation, you are probably a bit lost, so let's look at a picture. Warning: long image!

![p2](./images/div-com2.jpg)

### Implementation

Finally, here is an implementation for reference. The code is taken from [Da Mi Bing's blog](https://www.cnblogs.com/Paul-Guderian/p/11020708.html), with some comments added.

```cpp
#include <algorithm>
#include <cstdio>
using namespace std;
constexpr int N = 200010;

int n, m, a[N], st1[N], st2[N], tp1, tp2, rt;
int L[N], R[N], M[N], id[N], cnt, typ[N], bin[20], st[N], tp;

// the original problem for this code should be CERC2017 Intrinsic Interval
// array a is the permutation from the original problem
// st1 and st2 are two monotonic stacks, tp1 and tp2 are their tops, rt is the root of the permutation tree
// arrays L and R are the left and right endpoints of each tree node; array M is explained in the tree construction
// id stores the node index corresponding to each position of the permutation; typ marks prime vs. linear nodes
// st is a stack of permutation tree node indices, and tp is its top
struct RMQ {  // precompute RMQ (Max & Min)
  int lg[N], mn[N][17], mx[N][17];

  void chkmn(int& x, int y) {
    if (x > y) x = y;
  }

  void chkmx(int& x, int y) {
    if (x < y) x = y;
  }

  void build() {
    for (int i = bin[0] = 1; i < 20; ++i) bin[i] = bin[i - 1] << 1;
    for (int i = 2; i <= n; ++i) lg[i] = lg[i >> 1] + 1;
    for (int i = 1; i <= n; ++i) mn[i][0] = mx[i][0] = a[i];
    for (int i = 1; i < 17; ++i)
      for (int j = 1; j + bin[i] - 1 <= n; ++j)
        mn[j][i] = min(mn[j][i - 1], mn[j + bin[i - 1]][i - 1]),
        mx[j][i] = max(mx[j][i - 1], mx[j + bin[i - 1]][i - 1]);
  }

  int ask_mn(int l, int r) {
    int t = lg[r - l + 1];
    return min(mn[l][t], mn[r - bin[t] + 1][t]);
  }

  int ask_mx(int l, int r) {
    int t = lg[r - l + 1];
    return max(mx[l][t], mx[r - bin[t] + 1][t]);
  }
} D;

// maintain L_i

struct SEG {  // segment tree
#define ls (k << 1)
#define rs (k << 1 | 1)
  int mn[N << 1], ly[N << 1];  // range add; range minimum

  void pushup(int k) { mn[k] = min(mn[ls], mn[rs]); }

  void mfy(int k, int v) { mn[k] += v, ly[k] += v; }

  void pushdown(int k) {
    if (ly[k]) mfy(ls, ly[k]), mfy(rs, ly[k]), ly[k] = 0;
  }

  void update(int k, int l, int r, int x, int y, int v) {
    if (l == x && r == y) {
      mfy(k, v);
      return;
    }
    pushdown(k);
    int mid = (l + r) >> 1;
    if (y <= mid)
      update(ls, l, mid, x, y, v);
    else if (x > mid)
      update(rs, mid + 1, r, x, y, v);
    else
      update(ls, l, mid, x, mid, v), update(rs, mid + 1, r, mid + 1, y, v);
    pushup(k);
  }

  int query(int k, int l, int r) {  // find the position of 0
    if (l == r) return l;
    pushdown(k);
    int mid = (l + r) >> 1;
    if (!mn[ls])
      return query(ls, l, mid);
    else
      return query(rs, mid + 1, r);
    // if there is no 0, it automatically returns the position you are querying
  }
} T;

int o = 1, hd[N], dep[N], fa[N][18];

struct Edge {
  int v, nt;
} E[N << 1];

void add(int u, int v) {  // add an edge in the tree
  E[o] = Edge{v, hd[u]};
  hd[u] = o++;
}

void dfs(int u) {
  for (int i = 1; bin[i] <= dep[u]; ++i) fa[u][i] = fa[fa[u][i - 1]][i - 1];
  for (int i = hd[u]; i; i = E[i].nt) {
    int v = E[i].v;
    dep[v] = dep[u] + 1;
    fa[v][0] = u;
    dfs(v);
  }
}

int go(int u, int d) {
  for (int i = 0; i < 18 && d; ++i)
    if (bin[i] & d) d ^= bin[i], u = fa[u][i];
  return u;
}

int lca(int u, int v) {
  if (dep[u] < dep[v]) swap(u, v);
  u = go(u, dep[u] - dep[v]);
  if (u == v) return u;
  for (int i = 17; ~i; --i)
    if (fa[u][i] != fa[v][i]) u = fa[u][i], v = fa[v][i];
  return fa[u][0];
}

// check whether the current range is a continuous segment
bool judge(int l, int r) { return D.ask_mx(l, r) - D.ask_mn(l, r) == r - l; }

// build the tree
void build() {
  for (int i = 1; i <= n; ++i) {
    // monotonic stack
    // the minimum on the range [st1[tp1-1]+1,st1[tp1]] is a[st1[tp1]]
    // popping it now means adding back the Min that was over-subtracted.
    // leaf j of the segment tree stores, from j to the current i,
    // Max{j,i}-Min{j,i}-(i-j)
    // the range add is just a tag.
    // the monotonic stacks help the segment tree move from i-1 to i.
    // after moving to i, query the global minimum to see whether a solution exists

    while (tp1 && a[i] <= a[st1[tp1]])  // increasing stack, maintains Min
      T.update(1, 1, n, st1[tp1 - 1] + 1, st1[tp1], a[st1[tp1]]), tp1--;
    while (tp2 && a[i] >= a[st2[tp2]])
      T.update(1, 1, n, st2[tp2 - 1] + 1, st2[tp2], -a[st2[tp2]]), tp2--;

    T.update(1, 1, n, st1[tp1] + 1, i, -a[i]);
    st1[++tp1] = i;
    T.update(1, 1, n, st2[tp2] + 1, i, a[i]);
    st2[++tp2] = i;

    id[i] = ++cnt;
    L[cnt] = R[cnt] = i;  // L, R here are the left and right endpoints of the node's range
    int le = T.query(1, 1, n), now = cnt;
    while (tp && L[st[tp]] >= le) {
      if (typ[st[tp]] && judge(M[st[tp]], i)) {
        // check whether it can become a child; if so, do it
        R[st[tp]] = i, M[st[tp]] = L[now], add(st[tp], now), now = st[tp--];
      } else if (judge(L[st[tp]], i)) {
        typ[++cnt] = 1;  // linear nodes are always created this way
        L[cnt] = L[st[tp]], R[cnt] = i, M[cnt] = L[now];
        // array M records the left endpoint of the node's rightmost child, used for the can-become-a-child check above
        add(cnt, st[tp--]), add(cnt, now);
        now = cnt;
      } else {
        add(++cnt, now);  // create a new node and add now as its child
        // if no continuous segment can be formed starting at the current node, merge.
        // until we find a node that forms a continuous segment. And we can always find
        // such a node.
        do add(cnt, st[tp--]);
        while (tp && !judge(L[st[tp]], i));
        L[cnt] = L[st[tp]], R[cnt] = i, add(cnt, st[tp--]);
        now = cnt;
      }
    }
    st[++tp] = now;  // the increment ends; push the current node

    T.update(1, 1, n, 1, i, -1);  // the right endpoint moves one step right, so subtract 1 everywhere
  }

  rt = st[1];  // the last node left in the stack is the root
}

// split on whether the lca is prime or linear; leaves are treated as prime here
void query(int l, int r) {
  int x = id[l], y = id[r];
  int z = lca(x, y);
  if (typ[z] & 1)
    l = L[go(x, dep[x] - dep[z] - 1)], r = R[go(y, dep[y] - dep[z] - 1)];
  // the linear node is special-cased because it is not necessarily the smallest continuous segment containing l, r.
  // every subrange of a linear node's range is also a continuous segment, and we only need one of them.
  else
    l = L[z], r = R[z];
  printf("%d %d\n", l, r);
}

int main() {
  scanf("%d", &n);
  for (int i = 1; i <= n; ++i) scanf("%d", &a[i]);
  D.build();
  build();
  dfs(rt);
  scanf("%d", &m);
  for (int i = 1; i <= m; ++i) {
    int x, y;
    scanf("%d%d", &x, &y);
    query(x, y);
  }
  return 0;
}

// 20190612
// permutation tree (divide-combine tree)
```

## References and links

[Da Mi Bing's blog - [Study notes] Permutation tree](https://www.cnblogs.com/Paul-Guderian/p/11020708.html)

[^ref1]: Liu Cheng'ao. A simple data structure for continuous segments. WC2019 camper exchange talk.
