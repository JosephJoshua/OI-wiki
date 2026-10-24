## Introduction

A tree in graph theory looks just like a real tree, except that when solving problems we usually draw the root at the top. The data structure looks like an upside-down tree, which is where the name comes from.

## Definition

A tree without a fixed root node is called an **unrooted tree**. There are several equivalent formal definitions of an unrooted tree:

-   A connected undirected graph with $n$ nodes and $n-1$ edges

-   A connected undirected graph with no cycles

-   An undirected graph in which there is exactly one simple path between any two nodes

-   A connected graph in which every edge is a bridge

-   A graph with no cycles, such that adding an edge between any two distinct vertices creates exactly one cycle

If we pick one node of an unrooted tree and call it the **root**, we get a **rooted tree**. A rooted tree is still often represented as an undirected graph; we just fix the parent-child relationship between nodes, as described below.

## Tree-related definitions

### For both unrooted and rooted trees

-   **Forest**: a graph in which every connected component is a tree. By this definition, a single tree is also a forest.

-   **Spanning tree**: a spanning subgraph of a connected undirected graph that is also a tree. In other words, pick $n - 1$ edges from the graph's edge set so that all vertices are connected.

-   **Leaf node of an unrooted tree**: a node with degree at most $1$.

    ???+ question "Why not degree exactly $1$?"
        Consider $n = 1$.

-   **Leaf node of a rooted tree**: a node with no children.

### Only for rooted trees

-   **Parent node**: for every node other than the root, the second node on the path from that node to the root.  
    The root has no parent.
-   **Ancestor**: any node on the path from a node to the root, other than the node itself.  
    The root's set of ancestors is empty.
-   **Child node**: if $u$ is the parent of $v$, then $v$ is a child of $u$.  
    The order of children usually does not matter; binary trees are an exception.
-   **Depth of a node**: the number of edges on the path to the root.
-   **Height of a tree**: the maximum depth over all nodes.
-   **Sibling**: children of the same parent are siblings of each other.
-   **Descendant**: a child, or a descendant of a child.  
    Equivalently: if $u$ is an ancestor of $v$, then $v$ is a descendant of $u$.

![tree-definition.svg](images/tree-definition.svg)

-   **Subtree**: the part of the graph containing a node after deleting the edge between it and its parent.

    ![tree-definition-subtree.svg](images/tree-definition-subtree.svg)

## Special trees

-   **Chain (path graph)**: a tree in which every node has at most $2$ incident edges.

-   **Star**: a tree with a node $u$ such that every node other than $u$ is connected to $u$.

-   **Rooted binary tree**: a rooted tree where every node has at most two children. Usually the two children are ordered and called the left child and the right child.  
    In most cases, the term **binary tree** means a rooted binary tree.

-   **Full (proper) binary tree**: a binary tree where every node has either 0 or 2 children. In other words, every node is either a leaf or has both left and right subtrees non-empty.

    ![](images/tree-binary-proper.svg)

-   **Complete binary tree**: only nodes in the bottom two levels may have degree less than 2, and the nodes in the bottom level are packed together in consecutive positions on the far left.

    ![](images/tree-binary-complete.svg)

-   **Perfect binary tree**: a binary tree where all leaves have the same depth and every non-leaf node has exactly 2 children.

    ![](images/tree-binary-perfect.svg)

???+ warning "Warning"
    The Chinese name for "proper binary tree" is not fixed, and the definitions of complete binary tree and full binary tree differ between textbooks. When you meet these terms, decide what they mean from context.

When OIers say "full binary tree", they usually mean a perfect binary tree.

## Storage

### Storing only the parent

Use an array `parent[N]` to record the parent of each node.

This gives relatively little information and makes top-down traversal inconvenient. It is often used for bottom-up recurrences.

### Adjacency list

-   For an unrooted tree: give each node a linear list that records all nodes adjacent to it.
    ```cpp
    std::vector<int> adj[N];
    ```
