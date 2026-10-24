author: sshwy

The way of thinking behind the disjoint set union (DSU) and the Kruskal reconstruction tree is very similar; both can be used to handle problems about connectivity. This article uses example problems to show how the DSU idea can be applied.

## A

???+ note "A"
    There are $n$ vertices, all initially isolated.
    
    Then there are $m$ edge-adding operations; the $i$-th operation adds an undirected edge between $a_i$ and $b_i$. Let $L(i,j)$ mean that vertices $i$ and $j$ first become connected after the $L(i,j)$-th operation.
    
    After all $m$ operations, you need to compute $\sum_{i=1}^n\sum_{j=i+1}^nL(i,j)$.

This is a basic application of DSU, where the DSU also keeps the size of each subtree. Count the contribution of each operation. If in the $i$-th operation $a_i$ and $b_i$ belong to two different subtrees, merge the two subtrees, and add the product of their sizes times $i$ to the answer. The time complexity is $O(n\alpha(n))$.

## B

???+ note "B"
    There are $n$ vertices, all initially isolated.
    
    Then there are $m$ edge-adding operations; the $i$-th operation adds an undirected edge between $a_i$ and $b_i$.
    
    Then there are $q$ queries; the $i$-th query asks after which operation $u_i$ and $v_i$ first become connected.

While merging in the DSU, record a "DSU spanning tree": if in the $i$-th operation $a_i$ and $b_i$ belong to two different subtrees, add the edge $(a_i,b_i)$ to the spanning tree with weight $i$. Then a query asks for the maximum edge weight on the path from $u$ to $v$, which can be maintained with binary lifting on the tree or heavy-light decomposition. The time complexity is $O(n\log n)$.

Another method is to maintain a Kruskal reconstruction tree, which is essentially the same as the DSU spanning tree. The complexity is also the same.

## C

???+ note "C"
    There are $n$ vertices, all initially isolated.
    
    Then there are $m$ edge-adding operations; the $i$-th operation adds an undirected edge between $a_i$ and $b_i$.
    
    Then there are $q$ queries; the $i$-th query asks for the size of the connected component containing vertex $x_i$ after the $t_i$-th operation.

Offline algorithm: sort the queries by $t_i$ in increasing order. While adding edges, use the DSU to answer the queries along the way. The time complexity is $O(q\log q+(n+q)\alpha(n))$.

Online algorithm: for this problem, the online algorithm can only use the Kruskal reconstruction tree. The difference between the Kruskal reconstruction tree and the DSU is this: when $a_i$ and $b_i$ belong to two different subtrees in the $i$-th operation, Kruskal creates a new node $u$, and connects the root of $a_i$'s subtree and the root of $b_i$'s subtree to $u$ as its two children. Let the weight of $u$ be $i$. The original $n$ vertices have weight $0$.

For a query, we only need to find the largest connected part containing $x_i$ in the reconstruction tree such that the maximum node weight in it does not exceed $t_i$. The answer to the query is the number of nodes with weight $0$ in this part, that is, the number of leaves.

Since the operation indices increase, a parent's weight in the reconstruction tree is always greater than its child's weight. This means we can use binary lifting on the path from $x_i$ to the root of the reconstruction tree to find the node with the largest weight not exceeding $t_i$. This gives the answer. The time complexity is $O(n\log n)$.

## D

???+ note "D"
    You are given a 01 sequence $a_1,\ldots,a_n$ of length $n$, initially all $0$. Then $m$ operations are performed:
    
    -   Set $a_x=1$;
    -   Find the first position from the left among $a_x,a_{x+1},\ldots,a_n$ whose value is $0$.

Build a DSU where $f_i$ is the position of the first $0$ among $a_i,a_{i+1},\ldots,a_n$. Initially $f_i=i$.

For an operation $a_x=1$, if $a_x$ already equals $1$, do nothing. Otherwise, set $f_x=f_{x+1}$.

The time complexity is $O(n\log n)$. Using union by rank makes the implementation more troublesome, but it is still possible; then the time complexity can become $O(n\alpha(n))$.

## E

???+ note "E"
    You are given three sequences $a$, $b$, $c$ of positive integers, each of length $n$. Over all $1\le i\le j\le n$, find the maximum of $a_i\cdot b_j\cdot \min_{i\le k\le j}c_k$.

