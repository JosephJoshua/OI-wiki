author: DanJoshua, opsiff, yzy-1, yingqi-z20

## Definitions

Since we drop the notion of **source and sink**, we need to redefine the concept of a **cut**.

(In fact, the definition of a cut in the network flow section does not match Wikipedia's. It is just that the cuts people usually meet are in "minimum cut problems with a source and sink", so that meaning became the convention.)

### Cut

A set of edges whose removal makes a flow network graph disconnected (that is, splits it into two subgraphs) is called a cut of the graph.

That is: in an undirected graph $G = (V, E)$, let $C$ be a set of edges of $G$. If deleting all edges in $C$ from $G$ makes $G$ disconnected, then $C$ is called a cut of $G$.

### Minimum cut with a source and sink

Same as the definition in [Minimum cut](./flow/min-cut.md).

### Minimum cut without a source and sink

The cut whose edges have the smallest total weight. It is also called the global minimum cut.

Clearly, simply running network flow is too slow.

***

## Stoer–Wagner algorithm

### Introduction

The Stoer–Wagner algorithm was proposed by *Mechthild Stoer* and *Frank Wagner* in 1995. It solves the global minimum cut problem on **undirected graphs with positive weights** using **recursion**.

### Properties

The complexity of the algorithm is $O(|V||E| + |V|^{2}\log|V|)$, which can usually be treated as roughly $O(|V|^3)$.

It is based on the following basic fact: let $S, T$ be any two vertices of graph $G$. Then for any cut $C$ of $G$, either $S$ and $T$ are in the same connected component, or $C$ is an ${S-T}$ cut.

### Process

1.  Pick any two vertices $s, t$ of $G$, compute the minimum $S-T$ cut of $G$ with these two vertices as source and sink (called the *cut of phase*), and update the current answer.
2.  "Merge" vertices $s, t$. If $|V|$ of $G$ is greater than $1$, go back to step 1.
3.  Output the minimum over all *cuts of phase*.

Merging two vertices $s, t$: delete the edge $(s, t)$ between them; for every vertex $k$ in $G \setminus \{s, t\}$, delete $(t, k)$ and add its weight $d(t, k)$ to $d(s, k)$.

Explanation: if $s, t$ are in the same connected component, then for a vertex $k$ in $G \setminus \{s, t\}$, if $(k, s) \in C_{\min}$, then $(k, t) \in C_{\min}$ must also hold. Otherwise, since $s, t$ are connected and $k, t$ are connected, $s, k$ would be in the same connected component, and then $C = C_{\min} \setminus \{(t, k)\}$ would be better than $C_{\min}$. The converse holds too. So $s, t$ can be treated as a single vertex.

Step 1 handles the case where $s,t$ are not in the same connected component, and step 2 handles the remaining case. Each execution of step 2 decreases $|V|$ by $1$, so the algorithm ends after $|V| - 1$ rounds.

### Finding the minimum S-T cut

(Obviously not with network flow.)

Suppose that after some merges the current graph is $G'=(V', E')$, and we run step 1.

We build a set $A$, starting with $A = \varnothing$.

Each time, among all vertices of $V'$ with $i \notin A$, we add the one with the largest value of the weight function $w(A, i)$ to $A$, until $|A| = |V'|$.

The weight function is defined as:

$w(A, i) = \sum_{j \in A} d(i, j)$

(if $(i, j) \notin E'$, then $d(i, j) = 0$).

It is easy to see that the order in which vertices are added to $A$ is fixed. Let $\operatorname{ord}(i)$ be the $i$-th vertex added to $A$, and $t = \operatorname{ord}(|V'|)$. Let $\operatorname{pos}(v)$ be the size of $|A|$ right after $v$ is added, that is, the position at which $v$ is added.

Then for any vertex $s$, an $s$-$t$ cut is given by $w(t)$.

### Proof

A vertex $v$ is called active if and only if, when $v$ is added to $A$, the last vertex $u$ currently in $A$ (which was added before $v$) and $v$ are not in the same connected component of the graph $G'' = (V', E'/C)$.

![Stoer-Wagner1](./images/Stoer-Wagner1.png)

In the figure, the blue and yellow regions are two different connected components, and the numbers in square brackets are the order in which vertices are added to $A$. Gray vertices are active; white vertices are not.

Define $A_v = \{u \mid \operatorname{pos}(u) < \operatorname{pos}(v)\}$, that is, the vertices added to $A$ strictly before $v$. Let $E_v$ be the edge set of the subgraph of $E'$ induced by the vertex set $A_v \cup\{v\}$. (Note that it includes $v$.)

Define the induced cut $C_v$ as $C \cap E_v$, and $w(C_v) = \sum_{(i,j) \in C_v} d(i, j)$.

???+ note "Lemma 1"
    For every active vertex $v$, $w(A_v, v) \le w(C_v)$.
    
    Proof: by induction.
    
    For the first active vertex $v_0$, the definition gives $w(A_{v_0}, v_0) = w(C_{v_0})$.
    
    For two later active vertices $u, v$, suppose $\operatorname{pos}(v) < \operatorname{pos}(u)$. Then:
    
    $w(A_u, u) = w(A_v, u) + w(A_u - A_v, u)$
    
    We also know:
    
    $w(A_v, u) \le w(A_v, v)$ and $w(A_v, v) \le w(C_v)$. Combining them gives:
    
    $w(A_u, u) \le w(C_v) + w(A_u - A_v, u)$
    
    Since $w(A_u - A_v, u)$ contributes to $w(C_u)$ but not to $w(C_v)$, and all edges have positive weights, we get:
    
    $w(A_u,u) \le w(C_u)$
    
    This completes the induction.

Since $\operatorname{pos}(s) < \operatorname{pos}(t)$ and $s, t$ are not in the same connected component, $t$ is active, so $w(A_t, t) \le w(C_t) = w(C)$.

??? note "[P5632 \[Template\] Stoer–Wagner Algorithm](https://www.luogu.com.cn/problem/P5632)"
    ```cpp
    --8<-- "docs/graph/code/stoer-wagner/stoer-wagner_1.cpp"
    ```

***

### Complexity analysis and optimization

The complexity of the *contract* operation is $O(|E| + |V|\log|V|)$.

There are $O(|V|)$ *contract* operations in total, so the total complexity is $O(|E||V| + |V|^2\log|V|)$.

From experience with [shortest paths](./shortest-path.md), the bottleneck of the algorithm is finding the vertex with the largest weight.

Each *contract* needs to find the heap top $|V|$ times and increase weights $|E|$ times.

A Fibonacci heap can find the heap top in $O(\log|V|)$ and increase a weight in $O(1)$, so in theory the complexity can reach $O(|E| + |V|\log|V|)$. But Fibonacci heaps have a large constant factor and a lot of code, so they are of little practical value here.

(In actual tests, even with O2 enabled, it only passes if you get lucky with judge timing fluctuations.)
