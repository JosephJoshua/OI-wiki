## Definition

Prerequisite: [Order and primitive roots](./primitive-root.md).

The discrete logarithm is defined much like the ordinary logarithm. Take a positive integer modulus $m$ that has a primitive root, and let $g$ be one of its primitive roots. For an integer $a$ with $(a,m)=1$, we know there is a unique integer $0\leq k<\varphi(m)$ such that

$$
g^k\equiv a\pmod m
$$

We call this $k$ the discrete logarithm of $a$ to the base $g$ modulo $m$, written $k=\operatorname{ind}_g a$, or just $\operatorname{ind} a$ when there is no risk of confusion.

Clearly $\operatorname{ind}_g 1=0$ and $\operatorname{ind}_g g=1$.

## Properties

Discrete logarithms share many properties with ordinary logarithms.

???+ note "Properties"
    Let $g$ be a primitive root modulo $m$, and $(a,m)=(b,m)=1$. Then:
    
    1.  $\operatorname{ind}_g(ab)\equiv\operatorname{ind}_g a+\operatorname{ind}_g b\pmod{\varphi(m)}$
    
        Hence $(\forall n\in\mathbf{N}),~~\operatorname{ind}_g a^n\equiv n\operatorname{ind}_g a\pmod{\varphi(m)}$
    2.  If $g_1$ is also a primitive root modulo $m$, then $\operatorname{ind}_g a\equiv\operatorname{ind}_{g_1}a \cdot \operatorname{ind}_g g_1\pmod{\varphi(m)}$
    3.  $a\equiv b\pmod m\iff \operatorname{ind}_g a=\operatorname{ind}_g b$

???+ note "Proof"
    1.  $g^{\operatorname{ind}_g(ab)}\equiv ab\equiv g^{\operatorname{ind}_g a}g^{\operatorname{ind}_g b}\equiv g^{\operatorname{ind}_g a+\operatorname{ind}_g b}\pmod m$
    2.  Let $x=\operatorname{ind}_{g_1}a$, so $a\equiv g_1^x\pmod m$. Also let $y=\operatorname{ind}_g g_1$, so $g_1\equiv g^y\pmod m$.
    
        Therefore $a\equiv g^{xy}\pmod m$, that is, $\operatorname{ind}_g a\equiv xy\equiv\operatorname{ind}_{g_1}a \cdot \operatorname{ind}_g g_1\pmod{\varphi(m)}$
    3.  Note that
    
        $$
        \begin{aligned}
            \operatorname{ind}_g a=\operatorname{ind}_g b&\iff \operatorname{ind}_g a\equiv\operatorname{ind}_g b\pmod{\varphi(m)}\\
            &\iff g^{\operatorname{ind}_g a}\equiv g^{\operatorname{ind}_g b}\pmod m\\
            &\iff a\equiv b\pmod m
        \end{aligned}
        $$

## Baby-step giant-step

