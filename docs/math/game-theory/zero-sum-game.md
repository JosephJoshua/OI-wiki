Prerequisites: [Introduction to game theory](./intro.md)

This article discusses (two-player) [zero-sum games](./intro.md#zero-sumnon-zero-sum-games).

In a zero-sum game, the payoffs of the two players always add up to zero, so one player's gain is always the other player's loss. Zero-sum games can be seen as a special case of constant-sum games. Conversely, any constant-sum game can be turned into an equivalent zero-sum game by adding or subtracting a constant to all of one player's payoffs, so we only need to discuss zero-sum games.

Zero-sum games that appear in competitive programming roughly fall into two types: sequential zero-sum games and simultaneous zero-sum games.

## Sequential zero-sum games

In a sequential zero-sum game, the two players take turns until the game ends.

In a sequential zero-sum game, the players' payoff functions have a recursive structure. The game positions $S$ fall into three kinds: terminal positions $S_0$, positions $S_1$ where player $1$ moves, and positions $S_2$ where player $2$ moves. Suppose that at a terminal position $s\in S_0$, player $1$ gets payoff $v(s)$, and so player $2$ gets payoff $-v(s)$. So when it is player $2$'s turn, maximizing their own payoff is the same as minimizing player $1$'s payoff. Therefore, assuming both sides play optimally, the maximum payoff $V(s)$ that player $1$ can get from position $s\in S$ satisfies the following recurrence:

$$
V(s) = \begin{cases}
v(s), & s \in S_0,\\
\max_{t\in s} V(t), & s\in S_1,\\
\min_{t\in s} V(t), & s\in S_2.
\end{cases}
$$

Here $t\in s$ means that $t$ is a successor position of $s$. This is the [minimax idea](../../search/alpha-beta.md#minimax-algorithm).

When applying this algorithm to real problems, the usual concrete approaches are:

-   If the game has few positions, just implement this algorithm directly by brute force.

-   If the game has a large number of positions and no special structure, consider [Alpha–Beta pruning](../../search/alpha-beta.md#alphabeta-pruning), combined with other search pruning techniques.

-   If a single position is often a successor of many positions, consider memoized search or another dynamic programming algorithm to avoid repeated search.

-   If a player's final payoff is the sum of payoffs of all moves made before the game ends, the model can be improved. Specifically, suppose that when the game reaches terminal position $s\in S_0$, the move sequences of players $i=1,2$ are $\{a^{(i)}_j\}_{j=1}^{k_i}$, the payoff of move $a$ is $w(a)$, and player $1$'s payoff function is

    $$
    v(s) = \sum_{j=1}^{k_1}w(a_j^{(1)}) - \sum_{j=1}^{k_2}w(a_j^{(2)}).
    $$

    Then let $\tilde V(s)$ be the maximum, over the rest of the game after position $s\in S$, of the payoff of the player to move minus the payoff of their opponent. For the initial state $s_0$, where player $1$ moves first, we have $V(s_0)=\tilde V(s_0)$, so computing $\tilde V(\cdot)$ is enough to solve the original problem. $\tilde V(\cdot)$ satisfies the recurrence:

    $$
    \tilde V(s) = \begin{cases}
    0, & s \in S_0, \\
    \max_{t\in s} \{w(a_{s\to t}) - \tilde V(t)\}, & s\in S_1\cup S_2.
    \end{cases}
    $$

    Here $a_{s\to t}$ is a move that takes the state from $s$ to $t$. If there are several such moves, take the one with the highest payoff $w(a)$.

-   Impartial games are all sequential zero-sum games: just give the winner payoff $+1$ and the loser payoff $-1$. Then the recurrence for the payoff function $V(\cdot)$ is exactly the [lemma](./impartial-game.md#game-graphs-and-states) for determining winning and losing states.

    A common variant of such problems asks for the minimum number of turns the winner needs and the maximum number of turns the loser can hold out. For this, note the following: run a BFS starting from the terminal states, and classify states as winning or losing according to the lemma. The BFS round in which a state is classified as winning or losing is exactly the number of turns we want. This is because a state is classified as winning as soon as one successor is a losing state, so it is always reached from the losing successor with the smallest round number; and a state is classified as losing only when all of its successors are winning states, so it is always reached from the winning successor with the largest round number.

    This method also extends to general [directed graph games](./impartial-game.md#directed-graph-games).

### Example problem

???+ example "[Codeforces 794 E. Choosing Carrot](https://codeforces.com/problemset/problem/794/E)"
    There is a sequence $\{a_i\}$ of length $n$. Two players, $1$ and $2$, take turns removing one number from either end of the sequence, until only one number is left. Player $1$ wants to maximize this last number, and player $2$ wants to minimize it. Before the game officially starts, player $1$ may also make $k$ moves first. Assume both players play optimally throughout. For each $k = 0,1,2,\cdots,n-1$, find the number left at the end of the game. Here $1 \le n \le 3\times 10^5$.

??? note "Solution"
    No matter how the two sides remove numbers, what remains of the sequence is always a contiguous interval. So a game position can be described just by the interval $[l,r]$ and the player to move $i=1,2$, and the game can be solved with dynamic programming. Let $f(l,r,i)$ be the number left at the end of the game when the position is described by $(l,r,i)$. From the analysis above, when $l < r$ this function satisfies the transitions:
    
    $$
    \begin{aligned}
    f(l,r,1) &= \max\{f(l+1,r,2),f(l,r-1,2)\},\\
    f(l,r,2) &= \min\{f(l+1,r,1),f(l,r-1,1)\}.
    \end{aligned}
    $$
    
    The terminal condition is $f(l,l,1)=f(l,l,2) = a_l$. With this, we can compute the function value of every possible position in $\Theta(n^2)$ time. For each $k$, the answer is
    
    $$
    g(k) = \max f(l,r,1) \text{ subject to } r - l + 1 = n - k.
    $$
    
    This algorithm is too slow for the constraints of the original problem, so we need to optimize the transitions. There are many ways to do this; this article gives just one.
    
    Think of the transitions as operations on the whole sequence. The two transitions build a new sequence by taking the maximum and the minimum of adjacent numbers, respectively. Call them the "max operation" and the "min operation". Each operation shortens the sequence by one. The results for all intervals of length $d$ form $(n-d+1)$ values, which is exactly the sequence obtained after applying $(d-1)$ operations to the original sequence. Also, to get $f(l,r,1)$, the last operation must be a max operation. So in these operation sequences the two operations alternate, and the last one is always a max operation.
    
    Consider how two consecutive operations change the sequence. Without loss of generality, do a min operation first and then a max operation. Then the sequence $a_1,a_2,a_3$ becomes
    
    $$
    \max\{\min\{a_1,a_2\},\min\{a_2,a_3\}\}.
    $$
    
    By going through all possible orderings of $a_1,a_2,a_3$, we see that this expression always equals $a_2$, except when $a_1 < a_2$ and $a_2 > a_3$ (that is, $a_2$ is a strict local maximum). In other words, if a sequence has no strict local maxima, then the only effect of two consecutive operations is to delete one number from each end of the sequence. This clearly simplifies the transitions a lot. The only remaining question is: how do we make sure the sequence has no strict local maxima? In fact, applying one max operation to the sequence is enough to guarantee that there are no strict local maxima. Therefore, the results of all even numbers of operations can be obtained from the sequence after two operations on the initial sequence, by repeatedly deleting the first and last numbers in pairs; the results of all odd numbers of operations can be obtained from the sequence after one operation on the initial sequence, in the same way. (The case of zero operations, that is $k=n-1$, has answer $\max_i a_i$ and must be handled separately.)
    
    Since we need at most $3$ full operations on the sequence, and collecting the answers takes only $2$ passes, the total time complexity of this algorithm is $\Theta(n)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/zero-sum-game/zero-sum-game-1.cpp"
    ```

### Exercises

-   [Luogu P2734 \[USACO3.3\] A Game](https://www.luogu.com.cn/problem/P2734)
-   [Luogu P4576 \[CQOI2013\] Board Game](https://www.luogu.com.cn/problem/P4576)
-   [Luogu P7097 \[yLOI2020\] Marionette Play](https://www.luogu.com.cn/problem/P7097)
-   [Codeforces 388 C. Fox and Card Game](https://codeforces.com/problemset/problem/388/C)
-   [Codeforces 794 E. Choosing Carrot](https://codeforces.com/problemset/problem/794/E)
-   [Codeforces 1628 D2. Game on Sum (Hard Version)](https://codeforces.com/problemset/problem/1628/D2)
-   [Luogu P3210 \[HNOI2010\] Stone-Taking Game](https://www.luogu.com.cn/problem/P3210)

## Simultaneous zero-sum games

In a simultaneous zero-sum game, the two players move at the same time.

Simultaneous zero-sum games are usually described with a payoff matrix. Suppose the action set of player $i=1,2$ is $A_i$, and when players $i=1,2$ take actions $a_i\in A_i$, their payoffs are $v(a_1,a_2)$ and $-v(a_1,a_2)$ respectively.

???+ example "Example"
    Consider rock paper scissors. Say a win scores $1$ point, a loss scores $-1$ point, and a draw scores $0$ points. Then the payoffs of the two players can be written as
    
    $$
    \begin{pmatrix}
    0,0 & 1,-1 & -1,1 \\
    -1,1 & 0,0 & 1,-1 \\
    1,-1 & -1,1 & 0,0
    \end{pmatrix}.
    $$
    
    A general two-player simultaneous game can be written in a similar form, so it is also called a [bimatrix game](https://en.wikipedia.org/wiki/Bimatrix_game). For a zero-sum game, player $1$'s payoff matrix is the negative of player $2$'s, so we only need to consider player $1$'s payoff matrix:
    
    $$
    V = (v(a_1,a_2))_{(a_1,a_2)\in A_1\times A_2} = \begin{pmatrix}
    0 & 1 & -1 \\
    -1 & 0 & 1 \\
    1 & -1 & 0
    \end{pmatrix}.
    $$

The problem to solve is: given the payoff matrix $V = (v(a_1,a_2))_{(a_1,a_2)\in A_1\times A_2}$, how do we find both players' optimal strategies and maximum payoffs?

### Mixed strategies

Unlike in sequential zero-sum games, the two players in a simultaneous game play symmetric roles. But since we have already solved sequential zero-sum games, let us look at sequential versions of the simultaneous game. For example, if we assume player $1$ moves first and then player $2$ moves, then by the discussion above, player $1$'s payoff at the end of the game is

$$
w_-=\max_{a_1\in A_1}\min_{a_2\in A_2} v(a_1,a_2)
$$

Since player $1$'s move is visible to player $2$ (but not the other way around), this should be the worst outcome player $1$ can get. Symmetrically, if we assume player $2$ moves first, then player $1$'s payoff is

$$
w_+ = \min_{a_2\in A_2}\max_{a_1\in A_1} v(a_1,a_2)
$$

Since player $2$'s move is visible to player $1$ (but not the other way around), this should be the best outcome player $1$ can get. Player $1$ should expect the payoff $w$ in the actual game to satisfy $w\in[w_-,w_+]$. Although the inequality $w_-\le w_+$ always holds (for a proof, see the [weak duality theorem](../linear-programming.md#duality-principle)), equality does not necessarily hold. So in general, analyzing sequential games alone cannot uniquely determine the outcome of the game.

???+ example "Example (continued)"
    In rock paper scissors, if the players move one after the other, the first player always loses and the second player always wins. In mathematical terms, this is the inequality:
    
    $$
    w_- = -1 \le +1 = w_+.
    $$
    
    Here $w_- = w_+$ does not hold.

The analysis above misses a key element of simultaneous games: a player cannot predict the opponent's move exactly. Formally, this means both sides can use some kind of random strategy. This idea does not work for sequential games, because no matter how the first player randomly chooses a move, the second player can always see exactly what it was and respond to it. But in a simultaneous game, the strategic ambiguity created by a random strategy prevents the opponent from effectively targeting your move.

???+ example "Example (continued)"
    In rock paper scissors, if player $1$ chooses rock, scissors or paper uniformly at random, then depending on player $2$'s move, player $1$'s payoff is
    
    $$
    \dfrac{1}{3}(0,1,-1)^T + \dfrac{1}{3}(-1,0,1)^T + \dfrac{1}{3}(1,-1,0)^T = (0,0,0)^T.
    $$
    
    So no matter what player $2$ does, player $1$'s expected payoff is always $0$. This is clearly better than deterministically picking a single move.

This leads to the concept of a mixed strategy.

???+ abstract "Mixed strategy"
    In a simultaneous game, a **mixed strategy** of player $i$, or simply a **strategy**, is a function $s_i:A_i\to[0,1]$ that satisfies $\sum_{a_i\in A_i}s_i(a_i)=1$. In other words, a strategy $s_i$ is a probability distribution over player $i$'s action set $A_i$. The set of all mixed strategies of player $i$ is written $S_i=\Delta(A_i)$, where $\Delta(A_i)$ denotes the set of all probability distributions over $A_i$. If $s_i$ is a degenerate distribution, that is, there exists $a\in A_i$ with $s_i(a)=1$, then $s_i$ is also called a **pure strategy**.

The payoff of mixed strategies is the expected value of the payoffs of single actions:

$$
v(s_1,s_2) = \sum_{a_1\in A_1}\sum_{a_2\in A_2}s_1(a_1)s_2(a_2)v(a_1,a_2).
$$

If we treat each single action as the corresponding pure strategy, the action set $A_i$ embeds into the (mixed) strategy set $S_i$, and $v(s_1,s_2)$ defined above can be seen as extending $v(a_1,a_2)$ from $A_1\times A_2$ to $S_1\times S_2$.

### von Neumann's theorem

Once mixed strategies are allowed, the maximin idea and the minimax idea give the same result, so the outcome of a simultaneous zero-sum game is uniquely determined.

???+ note "Theorem (von Neumann)"
    In a simultaneous zero-sum game with mixed strategies allowed, if both sides play optimally, player $1$'s maximum payoff is
    
    $$
    w = \max_{s_1\in S_1}\min_{s_2\in S_2} v(s_1,s_2) = \min_{s_2\in S_2}\max_{s_1\in S_1} v(s_1,s_2),
    $$
    
    and player $2$'s maximum payoff is $-w$.

??? note "Proof"
    Let $w = \max_{s_1\in S_1}\min_{s_2\in S_2} v(s_1,s_2)$. Consider the inner minimization. Since $v(s_1,s_2)=\sum_{a_2\in A_2}s_2(a_2)v(s_1,a_2)$, we have $\min_{s_2\in S_2}v(s_1,s_2)=\min_{a_2\in A_2}v(s_1,a_2)$, and the pure strategy corresponding to an optimal solution of the latter is an optimal solution of the former. So $w = \max_{s_1\in S_1}\min_{a_2\in A_2} v(s_1,a_2)$. Then, introducing an auxiliary variable $u$, the problem can be rewritten as
    
    $$
    w = \max_{u,s_1} u \text{ subject to }u \le \min_{a_2\in A_2} v(s_1,a_2).
    $$
    
    This constraint is equivalent to $u\le v(s_1,a_2)$ holding for every $a_2\in A_2$. Finally, plugging in the definition of a mixed strategy $s_1$ and the expression for the payoff function $v(s_1,a_2)$, the original problem is equivalent to the [linear programming problem](../linear-programming.md)
    
    $$
    (P) \qquad
    \begin{aligned}
    w = \max_{u,s_1}\; & u\\
    \text{subject to }& \sum_{a_1\in A_1}s_1(a_1)v(a_1,a_2) \ge u,~\forall a_2\in A_2,\\
    & \sum_{a_1\in A_1}s_1(a_1) = 1,\\
    & s_1(a_1) \ge 0,~\forall a_1\in A_1.
    \end{aligned}
    $$
    
    This problem is clearly feasible and its objective is bounded, so an optimal solution exists. By the [duality principle](../linear-programming.md#duality-principle), its optimal value equals the optimal value of the dual problem:
    
    $$
    (D) \qquad
    \begin{aligned}
    w = \min_{t,s_2}\; & t\\
    \text{subject to }&\sum_{a_2\in A_2}s_2(a_2)v(a_1,a_2) \le t,~\forall a_1\in A_1,\\
    &\sum_{a_2\in A_2}s_2(a_2) = 1,\\
    &s_2(a_2)\ge 0,~\forall a_2\in A_2.
    \end{aligned}
    $$
    
    Repeating the steps above, this problem is equivalent to $\min_{s_2\in S_2}\max_{s_1\in S_1}v(s_1,s_2)$. This proves the theorem.

The optimal strategies of the two sides form a [Nash equilibrium](https://en.wikipedia.org/wiki/Nash_equilibrium) of the game. That is, if both sides choose their optimal strategies in the equilibrium, no player can strictly gain by deviating from the equilibrium strategy on their own.

### Reducing to linear programming

The proof of von Neumann's theorem also shows how to solve simultaneous zero-sum games. Let $n$ and $m$ be the numbers of actions available to players $1$ and $2$. Given player $1$'s payoff matrix $V\in\mathbf R^{n\times m}$, solve the following linear program:

$$
\begin{aligned}
w = \max_{(u,s)\in\mathbf R\times\mathbf R^n}\; & u\\
\text{subject to }& V^Ts \ge u\mathbf 1,\\
& \mathbf 1^Ts = 1,\\
& s \ge 0.
\end{aligned}
$$

This is a linear program with $n+1$ variables and $m+1$ constraints (not counting nonnegativity constraints), and it can be solved efficiently with the [simplex method](../simplex.md). Since $u$ may be negative, you can first add the same constant $c$ to every entry of $V$ to make them all positive, so that you can require $u\ge 0$. This does not change the optimal strategies; subtracting $c$ from the resulting $w$ gives the value of the original game. The optimal solution $s$ found by the algorithm is player $1$'s optimal (mixed) strategy. To get player $2$'s optimal strategy, just read off the dual variables (that is, the shadow prices) of the optimal solution from the simplex tableau.

### Exercises

-   [Luogu P4232 Hide-and-Seek Beyond the Unconscious](https://www.luogu.com.cn/problem/P4232)

## References and notes

-   [Zero-sum game - Wikipedia](https://en.wikipedia.org/wiki/Zero-sum_game)
-   [Minimax theorem - Wikipedia](https://en.wikipedia.org/wiki/Minimax_theorem)
