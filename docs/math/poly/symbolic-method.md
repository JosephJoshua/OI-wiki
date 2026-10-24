The symbolic method is a way to quickly turn combinatorial objects into generating functions. We look at specific operations defined on sets, and then derive the corresponding operations on generating functions.

We call $(\mathcal{A},\lvert \cdot \rvert)$ a combinatorial class (or just a class), where $\mathcal{A}$ is a set of combinatorial objects and the function $\lvert \cdot \rvert$ maps each combinatorial object to a non-negative integer; this function is usually called the size function. Note that this non-negative integer cannot be infinite. For example, for strings over the alphabet $\lbrace 0,1\rbrace$, we can use the length of the string as its size function; for trees or graphs we can use the number of nodes as the size function. This is not absolute: we might, for example, give certain special nodes size $0$.

This article is a simplified version of Chapter 1 of the book Analytic Combinatorics.

## The unlabeled setting

In the unlabeled setting we use ordinary generating functions (OGFs). For a set $\mathcal{A}$, its OGF is written

$$
A(z)=\sum_{\alpha\in\mathcal{A}}z^{\lvert \alpha \rvert}=\sum_{n\geq 0}a_nz^n
$$

By convention, we use letters from the same group for the generating function and other things belonging to the same class. For example, $a_n$ denotes $\lbrack z^n\rbrack A(z)$, the coefficient of $z^n$ in $A(z)$, and $\mathcal{A}_n$ denotes the set of objects in $\mathcal{A}$ whose size is $n$ (so $a_n=\operatorname{card}(\mathcal{A}_n)$, where $\operatorname{card}$ is the cardinality).

This article does not discuss admissibility; readers can refer to the references.

We now introduce two special combinatorial classes and combinatorial objects:

-   Let $\epsilon$ be the neutral object and $\mathcal{E}=\lbrace \epsilon \rbrace$ the neutral class. The neutral object has size $0$, and the OGF of the neutral class is $E(z)=1$.
-   Let $\circ$ or $\bullet$ be the atom object, and $\mathcal{Z}_{\circ}=\lbrace \circ\rbrace$ or $\mathcal{Z}_{\bullet}=\lbrace \bullet\rbrace$, or simply $\mathcal{Z}$, the atom class. The atom object has size $1$, and the OGF of the atom class is $Z(z)=z$.

When two combinatorial classes $\mathcal{A}$ and $\mathcal{B}$ are combinatorially isomorphic, we write $\mathcal{A}=\mathcal{B}$ or $\mathcal{A}\cong\mathcal{B}$; the latter notation is only used when the isomorphism is non-trivial.

We have

$$
\mathcal{A}\cong\mathcal{E}\times \mathcal{A}\cong\mathcal{A}\times\mathcal{E}
$$

where $\times$ is a binary operation meaning the Cartesian product of sets.

### The (disjoint) union construction

The union of classes $\mathcal{A}$ and $\mathcal{B}$ is written

$$
\mathcal{A}+\mathcal{B}=(\mathcal{E}_{1}\times\mathcal{A})+(\mathcal{E}_2\times\mathcal{B})
$$

Defined this way, it does not violate the set-theoretic requirement that the sets be disjoint. You can imagine coloring the objects in $\mathcal{A}$ red and the objects in $\mathcal{B}$ blue.

The corresponding OGF is

$$
A(z)+B(z)
$$

Consider

$$
A(z)+B(z)=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert} + \sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}=\sum_{n\geq 0}(a_n+b_n)z^n
$$

This corresponds to addition of formal power series.

### The Cartesian product construction

The Cartesian product of classes $\mathcal{A}$ and $\mathcal{B}$ is written

$$
\mathcal{A}\times \mathcal{B}=\left\lbrace (\alpha, \beta)\mid \alpha \in \mathcal{A},\beta\in\mathcal{B}\right\rbrace
$$

The corresponding OGF is

$$
A(z)\cdot B(z)
$$

We define the size of $(\alpha,\beta)$ as the sum of the sizes of its components. Then clearly also

$$
\gamma =(\alpha_1,\alpha_2,\dots ,\alpha_n)\implies \lvert \gamma\rvert =\lvert \alpha_1\rvert +\lvert \alpha_2\rvert +\cdots +\lvert \alpha_n\rvert
$$

So

