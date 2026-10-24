Competitive programming sometimes uses [randomized algorithms](../../misc/rand-technique.md). The correctness and time/space complexity of these algorithms usually rely on the premise that "the probability of certain random events is small". For example, the complexity of quicksort relies on the event "the chosen `pivot` is almost the smallest or largest element" happening rarely.

This article gives a short introduction to some tools for analyzing randomized algorithms, along with a few simple examples of how to use them.

## Union Bound

Let $A_1, \cdots, A_m$ be random events. Then

$$
P\left\{ \bigcup_{i=1}^m A_i \right\} \leq \sum_{i=1}^m P\{A_i\}
$$

That is: the probability that at least one event in a group happens is at most the sum of their individual probabilities.

In fact, this result can be strengthened a little:

-   The probability that at least one event in a group happens is **at least** the sum of their individual probabilities, minus the sum of the probabilities of every pair happening together.
-   The probability that at least one event in a group happens is **at most** the sum of their individual probabilities, minus the sum of the probabilities of every pair happening together, plus the sum of the probabilities of every triple happening together.
-   ...

As more levels are added, the alternating upper and lower bounds get tighter and tighter. This series of results looks like the inclusion–exclusion principle, and the proof is also similar to inclusion–exclusion, so we omit it here.

## Markov's inequality

Let $X$ be a random variable that takes non-negative values. Then for any positive real number $a$,

$$
P\{ X \geq a \} \leq \frac{EX}{a}
$$

In fact, since Markov's inequality uses no information about the distribution of the random variable other than its expected value, the bounds you get by applying it directly are usually very loose.

### Proof

Let $I$ be the indicator function of the event $X \geq a$. Then

$$
I \leq \frac{X}{a}
$$

and so

$$
P\{ X \geq a \} = EI \leq E \left[ \frac{X}{a} \right] = \frac{EX}{a}
$$

## Chebyshev's inequality

Let $X$ be a random variable. Then for any $a > 0$,

$$
P \{ |X - EX| \geq a \} \leq \frac{DX}{a^2}
$$

In particular, taking $a$ to be $k\sigma$ gives

$$
P \{ |X - EX| \geq k\sigma \} \leq \frac{1}{k^2}
$$

where $\sigma$ is the standard deviation of $X$.

### Proof

From the given information,

$$
P \{ |X - EX| \geq a \} = P \{ (X - EX)^2 \geq a^2 \}
$$

Note that $(X - EX)^2$ is non-negative, so by Markov's inequality

$$
P \{ (X - EX)^2 \geq a^2 \} \leq \frac{E(X - EX)^2}{a^2} = \frac{DX}{a^2}
$$

## Chernoff bound

The general Chernoff bound follows from applying Markov's inequality directly to the random variable $\mathrm{e}^{tX}$:

Let $X$ be a random variable. Then for any $t > 0$,

$$
P\{ X \geq a \} = P\{ \mathrm{e}^{tX} > \mathrm{e}^{ta} \} \leq \frac{E \mathrm{e}^{tX}}{\mathrm{e}^{ta}}
$$

Similarly, when $t < 0$,

$$
P\{ X \leq a \} = P\{ \mathrm{e}^{tX} > \mathrm{e}^{ta} \} \leq \frac{E \mathrm{e}^{tX}}{\mathrm{e}^{ta}}
$$

### Chernoff bound for sums of Poisson trials

The random variables in competitive programming are usually not that "general". We can describe them using Poisson trials from probability theory.

A Poisson trial is a random experiment with only two possible outcomes.

The result of one Poisson trial can be described by a random variable $X$ taking the value $0$ or $1$, with probability distribution

$$
P\{ X = i \} = \begin{cases}
    p_i, & i = 1 \\
    1 - p_1, & i = 0
\end{cases}
$$

For Poisson trials we have the following result:

For $n$ independent Poisson trials $X_1, X_2, \cdots, X_n$, let $X = \sum_{i=1}^{n} X_i$ and $\mu = EX$. Then for any $0 < \epsilon < 1$,

$$
P\left\{ |X - \mu| \geq \epsilon \mu \right\} \leq 2 \exp\left( - \frac{1}{3} \mu \epsilon^2 \right)
$$

## Hoeffding's inequality

If $X_1, \cdots, X_n$ are mutually independent real random variables with $X_i\in [a_i,b_i]$, and $X=\sum\limits_{i=1}^n X_i$, then

$$
P\{ |X - EX| \geq \epsilon \} \leq 2\exp \left( \frac {-2\epsilon^2}{\sum\limits_{i=1}^n (b_i-a_i)^2} \right)
$$

The Chernoff bound and Hoeffding's inequality both limit how far a random variable can stray from its expected value. Their proofs are fairly long; interested readers can look at the relevant chapters of the book Probability and Computing.

