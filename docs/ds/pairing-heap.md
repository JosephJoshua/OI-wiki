## Introduction

The pairing heap is a data structure that supports insertion, finding/deleting the minimum, merging, and changing an element's value. It is a mergeable heap. It is fast and simple, but because its complexity is amortized (based on potential analysis), it cannot be made persistent.

## Definition

A pairing heap is a weighted multiway tree that satisfies the heap property (see the figure below): every node's value is less than or equal to the values of all its children (we use a min-heap as the example here and below).  
![](./images/pairingheap1.jpg)

We usually store a pairing heap with the child-sibling representation (see the figure below): all children of a node form a singly linked list. Each node stores a pointer to its first child, which is the head of that list, and a pointer to its right sibling.

This representation makes the pairing heap easy to implement, and it also makes the complexity analysis easier.

![](./images/pairingheap2.jpg)

```cpp
struct Node {
  T v;  // T is the value type
  Node *child, *sibling;
  // child points to this node's first child, sibling points to its next sibling.
  // If the node has no child/next sibling, the pointer is nullptr.
};
```

From the definition, we can see that unlike other common heaps, the pairing heap stores no extra information such as tree size, depth or rank (the binary heap also stores no extra information, but it guarantees its complexity by keeping a strict complete binary tree shape). Also, any tree that satisfies the heap property is a valid pairing heap. Being this simple and flexible is what makes pairing heaps so fast in practice. In contrast, the Fibonacci heap has a poor constant factor precisely because it must maintain a lot of extra information.

The pairing heap guarantees its total complexity through a carefully designed order of operations. The original paper[^ref1] calls it "a Self Adjusting Heap". In this respect it is quite similar to the splay tree (called a "Self Adjusting Binary Tree" in its original paper).

## Process

### Finding the minimum

By the definition, the root of a pairing heap always has the smallest value, so we just return the root.

### Merging

Merging two pairing heaps is simple: make the smaller of the two roots the new root, and insert the larger root as its child. (See the figure below.)

![](./images/pairingheap3.jpg)

Note that a node's child list is ordered by insertion time: the rightmost node became a child of the parent earliest, and the leftmost node became a child most recently.

???+ note "Implementation"
    ```cpp
    Node* meld(Node* x, Node* y) {
      // If one of them is empty, return the other
      if (x == nullptr) return y;
      if (y == nullptr) return x;
      if (x->v > y->v) std::swap(x, y);  // after the swap, x is the heap with the smaller value, y the one with the larger value
      // make y a child of x
      y->sibling = x->child;
      x->child = y;
      return x;  // the new root is x
    }
    ```

### Insertion

Since we already have merging, to insert we just treat the new element as a new pairing heap and merge it with the original heap.

### Deleting the minimum

First, note that the operations above are all very lazy: they do no maintenance of the data structure at all. So we must design the delete-min operation carefully to keep the total complexity under control.

The root is the minimum, so we need to delete the root. Think about what happens once the root is removed: all its former children form a forest. But a pairing heap must be a single tree, so we need to merge all these children together in some order.

A natural idea is to use `meld` to merge the children one by one from left to right. This is obviously correct, but a single operation can then degrade to $O(n)$.

To guarantee the total amortized complexity, we need a "two-pass" merging method:

1.  Pair up the children two by two, and use `meld` to merge the two children in each pair (see figure 1 below),
2.  Merge the resulting heaps one by one **from right to left** (that is, from older children to newer children) (see figure 2 below).

![](./images/pairingheap4.jpg)

![](./images/pairingheap5.jpg)

First we implement a helper function `merges`, which merges a node with all of its siblings.

???+ note "Implementation"
    ```cpp
    Node* merges(Node* x) {
      if (x == nullptr || x->sibling == nullptr)
        return x;  // if the tree is empty or has no next sibling, there is nothing to merge; return.
      Node* y = x->sibling;                // y is the next sibling of x
      Node* c = y->sibling;                // c is the sibling after that
      x->sibling = y->sibling = nullptr;   // split them apart
      return meld(merges(c), meld(x, y));  // the core part
    }
    ```

The last line is the core of the function. It has three parts:

1.  `meld(x,y)` "pairs" x and y.
2.  `merges(c)` recursively merges c and its siblings.
3.  The two new trees produced by the two operations above are merged.