-   For a rooted tree:
    -   Method 1: if the input is an undirected graph, you can still store it in the form above. Below we explain how to tell parents from children.
    -   Method 2: if the input guarantees the parent-child relationship, you can use that. Give each node a linear list recording all its children; if needed, also record its parent in another array.
        ```cpp
        std::vector<int> children[N];
        int parent[N];
        ```
        Of course, you can also use something else (such as a linked list) instead of `std::vector`.

### Left-child right-sibling representation

#### Process

For rooted trees there is a simple representation.

First, choose an arbitrary order for the children of each node.

Then record two values for each node: its **first child**  `child[u]` and its **next sibling**  `sib[u]`. If the node has no children, `child[u]` is empty; if the node is the last child of its parent, `sib[u]` is empty.

#### Implementation

You can iterate over all children of a node like this.

```cpp
int v = child[u];  // start from the first child
while (v != EMPTY_NODE) {
  // ...
  // process child v
  // ...
  v = sib[v];  // move to the next child, i.e. a sibling of v
}
```

It can also be written more briefly as follows.

```cpp
for (int v = child[u]; v != EMPTY_NODE; v = sib[v]) {
  // ...
  // process child v
  // ...
}
```

### Binary tree

We need to record the left and right child of each node.

???+ note "Implementation"
    ```cpp
    int parent[N];
    int lch[N], rch[N];
    // -- or --
    int child[N][2];
    ```

## Tree traversal

### DFS on a tree

DFS on a tree works like this: first visit the root, then visit the subtree of each of the root's children in turn.

It can be used to find information such as the depth and parent of each node.

### DFS traversals of a binary tree

#### Preorder traversal

![preorder](images/tree-basic-preorder.svg)

Traverse the binary tree in the order **root, left, right**.

???+ note "Implementation"
    ```cpp
    void preorder(BiTree* root) {
      if (root) {
        cout << root->key << " ";
        preorder(root->left);
        preorder(root->right);
      }
    }
    ```

#### Inorder traversal

![inorder](images/tree-basic-inorder.svg)

Traverse the binary tree in the order **left, root, right**.

???+ note "Implementation"
    ```cpp
    void inorder(BiTree* root) {
      if (root) {
        inorder(root->left);
        cout << root->key << " ";
        inorder(root->right);
      }
    }
    ```

#### Postorder traversal

![postorder](images/tree-basic-postorder.svg)

Traverse the binary tree in the order **left, right, root**.

???+ note "Implementation"
    ```cpp
    void postorder(BiTree* root) {
      if (root) {
        postorder(root->left);
        postorder(root->right);
        cout << root->key << " ";
      }
    }
    ```

#### Reconstructing traversals

Given the inorder sequence and one other traversal sequence, you can work out the third.

![reverse](images/tree-basic-reverse.svg)

1.  The first element of the preorder sequence is `root`, and the last element of the postorder sequence is `root`.
2.  Find the root first. Then, in the inorder sequence, everything left of the root is the left subtree and everything right of it is the right subtree.
3.  Treat each subtree as a brand-new tree and apply the same rules again.

### BFS on a tree

Start from the root and visit nodes strictly level by level.

During BFS you can also find the depth and parent of each node along the way.

#### Level-order traversal

Level-order traversal visits nodes one level at a time, going across each level, from the root down to the leaves. By the definition of BFS, the order BFS produces is a level-order traversal. But level-order traversal requires different levels to be kept apart, so the result is usually given as a 2D array.

For example, the level-order traversal of the tree below is `[[1], [2, 3, 4], [5, 6]]` (each level from left to right).

![tree-basic-levelOrder](images/tree-basic-levelOrder.svg)

???+ note "Implementation"
    ```cpp
    vector<vector<int>> levelOrder(Node* root) {
      if (!root) {
        return {};
      }
      vector<vector<int>> res;
      queue<Node*> q;
      q.push(root);
      while (!q.empty()) {
        int currentLevelSize = q.size();  // number of nodes on the current level
        res.push_back(vector<int>());
        for (int i = 0; i < currentLevelSize; ++i) {
          Node* cur = q.front();
          q.pop();
          res.back().push_back(cur->val);
          for (Node* child : cur->children) {  // push all children
            q.push(child);
          }
        }
      }
      return res;
    }
    ```

