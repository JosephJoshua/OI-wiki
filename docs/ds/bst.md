author: 2323122, aofall, AtomAlpaca, Bocity, CoelacanthusHex, countercurrent-time, Early0v0, Enter-tainer, fearlessxjdx, Great-designer, H-J-Granger, hsfzLZH1, iamtwz, Ir1d, ksyx, Marcythm, NachtgeistW, ouuan, Persdre, shuzhouliu, StudyingFather, SukkaW, Tiphereth-A, wsyhb, Yesphet, yuhuoji, lingkerio, bililateral, q-wind

## Definition

A binary search tree is a tree data structure built on a binary tree. It is defined as follows:

1.  An empty tree is a binary search tree.

2.  If the left subtree of a binary search tree is not empty, then the values of all nodes in its left subtree are less than the value of its root.

3.  If the right subtree of a binary search tree is not empty, then the values of all nodes in its right subtree are greater than the value of its root.

4.  The left and right subtrees of a binary search tree are both binary search trees.

The time taken by the basic operations on a binary search tree is proportional to the height of the tree. For a binary search tree with $n$ nodes, these operations take $O(\log n)$ time in the best case and $O(n)$ in the worst case. A randomly built binary search tree has expected height $O(\log n)$.

## Process

### Defining a binary search tree node

???+ note "Implementation"
    ```cpp
    struct TreeNode {
      int key;
      TreeNode* left;
      TreeNode* right;
      // maintain other information, such as height, number of nodes, etc.
      int size;   // size of the subtree rooted at this node
      int count;  // number of copies of this node's value
    
      TreeNode(int value)
          : key(value), size(1), count(1), left(nullptr), right(nullptr) {}
    };
    ```

### Traversing a binary search tree

From the recursive definition of a binary search tree, the in-order traversal of a binary search tree gives a non-decreasing sequence of values. The time complexity is $O(n)$.

The code for traversing a binary search tree is as follows:

???+ note "Implementation"
    ```cpp
    void inorderTraversal(TreeNode* root) {
      if (root == nullptr) {
        return;
      }
      inorderTraversal(root->left);
      std::cout << root->key << " ";
      inorderTraversal(root->right);
    }
    ```

### Finding the minimum/maximum

From the properties of a binary search tree, the minimum is at the end of the left chain of the tree, and the maximum is at the end of the right chain. The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    int findMin(TreeNode* root) {
      if (root == nullptr) {
        return -1;
      }
      while (root->left != nullptr) {
        root = root->left;
      }
      return root->key;
    }
    
    int findMax(TreeNode* root) {
      if (root == nullptr) {
        return -1;
      }
      while (root->right != nullptr) {
        root = root->right;
      }
      return root->key;
    }
    ```

### Searching for an element

Search for a node with value `value` in the binary search tree rooted at `root`.

There are the following cases:

-   If `root` is empty, return `false`.
-   If the value of `root` equals `value`, return `true`.
-   If the value of `root` is greater than `value`, continue searching in the left subtree of `root`.
-   If the value of `root` is less than `value`, continue searching in the right subtree of `root`.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    bool search(TreeNode* root, int target) {
      if (root == nullptr) {
        return false;
      }
      if (root->key == target) {
        return true;
      } else if (target < root->key) {
        return search(root->left, target);
      } else {
        return search(root->right, target);
      }
    }
    ```

Insertion, deletion and modification all start with a search in the binary search tree.

### Inserting an element

Insert a node with value `value` into the binary search tree rooted at `root`.

There are the following cases:

-   If `root` is empty, just return a new node with value `value`.

-   If the value of `root` equals `value`, increase the occurrence count stored in that node by $1$.

-   If the value of `root` is greater than `value`, insert a node with value `value` into the left subtree of `root`.

