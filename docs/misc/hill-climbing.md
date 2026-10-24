## Introduction

Hill climbing is a local-improvement method. It is a heuristic method and an improvement on depth-first search: it uses feedback to help decide which solution to generate next.

Put simply: when you cannot jump straight to the optimal solution, but you can tell which of two solutions is better, you use some feedback to generate a new candidate solution.

So each time, hill climbing looks for a new solution near the best solution $x$ found so far. If the new solution $x'$ is better, move to $x'$; otherwise stay put.

This clearly works for unimodal functions.

Q: If we already know the function is unimodal, why not just use ternary search?

A: The advantage of hill climbing is that when you don't know how to write the intended solution (common in nasty computational geometry and nasty math problems), or when the state has many dimensions and divide and conquer is hard to write (Example 2 can be solved correctly with binary search), you can still get the optimal solution through very brute-force computation.

But for most functions you need to optimize, hill climbing easily gets stuck in a local optimum, as in the figure below (the optimal solution is $\color{green}{\Uparrow}$, while hill climbing may end up at $\color{red}{\Downarrow}$).

![](./images/hill-climbing.png)

## Implementation

Hill climbing usually introduces a temperature parameter (similar to simulated annealing). As an analogy, hill climbing is like a drunk rabbit hopping around on a mountain. Each time it hops toward what it believes is higher ground (often only a rough trend). It might reach the top in one hop, or it might overshoot and land on the other side. That's fine: after going over, the rabbit will hop back. But clearly this alone is useless, and the rabbit would never find its way. So during the process the rabbit calms down and becomes more careful with each hop, hopping a bit less, so that it settles at a good optimum.

The rabbit gradually sobering up is the cooling process: the temperature parameter keeps decreasing as we climb.

About cooling: the cooling factor is a constant slightly less than $1$, usually chosen from $[0.985, 0.999]$.

## Example problems

???+ example "[JSOI2008 Spherical Space Generator](https://www.luogu.com.cn/problem/P4035)"
    You are given $n + 1$ points in $n$-dimensional space. They are known to lie on the same $n$-dimensional sphere. Find the center of the sphere. $n \leq 10$, and the absolute value of each coordinate is at most $20000$.

??? note "Solution"
    This is clearly a unimodal function, so hill climbing works. The algorithm for this problem:
    
    1.  Initialize the center as the centroid of the given points (each coordinate is the average of that coordinate over all given points), to reduce the amount of searching.
    2.  For the current center, compute the average Euclidean distance from the known points to it.
    3.  Go through all known points. Keep a change vector $\textit{cans}$ (recorded separately for each dimension). For each point's Euclidean distance, if it is larger than the average, add the difference to the change; otherwise subtract it. In fact you don't need to compare at all: just ignore absolute values and compute directly with the coordinates. You can picture this as a new center being pushed around in space: it gets pulled a bit toward points that are too far, and pushed a bit away from points that are too close.
    4.  Multiply the recorded $\textit{cans}$ by the temperature, update the center, and go back to step 2.
    5.  Stop when the temperature drops below some given threshold.
    
    So when updating the center, we don't add the change directly, but the change times the temperature.
    
    Not every hill climbing problem can be solved with temperature in exactly this way; this is just one example.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/hill-climbing/hill-climbing_1.cpp"
    ```

???+ example "[BZOJ 3680 Beat Up XXX](https://hydro.ac/p/bzoj-P3680)"
    Find the weighted Fermat-like point of $n$ points.

??? note "Solution"
    The framework is similar, using a bit of physics.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/hill-climbing/hill-climbing_2.cpp"
    ```

## Optimization

An obvious idea is to climb several times to get as good an answer as possible. You can vary the initial state, the cooling factor, the initial temperature, and so on, and keep a global best solution. After each climb, update the global best.

The possible problem with this is exceeding the time limit. In a real contest, build large test data by hand to tune the parameters.

## Drawbacks

The drawback of hill climbing was already mentioned above: it easily gets stuck in a local optimum. When the objective function is not unimodal, this drawback is fatal. That is why we introduce [**simulated annealing**](./simulated-annealing.md).
