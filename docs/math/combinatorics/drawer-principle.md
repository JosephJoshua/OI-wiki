## Definition

The drawer principle is also called the pigeonhole principle.

It is often used for existence proofs and for finding worst-case answers.

## Simple case

If $n+1$ objects are divided into $n$ groups, then at least one group has two (or more) objects.

This theorem looks fairly obvious. We prove it by contradiction: if every group had at most $1$ object, there would be at most $1\times n$ objects, but there are actually $n+1$ objects, a contradiction.

## Generalization

If $n$ objects are divided into $k$ groups, then at least one group contains at least $\left \lceil \dfrac{n}{k} \right \rceil$ objects.

The generalized form can also be proved by contradiction: if every group contained fewer than $\left \lceil \dfrac{n}{k} \right \rceil$ objects, the total would be $S\leq (\left \lceil \dfrac{n}{k} \right \rceil -1 ) \times k=k\left\lceil \dfrac{n}{k} \right\rceil-k < k(\dfrac{n}{k}+1)-k=n$, a contradiction.

Also, the partition can be weakened to a cover and the conclusion still holds.  
Given a set $S$ and a family $\{A_1,A_2\ldots A_k\}$ of non-empty subsets of $S$:

-   if it satisfies $\bigcup_{i=1}^k A_i$, it is called a cover of $S$;
-   if a cover also satisfies $i\neq j\to A_i\cap A_j=\varnothing$, it is called a partition of $S$.

The pigeonhole principle can be stated as: for a cover $\{A_1,A_2\ldots A_k\}$ of $S$, at least one set $A_i$ satisfies $\left\vert A_i \right\vert \geq \left\lceil \dfrac{\left\vert S \right\vert}{k} \right\rceil$.

## References

-   [Wikipedia: Pigeonhole principle](https://en.wikipedia.org/wiki/Pigeonhole_principle)
-   *Discrete Mathematics and Its Applications*: Chapter 6, Section 1
