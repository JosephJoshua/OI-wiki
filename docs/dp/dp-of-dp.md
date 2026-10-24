author: Hope666666

## Introduction

This article introduces the idea of DP of DP (a DP nested inside another DP), and shows how to apply it to concrete problems through two example problems.

## Idea

"DP of DP" means that during dynamic programming, we abstract the process of solving a subproblem (usually itself a DP) into an automaton (DFA), and then design a new layer of DP on top of this automaton.

This technique is mainly used for a class of **sequence counting**, **probability** or **expected value** problems. A typical problem has the following structure:

-   We are given an alphabet $\Sigma$ and a set $A\subseteq\Sigma^n$ of "valid sequences" of length $n$ over it. Depending on the alphabet, the sequences can be binary strings, digit strings, sequences of states, and so on.
-   For each specific sequence $s\in\Sigma^n$, we can use dynamic programming to decide whether it is valid (i.e. $s\in A$), compute its weight, or find some related value.
-   In the end, we want to compute the number of sequences in $A$, their total weight, the expected value, etc.

Enumerating all sequences is infeasible here. So we abstract the process of "deciding whether a sequence is valid" (the inner DP) into a [deterministic finite automaton](../misc/fsm.md#确定性有限状态自动机) (DFA). In general, for a fixed sequence $s\in\Sigma^n$, the state function of the inner DP can be written as $g(i,x;s)$: the value of some quantity after processing the prefix of $s$ of length $i$, with the other state components equal to $x$. Correspondingly, the state transition equation of the inner DP is

$$
g(i,\cdot;s) = G(g(i-1,\cdot;s),s_i).
$$

That is, the function $g(i,\cdot;s)$ is uniquely determined by the previous function $g(i-1,\cdot;s)$ and the current character $s_i$. If we view the function $g(i,\cdot;s)$ as a state of an automaton, then the state transition equation of the inner DP gives a transition of the automaton. So the automaton $(Q,\Sigma,\delta,q_0,F)$ corresponding to the inner DP looks like this:

-   The state set $Q$ is the set of functions $g(i,\cdot;s)$ for all possible $s\in\Sigma^n$ and $i=0,1,\cdots,n$;
-   The transition function $\delta:Q\times\Sigma\to Q$ is $G$ in the state transition equation of the inner DP;
-   The start state $q_0$ is usually obvious: it is the initial state of the inner DP;
-   The set of accepting states $F$ corresponds to all valid sequences $s\in A$.

The function $g(i,\cdot;s)$ itself can be quite complex. So when solving a concrete problem, we usually need [bitmask compression of states](./state.md) or DFA minimization techniques to shrink the state space. This is the main reason why DP of DP can greatly reduce time and space complexity compared to a brute-force DP.

After abstracting the inner DP into a DFA, we can design a new DP on this DFA to solve the original problem: the outer DP. For simplicity, take a simple counting problem as an example. The state function of the outer DP is $f(i,q)$: the number of prefixes of length $i$ that reach state $q\in Q$ of the DFA. Its state transition equation is

$$
f(i,q) = \sum_{c\in\Sigma}\sum_{q'\in Q:\delta(q',c)=q} f(i-1,q').
$$

The initial value is of course $f(0,q_0)=1$, and the final answer can usually be computed easily from $\{f(n,q):q\in F\}$. The outer DP is in fact a special case of [DP on a DAG](./dag.md).

## Example problems

The next two example problems explain the general method of DP of DP in detail.

### Example 1

???+ example "[Hero meet devil](https://www.luogu.com.cn/problem/P10614)"
    You are given a string $S$ over the alphabet `ACGT`, with $|S|\le 15$. For each $0\leq i \leq |S|$, count the strings $T$ of length $m$ over the alphabet `ACGT` whose longest common subsequence with $S$ has length $i$.

??? note "Solution"
    The first DP that comes to mind is: let $f_{i,j}$ be the number of strings $T$ of length $i$ whose longest common subsequence with $S$ has length $j$. But this cannot be transitioned. The main problem is that we do not know which characters this longest common subsequence corresponds to.
    
    Consider the naive process of computing the longest common subsequence. Let $g_{i,j}$ be the length of the longest common subsequence of the first $i$ characters of $T$ and the first $j$ characters of $S$. Then
    
    $$
    g_{i,j} = \max\{g_{i-1,j},g_{i,j-1},g_{i-1,j-1}+[T_i=S_j]\}.
    $$
    
    We notice that for a fixed $i$, recording the value of every entry of the one-dimensional array $g_i$ is enough to exactly describe the LCS state between $S$ and the first $i$ characters of $T$. Since $S$ has length at most $15$, this idea is feasible.
    
    So we redefine the state $f_{i,x}$ as the number of strings $T$ of length $i$ whose DP array with $S$ (i.e. $g_i$) is in state $x$. This DP seems to have many states, but since $g_{i,j}-g_{i,j-1}\in\{0,1\}$, we can store the difference array of $g_i$ instead, and the number of states is $2^{|S|}$.
    
    Now think about the transition. If we know the array $g_i$ and also know $T_{i+1}$, we can compute $g_{i+1}$ with the naive LCS transition (the DP equation above). So the naive LCS becomes the inner DP that helps $f$ transition.
    
    So we enumerate $T_{i+1}$, compute the state $x'$ that $x$ transitions to, and add $f_{i,x}$ to $f_{i+1,x'}$. This completes the state transition of the outer DP. Finally, let $\textit{ans}_i$ be the answer for LCS length $i$. Enumerate every state $x$ and add $f_{m,x}$ to $\textit{ans}_{\operatorname{popcount}(x)}$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/dp-of-dp/dp-of-dp_1.cpp"
    ```

### Example 2

???+ example "[\[ZJOI2019\] Mahjong](https://loj.ac/p/3042)"
    Suppose mahjong tiles come in $n$ ranks, with $4$ tiles of each rank. A meld is either three tiles of consecutive ranks $i,i+1,i+2$ (a chow) or three tiles of the same rank $i,i,i$ (a pung). A pair is two tiles of the same rank $i,i$. A sequence of mahjong tiles is a winning hand if and only if (viewed as a multiset) it can be split into four melds and one pair, or into seven distinct pairs. You are given $13$ initial tiles. The remaining $4n-13$ tiles are shuffled uniformly at random and drawn one by one. Find the expected number of further tiles you need to draw until there is a subsequence that is a winning hand. Output the answer modulo $998244353$.

??? note "Solution"
    First, for a set of tiles, we only need to consider how many tiles of each rank there are, not their order. So any prefix of any tile sequence can be turned into a sequence of length $n$ where each position is between $0$ and $4$. Initially there are $a_i$ tiles of rank $i$, which means the $i$-th number $x_i$ of the sequence is limited to integers in $[a_i,4]$. Note that this converted sequence ignores the drawing order, while the tile sequences in the problem do take order into account.
    
    Let $X$ be the minimum number of draws needed to win. Computing the expected value $\mathbf E[X]$ directly is hard, so we transform it as follows. Let $h_i$ be the number of ways to choose $i$ tiles from the remaining tiles (different tiles of the same rank count as different) such that the hand is **not yet winning**. In a corresponding tile sequence, these $i$ tiles must come before the remaining $(4n-13-i)$ tiles, but the order within these $i$ tiles and within the remaining $(4n-13-i)$ tiles is arbitrary. So the number of tile sequences that cannot win after drawing only the first $i$ tiles is
    
    $$
    h_i\cdot i!(4n-13-i)!.
    $$
    
    Since the total number of tile sequences is $(4n-13)!$, the probability that you cannot win after drawing only the first $i$ tiles is
    
    $$
    \mathbf P[X>i] = \dfrac{h_i\cdot i!(4n-13-i)!}{(4n-13)!}.
    $$
    
    Using the tail-sum formula, we get the expected value we want:
    
    $$
    \mathbf E[X] = \sum_{i=0}^\infty\mathbf P[X>i] = 1 + \sum_{i=1}^{4n-13}\dfrac{h_i\cdot i!(4n-13-i)!}{(4n-13)!}.
    $$
    
    Now the problem becomes how to compute $h_i$. We solve it with DP of DP.
    
    First, consider the inner DP, which uses dynamic programming to decide whether a (converted) sequence is a winning hand. The seven-pairs case is easy, so we focus on the first kind of winning hand. Let $g_{0/1,i,j,k}$ be the maximum number of melds after processing the first $i$ ranks, with $j$ groups of $(i-1,i)$ and $k$ tiles of rank $i$ left over, and with no pair / a pair (i.e. $0/1$). If running this DP on a sequence gives a $g_{1,n}$ that contains a number greater than or equal to $4$, the sequence is a winning hand.
    
    The state transitions of this DP are fairly complex. We discuss them in two steps. Step one: consider the transition for $g_{0/1,i}$. That is, if we add $x_i$ tiles of rank $i$ to the current hand without forming a new pair, how does the number of melds change? Clearly, if after adding $x_i$ tiles of rank $i$ we want $\ell$ chows, $j$ groups of $(i-1,i)$ and $k$ single tiles of rank $i$, we should transition from $(g_{0/1,i-1})_{\ell,j}$ (this choice wastes as little as possible), and use the remaining $(x_i-\ell-j-k)$ tiles to form as many pungs as possible. Going through all possibilities gives the following transition equation:
    
    $$
    \tilde G(g_{0/1,i-1}, x_i)_{j,k} = \max\left\{(g_{0/1,i-1})_{\ell,j} + \ell + \left\lfloor\dfrac{x_i-\ell-j-k}{3}\right\rfloor:\ell+j+k\le x_i\right\}.
    $$
    
    Step two: consider the case where a pair needs to be formed. When adding $x_i$ tiles of rank $i$, there are three transitions:
    
    -   Add $x_i$ tiles to $g_{0,i-1}$ to get $g_{0,i}$;
    -   Add $x_i$ tiles to $g_{1,i-1}$ to get $g_{1,i}$;
    -   If $x_i\ge 2$, add $x_i-2$ tiles to $g_{0,i-1}$ to get $g_{1,i}$.
    
    This gives all the transitions from $g_{i-1}$ to $g_i$ when adding $x_i$ tiles.
    
    With the state transitions of the inner DP worked out, we can build the **winning-hand automaton**. Its transitions are the inner DP transitions above. We still need to decide how to represent each state of the automaton. Each state corresponds to one possible value of $g_i$, which has three dimensions $(0/1,j,k)$. The $(i-1,i)$ groups and $i$ tiles kept in dimensions $j$ and $k$ are all meant to form chows later, and three identical chows can always be regrouped into three pungs. So we only need to consider forming at most $2$ identical chows, and only need to keep at most $2$ of each kind, i.e. $j,k\in\{0,1,2\}$. So $g_i$ can be represented as a $2\times 3\times 3$ array. In addition, to track the seven-pairs winning hand, each state also needs a counter for the maximum number of pairs that can currently be formed.
    
    Each element of the array $g_i$ may take values in $\{-\infty\}\cup\mathbf N$. But since $4$ or more melds always means a winning hand, we can cap each element at $4$. Since adding any tiles to a winning sequence still gives a winning sequence, we can use the idea of DFA minimization and merge all winning states into one state. So for non-winning states, each position of $g_1$ only needs values in $\{-\infty\}\cup\{0,1,2,3\}$, and each position of $g_0$ takes values in $\{-\infty\}\cup\{0,1,2,3,4\}$. In the implementation, $-\infty$ is represented by $-1$.
    
    Even so, there are still a great many possible states: $1+7\times 5^9\times 6^9$ in total. Enumerating them is not practical. In fact, the vast majority of these never actually appear in the winning-hand automaton. To avoid considering states that do not exist, we can use the idea of BFS: start from the initial state and expand states step by step, stopping at the winning state. The automaton obtained this way has $N = 2092$ states.
    
    Finally, consider the DP on the winning-hand automaton (the outer DP). Let $f_{i,j,k}$ be the number of ways in which, after processing the first $i$ ranks, a total of $j$ tiles have been drawn and we are at state $k$ of the winning-hand automaton. For the transition, enumerate the number of drawn tiles $0\leq t\leq 4-a_i$, where $a_i$ is the number of tiles of rank $i$ among the initial $13$ tiles. Multiply the previous count by $\dbinom{4-a_i}{t}$, the number of ways to choose $t$ tiles out of $4-a_i$, and add it up. Formally:
    
    $$
    f_{i,j+t,k'} \gets f_{i,j+t,k'} + \dbinom{4-a_i}{t}f_{i-1,j,k}.
    $$
    
    Here $k'=\delta(k,a_i+t)$ is the state reached by adding $a_i+t$ tiles to state $k$ of the automaton. After the outer DP, we can compute the number of ways to have drawn $i$ tiles without winning:
    
    $$
    h_i=\sum_{k\notin F} f_{n,i,k},
    $$
    
    where $F$ is the set of winning states. Substituting into the expression above gives the expected value we want.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/dp-of-dp/dp-of-dp_2.cpp"
    ```

## Exercises

-   [CF979E Kuro and Topological Parity](https://codeforces.com/problemset/problem/979/E)
-   [\[TJOI2018\] Garden Party](https://loj.ac/p/2575)
-   [\[NOI2022\] Removing Stones](https://loj.ac/p/3848)