### Morris traversal of a binary tree

The core problem in traversing a binary tree is: after visiting a node's children, how do we get back to that node and continue? Both the recursive and non-recursive methods use a stack to record the way back, which lets us move from a lower level to an upper level. The space complexity is $O(\log n)$ at best and $O(n)$ at worst (when the tree is a chain).

The idea of Morris traversal is to avoid the stack. It uses the unused `right` pointers of lower nodes to point back to some upper node, and that is how it moves from a lower level back up.

#### How Morris traversal works

Let `cur` be the current node. At the start, it is the root.

1.  If `cur` is empty, stop. Otherwise do the following.
2.  If `cur` has no left subtree, move `cur` right (`cur = cur->right`).
3.  If `cur` has a left subtree, find the rightmost node of the left subtree and call it `mostRight`.
    -   If the `right` pointer of `mostRight` is null, point it to `cur`, then move `cur` left (`cur = cur->left`).
    -   If the `right` pointer of `mostRight` points to `cur`, set it back to `null`, then move `cur` right (`cur = cur->right`).

For example, `cur` starts at node 1.

![tree-basic-morris-1](images/tree-basic-morris-1.svg)

The first time `cur` visits node 2, it finds the rightmost node of the left subtree, node 4, and points 4's `right` pointer at `cur` (node 2).

![tree-basic-morris-2](images/tree-basic-morris-2.svg)

`cur` goes back up through 4's `right` pointer. On the second visit to node 2, it again finds the rightmost node of the left subtree, node 4, sets 4's `right` pointer back to `null`, and continues into the right subtree. The rest of the process is omitted.

![tree-basic-morris-1](images/tree-basic-morris-1.svg)

The visiting order for the whole tree is `1242513637`. Notice that nodes with a left subtree are visited twice, and nodes without one are visited only once.

???+ note "Implementation"
    ```cpp
    void morris(TreeNode* root) {
      TreeNode* cur = root;
      while (cur) {
        if (!cur->left) {
          // If the current node has no left child, output its value and go into the right subtree
          std::cout << cur->val << " ";
          cur = cur->right;
          continue;
        }
        // Find the rightmost node of the current node's left subtree
        TreeNode* mostRight = cur->left;
        while (mostRight->right && mostRight->right != cur) {
          mostRight = mostRight->right;
        }
        if (!mostRight->right) {
          // If the rightmost node's right pointer is null, point it to the current node and go into the left subtree
          mostRight->right = cur;
          cur = cur->left;
        } else {
          // If the rightmost node's right pointer points to the current node, the left subtree is done; output the current node's value and go into the right subtree
          mostRight->right = nullptr;
          std::cout << cur->val << " ";
          cur = cur->right;
        }
      }
    }
    ```

### Unrooted trees

#### Process

Trees are usually traversed depth-first. The main thing to watch out for is not visiting a node twice.

Since a tree has no cycles, we only need to remember which node we came from, and then go into every adjacent node except that one. This avoids repeated visits.

???+ note "Implementation"
    ```cpp
    void dfs(int u, int from) {
      // Recurse into all children except from
      // For the starting node, from is empty, so all adjacent nodes are visited, as expected
      for (int v : adj[u])
        if (v != from) {
          dfs(v, u);
        }
    }
    
    // To start the traversal
    int EMPTY_NODE = -1;  // an index that does not exist
    int root = 0;         // pick any node as the starting point
    dfs(root, EMPTY_NODE);
    ```

### Rooted trees

For a rooted tree we need to tell parents from children.

Look at the traversal above: if we start from the root, the value of `from` when we reach a node is exactly the index of its parent.

This way, from an undirected input we can find the parent of every node, as well as each node's list of children.

**Part of this page is quoted from the blog post [Binary trees: preorder, inorder and postorder traversal](https://blog.csdn.net/weixin_43357638/article/details/99730284), under the CC 4.0 BY-SA license.**
