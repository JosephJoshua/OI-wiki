author: isdanni

???+ warning "Note"
    This chapter is optional reading. Before reading it, make sure you have some familiarity with functional programming.

## Overview

A **finger tree** is a **purely functional** data structure proposed by Ralf Hinze and Ross Paterson.

## Why finger trees

In functional programming, lists are a very common data type. Almost every functional language supports sequence-based operations such as adding and removing elements at both ends (deque operations), inserting, concatenating and deleting at arbitrary nodes, finding an element that meets some condition, and splitting a sequence into subsequences. But these languages struggle to do more of these operations efficiently. Even when matching implementations exist, they are usually very complicated and hard to use in practice.

A finger tree provides a purely functional sequence data structure. It supports access and adding to the front and back of the sequence in amortized constant time, and concatenation and random access in logarithmic time. Besides good asymptotic running-time bounds, finger trees are also very flexible: combined with a [monoidal tag](https://en.wikipedia.org/wiki/Monoidal_category) on the elements, a finger tree can be used to implement efficient random-access sequences, ordered sequences, interval trees and priority queues.

## Basic structure

A finger tree stores data at the "fingers" (leaves) of the tree, with amortized constant access time. A finger is a point through which you can access part of a data structure. In imperative languages, this is called a pointer. In a finger tree, a "finger" is a structure pointing to the ends of the sequence, or to leaf nodes. A finger tree also stores, in each internal node, the result of applying some associative operation to its descendants. The data stored in internal nodes can be used to provide functionality beyond that of tree-like data structures.

1.  The depth of a finger tree is counted from the bottom up.
2.  The first level of a finger tree, the leaves, contains only values and has depth $0$. The second level has depth $1$, the third has depth $2$, and so on.
3.  The closer a node is to the root, the deeper the subtree of the original tree (the tree before it became a finger tree) that it points to. So working down the tree means going from the leaves to the root of the original tree, which is the opposite of a typical tree data structure. To get this structure, we must make sure the original tree has uniform depth. When declaring the node type, it must be parameterized by the type of its children. Nodes on the spine at depth $1$ and above point to trees, and with this parameterization they can be represented as nested nodes.

### Turning a tree into a finger tree

???+ note "Note"
    A **2-3 tree** is a tree data structure where every node with children (an internal node) has either two children (a $2$ node) and one data element, or three children (a $3$ node) and two data elements. A 2-3 tree is a B-tree of order $3$. Nodes on the outside of the tree (leaves) have no children and one or two data elements.

We start this process with a balanced 2-3 tree. For a finger tree to work, all leaves need to be on the same level, as in the figure below (taken from the finger tree paper):

![](./images/finger-tree-1.png)

A finger is "a structure that gives efficient access to nodes of a tree near a particular location." To make a finger tree, we put fingers at the left and right ends of the tree: we take the leftmost and rightmost internal nodes and pull them up, so that the rest of the tree hangs between them. This gives us amortized constant access time to the ends of the sequence.

![](./images/finger-tree-2.png)

This new data structure is called a finger tree. A finger tree consists of several layers (the blue boxes below) along its spine (the brown line):

![](./images/finger-tree-3.png)

```haskell
data FingerTree a = Empty
                  | Single a
                  | Deep (Digit a) (FingerTree (Node a)) (Digit a)

data Digit a = One a | Two a a | Three a a a | Four a a a a
data Node a = Node2 a a | Node3 a a a
```

The digits in the example are the nodes with letters. Each list is split by the prefix or suffix of each node on the spine. In the transformed 2-3 tree, the digit lists at the top level can have length two or three, while lower levels have length only one or two. To let some applications of finger trees run efficiently, a finger tree allows $1$ to $4$ subtrees at each level. The digits of a finger tree can be turned into a list, like:

```haskell
type Digit a = One a | Two a a | Three a a a | Four a a a a
```

The top level has elements of type $a$, and the next level has elements of type Node $a$, because of the nodes between the spine and the leaves. In general, this means level $n$ of the tree has elements of type $Node^{n}$ $a$, that is, 2-3 trees of depth $n$. So a sequence of $n$ elements is represented by a tree of depth `Θ(log n)`. An element at distance $d$ from the nearest end is stored at depth `Θ(log d)` in the tree.

### Deque operations

A finger tree also makes an efficient deque. Whether or not the structure is used persistently, all operations take `Θ(1)` time. It can be seen as an extension of the implicit deque[^okasaki1999purely]:

1.  Replacing pairs with 2-3 nodes gives enough flexibility to support efficient concatenation. (To keep deque operations constant-time, Digit must be extended to four.)
2.  Annotating internal nodes with a monoid allows efficient splitting.

```haskell
data ImplicitDeque a = Empty
                     | Single a
                     | Deep (Digit a) (ImplicitDeque (a, a)) (Digit a)

data Digit a = One a | Two a a | Three a a a
```

## Time complexity

A finger tree gives amortized constant-time access to the "fingers" (leaves) of the tree, where the data is stored, and concatenation and splitting in time logarithmic in the size of the smaller part. It also stores, in each internal node, the result of applying some associative operation to its descendants. The "summary" data stored in internal nodes can be used to provide functionality of data structures other than trees.

| Operation                     | Finger tree            | Annotated 2-3 tree            | List                 | Vector     |
| ----------------------------- | ---------------------- | ----------------------------- | -------------------- | ---------- |
| `cons`,`snoc`                 | $O(1)$                 | $O(\log n)$                   | $O(1)$/$O(n)$        | $O(n)$     |
| `viewl`,`viewr`               | $O(1)$                 | $O(\log n)$                   | $O(1)$/$O(n)$        | $O(1)$     |
| `measure`/`length`            | $O(1)$                 | $O(1)$                        | $O(n)$               | $O(1)$     |
| `append`                      | $O(\log \min(l1, l2))$ | $O(\log n)$                   | $O(n)$               | $O(m+n)$   |
| `split`                       | $O(\log \min(n, l-n))$ | $O(\log n)$                   | $O(n)$               | $O(1)$     |
| `replicate`                   | $O(\log n)$            | $O(\log n)$                   | $O(n)$               | $O(n)$     |
| `fromList`,`toList`,`reverse` | $O(l)$/$O(l)$/$O(l)$   | $O(l)$                        | $O(1)$/$O(1)$/$O(n)$ | $O(n)$     |
| `index`                       | $O(\log \min(n, l-n))$ | $O(\log n)$                   | $O(n)$               | $O(1)$     |

## Applications

Finger trees can be used to build other trees. For example, a priority queue can be implemented by labeling each internal node with the minimum priority among its children, and an indexed list/array can be implemented by labeling each node with the count of leaves under its children. Other applications include random-access sequences (described below), ordered sequences and interval trees.

A finger tree can provide amortized $O(1)$ push, reverse and pop, and $O(\log n)$ append and split, and it can be adapted to indexed or ordered sequences. Like all functional data structures, it is inherently persistent; that is, old versions of the tree are always kept.

For implementations, the finite sequence `Seq` in Haskell's core libraries uses 2-3 finger trees ([Data.Sequence](https://hackage.haskell.org/package/containers-0.6.5.1/docs/Data-Sequence.html)), and the [implementation](https://ocaml-batteries-team.github.io/batteries-included/hdoc2/BatFingerTree.html) of the `BatFingerTree` module in OCaml also uses a general finger tree data structure. Finger trees can be implemented with or without lazy evaluation, but laziness allows a simpler implementation.

## References and further reading

1.  Ralf Hinze and Ross Paterson, "[Finger trees: a simple general-purpose data structure](http://www.staff.city.ac.uk/~ross/papers/FingerTree.html)", Journal of Functional Programming 16:2 (2006) pp 197-217.
2.  [Finger Tree - Wikipedia](https://en.wikipedia.org/wiki/Finger_tree)

[^okasaki1999purely]: [Purely Functional Data Structures](https://www.cambridge.org/us/academic/subjects/computer-science/programming-languages-and-applied-logic/purely-functional-data-structures), Chris Okasaki (1999)
