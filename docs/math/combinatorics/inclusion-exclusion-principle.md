## Introduction

???+ note "Warm-up problem"
    Suppose $10$ students in a class like math, $15$ like Chinese, and $21$ like programming. How many students in the class like at least one of these subjects?

Is it $10+15+21=46$? No. Some students may like both math and Chinese, or both Chinese and programming, or even all three.

For convenience, let $A,B,C$ be the sets of students who like Chinese, math and programming. Then the number of students we want is $|A\cup B\cup C|$. As noted above, if we simply add up the sizes $|A|,|B|,|C|$ of the three sets, some elements are counted more than once. So we must subtract $|A\cap B|,|B\cap C|,|C\cap A|$. But then a small part is subtracted too many times and must be added back, namely $|A\cap B\cap C|$. That is,

$$
|A\cup B\cup C|=|A|+|B|+|C|-|A\cap B|-|B\cap C|-|C\cap A|+|A\cap B\cap C|
$$

![Inclusion–exclusion principle - Venn diagram example](./images/incexcp.png)

Generalizing this problem to the general case gives the well-known inclusion–exclusion principle.

## Definition

Suppose the elements of U can have n different properties. Call the $i$-th property $P_i$, and let $S_i$ be the set of elements that have property $P_i$. Then

$$
\begin{aligned}
\left|\bigcup_{i=1}^{n}S_i\right|=&\sum_{i}|S_i|-\sum_{i<j}|S_i\cap S_j|+\sum_{i<j<k}|S_i\cap S_j\cap S_k|-\cdots\\
&+(-1)^{m-1}\sum_{a_i<a_{i+1} }\left|\bigcap_{i=1}^{m}S_{a_i}\right|+\cdots+(-1)^{n-1}|S_1\cap\cdots\cap S_n|
\end{aligned}
$$

That is,

$$
\left|\bigcup_{i=1}^{n}S_i\right|=\sum_{m=1}^n(-1)^{m-1}\sum_{a_i<a_{i+1} }\left|\bigcap_{i=1}^mS_{a_i}\right|
$$

### Proof

For each element, we use the binomial theorem to count how many times it is counted. Take an element x and suppose it belongs to the sets $T_1,T_2,\cdots,T_m$. Then the number of times it is counted is

$$
\begin{aligned}
Cnt=&|\{T_i\}|-|\{T_i\cap T_j|i<j\}|+\cdots+(-1)^{k-1}\left|\left\{\bigcap_{i=1}^{k}T_{a_i}|a_i<a_{i+1}\right\}\right|\\
&+\cdots+(-1)^{m-1}|\{T_1\cap\cdots\cap T_m\}|\\
=&\dbinom{m}{1}-\dbinom{m}{2}+\cdots+(-1)^{m-1}\dbinom{m}{m}\\
=&\dbinom{m}{0}-\sum_{i=0}^m(-1)^i\dbinom{m}{i}\\
=&1-(1-1)^m=1
\end{aligned}
$$

So every element is counted exactly once, and putting them together gives the union. This completes the proof.

### Complement

With universe U, a **union of sets** can be computed with inclusion–exclusion, while an intersection of sets can be found by subtracting the **union of the complements** from the universe:

$$
\left|\bigcap_{i=1}^{n}S_i\right|=|U|-\left|\bigcup_{i=1}^n\overline{S_i}\right|
$$

Then apply inclusion–exclusion to the right-hand side.

Readers who have seen inclusion–exclusion before probably know all this already, and care more about how it is applied.

So next we give 3 example problems of different levels to show how inclusion–exclusion is used.

## Counting non-negative integer solutions of an indeterminate equation

???+ note "Counting non-negative integer solutions of an indeterminate equation"
    Given the indeterminate equation $\sum_{i=1}^nx_i=m$ and $n$ constraints $x_i\leq b_i$, where $m,b_i \in \mathbb{N}$, find the number of non-negative integer solutions of the equation.

### Without constraints