No polynomial-time classical algorithm for the discrete logarithm problem is currently known (the input size of the problem is the number of bits in the input). In cryptography, many asymmetric encryption schemes are built on this fact, such as [Ed25519](https://en.wikipedia.org/wiki/EdDSA#Ed25519).

In competitive programming, BSGS (baby-step giant-step) is the usual way to solve discrete logarithm problems. Formally, for $a,b,m\in\mathbf{Z}^+$, the algorithm solves

$$
a^x \equiv b \pmod m
$$

in $O(\sqrt{m})$ time, where $a\perp m$. The solution $x$ satisfies $0 \le x < m$. (Note that $m$ need not be prime.)

### How it works

Let $x = A \left \lceil \sqrt m \right \rceil - B$, where $0\le A,B \le \left \lceil \sqrt m \right \rceil$. Then $a^{A\left \lceil \sqrt m \right \rceil -B} \equiv b \pmod m$, which rearranges to $a^{A\left \lceil \sqrt m \right \rceil} \equiv ba^B \pmod m$.

We know $a$ and $b$, so we can first compute every value of the right-hand side $ba^B$ by enumerating $B$, and store them in a `hash`/`map`. Then we compute $a^{A\left \lceil \sqrt m \right \rceil}$ for each $A$ in turn and check whether some $ba^B$ equals it. This gives us every $x$, with $x=A \left \lceil \sqrt m \right \rceil - B$.

Since $A$ and $B$ are both less than $\left \lceil \sqrt m \right \rceil$, the time complexity is $\Theta\left  (\sqrt m\right )$, with an extra $\log$ factor if you use `map`.

??? note "Why $a$ must be coprime to $m$"
    What we find are $A$ and $B$, and we need to be sure that $a^{A\left \lceil \sqrt m \right \rceil} \equiv ba^B \pmod m$ implies $a^{A\left \lceil \sqrt m \right \rceil -B} \equiv b \pmod m$. The second is obtained by dividing both sides of the first by $a^B$, so we need $a^B \perp m$, that is, $a\perp m$.

## Extended BSGS

For $a,b,m\in\mathbf{Z}^+$, solve

$$
a^x\equiv b\pmod m
$$

where $a$ and $m$ are not necessarily coprime.

When $(a, m)=1$, $a$ has an inverse modulo $m$, so plain BSGS works. So we try to make them coprime.

Specifically, let $d_1=(a, m)$. If $d_1\nmid b$, the equation has no solution. Otherwise, divide the whole equation by $d_1$ to get

$$
\frac{a}{d_1}\cdot a^{x-1}\equiv \frac{b}{d_1}\pmod{\frac{m}{d_1}}
$$

If $a$ and $\frac{m}{d_1}$ are still not coprime, divide again. Let $d_2=\left(a, \frac{m}{d_1}\right)$. If $d_2\nmid \frac{b}{d_1}$, there is no solution; otherwise divide by $d_2$ to get

$$
\frac{a^2}{d_1d_2}\cdot a^{x-2}≡\frac{b}{d_1d_2} \pmod{\frac{m}{d_1d_2}}
$$

Keep going in the same way until $a\perp \dfrac{m}{d_1d_2\cdots d_k}$.

Let $D=\prod_{i=1}^kd_i$. The equation becomes:

$$
\frac{a^k}{D}\cdot a^{x-k}\equiv\frac{b}{D} \pmod{\frac{m}{D}}
$$

Since $a\perp\dfrac{m}{D}$, it follows that $\dfrac{a^k}{D}\perp \dfrac{m}{D}$. So $\dfrac{a^k}{D}$ has an inverse, and we can move it to the right-hand side. Now it is an ordinary BSGS problem: solve for $x-k$, then add $k$ to get the solution of the original equation.

Note that the solution may be less than or equal to $k$. To handle this, before removing factors, do a $\Theta(k)$ enumeration that checks $a^i\equiv b \pmod m$ directly.

## Fast discrete logarithm with value-range preprocessing

The BSGS algorithm above takes $O(\sqrt m)$ time per query, which is slow when there are many queries. If every query uses the same fixed prime modulus $p$, there is a faster algorithm based on preprocessing over the range of values.

We know $\operatorname{ind}_g(ab)\equiv\operatorname{ind}_g a+\operatorname{ind}_g b\pmod{p-1}$, so we could compute discrete logarithms with BSGS only for primes, and turn the discrete logarithm of a composite into a sum of known discrete logarithms of primes using this formula. That is still not fast enough, so we preprocess only some of the discrete logarithms: specifically, those of $1$ to $L = \lfloor\sqrt p\rfloor + 1$. Note that here the BSGS block length $B$ **must not be** $O(\sqrt{L})$. The BSGS preprocessing (inserting into the hash table) costs $O(B)$, and there are $O(\pi(L))$ queries in total, so the total time complexity is $O\left(B+\dfrac{\pi(L)p}{B}\right)$, which is optimal with $B=O(\sqrt{\pi(L)p})$. By the [prime number theorem](./prime.md), $\pi(n)\sim\dfrac{n}{\log n}$, so the total preprocessing time balances to $O\left(\dfrac{p^{3/4}}{\log^{1/2} p}\right)$.

Next, how to answer a query. Suppose we want $\operatorname{ind}_g y$. If $y\le L$, return it directly. Otherwise write $p=vy+r$, so $v=\left\lfloor\dfrac{p}{y}\right\rfloor<L$, $r=p\bmod y$, and $y=\dfrac{p-r}{v}$. Then

$$
\begin{aligned}
\operatorname{ind}_g y &\equiv \operatorname{ind}_g (p-r)-\operatorname{ind}_g v\\
&\equiv \operatorname{ind}_g (-r)-\operatorname{ind}_g v\\
&\equiv \operatorname{ind}_g (p-1)+\operatorname{ind}_g r-\operatorname{ind}_g v \pmod{p-1}.
\end{aligned}
$$

Note that $\operatorname{ind}_g (p-1)=(p-1)/2$, so we only need to compute the discrete logarithm of $r$ recursively.

We can also write $y$ another way. Since $p=vy+r=(v+1)y+r-y$, we have $y=\dfrac{p-r+y}{v+1}$, so

$$
\operatorname{ind}_g y\equiv \operatorname{ind}_g (y-r)-\operatorname{ind}_g (v+1) \pmod{p-1}.
$$

Here $v+1 \le L$, so we only need to compute the discrete logarithm of $y-r$ recursively.

Combining the two, we have $\min\{r,y-r\}\le \dfrac{y}{2}$, so recursing on the smaller one gives $O(\log p)$ time per query.

This gives an algorithm with $O\left(\dfrac{p^{3/4}}{\log^{1/2} p}\right)$ preprocessing and $O(\log p)$ per query.

??? example "[Luogu P11175 [Template] Fast Discrete Logarithm with Value-Range Preprocessing](https://www.luogu.com.cn/problem/P11175)"
    ```cpp
    --8<-- "docs/math/code/discrete-logarithm/discrete-logarithm-1.cpp"
    ```

## Exercises

-   [SPOJ MOD](https://www.spoj.com/problems/MOD/) template
-   [SDOI2013 Random Number Generator](https://www.luogu.com.cn/problem/P3306)
-   [SGU261 Discrete Roots](https://codeforces.com/problemsets/acmsguru/problem/99999/261) template
-   [SDOI2011 Calculator](https://loj.ac/problem/10214) template
-   [Luogu P4195 [Template] exBSGS / SPOJ3105 Mod](https://www.luogu.com.cn/problem/P4195) template
-   [Codeforces - Lunar New Year and a Recursive Sequence](https://codeforces.com/contest/1106/problem/F)
-   [LOJ6542 Discrete Logarithm](https://loj.ac/problem/6542) index calculus method, not a template problem

**Parts of this page and its code are translated from the article [Дискретное извлечение корня](http://e-maxx.ru/algo/discrete_root) and its English translation [Discrete Root](https://cp-algorithms.com/algebra/discrete-root.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

## References

1.  [Discrete logarithm - Wikipedia](https://en.wikipedia.org/wiki/Discrete_logarithm)
2.  Pan Chengdong, Pan Chengbiao. *Elementary Number Theory* (in Chinese).
3.  Feng Keqin. *Elementary Number Theory and Its Applications* (in Chinese).
