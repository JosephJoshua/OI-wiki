author: Ir1d, partychicken, ouuan, Marcythm, TianyiQ

## Overview

Prerequisites: [random functions](../misc/random.md) and [basic probability](../math/probability/basic-conception.md)

This article gives a simple classification of randomization techniques in OI/ICPC and introduces each category. It also covers some methods that are rarely used in OI/ICPC but are fairly close to OI/ICPC in style; these are marked with `(*)`.

This classification does not represent a broad consensus and certainly cannot cover every possibility, so treat it only as a reference.

**Notation and conventions**:

-   $\mathrm{Pr}[A]$ denotes the probability that event $A$ happens.
-   $\mathrm{E}[X]$ denotes the expected value of random variable $X$.
-   The assignment symbol $:=$ introduces a new quantity. For example, $Y:=1926$ introduces a quantity $Y$ with value $1926$.

## Covering the target element with a random set

Among a huge solution space, there is one (or more) solution we want. We can try casting a net many times; as long as one cast catches the target solution, we succeed.

### Example: deciding 3-colorability

???+ note "Problem"
    Given a simple undirected graph with $n$ vertices and $m$ edges, color each vertex with one of three colors R, G, B so that every pair of neighbors gets different colors, or report that no solution exists.

For each vertex $v$, choose a color $C_v$ from $\{R,G,B\}$ independently and uniformly at random, and require that $v$ is **not** colored $C_v$. Clearly, the probability that an optimal solution satisfies all these restrictions is exactly $\big(\frac 23\big)^n$.

Under these restrictions, for a pair of neighbors $(u,v)$, the requirement "$u,v$ have different colors" is equivalent to the following implication:

-   For every color $X$ different from $C_u,C_v$, if $u$ is colored $X$, then $v$ is colored $\{R,G,B\}\setminus\{X,C_v\}$.

So for each $v$ we can set up a boolean variable $B_v$ whose value says which of the two remaining colors $v$ gets. With the 2-SAT model, this problem can be solved in $O(n+m)$.

With this approach, a single run succeeds with probability $\big(\frac 23\big)^n$. Repeat the algorithm $-\big(\frac 32\big)^n\log \epsilon$ times and output a solution as soon as one is found; this guarantees a success probability of $1-\epsilon$. (See "Analysis of probability upper bounds" later.)

***

**Recap**: in this problem, the "solution space" is the set $\{R,G,B\}^n$. Each time, we add random restrictions so that we search for the "target solution" (a valid coloring) in a smaller range.

### Example: [CodeChef SELEDGE](https://www.codechef.com/problems/SELEDGE)

???+ note "Problem summary"
    Given an undirected graph where both vertices and edges have non-negative weights, find an edge set $S$ of size $\leq K$ that maximizes the total weight of vertices touched by $S$ minus the total weight of the edges in $S$. Each vertex's weight is counted only once.

Observation: if three of the chosen edges form a path, removing the middle one is never worse; if some chosen edges form a cycle, removing any one of them is never worse.

Corollary: the edge set chosen by an optimal solution always forms several disjoint star graphs (that is, trees of diameter at most 2).

Corollary: the edge set chosen by an optimal solution always forms a bipartite graph.

We color each vertex black or white independently and uniformly at random, and require this coloring to be exactly the black-white coloring of the bipartite graph given by the optimal solution.

Let's compute the probability that the optimal solution meets this requirement:

-   Consider a star graph with $n$ vertices. It clearly has 2 valid colorings, so the probability that it is colored correctly is $\dfrac 2{2^n}=2^{1-n}$.
-   Suppose the stars in the optimal solution have $a_1,\cdots,a_l$ vertices. Then $(a_1-1)+\cdots+(a_l-1)\leq K$, where $K$ is the maximum number of edges we may choose.
-   So the probability that all stars are colored correctly is $2^{1-a_1}\cdots 2^{1-a_l}\geq 2^{-K}$.

Under this requirement, we build a min-cost flow model to compute the optimal answer:

-   Build a bipartite graph: white vertices on the left, connected to $S$; black vertices on the right, connected to $T$.
    -   For a white vertex $v$, add an edge from $S$ to it with capacity 1 and cost $-A_v$, and an edge with capacity $\infty$ and cost 0.
    -   For a black vertex $v$, add an edge from it to $T$ with capacity 1 and cost $-A_v$, and an edge with capacity $\infty$ and cost 0.
-   For each edge $(u,v,B)$ of the original graph where $u$ is white and $v$ is black, add an edge from $u$ to $v$ with capacity 1 and cost $B$.
-   Limit the flow in this graph to at most $K$; then the negative of the minimum cost is the answer.

Solving it with SPFA-based min-cost flow takes $O\big(K^2(n+m)\big)$. Proof:

