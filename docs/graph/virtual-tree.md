author: HeRaNO, Ir1d, konnyakuxzy, ksyx, Xeonacid, konnyakuxzy, greyqz, sshwy, y-kx-b

## Introduction

???+ note "[SDOI2011 War of Attrition](https://www.luogu.com.cn/problem/P2495)"
    In a war, the battlefield consists of $n$ islands and $n-1$ bridges, and there is exactly one path between any two islands. Our army has found that the enemy headquarters is on island $1$, and the enemy no longer has enough energy to keep fighting, so victory is in sight. Some other $k$ islands are rich in energy. To stop the enemy from getting energy, our task is to blow up some bridges so that the enemy cannot reach any energy-rich island. Bridges are made of different materials and structures, so blowing up different bridges has different costs. We want to achieve the goal with the minimum total cost.
    
    The scouts also found that the enemy has a mysterious machine that they can use even after we cut off all their energy. The machine not only repairs every bridge we blew up, but also redistributes the resources at random (though it is guaranteed that no resources end up on island $1$). However, the scouts found the machine can only be used $m$ times, so we just need to complete the task each time.
    
    For all test data, $2\le n\le 2.5\times 10^5,1\le m\le 5\times 10^5,\sum k_i\le 5\times 10^5,1\le k_i\le n-1$.

### Naive approach

For the problem above, it is easy to see that if the tree had only a few nodes, we could just run a DP directly.

First, we call the nodes selected in a query **"key nodes"**.

Let $Dp(i)$ be the **minimum cost** to disconnect $i$ from every key node in its subtree.

Let $w(a,b)$ be the weight of the edge between $a$ and $b$.

Then enumerate each child $v$ of $i$:

-   If $v$ is not a key node: $Dp(i)=Dp(i) + \min \{Dp(v),w(i,v)\}$;
-   If $v$ is a key node: $Dp(i)=Dp(i) + w(i,v)$.

Great, this gives us an $O(nq)$ solution.

Sounds interesting.

### Optimized approach

It is easy to see that many nodes are actually useless. Take the tree below as an example:

![vtree-1](images/vtree-tree.svg)

Suppose the key nodes we pick are:

![vtree-2](images/vtree-key-vertex.svg)

Only the two red nodes in the figure are **key nodes**; all other nodes are "non-key nodes".

For this problem, we just need to make sure the red nodes cannot reach node $1$.

Just by looking, we can see that the right subtree of node $1$ (there could really be many subtrees, but here there are only two, so we call it that for now) has no red nodes at all, **so there is no need to run DP on it**.

Looking at the constraints, the total number of red nodes (key nodes) is of the same order as $n$. That means in a single query the red nodes are very sparse compared with the whole tree. So it would be great if the complexity depended only on the total number of red nodes.

So we need to **compress the information, shrinking a whole big tree into a small one**.

## Virtual tree

This leads to the idea of a **"virtual tree"**.

Let us first get an intuitive look at what a virtual tree is.

In the figures below, the red nodes are the key nodes we chose. Both red and black nodes are nodes of the virtual tree. Black edges are edges of the virtual tree.

![vtree-3](images/vtree-vtree1.svg)

![vtree-4](images/vtree-vtree2.svg)

![vtree-5](images/vtree-vtree3.svg)

![vtree-6](images/vtree-vtree4.svg)

The LCA of any two key nodes also has to hold important information, so we need to keep these LCAs as well. That is why a virtual tree does not contain only key nodes.

It is easy to see that the ancestor-descendant relationships do not change in the virtual tree. (That is, nothing weird happens like $a$ being an ancestor of $b$ originally and then becoming a descendant of $b$.)

But we cannot enumerate LCAs by brute force in $O(k^2)$. So the natural idea is: first sort the key nodes by DFS order, then for each pair of adjacent key nodes after sorting (adjacent meaning their indices in the sorted sequence differ by 1), compute their LCA and add it to the virtual tree.

Our most urgent job is to figure out how to build the virtual tree.

Before giving a method, let us confirm one fact: in a virtual tree, we can add any nodes we like, as long as the ancestor-descendant relationships stay the same.

So if we wanted to, we could add every node of the original tree to the virtual tree without getting WA (though we would get TLE).

So for convenience, we can first add node $1$ to the virtual tree; this does not affect the answer.

### Construction method 1: sort twice + connect via LCA

Several pairs of nodes may have the same LCA, so we must not add it to the virtual tree more than once.

A very intuitive method is:

-   Sort the key nodes by DFS order;
-   Go through them once, compute the LCA of every two adjacent key nodes, and remove duplicates;
-   Then build the tree according to the ancestor-descendant relationships in the original tree.