-   If the value of `root` is less than `value`, insert a node with value `value` into the right subtree of `root`.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    TreeNode* insert(TreeNode* root, int value) {
      if (root == nullptr) {
        return new TreeNode(value);
      }
      if (value < root->key) {
        root->left = insert(root->left, value);
      } else if (value > root->key) {
        root->right = insert(root->right, value);
      } else {
        root->count++;  // equal value: increase the count of copies
      }
      root->size = root->count + (root->left ? root->left->size : 0) +
                   (root->right ? root->right->size : 0);  // update the subtree size
      return root;
    }
    ```

### Deleting an element

Delete a node with value `value` from the binary search tree rooted at `root`.

First search the binary search tree for the node with value `value`. There are the following cases:

-   If the node's `count` is greater than $1$, just decrease `count`.

-   If the node's `count` is $1$:

    -   If `root` is a leaf, just delete the node.

    -   If `root` is a chain node, that is, a node with only one child, return that child.

    -   If `root` has two non-empty children, we usually replace it with the maximum of its left subtree (the rightmost node of the left subtree) or the minimum of its right subtree (the leftmost node of the right subtree), then delete it.

The time complexity is $O(h)$.

???+ note "Implementation"
    The method is called as `root = remove(root, 1)`, which deletes the node with value 1 from the tree rooted at `root` and returns the new root.
    
    ```cpp
    // the return value is the new root after deleting value
    TreeNode* remove(TreeNode* root, int value) {
      if (root == nullptr) {
        return root;
      }
      if (value < root->key) {
        root->left = remove(root->left, value);
      } else if (value > root->key) {
        root->right = remove(root->right, value);
      } else {
        if (root->count > 1) {
          root->count--;  // more than 1 copy: decrease the count
        } else {
          if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
          } else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
          } else {
            TreeNode* successor = findMinNode(root->right);
            root->key = successor->key;
            root->count = successor->count;  // update the count
            // when successor->count > 1 we must still delete that node, otherwise
            // the later deletion would only decrease the count
            successor->count = 1;
            root->right = remove(root->right, successor->key);
          }
        }
      }
      // recompute size instead of writing --root->size;
      // because value may not be in the tree, so nothing may have been deleted
      root->size = root->count + (root->left ? root->left->size : 0) +
                   (root->right ? root->right->size : 0);
      return root;
    }
    
    // here we use the minimum of the right subtree as the example
    TreeNode* findMinNode(TreeNode* root) {
      while (root->left != nullptr) {
        root = root->left;
      }
      return root;
    }
    ```

### Finding the rank of an element

The rank is defined as the number of elements before the first equal element, plus one, after sorting the array in ascending order.

To find the rank of an element, walk from the root to this element. Each time we move right, add the size of the left child's subtree plus the count of the current node to the answer. At the end, add the size of the left subtree of the final node plus one.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    int queryRank(TreeNode* root, int v) {
      if (root == nullptr) return 0;
      if (root->key == v) return (root->left ? root->left->size : 0) + 1;
      if (root->key > v) return queryRank(root->left, v);
      return queryRank(root->right, v) + (root->left ? root->left->size : 0) +
             root->count;
    }
    ```

### Finding the element with rank k

In a subtree, the rank of the root depends on the size of its left subtree.

-   If the size of its left subtree is greater than or equal to $k$, the element is in the left subtree;

