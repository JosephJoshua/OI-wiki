author: ChungZH, billchenchina, Chrogeek, Early0v0, ethan-enhe, HeRaNO, hsfzLZH1, iamtwz, Ir1d, konnyakuxzy, luoguojie, Marcythm, orzAtalod, StudyingFather, wy-luke, Xeonacid, CCXXXI, chenryang, chenzheAya, CJSoft, cjsoft, countercurrent-time, DawnMagnet, Enter-tainer, GavinZhengOI, Haohu Shen, Henry-ZHR, hjsjhn, hly1204, jaxvanyang, Jebearssica, kenlig, ksyx, megakite, Menci, moon-dim, NachtgeistW, onelittlechildawa, ouuan, shadowice1984, shawlleyw, shuzhouliu, SukkaW, Tiphereth-A, x2e6, Ycrpro, yifan0305, zeningc

Merging and splitting segment trees are common segment tree techniques. They often appear when a value-domain segment tree maintains a multiset.

For example, suppose some tree nodes carry a number of operations, and we need to pass information from children up to their parents, bottom-up. If the information at a single node is easy to maintain with a segment tree, we can use segment tree merging to keep the overall complexity under control.

## Segment tree merging

### How it works

As the name suggests, segment tree merging builds a new segment tree in which every node is the result of merging the corresponding nodes of two original segment trees. It is often used to maintain information on trees or graphs.

Clearly, we cannot really build a full new segment tree every time, so we use the dynamically allocated segment tree described earlier.

The merging process is basically brute force:

Say the two segment trees are A and B. We merge them recursively, starting from node 1.

When the recursion reaches a node, if the corresponding node in tree A or tree B is empty, we simply return the corresponding node of the other tree. This uses a property of dynamically allocated segment trees.

If the recursion reaches a leaf, we merge the corresponding nodes of the two trees.

Finally, we update the current node from its children and return it.

???+ note "Complexity of segment tree merging"
    Clearly, for two full segment trees, a single merge costs $O(n)$. In practice, though, we usually merge value-domain segment trees, and the total number of nodes in all trees to be merged is not much larger than $n$. Also, a merge usually does not merge the same tree again and again, so the total number of nodes we add is roughly $n\log n$. So the total cost of merging all the segment trees is about $O(n\log n)$. Of course, in some cases a mergeable heap may be a better choice.

### Implementation

```cpp
int merge(int a, int b, int l, int r) {
  if (!a) return b;
  if (!b) return a;
  if (l == r) {
    // do something...
    return a;
  }
  int mid = (l + r) >> 1;
  tr[a].l = merge(tr[a].l, tr[b].l, l, mid);
  tr[a].r = merge(tr[a].r, tr[b].r, mid + 1, r);
  pushup(a);
  return a;
}
```

### Example problem

???+ note "[Luogu P4556 \[Vani's Date\] Rainy Day Tails / \[Template\] Segment Tree Merging](https://www.luogu.com.cn/problem/P4556)"
    ??? note "Solution idea"
        This is the template problem for segment tree merging. Use a difference array on the tree to turn path updates into point updates, then run a DFS upward, merging segment trees to compute the answers.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-merge.cpp"
        ```

## Segment tree splitting

### How it works

Segment tree splitting is basically the reverse of segment tree merging. It only makes sense for ordered sequences, not unordered ones, and it is mostly used on dynamically allocated value-domain segment trees.

Note that when both splitting and merging are used, we must recycle nodes during merging. Otherwise the same node might end up used twice after a split.

To split $[l,r]$ out of a segment tree over $[1,N]$ into a new tree:

Split recursively starting from node 1. If the node does not exist, or its interval $[s,t]$ does not intersect $[l,r]$, return immediately.

If $[s,t]$ intersects $[l,r]$, create a new node.

If $[s,t]$ is contained in $[l,r]$, attach the current node directly under the new tree and cut the old edge.

???+ note "Complexity of segment tree splitting"
    At most $\log n$ edges are cut, so each split takes $O(\log⁡ n)$ time, the same as a range query.

### Implementation

```cpp
void split(int &p, int &q, int s, int t, int l, int r) {
  if (t < l || r < s) return;
  if (!p) return;
  if (l <= s && t <= r) {
    q = p;
    p = 0;
    return;
  }
  if (!q) q = New();
  int m = s + t >> 1;
  if (l <= m) split(ls[p], ls[q], s, m, l, r);
  if (m < r) split(rs[p], rs[q], m + 1, t, l, r);
  push_up(p);
  push_up(q);
}
```

### Example problem

???+ note "[P5494 \[Template\] Segment Tree Splitting](https://www.luogu.com.cn/problem/P5494)"
    ??? note "Solution idea"
        This is the template problem for segment tree splitting. Split out $[x,y]$.
        
        -   Merge tree $t$ into tree $p$: a single merge does it.
        
        -   Insert $x$ copies of $q$ into tree $p$: a point update.
        
        -   Count the numbers in $[x,y]$: a range sum.
        
        -   Find the $k$-th smallest.
    
    ??? note "Reference code"
        ```cpp
        --8<-- "docs/ds/code/seg/seg-split.cpp"
        ```

## Exercises

-   [Luogu P4556 \[Vani's Date\] Rainy Day Tails / \[Template\] Segment Tree Merging](https://www.luogu.com.cn/problem/P4556)
-   [Luogu P5494 \[Template\] Segment Tree Splitting](https://www.luogu.com.cn/problem/P5494)
-   [Luogu P1600 Running Every Day](https://www.luogu.com.cn/problem/P1600)
-   [Luogu P4577 \[FJOI2018\] Leadership Group Problem](https://www.luogu.com.cn/problem/P4577)
-   [Luogu P2824 \[HEOI2016/TJOI2016\] Sorting](https://www.luogu.com.cn/problem/P2824)
