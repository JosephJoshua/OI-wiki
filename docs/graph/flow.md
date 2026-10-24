This page covers the basics of network flow.

## Overview

A network is a special directed graph $G=(V,E)$. It differs from an ordinary directed graph in that it has capacities, a source and a sink.

-   Each edge $(u, v)$ in $E$ has a weight called its capacity, written $c(u, v)$. When $(u,v)\notin E$, we can assume $c(u,v)=0$.

-   $V$ has two special vertices: the source $s$ and the sink $t$ ($s \neq t$).

For a network $G=(V, E)$, a flow is a function from the edge set $E$ to the integers or the reals that satisfies the following properties.

1.  Capacity constraint: the flow on each edge cannot exceed its capacity, that is, $0 \leq f(u,v) \leq c(u,v)$;
2.  Flow conservation: every vertex $u$ other than the source and the sink has net flow $0$. Here the net flow of $u$ is defined as $f(u) = \sum_{x \in V} f(u, x) - \sum_{x \in V} f(x, u)$.

For a network $G = (V, E)$ and a flow $f$ on it, we define the value $|f|$ of $f$ as the net flow $f(s)$ of $s$. As a consequence of flow conservation, this also equals the negated net flow of $t$, $-f(t)$.

For a network $G = (V, E)$, if $\{S, T\}$ is a partition of $V$ (that is, $S \cup T = V$ and $S \cap T = \varnothing$) with $s \in S, t \in T$, we call $\{S, T\}$ an $s$-$t$ cut of $G$. The capacity of the $s$-$t$ cut $\{S, T\}$ is defined as $||S, T|| = \sum_{u \in S} \sum_{v \in T} c(u, v)$.

## Common problems

Common network flow problems include, but are not limited to, the following.

-   Maximum flow: for a network $G = (V, E)$, assign a flow to each edge to get a valid flow $f$ whose value is as large as possible. Such an $f$ is called a maximum flow of $G$.
-   Minimum cut: for a network $G = (V, E)$, find an $s$-$t$ cut $\{S, T\}$ whose total capacity is as small as possible. The total capacity of such $\{S, T\}$ is called the minimum cut of $G$.
-   Minimum-cost maximum flow: in a network $G = (V, E)$, each edge has a weight $w(u, v)$ called its cost, which is the cost of sending one unit of flow through $(u, v)$. Among all maximum flows of $G$, the one with the smallest total cost is called the minimum-cost maximum flow.

We will cover them in detail in later sections.

## Example problems: the 24 network flow problems

The "24 network flow problems" is a problem list widely shared on the Chinese internet ([LibreOJ](https://loj.ac/problems/tag/30)/[Luogu](https://www.luogu.com.cn/problem/list?tag=332)). It has existed since at least around 2010. The list introduces some classic techniques for modeling other problems as network flow problems. Because of their age, these problems are not necessarily the most representative network flow problems, but they are still worth reading for anyone serious about competitive programming.