-   First, SPFA clearly runs at most $K$ times.
-   Next, within one SPFA run, each vertex enters the queue at most $O(K)$ times. This is because:
    -   At any moment, at most $3K$ edges carry flow; otherwise more than $K$ edges of the original graph would have been chosen.
    -   In any augmenting path of length $L$, at least $\dfrac L2-2$ edges are reverse edges of edges carrying flow, because forward edges all go from the left side to the right side, and only these reverse edges go from right to left.
    -   Combining the two points above, every augmenting path has length at most $6K+4$.
-   In conclusion, the complexity is $O\big(K^2(n+m)\big)$.

As in the previous problem, we need to repeat the whole process $-2^K \log\epsilon$ times to get a success probability of $1-\epsilon$. The total complexity is $O\big(2^KK^2(n+m)\cdot -\log\epsilon\big)$.

## Hitting the target set with a random element

We need to find any one element of some set. To do so, we pick elements at random, hoping to hit the set.

### Example: [Gym 101550I](https://codeforces.com/gym/101550/attachments)

???+ note "Problem summary"
    The graph looks like this: two parallel paths, plus two parallel edges connecting them. Given several simple paths on this graph (each path is a phone call), choose as few edges as possible to place wiretaps on, so that every given path has at least one wiretap.

The whole graph can be split into one cycle plus four paths sticking out of it. For any one of these four paths (call it $C$), consider how to place wiretaps on it. A greedy algorithm easily gives a placement that satisfies:

-   It uses the fewest wiretaps while intercepting all calls entirely inside $C$.
-   Under the condition above, the shortest distance from the wiretaps on $C$ to the cycle is as small as possible.
    -   The purpose of this requirement is to intercept as many calls as possible that have exactly one endpoint inside $C$.

Next, consider the 4 edges where the paths meet the cycle. We enumerate by brute force whether each of these edges has a wiretap. Clearly, to intercept calls that cross between a path and the cycle, placing wiretaps on these 4 edges is always optimal. Now we can divide the call routes into the following kinds:

1.  Calls entirely on a path. These are definitely intercepted already, so we can ignore them.
2.  Calls crossing a path and the cycle that are already intercepted. These can be ignored.
3.  Calls crossing a path and the cycle that are not yet intercepted. We can cut off the part on the path (since the wiretap placement on the paths is already fixed) and keep only the part on the cycle.
4.  Calls entirely on the cycle.

So the problem has become a problem on a cycle.

Suppose the optimal solution places wiretaps on the edge set $S$ of the cycle. If we already know any one element $e$ of $S$, we can:

-   First break the cycle into a path at $e$.
-   Then run a greedy starting from $e$, repeatedly finding the next edge to place a wiretap on. Note that with suitable preprocessing, each greedy step takes $O(1)$.
-   This solves the problem in $O(|S|)$.

We pick a random edge $e'$ of the cycle, require $e'\in S$, run the process above, and repeat many times, taking the best result.

Analysis of the cost of a single run:

