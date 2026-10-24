Number-theoretic sqrt decomposition (also known as division blocks) quickly computes sums of the form

$$
\sum_{i=1}^nf(i)g\left(\left\lfloor\dfrac ni\right\rfloor\right)
$$

If $\sum_{i=l}^{r}f(i)$ can be computed in $O(1)$ time, or the prefix sums of $f$ have been precomputed, sqrt decomposition computes the value of this sum in $O(\sqrt{n})$ time.

Sqrt decomposition is often combined with techniques such as [Möbius inversion](./mobius.md).

## Idea

We start with a simple example to show the idea. Suppose we want to count the lattice points under the hyperbola shown below:

![Lattice points under a hyperbola](./images/sqrt-decomposition.svg)

This is the same as computing the sum:

$$
\sum_{i=1}^{11}\left\lfloor\dfrac{11}{i}\right\rfloor.
$$

This is the special case of the sum above with $f(k)=1,~g(k)=k$.

The simplest approach is of course to count column by column and add up, but that needs the number of lattice points in each column $i=1,2,\cdots,11$. Looking at the figure, these columns can be grouped into $5$ blocks. Within each block, all columns have the same height, forming a rectangular grid of points. So if we know the widths of these blocks, we can count quickly by computing the sizes of these rectangles.

This is the basic idea of sqrt decomposition.

## Properties

This section gives some results about splitting the lattice points under the hyperbola $y = \dfrac{n}{x}$ into blocks. Specifically, we split the integers from $1$ to $n$ into blocks by the value of $\left\lfloor\dfrac{n}{i}\right\rfloor$. Let

$$
D(n) = \left\{\left\lfloor\dfrac{n}{i}\right\rfloor : 1 \le i \le n,~i\in\mathbf N_+\right\}.
$$

This is the set of all possible values of $\left\lfloor\dfrac{n}{i}\right\rfloor$.

First, there are only $O(\sqrt{n})$ distinct values. So sqrt decomposition produces only $O(\sqrt{n})$ blocks.

???+ note "Property 1"
    $|D(n)|\le 2\sqrt{n}$.

??? note "Proof"
    There are two cases:
    
    -   When $i\le\sqrt{n}$, $i$ takes at most $\sqrt{n}$ values, so $\left\lfloor\dfrac{n}{i}\right\rfloor$ also takes at most $\sqrt{n}$ values.
    -   When $i>\sqrt{n}$, $\left\lfloor\dfrac{n}{i}\right\rfloor \le\dfrac{n}{i} < \sqrt{n}$, which also allows at most $\sqrt{n}$ values.
    
    So the total number of possible values is $|D(n)|\le 2\sqrt{n}$.

With a more careful analysis, we can describe the set $D(n)$ and its size exactly.

???+ note "Property 2"
    Let $s = \lfloor\sqrt{n}\rfloor$. The elements of $D(n)$ in increasing order are
    
    $$
    1 < 2 < \cdots < s-1 < s \le \left\lfloor\dfrac{n}{s}\right\rfloor < \left\lfloor\dfrac{n}{s-1}\right\rfloor < \cdots < \left\lfloor\dfrac{n}{2}\right\rfloor < \left\lfloor\dfrac{n}{1}\right\rfloor = n.
    $$
    
    Hence $|D(n)| = \lfloor \sqrt{4n+1}\rfloor - 1$.