Without the constraints $x_i\leq b_i$, the number of non-negative integer solutions of $\sum_{i=1}^nx_i=m$ is $\dbinom{m+n-1}{n-1}$.

Proof sketch: stars and bars.

This is the same as putting $m$ balls into $n$ boxes, where a box may be empty. This cannot be solved directly with a binomial coefficient.

So we add $n-1$ more balls. Now the problem becomes choosing $n-1$ balls from a row of $m+n-1$ balls. These $n-1$ balls cut the row into $n$ parts, which correspond one-to-one to the $n$ boxes. The number of ways to choose $n-1$ balls out of $m+n-1$ is $\dbinom{m+n-1}{n-1}$.

### Inclusion–exclusion model

Next we try to describe the problem in terms of the inclusion–exclusion model:

1.  Universe U: the non-negative integer solutions of $\sum_{i=1}^nx_i=m$
2.  Elements: the variables $x_i$.
3.  Properties: the property of $x_i$ is the condition it must satisfy, i.e. $x_i\leq b_i$

Goal: the size of the set where every variable has its property, i.e. $|\bigcap_{i=1}^nS_i|$.

We can compute this with $\left|\bigcap_{i=1}^{n}S_i\right|=|U|-\left|\bigcup_{i=1}^n\overline{S_i}\right|$. $|U|$ is a binomial coefficient, and the second part is naturally expanded with inclusion–exclusion.

The problem now becomes finding the size of an intersection of some sets $\overline{S_{a_i}}$. $\overline{S_{a_i} }$ is the set of solutions with $x_{a_i}\geq b_{a_i}+1$, and the intersection means all these conditions hold at once. So in the equation corresponding to this intersection, some variables have a **lower bound**, while the others have no constraint.

Can we get rid of these lower bounds? We are counting non-negative integer solutions, and some variables have a lower bound greater than $0$. If we simply **subtract the lower bound**, these variables get lower bound $0$, i.e. no lower bound at all. So for

$$
\left|\bigcap_{a_i<a_{i+1} }^{1\leq i\leq k}S_{a_i}\right|
$$

the corresponding equation is

$$
\sum_{i=1}^nx_i=m-\sum_{i=1}^k(b_{a_i}+1)
$$

So this can also be computed with a binomial coefficient. The array $a$ of length $k$ is just an enumeration of subsets.

## HAOI2008 Coin Shopping

???+ note "HAOI2008 Coin Shopping"
    There are 4 kinds of coins, and the $i$-th kind has value $C_i$. There are $n$ queries. Each query gives the number $D_i$ of coins of each kind and a price $S$. Find the number of ways to pay.
    
    $n\leq 10^3,S\leq 10^5$.

Using a knapsack directly takes $O(4nS)$, which is too slow. The most obvious feature of this problem is that there are only four kinds of coins. As a model, we are asked for the number of non-negative integer solutions of $\sum_{i=1}^4C_ix_i=S,x_i\leq D_i$.

We use the same inclusion–exclusion approach, where the property of $x_i$ is $x_i\leq D_i$. Applying the inclusion–exclusion formula, in the end we need to solve

$$
\sum_{i=1}^4C_ix_i=S-\sum_{i=1}^kC_{a_i}(D_{a_i}+1)
$$

