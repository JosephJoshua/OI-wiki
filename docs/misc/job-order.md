You have $n$ jobs, and you need to find an order to run them with the minimum cost. Job $i$ takes time $t_i$, and if job $i$ waits for time $t$, it costs $f_i(t)$.

Formally: given $n$ functions $f_i$ and $n$ numbers $t_i$, find a permutation $p$ that minimizes

$$
F(p)=\sum_{i=1}^nf_{p_i}\left(\sum_{j=1}^{i-1}t_{p_j}\right)
$$

## Special cost functions

### Linear cost functions

First, suppose all the functions are linear, i.e. $f_i(x)=c_ix+d_i$, where $c_i$ is a nonnegative integer. Clearly we can add up the constant terms beforehand, so the functions become $f_i(x)=c_ix$.

Consider two permutations $p$ and $p'$, where $p'$ is obtained from $p$ by swapping the numbers at positions $i$ and $i+1$. Then

$$
\begin{aligned}
F(p')-F(p)&=c_{p'_i}\sum_{j=1}^{i-1}t_{p'_j}+c_{p'_{i+1}}\sum_{j=1}^{i}t_{p'_j}
-\left(c_{p_i}\sum_{j=1}^{i-1}t_{p_j}+c_{p_{i+1}}\sum_{j=1}^{i}t_{p_j}\right)\\
&=c_{p_i}t_{p_{i+1}}-c_{p_{i+1}}t_{p_i}
\end{aligned}
$$

So we just sort with the rule "swap if $c_{p_i}t_{p_{i+1}}-c_{p_{i+1}}t_{p_i}<0$". Written as $\dfrac{c_{p_i}}{t_{p_i}}<\dfrac{c_{p_{i+1}}}{t_{p_{i+1}}}$, this means sorting the permutation by $\dfrac{c_i}{t_i}$ in descending order.

Our approach to this problem is to look at how the cost changes under a small perturbation (an adjacent swap), and greedily choose the best solution.

### Exponential cost functions

Suppose the cost functions have the form $f_i(x)=c_i\mathrm{e}^{ax}$, where $c_i\ge 0,a>0$.

Using the same idea as before, look at how the cost changes when swapping the numbers at positions $i$ and $i+1$. The resulting algorithm sorts the permutation by $\dfrac{1-\mathrm{e}^{at_i}}{c_i}$ in ascending order.

### Identical increasing functions

Suppose all $f_i(x)$ are the same increasing function. Then clearly we just sort the permutation by $t_i$ in ascending order.

## Livshits–Kladov theorem

The Livshits–Kladov theorem says this holds if and only if the cost functions fall into one of these three cases:

-   Linear functions: $f_i(t) = c_it + d_i$, where $c_i\ge 0$;
-   Exponential functions: $f_i(t) = c_i \mathrm{e}^{a t} + d_i$, where $c_i,a>0$;
-   Identical increasing functions: $f_i(t) = \phi(t)$, where $\phi(t)$ is an increasing function.

The theorem is proved under the assumption that the cost functions are smooth enough (have third derivatives). In these three cases, the optimal solution can be found by a simple sort in $O(n\log n)$ time.

**This page is mainly translated from the article [Задача Джонсона с одним станком](http://e-maxx.ru/algo/johnson_problem_1) and its English translation [Scheduling jobs on one machine](https://cp-algorithms.com/schedules/schedule_one_machine.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
