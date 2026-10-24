author: F7487

## Self-Adjusting Top Tree

### Overview

The Self-Adjusting Top Tree (SATT for short) is a data structure for maintaining fully dynamic forests, based on the theory of Top Trees. It was proposed by Tarjan and Werneck in 2005 in their paper Self-Adjusting Top Trees.

A Self-Adjusting Top Tree supports path updates/queries, subtree updates/queries and non-local searches on any tree in the forest.

The Splay Tree is the foundation of SATT, but the Splay Tree used in SATT differs from an ordinary Splay in some details (it has been extended a bit).

### The problem

Maintain a forest that supports the following operations:

-   Delete or add an edge, with the guarantee that the graph is still a forest before and after the operation.

-   Update the weights on a simple path in some tree.

-   Update the weights in the subtree rooted at some vertex.

-   Query the sum of weights on a simple path in some tree.

-   Query the sum of weights in the subtree rooted at some vertex.

### Tree contraction

Using the theory of **tree contraction**, any tree can be contracted into a single edge.

Concretely, tree contraction has two basic operations: **Compress** and **Rake**. A Compress operation picks a vertex $x$ of degree $2$. Call the two neighbors of $x$ $y$ and $z$. We add a new edge $yz$, store the information of vertex $x$, edge $xz$ and edge $xy$ in $yz$, and delete them. See the figure.

![](./images/top-tree1.svg)

A Rake operation picks a vertex $x$ of degree $1$ whose neighbor $y$ has degree greater than $1$. Let $z$ be another neighbor of $y$. We store the information of vertex $x$ and edge $xy$ in edge $yz$, and delete them. See the figure.

![](./images/top-tree2.svg)

It is not hard to prove that any tree can be contracted into a single edge using only Compress and Rake operations, as shown in the figure.

![](./images/top-tree3.svg)

### Clusters

For convenience, let $T$ be the original tree before any operation. Let $T_x$ be the tree after applying some tree contraction operations to $T$ (possibly none).

Let us study what information an edge in some $T_x$ carries.

Besides its own information (of course, if this edge does not exist in $T$, it has no information of its own), this edge may also carry the information of other vertices and edges that were merged into it by Compress/Rake operations. Let us pick an edge from the tree contraction process in the figure below and see which vertices and edges of $T$ its information stands for.

![](./images/top-tree4.svg)

In the figure, the chosen edge and the corresponding part of the graph are circled in red.

We can see that the vertices and edges of $T$ represented by the information of this edge are connected. More generally, the information stored on any edge of any $T_x$ always corresponds to a connected subgraph of $T$. We call such a connected subgraph a **cluster**.

However, a cluster is an **incomplete subgraph**: some of its edges have endpoints that are not part of the cluster itself. We call these endpoints the **endpoints** of the cluster, the vertices of the connected subgraph its **internal nodes**, and the edges of the connected subgraph its **internal edges**.

Every cluster has the following properties:

1.  A cluster only stores and maintains the information of its internal nodes and internal edges.

2.  A cluster has two endpoints. They are the two vertices joined by the edge of $T_x$ that represents the cluster. The path between the two endpoints is called the **cluster path**. If the two endpoints of a cluster are $x$ and $y$, we write the cluster as $C(x,y)$ below.

3.  Internal nodes are only adjacent to endpoints or other internal nodes.

