## Introduction

The **stable matching problem** is a classic problem in combinatorial optimization and cooperative game theory. Compared with the traditional graph matching problem, stable matching adds individual preferences and a stability requirement, so algorithm design depends more on preference orders than on the graph structure alone. In the stable matching model, each individual has preferences over its potential partners, and the goal is to build a stable matching between them. In a stable matching, no group of individuals would want to jointly break away from the current matching because they could get better choices. Stable matching and related problems are widely used in labor markets, school admissions, allocation of medical resources, and so on.

The stable matching problem that appears most often in competitive programming is one-to-one matching in a two-sided market, namely the stable marriage problem. This page focuses on the stable marriage problem and its algorithm.

## Stable marriage problem

The stable marriage problem is the earliest studied stable matching problem. Like bipartite matching, it can be described as a matching problem on a marriage market: there are some men and some women, each person has a preference order over people of the opposite sex, and the goal is to find a matching such that no man and woman would both rather leave their partners and be with each other.

### Problem statement

The matching market consists of a set of men $M$ and a set of women $W$. Each person has a strict preference order over the opposite sex:

-   For each man $m\in M$, there is a strict total order $\preceq_m$ on the set $W\cup\{m\}$;
-   For each woman $w\in W$, there is a strict total order $\preceq_w$ on the set $M\cup\{w\}$.

Besides comparing people of the opposite sex, each person also puts themselves into this preference order. This means a person will only accept partners they prefer to being single; such partners are called **acceptable**. Clearly, the order among unacceptable partners does not matter; in principle, only the order among acceptable partners needs to be given. So preferences with some unacceptable partners are also called preferences with incomplete lists.

???+ example "Example"
    Suppose $m$ is a man, $w_1,w_2,w_3$ are three women, and the preference $w_1\prec_m m \prec_m w_2\prec_m w_3$ holds. Then man $m$ prefers being single to being matched with $w_1$; prefers being matched with $w_2$ to being single; and prefers being matched with $w_3$ to being matched with $w_2$. For man $m$, woman $w_1$ is unacceptable, and women $w_2,w_3$ are acceptable.

A **matching** $\mu:M\cup W\rightarrow M\cup W$ on the market must satisfy the following properties:

-   Each person can only be matched with someone of the opposite sex or with themselves. That is, $\mu(m)\in W\cup\{m\}$ for all $m\in M$, and $\mu(w)\in M\cup\{w\}$ for all $w\in W$.
-   Matching is mutual. That is, $i = \mu(\mu(i))$ for all $i\in M\cup W$.

A matching $\mu$ can be unstable in two ways:

-   If some individual $i\in M\cup W$ has $\mu(i)\prec_i i$, that is, $i$ would rather be single than stay with the current partner, then $i$ is called a **blocking individual** of $\mu$.
-   If some man $m\in M$ and woman $w\in W$ have $\mu(m)\prec_m w$ and $\mu(w)\prec_w m$, that is, $m$ and $w$ would both rather be with each other than with their current partners, then $(m,w)$ is called a **blocking pair** of $\mu$.

If a matching $\mu$ has no blocking individual and no blocking pair, then $\mu$ is called **stable**. In a stable matching, nobody can break the current situation: a single person cannot find anyone willing to be with them; a married person neither wants to divorce and be single, nor can find anyone willing to run away with them.

The stable matching problem asks: for any given set of preference orders, does a stable matching always exist? If so, how can we find one?

### Gale–Shapley algorithm

In 1962, Gale and Shapley proposed the **deferred acceptance algorithm**, which finds a stable matching for any given set of preference orders. So a stable matching always exists.

The Gale–Shapley algorithm has two symmetric versions: men propose, or women propose. Taking the men-proposing version as an example, the algorithm works as follows:

1.  At the start, each woman is considered to be holding a proposal from herself, and every man is marked active.
2.  Each active man proposes to his favorite woman among those who are acceptable to him and whom he has not yet proposed to; if no such woman exists, he does nothing. Whether or not he proposes, all men are then marked inactive.
3.  Each woman who receives new proposals compares them with the proposal she is currently holding, keeps only her favorite one (possibly herself), and rejects all others. Rejected men are marked active again.
4.  Repeat the previous two steps until no man is active. At that point, each woman accepts the proposal she is currently holding. The resulting matching is a stable matching.

Since each man proposes to each woman at most once, the algorithm always ends within $O(|M||W|)$ time.

Here is a reference implementation:

??? example "Template problem [SPOJ STABLEMP - Stable Marriage Problem](https://www.spoj.com/problems/STABLEMP/) reference implementation"
    ```cpp
    --8<-- "docs/graph/code/graph-matching/stable-match/stable-match.cpp"
    ```

### Properties of stable matchings

