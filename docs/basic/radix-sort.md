???+ warning "Note"
    This page is not about [**counting sort**](./counting-sort.md).

This page gives a short introduction to radix sort.

## Definition

Radix sort is a non-comparison sorting algorithm. It was first used to sort punched cards. Radix sort splits each element into $k$ keys and sorts the elements by these keys one at a time, which in the end sorts all the elements.

If the keys are compared in order from the $1$st key to the $k$-th key, the algorithm is called MSD (Most Significant Digit first) radix sort.

If the keys are compared in order from the $k$-th key to the $1$st key, the algorithm is called LSD (Least Significant Digit first) radix sort.

## Comparing elements with k keys

Below, $a_i$ denotes the $i$-th key of element $a$.

Suppose each element has $k$ keys. The default way to compare two elements $a$ and $b$ is:

-   Compare the $1$st keys $a_1$ and $b_1$. If $a_1 < b_1$, then $a < b$; if $a_1 > b_1$, then $a > b$; if $a_1 = b_1$, go to the next step.
-   Compare the $2$nd keys $a_2$ and $b_2$. If $a_2 < b_2$, then $a < b$; if $a_2 > b_2$, then $a > b$; if $a_2 = b_2$, go to the next step.
-   ...
-   Compare the $k$-th keys $a_k$ and $b_k$. If $a_k < b_k$, then $a < b$; if $a_k > b_k$, then $a > b$; if $a_k = b_k$, then $a = b$.

Examples:

-   To compare natural numbers, line them up by their ones digit and pad the higher positions with $0$s. Then the $i$-th digit from the left can serve as the $i$-th key.
-   To compare strings in lexicographic order, the $i$-th character from the left can serve as the $i$-th key.
-   The default comparison of C++'s built-in `std::pair` and `std::tuple` works exactly as described above.

## MSD radix sort

The comparison method above suggests an idea: first compare the $1$st key of all elements, which gives a rough ordering. Then, among **elements with the same $1$st key**, compare their $2$nd keys, and so on.

Since this compares keys in order from the $1$st to the $k$-th, the resulting sorting algorithm is called MSD (Most Significant Digit first) radix sort.

### How it works

Split each element into $k$ keys. First stably sort by the $1$st key. Then, for each group of **elements with the same key**, stably sort by the $2$nd key (recursively)... and finally, for each group of **elements with the same keys**, stably sort by the $k$-th key.

We usually assume radix sort is stable, so in MSD radix sort we also only use a **stable algorithm** (usually counting sort) for the inner sort on each key.

For correctness, see the comparison of elements with k keys above.

### Reference code

#### Sorting natural numbers

Below is a recursive MSD radix sort that handles at most `MAXN` integers in $[0,2^{32}-1]$. Initially `digit=10`. If you change the radix, you must also change `RADIX` and `powRADIX` to match.

??? example "Reference code"
    ```cpp
    --8<-- "docs/basic/code/radix-sort/radix-sort_1.cpp:core"
    ```

#### Sorting strings

Below is a recursive MSD radix sort that sorts `std::string`s containing only lowercase English letters in lexicographic order:

??? example "Reference code"
    ```cpp
    --8<-- "docs/basic/code/radix-sort/radix-sort_2.cpp:core"
    ```

Comparing two strings can easily take $O(n)$ linear time. So for sorting strings, MSD radix sort beats most comparison-based sorting algorithms, both in time complexity and in actual running time.

### Relation to bucket sort

Prerequisite: [Bucket sort](./bucket-sort.md)

Bucket sort needs another sorting algorithm to sort the elements inside each bucket. But in fact, we can simply run bucket sort again on each bucket, until at some step every bucket holds $\le 1$ element.

So another way to see MSD radix sort is: bucket sort that uses bucket sort for its buckets.

This also suggests a way to cut the constant factor of MSD radix sort: once a bucket holds $\le B$ elements at some step ($B$ is a constant you choose), just run insertion sort on it and return. This reduces the number of recursive calls.

## LSD radix sort

MSD radix sort compares keys in order from the $1$st to the $k$-th, so it needs recursion or iteration to implement. Its constant factor is still fairly large, and it is a bit awkward for comparing natural numbers.

If we reverse the recursive process and compare keys in order from the $k$-th to the $1$st, we get LSD (Least Significant Digit first) radix sort, a sorting algorithm that needs no recursion.

### How it works

Split each element into $k$ keys. First stably sort **all elements** by the $k$-th key, then stably sort **all elements** by the $(k-1)$-th key, then stably sort **all elements** by the $(k-2)$-th key... and finally stably sort **all elements** by the $1$st key. This gives a stable sort of the whole sequence.