-   If the size of its left subtree is in the range $[k-\textit{count},k-1]$ (where `count` is the number of occurrences of the current node's value), the element is the root of the subtree;

-   If the size of its left subtree is less than $k-\textit{count}$, the element is in the right subtree.

The time complexity is $O(h)$.

???+ note "Implementation"
    ```cpp
    int querykth(TreeNode* root, int k) {
      if (root == nullptr) return -1;  // or return another suitable value as needed
      if (root->left) {
        if (root->left->size >= k) return querykth(root->left, k);
        if (root->left->size + root->count >= k) return root->key;
      } else {
        if (k <= root->count) return root->key;
      }
      return querykth(root->right,
                      k - (root->left ? root->left->size : 0) - root->count);
    }
    ```

## Introduction to balanced trees

One goal of using a search tree is to reduce the time for inserting, deleting, modifying and finding nodes (insertion, deletion and modification all include a find).

As for search efficiency, if a tree has height $h$, in the worst case finding a key takes $h$ comparisons, so the search time (also called the average search length, ASL) is at most $O(h)$. In an ideal binary search tree, all operations can be done in $O(\log n)$ time (where n is the total number of nodes).

However, $O(\log n)$ is only the ideal case. In the worst case, a search tree can degrade into a linked list. Imagine a binary search tree where every node has only a right child: it behaves just like a linked list, and all operations (insert, delete, modify, find) take $O(n)$ time.

We can see that the complexity of the operations depends on the height $h$ of the tree. This leads to balanced trees, which keep the height of the tree small (balanced) through certain operations to reduce the cost of operations.

### Definition of balance

As for whether a search tree is "**balanced**", different balanced trees define "**balanced**" in different ways. For example, if in a binary search tree rooted at T the left and right subtrees differ greatly in height, or the left subtree has far more nodes than the right subtree, the tree is clearly not balanced.

For binary search trees, a common definition of balance is: in the tree rooted at T, the heights of the left and right subtrees of every node differ by at most 1.

-   In a [Splay tree](splay.md), any access to a node (search, insertion or deletion) moves the accessed node to the root of the tree.

-   In an [AVL tree](avl.md), each node N stores the height of the tree rooted at N. An AVL tree defines balance as follows: T is an AVL tree if and only if its left and right subtrees are AVL trees and $|height(T->left) - height(T->right)| \leq 1$.

-   In a [Size Balanced Tree](sbt.md), each node N stores `size`, the number of nodes in the tree rooted at N. Balance is defined as: the `size` of any node is not less than the `size` of any child (nephew) of its sibling.

Also, for search trees with the same set of values, the balanced state may not be unique. That is, two different search trees may contain the same set of values and both be balanced.

### Rebalancing

Adjusting a search tree that does not satisfy the balance condition can make an unbalanced search tree balanced again.

For balanced binary trees, rebalancing uses two operations: **left rotation (Left Rotate, or zag)** and **right rotation (Right Rotate, or zig)**. A balanced binary tree must keep its in-order traversal unchanged during rebalancing, and neither of these operations changes the in-order traversal.

We introduce the right rotation first. It is also called a "single right rotation" or an "LL balancing rotation". A right rotation at node $A$ means: rotate $A$'s left child $B$ up and to the right so that it replaces $A$ as the root; rotate $A$ down and to the right so that it becomes the root of $B$'s right subtree; and $B$'s original right subtree becomes $A$'s left subtree.

![bst-rotate](images/bst-rotate.svg)

A right rotation only changes three node links, which is like cyclically permuting three edges. So we need to save one node temporarily before updating the links in turn.

The usual update order for a right rotation is: save node $B$ (the new root), make $A$'s left child point to $B$'s right subtree $T2$, then make $B$'s right child pointer point to $A$, and finally make $A$'s parent point to the saved $B$.

In exactly the same way, there is a corresponding left rotation, also called a "single left rotation" or an "RR balancing rotation". The left and right rotations are mirror images of each other.

Below is the code for left and right rotations.

???+ note "Implementation"
    ```cpp
    TreeNode* rotateLeft(TreeNode* root) {
      TreeNode* newRoot = root->right;
      root->right = newRoot->left;
      newRoot->left = root;
      // update the information of the affected nodes
      updateHeight(root);
      updateHeight(newRoot);
      return newRoot;  // return the new root
    }
    
    TreeNode* rotateRight(TreeNode* root) {
      TreeNode* newRoot = root->left;
      root->left = newRoot->right;
      newRoot->right = root;
      updateHeight(root);
      updateHeight(newRoot);
      return newRoot;
    }
    ```

When calling this example code, you need to keep the parent `pre` of `root`. The method returns a pointer to the new root, so you just need to make `pre` point to the new root.

#### Four cases where balance is broken

Different balanced binary trees have different definitions, but they differ only in what information their nodes store and how that information is updated after a rotation. There are only four ways the balance of a balanced binary tree can be broken, and rebalancing only uses left and right rotations. Below we first introduce the four cases, then compare different balanced binary trees.

LL case: the left subtree of T's left child is too tall, which breaks the balance.

Fix: rotate node T right.

![bst-LL](images/bst-LL.svg)

RR case: like the LL case, the right subtree of T's right child is too tall, which breaks the balance.

Fix: rotate node T left.

![bst-RR](images/bst-RR.svg)

LR case: the right subtree of T's left child is too tall, which breaks the balance.

Fix: first rotate node L left, which turns it into the LL case, then rotate node T right.

![bst-LR](images/bst-LR.svg)

RL case: like the LR case, the left subtree of T's right child is too tall, which breaks the balance.

Fix: first rotate node R right, which turns it into the RR case, then rotate node T left.

![bst-RL](images/bst-RL.svg)