$$
A(z)\cdot B(z)=\left(\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}\right)\left(\sum _ {\beta\in\mathcal{B}}z^{\lvert \beta\rvert}\right)=\sum _ {(\alpha, \beta)\in(\mathcal{A}\times \mathcal{B})}z^{\lvert \alpha\rvert +\lvert \beta\rvert}=\sum_{n\geq 0}\sum_{i+j=n}a_ib_jz^n
$$

This corresponds to multiplication of formal power series.

### The Sequence construction

The Sequence construction generates all possible combinations.

???+ note "Example"
    $$
    \begin{aligned}
    \operatorname{SEQ}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    \operatorname{SEQ}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a,b\rbrace +\lbrace (a,b)\rbrace + \lbrace(b,a)\rbrace +\lbrace (a,a)\rbrace +\lbrace (b,b)\rbrace\\
    &+\lbrace (a,b,a)\rbrace +\lbrace (a,b,b)\rbrace +\lbrace (a,a,b)\rbrace\\
    &+\lbrace (b,b,a)\rbrace +\lbrace (b,a,b)\rbrace +\lbrace (b,b,b)\rbrace +\lbrace (a,a,a)\rbrace +\lbrace (b,a,a)\rbrace\\
    &+\cdots
    \end{aligned}
    $$
    
    We can see that elements like $\lbrace (a,b)\rbrace ,\lbrace (b,a)\rbrace$, which differ only in the order of their components, are both generated. You can think of the Sequence construction as generating ordered combinations.

We define

$$
\operatorname{SEQ}(\mathcal{A})=\mathcal{E}+\mathcal{A}+(\mathcal{A}\times \mathcal{A})+(\mathcal{A}\times \mathcal{A}\times \mathcal{A})+\cdots
$$

and require $\mathcal{A}_0=\varnothing$, i.e. $\mathcal{A}$ has no objects of size $0$.

The corresponding OGF is

$$
Q(A(z))=1+A(z)+A(z)^2+A(z)^3+\cdots =\frac{1}{1-A(z)}
$$

where $Q$ is the Pólya quasi-inverse.

