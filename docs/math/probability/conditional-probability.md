## Overview

Once some event has happened, the probabilities of other random events may change because we now know more. For example, when pulling for cards in a mobile game, we might think that getting a six-star and not getting a six-star on a single pull are equally likely. But after $50$ pulls in a row without a single six-star, stubbornly believing that "getting a six-star and not getting one are equally likely" no longer seems very wise.

In short, it is necessary to study the probability of events under some known conditions.

## Conditional probability

### Definition

Given that event $A$ has happened, the probability that event $B$ happens under this condition is called the **conditional probability**, written $P(B|A)$.

In a probability space $(\Omega, \mathcal{F}, P)$, if an event $A \in \mathcal{F}$ satisfies $P(A) > 0$, the conditional probability $P(\cdot|A)$ is defined as

$$
P(B|A) = \frac{P(AB)}{P(A)} \quad \forall B \in \mathcal{F}
$$

One can check that the $P(\cdot|A)$ defined this way is a probability function on $(\Omega, \mathcal{F})$.

The following two equations follow directly from the definition of conditional probability:

-   **Multiplication rule**: in a probability space $(\Omega, \mathcal{F}, P)$, if $P(A) > 0$, then for any event $B$,

$$
P(AB) = P(A)P(B|A)
$$

-   **Law of total probability**: in a probability space $(\Omega, \mathcal{F}, P)$, if a group of events $A_1, \cdots, A_n$ are pairwise disjoint and their sum is $\Omega$, then for any event $B$,

$$
P(B) = \sum_{i=1}^{n} P(A_i)P(B|A_i)
$$

### Bayes' formula

In general, suppose the possible causes of event $B$ are $A_1, A_2, \cdots, A_n$. When $P(A_i)$ and $P(B|A_i)$ are known, we can compute the probability of event $B$ with the law of total probability. But in many cases, we need to work backwards from the result "event $B$ happened" to the probability of each cause. This gives

$$
P(A_i|B) = \frac{P(A_iB)}{P(B)} = \frac{P(A_i)P(B|A_i)}{\sum_{j=1}^{n} P(A_j)P(B|A_j)}
$$

This is Bayes' formula.

## Independence of events

When studying conditional probability, it may happen that $P(B|A) = P(B)$. Intuitively, this means whether event $B$ happens tells us nothing about event $A$, i.e. event $B$ is "unrelated" to event $A$. This leads to the following definition.

### Definition

If events $A$, $B$ in the same probability space satisfy

$$
P(AB) = P(A)P(B)
$$

then $A$, $B$ are called **independent**. For multiple events $A_1, A_2, \cdots, A_n$, we call them independent if and only if for any group of events $\{ A_{i_k} : 1 \leq i_1 < i_2 < \cdots < i_k \leq n \}$,

$$
P( A_{i_1}A_{i_2} \cdots A_{i_r} ) = \prod_{k=1}^{r} P(A_{i_k})
$$

### Independence of multiple events

For multiple events, pairwise independence does not in general imply that the events are independent. Consider the following counterexample:

There is a regular tetrahedral die. Three of its faces are painted red, green and blue respectively, and the remaining face has all three colors. Roll the die once, and let events $A$, $B$, $C$ mean that the face touching the table contains red, green and blue respectively.

It is easy to compute $P(A) = P(B) = P(C) = \frac{1}{2}$, and $P(AB) = P(BC) = P(CA) = P(ABC) = \frac{1}{4}$.

Clearly $A, B, C$ are pairwise independent, but since $P(ABC) \neq P(A)P(B)P(C)$, $A, B, C$ are not independent.