From experience, if $EX$ is not too close to $a_1+\cdots+a_n$, the bound given by this inequality is usually fairly tight. If it is very close (for example in [UOJ #72, a brand-new approach](https://matthew99.blog.uoj.ac/blog/5511)), the bound is usually very loose, and the Chernoff bound is a better choice.

## Example applications

### Example: estimating pi by throwing random points

Consider the following algorithm for estimating the value of $\pi$:

Generate $n$ random points in the square $[-1, 1]^2$, and let $m$ be the number of them that fall inside the unit disk $x^2 + y^2 \leq 1$. Then take $\dfrac{4m}{n}$ as an approximation of $\pi$.

Question: if we want the algorithm above to return a result with relative error at most $\epsilon$ with probability at least $(1 - \delta)$, how should we choose $n$?

??? note "Answer"
    Let $X_i$ denote the event "the $i$-th random point is inside the unit circle". Then the total number of points inside the circle is $X = \sum_{i=1}^{n} X_i$. We need to find a suitable $n$ such that
    
    $$
    P\left\{ \left| \frac{4X}{n} - \pi \right| \geq \epsilon \pi \right\} \leq \delta
    $$
    
    This is equivalent to
    
    $$
    P\left\{ \left| X - \frac{\pi}{4}n \right| \geq \epsilon \cdot \frac{\pi}{4}n  \right\} \leq \delta
    $$
    
    By the Chernoff bound, it is enough to make
    
    $$
    2 \exp\left( - \frac{1}{3} \epsilon^2 \cdot \frac{\pi}{4}n \right) \leq \delta
    $$
    
    Solving this gives
    
    $$
    n \geq \frac{12}{\pi} \epsilon^{-2} \ln \frac{2}{\delta}
    $$
    
    That is, when $n = \Omega(\epsilon^{-2} \ln \frac{1}{\delta})$, we get the required accuracy.

### Example: the lottery problem

A box contains $n$ balls, and exactly $k$ of them are grand prizes. You draw from the box several times, independently and uniformly at random, putting the ball back after each draw. How many draws guarantee, with probability at least $(1 - \epsilon)$, that **every** prize ball is drawn at least once?

??? note "Answer"
    If there is only one prize ball, then $M=n\log\epsilon^{-1}$ draws are enough, because the probability that all $M$ draws miss it is
    
    $$
    \Big(1-\dfrac 1n\Big)^{n\log\epsilon^{-1}}\leq e^{\log\epsilon}=\epsilon
    $$
    
    Now there are $k>1$ prize balls. By the Union Bound, we only need to make sure the probability that each prize ball is missed is at most $\dfrac \epsilon k$. So the answer is $n \log \dfrac{k}{\epsilon}$.

### Example: randomly choosing half the elements

Give an algorithm that chooses, uniformly at random, a subset of size $\dfrac{n}{2}$ from $n$ elements, where $n$ is guaranteed to be even. The only source of randomness you may use is a fair coin, and you should try to keep the number of coin flips small (it does not have to be minimal).

??? note "Solution"
    The first algorithm that comes to mind is:
    
    -   By flipping the coin $n$ times, we can choose a subset uniformly at random from all subsets.
    -   Repeat this process until the chosen subset has size exactly $\dfrac n2$.
        -   Note that subsets of size $\dfrac n2$ make up at least $\dfrac 1n$ of all subsets, so the expected number of repetitions is $\leq n$.
    
    This algorithm needs $n^2$ coin flips in expectation.
    
    Another algorithm:
    
    -   We can choose 1 out of $n$ uniformly at random with $2\lceil\log_2 n\rceil$ coin flips in expectation.
        -   Concretely: generate a random binary number with $\lceil\log_2 n\rceil$ bits. If it is at least $n$, try again; otherwise choose the element with that index (indices start from 0) and stop.
    -   Then we choose one element from all elements, then another from the remaining elements, and so on, until $\dfrac n2$ elements have been chosen.
    
    This algorithm needs $n\lceil\log_2 n\rceil$ coin flips in expectation.
    
    Now stitch the two algorithms together:
    
    -   First use the first algorithm to get a random subset.
    -   If the subset has fewer than $\dfrac n2$ elements, use the second algorithm to keep adding elements until the size reaches $\dfrac n2$.
    -   If the subset has more than $\dfrac n2$ elements, use the second algorithm to keep removing elements until the size goes down to $\dfrac n2$.
    
    Let us analyze the number of operations (additions/removals of elements) needed in the second and third steps:
    
    -   Let the 0/1 random variable $X_i$ indicate whether $i$ is chosen in the initial subset, and let $X:=X_1+\cdots+X_n$ be the size of the subset. Then the number of operations needed in the second and third steps equals $\big|X-\mathrm{E}[X]\big|$. Taking $t=c\cdot\sqrt n$ (where $c$ is any constant) in Hoeffding's inequality gives $\mathrm{Pr}\Big[\big|X-\mathrm{E}[X]\big|\geq t\Big]\leq 2\mathrm{e}^{-c^2}$. In other words, by allowing a deviation of order $\Theta(\sqrt n)$, we can make the failure probability an arbitrarily small constant.
    
    So far we have shown: with high probability, this algorithm uses at most $n+\Theta(\sqrt n\log n)$ coin flips.
    
    -   Here $n$ comes from the coin flips used to get the initial subset; $\Theta(\sqrt n\log n)$ is the total cost of $\Theta(\sqrt n)$ additions/removals.
    
    ??? note "Computing the expected complexity"
        Let us analyze it from another angle and compute the expected number of coin flips of this algorithm.
        
        Use Hoeffding's inequality to bound the expected number of operations in the second and third steps:
        
        $$
        E|X - EX| = \int_0^\infty P\{ |X - E[X]| \geq t \} \mathrm{d}t \leq 
        2 \int_0^\infty \exp \left(-\frac {t^2}{n}\right) \mathrm{d}t=\sqrt{\pi n}
        $$
        
        So the expected number of coin flips needed in the second and third steps is $\sqrt{\pi n}\cdot2\lceil\log_2 n\rceil$.
        
        In summary, this algorithm needs $n+2\sqrt{\pi n}\lceil\log_2 n\rceil$ coin flips in expectation.

### Exercise: Balls and Bins

$n$ balls are thrown independently and uniformly at random into $n$ bins. Prove that with probability $1 - \dfrac{1}{n}$, the number of balls in the fullest bin is at least $\Omega \left( \dfrac{\log n}{\log \log n} \right)$.