Concretely, on the **sequence of key nodes**, enumerate **every two adjacent entries**, compute their LCA, and add it to a sequence $A$.

Because of the properties of DFS order, the sequence $A$ now contains **all nodes of the virtual tree**, though possibly with duplicates.

So we **sort $A$ by DFS order in increasing order and remove duplicates**.

Finally, on sequence $A$, enumerate every two **adjacent** **node indices**  $x,y$, compute their LCA and connect $\operatorname{LCA}(x,y),y$. The virtual tree is then complete.

Why does connecting $\operatorname{LCA}(x,y)$ and $y$ give every edge exactly once, with nothing missed or repeated?

??? note "Proof"
    If $x$ is an ancestor of $y$, then $x$ connects directly to $y$. Since $x$ and $y$ are adjacent in DFS order, there are no key nodes on the path from $x$ to $y$.
    
    If $x$ is not an ancestor of $y$, treat $\operatorname{LCA}(x,y)$ as the ancestor of $y$. By the previous case, there are no key nodes on the path from $\operatorname{LCA}(x,y)$ to $y$ either.
    
    So connecting $\operatorname{LCA}(x,y)$ and $y$ misses nothing and repeats nothing.
    
    Also, does it matter that the first node is not connected from any node? The first node must be the root of the tree, so it does not matter. The total number of edges is therefore $m-1$.

It takes at least two real nodes to summon one virtual node, and there is also the root, so the number of nodes in the virtual tree is (at most) twice the number of real nodes.

The time complexity is $O(m\log n)$, where $m$ is the number of key nodes and $n$ is the total number of nodes.

#### Implementation

```cpp
int dfn[MAXN];
int h[MAXN], m, a[MAXN], len;  // stores the key nodes

bool cmp(int x, int y) {
  return dfn[x] < dfn[y];  // sort by DFS order
}

void build_virtual_tree() {
  sort(h + 1, h + m + 1, cmp);  // sort the key nodes by DFS order
  for (int i = 1; i < m; ++i) {
    a[++len] = h[i];
    a[++len] = lca(h[i], h[i + 1]);  // insert the lca
  }
  a[++len] = h[m];
  sort(a + 1, a + len + 1, cmp);  // sort all virtual tree nodes by DFS order
  len = unique(a + 1, a + len + 1) - a - 1;  // remove duplicates
  for (int i = 1, lc; i < len; ++i) {
    lc = lca(a[i], a[i + 1]);
    conn(lc, a[i + 1]);  // add an edge; with edge weights, it is distance(lc,a[i+1])
  }
}
```

This is actually enough to build a virtual tree.

### Construction method 2: using a monotonic stack

How do we build a virtual tree with a monotonic stack?

First, let us be clear about the goal: we use the monotonic stack to maintain one chain of the virtual tree.

That is, any two adjacent nodes in the stack are also adjacent in the virtual tree, and the stack increases monotonically from bottom to top (in terms of DFS order of the nodes). Put simply, the parent of a node is the node just below it in the stack.

First, push node $1$ onto the stack.

Then add the key nodes in increasing DFS order.

If the LCA of the current node and the top node is the top node itself, they are on one chain. So just push the current node.

![vtree-7](./images/vtree-add1.svg)

If the LCA of the current node and the top node is not the top node:

![vtree-8](./images/vtree-add2.svg)

Then the chain currently kept by the monotonic stack is:

![vtree-9](./images/vtree-add3.svg)

But we need the chain to become:

![vtree-10](./images/vtree-add4.svg)

So we pop the nodes marked with dashed lines. Before popping each one, don't forget to connect it to its parent in the virtual tree.

![vtree-11](./images/vtree-add5.svg)

If after popping the top of the stack is not the LCA, push the LCA.

Then push the current node, and we are done.

Here is a concrete example. Suppose we want to build the virtual tree of nodes 4, 6 and 7 of the tree below:

![vtree-12](./images/vtree-construction1.svg)

The steps are:

-   Sort the 3 key nodes $6,4,7$ by DFS order to get the sequence $[4,6,7]$.
-   Push $1$.

![vtree-13](./images/vtree-construction2.svg)

Red nodes are in the stack, and cyan nodes are those popped from the stack.

-   Take the first node in the sequence as the current node, which is $4$. The top of the stack is $1$. The LCA of $1$ and $4$ is $LCA(1,4)=1$.
-   $LCA(1,4)=$ the top element, so they are on one chain of the virtual tree. Push the current node $4$ directly; the stack is now $4,1$.

![vtree-14](./images/vtree-construction3.svg)