???+ note "Example: ordered rooted trees"
    We can use the Sequence construction to define ordered rooted trees, i.e. rooted trees where the order of the children matters. Let this combinatorial class be $\mathcal{T}$. A tree is a root node together with a Sequence of trees, that is,
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{SEQ}(\mathcal{T})
    $$
    
    The corresponding OGF is
    
    $$
    T(z)=\frac{z}{1-T(z)}
    $$
    
    The first few coefficients are `0 1 1 2 5 14 42 132 429 1430 4862 16796`; ignoring the constant term, this is OEIS [A000108](http://oeis.org/A000108).

### The Multiset construction

The Multiset construction generates all possible combinations, but does not distinguish the order of the component elements.

???+ note "Example"
    $$
    \begin{aligned}
    \operatorname{MSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    \operatorname{MSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace (a,a)\rbrace +\lbrace (a,a,a)\rbrace +\cdots\\
    &+\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace (a,a,b)\rbrace +\cdots \\
    &+\lbrace (b,b)\rbrace + \lbrace (a,b,b)\rbrace +\lbrace (a,a,b,b)\rbrace + \cdots\\
    &+\cdots
    \end{aligned}
    $$
    
    Notice that $\lbrace (b,a)\rbrace,\lbrace (a,b,a)\rbrace$ appear in $\operatorname{SEQ}(\lbrace a,b\rbrace)$ but not in $\operatorname{MSET}(\lbrace a,b\rbrace)$. You can think of Multiset as generating unordered combinations.

We define it by the recurrence

$$
\operatorname{MSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_n\rbrace)=\operatorname{MSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_{n-1}\rbrace)\times \operatorname{SEQ}(\lbrace \alpha_n\rbrace)
$$

that is,

$$
\operatorname{MSET}(\mathcal{A})=\prod _ {\alpha\in\mathcal{A}}\operatorname{SEQ}(\lbrace \alpha\rbrace)
$$

and require $\mathcal{A}_0=\varnothing$. Or, equivalently,

$$
\operatorname{MSET}(\mathcal{A})=\operatorname{SEQ}(\mathcal{A})/\mathbf{R}
$$

where $\mathbf{R}$ is an equivalence relation: $(\alpha_1,\dots,\alpha_n)\mathbf{R}(\beta_1,\dots,\beta_n)$ if and only if there is some permutation $\sigma$ such that $\beta_{j}=\alpha_{\sigma(j)}$ for all $j$.

The corresponding OGF is

$$
\operatorname{Exp}(A(z))=\prod _ {\alpha \in\mathcal{A}}\left(1-z^{\lvert \alpha \rvert}\right)^{-1}=\prod _ {n\geq 1}\left(1-z^n\right)^{-a_n}
$$

Note that

$$
\ln(1+z)=\frac{z}{1}-\frac{z^2}{2}+\frac{z^3}{3}-\cdots =\sum_{n\geq 1}\frac{(-1)^{n-1}z^n}{n}
$$

and $A(z)=\exp(\ln(A(z)))$, so

$$
\begin{aligned}
\operatorname{Exp}(A(z))&=\exp\left(\sum _ {n\geq 1}-a_n\cdot \ln\left(1-z^n\right)\right)\\
&=\exp\left(\sum _ {n\geq 1}-a_n\cdot \sum _ {m\geq 1}\frac{-z^{nm}}{m}\right)\\
&=\exp\left(\frac{A(z)}{1}+\frac{A(z^2)}{2}+\frac{A(z^3)}{3}+\cdots \right)
\end{aligned}
$$

where $\operatorname{Exp}$ is the Pólya exponential, also known as the Euler transform.

???+ note "Example problem [LOJ 6268. Partition Numbers](https://loj.ac/p/6268)"
    **Problem**: Let $f(n)$ be the number of ways to partition $n$. Compute $f(1),f(2),\dots,f(10^5)$ modulo $998244353$.
    
    **Solution**: Let $\mathcal{I}$ be the class of all positive integers. Then $\mathcal{I}=\operatorname{SEQ}_{\geq 1}(\mathcal{Z})=\mathcal{Z}\times \operatorname{SEQ}(\mathcal{Z})$ (the subscript $\geq 1$ means a restricted construction; see below). What we want is
    
    $$
    \operatorname{MSET}(\mathcal{I})
    $$
    
    The first few coefficients of the corresponding OGF are `1 2 3 5 7 11 15 22 30 42` (ignoring the constant term), which is OEIS [A000041](https://oeis.org/A000041).

???+ note "Example problem [Luogu P4389 Princess Fu's Knapsack](https://www.luogu.com.cn/problem/P4389)"
    **Problem**: Given $n$ kinds of items with volumes $v_1,\dots ,v_n$ and a positive integer $m$, for each volume $1,2,\dots,m$ count the number of ways to fill a knapsack of that volume exactly (there is no limit on the number of each item, and different kinds of items may have the same volume), modulo $998244353$. Constraints: $1\leq n,m\leq 10^5$ and $1\leq v_i\leq m$.
    
    **Solution**: Let $\mathcal{A}$ be the combinatorial class of items. What we want is the coefficients of the OGF of $\operatorname{MSET}(\mathcal{A})$.

???+ note "Example problem [Luogu P5900 Counting Unlabeled Unrooted Trees](https://www.luogu.com.cn/problem/P5900)"
    **Problem**: Count the unlabeled unrooted trees with $n$ nodes, modulo $998244353$. Constraints: $1\leq n\leq 2\times 10^5$.
    
    **Solution**: Let $\mathcal{T}$ be the combinatorial class of unlabeled rooted trees. Then
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{MSET}(\mathcal{T})
    $$
    
    According to Richard Otter's paper [The Number of Trees](https://users.math.msu.edu/users/magyarp/Math482/Otter-Trees.pdf), the OGF of unrooted trees is
    
    $$
    T(z)-\frac{1}{2}T^2(z)+\frac{1}{2}T(z^2)
    $$
    
    The first few coefficients are `1 1 1 2 3 6 11 23 47 106` (ignoring the constant term), which is OEIS [A000055](https://oeis.org/A000055).

### The Powerset construction

The Powerset construction generates all subsets.

???+ note "Example"
    $$
    \begin{aligned}
    \operatorname{PSET}(\lbrace a\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace \\
    \operatorname{PSET}(\lbrace a,b\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace \\
    \operatorname{PSET}(\lbrace a,b,c\rbrace)&=\lbrace \epsilon\rbrace +\lbrace a\rbrace +\lbrace b\rbrace +\lbrace (a,b)\rbrace +\lbrace c\rbrace +\lbrace (a,c)\rbrace +\lbrace (b,c)\rbrace +\lbrace (a,b,c)\rbrace\\
    \end{aligned}
    $$

We define it by the recurrence

$$
\operatorname{PSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_n\rbrace)=\operatorname{PSET}(\lbrace \alpha_0,\alpha_1,\dots, \alpha_{n-1}\rbrace)\times (\lbrace \epsilon\rbrace +\lbrace \alpha_n\rbrace)
$$

that is,

$$
\operatorname{PSET}(\mathcal{A})\cong \prod _ {\alpha\in\mathcal{A}}\left(\lbrace \epsilon \rbrace +\lbrace \alpha\rbrace\right)
$$

and require $\mathcal{A}_0=\varnothing$.

The corresponding OGF is

$$
\begin{aligned}
\overline{\operatorname{Exp}}(A(z))&=\prod _ {\alpha\in\mathcal{A}}\left(1+z^{\lvert \alpha \rvert}\right)=\prod _ {n\geq 1}\left(1+z^n\right)^{a_n}\\
&=\exp\left(\sum _ {n\geq 1}a_n\cdot \ln\left(1+z^n\right)\right)\\
&=\exp\left(\sum _ {n\geq 1}a_n\cdot \sum _ {m\geq 1}\frac{(-1)^{m-1}z^{nm}}{m}\right)\\
&=\exp\left(\frac{A(z)}{1}-\frac{A(z^2)}{2}+\frac{A(z^3)}{3}-\cdots \right)
\end{aligned}
$$

where $\overline{\operatorname{Exp}}$ is the modified Pólya exponential.

It is easy to see that $\operatorname{PSET}(\mathcal{A})\subset \operatorname{MSET}(\mathcal{A})$.

### The Cycle construction

The Cycle construction generates all possible combinations, but does not distinguish combinations that differ only by a rotation.

We define it as

$$
\operatorname{CYC}(\mathcal{A})=\left(\operatorname{SEQ}(\mathcal{A})\setminus\lbrace \epsilon\rbrace\right)/\mathbf{S}
$$

where $\mathbf{S}$ is an equivalence relation: $(\alpha_1,\dots,\alpha_n)\mathbf{S}(\beta_1,\dots,\beta_n)$ if and only if there is some cyclic shift $\tau$ such that $\beta_j=\alpha_{\tau(j)}$ for all $j$.

???+ note "Example"
    For simplicity, let $\texttt{a},\texttt{b}$ both be characters of size $1$. We only list the strings of size $3$ and $4$:
    
    $$
    \operatorname{CYC}(\lbrace \texttt{a},\texttt{b}\rbrace)_3=\lbrace \texttt{aaa}\rbrace +\lbrace \texttt{aab}\rbrace+\lbrace \texttt{abb}\rbrace+\lbrace \texttt{bbb}\rbrace
    $$
    
    Here, of $\texttt{aab}\mathbf{S}\texttt{baa}\mathbf{S}\texttt{aba}$ only one is kept, and likewise only one of $\texttt{abb}\mathbf{S}\texttt{bab}\mathbf{S}\texttt{bba}$ is kept.
    
    $$
    \operatorname{CYC}(\lbrace \texttt{a},\texttt{b}\rbrace)_4=\lbrace \texttt{aaaa}\rbrace +\lbrace \texttt{aaab}\rbrace+\lbrace \texttt{aabb}\rbrace+\lbrace \texttt{abbb}\rbrace+\lbrace \texttt{bbbb}\rbrace +\lbrace \texttt{abab}\rbrace
    $$
    
    Here $\texttt{aaab}\mathbf{S}\texttt{baaa}\mathbf{S}\texttt{abaa}\mathbf{S}\texttt{aaba}$, $\texttt{aabb}\mathbf{S}\texttt{baab}\mathbf{S}\texttt{bbaa}\mathbf{S}\texttt{abba}$, $\texttt{abbb}\mathbf{S}\texttt{babb}\mathbf{S}\texttt{bbab}\mathbf{S}\texttt{bbba}$ and $\texttt{abab}\mathbf{S}\texttt{baba}$.

The corresponding OGF is

$$
\operatorname{Log}(A(z))=\sum _ {n\geq 1}\frac{\varphi(n)}{n}\ln\frac{1}{1-A(z^n)}
$$

where $\varphi$ is Euler's totient function and $\operatorname{Log}$ is the Pólya logarithm.

Since the proof is fairly involved, readers can refer to Flajolet's paper [The Cycle Construction](https://epubs.siam.org/doi/10.1137/0404006) or the appendix of Analytic Combinatorics.

### Restricted constructions

In all the constructions above, we did not limit the number of "components". We can put a predicate on integers in the subscript of $\operatorname{SEQ}$ to constrain the number of components, such as

$$
\operatorname{SEQ}_{=k}(\mathcal{B}),\quad \operatorname{SEQ}_{\geq k}(\mathcal{B}),\quad \operatorname{SEQ}_{1..k}(\mathcal{B})
$$

where $\operatorname{SEQ}_{=k}(\mathcal{B})$ is often shortened to $\operatorname{SEQ}_k(\mathcal{B})$, and $\operatorname{SEQ}_{1..k}(\mathcal{B})$ means the number lies in the range $\lbrack 1..k\rbrack$.

Let $\mathfrak{K}$ be any one of $\operatorname{SEQ},\operatorname{PSET},\operatorname{MSET},\operatorname{CYC}$ above, and let

$$
\mathcal{A}=\mathfrak{K}_k(\mathcal{B})
$$

That is, for $\alpha\in\mathcal{A}$ we need

$$
\alpha =\lbrace (\beta_1,\beta_2,\dots ,\beta_k)\mid \beta\in\mathcal{B}\rbrace
$$

Let the function $\chi$, applied to a combinatorial object, give its number of components; so we need $\chi(\alpha)=k$. We add one more variable to "track" the number of components.

Let

$$
A _ {n,k}=\operatorname{card}\left\lbrace \alpha\in\mathcal{A}\mid \lvert \alpha\rvert =n,\chi(\alpha)=k\right\rbrace
$$

Then

$$
A(z,u)=\sum _ {n,k}A _ {n,k}u^kz^n=\sum _ {\alpha\in\mathcal{A}}z^{\lvert \alpha\rvert}u^{\chi(\alpha)}
$$

Then we just extract the coefficient of $u^k$ to get the corresponding expression. For example, $\mathcal{A}=\operatorname{SEQ}_k(\mathcal{B})$ directly gives

$$
\begin{aligned}
&{}A(z,u)=\sum _ {k\geq 0}u^kB(z)^k=\frac{1}{1-uB(z)}\\
\implies &{}A(z)=B(z)^k
\end{aligned}
$$

Clearly also

$$
\mathcal{A}=\operatorname{SEQ}_{\geq k}(\mathcal{B})\implies A(z)=\frac{B(z)^k}{1-B(z)}
$$

For $\operatorname{MSET} _ k(\mathcal{B})$ and $\operatorname{PSET} _ k(\mathcal{B})$ we already have

$$
\begin{aligned}
&{}A(z,u)=\prod_n\left(1-uz^n\right)^{-b_n}\\
\implies &{}A(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots\right)
\end{aligned}
$$

and

$$
\begin{aligned}
&{}A(z,u)=\prod_n\left(1+uz^n\right)^{b_n}\\
\implies &{}A(z)=\lbrack u^k\rbrack \exp\left(\frac{u}{1}B(z)-\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)-\cdots\right)
\end{aligned}
$$

$\operatorname{CYC}_k(\mathcal{B})$ works the same way.

??? note "Using the formula above to compute the OGFs of $\operatorname{MSET}_3(\mathcal{B})$ and $\operatorname{MSET}_4(\mathcal{B})$"
    Let us compute $\mathcal{A}=\operatorname{MSET}_3(\mathcal{B})$:
    
    $$
    \begin{aligned}
    \lbrack u^3\rbrack A(z,u)&= \frac{1}{0!}\left(\lbrack u^3\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots \right)\right)\\
    &+\frac{1}{2!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\cdots \right)^2\right)\\
    &+\frac{1}{3!}\left(\lbrack u^3\rbrack \left(\frac{u}{1}B(z)+\cdots \right)^3\right)\\
    &=\frac{B(z)^3}{6}+\frac{B(z)B(z^2)}{2}+\frac{B(z)^3}{3}
    \end{aligned}
    $$
    
    Let us compute $\mathcal{A}=\operatorname{MSET}_4(\mathcal{B})$:
    
    $$
    \begin{aligned}
    \lbrack u^4\rbrack A(z,u)&= \frac{1}{0!}\left(\lbrack u^4\rbrack 1\right)+\frac{1}{1!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\frac{u^4}{4}B(z^4)+\cdots \right)\right)\\
    &+\frac{1}{2!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\frac{u^3}{3}B(z^3)+\cdots \right)^2\right)\\
    &+\frac{1}{3!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\frac{u^2}{2}B(z^2)+\cdots \right)^3\right)\\
    &+\frac{1}{4!}\left(\lbrack u^4\rbrack \left(\frac{u}{1}B(z)+\cdots \right)^4\right)\\
    &=\frac{B(z^4)}{4}+\frac{1}{2!}\left(\frac{B(z^2)^2}{4}+\frac{2B(z)B(z^3)}{3}\right)+\frac{1}{3!}\left(\frac{3B(z)^2B(z^2)}{2}\right)+\frac{B(z)^4}{4!}\\
    &=\frac{B(z)^4}{24}+\frac{B(z)^2B(z^2)}{4}+\frac{B(z)B(z^3)}{3}+\frac{B(z^2)^2}{8}+\frac{B(z^4)}{4}
    \end{aligned}
    $$

We see that in $\mathcal{A}=\mathfrak{K}_k(\mathcal{B})$, $A(z)$ is an expression in $B(z),B(z^2),\dots ,B(z^k)$.

Note that the restricted construction $\mathfrak{K}_k(\mathcal{B})$ does not require $\mathcal{B}_0=\varnothing$.

???+ note "Commonly used restricted constructions"
    $$
    \begin{aligned}
    \operatorname{PSET} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}-\frac{A(z^2)}{2}\\
    \operatorname{MSET} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}+\frac{A(z^2)}{2}\\
    \operatorname{CYC} _ {2}(\mathcal{A})&:\quad \frac{A(z)^2}{2}+\frac{A(z^2)}{2}
    \end{aligned}
    $$
    
    $$
    \begin{aligned}
    \operatorname{PSET} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{6}-\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
    \operatorname{MSET} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{6}+\frac{A(z)A(z^2)}{2}+\frac{A(z^3)}{3}\\
    \operatorname{CYC} _ {3}(\mathcal{A})&:\quad \frac{A(z)^3}{3}+\frac{2A(z^3)}{3}\\
    \end{aligned}
    $$
    
    $$
    \begin{aligned}
    \operatorname{PSET} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{24}-\frac{A(z)^2A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A(z^2)^2}{8}-\frac{A(z^4)}{4}\\
    \operatorname{MSET} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{24}+\frac{A(z)^2A(z^2)}{4}+\frac{A(z)A(z^3)}{3}+\frac{A(z^2)^2}{8}+\frac{A(z^4)}{4}\\
    \operatorname{CYC} _ {4}(\mathcal{A})&:\quad \frac{A(z)^4}{4}+\frac{A(z^2)^2}{4}+\frac{A(z^4)}{2}\\
    \end{aligned}
    $$

