## Introduction

Simulated annealing is a randomized algorithm. When a problem has a huge (even infinite) number of candidate solutions and the objective is not a unimodal function, we often use simulated annealing to solve it.

## Explanation

Looking at how the [hill climbing algorithm](./hill-climbing.md) works, we notice that it simply throws away any non-optimal solution near the current best solution. But in many cases we need to accept such a non-optimal solution in order to escape a local optimum. Doing this is the idea of simulated annealing.

??? note "What is annealing? (from [Baidu Baike](https://baike.baidu.com/item/%E9%80%80%E7%81%AB/1039313))"
    Annealing is a heat treatment process for metals. The metal is slowly heated to a certain temperature, held there for long enough, and then cooled at a suitable rate. Its purposes are to reduce hardness and improve machinability; to remove residual stress, stabilize dimensions, and reduce the tendency to deform and crack; and to refine the grains, adjust the microstructure, and remove structural defects. More precisely, annealing is a heat treatment process for materials, both metallic and non-metallic. The purposes of annealing new materials are partly the same as, and partly different from, those of traditional metal annealing.

Because the annealing process brings in more randomness, the probability of reaching the optimal solution increases greatly. So we can simulate this process, using the objective function as the energy function.

### How it works

In one sentence: if the new state is better, update the answer; otherwise, accept the new state with a certain probability.

Let the current temperature be $T$. Let $\Delta E$ ($\Delta E\geqslant 0$) be the energy (value) difference between the new state $S'$ and the known state $S$ (the new state is obtained from the known state randomly). Then the probability of moving to the new state (updating the best solution) is

$$
P(\Delta E)=
\begin{cases}
1,                              & S' \text{ is better than } S,\\
\mathrm{e}^\frac{-\Delta E}{T}, & \text{otherwise}.
\end{cases}
$$

**Note**: sometimes, to improve the quality of the solution, after simulated annealing finishes we randomly try many states near the solution found, at the current temperature, to look for a better one (the process is similar to simulated annealing).

### How to anneal (cool down)

Simulated annealing has three parameters: the initial temperature $T_0$, the cooling factor $d$, and the final temperature $T_k$. $T_0$ is a fairly large number, $d$ is a number very close to $1$ but less than $1$, and $T_k$ is a positive number close to $0$.

First set the temperature $T=T_0$. Then perform one transition attempt as described above, and set $T=d\cdot T$. When $T<T_k$, simulated annealing ends, and the current best solution is the final answer.

Note that to get a more accurate answer, we usually do not take the current solution as the answer directly. Instead, we keep track of the best value among all solutions seen during annealing.

Here is a picture from [Simulated annealing - Wikipedia](https://en.wikipedia.org/wiki/Simulated_annealing) (as the temperature drops, the jumps become less and less random, and the best solution becomes more and more stable).

![](./images/simulated-annealing.gif)

## Implementation

The code here uses [BZOJ 3680 — Hanging XXX](https://hydro.ac/p/bzoj-P3680) (finding the weighted Fermat-like point of $n$ points) as an example.

```cpp
--8<-- "docs/misc/code/simulated-annealing/simulated-annealing_1.cpp"
```

## Some tricks

### Simulated annealing by segments

Sometimes the function has many peaks, and simulated annealing has trouble finding the optimum.

In that case, you can split the whole domain into several segments, run simulated annealing once on each segment, and then take the best result.

### Running until the time limit

The `clock()` function returns how long the program has been running.

You can replace `simulateAnneal();` in the main program with `while ((double)clock()/CLOCKS_PER_SEC < MAX_TIME) simulateAnneal();`. This keeps running simulated annealing until the time used is about to exceed the time limit.

Here `MAX_TIME` is a self-chosen number slightly smaller than the time limit (in seconds).

## Exercises

-   [BZOJ 3680 — Hanging XXX](https://hydro.ac/p/bzoj-P3680)
-   [JSOI 2016 — Bomb Attack](https://loj.ac/problem/2076)
-   [HAOI 2006 — Evenly Dividing Data](https://www.luogu.com.cn/problem/P2503)