This problem also has many solutions; here we focus on the DSU approach. Consider the $c_k$ in decreasing order of value. This is like adding a point at $k$, then merging it with the connected components containing the points at positions $k-1$ and $k+1$ (if those positions have points). Each connected component records the maximum of $a$ and the maximum of $b$, so the answer can be updated during merging. The time complexity is $O(n\log n)$.

## F

???+ note "F"
    You are given a tree with $n$ vertices. Then there are $m$ operations:
    
    -   Add an edge from $a_i$ to $b_i$.
    -   Ask whether there are at least two edge-disjoint paths between vertices $u_i$ and $v_i$.

A query can be rephrased as: are $u_i$ and $v_i$ on the same simple cycle? Following the idea of contracting biconnected components, each time we add an edge between $a_i$ and $b_i$, we can contract the vertices on the tree path from $a_i$ to $b_i$ into one. If the tree paths of two edges $(a_i,b_i)$ and $(a_j,b_j)$ intersect, the two edges get contracted together.

In other words, adding an edge can be seen as covering the edges on the tree path from $a_i$ to $b_i$ once. A query then becomes: is there any uncovered edge on the path from $u_i$ to $v_i$? If not, then $u_i$ and $v_i$ belong to the same biconnected component, and therefore to the same simple cycle.

We maintain this with a DSU. Root the tree, and let $f_i$ be the first uncovered edge on the path from $i$ to the root. Then for each edge-adding operation, we jump through the DSU by brute force. After covering an edge, merge the $f$ of the node corresponding to that edge with its parent. This way, each edge is covered at most once, and the total complexity is $O(n\log n)$. With a DSU using union by rank, we can also reach $O(n\alpha(n))$.

The way this problem is maintained is like a tree version of D.

## G

???+ note "G"
    An undirected graph $G$ has $n$ vertices, all initially isolated (that is, there are no edges).
    
    Then there are $m$ edge-adding operations; the $i$-th operation adds an undirected edge between $a_i$ and $b_i$.
    
    After each operation, you need to find the number of bridges in the graph.
    
    A bridge is defined as follows: an edge $(x,y)$ in $G$ is called a bridge if deleting it increases the number of connected components.
    
    The problem must be solved online.

This problem tests your understanding of the properties of DSU. Use a DSU to maintain connectivity. For the bridge tree (the tree of 2-edge-connected components), maintain a rooted tree, where $p_i$ is the parent of node $i$. This is just a DSU without path compression.

If in the $i$-th operation $a_i$ and $b_i$ are in the same connected component, we need to contract the nodes on the path from $a_i$ to $b_i$ in the bridge tree. This can be maintained with a DSU. Each contraction decreases the number of 2-edge-connected components by $1$, and this can happen at most $n-1$ times, so the DSU cost of the contraction part is $O(n\alpha(n))$.

To contract, we first need the LCA of $a_i$ and $b_i$ in the bridge tree. For this we can maintain a mark array. Starting from $a_i$ and $b_i$, take turns jumping up one ancestor at a time, marking every node along the way. As soon as we reach a node that has already been marked, that node is the LCA of $a_i$ and $b_i$. The cost of this algorithm is linear in the length of the path from $a_i$ to $b_i$, which is acceptable.

If $a_i$ and $b_i$ are in two different connected components, we merge the two components, and the number of bridges increases by $1$. We then need to join the bridge trees of the two vertices, that is, add an edge from $a_i$ to $b_i$. So we need to re-root one of the trees and attach it to the other. Here we use the idea of small-to-large merging: we re-root the tree with fewer nodes. The total complexity is then $O(n\log n)$.

In summary, the total complexity of this algorithm is $O(n\log n+m\log n)$.

## Summary

DSU and the Kruskal reconstruction tree have a lot in common, and the DSU optimization (union by rank) is exactly an application of small-to-large merging. So by using DSU flexibly, you can easily handle many graph theory problems about connectivity.

**Parts of this page are translated from the blog post [Поиск мостов в режиме онлайн](http://e-maxx.ru/algo/bridge_searching_online) and its English translation [Finding Bridges Online](https://cp-algorithms.com/graph/bridge-searching-online.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
