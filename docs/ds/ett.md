author: Backl1ght

The Euler Tour Tree (ETT for short below) is a data structure for solving **dynamic tree** problems. ETT turns operations on a dynamic tree into range operations on its DFS sequence, and then uses another data structure to maintain range operations on that sequence, which in turn maintains the dynamic tree. For example, ETT turns adding an edge to a dynamic tree into several sequence split and sequence merge operations; if we can support sequence split and merge, we can support adding edges to the dynamic tree.

The LCT (link/cut tree) is another data structure for dynamic tree problems, and it is more common than ETT. LCT is better suited to maintaining information on tree paths, while ETT is better suited to maintaining information on **subtrees**. For example, ETT can maintain the minimum of a subtree, while LCT cannot.

ETT can be maintained with any data structure, as long as that data structure supports the needed sequence range operations within the required complexity. Usually a balanced binary search tree such as a Splay tree or a Treap is used to maintain the sequence. These data structures all handle range operations in $O(\log n)$, so dynamic tree operations can also be done in $O(\log n)$ time. Using a multiway balanced search tree such as a B-tree to maintain range operations can give even better complexity.

In fact, ETT can be seen as an idea: maintain some sequence that corresponds one-to-one with the original tree, and thereby maintain the original tree. This page only covers some workable implementations and applications of this idea.

## Euler tour representation of a tree

If we view each tree edge as two directed edges, a tree can be represented as an Euler circuit of a directed graph. This is called the Euler tour representation (ETR) of the tree.

The sequence we maintain later is actually a variant of the ETR: the tree's vertices are treated as self-loops and also added to the ETR. Since the authors of the original paper did not give it a new name, we will keep calling it the ETR.

The Euler tour representation of a tree $T$ can be obtained with the following algorithm:

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{A rooted tree }T\\
2 & \textbf{Output. } \text{The dfs sequence of rooted tree }T\\
3 & \operatorname{ET}(u)\\
4 & \qquad \text{visit vertex }u\\
5 & \qquad \text{for all child } v \text{ of } u\\
6 & \qquad \qquad \text{visit directed edge } u \to v\\
7 & \qquad \qquad \operatorname{ET}(v)\\
8 & \qquad \qquad \text{visit directed edge } v \to u\\
\end{array}
$$

The Euler tour representation $\operatorname{ETR}(T)$ of tree $T$ starts empty. During the DFS, each time we visit a vertex or a directed edge, we append it to the end of $\operatorname{ETR}(T)$. This gives us $\operatorname{ETR}(T)$.

If $T$ has $n$ vertices, it has $2n - 2$ directed edges. During the DFS, each vertex and each directed edge is visited once, so $\operatorname{ETR}(T)$ has length $3n - 2$.

Treat vertex $u$ as a self-loop; then $\operatorname{ETR}(T)$ can be seen as an Euler circuit in a directed graph. We can cut the Euler circuit somewhere and view it as a chain of edges joined end to end; we can glue such a chain back together at the cut to get an Euler circuit again; and we can join two such chains into a new Euler circuit by adding some edges.

From here on, unless stated otherwise, the sequence we maintain is the Euler tour representation of the tree.

## Basic ETT operations

The following 3 operations are the basic operations of ETT. Each can be turned into a constant number of sequence operations, so their complexity is the same as that of the sequence operations.

What is given here is just one workable implementation; any approach works as long as it builds the modified sequence with a constant number of sequence operations.

### MakeRoot(u)

This is the re-rooting operation. In ETT, re-rooting becomes 1 sequence split and 1 sequence merge, which can also be seen as 1 range shift.

Let $T$ be the tree containing vertex $u$, with current root $r$; we want to make $u$ the root. Let $L$ be the sequence of tree $T$. Split $L$ at $(u, u)$ into sequences $L^1$ and $L^2$: the former contains the elements of $L$ before $(u, u)$ plus $(u, u)$ itself, and the latter contains the rest. Then merging $L^2$ and $L^1$ in that order gives the sequence of the re-rooted tree.

You can think of this as rotating an Euler circuit. An Euler circuit is a cycle, so rotating it does not change its structure, which means it does not change the tree's structure; it just rotates vertex $u$ into the root position.

### Insert(u, v)

This is the edge-insertion operation. In ETT, inserting an edge becomes 2 sequence splits and 5 sequence merges.