which is an unbounded knapsack problem. This can be precomputed. Including the queries, the total complexity is $O(4S+2^4n)$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/inclusion-exclusion-principle/inclusion-exclusion-principle_1.cpp"
    ```

## Coloring subgraphs of a complete graph

The previous three problems all use inclusion–exclusion in the forward direction. This problem needs inclusion–exclusion in reverse.

???+ note "Coloring subgraphs of a complete graph"
    A and B like coloring graphs (not necessarily connected), and their rule is that adjacent vertices must have the same color. Today A and B play a game on the **complete graph** $G=(V,E)$ with $n$ vertices. They define an evaluation function $F(S)$, where S is an edge set, $S\subseteq E$. $F(S)$ is the total number of ways to color the graph $G'=(V,S)$ with $m$ colors. Their other rule is that if $|S|$ is odd, A's score increases by $F(S)$; otherwise B's score increases by $F(S)$. Find the difference between A's and B's scores.

### Mathematical form

It is not obvious which algorithm this problem calls for, so for a tricky problem like this we first write it in mathematical form. The score difference is a signed sum over odd and even sizes, so we can use a power of -1 as the coefficient. We want

$$
Ans=\sum_{S\subseteq E}(-1)^{|S|-1}F(S)
$$

### Inclusion–exclusion model

We treat "adjacent vertices have the same color" as a property. For now, ignore the coloring rule and just color the graph with m colors. We treat a graph $G'=(V,S)$ as an **element**. The **property** $x_i=x_j$ means that vertices i and j have the same color (note that we do not require an edge between i and j).

The **set** for the property $x_i=x_j$ is denoted $Q_{i,j}$. It is the set of all colorings of $G'$ that satisfy the property. Its size is the number of colorings satisfying the property, and its elements are all the colored versions of $G'$ that satisfy the property.

Back to the problem: "adjacent vertices must have the same color" can be seen as the intersection of several sets $Q$. So we can write

$$
F(S)=\left|\bigcap_{(i,j)\in S}Q_{i,j}\right|
$$

The right-hand side is the number of colorings in which $x_i=x_j$ for every edge $(i,j)$ in S, which is exactly $F(S)$.

Doesn't this look a lot like inclusion–exclusion now? The inclusion–exclusion principle itself does not work with pairs, so we map **all** edges $(i,j)$ to $T=\frac{n(n+1)}{2}$ integers. Suppose $(i,j)$ is mapped to $k,1\leq k\leq T$, and $Q_{i,j}$ is mapped to $Q_k$. Then the property $x_i=x_j$ is defined as $P_k$.

Also, S can be written as a set of such k, i.e. $S\iff K=\{k_1,k_2,\cdots,k_m\}$. (In other words, we set up an equivalence between edge sets and sets of numbers.)

And E corresponds to the set $M=\left\{1,2,\cdots,\frac{n(n+1)}{2}\right\}$. So

$$
F(S)\iff F(\{ {k_i}\})=\left|\bigcap_{k_i}Q_{k_i}\right|
$$

### Reverse analysis

Now expand the expression we want:

$$
\begin{aligned}
Ans &= \sum_{K\subseteq M}(-1)^{|K|-1}\left|\bigcap_{k_i\in K}Q_{k_i}\right|\\
    &= \sum_{i}|Q_i|-\sum_{i<j}|Q_i\cap Q_j|+\sum_{i<j<k}|Q_i\cap Q_j\cap Q_k|-\cdots+(-1)^{T-1}\left|\bigcap_{i=1}^TQ_i\right|
\end{aligned}
$$

This is exactly the expanded form of inclusion–exclusion, so we derive it in reverse:

$$
Ans=\left|\bigcup_{i=1}^TQ_i\right|
$$

Now look at what the right-hand side means: any one of the conditions $1\sim T$ holds. That is, it counts the colorings in which some two vertices (not necessarily adjacent) have the same color! The universe of colorings is $U$, and clearly $|U|=m^n$. Taking the complement, we need the number of colorings where all vertices have different colors, which is $A_m^n=\frac{m!}{(m-n)!}$. So

$$
Ans=m^n-A_m^n
$$

To solve this problem, we first wrote it in mathematical form. Then we started from the condition that carries the most information, the definition of $F(S)$, and turned it into intersections, unions and complements of sets. Finally we turned the expression into the form of inclusion–exclusion and **derived the result in reverse**. This problem shows exactly how inclusion–exclusion can be used in reverse.

## Inclusion–exclusion in number theory

Inclusion–exclusion can solve some number theory problems in a neat way.

### Counting pairs with GCD k using inclusion–exclusion

Consider the following problem:

???+ note "Count the pairs whose greatest common divisor is $k$"
    Let $1 \le x, y \le N$, and let $f(k)$ be the number of ordered pairs $(x, y)$ whose greatest common divisor is $k$. Find the values $f(1)$ to $f(N)$.

This problem can of course be solved with Euler's totient function or Möbius inversion, but neither is as simple as inclusion–exclusion.

By inclusion–exclusion, we first find all pairs that have $k$ as a **common divisor**, and then remove all pairs that have a multiple of $k$ as a **common divisor**. The remaining pairs are exactly those with $k$ as their **greatest common divisor**. That is, $f(k)=$ (number of pairs with $k$ as a **common divisor**) $-$ (number of pairs with a multiple of $k$ as a **common divisor**).

Going further, the number of pairs with a multiple of $k$ as a **common divisor** equals the sum of the numbers of pairs whose **greatest common divisor** is a multiple of $k$. So we can write:

$$
f(k)= \lfloor (N/k) \rfloor ^2 - \sum_{i=2}^{i*k \le N} f(i*k)
$$

When $k>N/2$, we can directly compute $f(k)= \lfloor (N/k) \rfloor ^2$. So we can work backwards, computing from $f(N)$ down to $f(1)$. This solves the problem using inclusion–exclusion.

```cpp
for (long long k = N; k >= 1; k--) {
  f[k] = (N / k) * (N / k);
  for (long long i = k + k; i <= N; i += k) f[k] -= f[i];
}
```

The time complexity of this method is $O( \sum_{i=1}^{N} N/i)=O(N \sum_{i=1}^{N} 1/i)=O(N \log N)$.

Here are three practice problems that use the same idea:

-   [Luogu P2398 GCD SUM](https://www.luogu.com.cn/problem/P2398)
-   [Luogu P2158 \[SDOI2008\] Honor Guard](https://www.luogu.com.cn/problem/P2158)
-   [Luogu P1447 \[NOI2010\] Energy Harvesting](https://www.luogu.com.cn/problem/P1447)

### Deriving Euler's totient function with inclusion–exclusion

Consider the following problem:

???+ note "Formula for Euler's totient function"
    Compute Euler's totient function $\varphi(n)$, where $\varphi(n)=|\{1\leq x\leq n|\gcd(x,n)=1\}|$.

Direct computation takes $O(n\log n)$, a linear sieve takes $O(n)$, and Du's sieve takes $O(n^{\frac{2}{3}})$ (though why would an introductory number theory problem solved with inclusion–exclusion need Du's sieve?). Next we use inclusion–exclusion to derive the formula for Euler's totient function.

To check whether two numbers are coprime, first factor into primes:

$$
n=\prod_{i=1}^k{p_i}^{c_i}
$$

Then we need $x$ to not be a multiple of any $p_i$, i.e. $p_i\nmid x$. Treat this as a property with corresponding set $S_i$. Then

$$
\varphi(n)=\left|\bigcap_{i=1}^kS_i\right|=|U|-\left|\bigcup_{i=1}^k\overline{S_i}\right|
$$

The universe has size $|U|=n$, and $\overline{S_i}$ is the set of $x$ with $p_i\mid x$. Clearly $|\overline{S_i}|=\frac{n}{p_i}$, and from this we get

$$
\left|\bigcap_{a_i<a_{i+1}}S_{a_i}\right|=\frac{n}{\prod p_{a_i}}
$$

Therefore

$$
\begin{aligned}
\varphi(n)&=n-\sum_{i}\frac{n}{p_i}+\sum_{i<j}\frac{n}{p_ip_j}-\cdots+(-1)^k\frac{n}{p_1p_2 \cdots p_k}\\
&=n\left(1-\frac{1}{p_1}\right)\left(1-\frac{1}{p_2}\right)\cdots\left(1-\frac{1}{p_k}\right)\\
&=n\prod_{i=1}^k\left(1-\frac{1}{p_i}\right)
\end{aligned}
$$

This is the mathematical formula for Euler's totient function.

## Generalized inclusion–exclusion

Inclusion–exclusion is often used to count sets. More generally, for two functions on sets $f(S),g(S)$, if

$$
f(S)=\sum_{T\subseteq S}g(T)
$$

then

$$
g(S)=\sum_{T\subseteq S}(-1)^{|S|-|T|}f(T)
$$

### Proof

Here is a short proof. We start from the right-hand side:

$$
\begin{aligned}
&\sum_{T\subseteq S}(-1)^{|S|-|T|}f(T)\\
=&\sum_{T\subseteq S}(-1)^{|S|-|T|}\sum_{Q\subseteq T}g(Q)\\
=&\sum_{Q}g(Q)\sum_{Q\subseteq T\subseteq S}(-1)^{|S|-|T|}\\
\end{aligned}
$$

Notice that the inner sum does not depend on the elements of $Q$, so we remove $Q$ from it:

$$
=\sum_{Q}g(Q)\sum_{T\subseteq (S\setminus Q)}(-1)^{|S\setminus Q|-|T|}
$$

Define the function $F(P)=\sum_{T\subseteq P}(-1)^{|P|-|T|}$ on a set $P$, and simplify it:

$$
\begin{aligned}
F(P)&=\sum_{T\subseteq P}(-1)^{|P|-|T|}\\
&=\sum_{i=0}^{|P|}\dbinom{|P|}{i}(-1)^{|P|-i}=\sum_{i=0}^{|P|}\dbinom{|P|}{i}1^i(-1)^{|P|-i}\\
&=(1-1)^{|P|}=0^{|P|}
\end{aligned}
$$

So the value of the original expression is

$$
\sum_{Q}g(Q)\sum_{T\subseteq (S\setminus Q)}(-1)^{|S\setminus Q|-|T|}=\sum_{Q}g(Q)F(S\setminus Q)=\sum_{Q}g(Q)\cdot 0^{|S\setminus Q|}
$$

Only when $|S\setminus Q|=0$ do we get $0^0=1$. In that case $Q=S$, and the contribution to the answer is $g(S)$. Otherwise $0^{|S\setminus Q|}=0$ and there is no contribution. So we get

$$
\sum_{Q}g(Q)\cdot 0^{|S\setminus Q|}=g(S)
$$

This completes the proof.

### Corollary

This form has the following corollary. With universe $U$, for functions $f(S),g(S)$, if

$$
f(S)=\sum_{S\subseteq T}g(T)
$$

then

$$
g(S)=\sum_{S\subseteq T}(-1)^{|T|-|S|}f(T)
$$

This corollary is really the complement form, and its proof is similar.

## Counting DAGs

???+ note "Counting DAGs"
    Count the labeled directed acyclic graphs on $n$ vertices, modulo $10^9+7$. $n\leq 5\times 10^3$.

### Direct DP

Consider DP. Let $f[i,j]$ be the number of DAGs on $i$ vertices with exactly $j$ vertices of in-degree $0$. Suppose that after removing these $j$ vertices, $k$ vertices have in-degree $0$. Then before the removal, each of these $k$ vertices must have an edge from at least one of the $j$ vertices, giving $2^j-1$ choices each. Besides edges to the $k$ vertices, the $j$ vertices may have any edges to the remaining vertices, giving $2^{i-j-k}$ choices each. So the recurrence is:

$$
f[i,j]=\binom{i}{j}\sum_{k=1}^{i-j}(2^j-1)^k2^{(i-j-k)j}f[i-j,k]
$$

Computing this takes $O(n^3)$.

### Relaxing the constraint

The DP above requires exactly $j$ vertices of in-degree $0$, which is too strict. We can relax it to at least $j$ vertices of in-degree $0$. Define $f[i]$ directly as the number of DAGs on $i$ vertices, and apply inclusion–exclusion. For the $j$ chosen vertices, they may have any edges to the remaining $i-j$ vertices, giving $\left(2^{i-j}\right)^j=2^{(i-j)j}$ choices:

$$
f[i]=\sum_{j=1}^i(-1)^{j-1}\binom{i}{j}2^{(i-j)j}f[i-j]
$$

Computing this takes $O(n^2)$.

## Min-max inclusion–exclusion

For a sequence $\{x_i\}$ of length $n$ whose elements form a [total order](../order-theory.md#partially-ordered-sets) and support addition and subtraction, let $S=\{1,2,3,\cdots,n\}$. Then:

$$
\max_{i\in S}{x_i}=\sum_{T\subseteq S}{(-1)^{|T|-1}\min_{j\in T}{x_j}}
$$

$$
\min_{i\in S}{x_i}=\sum_{T\subseteq S}{(-1)^{|T|-1}\max_{j\in T}{x_j}}
$$

**Proof:** We map this to the ordinary inclusion–exclusion principle. For $x\in S$, suppose $x$ is the $k$-th smallest element. Define the map $f:x\mapsto \{1,2,\cdots,k\}$. Clearly this is a bijection.

It is easy to see that for $x,y\in S$, $f(\min(x,y))=f(x)\cap f(y)$ and $f(\max(x,y))=f(x)\cup f(y)$. So we get:

$$
\begin{aligned}
\left|f\left(\max_{i\in S}{x_i}\right)\right|
&= \left| \bigcup_{i\in S} f(x_i) \right|\\
&= \sum_{T\subseteq S}(-1)^{|T|-1} \left|\bigcap_{j\in T}f(x_j)\right|\\
&= \sum_{T\subseteq S}(-1)^{|T|-1} \left|f\left(\min_{j\in T}{x_j}\right)\right|\\
\end{aligned}
$$

Then map $\left|f\left(\max_{i\in S}{x_i}\right)\right|$ back to $\max_{i\in S}{x_i}$. The case of $\min$ is similar.

This completes the proof.

You might think this formula is silly, since the maximum can be found directly. Min-max inclusion–exclusion is important because it also holds for expected values:

$$
E\left(\max_{i\in S}{x_i}\right)=\sum_{T\subseteq S}{(-1)^{|T|-1}E\left(\min_{j\in T}{x_j} \right)}
$$

$$
E\left(\min_{i\in S}{x_i}\right)=\sum_{T\subseteq S}{(-1)^{|T|-1}E\left(\max_{j\in T}{x_j} \right)}
$$

**Proof:** Consider one way of computing the expected value:

$$
E\left(\max_{i\in S}{x_i}\right)=\sum_{y}{P(y=x)\max_{j\in S}{y_j}}
$$

where $y$ is a sequence of length $n$.

Apply the earlier formula to the $\max$ on the right:

$$
\begin{aligned}E\left(\max_{i\in S}{x_i}\right)&=\sum_{y}{P(y=x)\max_{j\in S}{y_j}}\\
&=\sum_{y}{P(y=x)\sum_{T\subseteq S}{(-1)^{|T|-1}\min_{j\in T}{y_j}}} \end{aligned}
$$

Swap the order of summation:

$$
\begin{aligned}E\left(\max_{i\in S}{x_i}\right)
&=\sum_{y}{P(y=x)\sum_{T\subseteq S}{(-1)^{|T|-1}\min_{j\in T}{y_j}}}\\
&=\sum_{T\subseteq S}{(-1)^{|T|-1}\sum_y{P(y=x)\min_{j\in T}{y_j}}}\\
&=\sum_{T\subseteq S}{(-1)^{|T|-1}E\left(\min_{j\in T}{y_j}\right)} \end{aligned}
$$

The case of $\min$ is similar.

This completes the proof.

There is an even stronger version:

$$
\underset{i\in S}{\operatorname{kthmax}{x_i}}=\sum_{T\subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}\min_{j\in T}{x_j}}
$$

$$
\underset{i\in S}{\operatorname{kthmin}{x_i}}=\sum_{T\subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}\max_{j\in T}{x_j}}
$$

$$
E\left(\underset{i\in S}{\operatorname{kthmax}{x_i}}\right)=\sum_{T\subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}E\left(\min_{j\in T}{x_j}\right)}
$$

$$
E\left(\underset{i\in S}{\operatorname{kthmin}{x_i}}\right)=\sum_{T\subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}E\left(\max_{j\in T}{x_j}\right)}
$$

By convention, if $n< m$, then $\dbinom nm=0$.

**Proof:** Without loss of generality, assume $\forall 1\le i<n,x_i\le x_{i+1}$. Then:

$$
\begin{aligned}
\sum_{T\subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}\min_{j\in T}{x_j}}
&=\sum_{i\in S}{x_i\sum_{T\subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}\left[x_i=\min_{j\in T}{x_j} \right]}}\\
&=\sum_{i\in S}{x_i\sum_{j=k}^n{\dbinom {n-i}{j-1}\dbinom {j-1}{k-1}(-1)^{j-k}}}
\end{aligned}
$$

Using the combinatorial identity $\dbinom ab\dbinom bc=\dbinom ac\dbinom {a-c}{b-c}$, we get:

$$
\begin{aligned}
\sum_{T\subseteq S}{(-1)^{|T|-k}\dbinom {|T|-1}{k-1}\min_{j\in T}{x_j}}
&=\sum_{i\in S}{x_i\sum_{j=k}^n{\dbinom {n-i}{j-1}\dbinom {j-1}{k-1}(-1)^{j-k}}}\\
&=\sum_{i\in S}{x_i\sum_{j=k}^n{\dbinom {n-i}{k-1}\dbinom {n-i-k+1}{j-k}(-1)^{j-k}}}\\
&=\sum_{i\in S}{\dbinom {n-i}{k-1}x_i\sum_{j=k}^n{\dbinom {n-i-k+1}{j-k}(-1)^{j-k}}}\\
&=\sum_{i\in S}{\dbinom {n-i}{k-1}x_i\sum_{j=0}^{n-i-k+1}{\dbinom {n-i-k+1}j(-1)^{j}}}
\end{aligned}
$$

When $i=n-k+1$:

$$
\dbinom {n-i}{k-1}\sum_{j=0}^{n-i-k+1}{\dbinom {n-i-k+1}j(-1)^{j}}=1
$$

Otherwise:

$$
\dbinom {n-i}{k-1}\sum_{j=0}^{n-i-k+1}{\dbinom {n-i-k+1}j(-1)^{j}}=0
$$

So:

$$
\sum_{i\in S}{\dbinom {n-i}{k-1}x_i\sum_{j=0}^{n-i-k+1}{\dbinom {n-i-k+1}j(-1)^{j}}}=\underset{i\in S}{\operatorname{kthmax}}{x_i}
$$

The other three are similar.

This completes the proof.

From min-max inclusion–exclusion we also get the following formula:

$$
\underset{i\in S}{\operatorname{lcm}}{x_i}=\prod_{T\subseteq S}{\left(\gcd_{j\in T}{x_j} \right)^{(-1)^{|T|-1}}}
$$

This holds because $\operatorname{lcm},\gcd,a^{1},a^{-1}$ play the roles of $\max,\min,+,-$ respectively. In other words, it is min-max inclusion–exclusion applied to the exponents, so it is naturally correct.

## PKUWC2018 Random Walk

???+ note "[PKUWC2018 Random Walk](https://loj.ac/problem/2542)"
    You are given a tree with $n$ vertices. You start at $x$, and at each step you pick one of the edges incident to your current vertex uniformly at random and walk along it.
    
    There are $Q$ queries. Each query gives a set $S$. Starting from $x$ and walking randomly, find the expected number of steps until every vertex in $S$ has been visited at least once.
    
    In particular, vertex $x$ (the starting vertex) counts as visited once from the start.
    
    Output the answer modulo $998244353$.
    
    $1\le n\le 18,1\le Q\le 5000,1\le |S|\le n$.

The expected number of steps is the same as the walking time. Let the random variable $x_i$ be the time when vertex $i$ is first reached. Then what we want is

$$
E\left(\max_{i\in S}x_i\right)
$$

Using min-max inclusion–exclusion, we get

$$
E\left(\max_{i\in S}x_i\right)
=E\left(\sum_{T\subseteq S}(-1)^{|T|-1}\min_{i\in T}x_i\right)
=\sum_{T\subseteq S}(-1)^{|T|-1}E\left(\min_{i\in T}x_i\right)
$$

For a set $T\in[n]$, we want to compute $F(T)=E(\min_{i\in T}x_i)$.

$E(\min_{i\in T}x_i)$ is the expected time to first reach some vertex in $T$. Let $f(i)$ be the expected time to first reach some vertex of $T$ when starting from vertex $i$.

-   For $i\in T$, $f(i)=0$.
-   For $i\notin T$, $f(i)=1+\frac{1}{\text{deg}(i)}\sum_{(i,j)\in E}f(j)$.

Plain Gaussian elimination takes $O(n^3)$. Then computing $F(T)$ for every $T$ would take $O(2^nn^3)$ in total, which is too slow. Instead we use the trick of elimination on a tree.

Let the root be $1$, and let $p_u$ be the parent of vertex $u$. For a leaf $i$, $f(i)$ depends only on the parent of $i$ (or $f(i)=0$, which is even better). So we can write $f(i)$ in the form $f(i)=A_i+B_if(p_i)$, where $A_i,B_i$ are quick to compute.

For a non-leaf vertex $i$, consider its children $j_1,\cdots,j_k$. Since $f(j_e)=A_{j_e}+B_{j_e}f(i)$, we get

$$
f(i)=1+\frac{1}{\deg(i)}\sum_{e=1}^k\left(A_{j_e}+B_{j_e}f(i)\right)+\frac{f(p_i)}{\deg(i)}
$$

Rearranging gives

$$
f(i)=\frac{\deg(i)+\sum_{e=1}^kA_{j_e}}{\deg(i)-\sum_{e=1}^kB_{j_e}}+
\frac{f(p_i)}{\deg(i)-\sum_{e=1}^kB_{j_e}}
$$

So $f(i)$ can also be written in the form $A_i+B_if(p_i)$. We can keep working backwards up to the root. The root has no parent, so

$$
f(1)=\frac{\deg(1)+\sum_{e=1}^kA_{j_e}}{\deg(1)-\sum_{e=1}^kB_{j_e}}
$$

Solving this equation gives $f(1)$, and one more pass from top to bottom gives $f(i)$ for every vertex. Then $F(T)=f(x)$. The time complexity is $O(n)$.

This way we can compute $F(T)$ for every $T$ in $O(2^nn)$ time.

Back to the inclusion–exclusion part: we know $E(\max_{i\in S}x_i)=\sum_{T\subseteq S}(-1)^{|T|-1}F(T)$.

Let $F'(T)=(-1)^{|T|-1}F(T)$. Then $E(\max_{i\in S}x_i)=\sum_{T\subseteq S}F'(T)$. So we can use FMT (also called subset prefix sums, or the OR version of FWT) to compute $E(\max_{i\in S}x_i)$ for every $S$ in $O(2^nn)$ time, and then answer each query in $O(1)$.

### Exercises

-   [ABC331- G - Collect Them All](https://atcoder.jp/contests/abc331/tasks/abc331_g)
-   [Luogu P4707 Return to Reality](https://www.luogu.com.cn/problem/P4707)

## References

[A Brief Exploration of the Inclusion–Exclusion Principle - Wang Di](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2013%E8%AE%BA%E6%96%87%E9%9B%86.pdf), Collected Papers of the 2013 Chinese National Team Candidates in Informatics Olympiad

[Counting Labeled DAGs Series - Cyhlnj](https://www.cnblogs.com/cjoieryl/p/10078167.html)

[Total order - Wikipedia](https://en.wikipedia.org/wiki/Total_order)
