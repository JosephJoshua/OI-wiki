## Introduction

The Link/Cut Tree is a data structure used to solve **dynamic tree problems**.

The Link/Cut Tree is also called the Link-Cut Tree, or LCT for short. But it is not called a "dynamic tree": "dynamic tree" refers to a class of problems.

The Splay Tree is the foundation of the LCT, but the Splay Tree used in an LCT differs from an ordinary Splay in some details (it has some extensions).

## Motivating problem

Maintain a tree that supports the following operations:

-   Update the weights on the path between two vertices.
-   Query the sum of weights on the path between two vertices.
-   Update the weights in the subtree of a vertex.
-   Query the sum of weights in the subtree of a vertex.

This is a standard heavy-light decomposition template problem.

But now add one more operation:

-   Cut and link some edges, while guaranteeing the result is still a tree.

The answers above must be computed online.

This turns it into a dynamic tree problem, which can be solved with an LCT.

## Dynamic tree problems

Maintain a **forest** that supports deleting an edge and adding an edge, with the guarantee that it is still a forest after each addition or deletion. We need to maintain some information about this forest.

Common operations include checking whether two vertices are connected, the sum of weights on the path between two vertices, linking two vertices, cutting an edge, updating information, and so on.

### Reviewing heavy-light decomposition from the LCT point of view

-   Decompose the whole tree by subtree size, and relabel the vertices.
-   After relabeling, the tree is made of contiguous ranges, one per chain, and range operations can be done on them with a segment tree.

### Moving to dynamic tree problems

The heavy-light decomposition we just described splits the tree based on subtree sizes. Can we define a different kind of decomposition that suits dynamic tree problems better?

Let's think about what kind of chains dynamic tree problems need.

Since we maintain a forest dynamically, we clearly want these chains to be ones we choose ourselves, so that we can use them to solve the problem.

## Preferred-path decomposition

Among the edges from a vertex to all its children, we choose one edge ourselves for the decomposition. The chosen edge is called a preferred (solid) edge, and the other edges are called light (dashed) edges. For a preferred edge, the child it connects to is called the preferred child. A chain made of preferred edges is called a preferred path. Remember the most important reason for choosing this decomposition: it is chosen by us, so it is flexible and can change. Because of this flexibility, we use Splay Trees to maintain these preferred paths.

## LCT

Simply put, you can think of an LCT as using several Splays to maintain a dynamic path decomposition of a tree, so that range operations can be done on a dynamic tree. For each preferred path, we build a Splay to maintain information about the whole path.

## Auxiliary tree

Let's first look at some properties of the auxiliary tree, and then look at a figure to see its actual structure.

In this article, you can think of several Splays as forming one auxiliary tree, where each auxiliary tree maintains one tree. Several auxiliary trees form the LCT, which maintains the whole forest.

1.  An auxiliary tree consists of several Splays. Each Splay maintains one path in the original tree, and the in-order traversal of the Splay gives the vertices of that path in "top-to-bottom" order in the original tree.
2.  Each vertex of the original tree corresponds one-to-one with a Splay node of the auxiliary tree.
3.  The Splays in an auxiliary tree are not independent. The parent of each Splay's root would normally be empty, but in an LCT the parent of each Splay's root points to the parent of **this path** in the original tree (that is, the parent of the topmost vertex of the path). Unlike an ordinary Splay parent link, here the child knows its parent but the parent does not know the child. This corresponds to a **virtual edge** in the original tree. So in each connected component, exactly one vertex has an empty parent.
4.  Because of these properties of the auxiliary tree, we never need to maintain the original tree for any operation. The auxiliary tree always determines a unique original tree, so we only need to maintain the auxiliary tree.

Now suppose we have an original tree, as shown below. (Bold edges are preferred edges, and dashed edges are virtual edges.)

![tree](images/lct-atree-1.svg)

By the definition above, the auxiliary tree has the structure shown below.

![auxtree](images/lct-atree-2.svg)

### The structural relationship between the original tree and the auxiliary tree

-   A preferred path in the original tree: in the auxiliary tree, its nodes are all in the same Splay.
-   A virtual edge in the original tree: in the auxiliary tree, the Father of the Splay containing the child points to the parent, but neither of the parent's two children points to the child.
-   Note: the root of the original tree is not the same as the root of the auxiliary tree.
-   The Father pointers of the original tree are not the same as the Father pointers of the auxiliary tree.
-   The auxiliary tree can be re-rooted freely as long as the properties of the auxiliary tree and of Splays hold.
-   Switching edges between preferred and light is easy to do on the auxiliary tree. This is how we maintain the path decomposition dynamically.

### Variables used below

-   `ch[N][2]` left and right children
-   `f[N]` parent pointer
-   `sum[N]` sum of weights on the path
-   `val[N]` vertex weight
-   `tag[N]` reversal tag
-   `laz[N]` weight tag
-   `siz[N]` subtree size in the auxiliary tree
-   Other\_Vars

### Functions

#### General data structure functions (as the names say)

1.  `PushUp(x)`
2.  `PushDown(x)`

#### Splay tree functions

Below are the functions used in the Splay tree. For details, see [Splay tree](./splay.md).

1.  `Get(x)` finds which child of its parent $x$ is.
2.  `Splay(x)` works together with Rotate to rotate $x$ to **the root of its current Splay**.
3.  `Rotate(x)` rotates $x$ up by one level.

#### New operations

