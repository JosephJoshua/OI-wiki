Before reading this article, please read [Maximum flow](./max-flow.md) and make sure you know maximum flow algorithms well.

## Overview

Network flow with lower and upper bounds means that each edge of the flow network has an upper bound $c(u,v)$ and a lower bound $b(u,v)$ on its flow. That is, a feasible flow must satisfy $b(u,v) \leq f(u,v) \leq c(u,v)$. At the same time, flow must be balanced at every vertex other than the source and the sink.

Depending on what the problem asks, we can use flow with lower and upper bounds to solve different problems.

## Feasible flow with bounds, without source and sink

You are given a flow network $G$ without a source and sink. Decide whether there is a way to assign a flow to each edge so that every edge's flow is within its bounds and flow is balanced at every vertex.

Assume each edge already carries $b(u,v)$ units of flow, and call this the initial flow. In a new graph, add an edge from $u$ to $v$ with capacity $c(u,v) - b(u,v)$. Then we adjust things on the new graph.

Maximum flow requires the initial flow to be balanced (maximum flow can be seen as maximum flow with bounds where all lower bounds are $0$), but the initial flow we built very likely is not balanced. Suppose for some vertex, initial inflow minus initial outflow equals $M$.

If $M=0$, the flow is balanced and no extra edge is needed.

If $M>0$, the inflow is too large. Create an extra source $S'$, and add an extra edge with capacity $M$ from $S'$ to this vertex.

If $M<0$, the outflow is too large. Create an extra sink $T'$, and add an extra edge with capacity $-M$ from this vertex to $T'$.

If an extra edge is saturated, the balance condition of that vertex can be satisfied; otherwise it cannot. (Because only after adding the extra flow to the original graph is the flow in the original graph balanced.)

After building the graph, run maximum flow from $S'$ to $T'$. If all edges going out of $S'$ are saturated, a feasible flow exists; otherwise it does not.

### Example problem

???+ note "[Luogu P14578 [Template] Feasible Flow with Bounds, without Source and Sink](https://www.luogu.com.cn/problem/P14578)"
    A directed graph $G$ with $n$ vertices and $m$ directed edges. Each edge has a lower bound $l_i$ and an upper bound $r_i$ on its flow.
    
    Construct an assignment in which every edge's flow $w_i$ satisfies $l_i\leq w_i\leq r_i$, and flow is balanced at every vertex, that is, inflow equals outflow at every vertex. Or report that there is no solution.

??? note "Reference code"
    ```cpp
    --8<-- "docs/graph/code/flow/bound/bound_1.cpp"
    ```

## Feasible flow with bounds, with source and sink

You are given a flow network $G$ with a source and a sink. Decide whether there is a way to assign a flow to each edge so that every edge's flow is within its bounds and flow is balanced at every vertex other than the source and the sink.

Let the source be $S$ and the sink be $T$.

We can add an edge from $T$ to $S$ with upper bound $\infty$ and lower bound $0$, which turns this into the feasible flow problem with bounds and without source and sink.

If a solution exists, the value of the feasible flow from $S$ to $T$ equals the flow on the extra edge from $T$ to $S$.

## Maximum flow with bounds, with source and sink

You are given a flow network $G$ with a source and a sink. Decide whether there is a way to assign a flow to each edge so that every edge's flow is within its bounds and flow is balanced at every vertex other than the source and the sink. If there is, find the largest possible flow value.

Find any feasible flow in the network. If there is none, we can stop right away.

Otherwise, consider the residual network after deleting all the extra edges, and adjust the flow on it.

Run maximum flow from $S$ to $T$ once more on the residual network. The answer is the feasible flow value plus this maximum flow value.

??? warning "A very common mistake"
    Run the maximum flow from $S$ to $T$ directly on the residual network left after computing the feasible flow with bounds and source/sink.
    
    Never run it on the original flow network.

## Minimum flow with bounds, with source and sink

You are given a flow network $G$ with a source and a sink. Decide whether there is a way to assign a flow to each edge so that every edge's flow is within its bounds and flow is balanced at every vertex other than the source and the sink. If there is, find the smallest possible flow value.

Similarly, we push back the flow that is not needed in the residual network.

Find any feasible flow in the network. If there is none, we can stop right away.

Otherwise, consider the residual network after deleting all the extra edges.

Run maximum flow from $T$ to $S$ once more on the residual network. The answer is the feasible flow value minus this maximum flow value.

??? note "[AHOI 2014 Side Quests](https://loj.ac/problem/2226)"
    For each story edge from $x$ to $y$ with cost $v$, set the upper bound to $\infty$ and the lower bound to $1$.
    
    For each vertex, add an edge to $T$ with weight $c$, upper bound $\infty$ and lower bound $1$.
    
    Vertex $S$ is node $1$.
    
    Then just run a minimum-cost feasible flow with bounds and source/sink once.
    
    Since the minimum-cost feasible flow method is similar to the minimum feasible flow, we do not go into it here.
