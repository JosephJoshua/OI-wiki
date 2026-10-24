author: orzAtalod

This section is reproduced and adapted from [Time Complexity - A Brief Look at Potential Analysis](https://www.luogu.com.cn/blog/Atalod/shi-jian-fu-za-du-shi-neng-fen-xi-qian-tan), with permission from the original author.

## Definition

### The Ackermann function

First we define $\alpha(n)$. To do that, we first define $A_k(j)$.

Define $A_k(j)$ as:

$$
A_k(j)=\left\{
\begin{aligned}
&j+1& &k=0&\\
&A_{k-1}^{(j+1)}(j)& &k\geq1&
\end{aligned}
\right.
$$

This is the Ackermann function.

Here, $f^i(x)$ means applying $f$ to $x$ repeatedly $i$ times, that is, $f^0(x)=x$ and $f^i(x)=f(f^{i-1}(x))$.

Then define $\alpha(n)$ as the smallest integer such that $A_{\alpha(n)}(1)\geq n$. Note that earlier we described it as $A_{\alpha(n)}(\alpha(n))\geq n$; either way, both grow very slowly and their values never exceed 4.

### Basic definitions

Every node has a rank. Here the rank is not the number of nodes but the depth. A node's initial rank is 0. When merging, if the two nodes have different ranks, the node with the smaller rank is attached to the node with the larger rank, and the larger node's rank is not updated. Otherwise, one node is attached to the other arbitrarily, and the root's rank increases by 1. So the root's rank gives the height of its tree. Write the rank of x as $rnk(x)$, and similarly write the parent of x as $fa(x)$. We always have $rnk(x)+1\leq rnk(fa(x))$.

To define the potential function, we first need a helper function $level(x)$, where $level(x)=\max(k:rnk(fa(x))\geq A_k(rnk(x)))$. When $rnk(x)\geq1$, we also define a helper function $iter(x)=\max(i:rnk(fa(x))\geq A_{level(x)}^i(rnk(x))$. These functions are only defined for $x$ with $rnk(x)>0$ where $x$ is not the root of a tree.

These definitions may make your head spin a little. To restate them: for an $x$ and $fa(x)$ with $rnk(x)>0$, we can always find a pair $i,k$ with $rnk(fa(x))\geq A_k^i(rnk(x))$. Then $level(x)=\max(k)$, and given that, $iter(x)=\max(i)$. So $level$ describes the highest level of $A$ we can iterate, and $iter$ describes the largest number of iterations at that highest level.

As operations go on, $level(x)$ only increases or stays the same, and if $level(x)$ does not increase, $iter(x)$ also only increases or stays the same. They also always satisfy the following two inequalities:

$$
0\leq level(x)<\alpha(n)
$$

$$
1\leq iter(x)\leq rnk(x)
$$

These are easy to prove from the definitions of $level(x)$, $iter(x)$ and $A_k^j$, so we leave them to the reader as a way to get familiar with the definitions.

Define the potential function $\Phi(S)=\sum\limits_{x\in S}\Phi(x)$, where $S$ is the whole DSU and $x$ is a node in it. Define $\Phi(x)$ as:

$$
\Phi(x)=
\begin{cases}
\alpha(n)\times \mathit{rnk}(x)& \mathit{rnk}(x)=0\ \text{or}\ x\ \text{is the root of a tree}\\
(\alpha(n)-\mathit{level}(x))\times \mathit{rnk}(x)-iter(x)& \text{otherwise}
\end{cases}
$$

Next, we use the change in potential caused by each operation to prove that the amortized time complexity is $\Theta(\alpha(n))$. Note that the $union(x,y)$ operation we discuss here guarantees that both $x$ and $y$ are roots, so there is no need to run $find(x)$ and $find(y)$ first.

Notice that the potential is always non-negative. Also, at the start, the potential of the DSU is $0$.

## Proof

### The union(x,y) operation

It takes $\Theta(1)$ time, so we look at the change in potential it causes.

Assume $rnk(x)\leq rnk(y)$, so $x$ is attached to $y$. Then the only nodes whose potential can increase are $x$ (it goes from root to non-root), $y$ (its rank may increase), and the children of $y$ before the operation (their parent's rank may increase). We first prove that the potential of a child $c$ of $y$ cannot increase, and if it decreases, it decreases by at least $1$.

Let the potential of $c$ before the operation be $\Phi(c)$ and after it be $\Phi(c')$. Here $c$ can be any non-root node with $rnk(c)>0$, and the operation can be any operation, including the find operation below. We consider the following cases.

1.  Neither $iter(c)$ nor $level(c)$ increases. Clearly $\Phi(c)=\Phi(c')$.
2.  $iter(c)$ increases and $level(c)$ does not. Then $iter(c)$ increases by at least one, so $\Phi(c')\leq \Phi(c)-1$: the potential decreases, by at least 1.
3.  $level(c)$ increases, and $iter(c)$ may decrease. But since $0<iter(c)\leq rnk(c)$, $iter(c)$ can decrease by at most $rnk(c)-1$, while $level(c)$ increases by at least $1$. From the definition $\Phi(c)=(\alpha(n)-level(c))\times rnk(c)-iter(c)$, we get $\Phi(c')\leq\Phi(c)-1$.
4.  Other cases. Since $rnk(c)$ does not change and $rnk(fa(c))$ does not decrease, these cannot happen.

So the only nodes whose potential can increase are $x$ and $y$. Node $x$ goes from root to non-root. If $rnk(x)=0$, then $\Phi(x)=\Phi(x')=0$ throughout. Otherwise, we always have $\alpha(x)\times rnk(x)\geq(\alpha(n)-level(x))\times rnk(x)-iter(x)$, that is, $\Phi(x')\leq \Phi(x)$.

Therefore, the only node whose potential can increase is $y$, and its potential increases by at most $\alpha(n)$. So the amortized time complexity of $union$ is $\Theta(\alpha(n))$.

### The find(a) operation

If the search path contains $\Theta(s)$ nodes, the search clearly takes $\Theta(s)$ time. If the search makes no node's potential increase, and makes at least $s-\alpha(n)$ nodes' potentials decrease by at least $1$ each, then $find(a)$ takes $\Theta(\alpha(n))$ amortized time. To avoid confusion, we use $a$ for the argument, while $x$ always refers to an arbitrary node in the DSU.

First we prove that no node's potential increases. This is clear: we proved above that the potential of any non-root node does not increase, and the root's $rnk$ does not change, so no node's potential increases.

Next we prove that at least $s-\alpha(n)$ nodes' potentials decrease by at least $1$. We proved above that if $level(x)$ or $iter(x)$ changes, the potential decreases by at least $1$. So we only need to prove that at least $s-\alpha(n)$ nodes have their $level(x)$ or $iter(x)$ changed.

Recall the definition of a non-root node's potential, $\Phi(x)=(\alpha(n)-level(x))\times rnk(x)-iter(x)$, where $level(x)$ and $iter(x)$ are the largest values with $rnk(fa(x))\geq A_{level(x)}^{iter(x)}(rnk(x))$.

So if $root_x$ is the root of the tree containing $x$, we only need to prove that $rnk(root_x)\geq A_{level(x)}^{iter(x)+1}(rnk(x))$. By the definition of $A_k^i$, $A_{level(x)}^{iter(x)+1}(rnk(x))=A_{level(x)}(A_{level(x)}^{iter(x)}(rnk(x)))$.

Note that we may write $k(x)$ for $level(x)$ and $i(x)$ for $iter(x)$ to keep formulas short. Then the goal is $rnk(root_x)\geq A_{k(x)}(A_{k(x)}^{i(x)}(x))$.

At this point you may be thinking "what on earth is this?". That means you may need to reread it a few times, or skip some parts and come back later.

We need one extra outer $A_{k(x)}$, which means we may need to find another node $y$. Let $y$ be a node after $x$ on the search path with $k(y)=k(x)$; here "after $x$ on the search path" means "an ancestor of $x$". Clearly, not every $x$ has such a $y$. It is easy to prove that at most $\alpha(n)+2$ nodes $x$ have no such $y$, because only the last $x$ for each $k$, plus $a$ and $root_a$, lack one.

To stress it again: $fa(x)$ means the parent of $x$ **before** path compression, and the parent of $x$ **after** path compression is always written $root_x$. For every $x$ that has a $y$, we always have $rnk(y)\geq rnk(fa(x))$. We also have $rnk(fa(x))\geq A_{k(x)}^{i(x)}(rnk(x))$. Since $k(x)=k(y)$, we just write $k$ for both, so $rnk(fa(x))\geq A_k^{i(x)}(rnk(x))$. We need to produce one more $A_k$, so we can ignore the value of $iter(y)$ and use the weaker $rnk(fa(y))\geq A_k(rnk(y))$.

If we chain these inequalities together, something magical happens: $rnk(fa(y))\geq A_k^{i(x)+1}(rnk(x))$. In other words, starting from $rnk(x)$, we can apply $A_k$ at least $i(x)+1$ times without exceeding $rnk(fa(y))$.

Clearly $rnk(root_y)\geq rnk(fa(y))$, and $rnk(x)$ does not change during path compression. So we get $rnk(root_x)\geq A_k^{i(x)+1}(rnk(x))$, which means $iter(x)$ increases by at least 1; if $rnk(x)$ does not increase, then $level(x)$ must have increased.

So $\Phi(x)$ decreases by at least 1. Since there are at least $s-\alpha(n)-2$ such nodes $x$, $\Phi(S)$ decreases by at least $s-\alpha(n)-2$ in total, and the amortized time complexity is $\Theta(\alpha(n)+2)=\Theta(\alpha(n))$.

## Why a DSU can be made slow

This question asks: if we don't use union by rank, which properties break, so that the DSU's time complexity is no longer guaranteed to be $\Theta(m\alpha(n))$?

Suppose that when merging, a node with larger $rnk$ gets attached to a node with smaller $rnk$. Then we set the smaller node's $rnk$ to the other node's $rnk$ plus one. This keeps $rnk(fa(x))\geq rnk(x)+1$, so we don't get a whole mess of broken properties, like a screen full of compile errors.

Clearly, in that case, what we break is the statement in $union(x,y)$ that "the potential of y increases by at most $\alpha(n)$".

There is a structure that drives a DSU with path compression down to $\Omega(m\log_{1+\frac{m}{n}}n)$ time. It is defined as follows:

A binomial tree (actually a bit different from the usual binomial tree), where j is a constant, and $T_k$ is a $T_{k-1}$ plus a $T_{k-j}$ attached as a child of the root.

![Binomial tree](./images/dsu-complexity.svg)

Base cases: $T_1$ through $T_j$ are each a single node.

Let $rnk(T_k)=r_k$; here we have $r_k=(k-1)/j$ (proof omitted). In each round, we attach the tree to a single node and then query the bottom $j$ nodes. That is, when we attach it to the single node, the single node's potential increases by $(k-1)/j+1$. With $j=\lfloor\frac{m}{n}\rfloor$, $i=\lfloor\log_{j+1}\frac{n}{2}\rfloor$ and $k=ij$, the increase in potential is:

$$
\alpha(n)\times((ij-1)/j+1)=\alpha(n)\times((\lfloor\log_{\lfloor\frac{m}{n}\rfloor+1}\frac{n}{2}\rfloor\times \lfloor\frac{m}{n}\rfloor-1)/\lfloor\frac{m}{n}\rfloor+1)
$$

Rewriting this and dropping all the floor signs, the increase in potential is $\geq \alpha(n)\times(\log_{1+\frac{m}{n}}n-\frac{n}{m})$, so m operations cost $\Omega(m\log_{1+\frac{m}{n}}n-n)=\Omega(m\log_{1+\frac{m}{n}}n)$.

## About union by size

Union by rank is harder to write than union by size (the small-to-large heuristic), so many experts choose union by size for their DSU. Concretely, each root keeps a $size(x)$, and each merge attaches the smaller $size$ to the larger.

So, can union by size be made slow?

First, we can look at the properties of rank used in the proof. If $size$ can take the place of $rnk$, then union by size works. To summarize quickly, the proof uses these three properties of rank:

1.  In each merge, at most one node's rank goes up, and by at most 1.
2.  We always have $rnk(fa(x))\geq rnk(x)+1$.
3.  A node's rank never decreases.

$siz$ clearly satisfies the second and third properties, but not the first: if $x$ is merged into $y$, $siz(y)$ grows by $siz(x)$.

So we can use $\log_2 siz(x)$ in place of $rnk(x)$.

For the first property, since a node's $siz$ at most doubles, $\log_2 siz(x)$ goes up by at most 1. The second and third properties follow fairly obviously, so we omit the proof.

So if you don't want to write union by rank, just write union by size; the time complexity is still $\Theta(m\alpha(n))$.