1.  `Access(x)` puts all vertices from the root to $x$ on one preferred path, so that the path from the root to $x$ is a preferred path and lies in the same Splay. **Only this operation is required; implement the others as the problem needs.**
2.  `IsRoot(x)` checks whether $x$ is the root of the tree (Splay) it is in.
3.  `Update(x)` after `Access`, recursively `PushDown`s from top to bottom to update information.
4.  `MakeRoot(x)` makes $x$ the root of its tree.
5.  `Link(x, y)` adds an edge between $x$ and $y$.
6.  `Cut(x, y)` deletes the edge between $x$ and $y$.
7.  `Find(x)` finds the index of the root of the tree containing $x$.
8.  `Fix(x, v)` changes the weight of $x$ to $v$.
9.  `Split(x, y)` extracts the path between $x$ and $y$, so that range operations are easy.

### Macros

-   `#define ls ch[p][0]`
-   `#define rs ch[p][1]`

## Functions explained

### `PushUp()`

```cpp
void PushUp(int p) {
  // maintain other variables
  siz[p] = siz[ls] + siz[rs] + 1;
}
```

### `PushDown()`

```cpp
void PushDown(int p) {
  if (tag[p] != std_tag) {
    // pushdown the tag
    tag[p] = std_tag;
  }
}
```

### `Splay() && Rotate()`

Here `Splay()` and `Rotate()` differ a little from the Splay tree implementation.

```cpp
#define Get(x) (ch[f[x]][1] == x)

void Rotate(int x) {
  int y = f[x], z = f[y], k = Get(x);
  if (!isRoot(y)) ch[z][ch[z][1] == y] = x;
  // The line above must come first. An ordinary Splay doesn't need this, because of isRoot (explained later)
  ch[y][k] = ch[x][!k], f[ch[x][!k]] = y;
  ch[x][!k] = y, f[y] = x, f[x] = z;
  PushUp(y), PushUp(x);
}

void Splay(int x) {
  Update(
      x);  // You'll see it soon. Before Splay, PushDown all nodes on the path the rotation will pass through
  for (int fa; fa = f[x], !isRoot(x); Rotate(x)) {
    if (!isRoot(fa)) Rotate(Get(fa) == Get(x) ? fa : x);
  }
}
```

For the functions above, see [Splay tree](./splay.md).

Below are the functions unique to LCT.

### `isRoot()`

```cpp
// As we said before, in an LCT, if a child is not a preferred child, its parent cannot find it
// So when a node is neither the left child nor the right child of its parent, it is the root of its current Splay
#define isRoot(x) (ch[f[x]][0] != x && ch[f[x]][1] != x)
```

### `Access()`

```cpp
// Access is the core operation of
// LCT. Imagine we want to solve for a path, and this path happens to be exactly one of our current Splays;
// then we can just use its information directly. Let's look at the code first, then go through the process with figures
int Access(int x) {
  int p;
  for (p = 0; x; p = x, x = f[x]) {
    Splay(x), ch[x][1] = p, PushUp(x);
  }
  return p;
}
```

-   We have this tree, where solid lines are preferred edges and dashed lines are virtual edges.

    ![initial tree](images/lct-access-1.svg)

-   Its auxiliary tree might look like this (different construction orders may give different LCT structures).

    ![initial auxtree](images/lct-access-2.svg)

-   Now we want to `Access(N)`: turn all edges on the path from $A$ to $N$ into preferred edges and pull them into one Splay.

    ![access tree](images/lct-access-3.svg)

-   We do this by updating the Splays step by step from bottom to top.

-   First, rotate $N$ to the root of its current Splay.

-   To keep the properties of the AuxTree (auxiliary tree), the old preferred edge from $N$ to $O$ must become a virtual edge.

-   Since a child knows its parent but not the other way around, we can simply set $N$'s child to `NULL` on its own.

-   So the original AuxTree changes from the figure below to the one after it.

    ![step 1 auxtree](images/lct-access-4.svg)

-   Next, rotate the Father that $N$ points to, $I$, to the root of $I$'s Splay tree.

-   The old preferred edge $I$—$K$ must be removed. Now we point $I$'s right child to $N$, which gives the Splay $I$—$L$.

    ![step 2 auxtree](images/lct-access-5.svg)

-   Next, following the same steps, since $I$'s Father points to $H$, we rotate $H$ to the root of its Splay Tree and then set $H$'s rs to $I$.

-   The tree afterward looks like this.

    ![step 3 auxtree](images/lct-access-6.svg)

-   Similarly, we `Splay(A)` and point $A$'s right child to $H$.

-   So we get this AuxTree, and we see that the whole path $A$—$N$ is now in the same Splay.

    ![step final auxtree](images/lct-access-7.svg)

```cpp
// Let's review the code
int Access(int x) {
  int p;
  for (p = 0; x; p = x, x = f[x]) {
    Splay(x), ch[x][1] = p, PushUp(x);
  }
  return p;
}
```

As you can see, `Access()` is actually quite easy. It has only four steps:

1.  Rotate the current node to the root.
2.  Replace its (right) child with the previous node.
3.  Update the current node's information.
4.  Move to the current node's parent and continue.

The Access given here also has a return value. It is the index of the light-edge parent at the last preferred/light switch. This value has two meanings:

-   When Access is called twice in a row, the return value of the second Access is the LCA of the two vertices.
-   It is the root of the Splay tree containing the path from $x$ to the root. This node must already have been rotated to the root, and its parent must be empty.

### `Update()`

```cpp
// Just pushDown level by level from top to bottom
void Update(int p) {
  if (!isRoot(p)) Update(f[p]);
  pushDown(p);
}
```

### `makeRoot()`