The computation above works but is fairly tedious. Readers can look at [Pólya Enumeration Theorem](https://mathworld.wolfram.com/PolyaEnumerationTheorem.html) and [Cycle Index](https://mathworld.wolfram.com/CycleIndex.html) on Wolfram MathWorld and related material. The cycle index also often appears in the generating function expressions on OEIS.

???+ note "Example problem [LOJ 6538. Counting Alkyl Groups, Harder Version, Even Harder Version](https://loj.ac/p/6538)"
    **Problem**: Count the unordered rooted trees with $n$ nodes in which the root has degree at most $3$ and every other node has degree at most $4$, modulo $998244353$. Constraints: $1\leq n\leq 10^5$.
    
    **Solution**: Let the combinatorial class be $\mathcal{T}$. Then
    
    $$
    \mathcal{T}=\lbrace \bullet\rbrace\times\operatorname{MSET}_{0,1,2,3}(\mathcal{T})
    $$
    
    Or let the combinatorial class $\hat{\mathcal{T}}=\mathcal{T}+\lbrace \epsilon\rbrace$. Then
    
    $$
    \hat{\mathcal{T}}=\lbrace \epsilon\rbrace +\lbrace \bullet\rbrace\times\operatorname{MSET}_{3}(\hat{\mathcal{T}})
    $$
    
    This gives the same result.

## References

-   Philippe Flajolet and Robert Sedgewick.[Analytic Combinatorics](http://algo.inria.fr/flajolet/Publications/books.html).
