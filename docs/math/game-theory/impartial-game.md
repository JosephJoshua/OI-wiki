author: cutekibry, woruo27, tinjyu, 2008verser, Backl1ght, billchenchina, Enter-tainer, FFjet, Ir1d, Molmin, orzAtalod, ouuan, SaMiiKaaaa, SamZhangQingChuan, Tiphereth-A, chu-yuehan

Prerequisites: [Introduction to game theory](./intro.md)

This article discusses [impartial games](./intro.md#impartial-games).

Among impartial games, the most basic and most important one is the normal Nim game. The Sprague–Grundy theorem says that every impartial game under the normal play rule is equivalent to a single-pile Nim game. From this we get the concepts of the Sprague–Grundy function and nimbers, which completely describe an impartial game under normal play. So this article first establishes the results for normal Nim and the Sprague–Grundy theory. After that, it discusses some impartial games that are common in competitive programming.

Finally, this article briefly discusses misère Nim. Misère games are much more complicated than normal games, and they rarely appear in competitive programming. Unless stated otherwise, every game mentioned in this article is an impartial game under normal play.

???+ info "'State', 'position' and 'game'"
    This article uses these three words interchangeably. In game theory, the state of a game usually includes all information that may be relevant to the game up to a certain moment. In general, the state of a game usually includes the past moves of both players, the values of random variables that have already been revealed, what each player knows, and so on. The position of a game is, relatively speaking, not a standard term in game theory. It usually means the situation the players face at a certain moment, such as where the pieces are in a board game. Only for impartial games (or more generally, zero-sum deterministic games with perfect information) is there no difference between state and position: these games have no randomness, and the players' future move sets and payoff functions do not depend on the history (that is, the earlier moves of both players) that led to the current position. Both can then be seen as a node in the game graph. Since a game can always be described by its initial position, the word "position" is sometimes used to refer to the game itself.

## Nim

The rules of Nim are simple:

???+ abstract "Nim"
    There are $n$ piles of stones, and pile $i$ has $a_i$ stones. Two players take turns. On each turn, a player removes any positive number of stones from any one pile; they may not take nothing. The player who takes the last stone wins.

It is easy to check that Nim is an impartial game under normal play.

???+ example "Example"
    Here is an example. Suppose there are $3$ piles with $2,5,4$ stones. One possible move is to take the $2$ stones from pile $1$, giving the position $0, 5, 4$; another is to take $4$ stones from pile $2$, giving the position $2, 1, 4$. If at some point the position becomes $0, 0, 5$ and it is player A's turn, then A can take all $5$ stones from pile $3$. That takes the last stone, so A wins.

### Game graphs and states

In Nim, the possible changes of position can be described with a game graph.

Treat every possible state as a node of a graph, and add an edge from each state to each of its successor states (states reachable with one move). This gives a directed acyclic graph, called the game graph. The graph is acyclic because in Nim the total number of stones strictly decreases with every move.

???+ example "Example"
    For example, for a Nim game whose initial position has $3$ piles with $1,1,2$ stones, we can draw the following game graph:
    
    ![Example of a game graph](./images/nim.svg)
    
    As we will explain shortly, red nodes in the graph are winning states and black nodes are losing states.

Since Nim is an impartial game, whether a player has a winning strategy depends only on the current state of the game, not on who the player is. So all states can be divided into (first-player) **winning states** and (first-player) **losing states**, written as $\mathcal N$-positions and $\mathcal P$-positions respectively[^n-vs-p]. This definition applies to all impartial games.

Using the following lemma, we can label every state as winning or losing by induction:

???+ note "Lemma"
    In an impartial game under normal play,
    
    1.  A state with no successor states is a losing state $\mathcal P$,
    2.  A state is a winning state $\mathcal N$ if and only if at least one of its successors is a losing state $\mathcal P$,
    3.  A state is a losing state $\mathcal P$ if and only if all of its successors are winning states $\mathcal N$.

??? note "Proof"
    For the first point: if the player to move has no available moves, they have already lost the game.
    
    For the second point: if the state has at least one losing successor, the player can move to that losing state. The opponent then faces a state that is losing for the player to move, so the player wins.
    
    For the third point: if no successor is a losing state, then whatever the player does, they can only move to a winning state. The opponent then faces a state that is winning for the player to move, so the player loses.

In every impartial game, the game graph is a directed acyclic graph. So with these three properties, once the game graph is drawn, we can determine whether each state is winning or losing in $O(|V|+|E|)$ time. Here $|V|$ is the number of states in the game graph and $|E|$ is the number of edges, that is, the total number of moves available over all states.

This lemma can be extended to misère games and to directed graphs that may contain cycles. See the section [Directed graph games](#directed-graph-games) for details.

### Nim sum

Let us continue with Nim.

By drawing the game graph, we can find out whether a position is a first-player win. But this takes $\Omega(\prod_{i=1}^n(a_i+1))$ time, which is far too slow to be practical. In fact, whether a Nim state is a first-player win depends only on the Nim sum of the pile sizes in the current position.

???+ abstract "Nim sum"
    The **Nim sum** of natural numbers $a_1,a_2,\cdots,a_n$ is defined as $a_1\oplus a_2\oplus\cdots\oplus a_n$.

The Nim sum is just the [XOR operation](../bit.md#bitwise-operations).

???+ note "Theorem"
    In Nim, the state $(a_1,a_2,\cdots,a_n)$ is a losing state $\mathcal P$ if and only if the Nim sum
    
    $$
    a_1\oplus a_2\oplus\cdots\oplus a_n = 0.
    $$

??? note "Proof"
    Apply induction over all possible states:
    
    1.  If $a_i=0$ for all $i=1,\cdots,n$, the state has no successors and the Nim sum is $0$, so the claim holds.
    2.  If $k = a_1\oplus a_2\oplus\cdots\oplus a_n\neq 0$, we need to prove that the state is winning. That is, we need to construct a legal move whose successor is a losing state. By the induction hypothesis, it is enough to show that the successor satisfies $a'_1\oplus a'_2\oplus\cdots\oplus a'_n=0$. Using properties of the Nim sum (XOR), this is the same as saying that there is some pile $i$ from which we can remove stones so that it has $a_i\oplus k$ stones left, that is, $a_i>a_i\oplus k$.
    
        Indeed, let the highest $1$ bit in the binary representation of $k$ be bit $d$. Then there must be some $a_i$ whose bit $d$ is $1$. For that pile, $a_i>a_i\oplus k$ must hold, because bit $d$ of $a_i\oplus k$ is $0$ and all higher bits are the same as in $a_i$.
    3.  If $a_1\oplus a_2\oplus\cdots\oplus a_n= 0$, we need to prove that the state is losing. By the induction hypothesis, it is enough to show that no successor has Nim sum $0$. This must be true: any legal move changes some $a_i$ to $a'_i\neq a_i$, which changes the Nim sum to $a'_i\oplus a_i\neq 0$.

So we can decide in $O(n)$ time whether a Nim state is a first-player win.

## Sprague–Grundy theory

Sprague–Grundy theory says that every impartial game under normal play is equivalent to a single-pile Nim game. This result is mainly used when a game is made of several independent subgames. Then we can decide the state of the whole game by computing the Nim sum of the SG values of the subgames. If the game has no such structure, deciding winning and losing states only needs the lemma from the [game graph](#game-graphs-and-states) section above.

### Notation for games

As explained above, every impartial game can be described by drawing its game graph. In a game graph, the nature of each state is determined only by its successors, so we can represent a state $S$ in the game graph by the set of its successor states.

???+ example "Example (continued)"
    Using the game graph above as an example, we get the following representations of the states:
    
    $$
    \begin{aligned}
    S_{0,0,0} &= \{\},\\
    S_{0,1,0} &= \{S_{0,0,0}\} = \{\{\}\},\\
    S_{0,0,1} &= \{S_{0,0,0}\} = \{\{\}\},\\
    S_{0,0,2} &= \{S_{0,0,0},S_{0,0,1}\} = \{\{\},\{\{\}\}\},\\
    S_{0,1,1} &= \{S_{0,1,0},S_{0,0,1}\} = \{\{\{\}\}\},\\
    S_{0,1,2} &= \{S_{0,0,2},S_{0,1,0},S_{0,1,1}\} = \{\{\{\},\{\{\}\}\},\{\{\}\},\{\{\{\}\}\}\}.
    \end{aligned}
    $$
    
    Here $S_{0,1,0}=S_{0,0,1}$.

A game can be represented by its initial state.

Although the representation of an impartial game can be quite complicated, single-pile Nim is much simpler. With just one pile of $n$ stones, it can be written as

$$
*0 = \{\},~*n = \{*m : m<n,~m\in\mathbf N\} = \{*0,*1,\cdots,*(n-1)\}.
$$

Here the notation $*n$ means (the initial state of) single-pile Nim with $n$ stones.

???+ example "Example (continued)"
    With this notation, the states in the example above can be written simply as
    
    $$
    S_{0,0,0} = *0,~
    S_{0,1,0} = S_{0,0,1} = *1,~
    S_{0,0,2} = *2,~
    S_{0,1,1} = \{*1\},~
    S_{0,1,2} = \{*1, *2, \{*1\}\}.
    $$

In what follows, the notation $T\in S$ means that state $T$ is a successor of state $S$.

### Sums of games and equivalence

Equivalence of games is built on the concept of the sum of games[^more-sums].

???+ note "Sum of games"
    The **sum** of games $G$ and $H$, also called the **combined game**, is written $G+H$ and is the game
    
    $$
    G + H = \{g + H : g \in G\} \cup \{G + h : h \in H\}.
    $$

You can think of the sum of games as a game made of two subgames played side by side without affecting each other. On each turn, a player must choose exactly one of the subgames and make one move in it. The game ends when neither subgame has a move left. The sum extends to any number of games, and it is associative and commutative; that is, the result of combining several games does not depend on the order in which they are combined or listed. Nim is exactly the sum of several single-pile Nim games.

One observation: in single-pile Nim, every state except the empty pile is a first-player win. Yet different single-pile Nim games give different results when combined with other single-pile Nim games. For example, the game $*n$ gives a losing game only when combined with another $*n$; combining it with any other single-pile Nim game $*n'\neq *n$ always gives a winning game.

This observation suggests that we can study a game by looking at its sums with other games. This leads to the concept of equivalence of games.

???+ abstract "Equivalence of games"
    If for every game $H$, the games $G_1+H$ and $G_2+H$ are both losing or both winning, then games $G_1$ and $G_2$ are called **equivalent**, written $G_1\approx G_2$.

It is easy to check that $\approx$ defined this way is indeed an [equivalence relation](../order-theory.md#binary-relations) on all impartial games.

### Sprague–Grundy function

The analysis of Nim shows that different single-pile Nim games are not equivalent to each other. However, every impartial game is equivalent to some single-pile Nim game. So we can assign a number to every impartial game. This is the Sprague–Grundy function.

To prove these results, we first need two lemmas about game equivalence. First, combining any game with a losing game gives a game equivalent to the original.

???+ note "Lemma 1"
    For any game $G$ and any losing game $A\in\mathcal P$, we have $G\approx G + A$.

??? note "Proof"
    By definition, we only need to prove that for every game $H$, the games $G+H$ and $G+A+H$ are both losing or both winning.
    
    If the game $G+H$ has a winning strategy, then so does $G+A+H$. If the opponent moves in the subgame $A$, move in subgame $A$ too, restoring it to a losing state; otherwise, follow the winning strategy for $G+H$. This guarantees the final win.
    
    If the game $G+H$ is a losing game, then $G+A+H$ is also a losing game. No matter whether a move this turn is made in the subgame $G+H$ or in the subgame $A$, the opponent can restore that subgame to a losing state on the next turn. In the end, the first player cannot win.

Second, two games are equivalent if and only if their sum is a losing game. This lemma gives a way to prove that two games are equivalent.

???+ note "Lemma 2"
    Games $G$ and $G'$ are equivalent if and only if $G+G'\in\mathcal P$ is a losing game.

??? note "Proof"
    If games $G$ and $G'$ are equivalent, then $G+G'$ and $G+G$ are both winning or both losing, and the game $G+G$ is a losing game. This is because for any move by the first player, the second player can make the same move in the other subgame, so in the end it is the first player who cannot move.
    
    Conversely, if $G+G'$ is a losing game, then by Lemma 1, $G\approx G+(G+G') = (G+G)+G' \approx G'$.

Using these lemmas, we get the following theorem:

???+ note "Theorem (Sprague–Grundy)"
    For every (finite) impartial game $G$, there exists $n\in\mathbf N$ such that $G\approx *n$.

??? note "Proof"
    We prove the theorem by mathematical induction. Let the game be $G = \{G_1,G_2,\cdots,G_k\}$. By the induction hypothesis, there exist $n_1,n_2,\cdots,n_k$ such that $G_i\approx *n_i$. Consider the game
    
    $$
    G' = \{*n_1,*n_2,\cdots,*n_k\}.
    $$
    
    We will prove that $G'\approx *m$, where $m=\operatorname{mex}\{n_1,n_2,\cdots,n_k\}$ is the smallest natural number not in the set.
    
    Step one: show that $G\approx G'$. By Lemma 2, it is enough to show that the game $G+G'$ is a losing game. Assume without loss of generality that $G\neq *0$. If the first player chooses $G_i$, the second player can choose $*n_i$; conversely, if the first player chooses $*n_i$, the second player can choose $G_i$. Either way, after these two moves the game becomes $G_i+*n_i$, which by Lemma 2 and $G_i\approx *n_i$ is a losing game. This proves $G\approx G'$.
    
    Step two: show that $G'\approx*m$. By Lemma 2, it is enough to show that $G'+*m$ is a losing game. Assume without loss of generality that $G'\neq *0$. If the first player chooses $*n_i\in *m$, then by the definition of $m$, the second player can choose $*n_i\in G'$, turning the position into $*n_i + *n_i\in\mathcal P$, so the first player loses. If the first player chooses $*n_i\in G'$ with $n_i<m$, the second player can choose $*n_i\in *m$, and again the position becomes $*n_i+*n_i\in\mathcal P$, so the first player loses. Finally, if the first player chooses $*n_i\in G'$ with $n_i>m$, the second player can choose $*m\in *n_i$, turning the position into $*m+*m\in\mathcal P$, so the first player loses. This proves $G'\approx *m$.
    
    By transitivity of the equivalence relation, $G\approx *m$. This completes the induction and proves that every game $G$ is equivalent to a single-pile Nim game.

This result shows that we can assign to every impartial game $G$ a natural number $n$ such that $G\approx *n$.

???+ abstract "Nimber"
    The **nimber** of an impartial game $G$ is the unique natural number $n$ such that $G\approx *n$.

The function that maps impartial games to nimbers is called the **Sprague–Grundy function**, or **SG function** for short, written $\operatorname{SG}(\cdot)$. Since every state of an impartial game is itself another impartial game, we can compute the nimber of each state of an impartial game, also called its SG value.

From the proof of the theorem in this section, the Sprague–Grundy function can be computed recursively as follows:

???+ note "Corollary"
    The Sprague–Grundy value $\operatorname{SG}(x)$ of a state $x$ in an impartial game $G$ satisfies
    
    $$
    \operatorname{SG}(x) = \operatorname{mex}\{\operatorname{SG}(x'): x'\in x\}.
    $$
    
    Here $\operatorname{mex}(A):=\min\{n\in\mathbf N:n\notin A\}$ is the smallest natural number not in the set $A$.

In other words, the SG value of a state equals the $\operatorname{mex}$ of the SG values of all its successor states.

Using SG values (nimbers), we can decide whether a state is a first-player win.

???+ note "Corollary"
    A state $x$ in an impartial game $G$ is a first-player win if and only if $\operatorname{SG}(x)\neq 0$.

Finally, the SG value of a sum of games is the Nim sum (XOR) of the SG values of the subgames.

???+ note "Theorem (Sprague–Grundy)"
    For impartial games $G_1,G_2,\cdots,G_n$,
    
    $$
    \operatorname{SG}(G_1+ G_2+\cdots + G_n) = \operatorname{SG}(G_1)\oplus \operatorname{SG}(G_2)\oplus\cdots\oplus\operatorname{SG}(G_n).
    $$

??? note "Proof"
    Since $*a_1+ *a_2 + \cdots + *a_n$ is exactly Nim with pile sizes $(a_1,a_2,\cdots,a_n)$, the result for Nim tells us that the game
    
    $$
    *a_1+ *a_2 + \cdots + *a_n + *(a_1\oplus a_2\oplus\cdots\oplus a_n)
    $$
    
    is a first-player loss. By Lemma 2,
    
    $$
    *a_1+ *a_2 + \cdots + *a_n \approx *(a_1\oplus a_2\oplus\cdots\oplus a_n).
    $$
    
    Therefore,
    
    $$
    \operatorname{SG}(*a_1 + *a_2 + \cdots + *a_n) = a_1\oplus a_2\oplus\cdots\oplus a_n.
    $$
    
    Let $a_i=\operatorname{SG}(G_i)$, so that $G_i\approx *a_i$. Then, using the algebraic properties of $\approx$,
    
    $$
    (G_1+ G_2+\cdots + G_n) + (*a_1 + *a_2 + \cdots + *a_n) = \sum_{i=1}^n(G_i+*a_i) \in\mathcal P.
    $$
    
    So
    
    $$
    \begin{aligned}
    \operatorname{SG}(G_1+ G_2+\cdots + G_n) &= \operatorname{SG}(*a_1 + *a_2 + \cdots + *a_n) \\
    &= a_1\oplus a_2\oplus \cdots \oplus a_n \\
    &= \operatorname{SG}(G_1)\oplus \operatorname{SG}(G_2)\oplus\cdots\oplus\operatorname{SG}(G_n).
    \end{aligned}
    $$

With this theorem, computing the SG value of a sum of games becomes much simpler.

To sum up, SG values are computed as follows:

-   For several independent games, compute the SG value of each one separately, then take their Nim sum;
-   Within a single game, the SG value of each state is the $\operatorname{mex}$ of the SG values of all its successor states;
-   In particular, the SG value of a terminal state (a state with no successors) is $\operatorname{mex}\varnothing = 0$.

### Nimbers

Every impartial game corresponds to exactly one nimber. The set of (finite) nimbers is the set of natural numbers $\mathbf N$. However, its algebraic properties are different from those of the natural numbers. Specifically, two operations can be defined on nimbers: the Nim sum $\oplus$ and the Nim product $\otimes$:

???+ abstract "Operations on nimbers"
    For nimbers $a,b$, define:
    
    -   The Nim sum $a\oplus b=\operatorname{mex}(\{a'\oplus b:a'<a,~a'\in\mathbf N\}\cup\{a\oplus b':b'<b,~b'\in\mathbf N\})$,
    -   The Nim product $a\otimes b=\operatorname{mex}(\{(a'\otimes b)\oplus(a\otimes b')\oplus(a'\otimes b'):a'<a,~b'<b,~a',b'\in\mathbf N\})$.

Under $\oplus$ and $\otimes$, the nimbers form a [field](../algebra/basic.md#fields) of characteristic $2$. Moreover, these operations and their inverses are closed on the first $2^{2^n}$ nimbers; this gives a series of [finite fields](../algebra/field-theory.md#finite-fields) $\mathbf F_{2^{2^n}}$ of size $2^{2^n}$.

## Common impartial games

Although Sprague–Grundy theory completely solves impartial games in principle, applying the Sprague–Grundy theorem directly to real impartial games is often still slow. For example, computing Sprague–Grundy values of Nim by brute force takes exponential time. So in practice we often guess the result for a specific impartial game by printing a table of small cases.

This section lists some common impartial games and their results. For each result, we only give the rule that tells winning states from losing states. As for the winning strategy, it is to make a suitable move that leaves the opponent in a losing state. Since variants of these games often appear in competitive programming, it is also important to understand the proof of each result.

???+ info "How the results in this section are proved"
    The proofs in this section are all verifications. For each game, the result describes its first-player losing states and first-player winning states. The proof only needs to check that from a losing state, every move leads to a winning state, and that from a winning state, at least one move leads to a losing state. To turn these into rigorous proofs, you would build the game graph and apply induction over its states; these verification steps are exactly the inductive step.

### Bachet's game

Compared with single-pile Nim, Bachet's game limits how many stones can be taken at a time.

???+ abstract "Bachet's game"
    There is one pile of $n$ stones. Two players take turns removing at least $1$ and at most $k$ stones. The player who takes the last stone wins.

The result is:

???+ note "Theorem"
    The first player loses if and only if $n\equiv 0\pmod {k+1}$.

??? note "Proof 1"
    When $n\not\equiv 0\pmod {k+1}$, taking $n\bmod{(k+1)}\in[1,k]$ stones puts the opponent in a losing state. So this is a first-player winning state.
    
    Conversely, when $n\equiv 0\pmod {k+1}$, either there is no move left, or after you take $k'$ stones, the opponent can immediately take $k+1-k'$ stones and put you back in a losing state.

??? note "Proof 2"
    As an application of the Sprague–Grundy theorem, let $f(n)$ be the SG value of the position with $n$ stones left.
    
    For $n\le k$, we can prove $f(n)=n$ by induction. This is the same as single-pile Nim, because the limit on the number of stones taken has no effect. For $n>k$, we need to prove $f(n)=n\bmod{(k+1)}$. Since each move takes $1$ to $k$ stones,
    
    $$
    f(n) = \operatorname{mex}\{f(n-k),f(n-k+1),\cdots,f(n-1)\}.
    $$
    
    By the induction hypothesis, these values cover every residue modulo $k+1$ except $n\bmod{(k+1)}$. So $f(n) = n\bmod{(k+1)}$.

### Moore's Nim-k

Compared with Nim, Moore's Nim-$k$ allows taking stones from up to $k$ piles at once.

???+ abstract "Moore's Nim-$k$"
    There are $n$ piles of stones, and pile $i$ has $a_i$ stones. Two players take turns. On each turn, a player chooses at least $1$ and at most $k$ piles and removes any number of stones from each of them; they may not take nothing. The player who takes the last stone wins.

The result is:

???+ note "Theorem"
    Write each pile size in binary. For each bit $d$, count how many piles have a $1$ in bit $d$, and take this count modulo $(k+1)$. If this remainder is $0$ for every bit, the first player loses; otherwise, the first player wins.

??? note "Proof"
    This is easy to prove by imitating the proof for Nim. Let $d$ be the highest bit whose remainder is not $0$, and let that remainder be $k'\le k$. The winning strategy is: among the piles with a $1$ in bit $d$, choose $k'$ piles, and remove stones so that in the position left for the opponent, the remainder for every bit is $0$. The only thing to check is that the final choice of how many stones to take is always possible.
    
    In fact, as long as bit $d$ of each of the $k'$ chosen piles becomes $0$, the remainder for bit $d$ becomes $0$; since the higher bits do not change, the lower bits of these piles can be set to anything. Handle the lower bits from high to low: suppose $c$ piles are already chosen, and the remainder for this bit among the other piles is $r$. If $c\ge k+1-r$, set this bit to $1$ in exactly $k+1-r$ of the chosen piles. Otherwise, $c+r\le k$, so choose $r$ more piles that have a $1$ in this bit, set this bit to $0$ in them, and set this bit to $0$ in all previously chosen piles. This way, the number of chosen piles never exceeds $k$.

### Staircase Nim

Staircase Nim is a bit more complicated: it allows stones to move between adjacent piles.

???+ abstract "Staircase Nim"
    There are $n$ piles of stones, and pile $i$ has $a_i$ stones. Two players take turns. On each turn, a player either removes any positive number of stones from pile $1$, or moves any positive number of stones from pile $i>1$ to pile $i-1$; they may not do nothing. The player who takes the last stone wins.

The result is:

???+ note "Theorem"
    The first player loses if and only if the Nim sum of the odd-numbered piles is $a_1\oplus a_3\oplus\cdots\oplus a_{n-1+(n\bmod 2)}=0$.

??? note "Proof"
    Whenever a player moves stones from an even-numbered pile to an odd-numbered pile, the opponent can move those same stones on to the next even-numbered pile (or remove them). So such moves do not affect the odd-numbered piles. Then moving stones from each odd-numbered pile down to the adjacent even-numbered pile (or removing them) can be seen as an independent single-pile Nim game. By the Sprague–Grundy result on sums of games, the SG value of staircase Nim is the Nim sum of the SG values of these subgames. This gives the result above.

### Fibonacci Nim

Fibonacci Nim is similar to Bachet's game: there is only one pile, and the number of stones taken each turn is limited. Unlike Bachet's game, the limit in Fibonacci Nim changes over time.

???+ abstract "Fibonacci Nim"
    There is one pile of $n$ stones. Two players take turns taking stones. The player who moves first may take any number of stones, but not all of them. After that, each move may take at most twice as many stones as the previous move (the opponent's turn). Each move must take a nonzero number of stones. The player who takes the last stone wins.

The result is:

???+ note "Theorem"
    At the start of the game, the first player loses if and only if the number of stones $n$ is a [Fibonacci number](../combinatorics/fibonacci.md).

??? note "Proof"
    Let $q$ be the quota: the maximum number of stones that can be taken in the current position. On the first turn, $q=n-1$; on later turns, $q$ is twice the number of stones the opponent took last time. Consider the [Fibonacci coding](../combinatorics/fibonacci.md#fibonacci-coding) of the number of remaining stones $n$, that is, the unique way of writing $n$ as a sum of non-adjacent positive Fibonacci numbers. We need to prove that the current state is winning if and only if $q$ is at least the smallest Fibonacci number in the decomposition of $n$.
    
    The winning strategy is: if possible, take all remaining stones; otherwise, take the smallest Fibonacci number in the decomposition. In the decomposition, the second smallest Fibonacci number is always strictly greater than twice the smallest one. So whenever the player in a winning state cannot take all the stones this turn, the opponent cannot take the second smallest Fibonacci number (which becomes the smallest Fibonacci number on the next turn) either. So the opponent is always in a losing state.
    
    Conversely, suppose the current state is losing. Let the number of stones taken now be $k$; it must be strictly less than the smallest Fibonacci number $F$ in the current decomposition. Let the smallest Fibonacci number on the next turn be $F'$; it must also be the smallest Fibonacci number in the decomposition of $F - k$. If $F'\le 2$, then since $k\ge 1$, the quota on the next turn is $2k\ge 2\ge F'$, so it is already a winning state. Otherwise, write $F'=F''+F'''$ with $F''>F'''$; that is, $F''',F'',F'$ are three consecutive Fibonacci numbers. If $k<F''$, then computing $k + (F-k)$ with Fibonacci coding involves no carries, so the result cannot be $F$. So $k\ge F''$ must hold. This shows that the quota on the next turn is $2k>F''+F'''=F'$, so it is a winning state.

### Wythoff's game

Wythoff's game allows removing stones from more than one pile at once, but requires removing the same number from each pile.

???+ abstract "Wythoff's game"
    There are two piles with $a_1$ and $a_2$ stones. Two players take turns taking stones from one or both piles. A player may not take nothing, and when taking from both piles, they must take the same number of stones from each. The player who takes the last stone wins.

The result is:

???+ note "Theorem"
    Assume without loss of generality that $a_1\le a_2$. Then the first player loses if and only if $a_1 = \lfloor(a_2-a_1)\phi\rfloor$, where $\phi=(\sqrt{5}+1)/2$ is the golden ratio.

To prove this result, we need the following lemma:

???+ abstract "Beatty sequence"
    Let $r > 1$ be an irrational number. The Beatty sequence it generates is $\mathcal B_r = \{\lfloor kr\rfloor : k \in\mathbf N_+\}$.

???+ note "Rayleigh's theorem"
    Let $r,s > 1$ be two irrational numbers with $\dfrac{1}{r}+\dfrac{1}{s}=1$. Then the sequences $\mathcal B_r$ and $\mathcal B_s$ form a partition of the set of positive integers $\mathbf N_+$. In this case they are also called complementary Beatty sequences.

??? note "Proof"
    Let $\mathcal A_r=\{kr:k\in\mathbf N_+\}$. Sort the elements of the set $\mathcal A=\mathcal A_r\cup\mathcal A_s$ to get a sequence $\{a_i\}_{i\in\mathbf N_+}$. It is enough to prove that $i=\lfloor a_i\rfloor$ for all $i\in\mathbf N_+$; this gives that $\mathcal B_r\cup\mathcal B_s$ is a partition of $\mathbf N_+$.
    
    First, we prove that the sequence has no repeated elements. Suppose otherwise: there exist $k,\ell\in\mathbf N_+$ with $kr=\ell s$. Then
    
    $$
    \dfrac{\ell}{k} = \dfrac{r}{s} = r - 1.
    $$
    
    But the left side is rational and the right side is irrational, a contradiction. So all numbers in the sequence are distinct.
    
    Next, we prove that exactly $\lfloor a_i\rfloor$ numbers in $\mathcal A$ are less than or equal to $a_i$. Assume without loss of generality that $a_i\in\mathcal A_r$, that is, $a_i=kr$. Counting the elements of $\mathcal A_r$ and $\mathcal A_s$ separately, the number of elements of $\mathcal A$ that are less than or equal to $a_i$ is exactly
    
    $$
    k + \left\lfloor\dfrac{kr}{s}\right\rfloor = k + \lfloor k(r-1)\rfloor = \lfloor kr\rfloor = \lfloor a_i\rfloor
    $$
    
    On the other hand, since the sequence $\{a_i\}$ is strictly increasing, exactly $i$ numbers are less than or equal to $a_i$. This gives $i=\lfloor a_i\rfloor$.

With this, we can prove the result above.

??? note "Proof of the result for Wythoff's game"
    For every first-player losing state $(a_1,a_2)$ with $a_1 < a_2$ described by the theorem, let $k = a_2 - a_1 \in\mathbf N_+$. Then $a_1=\lfloor k\phi\rfloor$ and $a_2=\lfloor k(\phi+1)\rfloor$. Since $\phi$ is the golden ratio, $\dfrac{1}{\phi}+\dfrac{1}{\phi+1}=1$. By Rayleigh's theorem, the sequences $\{\lfloor k\phi\rfloor\}$ and $\{\lfloor k(\phi+1)\rfloor\}$ form a partition of $\mathbf N_+$. This means that over all first-player losing states $(a_1,a_2)$ with $a_1 < a_2$, the components $a_1$ and $a_2$ together take every positive integer exactly once, and their difference $a_2-a_1$ also takes every positive integer exactly once.
    
    In Wythoff's game, a legal move either keeps one of the components unchanged or keeps the difference of the components unchanged. So from one first-player losing state, you indeed cannot reach another first-player losing state in one legal move. Conversely, take any first-player winning state $(a_1,a_2)$, assume without loss of generality that $a_1\le a_2$, and let $k=a_2-a_1$. If $a_1>\lfloor k\phi\rfloor$, the first player can take $(a_1 - \lfloor k\phi\rfloor)$ stones from each pile, turning the position into a losing state. Otherwise, since $(a_1,a_2)$ is a first-player winning state, $a_1 < \lfloor k\phi\rfloor$, so $k\ge 1$. By the result of the previous paragraph (together with the losing state $(0,0)$), for this $a_1$ there is exactly one losing state $(a_1,a_2')$ (here we do not require $a_1\le a_2'$). Now, if $a_1 \ge a_2'$, then clearly $a_2' \le a_1 < a_2$. Otherwise, if $a_1 < a_2'$, take $k'=a_2'-a_1$ so that $a_1=\lfloor k'\phi\rfloor$; since also $a_1 < \lfloor k\phi\rfloor$, we get $k' < k$, so $a_2'=a_1 + k' < a_1+k = a_2$. So whenever $a_1 < \lfloor k\phi\rfloor$, we must have $a_2' < a_2$, and the first player only needs to take $(a_2-a'_2)$ stones from the second pile to turn the position into a losing state.

### Coin-turning games

Coin-turning games are another common class of impartial games.

???+ abstract "Coin-turning game"
    Let $(S,\preceq)$ be a [well-founded partially ordered set](../order-theory.md), and let the map $f:S\rightarrow\mathcal P\mathcal PS$ satisfy: for every $s\in S$, the set $f(s)$ is nonempty; for every $T\in f(s)$, we have $s\in T$; and for every $t\in T$, we have $t\preceq s$. There is a coin at each element of $S$, either heads up or tails up. Players take turns. On each turn, a player chooses a heads-up coin $s$ and a set $T\in f(s)$, and flips all the coins in $T$. The player who turns all the coins tails up wins.

Coin-turning games are actually a large family of games. Their exact form depends on the choice of the partially ordered set $S$ and the map $f$. In the game description, the condition on $f$ says that each set $T$ of coins a player flips contains a heads-up coin $s$ such that all other elements of $T$ come before $s$. This guarantees that the game ends after a finite number of moves.

???+ example "Example"
    1.  Let $S=\{1,2,\cdots,n\}$ and $f(s)=\{\{t,s\}:t \le s\}$. This means there is a row of $n$ coins; each move flips one heads-up coin, and may also flip one coin to its left.
    2.  Let $S=\{1,2,\cdots,n\}$ and $f(s)=\{[t,s]:t \le s\}$. This means there is a row of $n$ coins; each move flips a contiguous block of coins, but the rightmost coin in the block must be heads up before the flip.
    3.  Let $S=\{1,2,\cdots,n\}^2$ and $f(s)=\{\{s\}\}$. This means there are $n$ rows and $n$ columns of coins, and each move can flip only one heads-up coin.
    4.  Let $S$ be the set of nodes of a rooted tree, and let $f(s)$ be the collection of all subsets of the nodes on the path from $s$ to the root that contain $s$ itself. This means there is a rooted tree with a coin on each node; each move flips one heads-up coin, and may also flip the coins on any of its ancestors.

Although there are many kinds of coin-turning games, they are all solved the same way. For a coin-turning game $(S,f)$, let $G_s$ be the position where only the coin at $s$ is heads up. These positions are called basic positions. Then any position $G$ can be seen as the sum of the games given by these basic positions. That is, the following result holds:

???+ note "Theorem"
    For a coin-turning game $(S,f)$ and a position $G$, let $H(G)\subseteq S$ be the set of positions of the heads-up coins. Then the SG value of $G$ is
    
    $$
    \operatorname{SG}(G) = \bigoplus_{s\in H(G)}\operatorname{SG}(G_s).
    $$

??? note "Proof"
    Consider a related game: in a position $G'$, there are some stones at each element of $S$. On each move, a player removes one stone at some $s$, chooses a set $T\in f(s)$, and then places one stone at each element of $T\setminus\{s\}$. For this kind of game we can still define basic positions $G'_s$, the position with a single stone at $s$. In this game, every position is the sum of the basic positions given by all its stones. This is because if each newly placed stone is linked to the stone that was removed, every stone appearing during the game can be traced back to one stone in the initial position. Then the subgames started by different initial stones do not affect each other, and the whole game can be seen as the sum of these subgames. Since stones at the same position have basic positions with the same SG value, the properties of XOR show that the SG value of $G'$ depends only on the parity of the number of stones at each position, not on the exact numbers. So for a position $G'$, if $H(G')$ is the set of positions with an odd number of stones, the analysis of this paragraph can be summed up in the formula:
    
    $$
    \operatorname{SG}(G') = \bigoplus_{s\in H(G')} \operatorname{SG}(G'_s).
    $$
    
    So to prove the formula in the theorem, it remains to establish the equivalence of game $G'$ and game $G$.
    
    We need to show that a position $G'$ of the new game and a position $G$ of the coin-turning game are equivalent whenever the positions with an odd number of stones in $G'$ are the same as the positions of heads-up coins in $G$. By Lemma 2 in the section [Sprague–Grundy function](#spraguegrundy-function), this is the same as proving that the position $G+G'$ is a losing state. The second player's winning strategy is simple: if the first player removes a stone at $s$ and there was more than one stone there, the second player simply copies the first player's move; otherwise, the second player chooses the same $s$ and $T\in f(s)$ as the first player, but in the other subgame: if the first player removed a stone, the second player flips coins, and if the first player flipped coins, the second player removes a stone. Whatever the first player does, the second player can always respond, and keep the positions with an odd number of stones equal to the positions of heads-up coins in the remaining position. So the game must end when the first player has no legal move, which means the first player loses. This proves the theorem.

Using this result, to decide whether a position is winning, we only need to compute the SG values of the basic positions for all heads-up coins and take their Nim sum. The SG values of these basic positions are not hard to compute either, because their successors are given by the map $f$, and the SG values of the successors can be computed by induction:

$$
\operatorname{SG}(G_s) = \operatorname{mex}\limits_{T\in f(s)}\bigoplus_{t\in T\setminus\{s\}}\operatorname{SG}(G_t).
$$

This gives a recurrence for the SG values of the basic positions.

### Bipartite graph games

Prerequisites: [Maximum bipartite matching](../../graph/graph-matching/bigraph-match.md)

To end this section, we discuss bipartite graph games. Although this game is usually called a bipartite graph game, neither its description nor the proof of its result depends on the graph being bipartite, so the result actually holds for general undirected graphs. However, maximum matching in general graphs is more complicated, so this result usually appears in problems on bipartite graphs.

???+ abstract "Bipartite graph game"
    Two players take turns. The position each player faces consists of an undirected graph $G=(V,E)$ and one of its vertices $v\in V$. On a player's turn, if the current position is $(G,v)$, the player must choose a vertex $u$ adjacent to $v$. Then vertex $v$ and all its incident edges are deleted from $G$, giving the remaining graph $G'$. The new position is $(G',u)$, which is handed to the next player. If at the start of a player's turn the current vertex $v$ has no neighbors in the graph (so there is no legal choice), that player cannot move and loses the game.

The result is:

???+ note "Theorem"
    The first player wins if and only if vertex $v$ is a critical vertex for maximum matchings of $G$, that is, $v$ is matched in every maximum matching of $G$.

??? note "Proof"
    First, suppose $v$ is a critical vertex for maximum matchings of $G$. Let $M$ be a maximum matching of $G$. The first player can move to the vertex $u$ matched with $v$ in $M$. Since $v$ appears in every maximum matching of $G$, a maximum matching of the remaining graph $G'$ has size at most $|M|-1$. Also, removing the edge $(u,v)$ from $M$ gives a matching $M'$ of $G'$ of size $|M|-1$. Together these show that $M'$ is a maximum matching of $G'$. But in the position the second player faces, the vertex $u$ is not matched in $M'$. So the second player must be in a losing state.
    
    Conversely, suppose there is a maximum matching $M$ in which $v$ is unmatched. Since $M$ does not contain $v$, it is also a maximum matching of the remaining graph $G'$. So every maximum matching $N$ of $G'$ is a maximum matching of $G$ that does not contain $v$. Every vertex $u$ adjacent to $v$ must be matched in $N$; otherwise, we could add the edge $(u,v)$ to $N$ and get a larger matching of $G$. This shows that $u$ is a critical vertex for maximum matchings of $G'$. So no matter what the first player chooses, the second player is in a winning state.

For the algorithm that finds the critical vertices for maximum matchings of a bipartite graph, see the [maximum bipartite matching page](../../graph/graph-matching/bigraph-match.md#critical-vertices-of-maximum-matchings).

There is also a variant of the bipartite graph game:

???+ abstract "Variant of the bipartite graph game"
    Let $G=(V,E)$ be an undirected graph with one stone on each vertex. Two players take turns removing stones. At the start of the game, the first player may remove any stone; on later turns, each player must remove a stone from a vertex adjacent to the vertex where the opponent removed a stone on the previous turn. The first player unable to remove a stone loses.

Clearly, this variant is the same as letting the first player choose the initial position of the bipartite graph game described above, and then playing the bipartite graph game starting with the second player. So in this variant, the first player loses if and only if every vertex is a critical vertex for maximum matchings, that is, the graph $G$ has a [perfect matching](../../graph/graph-matching/graph-match.md#definition).

## Misère Nim

This section discusses how to solve misère Nim.

???+ abstract "Misère Nim"
    There are $n$ piles of stones, and pile $i$ has $a_i$ stones. Two players take turns. On each turn, a player removes any positive number of stones from any one pile; they may not take nothing. The player who takes the last stone loses.

The result is:

???+ note "Theorem"
    In misère Nim, the state $(a_1,a_2,\cdots,a_n)$ is a losing state $\mathcal P$ if and only if
    
    1.  there exists $i$ with $a_i>1$, and the Nim sum $a_1\oplus a_2\oplus\cdots\oplus a_n=0$, or
    2.  $a_i\le 1$ for all $i$, and the number of nonempty piles left is odd.

??? note "Proof"
    Being unable to move is a first-player winning state $\mathcal N$. So by induction, if every pile has at most one stone, an odd number of nonempty piles corresponds to a first-player losing state $\mathcal P$, and an even number of nonempty piles corresponds to a first-player winning state $\mathcal N$.
    
    Next, consider the case where some piles have strictly more than $1$ stone.
    
    Case A: if exactly one pile has strictly more than $1$ stone, then the Nim sum cannot be $0$. Also, the first player can move to a position where every pile has at most $1$ stone, and can control the parity of the number of nonempty piles left. So this is a first-player winning state $\mathcal N$.
    
    Case B: now suppose more than one pile has strictly more than $1$ stone. Then whatever move is made, the next position still has at least one pile with strictly more than $1$ stone. By the induction hypothesis, in the next position a first-player loss corresponds to Nim sum zero and a first-player win corresponds to nonzero Nim sum. This is exactly the same as the induction hypothesis for normal Nim. So repeating the argument for Nim, the current position also satisfies the rule that Nim sum zero means a first-player losing state.

## Directed graph games

The impartial games discussed in this article require that the same position never appears twice and that there are no draws. So the corresponding game graph is always a directed acyclic graph. This section relaxes this restriction and discusses how to decide, on a general directed graph, whether each state is a first-player win, a first-player loss or a draw.

The rules of a directed graph game are mostly the same as for other impartial games: starting from the initial state, players take turns moving one step along an edge of the directed graph, until no move is possible. Under normal play the player who cannot move loses; under misère play that player wins. In such a game, each state has three possible outcomes: first-player win, first-player loss, or draw. In a draw the game never ends. Although things are a bit more complicated, the [lemma](#game-graphs-and-states) about losing and winning states still holds, and the remaining states are draws:

-   If a state has successors, it is a first-player win if and only if one of its successors is a losing state;
-   If a state has successors, it is a first-player loss if and only if all of its successors are winning states;
-   If a state cannot be classified as winning or losing, it is a draw.

To classify all states into these three kinds, just use an idea similar to [topological sort](../../graph/topo.md):

1.  To initialize, record the out-degree of every state. Push all states with out-degree zero into a queue, and mark them as losing or winning depending on whether the game uses normal or misère play.
2.  Pop the state at the front of the queue. If it is a losing state, mark all its predecessors that are not yet decided as winning states. Otherwise, the current state is a winning state: decrease the out-degree of each of its predecessors by one, and mark predecessors whose out-degree becomes zero as losing states. Push every predecessor that has just been decided as winning or losing into the queue.
3.  The algorithm stops when the queue is empty. Every state not yet decided as winning or losing is a draw.

This algorithm classifies all states in $O(|V|+|E|)$ time.

## Example problems

This section discusses some typical example problems.

???+ example "[Luogu P2148 \[SDOI2009\] E&D](https://www.luogu.com.cn/problem/P2148)"
    There are $2n$ piles of stones. For $k=1,2,\cdots,n$, piles $2k-1$ and $2k$ form a group. Two players take turns. On each turn, a player chooses a group, removes one of its piles, and splits the other pile into two nonempty piles, which are placed in the two positions of that group. If every pile has only one stone, the current player has no legal move and loses. Given the size of each pile $\{a_i\}_{i=1}^{2n}$, decide whether this is a first-player winning state.

??? note "Solution"
    Clearly, the games in different groups are independent, so if we compute the SG value of each group, we can get the SG value of the whole game and decide whether it is a winning state. The key is how to compute the SG value of each group, which is not easy. A common approach for this kind of game theory problem is to print a table. Let $f(i,j)$ be the SG value of a group whose piles have $(i,j)$ stones. Writing a brute-force program to print the table gives:
    
    ```text
    0 1 0 2 0 1 0 3 0 1 0 2 0 1 0 4 
    1 1 2 2 1 1 3 3 1 1 2 2 1 1 4 4
    0 2 0 2 0 3 0 3 0 2 0 2 0 4 0 4
    2 2 2 2 3 3 3 3 2 2 2 2 4 4 4 4
    0 1 0 3 0 1 0 3 0 1 0 4 0 1 0 4
    1 1 3 3 1 1 3 3 1 1 4 4 1 1 4 4
    0 3 0 3 0 3 0 3 0 4 0 4 0 4 0 4
    3 3 3 3 3 3 3 3 4 4 4 4 4 4 4 4
    0 1 0 2 0 1 0 4 0 1 0 2 0 1 0 4
    1 1 2 2 1 1 4 4 1 1 2 2 1 1 4 4
    0 2 0 2 0 4 0 4 0 2 0 2 0 4 0 4
    2 2 2 2 4 4 4 4 2 2 2 2 4 4 4 4
    0 1 0 4 0 1 0 4 0 1 0 4 0 1 0 4
    1 1 4 4 1 1 4 4 1 1 4 4 1 1 4 4
    0 4 0 4 0 4 0 4 0 4 0 4 0 4 0 4
    4 4 4 4 4 4 4 4 4 4 4 4 4 4 4 4
    ```
    
    This table has a very clear pattern. A simple observation: the table splits into $2\times 2$ blocks, where the top-left entry is always $0$ and the other three entries are always equal. So let us compress the table, replacing each $2\times 2$ block with the common value of its entries other than the top-left one:
    
    ```text
    1 2 1 3 1 2 1 4 
    2 2 3 3 2 2 4 4 
    1 3 1 3 1 4 1 4 
    3 3 3 3 4 4 4 4 
    1 2 1 4 1 2 1 4 
    2 2 4 4 2 2 4 4 
    1 4 1 4 1 4 1 4 
    4 4 4 4 4 4 4 4 
    ```
    
    Notice that the compressed table is the value at the same position in the full table plus one. That actually solves the problem. With indices starting from $0$, the value $g(i,j)$ at $(i,j)$ in the table is given by the recurrence:
    
    $$
    g(i,j) =
    \begin{cases}
    0, & \text{if }2\mid i\text{ and }2\mid j,\\
    g(\lfloor i/2\rfloor,\lfloor j/2\rfloor)+1,& \text{otherwise}.
    \end{cases}
    $$
    
    The SG function we want is $f(i,j)=g(i-1,j-1)$. With this recurrence, the algorithm computes $f(i,j)$ in $O(\log\max\{i,j\})$ time.
    
    Of course, a simple induction shows that $g(i,j)$ is just the minimum number of times $i$ and $j$ must both be halved (rounding down) until both are even. In other words, it is the number of trailing $1$ bits in the bitwise OR of $i$ and $j$. So the value can also be computed directly with `__builtin_ctz(~(i | j))`.
    
    In problems like this, once you get the expression for the SG function by printing tables and observing patterns, it is usually easy to prove by induction. So the key to solving the problem is to obtain the result somehow, not to derive it. For example, once the result is known, the recurrence in this problem can be proved by induction as follows. Let $S_k$ be the set of SG values of the positions obtained by splitting $k$ stones into two nonempty piles. Then $f(i,j) = \operatorname{mex}(S_i \cup S_j)$. So $S_k$ satisfies the recurrence:
    
    $$
    S_k = \{\operatorname{mex}(S_i \cup S_j) : i + j = k,~i,j\in\mathbf N_+\}.
    $$
    
    We need to prove that $d\in S_k$ if and only if bit $d$ (the lowest bit is bit $0$) of the binary representation of $(k-1)$ is $1$.
    
    Use induction. The base case $S_1=\varnothing$ clearly holds. Suppose the claim holds for all positive integers less than $k$. Then $d\in S_k$ if and only if there exist $i,j\in\mathbf N_+$ with $i+j=k$ such that bit $d$ of both $(i-1)$ and $(j-1)$ is $0$, and for each $d' < d$, at least one of them has a $1$ in bit $d'$. Clearly, such a split exists if and only if, looking only at bits $0\sim d$ (that is, modulo $2^{d+1}$), the possible values of $(k-1)=(i-1)+(j-1)+1$ cover the range $[2^d,2^{d+1})$. This condition is equivalent to bit $d$ of $(k-1)$ being $1$. So the inductive step holds, and the claim is proved.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/impartial-game/impartial-game-1.cpp"
    ```

???+ example "[Luogu P5675 \[GZOI2017\] Stone-Taking Game](https://www.luogu.com.cn/problem/P5675)"
    There are $n$ piles of stones, and pile $i$ has $a_i$ stones. Two people play Nim. You may choose any subset of the piles as the initial position, and choose one of these piles from which the first player must take stones on the first turn, but you cannot choose how many stones are taken. How many ways of choosing are there such that the first player cannot win? Constraints: $n,a_i\le 200$.

??? note "Solution"
    For problems like this, you need to combine the results for common games with other knowledge. Suppose the first player must take from pile $i$, and the Nim sum of all chosen piles is $v$. Then the first player cannot win if and only if $a_i \le a_i\oplus v$; that is, the size $a_i$ of pile $i$ is at most the Nim sum $a_i\oplus v$ of the other chosen piles. Since the constraints are small, just enumerate the pile used on the first turn. When enumerating pile $i$, each of the other piles is either chosen or not, and the number of ways to get each Nim sum can be computed with DP. Then add up the counts for Nim sums greater than or equal to $a_i$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/impartial-game/impartial-game-2.cpp"
    ```

???+ example "[Luogu P2599 \[ZJOI2009\] Stone-Taking Game](https://www.luogu.com.cn/problem/P2599)"
    There are $n$ piles of stones, and pile $i$ has $a_i$ stones. Two people take turns taking stones. On each turn, a player can only choose the leftmost or the rightmost pile and take any positive number of stones from it; they may not take nothing. The player who takes the last stone wins. Decide whether the first player wins.

??? note "Solution"
    Since this problem has no independent subgames, in principle it only uses the [lemma for deciding losing and winning states](#game-graphs-and-states). Start with the simplest case. When $n\le 2$, it is just Nim. When $n \ge 3$, things get complicated. However, since only the piles at the two ends can be changed, let their sizes be $x$ and $y$. Further, let $f(x,y)$ be the indicator function of first-player winning states: $f(x,y)=1$ if the first player wins, and $f(x,y)=0$ otherwise. It is easy to see that $f(x,y)$ satisfies the recurrence: $f(x,y)=0$ if and only if $f(x,t)=f(s,y)=1$ for all $s < x$ and $t < y$. The base case is $x=0$ or $y=0$; then the game has fewer than $n$ piles, and we must further consider the sizes of the middle piles. So for now assume $f(x,0)$ and $f(0,y)$ are known, and consider how to derive all values of $f(x,y)$ from them. This is not hard. Consider an infinite matrix indexed by $\mathbf N\times\mathbf N$. Computing $f(x,y)$ means filling it with $0$s and $1$s, subject to: each row and each column has at most one $0$, and a position must be $0$ if no earlier position in the same row or the same column has a $0$. The position of the $0$ in each row actually defines a function from the row index $x$ to the column index $y$. After trying a few examples (that is, printing a table), you will find the following. Let $x_0$ be the unique $x$ with $f(x,0)=0$, and $y_0$ the unique $y$ with $f(0,y)=0$. Then for any positive integer $x$, the $y$ that makes $f(x,y)=0$ is
    
    $$
    y = \begin{cases}
    0, & x = x_0,\\
    x - 1, & x_0 < x \le y_0,\\
    x + 1, & y_0 \le x < x_0,\\
    x, & \text{otherwise}.
    \end{cases}
    $$
    
    In other words, once we know $x_0$ and $y_0$, we can compute any $f(x,y)$ in $O(1)$ time and decide whether the current state is a first-player win. And $x_0$ and $y_0$ can be computed recursively. For example, $x_0$ is the unique solution of $f(x,0)=0$, but the value of $f(x,0)$ can also be computed by removing the rightmost pile and considering only the remaining $n-1$ piles. That is, considering only the first $n-1$ piles, we can similarly compute a function $f_{1,n-1}(x,y)$, and clearly $f(x,0)=f_{1,n-1}(x,a_{n-1})$. Similarly, after removing the leftmost pile and computing $f_{2,n}(x,y)$, we get $f(0,y)=f_{2,n}(a_2,y)$. Of course, computing the inner functions $f_{1,n-1}(x,y)$ and $f_{2,n}(x,y)$ depends on functions further inside. This is a typical [interval DP](../../dp/interval.md). Each level only needs to maintain the $x_0$ and $y_0$ of its function.

??? note "Reference code"
    ```cpp
    --8<-- "docs/math/code/impartial-game/impartial-game-3.cpp"
    ```

## Exercises

First, some template problems. They are simple applications of the results on this page:

-   [Luogu P2197 \[Template\] Nim Game](https://www.luogu.com.cn/problem/P2197)
-   [Luogu P2252 \[SHOI2002\] Stone-Taking Game](https://www.luogu.com.cn/problem/P2252)
-   [Luogu P2594 \[ZJOI2009\] Coloring Game](https://www.luogu.com.cn/problem/P2594)
-   [Luogu P3185 \[HNOI2007\] Splitting Game](https://www.luogu.com.cn/problem/P3185)
-   [Luogu P3480 \[POI 2009\] KAM-Pebbles](https://www.luogu.com.cn/problem/P3480)
-   [Luogu P4101 \[HEOI2014\] Everyone Praises Jiangnan](https://www.luogu.com.cn/problem/P4101)
-   [Luogu P4279 \[SHOI2008\] Little John's Game](https://www.luogu.com.cn/problem/P4279)
-   [Luogu P6487 \[COCI 2010/2011 #4\] HRPA](https://www.luogu.com.cn/problem/P6487)
-   [Luogu P6560 \[SBCOI2020\] The Passage of Time](https://www.luogu.com.cn/problem/P6560)
-   [Luogu P7589 Black and White Chess (2021 CoE-II B)](https://www.luogu.com.cn/problem/P7589)
-   [AtCoder Regular Contest 168 B - Arbitrary Nim](https://atcoder.jp/contests/arc168/tasks/arc168_b)

Next, some problems that need more insight or combine more ideas:

-   [Luogu P2490 \[SDOI2011\] Black and White Chess](https://www.luogu.com.cn/problem/P2490)
-   [Luogu P3179 \[HAOI2015\] Array Game](https://www.luogu.com.cn/problem/P3179)
-   [Luogu P5363 \[SDOI2019\] Moving Coins](https://www.luogu.com.cn/problem/P5363)
-   [Luogu P5970 \[POI 2016\] Nim z utrudnieniem](https://www.luogu.com.cn/problem/P5970)
-   [Luogu P6791 \[SNOI2020\] Taking Stones](https://www.luogu.com.cn/problem/P6791)
-   [Luogu P7864 \[EVOI-RD1\] Picking Leaves](https://www.luogu.com.cn/problem/P7864)
-   [Luogu P8347 \[Wdoi-6\] The Moon on the Other Side](https://www.luogu.com.cn/problem/P8347)
-   [AtCoder Grand Contest 002 E - Candy Piles](https://atcoder.jp/contests/agc002/tasks/agc002_e)
-   [AtCoder Grand Contest 010 F - Tree Game](https://atcoder.jp/contests/agc010/tasks/agc010_f)
-   [AtCoder Grand Contest 017 D - Game on Tree](https://atcoder.jp/contests/agc017/tasks/agc017_d)
-   [AtCoder Beginner Contest 278 G - Generalized Subtraction Game](https://atcoder.jp/contests/abc278/tasks/abc278_g)
-   [SPOJ COT3 - Combat on a tree](https://www.spoj.com/problems/COT3/)
-   [Codeforces 494 E. Sharti](https://codeforces.com/problemset/problem/494/E)
-   [Codeforces 1149 E. Election Promises](https://www.luogu.com.cn/problem/CF1149E)
-   [Codeforces 1451 F. Nullify The Matrix](https://codeforces.com/problemset/problem/1451/F)
-   [Codeforces 1704 F. Colouring Game](https://codeforces.com/problemset/problem/1704/F)

Finally, some bipartite graph game problems. They need bipartite matching algorithms, so they are listed separately:

-   [Luogu P4136 Who Can Win?](https://www.luogu.com.cn/problem/P4136)
-   [Luogu P4617 \[COCI 2017/2018 #5\] Planinarenje](https://www.luogu.com.cn/problem/P4617)
-   [Luogu P4055 \[JSOI2009\] Game](https://www.luogu.com.cn/problem/P4055)
-   [Luogu P1971 \[NOI2011\] Bunny and Egg Game](https://www.luogu.com.cn/problem/P1971)
-   [Codeforces 1147 F. Zigzag Game](https://codeforces.com/problemset/problem/1147/F)

## References and notes

-   [(Repost) Nim games (complete collection) by exponent - cnblogs](http://www.cnblogs.com/exponent/articles/2141477.html)
-   [\[Combinatorial games and game theory\] (study notes) by Candy? - cnblogs](https://www.cnblogs.com/candy99/p/6548836.html)
-   [Nim - Wikipedia](https://en.wikipedia.org/wiki/Nim)
-   [Sprague–Grundy theorem - Wikipedia](https://en.wikipedia.org/wiki/Sprague%E2%80%93Grundy_theorem)
-   [Nimber - Wikipedia](https://en.wikipedia.org/wiki/Nimber)
-   [Beatty Sequence - Wikipedia](https://en.wikipedia.org/wiki/Beatty_sequence)
-   [Games on arbitrary graphs - CP Algorithms](https://cp-algorithms.com/game_theory/games_on_graphs.html)
-   [Algorithm study notes (74): bipartite graph games by Pecco - Zhihu](https://zhuanlan.zhihu.com/p/359334008)
-   Conway, John H. On numbers and games. AK Peters/CRC Press, 2000.
-   Berlekamp, Elwyn R., John H. Conway, and Richard K. Guy. Winning ways for your mathematical plays, volume 1-4. AK Peters/CRC Press, 2001-2004.

[^n-vs-p]: The names "$\mathcal N$-position" and "$\mathcal P$-position" stand for "Next player wins" and "Previous player wins" respectively.

[^more-sums]: All "sums" discussed in this article are **disjunctive sums** under the **long rule**. This is the most common way to combine games. There are other possible ways to combine games as well. For a detailed discussion, see Chapter 14 of Conway, John H. On numbers and games. AK Peters/CRC Press, 2000.