??? note "Proof"
    First, for $1 \le i \le s$, we can show that $\left\lfloor\dfrac{n}{\lfloor n/i\rfloor}\right\rfloor = i$. Let $d = \left\lfloor\dfrac{n}{i}\right\rfloor$; we need to show $\left\lfloor\dfrac{n}{d}\right\rfloor = i$. As inequalities: given $d \le \dfrac{n}{i} < d + 1$, we need to show $i \le \dfrac{n}{d} < i + 1$. The given condition can be written as $i\le\dfrac{n}{d} < i + \dfrac{i}{d}$, so we only need $\dfrac{i}{d} \le 1$, that is, $i \le d = \left\lfloor\dfrac{n}{i}\right\rfloor$. This is equivalent to $i \le \dfrac{n}{i}$, which holds for all $1 \le i \le s \le \sqrt{n}$.
    
    This result shows that the map $i \mapsto \left\lfloor\dfrac{n}{i}\right\rfloor$ is a bijection between the set $\{i:1\le i \le s\}$ and the set $\left\{\left\lfloor\dfrac{n}{i}\right\rfloor: 1\le i\le s\right\}$. Since the $i$ are distinct, the values $\left\lfloor\dfrac{n}{i}\right\rfloor$ are distinct too. The only element the two sets might share is $s$ and $\left\lfloor\dfrac{n}{s}\right\rfloor$. So $|D(n)|=2s - \left[s = \lfloor n/s\rfloor\right]$.
    
    To get the final expression for $|D(n)|$, we need to find when $s = \left\lfloor\dfrac{n}{s}\right\rfloor$ holds.
    
    -   When $s = \left\lfloor\dfrac{n}{s}\right\rfloor$, we have $s \le \dfrac{n}{s} < s + 1$, that is, $s^2 \le n < s^2+s$. Then $4s^2 + 1 \le 4n + 1 < 4s^2+4s+1 = (2s+1)^2$. Since $4n+1$ is always odd, the left side can be relaxed to $4s^2$ without changing anything, so the condition is equivalent to $2s \le \sqrt{4n+1} < 2s+1$, that is, $\lfloor \sqrt{4n+1}\rfloor = 2s$.
    -   When $s < \left\lfloor\dfrac{n}{s}\right\rfloor$, we have $s + 1 \le \dfrac{n}{s}$, that is, $s^2 + s\le n$. Also $n < (s+1)^2$, so $s^2 + s\le n < (s+1)^2$. This is equivalent to $(2s+1)^2\le 4n+1 < 4(s+1)^2+1$. Using again that $4n+1$ is odd, the right side can be tightened to $4(s+1)^2$, so the condition is equivalent to $2s+1\le\sqrt{4n+1} < 2s+2$, that is, $\lfloor \sqrt{4n+1}\rfloor = 2s+1$.
    
    Putting the two cases together gives $|D(n)| = \lfloor \sqrt{4n+1}\rfloor - 1$.

Next, the left and right endpoints of each block are easy to find.

???+ note "Property 3"
    For $d\in D(n)$, the integers $i$ with $\left\lfloor\dfrac{n}{i}\right\rfloor=d$ are exactly those in the range
    
    $$
    \left\lfloor\dfrac{n}{d+1}\right\rfloor + 1\le i \le \left\lfloor\dfrac{n}{d}\right\rfloor.
    $$

??? note "Proof"
    $\left\lfloor\dfrac{n}{i}\right\rfloor=d$ is the same as the inequality
    
    $$
    d\le \dfrac{n}{i} < d+1.
    $$
    
    This is further equivalent to
    
    $$
    \dfrac{n}{d+1} < i\le \dfrac{n}{d}.
    $$
    
    Since $i\in\mathbf N_+$, we can take floors in this inequality, and it becomes
    
    $$
    \left\lfloor\dfrac{n}{d+1}\right\rfloor + 1 \le i\le \left\lfloor\dfrac{n}{d}\right\rfloor.
    $$

This property also reflects the symmetry of the picture: the set of right endpoints of the blocks (the green points in the figure above) is exactly $D(n)$. This is easy to see, since the whole picture is symmetric about the line $y=x$.

Besides these properties, the set $D(n)$ also has a nice recursive property:

???+ note "Property 4"
    For $m\in D(n)$, $D(m)\subseteq D(n)$.

