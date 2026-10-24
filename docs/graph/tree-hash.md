When checking whether some trees are isomorphic, we often turn the trees into hash values and store those, to lower the complexity.

Tree hashing is very flexible: you can design all kinds of hash schemes. But a carelessly designed one is quite likely to be wrong, and may be broken by anti-hash tests. Below we present a family of methods that is easy to implement and hard to break.

## Method

This method needs a hash function for multisets. The hash of the subtree rooted at a node is the hash of the multiset formed by the hashes of the subtrees rooted at all of its children, that is:

$$
h_x = f(\{ h_i \mid i \in son(x) \})
$$

Here $h_x$ is the hash of the subtree rooted at $x$, and $f$ is a hash function for multisets.

Take the hash function used in the code as an example:

$$
f(S) = \left( c + \sum_{x \in S} g(x) \right) \bmod m
$$

Here $c$ is a constant; $1$ is usually fine. $m$ is the modulus; usually $2^{32}$ or $2^{64}$ with natural overflow, though a large prime also works. $g$ is a mapping from integers to integers. The code uses xor shift; other functions also work, but polynomials are not recommended. To guard against problem setters who build tests against xor hashing, you can also XOR a random constant before and after the mapping.

This hash is very easy to write. If you need rerooting, in the second DP pass you just subtract the subtree's hash.

## Example problems

### [UOJ #763. Tree Hashing](https://uoj.ac/problem/763)

This is a template problem. Nothing more to say: just run one DFS with $1$ as the root.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/tree-hash/tree-hash_1.cpp"
    ```

### [\[BJOI2015\] Tree Isomorphism](https://www.luogu.com.cn/problem/P5043)

The isomorphism in this problem is for unrooted trees, while the method above is for rooted trees. So two isomorphic unrooted trees get the same hash only when they are rooted at matching nodes. Since the constraints are small, we can compute the hash with each node as the root by brute force, sort the hashes and compare.

If the constraints were larger, we could use rerooting DP, traversing the tree twice, to get the hash with each node as the root. We can also reuse the multiset hash function above: put the hashes for every choice of root into a multiset, compute the hash of that multiset, and compare (Approach 1).

We can also lower the complexity by finding centroids. A tree has at most two centroids, so we only need the hashes with it (or them) as the root. Then we can either compare these hashes separately (Approach 2), or, when there is one centroid, use its hash as the hash of the whole tree, and when there are two, take the smaller (or larger) of the two.

??? note "Approach 1"
    ```cpp
    --8<-- "docs/graph/code/tree-hash/tree-hash_2.cpp"
    ```

??? note "Approach 2"
    ```cpp
    --8<-- "docs/graph/code/tree-hash/tree-hash_3.cpp"
    ```

### [HDU 6647 Bracket Sequences on Tree](https://acm.hdu.edu.cn/showproblem.php?pid=6647)

The problem asks for the number of essentially different bracket sequences produced by traversing an unrooted tree.

First, note that two non-isomorphic rooted trees can never produce the same bracket sequence. Let us first count the essentially different bracket sequences from traversing a rooted tree. Suppose the root of the current subtree is $u$, and let $f(u)$ be the number of ways for this subtree. Going down from $u$, we can visit the children in any order, giving $|son(u)|!$ permutations, and the subtree of each child $v$ has $f(v)$ ways. So $f(u)=|son(u)|! \cdot \prod_{v \in son(u)} f(v)$. However, isomorphic subtrees cause duplicates, so $f(u)$ must be divided by the product of the factorials of how many times each distinct subtree appears, similar to permutations of a multiset.

With the DP above, we get the count for the root. Then with rerooting DP, passing the parent's hash and count information down to the children, we get the hash and count with each node as the root. Each distinct tree only needs to be counted once.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/tree-hash/tree-hash_4.cpp"
    ```

## References

The hashing method in this article is based on and extends the blog post [A tree hash that is easy to write and cannot be broken](https://peehs-moorhsum.blog.uoj.ac/blog/7891).
