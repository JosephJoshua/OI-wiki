author: sshwy, FFjet, qz-cqy

## Introduction

The Euclidean-like algorithm was presented by Hong Huadun in a talk at the 2016 Winter Camp. It is mostly used to find sums of sequences (indexed by $i$) of the form

$$
\left\lfloor\dfrac{ai+b}{c}\right\rfloor
$$

The main idea is to use the recursive structure of fractions to reduce the problem to a smaller one and solve it recursively. Because the recursive structure of fractions is directly [related](./continued-fraction.md#连分数表示的求法) to the [Euclidean algorithm](./gcd.md#欧几里得算法), this summation method is called the Euclidean-like algorithm.

Methods such as [continued fractions](./continued-fraction.md) and the [Stern–Brocot tree](./stern-brocot.md) describe the same recursive structure of fractions, so problems solvable with the Euclidean-like algorithm can usually be solved with them too. Compared with those methods, the Euclidean-like algorithm is usually easier to understand and simpler to implement.

## Euclidean-like algorithm

The simplest example is the sum:

$$
f(a,b,c,n)=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,
$$

where $a,b,c,n$ are all positive integers.

### Algebraic approach

First, reduce $a,b$ modulo $c$. This simplifies the problem to the case $0\le a,b<c$:

$$
\begin{aligned}
f(a,b,c,n)&=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor\\
&=\sum_{i=0}^n\left\lfloor
\frac{\left(\left\lfloor\frac{a}{c}\right\rfloor c+(a\bmod c)\right)i+\left(\left\lfloor\frac{b}{c}\right\rfloor c+(b\bmod c)\right)}{c}\right\rfloor\\
&=\sum_{i=0}^n\left(\left\lfloor\frac{a}{c}\right\rfloor i+\left\lfloor\frac{b}{c}\right\rfloor+\left\lfloor\frac{\left(a\bmod c\right)i+\left(b\bmod c\right)}{c}
\right\rfloor\right)\\
&=\frac{n(n+1)}{2}\left\lfloor\frac{a}{c}\right\rfloor
+(n+1)\left\lfloor\frac{b}{c}\right\rfloor+f(a\bmod c,b\bmod c,c,n).
\end{aligned}
$$

Now consider the reduced problem. Let

$$
m = \left\lfloor \frac{an+b}{c} \right\rfloor.
$$

Then the original sum can be written as a double sum:

$$
\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor
=\sum_{i=0}^n\sum_{j=0}^{m-1}\left[j<\left\lfloor \frac{ai+b}{c} \right\rfloor\right].
$$

We want to swap the order of summation, which requires finding, for each $j$, the range of $i$ that satisfies the condition. To do this, rewrite the condition:

$$
\begin{aligned}
&j<\left\lfloor \frac{ai+b}{c} \right\rfloor = \left\lceil \frac{ai+b+1}{c} \right\rceil-1\\
&\iff j + 1 < \left\lceil \frac{ai+b+1}{c} \right\rceil
\iff j+1< \frac{ai+b+1}{c} \\
&\iff \dfrac{cj+c-b-1}{a} < i
\iff \left\lfloor\dfrac{cj+c-b-1}{a}\right\rfloor < i.
\end{aligned}
$$

These steps use properties of the [floor and ceiling functions](./basic.md#取整函数) several times. Substituting the rewritten condition, the sum becomes:

$$
\begin{aligned}
f(a,b,c,n)&=\sum_{j=0}^{m-1}
\sum_{i=0}^n\left[i>\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor \right]\\
&=\sum_{j=0}^{m-1}\left(n-\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\right)\\
&=nm-f\left(c,c-b-1,a,m-1\right).
\end{aligned}
$$

Let $(a',b',c',n')=(c,c-b-1,a,m-1)$. This brings us back to the case $a'>c'$ discussed above.

Putting the two steps together, we see that $(a,c)$ is repeatedly reduced modulo and then swapped, until $a=0$. This is just like running the Euclidean algorithm on $(a,c)$, which is where the name comes from. The time complexity is $O(\log\min\{a,c\})$.

During the computation, we may get $m=0$, in which case the inner recursive call has $n=-1$. This does not affect the final result. However, if we stop the algorithm as soon as $m=0$, the time complexity improves to $O(\log\min\{a,c,n\})$.

??? note "Complexity explanation"
    Because of the similarity between this algorithm and the Euclidean algorithm, it is easy to see that the time complexity is $O(\log\min\{a,c\})$. So we only need to show that if we stop when $m=0$, the time complexity is also $O(\log n)$.
    
    Let $m=\lfloor(an+b)/c\rfloor$, and write $S=mn$ and $k=m/n$. In the geometric view (see the next section), these are the area of the lattice region and the slope of the line. For large enough $n$, approximately $k\doteq a/c$.
    
    Look at how $S$ and $k$ change during the algorithm. In the first step (taking remainders), $n$ stays the same and $k$ changes from about $a/c$ to about $(a\bmod c)/c$; that is, the slope goes from $k$ to $k-\lfloor k\rfloor$, and $S$ becomes about $(k-\lfloor k\rfloor)/k$ times its old value. In the second step (swapping the axes), $S$ stays about the same and $k$ becomes its reciprocal. So if after these two steps the pair $(k,S)$ becomes $(k',S')$, then $k'=(k-\lfloor k\rfloor)^{-1}$ and $S'=\dfrac{k-\lfloor k\rfloor}{k}S\le (k-\lfloor k\rfloor)S$, because from the second round on, $k\ge 1$ at the start of each round.
    
    Since $1\le\lfloor k'\rfloor\le k'<\lfloor k'\rfloor+1$, after two rounds of recursion, $S$ becomes at most the following fraction of its old value:
    
    $$
    (k'-\lfloor k'\rfloor)(k-\lfloor k\rfloor) = 1-\dfrac{\lfloor k'\rfloor}{k'} < 1-\dfrac{\lfloor k'\rfloor}{\lfloor k'\rfloor+1} = \dfrac{1}{\lfloor k'\rfloor+1}\le \dfrac{1}{2}.
    $$
    
    So the algorithm stops after at most $O(\log S)$ rounds. From the second round on, $S$ at the start of each round is at most the $S$ after the previous round's remainder step, which is about $kn^2$ with $k<1$. So $O(\log S)\subseteq O(\log n)$, which proves the claim.

A reference implementation for the template problem:

??? example "Template problem implementation ([Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear))"
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-0.cpp:full-text"
    ```

### Geometric view

The algorithm can also be understood geometrically. The problems the Euclidean-like algorithm solves are mainly about counting lattice points under a line.

As shown in the leftmost part of the figure below, the sum counts the lattice points below the line

$$
y = \dfrac{ax+b}{c}
$$

above the $x$-axis (not including the $x$-axis), with $x$-coordinate in $[0,n]$.

![](./images/euclidean-1.svg)

First, remove the integer parts of the slope and the intercept. This step counts the blue points in the middle part of the figure separately. When the slope and intercept are both integers, the blue points always form a trapezoid: the numbers of points in the columns form an arithmetic sequence, so they are easy to count. After removing them, the remaining lattice points match the red points in the rightmost part of the figure, and the problem becomes one where the slope and intercept are both less than one. The trapezoid has height $n+1$ and bases of length $\lfloor b/c\rfloor$ and $(\lfloor a/c\rfloor n+\lfloor b/c\rfloor)$, so by the trapezoid area formula, this step can be summarized as

$$
f(a,b,c,n) = f(a\bmod c,b\bmod c,c,n) + \dfrac{1}{2}(n+1)\left(\left\lfloor\dfrac{b}{c}\right\rfloor+\left(\left\lfloor\dfrac{a}{c}\right\rfloor n+\left\lfloor\dfrac{b}{c}\right\rfloor\right)\right).
$$

Next, swap the axes. As shown in the leftmost part of the figure below, the red and blue points together form a rectangular grid of width $n$ and height $m=\lfloor(an+b)/c\rfloor$. To count the red points, we can count the blue points and subtract that from the size of the rectangle. After swapping the axes, the blue points in the left part of the figure become the red points under some line. And after swapping, the slope is greater than one, so we are back to the case already handled above.

![](./images/euclidean-2.svg)

The key question is how to find the equation of the line above the new red points. Swapping the axes of the leftmost part of the figure gives the middle part. The line above the swapped red points (the solid line in the middle part) does not correspond to the original line (the solid line in the leftmost part), but to the original line shifted slightly up and to the left (the dashed line in the leftmost part). The reason is that if we swapped the original line (the solid line in the leftmost part) directly, we would get the dashed line in the middle part. But by definition, the points "under" a line include the lattice points lying exactly on it, so the lattice points on the line would be counted twice. To avoid this, we shift the swapped line $y=(cx-b)/a$ (obtained from $y=(ax+b)/c$) down slightly, to get $y=(cx-b-1)/a$. Then the points under it are exactly the blue points from before the swap.

There is one more detail. The line in the middle part has a negative intercept, which means we are not yet back to the initial form. To make the intercept nonnegative, shift the line (the solid line in the middle part) one unit to the left. This does not lose any lattice points: before the swap, no blue point has $y$-coordinate zero, so after the swap no point has $x$-coordinate zero. In the end, the line becomes $y=(cx+c-b-1)/a$, and the upper bound on the $x$-coordinates changes from $m$ to $m-1$. This step can be summarized as

$$
f(a,b,c,n) = mn - f(c,c-b-1,a,m-1).
$$

This recursive algorithm works for two main reasons:

-   First, the slope of the line repeatedly takes its fractional part and then its reciprocal. This is exactly computing the [continued fraction expansion](./continued-fraction.md#连分数表示的求法) of the slope $k=a/c$. The continued fraction of a rational number has length $O(\log\min\{a,c\})$, so the process ends after $O(\log\min\{a,c\})$ steps;
-   Second, each time we swap the axes, the slope is less than one, so intuitively $m<n$. That is, after each round, the range of $x$-coordinates keeps shrinking. The complexity analysis above shows rigorously that every two rounds, $S=mn$ drops to at most half, so the process ends after $O(\log n)$ steps.

This is why the Euclidean-like algorithm with rational slope runs in $O(\log\min\{a,c,n\})$.

Using a similar geometric view, the Euclidean-like algorithm can be extended to irrational slopes. See the example problems below for details.

### Example problems

???+ example "[[Template] Euclidean-like Algorithm](https://www.luogu.com.cn/problem/P5170)"
    There are multiple queries. Given positive integers $a,b,c,n$, find
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    g(a,b,c,n) &= \sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    h(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2.
    \end{aligned}
    $$

??? note "Solution 1"
    Following the derivation for $f$, we can get recursive formulas for $g$ and $h$.
    
    First, take remainders to reduce to the case $0\le a,b<c$:
    
    $$
    \begin{aligned}
    g(a,b,c,n)
    &=g(a\bmod c,b\bmod c,c,n)+\left\lfloor\frac{a}{c}\right\rfloor\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor\frac{n(n+1)}{2}, \\
    h(a,b,c,n)&=h(a\bmod c,b\bmod c,c,n)\\
    &\quad+2\left\lfloor\frac{b}{c}\right\rfloor f(a\bmod c,b\bmod c,c,n)
    +2\left\lfloor\frac{a}{c}\right\rfloor g(a\bmod c,b\bmod c,c,n)\\
    &\quad+\left\lfloor\frac{a}{c}\right\rfloor^2\frac{n(n+1)(2n+1)}{6}+\left\lfloor\frac{b}{c}\right\rfloor^2(n+1)
    +\left\lfloor\frac{a}{c}\right\rfloor\left\lfloor\frac{b}{c}\right\rfloor n(n+1).
    \end{aligned}
    $$
    
    Then swap the order of summation to transform further. Again, let
    
    $$
    m = \left\lfloor \frac{an+b}{c} \right\rfloor.
    $$
    
    Then for the sum $g$,
    
    $$
    \begin{aligned}
    g(a,b,c,n)&=\sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor\\
    &=\sum_{i=0}^n \sum_{j=0}^{m-1}i
    \left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right] \\
    &=\sum_{j=0}^{m-1}\sum_{i=0}^n i\left[i>\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor \right]\\
    &=\sum_{j=0}^{m-1}\dfrac{1}{2}\left(\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor+n+1\right)\left(n-\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\right)\\
    &=\dfrac{1}{2}mn(n+1) - \dfrac{1}{2}\sum_{j=0}^{m-1}\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor - \dfrac{1}{2}\sum_{j=0}^{m-1}\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor^2\\
    &=\dfrac{1}{2}mn(n+1) - \dfrac{1}{2}f(c,c-b-1,a,m-1) - \dfrac{1}{2}h(c,c-b-1,a,m-1).
    \end{aligned}
    $$
    
    For the sum $h$,
    
    $$
    \begin{aligned}
    h(a,b,c,n)&=\sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2\\
    &=\sum_{i=0}^n\sum_{j=0}^{m-1}(2j+1)\left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right]\\
    &=\sum_{j=0}^{m-1}\sum_{i=0}^n(2j+1)\left[i>\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor \right]\\
    &=\sum_{j=0}^{m-1}(2j+1)\left(n-\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\right)\\
    &=nm^2 - \sum_{j=0}^{m-1}\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor - 2\sum_{j=0}^{m-1}j\left\lfloor\frac{cj+c-b-1}{a}\right\rfloor\\
    &=nm^2 - f(c,c-b-1,a,m-1) - 2g(c,c-b-1,a,m-1).
    \end{aligned}
    $$
    
    Geometrically, these nonlinear sums give each point $(i,j)$ in the region a weight $w(i,j)$. Apart from the weights, the computation is exactly the same. In general, the weights can be chosen as
    
    $$
    \sum_{i=0}^ni^r\left\lfloor \frac{ai+b}{c} \right\rfloor^s = \sum_{i=0}^n\sum_{j=0}^{m-1} i^r\left((j+1)^s-j^s\right)\left[j<\left\lfloor\frac{ai+b}{c}\right\rfloor\right].
    $$
    
    Another feature of this problem is that the recursions for $g$ and $h$ call each other. So we need to recurse on the triple $(f,g,h)$ all at once.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-1.cpp"
    ```

???+ example "[\[Tsinghua Training Camp 2014\] Sum](https://www.luogu.com.cn/problem/P5172)"
    There are multiple queries. Given positive integers $n$ and $r$, find
    
    $$
    \sum_{d=1}^n(-1)^{\lfloor d\sqrt{r}\rfloor}.
    $$

??? note "Solution 1"
    If $r$ is a perfect square, then when $\sqrt{r}$ is even the sum is $n$; otherwise the sum alternates between $0$ and $-1$ depending on the parity of $n$. Below we consider the case where $r$ is not a perfect square.
    
    To apply the Euclidean-like algorithm, first rewrite the sum in a familiar form:
    
    $$
    \begin{aligned}
    \sum_{d=1}^n(-1)^{\lfloor d\sqrt{r}\rfloor} &= \sum_{d=1}^n\left(1 - 2(\lfloor d\sqrt{r}\rfloor\bmod 2)\right)\\
    &= n - 2\sum_{d=1}^n\left(\lfloor d\sqrt{r}\rfloor - 2\left\lfloor\dfrac{\lfloor d\sqrt{r}\rfloor}{2}\right\rfloor\right) \\
    &= n - 2\sum_{d=1}^n\lfloor d\sqrt{r}\rfloor + 4 \sum_{d=1}^n\left\lfloor\dfrac{d\sqrt{r}}{2}\right\rfloor\\
    &= n - 2f(1,0,1,n) + 4f(1,0,2,n).
    \end{aligned}
    $$
    
    Here the function $f$ has the form
    
    $$
    f(a,b,c,n) = \sum_{i=1}^n\left\lfloor\dfrac{a\sqrt{r}+b}{c}i\right\rfloor.
    $$
    
    Unlike the algorithm in the main text, the slope here is no longer rational. Let the slope be
    
    $$
    k = \dfrac{a\sqrt{r}+b}{c}.
    $$
    
    Again there are two cases. If $k\ge 1$, then
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=1}^n \lfloor ki\rfloor = \sum_{i=1}^n \lfloor(k-\lfloor k\rfloor)i\rfloor + \lfloor k\rfloor \sum_{i=1}^ni\\
    &= \lfloor k\rfloor\dfrac{n(n+1)}{2} + f(a,b-c\lfloor k\rfloor,c,n).
    \end{aligned}
    $$
    
    This reduces the problem to a slope less than one. If $k<1$, let $m=\lfloor nk\rfloor$. Then
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=1}^n \lfloor ki\rfloor = \sum_{i=1}^n\sum_{j=1}^m[j\le\lfloor ki\rfloor]\\
    &= \sum_{j=1}^m\sum_{i=1}^n[i>\lfloor k^{-1}j\rfloor] = nm - \sum_{j=1}^m\sum_{i=1}^n[i\le\lfloor k^{-1}j\rfloor].
    \end{aligned}
    $$
    
    In this derivation, swapping $i$ and $j$ is simpler than in the main text, because the line $y=kx$ passes through no lattice points other than the origin. The key is to write the swapped sum in the form $f(a,b,c,n)$, which means finding $a',b',c'$ with
    
    $$
    k^{-1} = \dfrac{a'\sqrt{r}+b'}{c'}.
    $$
    
    This is not hard: rationalizing the denominator gives
    
    $$
    k^{-1} = \dfrac{c}{a\sqrt{r}+b} = \dfrac{ca\sqrt{r}-cb}{a^2r-b^2}.
    $$
    
    So
    
    $$
    a'=ca,~b'=-cb,~c'=a^2r-b^2.
    $$
    
    This means
    
    $$
    f(a,b,c,n) = nm - f(ca,-cb,a^2r-b^2,m).
    $$
    
    To avoid integer overflow, divide $a,b,c$ by their greatest common divisor each time. This computation is exactly the same as computing the continued fraction of $k$, so by [continued fraction theory](./continued-fraction.md#二次无理数), as long as $\gcd(a,b,c)=1$, the values always stay within the integer range. Also, although $(a,b,c,n)$ never overflows, under this problem's constraints $f(a,b,c,n)$ may exceed the range of $64$-bit integers. Letting it overflow naturally is fine and needs no extra handling; the final result is always in $[-n,n]$.
    
    Even though the slope never becomes zero, the algorithm still runs in $O(\log n)$, which is easy to see from the complexity argument above.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-2.cpp"
    ```

???+ example "[Fraction](https://www.luogu.com.cn/problem/P5179)"
    Given positive integers $a,b,c,d$, among all reduced fractions $p/q$ with $a/b<p/q<c/d$, find the one whose pair $(q,p)$ is lexicographically smallest.

??? note "Solution"
    This problem is also a classic application of the [Stern–Brocot tree](./stern-brocot.md); a solution can be found [here](./continued-fraction.md#连分数的树). Since it only depends on the recursive structure of fractions, it can also be solved in a Euclidean-like way, so it can be seen as an application of the Euclidean-like algorithm as well.
    
    If there is at least one natural number strictly between $a/b$ and $c/d$, we can directly take $(q,p)=(1,\lfloor a/b\rfloor+1)$. Otherwise, we must have
    
    $$
    \left\lfloor\dfrac{a}{b}\right\rfloor \le \dfrac{a}{b} <\dfrac{p}{q} <\dfrac{c}{d}\le\left\lfloor\dfrac{a}{b}\right\rfloor+1.
    $$
    
    From this inequality, the integer part of $p/q$ must be $\lfloor a/b\rfloor$. Remove this integer part and take reciprocals of everything to determine the fractional part. This is exactly the [standard method](./continued-fraction.md#连分数表示的求法) for finding the continued fraction of $p/q$. If the final answer is $p/q$, the time complexity is $O(\log\min\{p,q\})$.
    
    There is one subtle point: is the lexicographically smallest fraction after taking reciprocals the same as the lexicographically smallest one before? In other words, among fractions $p/q$ with $a/b<p/q<c/d$, is the one with the smallest $(q,p)$ also the one with the smallest $(p,q)$? Suppose not: let $p/q$ have the smallest $(q,p)$, but $r/s\neq p/q$ have the smallest $(r,s)$. Then we must have $r<p$ and $q<s$. But this means
    
    $$
    \dfrac{a}{b} < \dfrac{r}{s} < \dfrac{r}{q} < \dfrac{p}{q} < \dfrac{c}{d}.
    $$
    
    So $r/q$ is strictly smaller than the current solution in either lexicographic order, which is a contradiction. Therefore the algorithm above is correct.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-3.cpp"
    ```

## Universal Euclidean algorithm

The derivations for the Euclidean-like algorithm in the previous section are often tedious, and the sums it can handle are mainly those that turn into counting (weighted) lattice points under a line. This section covers a more general method that abstracts the process further, so it can solve more problems. That is why it is called the universal Euclidean algorithm. It also uses the recursive structure of fractions, but its way of reducing the problem is a bit different from the Euclidean-like algorithm.

Again consider the most classic sum:

$$
f(a,b,c,n)=\sum_{i=1}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,
$$

where $a,b,c,n$ are all positive integers.

### Reformulating the problem

Let the segment with parameters $(a,b,c,n)$ be

$$
y = \frac{ax+b}{c},~0< x\le n.
$$

For this segment, define a string $S$ of $U$s and $R$s, called the **operation sequence**, as follows:

-   The string consists of exactly $n$ $R$s and $m=\lfloor(an+b)/c\rfloor$ $U$s;
-   The number of $U$s before the $i$-th $R$ is exactly $\lfloor(ai+b)/c\rfloor$, for $i=1,\cdots,n$.

Geometrically, this is roughly: start at the origin, and every time the segment crosses a vertical grid line going right, write an $R$; every time it crosses a horizontal grid line going up, write a $U$. See the figure below:

![](./images/euclidean-universal.svg)

Of course, this definition has a few special cases to handle:

-   When passing through a lattice point (crossing up and right at the same time), write $U$ first, then $R$;
-   At the start of the string, besides the number of horizontal lines crossed in $(0,1]$, add $\lfloor b/c\rfloor$ extra $U$s;
-   The string must not end with extra $U$s.

If anything about the geometric description is unclear, refer to the algebraic definition above. The geometric description helps in understanding the algorithm below.

The basic idea of the universal Euclidean algorithm is to treat $U$ and $R$ in the operation sequence as elements of some [monoid](../algebra/basic.md#群), and the whole operation sequence as a product of monoid elements. The final answer is related to this product.

For example, in this problem, we can define a state vector $v = (1,y,\sum y)$ representing the current state after starting at the origin and crossing some grid lines. The first component is a constant, the second is the $y$-coordinate, and the third is the sum we want. Initially $v=(1,0,0)$. Each time we cross a grid line going up, the $y$-coordinate increases by one, which is the same as right-multiplying the state vector by the matrix

$$
U = \begin{pmatrix}1 & 1 & 0 \\ 0 & 1 & 0 \\ 0 & 0 & 1\end{pmatrix}.
$$

Each time we cross a grid line going right, the sum adds the current $y$-coordinate, which is the same as right-multiplying the state vector by the matrix

$$
R = \begin{pmatrix}1 & 0 & 0 \\ 0 & 1 & 1 \\ 0 & 0 & 1\end{pmatrix}.
$$

So the final state is the product $(1,0,0)S$, where $S$ is understood as the product of the matrices above. The answer is the third component of the final state.

Instead of defining monoid elements as matrices, we can also define them as the contribution of a piece of the operation sequence to the final result, and define the product of operations as merging the contributions of two pieces.

In this problem, we can define the contribution of each piece as $(x,y,\sum y)$. To make this notation precise, think of each component as a function of the operation sequence: for an operation sequence $S$, its contribution is $(x(S),y(S),(\sum y)(S))$. Here $x(S)$ and $y(S)$ are the numbers of $R$s and $U$s in $S$, i.e., the number of times the segment crosses grid lines going right and going up. The summation in the last component is defined in general as follows: for a function $f(S)$ of operation sequences, define $(\sum f)(S)$, also written $\sum_S f$, as

$$
\sum_S f := \sum\{f(S_{[1,r]}):S_r=R\}.
$$

Here $S_r$ is the $r$-th character of $S$, and $S_{[1,r]}$ is the prefix of $S$ made of its first $r$ characters. In other words, this sum runs over all prefixes of $S$ that end in $R$. For example,

$$
\sum_S 1 = x,~ \sum_S x = \dfrac{1}{2}x(x+1).
$$

As another example, $\sum y$ adds up, at each crossing to the right, the number of upward crossings so far. For the whole operation sequence, the values of $y$ at the prefixes ending in $R$ are exactly the values $\lfloor(ai+b)/c\rfloor$ for $i=1,\cdots,n$. So $\sum y$ over the whole operation sequence is exactly the quantity we want.

The two operations are $U=(0,1,0)$ and $R=(1,0,0)$. The product of two elements $(x_1,y_1,s_1)$ and $(x_2,y_2,s_2)$ is defined as

$$
(x_1,y_1,s_1)\cdot (x_2,y_2,s_2) = (x_1+x_2,y_1+y_2,s_1+s_2+x_2y_1).
$$

The merged value of the last component comes from:

$$
\sum_{S_1+S_2}y = \sum_{S_1}y + \sum_{S_2}(y+y_1) = \sum_{S_1}y + \sum_{S_2}y + y_1\sum_{S_2}1 = s_1+s_2+x_2y_1.
$$

It is easy to check that this multiplication is associative with identity $(0,0,0)$, so these elements form a monoid under it. The answer is the third component of the product.

Both approaches give the correct result. But the matrix version keeps more redundant information and has a larger constant factor, so the second approach is more practical for real problems.

### How it works

Unlike the Euclidean-like algorithm, which reduces the whole problem at once, the universal Euclidean algorithm reduces the problem by merging operations in batches. Write the product of the operations in the string as

$$
F(a,b,c,n,U,R).
$$

The reduction goes as follows:

-   When $b\ge c$, the operation sequence starts with $\lfloor b/c\rfloor$ $U$s. Compute their product directly and remove these $U$s from the sequence. Now the number of $U$s before the $i$-th $R$ is

    $$
    \left\lfloor\dfrac{ai+b}{c}\right\rfloor - \left\lfloor\dfrac{b}{c}\right\rfloor = \left\lfloor\dfrac{ai+(b\bmod c)}{c}\right\rfloor.
    $$

    So this changes the segment parameters from $(a,b,c,n)$ to $(a,b\bmod c,c,n)$. Hence in this case,

    $$
    F(a,b,c,n,U,R) = U^{\lfloor b/c\rfloor}F(a,b\bmod c,c,n,U,R).
    $$

-   When $a\ge c$, every $R$ in the operation sequence has at least $\lfloor a/c\rfloor$ $U$s in front of it, and these can be merged into the $R$. That is, we can replace $R$ with $U^{\lfloor a/c\rfloor}R$. In the merged string, the number of $U$s before the $i$-th $R$ is

    $$
    \left\lfloor\dfrac{ai+b}{c}\right\rfloor - \left\lfloor\dfrac{a}{c}\right\rfloor i = \left\lfloor\dfrac{(a\bmod c)i+b}{c}\right\rfloor.
    $$

    So this changes the segment parameters from $(a,b,c,n)$ to $(a\bmod c,b,c,n)$. Hence in this case,

    $$
    F(a,b,c,n,U,R) = F(a\bmod c,b,c,n,U,U^{\lfloor a/c\rfloor}R).
    $$

-   In the remaining case, we swap the axes. This basically swaps $U$ and $R$, but the parameters of the swapped segment need careful computation. From the definition of the operation sequence, we need coefficients $(a',b',c',n')$ such that, in the original operation sequence, the number of $R$s before the $j$-th $U$ is exactly $\lfloor(a'j+b')/c'\rfloor$, and there are $n'$ $U$s in total. By definition,

    $$
    n'=\left\lfloor\dfrac{an+b}{c}\right\rfloor = m,
    $$

    and the number of $R$s before the $j$-th $U$ is the largest $i$ such that

    $$
    \begin{aligned}
    \left\lfloor\dfrac{ai+b}{c}\right\rfloor < j 
    &\iff \dfrac{ai+b}{c} < j \iff i < \dfrac{cj-b}{a} \\
    &\iff i < \left\lceil\dfrac{cj-b}{a}\right\rceil = \left\lfloor\dfrac{cj-b - 1}{a}\right\rfloor + 1.
    \end{aligned}
    $$

    So $i = \lfloor(cj-b-1)/a\rfloor$. This derivation is similar to the one for the Euclidean-like algorithm above and also uses properties of the floor and ceiling functions.

    There are two details to handle:

    -   The intercept $-(b+1)/a$ is negative. If we shift the segment one unit to the left, the intercept becomes nonnegative, since $(c-b-1)/a\ge 0$ always holds. So we can pull out the first piece $R^{\lfloor(c-b-1)/a\rfloor}U$ before swapping, and swap $U$ and $R$ only in the rest of the sequence;
    -   After swapping $U$ and $R$, there would be extra $U$s at the end. So before swapping, we also pull out the last run of $R$s, and swap $U$ and $R$ only in the rest of the sequence. This run has $n-\lfloor(cm-b-1)/a\rfloor$ $R$s.

    After removing these characters from both ends, the number of $R$s before the $j$-th $U$ becomes:

    $$
    \left\lfloor\dfrac{c(j+1)-b-1}{a}\right\rfloor - \left\lfloor\dfrac{c-b-1}{a}\right\rfloor = \left\lfloor\dfrac{cj+(c-b-1)\bmod a}{a}\right\rfloor.
    $$

    Recall that the number of $U$s in the sequence before swapping is $m = \lfloor(an+b)/c\rfloor$. Shifting one unit to the left requires at least one $U$ before swapping, that is, $m>0$. Based on this, there are two cases:

    -   When $m>0$, after handling the two points above, the sequence with $U$ and $R$ swapped is exactly a valid sequence for the segment with parameters $(c,(c-b-1)\bmod a,a,m-1)$. So

        $$
        F(a,b,c,n,U,R) = R^{\lfloor(c-b-1)/a\rfloor}UF(c,(c-b-1)\bmod a,a,m-1,R,U)R^{n-\lfloor(cm-b-1)/a\rfloor}.
        $$

    -   In particular, when $m=0$, the sequence before swapping contains only $n$ $R$s. There is nothing to swap, and we can return directly:

        $$
        F(a,b,c,n,U,R) = R^n.
        $$

        Unlike in the Euclidean-like algorithm, this special case must be handled separately in the universal Euclidean algorithm; otherwise negative powers would come up and the result would be wrong.

With these cases, the problem can be solved recursively.

Assume one multiplication of monoid elements takes $O(1)$ time. If all powers of these elements are computed with [binary exponentiation](../binary-exponentiation.md), the total complexity of the algorithm is $O(\log\max\{a,c\}+\log(b/c))$[^complexity].

??? note "Complexity explanation"
    Compared with the (Euclidean-like) Euclidean algorithm, the universal Euclidean algorithm only adds the binary exponentiation steps. The rest of the computation has the same complexity as the Euclidean-like algorithm, which we already showed is $O(\log\min\{a,c,n\})$. Now we need the total cost of the binary exponentiations.
    
    Except in the first round, we always have $b<c$, so each of these rounds involves three binary exponentiations, with total cost:
    
    $$
    O\left(\log\left\lfloor\dfrac{a}{c}\right\rfloor+\log\left\lfloor\dfrac{c-b_1-1}{a_1}\right\rfloor+\log\left(n-\left\lfloor\dfrac{cm-b_1-1}{a_1}\right\rfloor\right)\right),
    $$
    
    where $a_1=a\bmod c$, $b_1=b\bmod c$, and $m=\lfloor(a_1n+b_1)/c\rfloor$. The last two terms can be bounded as follows:
    
    $$
    \begin{aligned}
    \dfrac{c-b_1-1}{a_1} &\le \dfrac{c}{a_1},\\
    n-\left\lfloor\dfrac{cm-b_1-1}{a_1}\right\rfloor &\le n - \dfrac{cm-b_1-1}{a_1} + 1 \\
    &\le n - \dfrac{c((a_1n+b_1)/c-1)-b_1-1}{a_1} +1 \\
    &= \dfrac{c+1}{a_1}+1.
    \end{aligned}
    $$
    
    So both terms are $O(\log(c/a_1))$.
    
    In each round, the segment parameters change from $(a,\cdot,c,\cdot)$ to $(c,\cdot,a\bmod c,\cdot)$, and the total time of the round is
    
    $$
    O\left(\log\dfrac{a}{c}+\log\dfrac{c}{a\bmod c}\right).
    $$
    
    Over all rounds of recursion, these terms telescope, so the total is $O(\log a+\log c)=O(\log\max\{a,c\})$.
    
    Finally, adding the cost $O(\log(b/c))$ of the binary exponentiation $U^{\lfloor b/c\rfloor}$ in the first round, the total complexity is $O(\log\max\{a,c\}+\log(b/c))$.

The universal Euclidean algorithm can be written as a single template. For a specific problem, you only need to change the implementation of the template type `T`.

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-4.cpp:euclidean"
    ```

Using the universal Euclidean algorithm, the template problem can be implemented as follows:

??? example "Template problem implementation ([Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear))"
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-4.cpp:full-text"
    ```

### Example problems

???+ example "[[Template] Euclidean-like Algorithm](https://www.luogu.com.cn/problem/P5170)"
    There are multiple queries. Given positive integers $a,b,c,n$, find
    
    $$
    \begin{aligned}
    f(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    g(a,b,c,n) &= \sum_{i=0}^ni\left\lfloor \frac{ai+b}{c} \right\rfloor,\\
    h(a,b,c,n) &= \sum_{i=0}^n\left\lfloor \frac{ai+b}{c} \right\rfloor^2.
    \end{aligned}
    $$

??? note "Solution 2"
    To use the universal Euclidean template, first handle the $i=0$ term separately. The rest can be seen as computing $\sum y,\sum xy,\sum y^2$ for the segment with parameters $(a,b,c,n)$. As explained in the main text, there are two ways to turn the operation sequence into monoid elements.
    
    **Matrix approach**: define the state vector as $(1,x,y,xy,y^2,\sum y,\sum xy,\sum y^2)$. The initial state is $(1,0,0,0,0,0,0,0)$, and the two operations are
    
    $$
    U =
    \begin{pmatrix}
    1 & 0 & 1 & 0 & 1 & 0 & 0 & 0 \\
    0 & 1 & 0 & 1 & 0 & 0 & 0 & 0 \\
    0 & 0 & 1 & 0 & 2 & 0 & 0 & 0 \\
    0 & 0 & 0 & 1 & 0 & 0 & 0 & 0 \\
    0 & 0 & 0 & 0 & 1 & 0 & 0 & 0 \\
    0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 
    \end{pmatrix},~
    R = 
    \begin{pmatrix}
    1 & 1 & 0 & 0 & 0 & 0 & 0 & 0 \\
    0 & 1 & 0 & 0 & 0 & 0 & 0 & 0 \\
    0 & 0 & 1 & 1 & 0 & 1 & 1 & 0 \\
    0 & 0 & 0 & 1 & 0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 0 & 1 & 0 & 0 & 1 \\
    0 & 0 & 0 & 0 & 0 & 1 & 0 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 1 & 0 \\
    0 & 0 & 0 & 0 & 0 & 0 & 0 & 1 
    \end{pmatrix}.
    $$
    
    The answer is the last three components of the vector obtained by right-multiplying the initial state by the product of these operation matrices.
    
    This approach has a huge constant factor and does not pass this problem. The details are given here only to help understanding.
    
    **Merging contributions**: define the contribution of a piece of the operation sequence as $(x,y,\sum y,\sum xy,\sum y^2)$. The two operations are
    
    $$
    U = (0,1,0,0,0),~ R = (1,0,0,0,0).
    $$
    
    When merging contributions,
    
    $$
    \begin{aligned}
    \sum_{S_1+S_2} y 
    &= \sum_{S_1}y + \sum_{S_2}(y+y_1) = \sum_{S_1}y + \sum_{S_2}y + x_2y_1,\\
    \sum_{S_1+S_2} xy
    &= \sum_{S_1}xy + \sum_{S_2}(x+x_1)(y+y_1) \\
    &= \sum_{S_1}xy + \sum_{S_2}xy + x_1\sum_{S_2}y + y_1\sum_{S_2}x + x_1y_1\sum_{S_2}1\\
    &= \sum_{S_1}xy + \sum_{S_2}xy + x_1\sum_{S_2}y + \dfrac{1}{2}x_2(x_2+1)y_1 + x_1x_2y_1,\\
    \sum_{S_1+S_2}y^2
    &= \sum_{S_1}y^2 + \sum_{S_2}(y+y_1)^2 \\
    &= \sum_{S_1}y^2 + \sum_{S_2}y^2 + 2y_1\sum_{S_2}y + y_1^2\sum_{S_2}1  \\
    &= \sum_{S_1}y^2 + \sum_{S_2}y^2 + 2y_1\sum_{S_2}y + x_2y_1^2.
    \end{aligned}
    $$
    
    So the product of operations should be defined as
    
    $$
    \begin{aligned}
    &(x_1,y_1,s_1,t_1,u_1)\cdot(x_2,y_2,s_2,t_2,u_2)\\
    &= (x_1+x_2,y_1+y_2,s_1+s_2+x_2y_1,\\
    &\qquad t_1+t_2+x_1s_2+(1/2)x_2(x_2+1)y_1+x_1x_2y_1,\\
    &\qquad u_1+u_2+2y_1s_2+x_2y_1^2).
    \end{aligned}
    $$
    
    Checking it directly is tedious, but the contribution vectors defined above do form a monoid under this multiplication, with identity $(0,0,0,0,0)$.
    
    In general,
    
    $$
    \begin{aligned}
    \sum_{S_1+S_2}x^ry^s &= \sum_{S_1}x^ry^s + \sum_{S_2}(x+x_1)^r(y+y_1)^s \\
    &= \sum_{S_1}x^ry^s + \sum_{i=0}^r\sum_{j=0}^s\binom{r}{i}\binom{s}{j}x_1^{r-i}y_1^{s-j}\sum_{S_2}x^iy^j.
    \end{aligned}
    $$
    
    As long as the contributions of all lower powers are maintained, the general sum can be computed.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-5.cpp"
    ```

???+ example "[\[Tsinghua Training Camp 2014\] Sum](https://www.luogu.com.cn/problem/P5172)"
    There are multiple queries. Given positive integers $n$ and $r$, find
    
    $$
    \sum_{d=1}^n(-1)^{\lfloor d\sqrt{r}\rfloor}.
    $$

??? note "Solution 2"
    First, the case where $r$ is a perfect square is handled exactly as before, so we skip it. Here we only consider $r$ that is not a perfect square.
    
    There are many ways to apply the universal Euclidean algorithm to this problem. For example, we can define a linear map for each operation:
    
    $$
    U(x) = -x,~ R(x) = x + 1.
    $$
    
    The product of operations is the composition of linear maps. The answer is then the value at $x=0$ of the composition of the maps for the operation sequence.
    
    We can also define the contribution of each piece of the operation sequence as $((-1)^y,\sum(-1)^y)$. Then the two operations are
    
    $$
    U = (-1,0),~ R = (1,1).
    $$
    
    Contributions merge as
    
    $$
    (u_1,v_1)\cdot(u_2,v_2) = (u_1u_2,v_1+u_1v_2).
    $$
    
    It is easy to check that all operations form a monoid under this multiplication, with identity $(1,0)$. The answer is the second component of the product of all elements.
    
    The two approaches agree: if we write a linear map as $f(x)=ux+v$, then the way the coefficients change under composition is exactly the multiplication above. In other words, the two monoids are isomorphic.
    
    In this problem, the segment parameters are $(k,n)$, where $k\in\mathbf R$ is the slope of the line. Let $F(k,n,U,R)$ be the product of the operation sequence. Then we have the following recursive algorithm:
    
    -   If $k\ge 1$, every $R$ in the operation sequence has at least $\lfloor k\rfloor$ $U$s before it, so
    
        $$
        F(k,n,U,R) = F(k-\lfloor k\rfloor,n,U,U^{\lfloor k\rfloor} R).
        $$
    -   If $k<1$, swap $U$ and $R$ in the operation sequence and drop the trailing $U$s (the $R$s before the swap). Let $m=\lfloor kn\rfloor$. Then
    
        $$
        F(k,n,U,R) = F(k^{-1},m,R,U)R^{n-\lfloor k^{-1}m\rfloor}.
        $$
    
    In this algorithm, the iteration on $k$ is really computing the continued fraction expansion of $\sqrt{r}$. For this we can use the [PQa algorithm](./pell-equation.md#pqa-算法). Computing the continued fraction can be done at the same time as the iterations of the universal Euclidean algorithm.
    
    As with the Euclidean-like algorithm, the complexity is still $O(\log n)$.
    
    ```cpp
    --8<-- "docs/math/code/euclidean/euclidean-6.cpp"
    ```

## Exercises

Template problems:

-   [Library Checker - Sum of Floor of Linear](https://judge.yosupo.jp/problem/sum_of_floor_of_linear)
-   [Luogu P5170 [Template] Euclidean-like Algorithm](https://www.luogu.com.cn/problem/P5170)
-   [Luogu P5171 Earthquake](https://www.luogu.com.cn/problem/P5171)
-   [Luogu P5172 \[Tsinghua Training Camp 2014\] Sum](https://www.luogu.com.cn/problem/P5172)
-   [Luogu P4132 \[BJOI2012\] The Incomputable Equation](https://www.luogu.com.cn/problem/P4132)
-   [LOJ 138. Euclidean-like Algorithm](https://loj.ac/p/138)
-   [LOJ 6440. Universal Euclidean](https://loj.ac/p/6440)
-   [Luogu P5179 Fraction](https://www.luogu.com.cn/problem/P5179)
-   [Codeforces 1182 F. Maximum Sine](https://codeforces.com/problemset/problem/1182/F)

Applications:

-   [Luogu P4433 \[COCI 2009/2010 #1\] ALADIN](https://www.luogu.com.cn/problem/P4433)
-   [AtCoder Beginner Contest 372 G - Ax + By < C](https://atcoder.jp/contests/abc372/tasks/abc372_g)
-   [AtCoder Beginner Contest 313 G - Redistribution of Piles](https://atcoder.jp/contests/abc313/tasks/abc313_g)
-   [AtCoder Beginner Contest 283 Ex - Popcount Sum](https://atcoder.jp/contests/abc283/tasks/abc283_h)
-   [Codeforces 1098 E. Fedya the Potter](https://codeforces.com/problemset/problem/1098/E)
-   [Codeforces 868 G. El Toll Caves](https://codeforces.com/problemset/problem/868/G)

## References and notes

[^complexity]: In typical problems, $b$ is of the same order as $a$, so the $O(\log(b/c))$ term can be ignored. Moreover, if one round of Euclidean-like remainder-taking is done before calling the universal Euclidean algorithm, removing the effect of $b$, the binary exponentiation for this term can be avoided altogether. This is because in typical problems, the initial form of $U$ is special and its powers have a simpler closed form, so binary exponentiation is not needed. For example, in the main text, $U^{\lfloor b/c\rfloor}$ is just $U$ with its single off-diagonal $1$ replaced by $\lfloor b/c\rfloor$, with no binary exponentiation needed.