Stable matchings have nice theoretical properties. First, the Gale–Shapley algorithm proves constructively that a stable matching always exists.

???+ note "Theorem 1 (Gale and Shapley, 1962)"
    The Gale–Shapley algorithm produces a stable matching. Therefore, a stable matching exists.

??? note "Proof"
    A man never proposes to a woman he does not accept, and a woman immediately rejects proposals from men she does not accept. So the men and women matched in the end always accept each other, and there can be no blocking individual. To prove the matching is stable, we only need to show there is no blocking pair.
    
    We argue by contradiction. Suppose $(m,w)$ is a blocking pair. Since $\mu(m)\prec_m w$, man $m$ must have proposed to $w$. But since $w$ rejected $m$, she must have received a proposal from someone $m'$ she likes more. If $m'\neq \mu(w)$, then $w$ likes $\mu(w)$ even more than $m'$. So $w$ must prefer her final partner $\mu(w)$ to $m$. This contradicts $(m,w)$ being a blocking pair. So the matching is stable.

???+ note "Corollary"
    If $|M|=|W|$ and everyone of the opposite sex is acceptable, then a stable perfect matching exists.

In the Gale–Shapley algorithm, either men or women can propose. In general, the two versions produce different stable matchings. In fact, the stable matching produced by the men-proposing version is the best for men among all stable matchings, and vice versa.

???+ note "Theorem 2 (Gale and Shapley, 1962)"
    Let $\mu_M$ and $\mu_W$ be the stable matchings produced by the men-proposing and women-proposing Gale–Shapley algorithms, respectively. Then for every stable matching $\mu$, $\mu(m)\preceq_m\mu_M(m)$ holds for all $m\in M$, and $\mu(w)\preceq_w\mu_W(w)$ holds for all $w\in W$.

??? note "Proof"
    By symmetry, we only need to prove that $\mu(m)\preceq_m\mu_M(m)$ holds for all $m\in M$. To do this, again consider the men-proposing Gale–Shapley algorithm, and let $k(m,w)$ be the round of the algorithm in which woman $w$ rejects man $m$. This round is well-defined for every $(m,w)$ with $\mu_M(m)\prec_m w$.
    
    Suppose $\mu_M$ is not the best for all men. That is, there are a stable matching $\mu$ and a man $m\in M$ with $\mu_M(m)\prec_m\mu(m)$. Since $\mu_M$ is stable, $m\preceq_m\mu_M(m)\prec_m\mu(m)$, so $\mu(m)$ is a woman, and $k(m,\mu(m))$ is well-defined. We may assume $m$ is the man among all such men with the smallest $k(m,\mu(m))$. Suppose that when woman $w=\mu(m)$ rejected $m$ during the algorithm, she kept the proposal of man $m'$; that is, $m=\mu(w)\prec_w m'$. Since $\mu$ is stable, $(m',w)$ cannot be a blocking pair, and $\mu(m')\neq w$, so $w\prec_{m'}\mu(m')$. In the Gale–Shapley algorithm, $w$ may not keep the proposal from $m'$ until the end, so $\mu_M(m')\preceq_{m'}w\prec_{m'}\mu(m')$. Thus $k(m',\mu(m'))$ is well-defined. Moreover, since $w\prec_{m'}\mu(m')$, woman $\mu(m')$ must have rejected $m'$ before $w$ held the proposal from $m'$; that is, $k(m',\mu(m')) < k(m,\mu(m))$. This contradicts the choice of $m$. So, by contradiction, $\mu_M$ is the stable matching that is best for all men.

A matching market can have exponentially many stable matchings. Let $\mathcal S$ be the set of all stable matchings. Two partial orders can be defined on this set:

-   $\mu_1\preceq_M\mu_2$ if and only if $\mu_1(m)\preceq_m\mu_2(m)$ holds for all $m\in M$;
-   $\mu_1\preceq_W\mu_2$ if and only if $\mu_1(w)\preceq_w\mu_2(w)$ holds for all $w\in W$.

These two partial orders mean that one matching is better for all men, or for all women, respectively. In general, two stable matchings need not be comparable. However, any two stable matchings induce a decomposition as shown in the figure, so that in the three resulting parts, $\mu_1\preceq_M\mu_2$, $\mu_1=\mu_2$ and $\mu_2\preceq_M\mu_1$ hold respectively. Note that, although it is not drawn directly, the part where $\mu_1=\mu_2$ actually includes people matched to themselves (that is, unmatched).

![](./images/stable-match-decompose.svg)

This decomposition relies on the following lemma:

???+ note "Lemma (Knuth, 1976)"
    Let $\mu_1$ and $\mu_2$ be two stable matchings. Let $M(\mu_i)=\{m\in M : \mu_j(m)\prec_m\mu_i(m)\}$ and $W(\mu_i)=\{w\in W:\mu_j(w)\prec_w\mu_i(w)\}$ be the sets of men and women, respectively, who prefer their partner in $\mu_i$, where $i,j=1,2$ and $i\neq j$. Then $\mu_1$ and $\mu_2$ are both bijections between $M(\mu_1)$ and $W(\mu_2)$, and also both bijections between $M(\mu_2)$ and $W(\mu_1)$.

??? note "Proof"
    Let $m\in M(\mu_1)$. Since $m\preceq_m \mu_2(m)\prec_m\mu_1(m)$, we have $\mu_1(m)\in W$. Let $w=\mu_1(m)$. Since $\mu_2(w)\neq m$, and $\mu_2(w)\prec_w m$ would make $(m,w)$ a blocking pair of $\mu_2$, we get $\mu_1(w)=m\prec_w\mu_2(w)$. That is, $w\in W(\mu_2)$. This shows $\mu_1(M(\mu_1))\subseteq W(\mu_2)$. By symmetry, we also get $\mu_2(W(\mu_2))\subseteq M(\mu_1)$. Since $\mu_1$ and $\mu_2$ are both injective, $|M(\mu_1)|=|W(\mu_2)|$ and both maps are surjective. This shows that $\mu_1$ and $\mu_2$ are both bijections between $M(\mu_1)$ and $W(\mu_2)$. Similarly, they are also both bijections between $M(\mu_2)$ and $W(\mu_1)$.

