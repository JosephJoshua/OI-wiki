## Related concepts

### Random variable

Given a probability space $(\Omega, \mathcal{F}, P)$, a function $X : \Omega \to \mathbb{R}$ defined on the sample space $\Omega$ may satisfy the following: for every $t \in \mathbb{R}$,

$$
\{ \omega \in \Omega : X(\omega) \le t \} \in \mathcal{F}
$$

If it does, $X$ is called a **random variable**.

### Indicator function

For an event $A$ in the sample space $\Omega$, define the random variable

$$
I_A(\omega) = \begin{cases}
    1, & \omega \in A \\
    0, & \omega \notin A
\end{cases}
$$

$I_A$ is called the **indicator function** of the event $A$.

### Distribution function

For a random variable $X$, the function

$$
F(x) = P( X \leq x )
$$

is called the **distribution function** (cumulative distribution function) of $X$. We write $X \sim F(x)$.

A distribution function has the following properties:

-   **Right-continuity**: $F(x) = F(x + 0)$
-   **Monotonicity**: it is non-decreasing on $\mathbb{R}$ (not necessarily strictly increasing)
-   $F(-\infty) = 0$, $F(+\infty) = 1$

We can also prove that every function satisfying these conditions is the distribution function of some random variable. So distribution functions and random variables correspond one-to-one.

## Types of random variables

A random variable is a function (by definition). Depending on whether its range is countable, it is either **discrete** or **continuous**.

### Discrete random variables

Let $X$ be a discrete random variable whose possible values are $x_1, x_2, \cdots$. Then we can describe $X$ with a list of equations of the form $P\{ X = x_i \} = p_i$. This is the **probability distribution table** (probability mass function) we learned in high school.

### Continuous random variables

Let $X$ be a continuous random variable. Looking at $P\{ X = x \}$ is usually meaningless (because this probability is very likely $0$).

??? note "Why do we say the probability is \"very likely\" $0$"
    Consider this random variable $X$: with probability $\frac{1}{2}$ it takes the value $0$, and with probability $\frac{1}{2}$ it follows the uniform distribution on the open interval $(0, 1)$. Clearly $X$ fits the definition of a continuous random variable.
    
    For every real number $r \in (0, 1)$, it is easy to get $P\{ X = r \} = 0$, but at the same time $P\{ X = 0 \} = \frac{1}{2}$.

On the other hand, let $X \sim F(x)$. Then

$$
P( l < x \leq l + \Delta x ) = F(l + \Delta x) - F(l)
$$

A natural idea is to use the limit $\lim\limits_{\Delta x \to 0^+} \frac{F(l + \Delta x) - F(l)}{\Delta x}$ to describe how likely $X$ is to take the value $l$.

This expression is the familiar derivative. So the problem becomes finding a non-negative function $f(x)$ such that

$$
F(x) = \int_{-\infty}^{x} f(x) \text{d} x
$$

If such an $f(x)$ exists, it is called the **density function** (probability density function) of $X$.

## Independence of random variables

Earlier we discussed the independence of random events. Since random variables are closely tied to random events, we can define independence of random variables in a similar way.

### Definition

If random variables $X, Y$ satisfy, for all $x, y \in \mathbb{R}$,

$$
P( X \leq x, Y \leq y ) = P( X \leq x ) P( Y \leq y )
$$

then the random variables $X, Y$ are called **independent**.

??? note "Note"
    Some readers may notice that high-school textbooks define independence of random variables using probabilities like $P(X = \alpha)$. But a continuous random variable usually takes any specific value with probability $0$, so in the general case it is wiser to define independence using distribution functions.

### Properties

If random variables $X$, $Y$ are independent, then for any functions $f, g$, the random variables $f(X)$ and $g(Y)$ are also independent.

??? warning "Warning"
    Sometimes we study the distribution of some function $f(X, Y)$ (such as $XY^2$) of independent random variables $X$, $Y$.
    
    Even though $X$ and $Y$ are independent, you cannot simply assume that for some value $y$ of $Y$, $f(X, y)$ has the same distribution as $f(X, Y)$.