-   `Make_Root()` is just as important as `Access()`. When we maintain path information, there will always be paths whose depths are not strictly increasing, and by the properties of the AuxTree, such a path cannot appear in a single Splay.
-   This is when we need `Make_Root()`.
-   `Make_Root()` makes a given vertex the root of the original tree. Let's think about how to implement it.
-   Let the return value of `Access(x)` be $y$. Then the path from $x$ to the current root forms exactly one Splay, and the root of that Splay is $y$.
-   Represent the tree as a directed graph, giving each edge a direction from child to parent. It is easy to see that re-rooting is the same as reversing all edges on the path from $x$ to the root (think about this carefully).
-   So we just reverse the path from $x$ to the current root.
-   Since $y$ is the root of the Splay representing the path from $x$ to the current root, we just reverse the range of the Splay tree rooted at $y$.

```cpp
void makeRoot(int p) {
  p = Access(p);
  swap(ch[p][0], ch[p][1]);
  tag[p] ^= 1;
}
```

### `Link()`

-   Linking two vertices is actually simple: first `Make_Root(x)`, then point $x$'s parent to $y$. Clearly this operation cannot happen within the same tree, so remember to check that first.

```cpp
void Link(int x, int p) {
  makeRoot(x);
  splay(x);
  f[x] = p;
}
```

### `Split()`

-   The meaning of `Split` is simple: it pulls out a Splay that maintains the path from $x$ to $y$.
-   First `MakeRoot(x)`, then `Access(y)`. If you want $y$ as the root, also `Splay(y)`.
-   Also, these three steps of Split bring the needed path directly into $y$'s subtree, where other operations can be done.

### `Cut()`

-   `Cut` has two cases: the edge is guaranteed to exist, or it is not.
-   If it is guaranteed to exist, just `Split(x, y)`. Now $y$ is the root and $x$ must be its child, so cut the link in both directions. Like this:

```cpp
void Cut(int x, int p) { makeRoot(x), Access(p), Splay(p), ls = f[x] = 0; }
```

If the edge is not guaranteed to exist, we need to check whether it does. One option is to store edges in a `map`, but there is also a way that uses the structure's properties:

To delete an edge, the following three conditions must hold:

1.  $x$ and $y$ are connected.
2.  There are no other vertices on the path between $x$ and $y$.
3.  $x$ has no right child.

In short, these three statements all say one thing: there is an edge between $x$ and $y$.

The concrete implementation is left as an exercise. Checking connectivity uses the `Find` described later; for the other two points, a little thought about the structure will tell you how to check them.

### `Find()`

-   `Find()` finds the root of the **original tree** containing $x$. Don't confuse the root of the original tree with the root of the auxiliary tree. After `Access(p)`, do `Splay(p)`. Now the root is the vertex with the smallest depth in the tree, so just keep walking to the left child, calling `PushDown` along the way.
-   Walk until there is no ls. Very simple.
-   Note: after each query, `Splay` the node found as the answer to the top to keep the complexity bound.

```cpp
int Find(int p) {
  Access(p);
  Splay(p);
  pushDown(p);
  while (ls) p = ls, pushDown(p);
  Splay(p);
  return p;
}
```

### Things to watch out for

-   Before each operation, always think about whether you need `PushUp` or `PushDown`. Because an LCT is so flexible, missing a single `Pushdown` or `Pushup` can apply an update to the wrong vertices!
-   The LCT's `Rotate` differs from the Splay's: `if (z)` must come first.
-   The LCT's `Splay` only rotates a node to the root. There is no operation to rotate it to be the child of some node, because it is not needed.

## Time complexity

Most operations in an LCT are based on `Access`, and the rest take constant time. So we only need to analyze the time complexity of `Access`.

The time of `Access` mainly comes from the many splay operations and from visiting the virtual edges on the path. Below we analyze these two parts separately.