Let $T_1$ be the tree containing vertex $u$ and $T_2$ the tree containing vertex $v$. After adding the edge, the two trees merge into one tree $T$. Let $L_1$ be the sequence of tree $T_1$ and $L_2$ the sequence of tree $T_2$.

Split $L_1$ at $(u, u)$ into sequences $L_1^1$ and $L_1^2$: the former contains the elements of $L_1$ before $(u, u)$ plus $(u, u)$ itself, and the latter contains the rest. Similarly, split $L_2$ at $(v, v)$ into sequences $L_2^1$ and $L_2^2$. Then merging $L_1^2, L_1^1, [(u, v)], L_2^2, L_2^1,  [(v, u)]$ in that order gives the sequence $L$ of tree $T$.

You can think of this as two re-rooting operations, followed by cutting both Euler circuits at their current roots and using the two new directed edges to join them into one new Euler circuit.

### Delete(u, v)

This is the edge-deletion operation. In ETT, deleting an edge becomes 4 sequence splits and 1 sequence merge.

Let $T$ be the tree containing edges $(u, v)$ and $(v, u)$, and $L$ its sequence. After deleting the edge, $T$ splits into two trees.

Split $L$ into $L_1, [(u, v)], L_2, [(v, u)], L_3$. The sequences of the two resulting trees are $L_2$ and $L_1, L_3$. Note that in $L$, $[(u, v)]$ may appear after $[(v, u)]$; in that case, swap the values of $u$ and $v$ first and then proceed.

You can think of this as cutting an Euler circuit at the two directed edges to get two chains, and then joining each chain end to end to form two new Euler circuits.

## Implementation

Below we use a non-rotating Treap as an example to show how to implement ETT. The reader should already know how to maintain range operations with a non-rotating Treap.

`Split` and `Merge` are basic operations of a non-rotating Treap, so we won't repeat them here.

### SplitUp2(u)

Let $L$ be the sequence containing $u$. Split $L$ at $u$ into sequences $L^1$ and $L^2$: the former contains the elements of $L$ before $u$ plus $u$ itself, and the latter contains the rest.

If each Treap node also stores its parent, we can compute the position in the sequence of the element for a Treap node in $O(\log n)$ time, and then `Split` by position to get the result above.

We can also split from the bottom up to get the same result, which is more efficient than the method above. Concretely, while jumping from the node for $u$ up to the root, the binary search tree property tells us whether each node is before or after $u$ in $L$. From this we can compute the position of $u$ in the sequence, and also decide which of the two split trees each node belongs to.

```cpp
/*
 * Bottom up split treap p into 2 treaps a and b.
 *   - a: a treap containing nodes with position less than or equal to p.
 *   - b: a treap containing nodes with position greater than p.
 *
 * In the other word, split sequence containing p into two sequences, the first
 * one contains elements before p and element p, the second one contains
 * elements after p.
 */
static std::pair<Node*, Node*> SplitUp2(Node* p) {
  Node *a = nullptr, *b = nullptr;
  b = p->right_;
  if (b) b->parent_ = nullptr;
  p->right_ = nullptr;

  bool is_p_left_child_of_parent = false;
  bool is_from_left_child = false;
  while (p) {
    Node* parent = p->parent_;

    if (parent) {
      is_p_left_child_of_parent = (parent->left_ == p);
      if (is_p_left_child_of_parent) {
        parent->left_ = nullptr;
      } else {
        parent->right_ = nullptr;
      }
      p->parent_ = nullptr;
    }

    if (!is_from_left_child) {
      a = Merge(p, a);
    } else {
      b = Merge(b, p);
    }

    is_from_left_child = is_p_left_child_of_parent;
    p->Maintain();
    p = parent;
  }

  return {a, b};
}
```

### SplitUp3(u)

Let $L$ be the sequence containing $u$. Split $L$ at $u$ into sequences $L^1$, $u$ and $L^2$: the first contains the elements of $L$ before $u$, and the last contains the remaining elements.

A small change to `SplitUp2` is enough.

### MakeRoot(u)

Easy to get from `SplitUp2` and `Merge`.

```cpp
void MakeRoot(int u) {
  Node* vertex_u = vertices_[u];
  auto [L1, L2] = Treap::SplitUp2(vertex_u);
  Treap::Merge(L2, L1);
}
```