-   Observation: let $S'$ be the best solution among all solutions that include $e'$. Then $|S'|\leq |S|+1$.
-   So a single run costs $O(|S'|)=O(|S|)$.

Analysis of the success probability:

-   Clearly, a single run succeeds with probability $\dfrac {|S|}n$, where $n$ is the cycle length.
-   So we need to repeat it $-\dfrac n{|S|}\log\epsilon$ times to get a success probability of $1-\epsilon$.

In conclusion, the complexity of this algorithm is $O\big(|S|\cdot -\dfrac n{|S|}\log\epsilon\big)=O(-n\log\epsilon)$.

### Example: [CSES 1685 New Flight Routes](https://cses.fi/problemset/task/1685)

???+ note "Problem summary"
    Given a directed graph, add as few edges as possible to make it strongly connected. You must **output the edges added**.

First, contract the strongly connected components of the original graph. Our goal is clearly to make every sink reach every source.

It is not hard to prove that we only ever need to add edges from sinks to sources, because any other added edge corresponds to a sink-to-source edge that is at least as good.

Our core operation is: take a sink $t$ and a source $s$ (they need not be in the same weakly connected component), and add the edge $t\to s$ so that **neither $s$ nor $t$ is a sink or source anymore** (call this goal I). Ideally, each such operation removes one sink and one source, so we keep operating until only one sink or only one source is left, and that case is trivial. So we guess that the answer is the larger of the number of sources and the number of sinks.

It is easy to see that the operation achieves goal I if and only if $t$ has a predecessor other than $s$ and $s$ has a successor other than $t$. One can prove (the proof comes shortly) that in any DAG with at least two sources and at least two sinks, such an $(s,t)$ exists. But an existence result does not help us construct a solution, so more analysis is needed.

-   This necessary and sufficient condition alone does not directly give an algorithm. The main reason is that adding the edge $t\to s$ may affect whether other pairs $(s',t')$ are valid, which is hard to handle.

Note that we know very little about the relationships between sources and sinks (even quickly checking whether a given $s-t$ pair is reachable needs dfs + bitset preprocessing, which the time limit does not allow). This suggests we need some very general and powerful property.

Observation: at most $n+m-1$ pairs $(s,t)$ fail goal I, where $n$ is the number of sources and $m$ is the number of sinks.

-   Reason: if we view each such pair $(s,t)$ as an edge between $s$ and $t$, all these edges form several disjoint paths, so the number of edges is at most the number of vertices minus one.
-   The motivation for this observation: to apply an existence result in an algorithm, the first step is often to strengthen the qualitative result into a quantitative one.

Corollary: if we pick $(s,t)$ uniformly at random, the probability that it meets the requirement above is $\geq \dfrac {(n-1)(m-1)}{nm}$.

-   Note that this result is strictly stronger than the existence result given earlier.

Corollary: if we independently and uniformly at random pick $\dfrac {\min(n,m)}2$ pairs $(s,t)$ with no shared elements, one after another, and apply the operation to them **in order** (that is, add the edges $t\to s$), the probability that all these operations achieve goal I is $\geq \dfrac 14$.

-   Reason:

$$
\begin{aligned}
&\phantom{=\ }\dfrac {(n-1)(m-1)}{nm}\cdot\dfrac{(n-2)(m-2)}{(n-1)(m-1)}\cdots\dfrac{(n-k)(m-k)}{(n-k+1)(m-k+1)}\\
&=\dfrac{(n-k)(m-k)}{nm}\\
&\geq \dfrac 14
\end{aligned}
$$

After picking $k$ pairs $(s,t)$, checking whether they all achieve goal I is easy: just run SCC contraction again and check whether $n$ and $m$ both decreased by $k$. Note that if each round decreases them by $k=\dfrac{\min(n,m)}2$, then $\min(n,m)$ must become 1 within $O\big(\log(n+m)\big)$ rounds, which is the trivial case.

???+ note "Algorithm pseudocode"
    ```text
    while(n>1 and m>1):
        randomly choose k=min(n,m)/2 pairs (s,t)
        add edge t->s for all these pairs
        if new_n>n-k or new_m>m-k:
            roll_back()
    solve_trivial()
    ```

The complexity is $O\big((|V|+|E|) \log |V|\big)$.

***

**Recap**: we need to find any pair $(s,t)$ that achieves goal I, so we choose $(s,t)$ at random.

## Using randomization to get properties of random data

If a problem's data is randomly generated, we may be able to use properties of random data to solve it. And in some cases, even if the data is not random, we can use randomization to give it some properties of random data, which helps solve the problem.

### Example: randomized incremental algorithms

A randomly generated sequence of elements may have properties such as "the optimal solution of the prefix changes only a few times in expectation". Randomized incremental algorithms get these properties by randomly shuffling the input sequence.

See [randomized incremental algorithms](../geometry/random-incremental.md) for details.

### Example: a randomized solution to [TopCoder MagicMolecule](https://archive.topcoder.com/ProblemStatement/pm/11705)

???+ note "Problem summary"
    Given an undirected graph with $n$ vertices and vertex weights, among all cliques of size at least $\dfrac {2n}3$, find the one with the largest total vertex weight.
    
    $n\leq 50$

Meet-in-the-middle comes to mind easily. Split the vertex set evenly into two halves $V_L,V_R$ (each of size $\dfrac n2$), and compute an array $f_{L,k}$: the maximum total weight of a clique with $\geq k$ vertices inside the vertex set $L\subseteq V_L$. Then enumerate each clique $C_R$ of the right half, compute which vertices of the left half are adjacent to all vertices of $C_R$ (call this set $N_L$), and update the answer with $f_{N_L,\frac 23 n-|C_R|}+\textit{value}(C_R)$.

-   Note that each $f_{L,k}$ can be computed in $O(1)$. Specifically, take any element $d$ of $L$ and consider two cases:
    -   If $d$ is not in the clique of the optimal solution, take the value from $f_{L\setminus \{d\},k}$.
    -   If $d$ is in the clique of the optimal solution, take the value from $f_{L\cap N(d),k}+\textit{value}(d)$, where $N(d)$ is the set of neighbors of $d$.
    -   Don't forget to also update $f_{L,k}$ with $f_{L,k+1}$.

This solution is too slow. Let's optimize it:

-   Split the vertex set uniformly at random. Then, with a reasonable probability, the vertex set $C_{res}$ of the optimal solution is also split exactly in half (that is, $|C_{res}\cap V_L|=|C_{res}\cap V_R|$).
    -   Of course, $|C_{res}|$ may be odd. For simplicity we assume it is even here; the odd case does not change the solution in any essential way.
    -   Experiments show that about 20 random tries are enough to get at least one try with this property with high probability. In other words, if our algorithm relies on the property "$C_{res}$ is split in half", repeating it 20 times and taking the best still gives the correct answer with high probability.
-   With this property, we can directly require that the left clique $L$ and the right clique $C_R$ both have size $\geq \dfrac n3$. This improves the complexity in two ways:
    -   $f$ no longer needs the dimension that records the size.
    -   Since we only consider cliques of size $\geq \dfrac n3$, the number of left cliques $L$ and right cliques $C_R$ to consider drops sharply, to about $1.8\cdot 10^6$.
-   The bottleneck now becomes computing the total weight of a subset of one side, since that needs $O\big(2^{|V_L|}+2^{|V_R|}\big)$ preprocessing.
    -   Solution: split $V_L,V_R$ in half again internally; to query the total weight of a subset, split the subset into its left and right halves, query each, and add the results.
-   This is enough to pass the problem.

***

**Recap**: a random set has the property that "the sizes of the two halves of a split are not too different", and we obtained this property by splitting at random.

## Randomization for hashing

### Example: [UOJ #207 Gongjia Daye Visits Changsha](https://uoj.ac/problem/207)

???+ note "Problem summary"
    Maintain a dynamically changing tree and a dynamically changing set of vertex pairs. You need to support:
    
    -   Deleting and adding edges. The result is guaranteed to still be a tree.
    -   Adding/removing a vertex pair.
    -   Given an edge $e$, determine whether, for every vertex pair $(s,t)$ in the set, $e$ lies on the simple path between $s$ and $t$.

For each edge $e$ of the graph, define the set $S_e$ as the set of key paths (the $(a,b)$ pairs in the problem) passing through that edge. Consider maintaining a hash of $S_e$ dynamically for each edge; then we can easily check whether $S_e$ equals the full set (that is, whether $e$ is "on every path").

The hashing works like this: assign each $(a,b)$ a random non-negative integer $H_{(a,b)}$ below $2^{64}$; the hash of a set is the XOR of the $H$ values of its elements.

Then the hash of any fixed set is uniformly distributed on $R:=\left\{0,1,\cdots,2^{64}-1\right\}$ (in other words, the hash takes values in $R$, each with equal probability). This is because:

1.  A single $H_{(a,b)}$ is clearly uniformly distributed.
2.  The XOR of two independent random variables uniformly distributed on $R$ is also uniformly distributed on $R$. The proof is left to the reader.

So the correctness of this algorithm is guaranteed with high probability.

To maintain this hash, just use an LCT.

### Example: [CodeChef PANIC](https://www.codechef.com/problems/PANIC) and its error rate analysis

Rough solution of this problem:

1.  One can prove[^ref1] that $S(N)$ satisfies a linear recurrence of order $O(K)$ in $N$.
2.  Find this recurrence with the BM (Berlekamp–Massey) algorithm.
3.  Using the recurrence, compute $S(N)$ with the Cayley–Hamilton theorem.

Here we focus only on the second part, that is, how to find a recurrence for a sequence of matrices. So we only need to consider the following problem:

???+ note "Problem"
    Given a sequence of matrices that satisfies a homogeneous linear recurrence modulo $P:=998244353$ (scalar multiplication and addition in the recurrence are matrix scalar multiplication and addition), find the shortest recurrence.

If a sequence of matrices satisfies a recurrence $F$, then each entry also satisfies $F$. However, if we find the shortest recurrence $F'$ for one entry, $F'$ may be shorter than $F$, which causes problems.

Solution: give each entry $(i,j)$ of the matrix a random weight $x_{i,j}<P$. For each matrix in the sequence, compute the weighted sum of all its entries modulo $P$, put these numbers together into a sequence, and finally run the BM algorithm on that sequence.

Error rate analysis:

-   Suppose the method above finds a recurrence $F'$ of order $l$ that differs from $F$ (and is clearly not longer than $F$).
-   Since the matrix sequence does not satisfy $F'$, there must be some position $(i,j)$ of the matrix such that the sequence $S_{i,j}$ at that position does not satisfy $F'$ at some $N$. That is:

$$
S(N)_{i,j}-F'_1S(N-1)_{i,j}-\cdots-F'_lS(N-l)_{i,j}\not\equiv 0\pmod {P}
$$

-   If $(i,j)$ is the only position that does not satisfy it, then it must hold that:

$$
T_{i,j}:=\Big(x_{i,j}\cdot\big(S(N)_{i,j}-F'_1S(N-1)_{i,j}-\cdots-F'_lS(N-l)_{i,j}\big)\bmod P\Big)=0
$$

-   Clearly this holds only when $x_{i,j}=0$, which has probability $P^{-1}$.
-   What if there are several positions that do not satisfy it?
    -   For each such position $(i,j)$, it is easy to show that $T_{i,j}$ is uniformly distributed on $R:=\{0,1,\cdots,P-1\}$.
    -   The sum, modulo $P$, of several independent random variables uniformly distributed on $R$ is still uniformly distributed on $R$. The proof is left to the reader.
    -   So the error rate in this case is also $P^{-1}$.

### Example: [UOJ #552 Isomorphism Checking Duck](https://uoj.ac/problem/552) and its error rate analysis

???+ note "Problem summary"
    Given two directed graphs $G_0,G_1$ whose edge labels are lowercase letters, for each graph compute "the multiset of strings corresponding to all paths" (possibly infinite), and decide whether the two multisets are equal. If they are not, output a shortest string whose number of occurrences differs between the two multisets.

Let $f_{K,i,j}$ be the hash of the multiset of strings corresponding to all paths of length $j$ starting at vertex $i$ in graph $G_K$. Consider the states in increasing order of $j$; for a transition, enumerate the outgoing edges of $i$ and fix that edge as the first edge of the path.

To check whether a bad string of length $=L$ exists, just "combine" $\{f_{0,*,L}\}$ and $\{f_{1,*,L}\}$ separately and compare them (the wildcard `*` here stands for every vertex; for example, $\{f_{0,*,L}\}$ is the set of all $f_{0,i,L}$, where $i$ ranges over all vertices). The official editorial[^ref2] proves that the shortest bad string (if any) has length at most $n_1+n_2$, so the complexity of this solution is sound.

Next, consider the concrete hashing method. Note that the usual hashing method, which maps a string $a_1a_2\cdots a_k$ to $\big(a_1+Pa_2+P^2a_3+\cdots+P^{k-1}a_k\big)\bmod Q$ and defines the hash of a multiset as the sum of its elements' hashes modulo $Q$, does not work here. A counterexample: the sets `{"ab","cd"}` and `{"cb","ad"}` have the same hash, no matter what $P,Q$ are.

The problem with this method is that a string's hash is a sum, so its terms can be pulled apart and recombined. To avoid this, we make the hash a product instead. Also, commutativity of multiplication would make different positions indistinguishable, so to avoid that we give different positions different weights.

For each pair $(c,j)$ (where $c$ is a character and $j$ is an integer giving the position of $c$ in some string), we generate a random number $x_{c,j}$ in advance. Then we map a string $a_1a_2\cdots a_k$ to $x_{a_1,1}x_{a_2,2}\cdots x_{a_k,k}\bmod Q$ (where $Q$ is a **randomly chosen** prime), and define the hash of a multiset as the sum of its elements' hashes modulo $Q$. Next, let's analyze its error rate.

???+ note "(*)Schwartz–Zippel lemma"
    Let $f\in F[z_1,\cdots,z_k]$ be a nonzero polynomial of degree $d$ in $k$ variables over a field $F$, and let $S$ be a finite subset of $F$. Then at most $d\cdot |S|^{k-1}$ tuples $(z_1,\cdots,z_k)\in S^k$ satisfy $f(z_1,\cdots,z_k)=0$.
    
    ??? note "If you don't know what a field is"
        You only need to remember that these two things are fields:
        
        1.  The residues modulo a prime, with the usual operations on them.
        2.  The set of real numbers, with the usual operations on them.
    
    Corollary: if $z_1,\cdots,z_k$ are each chosen independently and uniformly at random from $S$, then $\mathrm{Pr}\big[f(z_1,\cdots,z_k)=0\big]\leq \dfrac d{|S|}$.

Let $F$ be the field of residues modulo $Q$. Then for an $L\leq n_1+n_2$, $\sum\limits_i f_{0,i,L}$ and $\sum\limits_i f_{1,i,L}$ each correspond to a multivariate polynomial of degree $L$ over $F$ in the variables $\{x_{*,*}\}$. Call these two polynomials $P_0,P_1$.

If two different multisets of strings have the same hash, there are two possibilities:

1.  $P_0\equiv P_1\pmod {Q}$, that is, every coefficient of $P_0,P_1$ is equal modulo $Q$.
2.  $P_0\not\equiv P_1\pmod {Q}, P_0(x_{*,*})\equiv P_1(x_{*,*})\pmod {Q}$, that is, $P_0,P_1$ are not identical, but the values $\{x_{*,*}\}$ we chose happen to make them evaluate to the same value.

Probability of the first case:

-   Observation: for any $A\neq B; A,B\leq N$ and a randomly chosen prime $Q\leq Q_{\max}$, we always have:

$$
\mathrm{Pr}\big[A\equiv B\pmod {Q}\big]=O\Big(\dfrac{\log N \log Q_{max}}{Q_{max}}\Big)
$$

-   This is because any $Q$ that makes $A\equiv B$ hold must satisfy $Q\big|(A-B)$, and there are $\omega(A-B)\leq \log_2 N$ such $Q$; by the prime number theorem, there are $\Theta\Big(\dfrac {Q_{\max}}{\log Q_{\max}}\Big)$ distinct primes up to $Q_{\max}$. Dividing one by the other gives the formula above.
-   In the observation above, take $A,B$ (with $A\neq B$) to be the coefficients of some particular term in $P_0,P_1$ (which equal the numbers of occurrences of the corresponding string in $G_0,G_1$). It is easy to see that $A,B\leq (m_1+m_2)^{L}$, so:

$$
\mathrm{Pr}\big[A\equiv B\pmod {Q}\big]=O\Big(\dfrac{L\log (m_1+m_2) \log Q_{max}}{Q_{max}}\Big)
$$

-   So taking $Q_{\max}\approx 10^{12}$ is more than enough. If the machine cannot handle integer arithmetic that large, use double hashing instead.

Probability of the second case:

-   In the Schwartz–Zippel lemma:
    -   Take the field $F$ to be the field of residues modulo $Q$
    -   Take $f(x_{*,*})=P_0(x_{*,*})-P_1(x_{*,*})$, a nonzero polynomial of degree $L$
    -   Take $S=F$
-   We get: the probability is $\leq \dfrac LQ$.

Note that we need correctness for every $L$, so to be fully rigorous we would also need the union bound (see below).

In practice we don't need to choose the modulus at random, because, for example, using your own birthday as the modulus is effectively already random.

### Example: (\*) number of distinct elements in a submatrix

???+ note "Problem"
    Given an $n\times m$ matrix, answer $q$ queries asking for the number of distinct elements in a contiguous submatrix. An online algorithm is required.
    
    A relative error of $\epsilon$ and an error rate of $\delta$ are allowed. In other words, for at least $(1-\delta)q$ of the queries, you must give an answer whose relative error from the correct answer is at most $\epsilon$.
    
    $n\cdot m\leq 2\cdot10^5;q\leq 10^6;\epsilon=0.5,\delta=0.2$

Lemma: let $X_{1\cdots k}$ be independent random variables, each uniformly distributed on $[0,1]$. Then $\mathrm{E}\big[\min\limits_i X_i\big]=\dfrac 1{k+1}$.

-   Proof: consider a unit circle with $k+1$ points whose **relative positions** are uniformly random, at positions $0,X_1,X_2,\cdots,X_k$. Then $\min\limits_i X_i$ equals the length of one particular gap among the $k+1$ gaps. Since the gaps are "symmetric", any particular gap has expected length $\dfrac 1{k+1}$.

We take $k$ to be the number of distinct elements, and use the lemma above to work back from $\min\limits_i X_i$ to $k$.

Consider a hash function that maps each element of the matrix uniformly and independently at random to a real number in $[0,1]$, with equal elements mapped to equal reals. Then the reals corresponding to all elements of a submatrix, after removing duplicates, are exactly an instance of the set $\{X_1,\cdots,X_k\}$ above, where $k$ is the number of distinct elements in the submatrix.

So we get an algorithm:

1.  Assign each matrix element a hash value in $[0,1]$. To ensure randomness, the hash function can be implemented directly with a `map` and a random number generator: whenever we see a new value that has not appeared before, give it a random hash value.
2.  To answer a query, find the minimum hash value $M$ in the submatrix and output $\dfrac 1M-1$.

However, this algorithm is not satisfactory. The expected value of its output is $\mathrm{E}\Big[\dfrac 1{\min\limits_i X_i}-1\Big]$, but this is not actually equal to $\dfrac 1{\mathrm{E}\big[\min\limits_i X_i\big]}-1=k$; instead (one can prove) it equals $\infty$.

That is, we cannot directly put a single sample of $\min\limits_i X_i$ in the denominator. We must first estimate its expected value, then put that expected value in the denominator.

How do we estimate the expected value? Average many random trials.

We run the process above with $C$ different hash functions. To answer a query, compute $C$ different values of $M$, take their average $\overline M$, and output $\big(\overline M\big)^{-1}-1$.

Experiments show that $C\approx 80$ is enough to meet the requirements. A rigorous proof is very tedious and is omitted here.

Finally, how do we find the minimum of a submatrix? Use a 2D sparse table: $O(nm\log n\log m)$ preprocessing and $O(1)$ per query.

## Other uses of randomization in algorithms

Other uses of randomization include:

-   Preventing test makers from breaking your solution with targeted data. For example, randomly shuffling the order of neighbors during a search.
-   Making the "operations" performed during an algorithm (in some sense) uniform. For example, the [simulated annealing](../misc/simulated-annealing.md) algorithm.

In these settings, randomization is often (but not always) tied to heuristic hacks and partial-credit tricks.

### Example: [TJOI2015 — Linear Algebra](https://loj.ac/problem/2100)

The standard solution of this problem is network flow, but here we use the following heuristic hack:

-   Each time, pick a random position, flip it, compute the value, and update the answer.

??? note "Code"
    ```cpp
    #include <algorithm>
    #include <cstdlib>
    #include <iostream>
    
    int n;
    
    int a[510], b[510], c[510][510], d[510];
    int p[510], q[510];
    
    int maxans = 0;
    
    void check() {
      memset(d, 0, sizeof d);
      int nowans = 0;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) d[i] += a[j] * c[i][j];
      for (int i = 1; i <= n; i++) nowans += (d[i] - b[i]) * a[i];
      maxans = std::max(maxans, nowans);
    }
    
    int main() {
      srand(19260817);
      std::cin >> n;
      for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++) std::cin >> c[i][j];
      for (int i = 1; i <= n; i++) std::cin >> b[i];
      for (int i = 1; i <= n; i++) a[i] = 1;
      check();
      for (int T = 1000; T; T--) {
        int tmp = rand() % n + 1;
        a[tmp] ^= 1;
        check();
      }
      std::cout << maxans << '\n';
    }
    ```

### Example: (\*) randomized heap[^ref3]

The most common mergeable heap is probably the leftist heap, which keeps merging efficient by maintaining tree heights so the tree leans left. But maintaining heights is a bit annoying, and we would like to avoid it.

So we can use a randomized heap: instead of swapping children based on tree height, swap them at random.

???+ note "Code"
    ```cpp
    struct Node {
      int child[2];
      long long val;
    } nd[100010];
    
    int root[100010];
    
    int merge(int u, int v) {
      if (!(u && v)) return u | v;
      int x = rand() & 1, p = nd[u].val > nd[v].val ? u : v;
      nd[p].child[x] = merge(nd[p].child[x], u + v - p);
      return p;
    }
    
    void pop(int &now) { now = merge(nd[now].child[0], nd[now].child[1]); }
    ```

The randomized heap places no hard or soft requirement on the shape of the heap, and the expected complexity of merging holds for any two heaps (passed as arguments to `merge`). We prove this below.

???+ note "Proof of the expected complexity"
    We will prove that for any heap $A$, if we start at the root and repeatedly go left or right at random (until we can go no further), the expected path length (the number of nodes on the path) $h(A)\leq\log_2 (|A|+1)$.
    
    -   Note that in the process above, the expected cost of merging heaps $A,B$ is $O\big(h(A)+h(B)\big)$, so this result guarantees the expected complexity of the randomized heap.
    
    We use mathematical induction. The base case is when $A$ is empty, which is obvious. Now assume $A$ is non-empty.
    
    Let the two subtrees of $A$ be $L,R$. Then:
    
    $$
    \begin{align} h(A)
    &=1+\frac{h(L)+h(R)}2
    \\&\leq1+\frac{\log_2(|L|+1)+\log_2(|R|+1)}2
    \\&=\log_2{2\sqrt{(|L|+1)(|R|+1)}}
    \\&\leq\log_2{\frac{2\big((|L|+1)+(|R|+1)\big)}2}
    \\&=\log_2{(|A|+1)} \end{align}
    $$
    
    This completes the proof.

## Proof techniques related to randomness

Below are a few fairly useful techniques.

Of course, these few items cannot be everything; if you know a technique that is not listed, you are welcome to add it.

### Analysis of probability upper bounds

See the [concentration inequalities](../math/probability/concentration-inequality.md) page for details.

Besides the inequalities mentioned on that page, the following result is also often used in derivations:

**Using the constant e**: $\Big(1-\dfrac{1}{n}\Big)^n\leq \dfrac{1}{\mathrm{e}},\forall n\geq1$

-   The left side is increasing in $n\geq 1$ and its limit at $+\infty$ is $\dfrac{1}{\mathrm{e}}$, which gives this result.
-   It tells us that if $n$ independent events each happen with probability $1-\dfrac 1n$, the probability that all of them happen is at most $\dfrac{1}{\mathrm{e}}$.

### The idea of "coupling"

The idea of "coupling" is often used to handle more than one random object at the same time, or a random object together with a deterministic one.

#### Warm-up: connectivity of random graphs

???+ note "Problem"
    For $n \in \mathbf{N}^*; p,q\in [0,1]$ with $q\leq p$, prove that the expected number of connected components of the random graph $G_1(n,p)$ is at most the expected number of connected components of the random graph $G_2(n,q)$. Here $G(n,\alpha)$ denotes a simple undirected graph $G$ with $n$ vertices, in which each of the $\dfrac {n(n-1)}2$ possible edges appears with probability $\alpha$, independently.

This result looks completely natural, but a rigorous proof is not so easy.

???+ note "Proof idea"
    Imagine that each of the two graphs uses a 0/1 random number generator to decide whether each edge exists. $G_1$'s generator $T_1$ outputs 1 with probability $p$ each time, and $G_2$'s generator $T_2$ outputs 1 with probability $q$ each time. To build a graph, we just run the corresponding generator $\dfrac {n(n-1)}2$ times.
    
    Now we merge the two generators into one. Consider a random number generator $T$ that outputs 0 with probability $q$, 1 with probability $p-q$, and 2 with probability $1-p$ each time. If we run this $T$ $\dfrac {n(n-1)}2$ times, we can build $G_1$ and $G_2$ at the same time. Specifically, if the output is 0, we consider the current edge to be absent from both $G_1$ and $G_2$; if the output is 1, the current edge is in $G_1$ only; if the output is 2, the current edge is in both $G_1$ and $G_2$.
    
    It is easy to check that $G_1$ and $G_2$ generated this way match their definitions, and that in every instance, the edge set of $G_2$ is a subset of the edge set of $G_1$. So in every instance, $G_2$ has at least as many connected components as $G_1$, and naturally the expected values satisfy the same inequality.

The idea used in this proof is called "coupling", and it can be understood literally. In this example, it shows up as merging two originally independent random processes into one.

#### Application: [NERC 2019 Problem G: Game Relics](https://codeforces.com/contest/1267/problem/G)

???+ note "Problem summary"
    There are several items, each with a price $c_i$. You want to get all the items. To do so, you can perform two kinds of operations in any order:
    
    1.  Choose an item $i$ you don't own and buy it for $c_i$ dollars.
    2.  Pay $x$ dollars to draw one item uniformly at random from all items (including ones you already own). If you don't own it yet, you get it; otherwise you get nothing, but $\dfrac x2$ dollars are refunded. $x$ is a constant given in the input.
    
    Find the expected cost under the optimal strategy.

Observation: if you choose to draw, you will keep drawing until you get a new item.

-   Reason: if a draw does not give a new item, the new situation is exactly the same as before the draw. So if the best action in the old situation was "draw once", the best action in the new situation must also be "draw again".

We can compute $f_k$: if you already own $k$ distinct items, how much money you expect to spend to draw a new item. By the observation just made, we can treat $f_k$ as a fixed cost, turning the operation into "pay $f_k$ dollars to get a random new item".

???+ note "Computing the expected cost"
    Clearly $f_k=\dfrac x2 \cdot (R-1)+x$, where $R$ is the expected number of draws needed to get a new item.
    
    Lemma: if a coin lands heads with probability $p$, the expected number of tosses until the first heads is $\dfrac 1p$.
    
    -   Intuition: $\dfrac 1p \cdot p = 1$, so tossing this many times gives 1 heads in expectation, which seems about right.
    -   This intuition can be made rigorous with the [law of large numbers](https://en.wikipedia.org/wiki/Law_of_large_numbers), by considering $n\to \infty$ runs of the experiment "toss the coin until heads". Details omitted.
    -   Another valid proof is to plug in the definition of expected value and compute directly. Details omitted.
    
    Clearly the probability that one draw gives a new item is $\dfrac {n-k}n$, so $R=\dfrac n{n-k}$.

Conclusion: the optimal strategy is always to draw some number of times first, then buy all items not yet drawn.

This conclusion matches intuition, because $f_k$ increases with $k$, so drawing early does seem a bit better than drawing late.

???+ note "Proof"
    First, consider proving a special case. We will prove that:
    
    -   Random process $A$: first buy item $x$, then keep drawing until you have all items
    -   ...is never better than...
    -   Random process $B$: keep drawing until you have all items other than $x$, then buy $x$ if you still don't have it
    
    Let random processes $A$ and $B$ use the same random number generator. That is, the first draw of $A$ and the first draw of $B$ give the same item, and likewise for the second, third, and so on.
    
    Clearly, $A$ and $B$ then make the same number of draws. For an item $y\neq x$ drawn by $A$, observe that:
    
    -   The number of items already owned when $A$ draws $y$ is at least the number already owned when $B$ draws $y$.
    
    So each draw of $B$ costs no more than the corresponding draw of $A$, and the total drawing cost of $B$ is no more than that of $A$.
    
    Clearly the buying cost of $B$ is also no more than that of $A$. Putting it together, $B$ is never worse than $A$.
    
    Then mathematical induction extends this result to the general case. Specifically, each time we find the last purchase in the current strategy, and by the result above, moving that purchase to the very end is never worse. Details omitted.

Based on this conclusion, we transform the problem equivalently once more: replace the operation "choose an item and pay its price to buy it" with "choose a random item you don't own and pay its price to buy it". The reason this is equivalent is that since buying is only used to finish up at the end, it doesn't matter which item is chosen.

Now we see that "drawing" and "buying" have essentially become the same operation; they differ only in the price paid. Whether we buy or draw has no effect on the order in which items are obtained, and every order of obtaining items is equally likely.

Observation: at any moment, we should buy if and only if the cost of the next draw (determined by how many items we already have) is greater than the average price of the remaining items (if equal, either is fine).

-   One can prove that over time, the cost of drawing grows at least as fast as the average price of the remaining items. This shows there is only one "tipping point" from drawing to buying, which further confirms the earlier conclusion.

Finally, we enumerate all possible situations (that is, the set of items already owned), compute the probability of each situation (the number of orderings of the owned items divided by the total number of orderings), multiply by the cost of the optimal decision in that situation (determined by the number of owned items and the total price of the remaining items), and add them up. This process can be optimized with a knapsack-style DP, which is enough to pass the problem.

***

**Recap**: we can see that the coupling technique is used twice in this problem. The first time is in the proof, where two random processes share the same source of randomness. The second time is turning buying into random buying (that is, introducing a source of randomness), so that the two operations, buying and drawing, are essentially "coupled" into the same operation (that is, drawing and buying share one source of randomness).

## References

[^ref1]: [PANIC - Editorial](https://discuss.codechef.com/t/panic-editorial/80145)

[^ref2]: [UOJ NOI Round #4 Day2 Editorial](https://peehs-moorhsum.blog.uoj.ac/blog/6375)

[^ref3]: [Anna Gambin and Adam Malinowski, Randomized Meldable Priority Queues](https://www.researchgate.net/publication/2801527_Randomized_Meldable_Priority_Queues)