In particular, each edge of $T$ is a cluster on its own (containing only the edge's own information). Such clusters are called **base clusters**. When $T$ is contracted down to a final $T_x$ with only one edge, the cluster represented by that edge contains the information of the whole $T$ except for its two endpoints. This cluster is called the **root cluster**.

![](./images/top-tree5.svg)

In the figure, the base clusters mentioned above are marked in red.

Looking at Compress/Rake from the point of view of clusters, both operations "merge two clusters into one", leaving one new cluster. So tree contraction is also the process of merging all base clusters into one cluster.

So we can also get the figure below, which is another way to represent a series of tree contraction operations.

![](./images/top-tree6.svg)

### Top Tree

Now we want to represent the whole process of contracting a tree.

We could use either of the two methods above, but that is very cumbersome: if the tree contraction takes $n$ steps, we need $n$ trees to represent the whole contraction.

To get a simpler representation of a particular contraction of a tree, we introduce the **Top Tree**.

![](./images/top-tree7.jpg)

The figure shows a Top Tree built from the contraction and the original tree used above.

A Top Tree has the following properties:

1.  A Top Tree corresponds to an original tree and one way to contract it. Each node of the Top Tree represents an edge in some $T_x$, that is, a cluster formed during tree contraction. A node of the form $N_x$ in the figure represents the cluster formed by the operation `compress(x)`.

2.  A node in a Top Tree has two children (each representing a cluster), and the cluster represented by the node is the new cluster obtained by merging these two clusters with a Compress or Rake operation.

3.  The leaves of a Top Tree are base clusters, and its root is the root cluster. So if we split a Top Tree into layers by topological order, each layer represents a $T_x$.

### Maintaining information with a ternarized Self-Adjusting Top Tree

#### Principle

The Top Tree greatly simplifies the tree contraction process, and shows that we can maintain information on a tree by maintaining its contraction process. SATT maintains information on a tree using exactly this principle.

Note that tree contraction is also a process of adding the tree's information bit by bit. When we run `compress(x)`, from that moment on the information of vertex $x$ appears in some cluster and affects the result we compute.

Suppose we now use a Top Tree to maintain some tree $T$, where every vertex and edge has a weight, and we want to maintain the total weight of $T$.

Now suppose we need to change the weight of some vertex $x$ in $T$. Clearly, we have to update every Top Tree node whose cluster information contains $x$. Done this way, a single operation costs $O(n)$ time.

However, if the vertex we pick has only a few Top Tree nodes whose cluster information contains $x$, that is, if its information is added to clusters as late as possible, a single operation becomes much faster. See the figure.

![](./images/top-tree8.jpg)

SATT maintains information on a tree by changing the order in which the information of **a vertex/a path** is added to clusters during tree contraction (to lower the cost of a single update on it).

### Actual structure

We first root the original tree $T$ and split it into layers. Then consider the root cluster of the Top Tree for some contraction order. It has two endpoints. We let one of them be the root of the original tree, and pick the other one freely.

![](./images/top-tree9.jpg)

The figure shows a chosen pair of endpoints for the root cluster. Here, when marking clusters, the endpoints are circled too.

From the basic operations of tree contraction, the information of the vertices and edges on the cluster path $(j,h,c,jh,hc)$ is finally added to $C(k,g)$ through Compress operations, while the vertices off the cluster path $(a,b,i,f,g,e,ig,\cdots)$ are added to $C(k,g)$ through Rake operations.

Take the cluster path out on its own. It is a tree with a special shape (a chain), and we build a top tree for it (with any contraction order).

![](./images/top-tree10.jpg)

We call this structure a **Compress Tree**, because in this Top Tree the two children of any node are merged into their parent by a Compress operation.

The nodes of a Compress Tree are called **Compress Nodes**. Considering only the current cluster path, a non-leaf Compress Node represents one compress step: it merges the information of its left and right children, then adds the information of vertex $x$ stored in this `compress(x)` itself. This Compress Tree maintains the information of the cluster path of $C(k,g)$.

In addition, the Compress Tree actually puts some restrictions on the Top Tree we use. Note that the Compress Tree maintains a chain in $T$ whose vertices all have different depths. We require that in the Compress Tree, the in-order traversal of the base clusters matches the depths of the corresponding edges in $T$, with earlier in-order positions meaning shallower depth. The same holds for the `compress(x)` nodes of each vertex $x$.

Now we maintain the information off the cluster path. Suppose the vertices and edges off the cluster path have already formed maximal clusters, and each maximal cluster is formed by the smaller clusters circled in blue raking onto each other. We represent the process of merging smaller clusters into one maximal cluster with a ternary tree. Similarly, we call this structure a **Rake Tree**, and its nodes are **Rake Nodes**. Each Rake Node represents a cluster, formed by raking its left and right children onto the smaller cluster represented by its middle child. See the figure below for details. Every node of a Rake Tree represents smaller clusters of $T$ that share the same endpoint.

![](./images/top-tree11.jpg)

In the figure, the maximal clusters are circled in blue, and the smaller clusters are circled in yellow.

For those smaller clusters, we do the same thing: choose a cluster path for each, build a Compress Tree, and so on recursively. This builds many Compress Trees and Rake Trees that together represent the tree contraction process.

![](./images/top-tree12.jpg)

The figure above shows the Rake-Compress Tree of the original tree (since each Rake Node is attached to a Compress Tree, it looks like one Rake Tree attached to many Compress Trees) and the Compress Tree representing the root cluster path.

Now consider joining these trees together in some way to make them one ordered whole. Let $x$ be the common endpoint of the set of smallest clusters represented by a Rake Tree. For the middle children of these Rake Nodes (a set of Compress Trees), we add the other endpoint that is not $x$, while still keeping their in-order traversal and the basic properties of a Top Tree. See the figure.

![](./images/top-tree13.jpg)

This step makes the Rake operation that adds some vertex of $T$ happen directly inside the Compress Tree. It not only lets us maintain the information of Rake Nodes correctly (just merge the information of the three children), but also makes the structure of the Compress Tree more complete. Next, we turn the Compress Tree into a ternary tree: if the common endpoint of some Rake Tree is vertex $x$, we hang that Rake Tree at the middle child of `compress(x)`. See the figure.

![](./images/top-tree14.jpg)

Now the meaning of a ternarized `compress(x)` node becomes: first rake its middle child onto the cluster path, then combine the information of its left and right children and vertex $x$.

Finally, we handle the Compress Tree of the root cluster path: just like all the other Compress Trees, add its two endpoints according to the in-order traversal, so that its root stores the information of the whole $T$.

And so we have used a ternarized Self-Adjusting Top Tree to maintain the information of a tree.

![](./images/top-tree15.jpg)

To sum up, SATT has the following properties:

1.  SATT consists of Compress Trees and Rake Trees. A Compress Tree is a special Top Tree; a Rake Tree is a ternary tree. Both correspond to the process of contracting a tree.

2.  A node in a Compress Tree has at most three children. A Compress Tree supports rotations similar to those of a Splay tree (we only need to keep its in-order traversal unchanged; when rotating a node, its middle child stays where it is).

3.  A node in a Rake Tree always has a middle child. A Rake Tree supports rotations similar to those of a Splay tree (we only need to keep its in-order traversal unchanged; when rotating a node, its middle child stays where it is).

4.  The topological order of SATT reflects the tree contraction order of the original tree $T$.

Can SATT really do what we mentioned above, "change the order in which the information of a vertex/a path is added to clusters during tree contraction"? The answer is yes.

SATT has an operation `access(x)`. It makes vertex $x$ the non-root endpoint of the root cluster, and at the same time makes `compress(x)` the root of the SATT.

With `access(x)`, we can rotate the SATT node representing `compress(x)` to the root of the whole SATT in amortized $O(\log n)$ time. By the fourth property of SATT, this changes the order of the `compress(x)` operation so that it is done last, and the information of vertex $x$ is added last. So when we want to change the information of vertex $x$, we only need to update `compress(x)`.

### Implementation

#### Push functions

First consider passing information up, i.e. the `Pushup(x)` function. When maintaining information for a node of SATT, we first split into cases by whether the node is in a Compress Tree or in a Rake Tree. The reason was explained above and is not repeated here. Below, we use maintaining the subtree size of a vertex as the example:

```cpp
// ls(x): left child of x
// rs(x): right child of x
// ms(x): middle child of x
// type==0: Compress Node
// type==1: Rake Node
void pushup(int x, int type) {
  if (type == 0)
    size[x] = size[rs(x)] + size[ms(x)] + 1;
  else
    size[x] = size[rs(x)] + size[ms(x)] + size[ls(x)];
  return;
}
```

To query the subtree size of vertex $x$, access it to the root of the SATT. The answer is the size of its middle child $+1$, because, as explained above, after an access its middle child is exactly its proper subtree.

Next consider passing information down, i.e. the `Pushdown(x)` function. If we want to update a whole subtree of the original tree, a natural idea is: access this node to the root of the SATT, then put a tag on its middle child. Likewise, to query a subtree, access it and then query its middle child.

If we want to update a whole path of the original tree, we expose the two endpoints of the path. Here `expose(x, y)` means making vertex $x$ the root of $T$ and making vertex $y$ the other endpoint of the root cluster. In the SATT, the Compress Tree of the root cluster is then exactly the path from $x$ to $y$. So we just put a tag on the Compress Tree of the root cluster. Likewise, to query a path, expose it and then query the root.

So now we know how to solve the problem from the beginning.

```cpp
void pushdown(int x, int type) {
  if (type == 0) {
    // Handle the path
    chain[ls(x)] += chain[x] chain[rs(x)] += chain[x];
    val[ls(x)] += chain[x];
    val[rs(x)] += chain[x];
    // Handle the subtree
    subtree[ls(x)] += subtree[x];
    subtree[rs(x)] += subtree[x];
    subtree[ms(x)] += subtree[x];
    val[ls(x)] += subtree[x];
    val[rs(x)] += subtree[x];
    val[ms(x)] += subtree[x];
    subtree[x] = 0;
  } else {
    subtree[ls(x)] += subtree[x];
    subtree[rs(x)] += subtree[x];
    subtree[ms(x)] += subtree[x];
    val[ls(x)] += subtree[x];
    val[rs(x)] += subtree[x];
    val[ms(x)] += subtree[x];
    subtree[x] = 0;
  }
  return;
}

// Push down tags
void pushall(int x, int type) {
  if (!isroot(x)) pushall(father[x], type);
  pushdown(x, type);
  return;
}
```

#### Splay functions

We know that both the Rake Trees and the Compress Trees in SATT can be rotated, which means they can be maintained with Splay. So we can write the following code:

```cpp
// isroot: the node is a middle child or has no parent
// ls: left child of a SATT node
// rs: right child of a SATT node
// ms: middle child of a SATT node
// type==1: in a Rake Tree
// type==0: in a Compress Tree
bool isroot(int x) { return rs(father[x]) != x && ls(father[x]) != x; }

bool direction(int x) { return rs(father[x]) == x; }

void rotate(int x, int type) {
  int y = father[x], z = father[y], d = direction(x), w = son[x][d ^ 1];
  if (z) son[z][ms(z) == y ? 2 : direction(y)] = x;
  son[x][d ^ 1] = y;
  son[y][d] = w;
  if (w) father[w] = y;
  father[y] = x;
  father[x] = z;
  pushup(y, type);
  pushup(x, type);
  return;
}

void splay(int x, int type, int goal = 0) {
  pushall(x, type);  // Push down tags
  for (int y; y = father[x], (!isroot(x)) && y != goal; rotate(x, type)) {
    if (father[y] != goal && (!isroot(y))) {
      rotate(direction(x) ^ direction(y) ? x : y, type);
    }
  }
  return;
}
```

Note that the functions `direction` and `isroot` differ from those in an ordinary Splay, because no matter how a node is rotated, its middle child never changes.

#### Access functions

`access(x)` means: rotate vertex $x$ to the root of the whole SATT and make $x$ one of the two endpoints of the root cluster (the other endpoint is the root of $T$), without changing the structure or the root of the original tree.

To implement `access(x)`, we first rotate $x$ to the root of its Compress Tree, then remove the right child of $x$, so that $x$ becomes an endpoint of the cluster corresponding to its Compress Tree.

```cpp
if (rs(x)) {
  int y = new_node();
  setfather(ms(x), y, 0);
  setfather(rs(x), y, 2);
  rs(x) = 0;
  setfather(y, x, 2);
  pushup(y, 1);
  pushup(x, 0);
}
```

If $x$ has now reached the root, stop. If not, do the following steps to move it past the Rake Tree above it:

1.  Splay its parent (which must be a Rake Node) to the root of its Rake Tree;

2.  Splay the grandparent of $x$ (which must be a Compress Node) to the root of its Compress Tree.

3.  If the grandparent of $x$ has a right child, swap vertex x with the grandparent's right child, update the information, then stop.

4.  If the grandparent has no right child, first make $x$ the right child of the grandparent. Now the original parent of $x$ has no middle child, and by the property of Rake Nodes above, it cannot exist. So call the `Delete` function to remove it, then stop.

Steps 1 and 2 together are called a **Local Splay**. Steps 3 and 4 together are called a **Splice**. For convenience, we write both inside the `Splice(x)` function.

The `Delete(x)` function mentioned above works like this:

1.  Check whether the vertex $x$ to delete has a left child. If it does, rotate the successor within the left child's subtree up to just below $x$ (making it the new left child), then make the right child (if any) the right child of that left child. Now the left child of $x$ replaces $x$. This is the same as the merge operation of a Splay.

2.  If there is no left child, simply let the right child replace $x$.

It is easy to see that `Splice(x)` changes the choice of endpoints for some clusters of the original tree. After one splice, we take the parent of $x$ as the new $x$ and do the next splice.

In the end, we find that the vertex $x$ we started with must be at the rightmost end of the root cluster's Compress Tree. We only need to do one final **Global Splay** to rotate it to the root of the SATT.

```cpp
// ls: left child of a SATT node
// rs: right child of a SATT node
// ms: middle child of a SATT node
// son[x][0] ls
// son[x][1] rs
// son[x][2] ms
// type==1: in a Rake Tree
// type==0: in a Compress Tree
int new_node() {
  if (top) {
    top--;
    return Stack[top + 1];
  }
  return ++tot;
}

void setfather(int x, int fa, int type) {
  if (x) father[x] = fa;
  son[fa][type] = x;
}

void Delete(int x) {
  setfather(ms(x), father[x], 1);
  if (ls(x)) {
    int p = ls(x);
    pushdown(p, 1);
    while (rs(p)) p = rs(p), pushdown(p, 1);
    splay(p, 1, x);
    setfather(rs(x), p, 1);
    setfather(p, father[x], 2);
    pushup(p, 1);
    pushup(father[x], 0);
  } else
    setfather(rs(x), father[x], 2);
  Clear(x);
}

void splice(int x) {
  // local splay
  splay(x, 1);
  int y = father[x];
  splay(y, 0);
  pushdown(x, 1);
  // splice
  if (rs(y)) {
    swap(father[ms(x)], father[rs(y)]);
    swap(ms(x), rs(y));
  } else
    Delete(x);
  pushup(x, 1);
  pushup(y, 0);
}

void access(int x) {
  splay(x, 0);
  if (rs(x)) {
    int y = new_node();
    setfather(ms(x), y, 0);
    setfather(rs(x), y, 2);
    rs(x) = 0;
    setfather(y, x, 2);
    pushup(y, 1);
    pushup(x, 0);
  }
  while (father[x]) {
    splice(father[x]);
    x = father[x];
    pushup(x, 0);
  }
  splay(x, 0)  // global splay
}
```

To make a vertex the root of the original tree, we access vertex $x$ to the root of the SATT. Now $x$ is already an endpoint of the final cluster. By the in-order property of the Compress Tree, flipping the Compress Tree containing $x$ left-to-right (swapping the left and right children of every node) makes $x$ the root of the original tree. In the implementation, we do this by putting a reverse tag on $x$ and pushing it down later.

```cpp
void makeroot(int x) {
  access(x);
  push_rev(x);
}
```

Then `expose(x, y)` follows naturally:

```cpp
void expose(int x, int y) {
  makeroot(x);
  access(y);
}
```

### Link & Cut

Now suppose we want to add an edge between two disconnected vertices of the original tree. We first make one vertex $x$ the root of the original tree, then rotate the other vertex $y$ to the root. Now $y$ should become the right child of $x$. Then we hang this edge on the right child of $y$ (in a SATT that only maintains vertices, this step can be skipped).

```cpp
void Link(int x, int y, int z) {
  // z is the edge connecting x and y
  access(x);
  makeroot(y);
  setfather(y, x, 1);
  setfather(z, y, 0);
  pushup(x, 0);
  pushup(y, 0);
}
```

`Cut` works on much the same principle as `Link`:

```cpp
void cut(int x, int y) {
  expose(x, y);
  clear(rs(x));  // Delete the base cluster xy
  father[x] = ls(y) = rs(x);
  pushup(y, 0);
}
```

### Full code

??? note "[Luogu P3690 [Template] Dynamic Tree](https://www.luogu.com.cn/problem/P3690)"
    ```cpp
    --8<-- "docs/ds/code/top-tree/top-tree_1.cpp"
    ```

### Proof of the time complexity of SATT

In a SATT with $n$ nodes, let the potential function of its current state $x$ be

$$
\varphi(x)= \sum_{i=1}^{n} r(i)
$$

where $r(i) = \lceil \log_2 \text{siz}(i) \rceil$, and $\text{siz}(i)$ is the size of the subtree rooted at $i$.

Then the amortized cost of a splay in SATT is clearly still $3n\log n + 1$, even though SATT is a ternary tree.

So for SATT, once we prove that the Access function has the right complexity, we have proved the time complexity of SATT.

Let us analyze the amortized cost of Access step by step.

First we rotate vertex $x$ to the root of its Compress Tree. The amortized cost of this step is

$$
a \leq  3\log n +1
$$

Next we make $x$ have no right child. The amortized cost of this step is

$$
a = 1 + r'(\gamma)- 0 \leq \log n +1
$$

![](./images/top-tree16.jpg)

The figure shows the process of removing the right child of vertex $x$.

Next comes a sequence of alternating Local Splay and Splice steps. After some number of Splices, vertex $x$ is rotated to the root of the SATT. Let us analyze one pair of Local Splay and Splice:

![](./images/top-tree17.jpg)

![](./images/top-tree18.jpg)

![](./images/top-tree19.jpg)

The figures show one Splice on vertex $x$, not including the final left rotation of $x$.

For convenience, let $r_x(i)$ be the $r$ value of node $i$ in state $x$.

From the figure, it is easy to see that the step from state 1 to state 2 (the Local Splay that rotates the parent of $x$ to the root of its Rake Tree) has amortized cost

$$
a \leq  3(r_2(\gamma)- r_1(\gamma))+1
$$

From the figure, it is easy to see that the step from state 2 to state 3 (the Local Splay that rotates the grandparent of $x$ to the root of its Compress Tree) has amortized cost

$$
a \leq  3(r_3(B)- r_2(B))+1
$$

The key step to analyze is the one from state 3 to state 4 (the Splice):

$$
a = r_4(\gamma) -r_3(\gamma) +1
$$

It is easy to see that $r_4(\gamma) \leq r_3(B)$.

So the amortized cost of this step is

$$
\begin{aligned}
a &\leq r_3(B)- r_3(\gamma)+1\\
&\leq 3(r_3(B)- r_3(\gamma))+1\\
\end{aligned}
$$

Putting these steps together, the cost of one Splice is

$$
a\leq 3r_3(B)+3r_3(B)+3r_2(\gamma)-3r_3(\gamma)-3r_2(B)-3r_1(\gamma)+3
$$

Let $r'(X)$ be the $r$ value of the vertex $X$ for the next Splice (i.e. vertex $B$ in state 4). Note that $r_3(\gamma),r_1(\gamma) \ge r_1(X)$, $r_3(B),r_2(\gamma) \leq r'(X)$ and $r_3(B)=r_2(B)$, so

$$
a\leq  9(r'(X)-r(X))+3
$$

Besides this cost, a Splice may also have extra amortized cost from `delete(x)`. Call this part $a' \leq 3\log n +1$.

Ignoring $a'$ for now: the $r'(X)$ of each Splice equals the $r(X)$ of the next one, and the $r(X)$ of the first Splice equals the $r(X)$ from when we first rotated vertex $x$ to the root of its Compress Tree. So for the cost of one `access(x)` without counting `delete(x)`, we have:

$$
a \leq 9(r'(x)-r(x))+ 3k + 1
$$

where $k$ is the number of Splices.

It looks like $a$ carries an extra $3k+1$ that prevents the amortized analysis from working, but we have a way to deal with it. Note that zig-zig/zig-zag rotations can be amortized like this:

$$
\begin{aligned}
a &\leq 3(r'(X)-r(X)) + q\\
&\leq 3(q-1)(r'(X)-r(X))
\end{aligned}
$$

If we can find enough zig-zig and zig-zag steps, we can spread this $3k+1$ over them and cancel it out.

It turns out that the Global Splay has enough zig-zig and zig-zag steps for us to use. The Global Splay must contain more than $k$ nodes, and the path from vertex $x$ to the root in the Global Splay has at least $k$ nodes. So one `access(x)` must contain at least $\dfrac k2$ zig-zag steps. Adding the amortized cost of the Global Splay, $a \leq 3\log n +1$, the amortized cost of one `access(x)` without `delete(x)` is

$$
\begin{aligned}
a&\leq 9(r'(X)-r(X)) + 3k + 1 + 18(r''(X)-r'(X)) -S+1 +3 \log n +1,S \ge 3k\\
a&\leq 18(r''(X)-r(X)) +2 +3\log n+1\\
a&\leq 21(r''(X)-r(X)) +3
\end{aligned}
$$

Now add $a'$ back and write the total for $m$ `access(x)` operations:

$$
\sum_{i=1}^m a_i' + \sum_{i=1}^m a_i = \sum_{i=1}^m c_i + \varphi(x_n) -\varphi(x_0)
$$

What we want is the actual cost:

$$
\begin{aligned}
\sum_{i=1}^m c_i &= \sum_{i=1}^m a_i +\sum_{i=1}^m a_i' - \varphi(x_n) +\varphi(x_0)\\
&\le \sum_{i=1}^m a_i' + 21m\log n +n\log n +3m
\end{aligned}
$$

Note that `delete(x)` essentially deletes a Rake Node. In $m$ operations we add at most $m$ Rake Nodes, and by the definition of Rake Nodes, there are at most $n$ Rake Nodes at the start. So we do at most $m+n$ `delete(x)` operations in total. Since $a' \leq 3\log n +1$, we get

$$
\sum_{i=1}^m c_i \leq 3(m+n)\log n + 21m\log n +n\log n +4m +n
$$

This proves the complexity of Access. Every other function is either based on Access or takes constant time per call, so this proves the complexity of SATT.

By the way, if we skip the Global Splay as in LCT, and instead rotate the vertex being accessed once during each Splice, the time complexity is still correct. (In practice, the version without Global Splay is much faster, and runs about as fast as LCT on Luogu P3690.)

### Example problems

#### Example problem 1

???+ note "[CEOI 2019 Dynamic Diameter](https://loj.ac/p/3163)"
    You are given a tree with $n$ nodes, where each edge has a weight. There are $q$ updates; each one changes the weight of one edge and asks for the diameter of the tree. The problem is forced online.

To maintain a dynamic diameter, after building the SATT, we only need to maintain the answer of each node in `Pushup(x)`, and finally query the answer at the root (the diameter of the whole tree).

```cpp
void pushup(int x, int op) {
  if (op == 0) {
    // Compress Node
    len[x] = len[ls(x)] + len[rs(x)];
    diam[x] = maxs[ls(x)][1] + maxs[rs(x)][0];
    diam[x] =
        max(diam[x], max(maxs[ls(x)][1], maxs[rs(x)][0]) + maxs[ms(x)][0]);
    diam[x] = max(diam[x], max(max(diam[ls(x)], diam[rs(x)]), diam[ms(x)]));
    maxs[x][0] =
        max(maxs[ls(x)][0], len[ls(x)] + max(maxs[ms(x)][0], maxs[rs(x)][0]));
    maxs[x][1] =
        max(maxs[rs(x)][1], len[rs(x)] + max(maxs[ms(x)][0], maxs[ls(x)][1]));
  } else {
    // Rake Node
    diam[x] = maxs[ls(x)][0] + maxs[rs(x)][0];
    diam[x] =
        max(diam[x], maxs[ms(x)][0] + max(maxs[ls(x)][0], maxs[rs(x)][0]));
    diam[x] = max(max(diam[x], diam[ms(x)]), max(diam[ls(x)], diam[rs(x)]));
    maxs[x][0] = max(maxs[ms(x)][0], max(maxs[ls(x)][0], maxs[rs(x)][0]));
  }
  return;
}
```

Here $diam$ is the answer of the current node (the diameter of the cluster it represents). $len$ is the length of the cluster path of the cluster containing the current Compress Node. $maxs_{0/1}$ is the maximum distance from the Compress Node to the vertices and endpoints in the cluster, without going into the cluster-path child / without going into the parent (for a Rake Node, we only store $maxs_0$, the maximum distance from the upper endpoint of the current cluster to the vertices and endpoints in the cluster). Each time, just query the diam at the root of the SATT. Correctness is obvious.

Note that `Pushrev(x)` needs a few changes.

```cpp
void pushrev(int x) {
  if (!x) return;
  r[x] ^= 1;
  swap(ls(x), rs(x));
  swap(maxs[x][0], maxs[x][1]);
}
```

#### Example problem 2

???+ note "["CSP-S 2019" Centroids of a Tree](https://loj.ac/p/3213)"
    Given a tree, for each edge, delete only that edge and find the centroids of the two resulting subtrees. Output the sum of the indices of all these centroids.

If we can maintain the centroid of a tree dynamically in $O(\log n)$, we have solved this problem.

SATT supports maintaining the centroid of a tree dynamically in $O(\log n)$. To do this, we need **non-local search**.

For a property on a tree, if a vertex/edge has the property in the whole tree, and also has it in every subtree that contains it, we call the property **local**; otherwise we call it **non-local**. Local information can usually be maintained with `pushup(x)`.

For example, minimum weight is local: if a vertex/edge has the minimum weight in the whole tree, then it also has the minimum weight in every subtree containing it. The second smallest weight, on the other hand, is clearly non-local.

The $diam$ we maintained above is also local information.

Back to the problem. The centroid is clearly non-local information, and cannot be maintained by a simple `pushup(x)`. We consider searching on the SATT instead:

Our search starts from the root of the SATT, i.e. the root cluster. Note that centroids have a nice property: if, for some edge, the number of vertices on one side is at least the number on the other side, then that side of the edge contains at least one centroid (there may be two centroids).

Let $sum$ be the number of vertices in a cluster, and let $maxs$ be the maximum $sum$ over the middle children of all Rake Nodes in a Rake Tree.

```cpp
void pushup(int x, int op) {
  if (op == 0) {
    // Compress Node
    sum[x] = sum[ls(x)] + sum[rs(x)] + sum[ms(x)] + 1;
  } else {
    // Rake Node
    maxs[x] = max(maxs[ls(x)], max(maxs[rs(x)], sum[ms(x)]));
    sum[x] = sum[ls(x)] + sum[rs(x)] + sum[ms(x)];
  }
}
```

![](./images/top-tree20.jpg)

The figure shows the SATT during a Non-local Search, together with the corresponding original tree $T$.

We make the following comparisons:

1.  Compare the $sum$ of cluster $compress(Y)$ with the $sum$ of the union of cluster $compress(Z)$, cluster $A$ and vertex $X$ (call it cluster $\alpha$ for now). If the $sum$ of $compress(Y)$ is at least the latter, at least one centroid is in the subtree of $compress(Y)$, so we recurse into $compress(Y)$. (If they are equal, vertex $X$ is also a centroid and must be recorded.)

2.  Compare the $sum$ of cluster $compress(Z)$ with the $sum$ of the union of cluster $compress(Y)$, cluster $A$ and vertex $X$ (call it cluster $\beta$ for now). If the $sum$ of $compress(Z)$ is at least the latter, at least one centroid is in the subtree of $compress(Z)$, so we recurse into $compress(Z)$. (If they are equal, vertex $X$ is also a centroid and must be recorded.)

3.  In the Rake Tree at the middle child of vertex $x$, take the smaller cluster with the largest $sum$. Compare its $sum$ with the $sum$ of the union of cluster $compress(Y)$, cluster $A$, vertex $X$ and the other smaller clusters (call it cluster $\gamma$ for now). If the $sum$ of that smaller cluster is at least the latter, at least one centroid is in the subtree of that smaller cluster, so we recurse into it. If they are equal, vertex $X$ is also a centroid and must be recorded.

4.  If none of the comparisons above recurses, vertex $X$ must be a centroid. Record it and stop.

The first step of the search is clearly correct. How should the search go after that?

Suppose we recurse into $Y$. Now the information stored at $Y$ is incomplete, because $compress(Y)$ only stores the information of its own cluster, while we want the centroid of the whole tree. The fix is to record the information of the earlier clusters, and when comparing at vertex $Y$, merge the previous cluster's information with $Y$'s own information. The implementation is as follows:

```cpp
void non_local_search(int x, int lv, int rv, int op) {
  // lv and rv are the information of the previous cluster in the search
  if (!x) return;
  psd(x, 0);
  if (op == 0) {
    if (maxs[ms(x)] >=
        sum[ms(x)] - maxs[ms(x)] + sum[rs(x)] + sum[ls(x)] + lv + 1 + rv) {
      if (maxs[ms(x)] ==
          sum[ms(x)] - maxs[ms(x)] + sum[rs(x)] + sum[ls(x)] + lv + 1 + rv) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(
          ms(x),
          sum[ms(x)] - maxs[ms(x)] + sum[rs(x)] + sum[ls(x)] + 1 + lv + rv, 0,
          1);
      return;
    }
    if (ss[rs(x)] + rv >= ss[ms(x)] + ss[ls(x)] + lv + 1) {
      if (ss[rs(x)] + rv == ss[ms(x)] + ss[ls(x)] + lv + 1) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(rs(x), sum[ms(x)] + 1 + sum[ls(x)] + lv, rv, 0);
      return;
    }
    if (sum[ls(x)] + lv >= sum[ms(x)] + sum[rs(x)] + 1 + rv) {
      if (sum[ls(x)] + lv == sum[ms(x)] + sum[rs(x)] + 1 + rv) {
        if (ans1)
          ans2 = x;
        else
          ans1 = x;
      }
      non_local_search(ls(x), lv, rv + sum[ms(x)] + 1 + sum[rs(x)], 0);
      return;
    }
  } else {
    if (maxs[ls(x)] == maxs[x]) {
      non_local_search(ls(x), lv, rv, 1);
      return;
    }
    if (maxs[rs(x)] == maxs[x]) {
      non_local_search(rs(x), lv, rv, 1);
      return;
    }
    non_local_search(ms(x), lv, rv, 0);
    return;
  }
  if (ans1)
    ans2 = x;
  else
    ans1 = x;
}
```

??? note "Sample code"
    ```cpp
    --8<-- "docs/ds/code/top-tree/top-tree_2.cpp"
    ```

### Reference

1.  Robert E. Tarjan and Renato F. Werneck. 2005. Self-adjusting top trees. In Proceedings of the sixteenth annual ACM-SIAM symposium on Discrete algorithms (SODA '05). Society for Industrial and Applied Mathematics, USA, 813–822. DOI 10.5555/1070432.1070547

2.  [negiizhao's blog](https://negiizhao.blog.uoj.ac/blog/4912)