Note that, as mentioned above, the second pass must merge in a specific direction (from right to left). This recursive implementation already guarantees that order. If you write your own iterative version, be sure to keep this order, or the complexity is no longer guaranteed.

With the `merges` function, the `delete-min` operation is straightforward.

???+ note "Implementation"
    ```cpp
    Node* delete_min(Node* x) {
      Node* t = merges(x->child);
      delete x;  // if memory needs to be freed
      return t;
    }
    ```

### Decreasing an element's value

To support this operation, we add a "parent" pointer to each node. If the node has a left sibling, it points to that left sibling instead of the actual parent; otherwise it points to the parent.

First, change the node definition to:

???+ note "Implementation"
    ```cpp
    struct Node {
      LL v;
      int id;
      Node *child, *sibling;
      Node *father;  // new: parent pointer; nullptr if this node is the root
    };
    ```

Change `meld` to:

???+ note "Implementation"
    ```cpp
    Node* meld(Node* x, Node* y) {
      if (x == nullptr) return y;
      if (y == nullptr) return x;
      if (x->v > y->v) std::swap(x, y);
      if (x->child != nullptr) {  // new: maintain the parent pointer
        x->child->father = y;
      }
      y->sibling = x->child;
      y->father = x;  // new: maintain the parent pointer
      x->child = y;
      return x;
    }
    ```

Change `merges` to:

???+ note "Implementation"
    ```cpp
    Node *merges(Node *x) {
      if (x == nullptr) return nullptr;
      x->father = nullptr;  // new: maintain the parent pointer
      if (x->sibling == nullptr) return x;
      Node *y = x->sibling, *c = y->sibling;
      y->father = nullptr;  // new: maintain the parent pointer
      x->sibling = y->sibling = nullptr;
      return meld(merges(c), meld(x, y));
    }
    ```

Now let us see how to implement `decrease-key`.  
First, notice that after we decrease the value of node `x`, the subtree rooted at `x` still satisfies the pairing heap property, but `x` and its parent may no longer satisfy the heap property.  
So we cut out the whole subtree rooted at `x`. Now both trees satisfy the pairing heap property, and we merge them back together to finish the operation.

???+ note "Implementation"
    ```cpp
    // root is the root of the heap, x is the node to change, v is the new value; the caller must ensure v <= x->v
    // returns the new root
    Node *decrease_key(Node *root, Node *x, LL v) {
      x->v = v;                 // update the value
      if (x == root) return x;  // if x is the root, return it directly
      // cut x out of fa's children; we must handle the cases by where x is.
      if (x->father->child == x) {
        x->father->child = x->sibling;
      } else {
        x->father->sibling = x->sibling;
      }
      if (x->sibling != nullptr) {
        x->sibling->father = x->father;
      }
      x->sibling = nullptr;
      x->father = nullptr;
      return meld(root, x);  // merge x and the root again
    }
    ```

## Complexity analysis

The pairing heap is simple in structure and implementation, but its time complexity is not easy to analyze.

The original paper[^ref1] only proved that `meld` and `delete-min` both take amortized $O(\log n)$ time, and conjectured that every operation has the same complexity as in a Fibonacci heap.

Unfortunately, it was later found that for pairing heaps that store no extra information, there are operation sequences on which the amortized cost of `decrease-key` is at least $\Omega (\log \log n)$[^ref2].

The best current upper bounds include Iacono's $O(1)$ `meld` and $O(\log n)$ `decrease-key`[^ref3], and Pettie's $O(2^{2 \sqrt{\log \log n}})$ `meld` and `decrease-key`[^ref4]. Note that these are all amortized bounds, so you cannot take the minimum of each result separately.

## References

[^ref1]: [The pairing heap: a new form of self-adjusting heap](http://www.cs.cmu.edu/~sleator/papers/pairing-heaps.pdf)

[^ref2]: [On the efficiency of pairing heaps and related data structures](https://dl.acm.org/doi/10.1145/320211.320214)

[^ref3]: [Improved upper bounds for pairing heaps](https://arxiv.org/abs/1110.4428)

[^ref4]: [Towards a Final Analysis of Pairing Heaps](http://web.eecs.umich.edu/~pettie/papers/focs05.pdf)

-   <https://en.wikipedia.org/wiki/Pairing_heap>
-   <https://brilliant.org/wiki/pairing-heap/>