### Insert(u, v)

Easy to get from `SplitUp2` and `Merge`.

```cpp
void Insert(int u, int v) {
  Node* vertex_u = vertices_[u];
  Node* vertex_v = vertices_[v];

  Node* edge_uv = AllocateNode(u, v);
  Node* edge_vu = AllocateNode(v, u);
  tree_edges_[u][v] = edge_uv;
  tree_edges_[v][u] = edge_vu;

  auto [L11, L12] = Treap::SplitUp2(vertex_u);
  auto [L21, L22] = Treap::SplitUp2(vertex_v);

  Node* L = L12;
  L = Treap::Merge(L, L11);
  L = Treap::Merge(L, edge_uv);
  L = Treap::Merge(L, L22);
  L = Treap::Merge(L, L21);
  L = Treap::Merge(L, edge_vu);
}
```

### Delete(u, v)

Easy to get from `SplitUp3` and `Merge`.

```cpp
void Delete(int u, int v) {
  Node* edge_uv = tree_edges_[u][v];
  Node* edge_vu = tree_edges_[v][u];
  tree_edges_[u].erase(v);
  tree_edges_[v].erase(u);

  int position_uv = Treap::GetPosition(edge_uv);
  int position_vu = Treap::GetPosition(edge_vu);
  if (position_uv > position_vu) {
    std::swap(edge_uv, edge_vu);
    std::swap(position_uv, position_vu);
  }

  auto [L1, uv, _] = Treap::SplitUp3(edge_uv);
  auto [L2, vu, L3] = Treap::SplitUp3(edge_vu);
  Treap::Merge(L1, L3);

  FreeNode(edge_uv);
  FreeNode(edge_vu);
}
```

## Maintaining connectivity

Vertices $u$ and $v$ are connected if and only if they belong to the same tree $T$, that is, both $(u, u)$ and $(v, v)$ are in $\operatorname{ETR}(T)$. We can check this by testing whether the Treap nodes for $u$ and $v$ are in Treaps with the same root.

### Example problem [P2147 \[SDOI2008\] Cave Exploration](https://www.luogu.com.cn/problem/P2147)

A template problem for maintaining connectivity.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/ett/ett_connectivity.cpp"
    ```

## Maintaining subtree information

Below we use the number of nodes in a subtree as an example.

For each element of $\operatorname{ETR}(T)$, give it weight $1$ if it corresponds to a vertex of the tree, and weight $0$ if it corresponds to an edge. Then the number of nodes in tree $T$ is the sum of the weights of the elements of $\operatorname{ETR}(T)$, so we only need to maintain the weight sum of the sequence to maintain the subtree size. Maintaining the weight sum of a sequence is a classic non-rotating Treap operation.

Similarly, operations like the subtree minimum can be turned into classic balanced tree operations like the sequence minimum, and maintained that way.

### Example problem [LOJ #2230. "BJOI2014" Great Integration](https://loj.ac/p/2230)

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/ett/ett_subtree_size.cpp"
    ```

## Maintaining path information

A fairly common trick is to use the properties of the bracket sequence to turn path information into range information, and then maintain the sequence with a data structure to maintain the path information. But this trick requires the information to be **subtractable**.

The sequence operations for the dynamic tree operations above may move a closing bracket in the bracket sequence in front of its opening bracket. So when maintaining something like the sum of vertex weights on a path, take extra care: operations must not change the order of each matching pair of brackets. This may require rethinking the sequence operations for the dynamic tree operations, or even rethinking which DFS order to maintain.

Also, ETT has a hard time supporting path updates.

### Example problem ["Interstellar Exploration"](https://hydro.ac/p/bzoj-P3786)

In this problem, the only dynamic tree operation is changing a node's parent. It can be seen as deleting an edge and then adding one, but that may change the order of the matching brackets.

We can turn vertex weights into edge weights and maintain the tree's bracket sequence. Changing the parent then becomes moving the whole subtree's bracket sequence to just after the parent's opening bracket.

??? note "Reference code"
    ```cpp
    --8<-- "docs/ds/code/ett/ett_1.cpp"
    ```

## References

-   Dynamic trees as search trees via euler tours, applied to the network simplex algorithm - Robert E. Tarjan
-   Randomized fully dynamic graph algorithms with polylogarithmic time per operation - Henzinger et al.
