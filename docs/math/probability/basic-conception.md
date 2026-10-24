## Overview

When studying a concrete random phenomenon, we usually focus on the following elements:

-   The sample space $\Omega$, which lists all possible outcomes of the random phenomenon.
-   The event space $\mathcal{F}$, which contains all the events we care about.
-   The probability $P$, which describes how likely each event is to happen.

## Sample space and random events

### Definition

An outcome of a random phenomenon that cannot be split any further is called a **sample point**. The set of all sample points is called the **sample space**, usually written $\Omega$.

A **random event** is a subset of the sample space $\Omega$. It consists of some sample points and is written with capital letters $A, B, C, \cdots$.

For an outcome $\omega$ of a random phenomenon and a random event $A$, we say event $A$ **happened** if and only if $\omega \in A$.

For example, the number shown when rolling a die once is a random phenomenon, and its sample space can be written as $\Omega=\{1,2,3,4,5,6\}$. Let the random event $A$ be "the number rolled is greater than $4$". Then $A = \{ 5, 6 \}$. If a roll gives $\omega = 3$, then since $\omega \notin A$, event $A$ did not happen.

### Operations on events

Since we defined random events as subsets of the sample space $\Omega$, we can carry set operations (such as intersection, union and complement) over to random events. The notation is the same as for set operations.

In particular, the union of events $A \cup B$ can also be written $A + B$, and the intersection $A \cap B$ can also be written $AB$; these are then called the **sum event** and the **product event**.

## Event space

When studying a concrete random phenomenon, we need to be clear about which events we are interested in. By the definition of random events, clearly $\mathcal{F} \subset 2^{\Omega}$ (the notation $2^{\Omega}$ means the power set of $\Omega$), but $\mathcal{F} = 2^{\Omega}$ is not required. This may be a bit hard to understand when the sample space $\Omega$ is finite, since $2^{\Omega}$ is larger but still finite. But when $\Omega$ is infinite, the cardinality of $2^{\Omega}$ becomes even larger, and it inevitably contains some "badly behaved" events that we do not care about. Giving up useful properties just to accommodate such events would not be worth it.

Although $\mathcal{F} = 2^{\Omega}$ is not required, this does not mean any subset of $2^{\Omega}$ can be an event space. We are usually interested in the probability of the events obtained by applying operations to other events, so we want the event space $\mathcal{F}$ to satisfy the following conditions:

-   $\varnothing \in \mathcal{F}$;
-   if $A \in \mathcal{F}$, then the complement event $\bar{A} \in \mathcal{F}$;
-   if there is a sequence of events $A_n \in \mathcal{F}, n = 1, 2, 3\dots$, then $\bigcup A_n \in \mathcal{F}$.

In short, the event space $\mathcal{F}$ is closed under complement and countable union, and contains the element $\varnothing$.

One can prove that an event space $\mathcal{F}$ satisfying the three conditions above is also closed under countable intersection.

Taking the die roll as an example, with sample space $\Omega=\{1,2,3,4,5,6\}$, the following two sets can be event spaces:

-   $\mathcal{F}_1 = \{ \varnothing, \Omega \}$
-   $\mathcal{F}_2 = \{ \varnothing, \{1, 3, 5\}, \{2, 4, 6\}, \Omega \}$

But the following two sets cannot

-   $\mathcal{F}_3 = \{ \varnothing, \{1\}, \Omega \}$ (not closed under complement)
-   $\mathcal{F}_4 = \{ \{1, 3, 5\}, \{2, 4, 6\} \}$ (does not contain $\varnothing$ and is not closed under union)

## Probability

### Definition

#### Classical definition

In the early practice of probability theory, the random phenomena involved were all fairly simple: the sample space $\Omega$ was a finite set, and intuitively all sample points were equally likely. So people came up with the following definition:

If a random phenomenon satisfies:

-   there are only finitely many basic outcomes;
-   each basic outcome is equally likely;

then for each event $A$, its probability is defined as

$$
P(A)=\frac{\#(A)}{\#(\Omega)}
$$

where $\#(\cdot)$ is a measure of the size of a random event (a set).

Later, people found that this definition can be directly extended to some situations where $\Omega$ is infinite, which gave rise to so-called [geometric probability](https://baike.baidu.com/item/%E5%87%A0%E4%BD%95%E6%A6%82%E5%9E%8B/4035773).

#### Axiomatic definition

The intuition-based definition above has a big logical gap: it uses the notion of "likelihood" to define "probability", which makes the definition circular. Also, "equally likely" becomes ambiguous when the sample space is infinite, which leads to a series of problems including [Bertrand's paradox](https://baike.baidu.com/item/%E8%B4%9D%E7%89%B9%E6%9C%97%E6%82%96%E8%AE%BA/9241081).

After continued exploration, the Soviet mathematician Kolmogorov gave the first axiomatic definition of probability in 1933, in his book *Foundations of the Theory of Probability*:

A probability function $P$ is a map from the event space $\mathcal{F}$ to the closed interval $[0, 1]$ that satisfies:

-   **Normalization**: the probability of the event $\Omega$ is $1$, i.e. $P(\Omega)=1$.
-   **Countable additivity**: if a sequence of events $A_1, A_2, \cdots$ are pairwise disjoint, then $P\left( \bigcup_{i \geq 1} A_i \right) = \sum_{i \geq 1} P(A_i)$.

### Properties of the probability function

For any random events $A, B \in \mathcal{F}$:

-   **Monotonicity**: if $A \subset B$, then $P(A) \leq P(B)$.
-   **Inclusion–exclusion principle**: $P(A+B) = P(A) + P(B) - P(AB)$.
-   $P(A - B) = P(A) - P(AB)$, where $A - B$ means set difference.

## Probability space

As mentioned at the start, when studying a concrete random phenomenon we usually focus on the sample space $\Omega$, the event space $\mathcal{F}$ and the probability function $P$. We call the triple $(\Omega, \mathcal{F}, P)$ a probability space.

Probability only makes sense when discussed within a fixed probability space. The Bertrand paradox mentioned earlier ultimately comes from an unclear definition of the sample space $\Omega$.

## References and notes

-   [Probability theory (branch of mathematics) - Baidu Baike](https://baike.baidu.com/item/概率论/829122)
-   [Probability - Wikipedia](https://en.wikipedia.org/wiki/Probability)