1.  splay

    -   Define $w(x) = \log size(x)$, where $size(x)$ is the total number of light and preferred edges under $x$ (in the subtree rooted at $x$).

    -   Define the potential function $\Phi = \sum_{x \in T} w(x)$, where $T$ is the set of all nodes.

    From the analysis of [the time complexity of Splay](./splay.md#time-complexity), it is easy to see that a splay operation takes amortized $O(\log n)$ time.

2.  Visiting virtual edges

    Following [heavy-light decomposition](../graph/hld.md#heavy-light-decomposition), we define two kinds of virtual edges:

    -   **Heavy virtual edge**: a virtual edge from node $v$ to its parent where $size(v) > \frac{1}{2} size(parent(v))$.

    -   **Light virtual edge**: a virtual edge from node $v$ to its parent where $size(v) \leq \frac{1}{2} size(parent(v))$.

    To handle virtual edges, we can use potential analysis. Define the potential function $\Phi$ as the number of heavy virtual edges, and define the amortized cost $c_i = t_i + \Delta \Phi_i$, where $t_i$ is the actual cost of the operation and $\Delta \Phi_i$ is the change in potential.

    -   Passing through a heavy virtual edge turns it into a preferred edge, which decreases the potential by $1$, since it improves the tree structure by strengthening an important connection. Its actual cost is $O(1)$, which is canceled out by the change in potential, so it does not add to the amortized cost. All of the amortized cost is concentrated on handling light virtual edges.

    -   Each `Access` passes through at most $O(\log n)$ light virtual edges, so it spends at most $O(\log n)$ actual cost and creates at most $O(\log n)$ heavy virtual edges, meaning the potential increases by $O(\log n)$.

    So the final amortized cost of visiting virtual edges is the sum of the actual cost and the change in potential, which is $O(\log n)$.

In summary, the time of `Access` in an LCT is the sum of the costs of splaying and of visiting virtual edges, so the final amortized complexity is $O(\log n)$. That is, for an LCT with n nodes, doing m `Access` operations takes $O(n \log n + m \log n)$ time. So operations based on `Access`, such as `Cut`, `Link` and `Findroot`, also take amortized $O(\log n)$.

## Exercises

-   [BZOJ 3282 Tree](https://hydro.ac/p/bzoj-P3282)
-   [HNOI2010 Bounce the Sheep](https://www.luogu.com.cn/problem/P3203)

## Maintaining path information

With `Split(x,y)`, an LCT can pull the path from $x$ to $y$ in the tree into the Splay rooted at $y$. Updating and querying path information then becomes operations on a balanced binary search tree, which gives the LCT an advantage for maintaining path information. Also, binary search on a tree path done with an LCT costs one $O(\log n)$ factor less than with heavy-light decomposition.

???+ note "Example problem [National Training Team Tree II](https://www.luogu.com.cn/problem/P1501)"
    Given a tree with $n$ nodes, each with initial weight $1$. There are $q$ operations, each one of the following four:
    
    1.  `- u1 v1 u2 v2`: delete the edge between $u_1$ and $v_1$, and connect $u_2$ and $v_2$. The operation is guaranteed to be valid and the result is still a tree.
    2.  `+ u v c`: add $c$ to the weights of all vertices on the path between $u$ and $v$.
    3.  `* u v c`: multiply the weights of all vertices on the path between $u$ and $v$ by $c$.
    4.  `/ u v`: output the sum of the weights of the vertices on the path between $u$ and $v$, modulo $51061$.
    
        $1\le n,q\le 10^5,0\le c\le 10^4$
    
        The `-` operation can be done directly as `Cut(u1,v1),Link(u2,v2)`.

To update the path between $u$ and $v$ in the tree, first `Split(u,v)`.

This problem needs subtree add, subtree multiply and subtree sum on the auxiliary tree. So besides the subtree reversal tag that every LCT maintains, we also need a subtree addition tag and a subtree multiplication tag. The tags are handled the same way as in a Splay.

When applying and pushing down the addition tag, the change in the subtree's sum depends on the number of nodes in the subtree, so we also need to maintain the subtree size `siz`.

When pushing down tags, watch the order: push down the multiplication tag first, then the addition tag. The subtree reversal tag does not conflict with the add/multiply tags.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    using namespace std;
    constexpr long long MAXN = 100010;
    constexpr long long mod = 51061;
    long long n, q, u, v, c;
    char op;
    
    struct Splay {
      long long ch[MAXN][2], fa[MAXN], siz[MAXN], val[MAXN], sum[MAXN], rev[MAXN],
          add[MAXN], mul[MAXN];
    
      void clear(long long x) {
        ch[x][0] = ch[x][1] = fa[x] = siz[x] = val[x] = sum[x] = rev[x] = add[x] =
            0;
        mul[x] = 1;
      }
    
      long long getch(long long x) { return (ch[fa[x]][1] == x); }
    
      long long isroot(long long x) {
        clear(0);
        return ch[fa[x]][0] != x && ch[fa[x]][1] != x;
      }
    
      void maintain(long long x) {
        clear(0);
        siz[x] = (siz[ch[x][0]] + 1 + siz[ch[x][1]]) % mod;
        sum[x] = (sum[ch[x][0]] + val[x] + sum[ch[x][1]]) % mod;
      }
    
      void pushdown(long long x) {
        clear(0);
        if (mul[x] != 1) {
          if (ch[x][0])
            mul[ch[x][0]] = (mul[x] * mul[ch[x][0]]) % mod,
            val[ch[x][0]] = (val[ch[x][0]] * mul[x]) % mod,
            sum[ch[x][0]] = (sum[ch[x][0]] * mul[x]) % mod,
            add[ch[x][0]] = (add[ch[x][0]] * mul[x]) % mod;
          if (ch[x][1])
            mul[ch[x][1]] = (mul[x] * mul[ch[x][1]]) % mod,
            val[ch[x][1]] = (val[ch[x][1]] * mul[x]) % mod,
            sum[ch[x][1]] = (sum[ch[x][1]] * mul[x]) % mod,
            add[ch[x][1]] = (add[ch[x][1]] * mul[x]) % mod;
          mul[x] = 1;
        }
        if (add[x]) {
          if (ch[x][0])
            add[ch[x][0]] = (add[ch[x][0]] + add[x]) % mod,
            val[ch[x][0]] = (val[ch[x][0]] + add[x]) % mod,
            sum[ch[x][0]] = (sum[ch[x][0]] + add[x] * siz[ch[x][0]] % mod) % mod;
          if (ch[x][1])
            add[ch[x][1]] = (add[ch[x][1]] + add[x]) % mod,
            val[ch[x][1]] = (val[ch[x][1]] + add[x]) % mod,
            sum[ch[x][1]] = (sum[ch[x][1]] + add[x] * siz[ch[x][1]] % mod) % mod;
          add[x] = 0;
        }
        if (rev[x]) {
          if (ch[x][0]) rev[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
          if (ch[x][1]) rev[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
          rev[x] = 0;
        }
      }
    
      void update(long long x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void print(long long x) {
        if (!x) return;
        pushdown(x);
        print(ch[x][0]);
        printf("%lld ", x);
        print(ch[x][1]);
      }
    
      void rotate(long long x) {
        long long y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        maintain(z);
      }
    
      void splay(long long x) {
        update(x);
        for (long long f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(long long x) {
        for (long long f = 0; x; f = x, x = fa[x])
          splay(x), ch[x][1] = f, maintain(x);
      }
    
      void makeroot(long long x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        rev[x] ^= 1;
      }
    
      long long find(long long x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    } st;
    
    main() {
      scanf("%lld%lld", &n, &q);
      for (long long i = 1; i <= n; i++) st.val[i] = 1, st.maintain(i);
      for (long long i = 1; i < n; i++) {
        scanf("%lld%lld", &u, &v);
        if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
      }
      while (q--) {
        scanf(" %c%lld%lld", &op, &u, &v);
        if (op == '+') {
          scanf("%lld", &c);
          st.makeroot(u), st.access(v), st.splay(v);
          st.val[v] = (st.val[v] + c) % mod;
          st.sum[v] = (st.sum[v] + st.siz[v] * c % mod) % mod;
          st.add[v] = (st.add[v] + c) % mod;
        }
        if (op == '-') {
          st.makeroot(u);
          st.access(v);
          st.splay(v);
          if (st.ch[v][0] == u && !st.ch[u][1]) st.ch[v][0] = st.fa[u] = 0;
          scanf("%lld%lld", &u, &v);
          if (st.find(u) != st.find(v)) st.makeroot(u), st.fa[u] = v;
        }
        if (op == '*') {
          scanf("%lld", &c);
          st.makeroot(u), st.access(v), st.splay(v);
          st.val[v] = st.val[v] * c % mod;
          st.sum[v] = st.sum[v] * c % mod;
          st.mul[v] = st.mul[v] * c % mod;
        }
        if (op == '/')
          st.makeroot(u), st.access(v), st.splay(v), printf("%lld\n", st.sum[v]);
      }
      return 0;
    }
    ```

### Exercises

-   [Luogu P3690 [Template] Link Cut Tree (Dynamic Tree)](https://www.luogu.com.cn/problem/P3690)
-   [SDOI2011 Coloring](https://www.luogu.com.cn/problem/P2486)
-   [SHOI2014 Trigeminal Nerve Tree](https://loj.ac/problem/2187)

## Maintaining connectivity

### Checking connectivity

Using the LCT's `Find()` function, we can check whether two vertices in a dynamic forest are connected. If `Find(x)==Find(y)`, then $x$ and $y$ are in the same tree and are connected.

???+ note "Example problem [SDOI2008 Cave Exploration](https://www.luogu.com.cn/problem/P2147)"
    Initially there are $n$ separate vertices and $m$ operations. Each operation is one of the following:
    
    1.  `Connect u v`: add an edge between $u$ and $v$.
    2.  `Destroy u v`: delete the edge between $u$ and $v$. It is guaranteed that such an edge exists.
    3.  `Query u v`: ask whether $u$ and $v$ are connected.
    
    It is guaranteed that the graph is a forest at all times.
    
    $n\le 10^4, m\le 2\times 10^5$

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    using namespace std;
    constexpr int MAXN = 10010;
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], tag[MAXN];
    
      void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = 0; }
    
      int getch(int x) { return ch[fa[x]][1] == x; }
    
      int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
          if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
          tag[x] = 0;
        }
      }
    
      void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
      }
    
      void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f;
      }
    
      void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
      }
    
      int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    } st;
    
    int n, q, x, y;
    char op[MAXN];
    
    int main() {
      scanf("%d%d", &n, &q);
      while (q--) {
        scanf("%s%d%d", op, &x, &y);
        if (op[0] == 'Q') {
          if (st.find(x) == st.find(y))
            printf("Yes\n");
          else
            printf("No\n");
        }
        if (op[0] == 'C')
          if (st.find(x) != st.find(y)) st.makeroot(x), st.fa[x] = y;
        if (op[0] == 'D') {
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          if (st.ch[y][0] == x && !st.ch[x][1]) st.ch[y][0] = st.fa[x] = 0;
        }
      }
      return 0;
    }
    ```

### Maintaining 2-edge-connected components

Suppose we need to contract each 2-edge-connected component into a single vertex. Each time an edge is added, if the two tree vertices it connects are already connected, then all vertices on the path between them are contracted into one vertex.

???+ note "Example problem [AHOI2005 Route Planning](https://www.luogu.com.cn/problem/P2542)"
    Given $n$ vertices and initially $m$ undirected edges, there are $q$ operations, each one of the following:
    
    1.  `0 u v`: delete the edge between $u$ and $v$. It is guaranteed that such an edge exists at that time.
    2.  `1 u v`: query the number of edges that every possible path between $u$ and $v$ must pass through at this time.
    
    It is guaranteed that the graph is connected at all times.
    
    $1<n<3\times 10^4,1<m<10^5,0\le q\le 4\times 10^4$

Notice that the number of edges every possible path between $u$ and $v$ must pass through equals, after contracting all 2-edge-connected components into vertices, the number of vertices on the path between the vertex containing $u$ and the vertex containing $v$, minus $1$.

Since edge deletion is hard to handle, we process the operations offline in reverse order, turning edge deletions into edge additions.

When adding an edge, if the two vertices were not connected before, link them in the LCT. Otherwise, extract the path between these two vertices in the LCT before adding the edge, and traverse this subtree of the auxiliary tree, which is the same as traversing this path. Merge these vertices, and use a DSU to keep track of the merges.

Replace the original path in the tree with the representative element of the merged DSU set. Note that every later operation must first find the DSU representative of the vertices it operates on.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <map>
    using namespace std;
    constexpr int MAXN = 200010;
    int f[MAXN];
    
    int findp(int x) { return f[x] ? f[x] = findp(f[x]) : x; }
    
    void merge(int x, int y) {
      x = findp(x);
      y = findp(y);
      if (x != y) f[x] = y;
    }
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], tag[MAXN], siz[MAXN];
    
      void clear(int x) { ch[x][0] = ch[x][1] = fa[x] = tag[x] = siz[x] = 0; }
    
      int getch(int x) { return ch[findp(fa[x])][1] == x; }
    
      int isroot(int x) {
        return ch[findp(fa[x])][0] != x && ch[findp(fa[x])][1] != x;
      }
    
      void maintain(int x) {
        clear(0);
        if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]];
      }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) tag[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
          if (ch[x][1]) tag[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
          tag[x] = 0;
        }
      }
    
      void print(int x) {
        if (!x) return;
        pushdown(x);
        print(ch[x][0]);
        printf("%d ", x);
        print(ch[x][1]);
      }
    
      void update(int x) {
        if (!isroot(x)) update(findp(fa[x]));
        pushdown(x);
      }
    
      void rotate(int x) {
        x = findp(x);
        int y = findp(fa[x]), z = findp(fa[y]), chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        if (z) maintain(z);
      }
    
      void splay(int x) {
        x = findp(x);
        update(x);
        for (int f = findp(fa[x]); f = findp(fa[x]), !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = findp(fa[x]))
          splay(x), ch[x][1] = f, maintain(x);
      }
    
      void makeroot(int x) {
        x = findp(x);
        access(x);
        splay(x);
        tag[x] ^= 1;
        swap(ch[x][0], ch[x][1]);
      }
    
      int find(int x) {
        x = findp(x);
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    
      void dfs(int x) {
        pushdown(x);
        if (ch[x][0]) dfs(ch[x][0]), merge(ch[x][0], x);
        if (ch[x][1]) dfs(ch[x][1]), merge(ch[x][1], x);
      }
    } st;
    
    int n, m, q, x, y, cur, ans[MAXN];
    
    struct oper {
      int op, a, b;
    } s[MAXN];
    
    map<pair<int, int>, int> mp;
    
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) st.maintain(i);
      for (int i = 1; i <= m; i++)
        scanf("%d%d", &x, &y), mp[{x, y}] = mp[{y, x}] = 1;
      while (scanf("%d", &s[++q].op)) {
        if (s[q].op == -1) {
          q--;
          break;
        }
        scanf("%d%d", &s[q].a, &s[q].b);
        if (!s[q].op) mp[{s[q].a, s[q].b}] = mp[{s[q].b, s[q].a}] = 0;
      }
      reverse(s + 1, s + q + 1);
      for (map<pair<int, int>, int>::iterator it = mp.begin(); it != mp.end(); it++)
        if (it->second) {
          mp[{it->first.second, it->first.first}] = 0;
          x = findp(it->first.first);
          y = findp(it->first.second);
          if (st.find(x) != st.find(y))
            st.makeroot(x), st.fa[x] = y;
          else {
            if (x == y) continue;
            st.makeroot(x);
            st.access(y);
            st.splay(y);
            st.dfs(y);
            int t = findp(y);
            st.fa[t] = findp(st.fa[y]);
            st.ch[t][0] = st.ch[t][1] = 0;
            st.maintain(t);
          }
        }
      for (int i = 1; i <= q; i++) {
        if (s[i].op == 0) {
          x = findp(s[i].a);
          y = findp(s[i].b);
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          st.dfs(y);
          int t = findp(y);
          st.fa[t] = st.fa[y];
          st.ch[t][0] = st.ch[t][1] = 0;
          st.maintain(t);
        }
        if (s[i].op == 1) {
          x = findp(s[i].a);
          y = findp(s[i].b);
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          ans[++cur] = st.siz[y] - 1;
        }
      }
      for (int i = cur; i >= 1; i--) printf("%d\n", ans[i]);
      return 0;
    }
    ```

### Exercises

-   [Luogu P3950 Tribal Conflict](https://www.luogu.com.cn/problem/P3950)
-   [BZOJ 4998 Planet Alliance](https://hydro.ac/p/bzoj-P4998)
-   [BZOJ 2959 Long Run](https://hydro.ac/p/bzoj-P2959)

## Maintaining edge weights

An LCT cannot handle edge weights directly. Instead, create a vertex for each edge, so that edge information on a path is easy to query. With this trick, a spanning tree can be maintained dynamically.

???+ note "Example problem [Luogu P4234 Minimum Difference Spanning Tree](https://www.luogu.com.cn/problem/P4234)"
    Given a weighted undirected graph with $n$ vertices and $m$ edges, find the spanning tree that minimizes the difference between its maximum and minimum edge weights, and output this difference.
    
    At least one spanning tree is guaranteed to exist.
    
    $1\le n\le 5\times 10^4,1\le m\le 2\times 10^5,1\le w_i\le 10^4$

Sort the edges by weight in increasing order and enumerate the rightmost chosen edge. To get the optimal answer, we need the smallest edge weight to be as large as possible.

Add edges in this order. If the two vertices to be connected are already connected, delete the edge with the smallest weight between them. If the whole graph is now connected into a tree, update the answer with the current edge weight minus the smallest edge weight. The smallest edge weight can be updated with two pointers.

An LCT has no fixed parent-child relationship, so edge weights cannot be stored as vertex weights.

To record information about edges on a tree path, we can **split edges**: create a vertex for each edge and connect it to both endpoints of that edge. Each original link or cut then becomes two operations.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    #include <set>
    using namespace std;
    constexpr int MAXN = 5000010;
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], tag[MAXN], val[MAXN], minn[MAXN];
    
      void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = tag[x] = val[x] = minn[x] = 0;
      }
    
      int getch(int x) { return ch[fa[x]][1] == x; }
    
      int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    
      void maintain(int x) {
        if (!x) return;
        minn[x] = x;
        if (ch[x][0]) {
          if (val[minn[ch[x][0]]] < val[minn[x]]) minn[x] = minn[ch[x][0]];
        }
        if (ch[x][1]) {
          if (val[minn[ch[x][1]]] < val[minn[x]]) minn[x] = minn[ch[x][1]];
        }
      }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) tag[ch[x][0]] ^= 1, swap(ch[ch[x][0]][0], ch[ch[x][0]][1]);
          if (ch[x][1]) tag[ch[x][1]] ^= 1, swap(ch[ch[x][1]][0], ch[ch[x][1]][1]);
          tag[x] = 0;
        }
      }
    
      void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void print(int x) {
        if (!x) return;
        pushdown(x);
        print(ch[x][0]);
        printf("%d ", x);
        print(ch[x][1]);
      }
    
      void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        if (z) maintain(z);
      }
    
      void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = fa[x]) splay(x), ch[x][1] = f, maintain(x);
      }
    
      void makeroot(int x) {
        access(x);
        splay(x);
        tag[x] ^= 1;
        swap(ch[x][0], ch[x][1]);
      }
    
      int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    
      void link(int x, int y) {
        makeroot(x);
        fa[x] = y;
      }
    
      void cut(int x, int y) {
        makeroot(x);
        access(y);
        splay(y);
        ch[y][0] = fa[x] = 0;
        maintain(y);
      }
    } st;
    
    constexpr int inf = 2e9 + 1;
    int n, m, ans, nww, x, y;
    
    struct Edge {
      int u, v, w;
    
      bool operator<(Edge x) const { return w < x.w; };
    } s[MAXN];
    
    multiset<int> mp;
    
    int main() {
      scanf("%d%d", &n, &m);
      for (int i = 1; i <= n; i++) st.val[i] = inf, st.maintain(i);
      for (int i = 1; i <= m; i++) scanf("%d%d%d", &s[i].u, &s[i].v, &s[i].w);
      sort(s + 1, s + m + 1);
      for (int i = 1; i <= m; i++) st.val[n + i] = s[i].w, st.maintain(n + i);
      for (int i = 1; i <= m; i++) {
        x = s[i].u;
        y = s[i].v;
        if (x == y) continue;
        if (st.find(x) != st.find(y)) {
          nww++;
          st.link(x, n + i);
          st.link(n + i, y);
          mp.insert(s[i].w);
          if (nww == n - 1) ans = s[i].w - (*(mp.begin()++));
        } else {
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          int t = st.minn[y] - n;
          st.cut(s[t].u, t + n);
          st.cut(t + n, s[t].v);
          mp.erase(mp.find(s[t].w));
          st.link(x, n + i);
          st.link(n + i, y);
          mp.insert(s[i].w);
          if (nww == n - 1) ans = min(ans, s[i].w - (*(mp.begin()++)));
        }
      }
      printf("%d\n", ans);
      return 0;
    }
    ```

### Exercises

-   [WC2006 Water Pipe Director](https://www.luogu.com.cn/problem/P4172)
-   [BJWC2010 Strict Second-Minimum Spanning Tree](https://www.luogu.com.cn/problem/P4180)
-   [NOI2014 Magic Forest](https://uoj.ac/problem/3)

## Maintaining subtree information

An LCT is not good at maintaining subtree information. By aggregating the information of all virtual subtrees of a node, we can get information about the whole tree.

???+ note "Example problem [BJOI2014 Great Fusion](https://loj.ac/problem/2230)"
    Given $n$ nodes and $q$ operations, each of the following form:
    
    1.  `A x y` adds an edge between nodes $x$ and $y$.
    2.  `Q x y` given an existing edge $(x,y)$, find how many simple paths contain the edge $(x,y)$.
    
    It is guaranteed that the graph is a forest at all times.
    
    $1\le n,q,x,y\le 10^5$

Let's rephrase the query `Q`. The answer equals the number of nodes on $x$'s side of the edge $(x,y)$ times the number of nodes on $y$'s side, that is, the sizes of the trees containing $x$ and $y$ after cutting the edge $(x,y)$. To undo the cut, we link the edge $(x,y)$ again after the query.

The operations in this problem include both linking and cutting edges, and the graph is guaranteed to be a forest at all times, so an LCT naturally comes to mind. But here the LCT must maintain subtree sizes, unlike the path information we usually maintain, and in an LCT **the child knows its parent but not the other way around**, which makes it hard to aggregate subtrees directly. What can we do?

The method is to aggregate the contributions of the subtrees represented by all virtual children of a node $x$ (children whose parent is $x$ but which are not $x$'s left or right child in the Splay).

Define $siz2[x]$ as the number of nodes in the subtrees represented by all virtual children of node $x$, and $siz[x]$ as the number of nodes in the subtree of node $x$.

Unlike how we usually maintain the number of nodes in a Splay subtree, when computing the number of nodes in the subtree of node $x$, we must also add $siz2[x]$, that is

```cpp
void maintain(int x) {
  clear(0);
  if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]] + siz2[x];
}
```

Also, whenever we **change the shape of the Splay** (that is, change which nodes are a node's left and right children in the Splay), we need to update $siz2[x]$ right away.

In `Rotate(),Splay()`, we only change the relative positions of nodes in the Splay and don't change whether any edge is preferred or light, so $siz2[x]$ is not modified.

In `access`, after each splay, the right child of the node just splayed changes. That is, the edge between this node and its old right child and the edge between this node and its new right child change between preferred and light. We need to add the contribution of the subtree attached by the edge that just became light, and subtract the contribution of the subtree attached by the edge that just became preferred. The code is:

```cpp
void access(int x) {
  for (int f = 0; x; f = x, x = fa[x])
    splay(x), siz2[x] += siz[ch[x][1]] - siz[f], ch[x][1] = f, maintain(x);
}
```

In `MakeRoot(),Find()`, we only call earlier functions or walk along edges in the Splay, so no changes are needed.

When linking two vertices, we change the parent of one node. We need to add the new child's subtree size to the parent's $siz2$ value.

```cpp
st.makeroot(x);
st.makeroot(y);
st.fa[x] = y;
st.siz2[y] += st.siz[x];
```

When cutting an edge, we only delete a preferred edge in the Splay. `Maintain` will keep this information up to date, so no changes are needed.

Those are the details of the code changes. Finally, let's summarize the requirements and method for maintaining subtree information with an LCT:

1.  The maintained information must be **subtractable**, like the number of nodes or the sum of weights in a subtree. Subtree maximum or minimum cannot be maintained directly, because when a virtual edge becomes preferred, the old virtual edge's contribution must be removed.
2.  Add an extra value storing the contribution of virtual subtrees. Include it in the node's answer when aggregating, and update it whenever an edge switches between preferred and light.
3.  Everything else is the same as an ordinary LCT. When aggregating subtree information, always make the node the root first.
4.  If the maintained information is not subtractable, such as a range maximum or minimum, you can keep a balanced binary search tree at each node to maintain the extreme values over the node's virtual subtrees.

??? note "Reference code"
    ```cpp
    #include <algorithm>
    #include <cstdio>
    #include <cstring>
    using namespace std;
    constexpr int MAXN = 100010;
    using ll = long long;
    
    struct Splay {
      int ch[MAXN][2], fa[MAXN], siz[MAXN], siz2[MAXN], tag[MAXN];
    
      void clear(int x) {
        ch[x][0] = ch[x][1] = fa[x] = siz[x] = siz2[x] = tag[x] = 0;
      }
    
      int getch(int x) { return ch[fa[x]][1] == x; }
    
      int isroot(int x) { return ch[fa[x]][0] != x && ch[fa[x]][1] != x; }
    
      void maintain(int x) {
        clear(0);
        if (x) siz[x] = siz[ch[x][0]] + 1 + siz[ch[x][1]] + siz2[x];
      }
    
      void pushdown(int x) {
        if (tag[x]) {
          if (ch[x][0]) swap(ch[ch[x][0]][0], ch[ch[x][0]][1]), tag[ch[x][0]] ^= 1;
          if (ch[x][1]) swap(ch[ch[x][1]][0], ch[ch[x][1]][1]), tag[ch[x][1]] ^= 1;
          tag[x] = 0;
        }
      }
    
      void update(int x) {
        if (!isroot(x)) update(fa[x]);
        pushdown(x);
      }
    
      void rotate(int x) {
        int y = fa[x], z = fa[y], chx = getch(x), chy = getch(y);
        fa[x] = z;
        if (!isroot(y)) ch[z][chy] = x;
        ch[y][chx] = ch[x][chx ^ 1];
        fa[ch[x][chx ^ 1]] = y;
        ch[x][chx ^ 1] = y;
        fa[y] = x;
        maintain(y);
        maintain(x);
        maintain(z);
      }
    
      void splay(int x) {
        update(x);
        for (int f = fa[x]; f = fa[x], !isroot(x); rotate(x))
          if (!isroot(f)) rotate(getch(x) == getch(f) ? f : x);
      }
    
      void access(int x) {
        for (int f = 0; x; f = x, x = fa[x])
          splay(x), siz2[x] += siz[ch[x][1]] - siz[f], ch[x][1] = f, maintain(x);
      }
    
      void makeroot(int x) {
        access(x);
        splay(x);
        swap(ch[x][0], ch[x][1]);
        tag[x] ^= 1;
      }
    
      int find(int x) {
        access(x);
        splay(x);
        while (ch[x][0]) x = ch[x][0];
        splay(x);
        return x;
      }
    } st;
    
    int n, q, x, y;
    char op;
    
    int main() {
      scanf("%d%d", &n, &q);
      while (q--) {
        scanf(" %c%d%d", &op, &x, &y);
        if (op == 'A') {
          st.makeroot(x);
          st.makeroot(y);
          st.fa[x] = y;
          st.siz2[y] += st.siz[x];
        }
        if (op == 'Q') {
          st.makeroot(x);
          st.access(y);
          st.splay(y);
          st.ch[y][0] = st.fa[x] = 0;
          st.maintain(x);
          st.makeroot(x);
          st.makeroot(y);
          printf("%lld\n", (ll)(st.siz[x] * st.siz[y]));
          st.makeroot(x);
          st.makeroot(y);
          st.fa[x] = y;
          st.siz2[y] += st.siz[x];
        }
      }
      return 0;
    }
    ```

### Exercises

-   [Luogu P4299 Capital](https://www.luogu.com.cn/problem/P4299)
-   [SPOJ QTREE5 - Query on a tree V](https://www.spoj.com/problems/QTREE5)
