## Definition

Suffixes are compared in lexicographic order. A suffix balanced tree is a balanced binary search tree that keeps these suffixes in sorted order: the suffix balanced tree of a string $T$ is the ordered set of all suffixes of $T$. Each node of the suffix balanced tree corresponds to one suffix of the original string.

In particular, the in-order traversal of a suffix balanced tree gives the suffix array.

## Construction

To build the suffix balanced tree of a string $T$ of length $n$, we insert its suffixes into the tree in reverse order (shortest first).

Let $X$ be the set kept by the suffix balanced tree, and let $S$ be the suffix added most recently. Then adding the next suffix means adding $\texttt{c}S$ to $X$ (you can also think of it as: the tree maintains the string $S$, and the next step prepends a character $\texttt{c}$ to $S$). This operation is just inserting a node into the balanced tree.

Here we use a balanced tree whose expected height is $O(\log n)$, such as a scapegoat tree or a treap.

### Method 1

When inserting, compare two suffixes by brute force to decide which subtree to go into next. One insertion makes at most $O(\log n)$ comparisons, and one comparison takes at most $O(n)$ time, so an insertion costs $O(n\log n)$ in total.

There are $n$ insertions, so this method has an upper bound of $O(n^2 \log n)$ on its time complexity.

### Method 2

Notice that $\texttt{c}S$ differs from $S$ only by the character $\texttt{c}$, and $S$ is already in $X$. We can use this to speed up insertion.

Suppose we want to compare the strings $\texttt{c}S$ and $A$, where $A, S \in X$. In each comparison, first compare the first characters of the two strings. If they differ, the order is already decided. If they are equal, we only need to compare the two strings with their first characters removed. Both of those strings are already in $X$, so we can finish the comparison using the balanced tree's $O(\log n)$ rank query. This way, one insertion costs at most $O(\log^2 n)$.

There are $n$ insertions, so this method has an upper bound of $O(n \log^2 n)$ on its time complexity.

### Method 3

Following method 2, if we could compare two nodes in the balanced tree in $O(1)$, we could build the suffix balanced tree in $O(n \log n)$ time.

Let $val_i$ be the value of node $i$. Suppose that while building the balanced tree, each node also keeps a tag $tag_i$ such that $tag_i > tag_j \iff val_i > val_j$. Then we can compare two nodes of the tree in $O(1)$ just by comparing their $tag_i$.

Let each node in the balanced tree correspond to an interval of real numbers, with the root corresponding to $(0, 1)$. For a node $i$ whose interval is $(l, r)$, set $tag_i = \frac{l + r}{2}$; its left subtree corresponds to the interval $(l, tag_i)$ and its right subtree to $(tag_i, r)$. It is easy to prove that $tag_i$ satisfies the requirement above.

Because we use a balanced tree whose expected height is $O(\log n)$, the precision is reasonably safe. In practice you can also use a larger interval, for example letting the root correspond to $(0, 10^{18})$.

### Method 4

We can also build the suffix array first and then build the suffix balanced tree from it. The bottleneck of this approach is either the cost of building the suffix array, or the cost of inserting $n$ elements at once into the chosen balanced tree.

## Deletion

Suppose the suffix added most recently is $\texttt{c}S$, and the one before it is $S$. The suffix balanced tree also supports deleting the suffix $\texttt{c}S$ (you can also think of it as: the tree maintains the string $\texttt{c}S$, and we delete the leading $\texttt{c}$).

Just like insertion, deleting $\texttt{c}S$ can be done with the balanced tree's node deletion.

## Advantages of the suffix balanced tree

-   The idea of the suffix balanced tree is clear and easier to understand than other suffix structures such as the suffix automaton. If you can write a balanced tree, you can write it.
-   Its complexity does not depend on the alphabet size.
-   It supports deleting a character from the front of the string.
-   If the balanced tree you use supports persistence, the suffix balanced tree can be made persistent too.

## Example problem

### [P3809 [Template] Suffix Sorting](https://www.luogu.com.cn/problem/P3809)

This is the template problem for suffix arrays. After building the suffix balanced tree, get the suffix array by an in-order traversal.

??? note "Reference code (SGT version)"
    ```cpp
    --8<-- "docs/string/code/suffix-bst/suffix-bst_1.cpp"
    ```

### [P6164 [Template] Suffix Balanced Tree](https://www.luogu.com.cn/problem/P6164)

???+ note "Problem statement"
    You are given an initial string $s$ and $q$ operations:
    
    1.  Append several characters to the end of the current string.
    2.  Delete several characters from the end of the current string.
    3.  Ask how many times the string $t$ occurs as a contiguous substring of the current string.
    
    The problem is **forced online**. The initial length and the length changes are $\le 8 \times 10^5$, $q \le 10^5$, and the total length of queries is $\le 3 \times 10^6$.

For operations 1 and 2: the suffix balanced tree easily supports inserting and deleting at the front, so we want to turn appending and deleting at the end into inserting and deleting at the front. We can do this by maintaining the suffix balanced tree of the reverse of $s$ instead of $s$ itself. Insertion and deletion in the balanced tree are both $O(\log n)$, so adding or deleting one character takes $O(\log n)$ time. If $N$ is the total number of characters added and deleted, this part takes $O(N \log n)$ time in total.

For operation 3: the number of occurrences of $t$ equals the number of suffixes that have $t$ as a prefix, which equals the rank of its successor minus the rank of its predecessor. Appending a very large character to $t$ gives a successor of $t$. Decreasing the last character of $t$ by 1 gives a predecessor of $t$.

Now we need the rank of a string $t$ in the suffix balanced tree. Since $t$ is not guaranteed to appear in the tree, we have to compare strings by brute force each time. One comparison takes $O(|t|)$, and one query makes at most $O(\log n)$ comparisons, so one query takes $O(|t|\log n)$. If $L$ is the total length of all query strings, this part takes $O(L \log n)$ time in total.

??? note "Reference code (SGT version)"
    ```cpp
    --8<-- "docs/string/code/suffix-bst/suffix-bst_2.cpp"
    ```

## References

-   Chen Lijie - "Applications of Weight-Balanced Trees and Suffix Balanced Trees in Informatics Olympiads"