This lemma shows that the posets $(\mathcal S,\preceq_M)$ and $(\mathcal S,\preceq_W)$ are [dual](../../math/order-theory.md#对偶) to each other. Moreover, under each partial order, the set $\mathcal S$ forms a [lattice](../../math/order-theory.md#有向集与格). Since $\mathcal S$ is finite, both lattices have a greatest element and a least element. These extreme elements are exactly the stable matchings produced by the two versions of the Gale–Shapley algorithm mentioned above.

???+ note "Theorem 3 (Conway and Knuth, 1976)"
    The posets $(\mathcal S,\preceq_M)$ and $(\mathcal S,\preceq_W)$ are lattices dual to each other. Moreover, $\mu_M$ and $\mu_W$ are the greatest and least elements of $(\mathcal S,\preceq_M)$ respectively, and the least and greatest elements of $(\mathcal S,\preceq_W)$ respectively.

??? note "Proof"
    By the lemma, it is easy to show the two posets are dual. If $\mu_1\preceq_M\mu_2$, then $M(\mu_1)=\varnothing$; by the lemma, $W(\mu_2)=\varnothing$, which means $\mu_2\preceq_W\mu_1$. The converse is similar. So the two are dual to each other. Combined with Theorem 2 above, $\mu_M$ and $\mu_W$ are the extreme elements of the two posets. What remains is to prove that both posets are lattices. By symmetry, we only need to prove that $(\mathcal S,\preceq_M)$ is a lattice. By the symmetry between meet and join, we only need to prove that the join of stable matchings is still a stable matching. Formally, for any $\mu_1,\mu_2\in\mathcal S$, we need to prove that the matching $\mu=\mu_1\lor_M\mu_2$ with $\mu(m)=\mu_1(m)\lor_m\mu_2(m)$ for all $m\in M$ is a stable matching, where $\lor_m$ is the join under the total order $\preceq_m$ (that is, whichever of the two $m$ likes more).
    
    We use the notation from the lemma. For $i\in M(\mu_1)\cup W(\mu_2)$, let $\mu(i)=\mu_1(i)$; otherwise, let $\mu(i)=\mu_2(i)$. By the lemma, $\mu_1$ and $\mu_2$ both map the set $M(\mu_1)\cup W(\mu_2)$ to itself, so $\mu$ is a well-defined matching. Since $\mu_1$ and $\mu_2$ are both stable, they have no blocking individuals, and neither does $\mu$. Suppose $(m,w)$ is a blocking pair of $\mu$. If $m\in M(\mu_1)$, then $\mu_2(m)\prec_m\mu_1(m)=\mu(m)\prec_m w$. In this case, if $w\in W(\mu_2)$, then $\mu_1(w)=\mu(w)\prec_w m$, so $(m,w)$ is a blocking pair of $\mu_1$, a contradiction; otherwise $w\in W\setminus W(\mu_2)$, and $\mu_2(w)=\mu(w)\prec_w m$, so $(m,w)$ is a blocking pair of $\mu_2$, also a contradiction. Similarly, the case $m\in M\setminus M(\mu_1)$ also leads only to contradictions. By contradiction, no such blocking pair exists. So $\mu_1\lor_M\mu_2$ is a stable matching. This proves the claim.

Finally, the sets of unmatched men and women are the same in all stable matchings.

???+ note "Theorem 4 (McVitie and Wilson, 1970)"
    Let $\mu_1$ and $\mu_2$ be two stable matchings. Then $\mu_1$ and $\mu_2$ have the same set of fixed points.

??? note "Proof"
    Suppose there are $\mu_1,\mu_2\in\mathcal S$ and $m\in M$ with $\mu_1(m)=m$ and $\mu_2(m)\neq m$. Then $m\in M(\mu_2)$. By the lemma, $m=\mu_1(m)\in W(\mu_1)$, which contradicts $m\in M$. So no such $m\in M$ exists. In the same way, no such $w\in W$ exists. So any two stable matchings must have the same set of fixed points.

Besides the properties discussed in this section, stable matchings also have some nice strategic properties. For these, see the references at the end of the page.

## Related problems

Stable matching and similar problems also appear in many other settings.

### College admissions problem

If we relax the one-to-one restriction in the stable marriage problem and allow many-to-one matching, we get the **college admissions problem**. Here a college can admit several students, as long as it does not exceed its quota; but each student can still attend at most one college. Similar settings appear in company hiring, hospitals hiring residents, and so on.

The Gale–Shapley algorithm still works for this kind of problem. For example, in the student-applying version, each college can keep a waitlist no longer than its quota, and whenever the number of applications exceeds the quota, it rejects the worst student. The earlier discussion of the properties of stable matchings still applies in this setting. In particular, the version of Theorem 4 says that the number of students each college admits is the same in all stable matchings. This is also called the **rural hospitals theorem**, because it means that no matter how the matching mechanism is changed, as long as the result is stable, rural hospitals that cannot fill their positions will never fill them.

### Stable roommates problem

If we relax the condition in the stable marriage problem that people can only be matched with the opposite sex, we get the **stable roommates problem**. Here we start with just a group of students who need to be paired up as roommates. For this kind of problem, a stable matching may not exist. In 1985, Irving proposed an algorithm that solves this problem in $O(n^2)$ time.

### Housing market problem

In the stable marriage problem, the two groups have preferences over each other, so it is a two-sided matching problem. We can also consider one-sided matching problems. A common setting is the **housing market problem**. There are $n$ residents, each owning one house. Each person has a strict preference over all houses. Now the houses are to be reassigned to the residents so that no resident gets a house worse than their original one, and no group of residents (of any size) can privately swap houses to get a better outcome. This problem can be solved in $O(n^2)$ time with the Top Trading Cycle algorithm. Problems like this also come up in kidney transplant exchange and similar settings.

## Exercises

-   [UOJ 41. [Tsinghua Training Camp 2014] Matrix Transformation](https://uoj.ac/problem/41)
-   [Codeforces 1147 F. Zigzag Game](https://codeforces.com/problemset/problem/1147/F)

## References and notes

-   [What is an algorithm: how to find stable marriages - Matrix67 (Chinese)](https://matrix67.com/blog/archives/2976)
-   [The Gale–Shapley algorithm: finding stable matchings in bipartite graphs (Chinese)](https://reimuyk.github.io/2021-03-24-Gale-Shapley-Algorithm/)
-   [Stable matching problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_matching_problem)
-   [Lattice of stable matchings - Wikipedia](https://en.wikipedia.org/wiki/Lattice_of_stable_matchings)
-   [Stable roommates problem - Wikipedia](https://en.wikipedia.org/wiki/Stable_roommates_problem)
-   [Top trading cycle - Wikipedia](https://en.wikipedia.org/wiki/Top_trading_cycle)
-   [Stable matching: Theory, evidence, and practical design - the 2012 Nobel Prize in Economics](https://www.nobelprize.org/uploads/2018/06/popular-economicsciences2012.pdf)
-   [Notes on Matching and Market Design by Xiang Sun](https://www.xiangsun.org/wp-content/uploads/2013/02/notes-2015-matching.pdf)
-   Gale, David, and Lloyd S. Shapley. "College admissions and the stability of marriage." The American Mathematical Monthly 69, no. 1 (1962): 9-15.
-   Irving, Robert W. "An efficient algorithm for the stable roommates problem." Journal of Algorithms 6, no. 4 (1985): 577-595.
-   Knuth, Donald Ervin. "Mariages stables et leurs relations avec d’autres problèmes combinatoires." Les Presses de l’Université de Montréal (1976).
-   McVitie, David G., and Leslie B. Wilson. "Stable marriage assignment for unequal sets." BIT Numerical Mathematics 10, no. 3 (1970): 295-309.
-   Roth, Alvin E., and Marilda Sotomayor. "Two-sided matching." Handbook of game theory with economic applications 1 (1992): 485-541.
-   Roth, Alvin E. "Deferred acceptance algorithms: History, theory, practice, and open questions." International Journal of Game Theory 36, no. 3-4 (2008): 537-569.
