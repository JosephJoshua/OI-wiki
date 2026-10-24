## Introduction

A persistent trie works much like a persistent segment tree. Each time, we only create the nodes that are added or whose values change, and keep the unchanged nodes, linking edges onto the previous version. In the end, the trie reached by traversing from each version's root is complete and contains all the information of that version.

In most persistent trie problems, the trie appears as a [01-trie (binary trie)](../string/trie.md#维护异或极值).

??? note "Example problem [Maximum XOR Sum](https://www.luogu.com.cn/problem/P4735)"
    Maintain the following operations on an array $a$ of length $n$:
    
    1.  Append a number $x$ to the end of the array; the length $n$ increases by $1$.
    2.  Given a query range $[l,r]$ and a value $k$, find the maximum of $k \oplus \bigoplus^{n}_{i=p} a_i$ over $l\le p\le r$.

## Process

The value being asked for looks a bit awkward. Using the usual trick for consecutive XORs, let $s_x=\bigoplus_{i=1}^x a_i$. Then the expression equals $s_{p-1}\oplus s_n\oplus k$. Since $s_n \oplus k$ is fixed during a query, the query becomes: find the maximum XOR of a fixed value ($s_n\oplus k$) with an element in the range $[l-1,r-1]$.

Following the same idea as the persistent segment tree, first suppose each query asks about the whole range. We just build a trie over the range, inserting every number in it. When querying, we try to go to the child whose bit differs from the current bit whenever possible.

To query a range, we use the idea of prefix sums and differences: subtracting two prefix tries (that is, two historical versions from inserting numbers in order) gives the trie for that range. We also create nodes dynamically and never add nodes that were not computed, which saves memory.

```cpp
--8<-- "docs/ds/code/persistent-trie/persistent-trie_1.cpp"
```
