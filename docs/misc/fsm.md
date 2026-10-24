author: CCXXXI, countercurrent-time, Enter-tainer, FFjet, H-J-Granger, Ir1d, mgt, NachtgeistW, orzAtalod, ouuan, SukkaW

Prerequisites: [languages and decision problems](./cc-basic.md#problems)

A **finite state machine** (FSM, also called a finite automaton, or just an automaton below) is the simplest kind of computational model: both its descriptive power and its resources are extremely limited. Automata are widely used in OI and computer science, and the idea shows up in many string algorithms. So we recommend learning about automata before studying string algorithms such as [KMP](../string/kmp.md), the [Aho–Corasick automaton](../string/ac-automaton.md) and the [SAM](../string/sam.md).

## Getting started with automata

First, let's understand what an automaton is for: an automaton is a mathematical model that decides whether a sequence of signals follows some particular pattern or rule.

Some of the terms in that sentence deserve an explanation. A "sequence of signals" is a list of signals in order, for example the characters of a string from front to back, the numbers of an array from $1$ to $n$, or the digits of a number from the most significant to the least significant. "Deciding whether it follows some rule" means: we care whether the sequence belongs to some particular set. That set is defined by a rule we fix in advance, such as "all binary strings of even length" or "all palindromes".

Sometimes we need to answer questions like this: does a given sequence have some property? For example, is a binary number odd, is a string a palindrome, or is it a subsequence of another string? Automata are the mathematical tool for solving such questions.

An automaton works much like a flowchart. Suppose you want to order a cup of milk tea on a food delivery app. All the choices you make form a sequence. Here is an example flowchart:

![order fsm](./images/fsm1.svg)

For example, if your sequence of choices is "open the order page -> choose milk tea -> have enough money for milk tea", the states you pass through in order might be "delivery app -> order page -> pay for milk tea -> got milk tea". In this way, our "milk tea automaton" uses our choices to decide whether we got milk tea. We can also see that there may be more than one way to reach a state. If you did not get milk tea, you may have quit right on the order page, or you may not have had enough money to buy it.

With this automaton, we split signal sequences into two kinds: those that end with buying milk tea, and those that don't. Based on which state we end up in, we have solved a decision problem.

We just compared the way an automaton works to a flowchart, but a flowchart is only an intuitive visual tool and is not a mathematical definition of an automaton. To describe the structure of an automaton more precisely, we need to abstract the elements of the flowchart. After abstraction, the structure of the flowchart turns out to be just a directed graph: each node stands for a state, and each directed edge stands for a transition between states.

So the core structure of an automaton can be formally viewed as a directed graph, which we call the **state diagram**.

An automaton works much like a flowchart, with these differences: every node of an automaton is a decision node; a node of an automaton is just a state, not a task; and an edge of an automaton can accept many kinds of characters (not only `T` or `F`).

For example, here is an automaton that decides whether a binary number is even:

![example fsm](./images/fsm2.svg)

Start from the start node, read the binary digits of the number from the most significant to the least significant, and see where you stop. If you stop at the red-circled node, the number is even; otherwise it is not.

We should stress one point here. Below we will often use words like "character" and "alphabet", but this does not mean automata only apply to strings. A character does not have to be a letter like $\tt abc\cdots z$; it can also be a choice.

If you need to decide how a finite signal sequence relates to another signal sequence (for example, whether the finite sequence is a substring of the other one), a common method is to build an automaton for the finite sequence. You will see this when you learn KMP.

Note that an automaton is only a **mathematical model**. It is **not an algorithm**, and it is **not a data structure** either. The same automaton can be implemented in many ways, possibly with different time and space complexities.

From here, you can either keep studying automata on this page, or go learn concrete examples such as [KMP](../string/kmp.md), the [Aho–Corasick automaton](../string/ac-automaton.md) or the [SAM](../string/sam.md).

FSMs come in two kinds: deterministic finite automata and nondeterministic finite automata.

## Deterministic finite automata

A **deterministic finite automaton** (DFA) is called deterministic because its decision process is deterministic. Take the "milk tea automaton" as an example: as soon as you open the order page, you get to the order page. Nothing unexpected happens, such as the network failing to load or your phone running out of battery.

???+ abstract "DFA"
    A DFA is a 5-tuple $(Q,\Sigma,\delta,q_0,F)$ consisting of:
    
    1.  A **finite set of states**  $Q$. If we view a DFA as a directed graph, the states of the DFA are the vertices of the graph.
    2.  An **alphabet** $\Sigma$. The automaton can only take these characters as input.
    3.  A **transition function** $\delta:Q\times \Sigma \to Q$, a function that takes two arguments and returns one value. The first argument and the return value are states, and the second argument is a character from the alphabet. If we view a DFA as a directed graph, the transition function corresponds to the edges between vertices, and each edge carries a character.
    4.  A **start state**  $q_0\in Q$, a special state. Different texts usually write the start state as $s$, $\textit{start}$ or $q_0$; this article uses $q_0$.
    5.  A **set of accepting states**  $F\subseteq Q$, a set of special states.

A DFA can be represented simply by the following struct:

???+ example "Reference implementation"
    ```cpp
    --8<-- "docs/misc/code/fsm/dfa.hpp:dfa"
    ```

Finding the sequence of states that an input string $w$ goes through in a DFA, and deciding whether it is accepted, is called **computation**.

???+ abstract "How a DFA computes"
    Let $M=(Q,\Sigma,\delta,q_0,F)$ be a DFA and $w=w_1w_2\cdots w_n\in\Sigma^*$ a string. If there is a sequence of states $r_0,r_1,\cdots,r_n$ in $Q$ such that
    
    -   $r_0=q_0$,
    -   $\delta(r_i,w_{i+1})=r_{i+1}$ holds for every $i=0,1,\cdots,n-1$,
    -   $r_n\in F$,
    
    then we say $M$  **accepts** $w$. Otherwise, we say $M$  **does not accept**  $w$.

When a DFA reads a string, it starts from the start state and moves one character at a time according to the transition function. If it is in an accepting state after reading all characters of the string, we say the DFA **accepts** the string; otherwise we say the DFA **does not accept** it.

???+ abstract "Formal language"
    A **formal language** over an alphabet $\Sigma$, or simply a **language**, is a set $L$ of strings over $\Sigma$.

???+ abstract "Language recognized by an automaton"
    For an automaton $M$, the language $L(M)$ it recognizes is defined as the set of all strings it accepts, $\{w\mid M\text{ accepts }w\}$.

Not every language can be recognized by a DFA.

???+ abstract "Regular language"
    If a language can be recognized by some DFA, it is called a **regular language**.

As mentioned above, an automaton can be drawn as a state diagram. Below is a DFA that accepts exactly the strings $\tt a$, $\tt ab$ and $\tt aac$:

![](./images/fsm3.svg)

(The dead state is omitted from the figure. Every transition not drawn goes to that dead state.)

## Nondeterministic finite automata

A **nondeterministic finite automaton**[^nfa-and-nfaepsilon] (NFA) is a natural generalization of a DFA. In an NFA, for any state and any character, there may be zero, one or several next states. Also, the NFAs discussed in this section allow the empty character: a state can move to one of its next states without consuming any character.

As an example, take the "milk tea automaton" again. After placing an order, even if you have the money, you may still not get milk tea because of a bad network connection; this is a case of several next states. Or, because you were too slow, the milk tea sold out, so you didn't get it even though your input string (that is, your sequence of actions) was the same; this is the empty character at work, a move that may or may not be taken. A small change to the earlier automaton gives this behavior:

![order nfa](./images/fsm4.svg)

Clearly, every DFA is an NFA, so NFAs can recognize at least all regular languages. But since an NFA extends a DFA, can it recognize more languages? In fact it cannot. We will look at the equivalence of DFAs and NFAs later.

???+ abstract "NFA"
    Let $\mathcal{P}(Q)$ denote the power set of $Q$. Let $\varepsilon\notin\Sigma$ denote the empty string, and write $\Sigma_\varepsilon = \Sigma\cup\{\varepsilon\}$. An NFA is a 5-tuple $(Q,\Sigma,\delta,q_0,F)$ consisting of:
    
    1.  A **finite set of states**  $Q$,
    2.  An **alphabet** $\Sigma$,
    3.  A **transition function** $\delta:Q\times \Sigma_{\varepsilon} \to \mathcal{P}(Q)$, a function that takes two arguments and returns a **set of states**. The first argument is a state, the second is a character from the alphabet or the empty string $\varepsilon$, and the return value is the set of all possible next states (possibly empty),
    4.  A **start state**  $q_0\in Q$,
    5.  A **set of accepting states**  $F\subseteq Q$.

Computation in an NFA is like running many DFAs at the same time. Every step tries all possibilities, and in the end, as long as one branch reaches an accepting state, the NFA accepts the whole string.

???+ abstract "How an NFA computes"
    Let $N=(Q,\Sigma,\delta,q_0,F)$ be an NFA. If the string $w$ can be written as some $y_1y_2\cdots y_m$ (where $y_i\in\Sigma_\varepsilon$), and there is a sequence of states $r_0,r_1,\cdots,r_m$ in $Q$ such that
    
    -   $r_0=q_0$,
    -   $r_{i+1}\in\delta(r_i,y_{i+1})$ holds for every $i=0,1,\cdots,m-1$,
    -   $r_m\in F$,
    
    then we say $N$  **accepts**  $w$. Otherwise, we say $N$  **does not accept**  $w$.

Because empty characters are allowed, any number of them can be inserted when writing $w$ as $y_1y_2\cdots y_m\in\Sigma^*_\varepsilon$. For example, the string $\texttt{abc}$ can be written as $\texttt{a}\varepsilon\texttt{bc}\varepsilon\varepsilon\in\Sigma^*_\varepsilon$. In a DFA each input leads to exactly one result, while in an NFA each input may lead to several results, forming a set of results.

## Equivalence of DFAs and NFAs

Two automata are called equivalent if and only if they recognize the same language. DFAs and NFAs are equivalent: every NFA is equivalent to some DFA, so the class of languages recognized by NFAs is also exactly the regular languages. Every DFA can be viewed directly as an NFA; in the other direction, an NFA can be turned into a DFA with the **powerset construction**.

???+ abstract "Powerset construction"
    Let the NFA be $N = (Q, \Sigma, \delta, q_0, F)$. Define $E(q)$ as the set of states reachable from state $q$ using only $\varepsilon$ transitions (including $q$ itself), i.e. the $\varepsilon$-closure of $q$.
    
    Construct the DFA $M = (Q', \Sigma, \delta', E(q_0), F')$, where:
    
    -   the **finite set of states** is  $Q' = \mathcal{P}(Q)$,
    -   the **transition function** $\delta' : Q' \times \Sigma \to Q'$ satisfies $\delta'(S, c) = \bigcup_{q \in S,~q' \in \delta(q, c)} E(q')$,
    -   the **set of accepting states** is  $F' = \{ S \subseteq Q \mid S \cap F \neq \varnothing \}$.
    
    Clearly, at every step of the computation, the state of $M$ corresponds to the set of states $N$ might be in.

Although NFAs and DFAs recognize the same languages, NFAs are still useful. For some regular languages, an NFA needs far fewer states than a DFA. For example, we can build an NFA with $n$ states whose minimal equivalent DFA has $\Theta(2^n)$ states. In such a case, computing with the NFA directly has a better time complexity.

## Time complexity of running DFAs and NFAs

Let the input string have length $n$, let the automaton have $s$ states, and let the alphabet size be a constant. Then clearly a DFA runs in $O(n)$ time: just simulate the process above.

Running an NFA naively takes $O(ns^2)$ time, because we have to consider every possible next state and also pay for merging the states. Of course, using a bitset or the Method of Four Russians, the complexity can be improved to $O\left(\dfrac{ns^2}{w}\right)$ or $O\left(\dfrac{ns^2}{w\cdot \log n}\right)$.

## Regular expressions and regular languages

This section discusses the definitions and properties of regular expressions and regular languages, and studies how regular expressions relate to FSMs.

### Regular expressions

A **regular expression** is another common way to describe regular languages. You can see the name in many modern languages (such as Python), but what those languages implement is actually a superset of regular expressions.

???+ abstract "Regular expression"
    Given an alphabet $\Sigma$, regular expressions are strings of symbols defined inductively by the following rules:
    
    1.  Any character $c \in \Sigma$ is a regular expression;
    2.  The empty-string symbol $\varepsilon$ is a regular expression;
    3.  The empty-language symbol $\varnothing$ is a regular expression;
    4.  If $R_1$ and $R_2$ are regular expressions, then $(R_1 + R_2)$, $(R_1 R_2)$ (also written $(R_1 \cdot R_2)$) and $(R_1^\ast)$ are all regular expressions.

The purpose of a regular expression is to describe a language with these symbols. Every regular expression has a corresponding formal language.

???+ abstract "Language described by a regular expression"
    Let $L(R)$ be the formal language of each regular expression $R$. Then:
    
    1.  If $R = c$ with $c \in \Sigma$, then $L(R) = \{c\}$;
    2.  If $R = \varepsilon$, then $L(R) = \{\varepsilon\}$;
    3.  If $R = \varnothing$, then $L(R) = \varnothing$;
    4.  If $R = (R_1 + R_2)$, then $L(R) = L(R_1) \cup L(R_2)$;
    5.  If $R = (R_1 R_2) = (R_1\cdot R_2)$, then $L(R) = \{ uv \mid u \in L(R_1),~ v \in L(R_2) \}$, where $uv$ means joining the two strings one after the other;
    6.  If $R = (R_1^\ast)$, then $L(R) = \{u_1 u_2 \cdots u_n \mid u_i \in L(R_1),\ n \in \mathbf{N}_+\}\cup\{\varepsilon\}$. This is called the **Kleene star** or **Kleene closure**, or just the closure.

Of course, once operator precedence is fixed, these parentheses can be omitted when there is no ambiguity.

???+ example "Example"
    Let $L(R_1) = \{0,\ 01\}$ and $L(R_2) = \{\varepsilon,\ 1,\ 11,\ 111,\ \dots\}$. Then:
    
    -   $L(R_1R_2) = \{0,\ 01,\ 011,\ 0111,\ \dots\}$,
    -   $L(R_2^\ast) = L(R_2)$,
    -   $L(R_1 + R_2) = \{0,\ 01,\ \varepsilon,\ 1,\ 11,\ 111,\ \dots\}$.

Every regular expression can be turned into an NFA with [Thompson's construction](https://zh.wikipedia.org/wiki/%E6%B1%A4%E6%99%AE%E6%A3%AE%E6%9E%84%E9%80%A0%E6%B3%95), and every DFA can be turned into a regular expression with the state elimination method[^state-elimination-method]. So regular expressions and FSMs are equivalent.

### Regular languages

In this subsection, we do not look at concrete regular expressions. Instead we consider regular expressions with variables as parameters (a variable can be any regular language). The algebraic laws of regular expressions help simplify regular expressions.

???+ note "Algebraic properties of regular languages"
    1.  Commutativity of union: $L + M = M + L$
    2.  Associativity of union: $(L + M) + N = L + (M + N)$
    3.  Associativity of concatenation: $(LM)N = L(MN)$
    4.  $\varnothing$ is the identity of union: $\varnothing + L = L + \varnothing = L$
    5.  $\varepsilon$ is the identity of concatenation: $\varepsilon L = L \varepsilon = L$
    6.  $\varnothing$ is the zero of concatenation: $\varnothing L = L \varnothing = \varnothing$
    7.  Distributivity: $L(M + N) = LM + LN$, $(M + N)L = ML + NL$
    8.  Idempotence of union: $L + L = L$
    9.  Laws about closure: $(L^\ast)^\ast = L^\ast$, $\varnothing^\ast = \varepsilon$, $\varepsilon^\ast = \varepsilon$

**Closure properties** are also important properties of regular languages. They let us start from some simple automata and, through certain operations, build finite state machines (FSMs) that recognize other languages. In short, closure properties are a tool for building complex FSMs.

For the closure properties of regular languages, we have:

???+ note "Closure properties of regular languages"
    Let $L,M$ be two regular languages over the alphabet $\Sigma$, and let $h:\Sigma\to\Sigma^*$ be a map. Define the homomorphism of a string $s=s_1s_2\cdots s_n$ as $h(s)=h(s_1)h(s_2)\cdots h(s_n)$. Then
    
    1.  the union of two regular languages $L + M$ is regular,
    2.  the concatenation of two regular languages $LM$ is regular,
    3.  the closure of a regular language $L^*$ is regular,
    4.  the complement of a regular language $\Sigma^*\setminus L$ is regular,
    5.  the intersection of two regular languages $L\cap M$ is regular,
    6.  the difference of two regular languages $L\setminus M$ is regular,
    7.  the reversal of a regular language $L^R=\{s_n\cdots s_2s_1 \mid s=s_1s_2\cdots s_n\in L\}$ is regular,
    8.  the homomorphic image of a regular language $h(L)=\{h(s)\mid s\in L\}$ is regular,
    9.  the inverse homomorphic image of a regular language $h^{-1}(L) = \{ s \in \Sigma^\ast \mid h(s) \in L \}$ is regular.

A simple corollary is that every finite language is regular. In fact, a [trie](../string/trie.md) is an automaton that recognizes them.

## Myhill–Nerode theorem

The Myhill–Nerode theorem gives a criterion for whether a language is regular. It describes the structure of regular languages through equivalence classes.

???+ abstract "Nerode equivalence relation"
    For a language $L$ and any strings $x,y\in \Sigma^\ast$, if for every $z\in\Sigma^*$ we have $xz\in L\iff yz\in L$, then we say the strings $x$ and $y$ are equivalent with respect to $L$, written $x\equiv_L y$.

In other words, take two strings $x$ and $y$ and append the same arbitrary string $z$ (possibly empty) to both. If the results are always either both in $L$ or both not in $L$, we say $x$ and $y$ are equivalent with respect to $L$.

By this definition, we split the set of all finite strings into one or more equivalence classes. If and only if there are finitely many classes, we can use them to build a DFA that recognizes the language. The number of states of this DFA equals the number of equivalence classes, and it is the smallest among all DFAs that recognize the language. This is the Myhill–Nerode theorem.

???+ note "Myhill–Nerode theorem"
    A language $L$ is regular if and only if the equivalence relation $\equiv_L$ splits $\Sigma^\ast$ into finitely many equivalence classes.
    
    For any DFA that recognizes $L$, any two strings $x$ and $y$ that drive it to the same state must be in the same equivalence class.
    
    Moreover, the number of equivalence classes is the number of states of the minimal DFA recognizing $L$. Each equivalence class corresponds to exactly one state of the minimal DFA. This minimal DFA is unique up to isomorphism.

This theorem gives a way to build a DFA from the equivalence relation:

-   The set of states is the set of all equivalence classes of the relation. Pick an arbitrary representative string for each class (for example, one of the shortest strings).
-   To build the transition function, append the transition's character to the chosen representative string, and find the state of the equivalence class the new string belongs to. That state is the next state of the transition. Since all strings in the same class are equivalent, the choice of representative does not affect the result.
-   The start state is the equivalence class of the empty string $\varepsilon$.
-   The set of accepting states is the set of equivalence classes whose representatives belong to the given language.

As a classic example, the [suffix automaton](../string/sam.md) is a minimal DFA built using the Myhill–Nerode theorem.

The Myhill–Nerode theorem is usually used to build DFAs for some infinite regular languages. Often the conditions of the problem are simple enough that we only need to examine a set of fairly short strings to build an automaton that recognizes the whole language.

### Example problems

This section uses an example problem to show how to apply the Myhill–Nerode theorem in practice.

???+ example "[P12294 \[THUPC 2025 Finals\] A 01 String, n Ternary Operations, Final Value 1 (Hard Version)](https://www.luogu.com.cn/problem/P12294)"
    A ternary operation table $s_0s_1\cdots s_7$ on $a,b,c$ ($s$ consists only of $0$ and $1$) means: if bit $a+2b+4c$ of $s$ is $1$, return $1$; otherwise return $0$.
    
    Given the operation table $s$ and $q$ $01$ strings of length $2n+1$, answer for each $01$ string separately:
    
    Can you perform $n$ operations, each replacing three consecutive digits with their operation value, so that the result is $1$? Give a way to do it, or report that there is none.
    
    $1\le 2n+1\le 10^5,~\sum(2n+1)\le 3\times 10^5$.

??? note "Solution"
    The set of $01$ strings that can be reduced to $1$ is a regular language (that is, there is a DFA that decides whether a $01$ string can be reduced to $1$)[^prove-regular-language]. So we consider using the Myhill–Nerode theorem. Because the conditions are simple, experiments show that we only need to split $01$ strings of length $\le 9$ into equivalence classes, and to decide whether two strings are equivalent, we only need to try all suffixes of length $\le 6$. If, for every suffix of length $\le 6$ appended to both, the two strings either can both be reduced to the string we want or both cannot, then the two strings are equivalent.
    
    Each transition appends a new $01$ character to the current string, then replaces the new string with the shortest string in its equivalence class. Design an automaton based on these transitions. It can decide in $O(n)$ time whether a string of length $n$ can be reduced so that the result is $1$. Also, the automaton has very few states.
    
    For convenience, we build $6$ automata, deciding whether the result can be made $0,1,00,01,10,11$ respectively. Over all possible operation tables, an automaton has at most $47$ states.
    
    With the automata and suitable preprocessing, we can answer static range queries (can the range be reduced so that the result is $1$?) using binary lifting or a cat tree. A query takes $O(\log n)$ with the former and $O(1)$ with the latter.
    
    Use divide and conquer for the construction. Let $f(l,r,t)$ be a way to reduce the range $[l,r]$ to $t\in\{0,1,00,01,10,11\}$. Use heuristic splitting: keep two pointers $i,j$, one scanning left to right and one right to left, so that the split point $\textit{mid}$ is enumerated as $i$ or $j$. For $t\in\{0,1\}$, enumerate how $t$ is split into a left and a right part, where one part has a $t$ of length $2$ and the other a $t$ of length $1$. (For example, with the median table $s=00010111$, $1$ can be split into $01$ and $1$.) For $t\in\{00,01,10,11\}$, $t$ is split directly into a left and a right part.
    
    If the two parts are $t_1$ and $t_2$, check whether $[l,\textit{mid}]$ can produce $t_1$ and $[\textit{mid}+1,r]$ can produce $t_2$; if so, recurse directly. With the $O(1)$ cat tree checks, this heuristic splitting construction takes $O(n\log n)$; with binary lifting checks instead, the construction takes $O(n\log^2n)$.
    
    With a cat tree, the total complexity is $O(n|Q|\log n+n\log n)$, where $|Q|\le 47$. For convenience, the reference code uses binary lifting and reduces the constant factor with sqrt decomposition at the bottom level, giving a total complexity of $O(n|Q|\log n+n\log^2 n)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/fsm/fsm_1.cpp:main"
    ```

### Exercises

-   [Median Replace Hard](https://qoj.ac/problem/12010)
-   [JOISC 2024 Card Collection](https://www.luogu.com.cn/problem/P10436) (build an automaton with the Myhill–Nerode theorem; this problem can then support many range queries)

## DFA minimization

As mentioned earlier, two DFAs are equivalent if and only if they recognize the same regular language. By the language they recognize, all DFAs fall into infinitely many equivalence classes. In algorithms such as DP of DP, the DFA we build may have a $|Q|$ that is too large, making the outer DP transitions too slow. So we often need to find the minimal DFA in the DFA's equivalence class, to reduce the cost of the outer DP transitions.

The Myhill–Nerode theorem from the previous section already gives one construction. But for more complex problems, building directly with the Myhill–Nerode theorem requires going through a set of fairly long strings, which takes a lot of time. So we need a way to start from a DFA we have already built (usually easier to get) and build a minimal DFA directly. This is called the **DFA minimization** problem.

The usual algorithm for DFA minimization is **Hopcroft's algorithm**. The Myhill–Nerode theorem says that for any DFA recognizing a language, all strings that drive it to the same state must be Nerode equivalent. All Nerode equivalent strings correspond to the same state of the minimal DFA, so every state of the minimal DFA must be a set of states of the current DFA (here we assume every state of the current DFA is reachable from $q_0$; otherwise, delete the unreachable states first). We can start from the states of the existing DFA and split them into equivalence classes, without looking at concrete strings. Hopcroft's algorithm starts from the coarsest partition $\{F,Q\setminus F\}$ and uses a series of witnesses $A$ to refine the partition until it cannot be refined further. This is the core idea of Hopcroft's algorithm.

A **witness**  $A$ is a set of states such that it and its complement $Q\setminus A$ must belong to different Nerode equivalence classes. That is, for any $u\in A$ and $v\in Q\setminus A$, there is some string $s\in\Sigma^*$ such that, starting from $u$ and from $v$ and reading $s$, exactly one of them ends in an accepting state. So if two states $u,v\in Q$ have some character $c$ under which exactly one moves into the witness $A$ and the other moves outside $A$, i.e. exactly one of $\delta(u,c)\in A$ and $\delta(v,c)\in A$ holds, then $u,v$ are not equivalent either: starting from $u$ and from $v$ and reading the string $cs$, exactly one of them ends in an accepting state. So we can refine the partition by whether $\delta(u,c)\in A$ holds. Specifically, let

$$
S_x = \{u\mid u\in P_x,~\delta(u,c)\in A\}.
$$

If neither $S_x$ nor $P_x\setminus S_x$ is empty, the state set $P_x$ in the current partition can be refined into $S_x$ and $P_x\setminus S_x$.

At the start, put the set of accepting states $F$ into the witness set $W$ as a witness, i.e. $W\gets\{F\}$, and keep the current partition as $P\gets\{F,~Q\setminus F\}$. The initial witness is obviously valid: states in $F$ and in $Q\setminus F$ can never be equivalent. Each time, take any set $A$ out of the witness set $W$ and use it to refine the current partition. Enumerate every character $c\in\Sigma$. For each state set $P_x$ in the current partition $P$, compute the $S_x$ described above. If $S_x\neq\varnothing$ and $|S_x|\neq|P_x|$, then $P_x$ can be further split into two sets $S_x$ and $P_x\setminus S_x$; replace $P_x$ in $P$ with them.

Every time we get a finer partition, we get new witnesses. In principle, we could put both new sets $S_x$ and $P_x\setminus S_x$ into the witness set $W$ to be checked later. But this is not necessary. It is easy to see that, of the three witnesses $P_x,S_x,P_x\setminus S_x$, checking any two of them is enough to guarantee a correct result: there are only three outcomes, $\delta(u,c)\in S_x$, $\delta(u,c)\in P_x\setminus S_x$ and $\delta(u,c)\notin P_x$, and splitting a set into three parts takes only two tests. So when $P_x$ is split into $S_x$ and $P_x\setminus S_x$, if $P_x$ is still in the witness set $W$, the witness $P_x$ has not been checked yet, and we replace $P_x$ in $W$ with both $S_x$ and $P_x\setminus S_x$. Otherwise, the current partition must already be equivalent to[^smaller-evidence] the result of checking $P_x$, so we only need to put the smaller of $S_x$ and $P_x\setminus S_x$ into $W$. Like heuristic splitting, this gives a good complexity.

Written as pseudocode, the process is:

$$
\begin{array}{l}
\textbf{Algorithm } \text{Hopcroft's Algorithm}(Q, \Sigma, \delta, q_0, F): \\
\textbf{Input. } \text{DFA } M=(Q, \Sigma, \delta, q_0, F). \\
\textbf{Output. } \text{A partition of } Q \text{ into equivalence classes of the minimal DFA.} \\
\textbf{Method. } \\
\begin{array}{ll}
1 & P \gets \{F,\; Q \setminus F\} \\
2 & W \gets \{F\} \\
3 & \textbf{while } W \ne \varnothing \\
4 & \quad \text{choose and remove any } A \in W \\
5 & \quad \textbf{for each } c \in \Sigma \\
6 & \quad \quad S \gets \{ q \in Q \mid \delta(q,c) \in A \} \\
7 & \quad \quad \textbf{for each } Y \in P \text{ such that } S \cap Y \ne \varnothing \text{ and } Y \setminus S \ne \varnothing \\
8 & \quad \quad \quad Y_1 \gets S \cap Y,~Y_2 \gets Y \setminus S \\
9 & \quad \quad \quad P \gets (P \setminus \{Y\}) \cup \{Y_1, Y_2\} \\
10 & \quad \quad \quad \textbf{if } Y \in W \\
11 & \quad \quad \quad \quad W \gets (W \setminus \{Y\}) \cup \{Y_1, Y_2\} \\
12 & \quad \quad \quad \textbf{else} \\
13 & \quad \quad \quad \quad \text{add the smaller of } Y_1 \text{ and } Y_2 \text{ to } W \\
14 & \textbf{return } P
\end{array}
\end{array}
$$

In an implementation, the bottleneck is computing $S$. Going through every $q\in Q$ and testing whether $\delta(q,c)\in A$ is too slow. So before running the algorithm, precompute the reverse transitions $\{q\in Q\mid \delta(q,c)=a\}$; then, using them, go through each $a\in A$ to get the set $S$. This way, each transition $\delta(q,c)=a$ is visited only when $a$ is in some witness. The witness selection rule above guarantees that, in the sequence of witnesses containing $a$ that the algorithm actually uses, $A_1\supset A_2\supset\cdots\supset A_k$, each one is at least twice as large as the next, so $k\in O(\log |Q|)$. In other words, each transition is visited at most $O(\log |Q|)$ times, and there are $|Q||\Sigma|$ transitions in total, so the total complexity is $O(|Q||\Sigma|\log |Q|)$.

Here is a reference implementation:[^detail]

??? example "Reference implementation"
    ```cpp
    --8<-- "docs/misc/code/fsm/dfa.hpp:hopcroft"
    ```

This reference implementation allows the states of the automaton to carry any integer label, not just the two labels "accepting" and "not accepting". As you can see from the code, the only difference from the basic Hopcroft's algorithm is how the initial partition and the witness set are built. Such an extended automaton is also called a [Moore machine](https://en.wikipedia.org/wiki/Moore_machine). For an application, see the second example problem in this section.

### Example problems

This section uses two example problems to show how to apply DFA minimization in practice.

???+ example "Example problem"
    Given a $01?$ string $a$ of length $n$ and a variable $x = 0$ at the start, we go through each $a_i$ in order and do the following:
    
    1.  If $a_i = 0$, set $x \gets x - \text{lowbit}(x)$;
    2.  If $a_i = 1$, set $x \gets x + \text{lowbit}(2^k - 1 - x)$;
    3.  If $a_i = ?$, you may choose $0$ or $1$ freely, giving one of the two operations above.
    
    If $x \in [0, r]$ at the end, the sequence of operations is called good.
    
    For each $i = 1 \ldots n$, count the "good" complete sequences under the condition that $a_i = 0$ is forced. In particular, if $a_i = 1$, the answer is $0$.
    
    $1\le n\le 10^5,~1\le k\le 20,~0\le r<2^k$. Output the answers modulo $998244353$.

??? note "Solution"
    Consider a naive DP. Let $f_{i,j}$ be the number of ways that, starting from $x=0$ and applying the operations in $[1,i]$, the current number is $j$. Let $g_{i,j}$ be the number of ways that, starting from $x=j$ and applying the operations in $[i,n]$, we end with $x \in [0, r]$. The answer when $a_i=0$ is forced is $\sum_j f_{i-1,j}g_{i+1,j - \text{lowbit}(j)}$. This takes $O(n2^k)$.
    
    Instead, build the transitions on $j$ directly as a DFA, run DFA minimization, and then do the DP.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/fsm/fsm_2.cpp:main"
    ```

???+ example "[Minimal Subset Difference](https://codeforces.com/contest/956/problem/F)"
    Let $f(n)$ be the minimum absolute value you can get by inserting a plus or minus sign between every pair of adjacent digits of the decimal number $n$.
    
    There are $T$ queries. Each gives $l, r, k$; count the $m$ with $l \le m \le r$ and $f(m) \le k$.
    
    $1 \le T \le 5\times 10^4$, $1 \le l \le r \le 10^{18}$, $0 \le k \le 9$.

??? note "Solution"
    First, here is a greedy way to compute $f(n)$. Go through the digits from the most significant to the least significant, starting with a sum of $0$. At each digit, if the current sum is at most $0$, add the digit; otherwise subtract it. With this process, the absolute value of the greedy result is always at most $9$. So the true $f(n)$ is at most $9$ in absolute value.
    
    Next, think about how large the intermediate values can get while building the final answer. The answer is at most $9$, the number has at most $19$ digits, and each step adds or subtracts at most $9$. So any intermediate value must be at most $90$, or else it could not be brought back down in the end. In fact, this bound can be made even lower[^upper-bound].
    
    Consider a naive DP of DP. First, think about how the inner DP decides the answer for a number: let $g_{i,c}$ say whether $c$ can be obtained using only the first $i$ digits. From the above, we only need to keep values of $c$ that are at most $90$. If the current digit is $v$, the transitions are:
    
    $$
    g_{i+1,c+v}\gets g_{i+1,c+v}\lor g_{i,c},~
    g_{i+1,|c-v|}\gets g_{i+1,|c-v|}\lor g_{i,c}.
    $$
    
    The outer DP is a digit DP. Split each query into a difference of two prefix queries. Let the state be $f_{\textit{len},\textit{lim},\textit{sta}}$, whose indices mean: we have processed up to digit $\textit{len}$, whether the upper bound still applies, and the current state of the automaton is $\textit{sta}$.
    
    Unlike an ordinary DFA, we need to record the corresponding answer for each state of the automaton. A brute-force search shows that the inner DP has only $19564$ states. Running DFA minimization on it then brings the number of states down to $715$.
    
    Now precompute all digit DP answers with $\textit{lim}=0$. Then for each test case we only need to handle the $\textit{lim}=1$ cases, which gives the answer quickly.
    
    The time complexity is $O(|S||\Sigma|\log |S|+(|Q||\Sigma|+T)|\Sigma|\log_{10} V)$ ($|S|=19564$, $|Q|=715$).

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/fsm/fsm_3.cpp:main"
    ```

### Exercises

-   [Language Recognition](http://poj.org/problem?id=3576)
-   [Equanimous](https://qoj.ac/problem/7083)

## Common applications of automata

This section lists some automata commonly seen in competitive programming[^is-dfa].

### Trie

The [trie](../string/trie.md) is the first automaton most OIers meet. It accepts exactly the strings in a given set. The transition function is the edges of the trie, and the accepting states are the states reached when inserting each string into the trie.

### KMP automaton

The [KMP algorithm](../string/kmp.md) can be viewed as an automaton. The KMP automaton for a string $s$ accepts exactly the strings that end with $s$, and its accepting state is $|s|$.

The transition function is as follows, where $s$ is 1-indexed and $\pi(i)$ is the length of the longest proper prefix of $s[1..i]$ that is also a suffix (that is, $\pi[i-1]$ in the [prefix function](../string/kmp.md)):

$$
\delta(i, c)=
\begin{cases}
i+1&i<|s|\land s[i+1]=c\\
0&s[1]\ne c\land i=0\\
\delta(\pi(i),c)&(i=|s|\lor s[i+1]\ne c)\land i>0
\end{cases}
$$

### Aho–Corasick automaton

The [Aho–Corasick automaton](../string/ac-automaton.md) accepts exactly the strings that end with some element of a given set of strings. In other words, it is trie + KMP.

### Suffix automaton

The [suffix automaton](../string/sam.md) accepts exactly the suffixes of a given string.

### General suffix automaton

The [general suffix automaton](../string/general-sam.md) accepts exactly the suffixes of the elements of a given set of strings. In other words, it is trie + SAM.

The general SAM relates to the SAM the same way the Aho–Corasick automaton relates to the KMP automaton.

### Palindromic tree

The [palindromic tree](../string/pam.md) is special: it is not easy to define it as an automaton.

If we must define it, it accepts exactly the **center and right half** of every palindromic substring of a string.

For odd-length palindromes, "center and right half" means just what it says. For even-length palindromes, it is defined as a special character followed by the right half. This definition looks strange, but it makes the PAM a real automaton rather than just two trees.

### Subsequence automaton

The [subsequence automaton](../string/seq-automaton.md) accepts exactly the subsequences of a given string.

### DP of DP

[DP of DP](../dp/dp-of-dp.md) is an application of automata. It can be seen as a technique that first builds an automaton with an inner DP, and then does counting or optimization with a DP on the automaton in the outer layer.

## Suffix links

Automata are closely tied to matching, and a basic idea of matching is "if this string doesn't work, try its suffix". So many automata (KMP, Aho–Corasick, SAM, PAM) have the concept of suffix links.

A state corresponds to several strings. Its suffix link points to the state of the longest common proper suffix of the strings of that state. In general, suffix links form a tree, and the suffix link trees of different automata share some properties, which are worth noticing as you study them.

## Further reading

-   [Computational Complexity (1) Warming Up: Automaton Models](https://lingeros-tot.github.io/2019/03/05/Warming-Up-自动机模型/)
-   [Chinese National Training Team 2021 paper, Xu Zhe'an: On Finite State Automata and Their Applications](https://github.com/OIerTFX/IOI/blob/master/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2021%E8%AE%BA%E6%96%87%E9%9B%86/pdf-files/%E5%BE%90%E5%93%B2%E5%AE%89%20%E6%B5%85%E8%B0%88%E6%9C%89%E9%99%90%E7%8A%B6%E6%80%81%E8%87%AA%E5%8A%A8%E6%9C%BA%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8.pdf)
-   [Myhill–Nerode theorem - Wikipedia](https://en.wikipedia.org/wiki/Myhill%E2%80%93Nerode_theorem)
-   Knuutila, Timo. "Re-describing an algorithm by Hopcroft." Theoretical Computer Science 250, no. 1-2 (2001): 333-363.
-   Hopcroft, John E., Rajeev Motwani, and Jeffrey D. Ullman. "Introduction to automata theory, languages, and computation." 2nd ed. Addison-Wesley, 2001.

[^nfa-and-nfaepsilon]: This definition allows transitions between states on the empty character ($\varepsilon$), so more precisely it is a nondeterministic finite automaton with $\varepsilon$ transitions (NFA-$\varepsilon$). Some textbooks simply call it an NFA, and for brevity this article does the same. In theory NFA and NFA-$\varepsilon$ are distinguished, but in practice they have the same computational power.

[^state-elimination-method]: See Section 3.2 of [Chinese National Training Team 2021 paper, Xu Zhe'an: On Finite State Automata and Their Applications](https://github.com/OIerTFX/IOI/blob/master/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2021%E8%AE%BA%E6%96%87%E9%9B%86/pdf-files/%E5%BE%90%E5%93%B2%E5%AE%89%20%E6%B5%85%E8%B0%88%E6%9C%89%E9%99%90%E7%8A%B6%E6%80%81%E8%87%AA%E5%8A%A8%E6%9C%BA%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8.pdf).

[^prove-regular-language]: See the [official editorial](https://qoj.ac/download.php?type=attachments&id=2079&r=1).

[^smaller-evidence]: "Equivalent to" here means: although $P_x$ may never actually have been checked, checking $P_x$ against the current partition would not refine it at all. Put simply, in the tree of witness sets produced by splitting, some ancestor of it and every side branch along the path have already been checked, so by induction it is as if it had been checked too.

[^detail]: There is one detail in the implementation: for a witness $A$, after checking some of the characters, the witness set may already have been split into $B$ and $C$. Assume $|B|\ge |C|$. In the reference implementation, the smaller set $C$ is pushed to the end of the witness queue, and the larger set $B$ takes the original place of $A$. When the algorithm continues, it actually only uses witness $B$ to check the remaining characters. This is correct, because for the characters already checked, at least the two sets $A$ and $C$ have been verified, and for the characters not yet checked, at least the two sets $B$ and $C$ will be verified.

[^upper-bound]: See Example 5.2 in [Chinese National Training Team 2021 paper, Xu Zhe'an: On Finite State Automata and Their Applications](https://github.com/OIerTFX/IOI/blob/master/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2021%E8%AE%BA%E6%96%87%E9%9B%86/pdf-files/%E5%BE%90%E5%93%B2%E5%AE%89%20%E6%B5%85%E8%B0%88%E6%9C%89%E9%99%90%E7%8A%B6%E6%80%81%E8%87%AA%E5%8A%A8%E6%9C%BA%E5%8F%8A%E5%85%B6%E5%BA%94%E7%94%A8.pdf).

[^is-dfa]: The definition in this article requires an automaton to be complete, that is, every state must have a transition on every character. Descriptions of these string automata usually leave out the dead state; the trie and the SAM are examples. To fit the definition in this article, a dead state must be added explicitly to the descriptions of these automata.