-   Take the second node in the sequence as the current node, which is $6$. The top of the stack is $4$. The LCA of $6$ and $4$ is $LCA(6,4)=1$.
-   $LCA(6,4)\neq$ the top element, so we go to the checking phase.
-   Checking phase: the DFS order of the top node $4$ is greater than that of $LCA(6,4)$, but the DFS order of the second node (the one just below the top) $1$ equals that of the LCA (equal DFS order means the same node). So the LCA is already in the stack. We directly add the edge $1\to4$, that is, the edge from the LCA to the top element, and pop $4$ off the stack.

![vtree-15](./images/vtree-construction4.svg)

-   The checking phase is over. Push $6$; the stack is now $6,1$.

![vtree-16](./images/vtree-construction5.svg)

-   Take the third node in the sequence as the current node, which is $7$. The top of the stack is $6$. The LCA of $7$ and $6$ is $LCA(7,6)=3$.
-   $LCA(7,6)\neq$ the top element, so we go to the checking phase.
-   Checking phase: the DFS order of the top node $6$ is greater than that of $LCA(7,6)$, but the DFS order of the second node (the one just below the top) $1$ is less than that of the LCA. So the LCA has not been pushed yet. We directly add the edge $3\to6$, that is, the edge from the LCA to the top element, pop $6$ off the stack, and push $LCA(6,7)$.
-   The checking phase is over. Push $7$; the stack is now $1,3,7$.

![vtree-17](./images/vtree-construction6.svg)

-   All 3 nodes in the sequence have been pushed, so we exit the loop.
-   The stack still holds 3 nodes: $1,3,7$. Clearly they are on one chain, so we connect them directly: the edges $1\to3$ and $3\to7$.
-   The virtual tree is built!

![vtree-18](./images/vtree-construction7.svg)

Next we delete the nodes that were never pushed (the non-cyan nodes), and the resulting virtual tree looks like this:

![vtree-19](./images/vtree-construction8.svg)

There are many details. For example, if the virtual tree is stored as an adjacency list, the list has to be cleared. Clearing the whole adjacency list directly is slow, so we **clear an element's adjacency list when that element is pushed onto the stack for the first time**.

The time complexity is also $O(m\log n)$ (because of sorting), where $m$ is the number of key nodes and $n$ is the total number of nodes.

#### Implementation

The C++ code for building a virtual tree looks roughly like this:

???+ note "Implementation"
    ```cpp
    bool cmp(const int x, const int y) { return id[x] < id[y]; }
    
    void build() {
      sort(h + 1, h + k + 1, cmp);
      sta[top = 1] = 1, g.sz = 0, g.head[1] = -1;
      // push node 1, clear node 1's adjacency list, and set the edge count to 0
      for (int i = 1, l; i <= k; ++i)
        if (h[i] != 1) {
          // if node 1 is a key node, don't add it again
          l = lca(h[i], sta[top]);
          // compute the LCA of the current node and the top node
          if (l != sta[top]) {
            // if the LCA differs from the top element, the current node is not on the chain stored in the stack
            while (id[l] < id[sta[top - 1]])
              // while the DFS order of the second node is greater than that of the LCA
              g.push(sta[top - 1], sta[top]), top--;
            // connect and pop the part of the chain that does not overlap with the current node's chain
            if (id[l] > id[sta[top - 1]])
              // if the LCA is not the second node (here "greater than" is no different from "not equal")
              g.head[l] = -1, g.push(l, sta[top]), sta[top] = l;
            // the LCA is pushed for the first time: clear its adjacency list, add the edge, pop the top element, and push the LCA
            // onto the stack
            else
              g.push(l, sta[top--]);
            // the LCA is the second node; just pop the top element
          }
          g.head[h[i]] = -1, sta[++top] = h[i];
          // the current node must be pushed for the first time; clear its adjacency list and push it
        }
      for (int i = 1; i < top; ++i)
        g.push(sta[i], sta[i + 1]);  // connect the last remaining chain
      return;
    }
    ```

And now we know how to build a virtual tree!

For War of Attrition, just run the DP from the start on the virtual tree. We have used the virtual tree to get rid of the useless non-key nodes! Again consider every child $v$ of $i$:

-   If $v$ is not a key node: $Dp(i)=Dp(i) + \min \{Dp(v),w(i,v)\}$
-   If $v$ is a key node: $Dp(i)=Dp(i) + w(i,v)$

And the problem is solved easily.

## Recommended exercises

-   [SDOI2011 War of Attrition](https://www.luogu.com.cn/problem/P2495)
-   [HEOI2014 Big Project](https://www.luogu.com.cn/problem/P4103)
-   [CF613D Kingdom and its Cities](http://codeforces.com/contest/613/problem/D/)
-   [HNOI2014 World Tree](https://www.luogu.com.cn/problem/P3233)