![An example of the full LSD radix sort process](images/radix-sort-1.svg)

LSD radix sort also needs a **stable algorithm** for the inner sort on each key. Again, counting sort is the usual choice.

For the correctness of LSD radix sort, see [the solution to Exercise 8.3-3 in *Introduction to Algorithms (3rd edition)*](https://walkccc.github.io/CLRS/Chap08/8.3/#83-3), or the explanation below.

### Correctness

Recall how elements with k keys are compared:

-   To decide the order of $a$ and $b$ from $a_1$ and $b_1$ alone, we need to already know the result of comparing $a_2$ and $b_2$, to handle the case $a_1 = b_1$.
-   To decide the order of $a$ and $b$ from $a_2$ and $b_2$ alone, we need to already know the result of comparing $a_3$ and $b_3$, to handle the case $a_2 = b_2$.
-   ...
-   To decide the order of $a$ and $b$ from $a_{k-1}$ and $b_{k-1}$ alone, we need to already know the result of comparing $a_k$ and $b_k$, to handle the case $a_{k-1} = b_{k-1}$.
-   $a_k$ and $b_k$ can be compared directly.

Now reverse the order:

-   $a_k$ and $b_k$ can be compared directly.
-   Once we know the result of comparing $a_k$ and $b_k$, we can get the result of comparing $a_{k-1}$ and $b_{k-1}$.
-   ...
-   Once we know the result of comparing $a_2$ and $b_2$, we can get the result of comparing $a_1$ and $b_1$.
-   Once we know the result of comparing $a_1$ and $b_1$, we finally have the result of comparing $a$ and $b$.

If we reorder the elements by each key as we go through this process, we get LSD radix sort.

### Pseudocode

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{An array } A \text{ consisting of }n\text{ elements, where each element has }k\text{ keys.}\\
2 & \textbf{Output. } \text{Array }A\text{ will be sorted in nondecreasing order stably.} \\
3 & \textbf{Method. }  \\
4 & \textbf{for }i\gets k\textbf{ down to }1\\
5 & \qquad\text{sort }A\text{ into nondecreasing order by the }i\text{-th key stably}
\end{array}
$$

### Reference code

Below is an LSD radix sort for elements with k keys.

??? example "Reference code"
    ```cpp
    --8<-- "docs/basic/code/radix-sort/radix-sort_lsd.cpp:core"
    ```

In fact, you don't have to loop from back to front to get a stable sort. It is enough to apply an operation equivalent to `std::exclusive_scan` to the `cnt` array.

???+ note "Example problem [Luogu P1177 [Template] Sorting](https://www.luogu.com.cn/problem/P1177)"
    Given $n$ positive integers, output them in increasing order.
    
    ```cpp
    --8<-- "docs/basic/code/radix-sort/radix-sort_3.cpp"
    ```

## Properties

### Stability

If the inner sort on each key is stable, then both MSD and LSD radix sort are stable sorting algorithms.

### Time complexity

Radix sort is usually faster than comparison-based sorting algorithms (such as quicksort). But it needs extra memory, so when memory is scarce, an in-place algorithm (such as quicksort) may be a better choice.[^ref1]

The bounds below assume that extracting one key and moving one element (or its index) each take $O(1)$ time. In general, if each key has a small value range, we can use [counting sort](./counting-sort.md) as the inner sort. The time complexities of LSD and MSD are then

$$
O\left(kn+\sum_{i=1}^k w_i\right),\qquad O\left(kn+\sum_{i=1}^k b_iw_i\right),
$$

where $b_i$ is the number of buckets on which counting sort is actually run at level $i$, and $w_i$ is the size of the value range of the $i$-th key. If the key value ranges are large, just use an $O(nk\log n)$ comparison-based sort instead of radix sort.

### Space complexity

Below we count auxiliary space beyond the input, assuming each element or its index takes $O(1)$ space. With counting sort, LSD can reuse a temporary array of length $n$ and the count array, so its auxiliary space is $O(n+\max_i w_i)$. Recursive MSD, if it reuses the temporary array but keeps the bucket boundaries at each level of recursion, uses $O(n+\sum_{i=1}^k w_i)$ auxiliary space. When the value range of each digit is fixed, these simplify to $O(n)$ and $O(n+k)$ respectively. Here $k$ is the number of keys.

## References and notes

[^ref1]: Thomas H. Cormen, Charles E. Leiserson, Ronald L. Rivest, and Clifford Stein.*Introduction to Algorithms*(3rd ed.). MIT Press and McGraw-Hill, 2009. ISBN 978-0-262-03384-8. "8.3 Radix sort", pp. 199.
