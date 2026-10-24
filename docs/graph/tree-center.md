author: littleparrot12345

## Definition

In a tree, if taking node $x$ as the root makes the longest chain starting from $x$ as short as possible, then $x$ is called a center of the tree.

## Properties

-   The center of a tree is not always unique, but there are at most $2$ centers, and if there are two, they are adjacent.
-   The center always lies on a diameter of the tree.
-   For every node, the path to its farthest node passes through the center.
-   When the center is the root, its two chains to the endpoints of the diameter are the longest and the second-longest chains.
-   When merging two trees into one by adding an edge between them, connecting their centers gives the smallest possible diameter of the new tree.
-   The distance from the center to any other node is at most half the diameter.

## How to find it

Find a node $x$ such that, with $x$ as the root, the length of the longest chain is as small as possible.

### Steps

1.  Maintain $len1_x$, the longest chain inside the subtree of node $x$.
2.  Maintain $len2_x$, the longest chain that does not overlap with $len1_x$.
3.  Maintain $up_x$, the longest chain outside the subtree of node $x$. This chain must pass through the parent of $x$.
4.  Find the node $x$ that minimizes $\max(len1_x, up_x)$; that $x$ is the center of the tree.

???+ note "Reference code"
    ```cpp
    // This code assumes nodes are numbered from 1, i.e. i ∈ [1,n], and stores the graph with vector
    int d1[N], d2[N], up[N], x, y, mini = 1e9;  // d1, d2 are len1, len2 above
    
    struct node {
      int to, val;  // to is the node the edge points to, val is the edge weight
    };
    
    vector<node> nbr[N];
    
    void dfsd(int cur, int fa) {  // compute len1 and len2
      for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;  // nxt is the node this edge leads to, val is the edge weight
        if (nxt == fa) {
          continue;
        }
        dfsd(nxt, cur);
        if (d1[nxt] + w > d1[cur]) {  // the longest chain can be updated
          d2[cur] = d1[cur];
          d1[cur] = d1[nxt] + w;
        } else if (d1[nxt] + w > d2[cur]) {  // cannot update the longest, but can update the second longest
          d2[cur] = d1[nxt] + w;
        }
      }
    }
    
    void dfsu(int cur, int fa) {
      for (node nxtn : nbr[cur]) {
        int nxt = nxtn.to, w = nxtn.val;
        if (nxt == fa) {
          continue;
        }
        up[nxt] = up[cur] + w;
        if (d1[nxt] + w != d1[cur]) {  // if the longest chain in our subtree is not in nxt's subtree
          up[nxt] = max(up[nxt], d1[cur] + w);
        } else {  // the longest chain in our subtree is in nxt's subtree, so use the second longest
          up[nxt] = max(up[nxt], d2[cur] + w);
        }
        dfsu(nxt, cur);
      }
    }
    
    void GetTreeCenter() {  // find the centers of the tree, stored as x and y (if it exists)
      dfsd(1, 0);
      dfsu(1, 0);
      for (int i = 1; i <= n; i++) {
        if (max(d1[i], up[i]) < mini) {  // found a node with smaller max(len1[x],up[x])
          mini = max(d1[i], up[i]);
          x = i;
          y = 0;
        } else if (max(d1[i], up[i]) == mini) {  // the other center
          y = i;
        }
      }
    }
    ```

### Example

Suppose we have the following tree:

```text
           A
          / \
         B   C
        / \   \
       D   E   F
```

-   The diameter of the tree is $D \rightarrow B \rightarrow A \rightarrow C \rightarrow F$, with length $4$.
-   The center is node $A$, because the longest chains from $A$ (to $D$ or $F$) both have length $2$.
-   If we made $B$ or $C$ the root, the longest chain from that node would get longer, so they are not centers.

### Time complexity

The algorithm above runs in $O(n)$ time, where $n$ is the number of nodes in the tree.

## References

-   [TutorialsPoint: Centers of a Tree](https://www.tutorialspoint.com/centers-of-a-tree)
-   [ProofWiki: Definition of Center of Tree](https://proofwiki.org/wiki/Definition:Center_of_Tree)
-   [Wikipedia: Tree (graph theory)](https://en.wikipedia.org/wiki/Tree_%28graph_theory%29#Properties)