??? note "Proof"
    Let $m = \left\lfloor\dfrac{n}{k}\right\rfloor$. Then for all $i\in\mathbf N_+$,
    
    $$
    \left\lfloor\dfrac{m}{i}\right\rfloor = \left\lfloor\dfrac{\lfloor n/k\rfloor}{i}\right\rfloor = \left\lfloor\dfrac{n}{ki}\right\rfloor \in D(n),
    $$
    
    so $D(m)\subseteq D(n)$. The second equality uses the property of the [floor function](./basic.md#取整函数) for nested fractions.

As mentioned above, $D(n)$ is both the set of values of $\left\lfloor\dfrac{n}{i}\right\rfloor$ over the blocks and the set of right endpoints of the blocks. This means that if we apply sqrt decomposition recursively (i.e., the value of a function at $n$ depends on its values at $m\in D(n)\setminus\{n\}$), then the set of values and the set of right endpoints involved in the whole computation are both just $D(n)$. A typical example is [Du's sieve](./hyperbola.md#杜教筛).

## Process

Using the results of the previous section, we get the concrete process of sqrt decomposition.

To compute the value of the sum

$$
\sum_{i=1}^nf(i)g\left(\left\lfloor\dfrac ni\right\rfloor\right)
$$

we can split the indices $i=1,2,\cdots,n$ into blocks by the value of $\left\lfloor\dfrac ni\right\rfloor$. The indices with the same value of $\left\lfloor\dfrac ni\right\rfloor$ form a range of consecutive integers $[l,r]$, so the contribution of this block to the sum is

$$
\left(\sum_{i=l}^rf(i)\right)\cdot g\left(\left\lfloor\dfrac nl\right\rfloor\right).
$$

To compute this quickly, we usually need to compute the sum over $f$ on the left quickly. Sometimes a closed form for this sum is known, so each evaluation takes $O(1)$ time. Other times we can precompute its prefix sums, so each query still takes $O(1)$ time.

When going through the blocks in order, the left endpoint $l$ of the current block is the right endpoint of the previous block plus $1$, and the right endpoint of the current block is $\left\lfloor\dfrac n{\lfloor n/l\rfloor}\right\rfloor$. This gives the following pseudocode:

$$
\begin{array}{l}
\textbf{Algorithm }\text{Sum}(f,g,n):\\
\textbf{Input. }n,~s(k)=\sum_{i=1}^kf(i),~g(k).\\
\textbf{Output. }S(n) = \sum_{i=1}^nf(i)g(\lfloor n/i\rfloor).\\
\textbf{Method.}\\
\begin{array}{ll}
1 & l \gets 1\\
2 & \textit{result} \gets 0 \\
3 & \textbf{while } l \leq n \textbf{ do}\\
4 & \qquad r \gets \left\lfloor \dfrac{n}{\lfloor n/l \rfloor} \right\rfloor\\
5 & \qquad \textit{result} \gets \textit{result} + (s(r)-s(l-1))\cdot g\left(\left\lfloor \dfrac{n}{l} \right\rfloor\right)\\
6 & \qquad l \gets r+1\\
7 & \textbf{end while}\\
8 & \textbf{return }\textit{result}
\end{array}
\end{array}
$$

If each evaluation of $s(\cdot)$ takes $O(1)$ time, the whole process takes $O(\sqrt{n})$ time.

## Extensions

So far we have covered the most common and basic form of sqrt decomposition. This section discusses extended forms.

### Sqrt decomposition with ceilings

Sqrt decomposition can compute sums with ceilings:

$$
\sum_{i=1}^nf(i)g\left(\left\lceil\dfrac ni\right\rceil\right).
$$

Since $\left\lceil\dfrac ni\right\rceil = \left\lfloor\dfrac {n-1}i\right\rfloor + 1$, this sum can be turned into the floor case:

$$
f(n)g(1) + \sum_{i=1}^{n-1}f(i)g\left(\left\lfloor\dfrac {n-1}i\right\rfloor + 1\right).
$$

Note the change in the upper limit of the sum, and the separate term for $i=n$.

### Multi-dimensional sqrt decomposition

Sqrt decomposition can also handle sums with more than one floor expression:

$$
\sum_{i=1}^{n}f(i)g\left(\left\lfloor\dfrac {n_1}i\right\rfloor,\left\lfloor\dfrac {n_2}i\right\rfloor,\cdots,\left\lfloor\dfrac {n_m}i\right\rfloor\right).
$$

Usually $n\le\min\{n_1,n_2,\cdots,n_m\}$; otherwise the cases where some $\lfloor n_j/i\rfloor=0$ need separate handling. To apply the idea of sqrt decomposition, we need every floor expression $\left\lfloor\dfrac {n_1}i\right\rfloor,\left\lfloor\dfrac {n_2}i\right\rfloor,\cdots,\left\lfloor\dfrac {n_m}i\right\rfloor$ to stay constant within each block. In other words, the multi-dimensional blocks should be the intersections of all the one-dimensional blocks. So for a known left endpoint $l$, the corresponding right endpoint is

$$
\min\left\{\left\lfloor\dfrac {n_1}{\lfloor n_1/l\rfloor}\right\rfloor,\left\lfloor\dfrac {n_2}{\lfloor n_2/l\rfloor}\right\rfloor,\cdots,\left\lfloor\dfrac {n_m}{\lfloor n_m/l\rfloor}\right\rfloor\right\}.
$$

That is, take the minimum of the right endpoints of all one-dimensional blocks as the right endpoint of the multi-dimensional block. The figure below helps:

![Illustration of multi-dimensional sqrt decomposition](./images/n-dimension-sqrt-decomposition.svg)

The two-dimensional form is the most common. In that case, replace $r \gets \left\lfloor \dfrac{n}{\lfloor n/l \rfloor}\right\rfloor$ in the pseudocode above with

$$
r \gets \min\left\{\left\lfloor \dfrac{n_1}{\lfloor n_1/l \rfloor}\right\rfloor,\left\lfloor \dfrac{n_2}{\lfloor n_2/l \rfloor}\right\rfloor\right\}.
$$

### Sqrt decomposition with arbitrary exponents

Sqrt decomposition can compute sums whose floor expressions have arbitrary exponents:

$$
\sum_{i=1}^{\lfloor n^{\alpha/\beta}\rfloor}f(i)g\left(\left\lfloor\dfrac {n^\alpha}{i^\beta}\right\rfloor\right).
$$

Here $\alpha,\beta$ are positive real numbers. The basic form discussed on this page has $\alpha=\beta=1$.

???+ note "Properties"
    For a positive integer $n$ and positive real numbers $\alpha, \beta$, let
    
    $$
    D(n,\alpha,\beta) = \left\{\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor: i=1,2,\cdots,\lfloor n^{\alpha/\beta}\rfloor\right\}.
    $$
    
    Then
    
    1.  $|D(n,\alpha,\beta)|\le 2n^{\alpha/(1+\beta)}$.
    2.  For $d\in D(n,\alpha,\beta)$, the values of $i$ with $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor=d$ are exactly those in the range
    
        $$
        \left\lfloor\dfrac{n^{\alpha/\beta}}{(d+1)^{1/\beta}}\right\rfloor + 1\le i \le \left\lfloor\dfrac{n^{\alpha/\beta}}{d^{1/\beta}}\right\rfloor.
        $$

??? note "Proof"
    For the first claim, there are two cases:
    
    -   When $i\le \dfrac{n^\alpha}{i^\beta}$, we have $i\le n^{\alpha/(1+\beta)}$, so $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor$ takes at most $n^{\alpha/(1+\beta)}$ values.
    -   When $i > \dfrac{n^\alpha}{i^\beta}$, we have $i> n^{\alpha/(1+\beta)}$, and so $\dfrac{n^\alpha}{i^\beta} < n^{\alpha/(1+\beta)}$. So $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor$ also takes at most $n^{\alpha/(1+\beta)}$ values.
    
    Combining the two cases gives $|D(n,\alpha,\beta)|\le 2n^{\alpha/(1+\beta)}$.
    
    For the second claim, $\left\lfloor\dfrac{n^\alpha}{i^\beta}\right\rfloor=d$ is equivalent to
    
    $$
    d \le \dfrac{n^\alpha}{i^\beta} < d+1 \iff \dfrac{n^{\alpha/\beta}}{(d+1)^{1/\beta}} < i \le \dfrac{n^{\alpha/\beta}}{d^{1/\beta}}.
    $$
    
    Taking floors in this inequality gives the second claim.

With these properties, sqrt decomposition with arbitrary exponents runs in $O(n^{\alpha/(1+\beta)})$ time.

???+ example "Example"
    For example, with $\alpha=\beta=1/2$, the sum
    
    $$
    \sum_{i=1}^nf(i)g\left(\left\lfloor\sqrt{\dfrac {n}{i}}\right\rfloor\right),
    $$
    
    can be computed with sqrt decomposition in $O(n^{1/3})$ time. Given the left endpoint $l$ of a block, the right endpoint is $r=\left\lfloor\dfrac{n}{\lfloor\sqrt{n/l}\rfloor^2}\right\rfloor$.

## Example problems

???+ example "[UVa11526 H(n)](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2521)"
    There are $T$ test cases, each with one integer $n$. For each test case, output $\sum_{i=1}^n\left\lfloor\dfrac ni\right\rfloor$.

??? note "Solution"
    By the analysis above, we can handle each block with the same value of $\left\lfloor\dfrac ni\right\rfloor$ at once. The time complexity is $O(T\sqrt n)$.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/sqrt-decomposition/sqrt-decomposition_1.cpp"
    ```

???+ example "[Codeforces 1954E Chain Reaction](https://codeforces.com/contest/1954/problem/E)"
    There is a row of $n$ monsters, and monster $i$ starts with $a_i$ health. One attack reduces the health of a contiguous segment of living monsters by $k$; a monster whose health is at most $0$ dies. For every $k$, find the number of attacks needed to kill all monsters. Here $n,a_i\leq 10^5$.

??? note "Solution"
    Let $a_0=0$. Suppose killing the first $(i-1)$ monsters takes $T(k,i-1)$ attacks, and monster $i$ has health $a_i$. Killing monster $(i-1)$ takes $\lceil a_{i-1}/k\rceil$ attacks on it, and all of these attacks can be extended to monster $i$. So killing monster $i$ only takes $\max\{0,\lceil a_i/k\rceil-\lceil a_{i-1}/k\rceil\}$ more attacks. So the total number of attacks is
    
    $$
    T(k,n)=\sum_{i=1}^n\max\left\{0,\left\lceil\dfrac{a_i}{k}\right\rceil-\left\lceil\dfrac{a_{i-1}}{k}\right\rceil\right\}.
    $$
    
    Since $n$ and $k$ are both fairly large, computing this sum separately for each $k$ is too slow. Instead, for each $i=1,2,\cdots,n$, we maintain the sequence $\{T(k,i)\}_k$. Initially, $T(k,0)\equiv 0$. Suppose the sequence $\{T(k,i-1)\}_k$ is known; how do we update it to get $\{T(k,i)\}_k$? By the analysis above, we just add $\max\left\{0,\left\lceil\dfrac{a_i}{k}\right\rceil-\left\lceil\dfrac{a_{i-1}}{k}\right\rceil\right\}$ to the $k$-th term. Using two-dimensional sqrt decomposition, this update splits into $O(\sqrt{a_{i-1}}+\sqrt{a_i})$ range updates, each adding a fixed value to a range. The final sequence $\{T(k,n)\}_k$ is the answer.
    
    The problem involves a series of range additions, and all queries come after all updates. So we can do the range additions on a difference array and get the sequence we want with prefix sums at the end. The total time complexity is $O(\max_i a_i+\sum_i\sqrt{a_i})$. There are other solutions to this problem too.

??? note "Implementation"
    ```cpp
    --8<-- "docs/math/code/sqrt-decomposition/sqrt-decomposition_2.cpp"
    ```

## Exercises

-   [UVa11526 H(n)](https://onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&category=27&page=show_problem&problem=2521)
-   [Luogu P2261 CQOI2007 Sum of Remainders](https://www.luogu.com.cn/problem/P2261)
-   [Luogu P3455 POI2007 ZAP-Queries](https://www.luogu.com.cn/problem/P3455)

## References and notes

-   [Time and space complexity analysis of Du's sieve, by riteme](https://riteme.site/blog/2018-9-11/time-space-complexity-dyh-algo.html)
