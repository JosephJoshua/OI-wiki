Before reading this article, please read [Automata](../misc/fsm.md) first.

## Definition

A subsequence automaton (sequence automaton) is an automaton that accepts exactly the subsequences of a string, and nothing else.

In this article, $s$ denotes this string.

### States

If $s$ has $n$ characters, the subsequence automaton has $n+1$ states.

Let $t$ be a subsequence of $s$. Then $\delta(start, t)$ is the position where the first occurrence of $t$ in $s$ ends.

In other words, a state $i$ represents the set difference between the subsequences of the prefix $s[1..i]$ and the subsequences of the prefix $s[1..i-1]$.

All states of the subsequence automaton are accepting states.

### Transitions

From the definition of states, we get $\delta(u, c)=\min\{i|i>u,s[i]=c\}$, that is, the position of the next occurrence of character $c$.

Why the "next" occurrence? Because if $i>j$, the subsequences of the suffix $s[i..|s|]$ form a subset of the subsequences of the suffix $s[j..|s|]$, so it is always best to pick a position as early as possible.

## Implementation

Scan from back to front, and keep track of the earliest position of each character seen so far:

$$
\begin{array}{ll}
1 & \textbf{Input. } \text{A string } S\\
2 & \textbf{Output. } \text{The state transition of the sequence automaton of }S \\
3 & \textbf{Method. }  \\
4 & \textbf{for }c\in\Sigma\\
5 & \qquad next[c]\gets null\\
6 & \textbf{for }i\gets|S|\textbf{ downto }1\\
7 & \qquad next[S[i]]\gets i\\
8 & \qquad \textbf{for }c\in\Sigma\\
9 & \qquad\qquad \delta(i-1,c)\gets next[c]\\
10 & \textbf{return }\delta
\end{array}
$$

Building it this way takes $O(n|\Sigma|)$ time.

## Example problem

???+ example "[HEOI 2015 Shortest Uncommon Substring](https://loj.ac/problem/2123)"
    You are given two strings $A$ and $B$ of lowercase English letters ($1\le |A|, |B|\le 2000$). Find:
    
    1.  a shortest substring of $A$ that is not a substring of $B$;
    2.  a shortest substring of $A$ that is not a subsequence of $B$;
    3.  a shortest subsequence of $A$ that is not a substring of $B$;
    4.  a shortest subsequence of $A$ that is not a subsequence of $B$.

??? note "Solution"
    Parts 1 and 3 need a suffix automaton and are solved in a similar way, so here we only explain parts 2 and 4.
    
    Part 2 is fairly easy: enumerate the substrings of A and feed each one into the subsequence automaton of B. If it is not accepted, count it toward the answer.
    
    Part 4 needs DP. Let $f(i, j)$ be the number of characters we still need to add so that the string is no longer a common subsequence, when we are at state $i$ in the subsequence automaton of A and at state $j$ in the subsequence automaton of B. The transition is:
    
    $$
    f(i, j)=\min_{\delta_A(i,c)\ne \textit{null}}f(\delta_A(i, c), \delta_B(j, c))+1.
    $$
    
    The base case is $f(i, \textit{null})=0$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/seq-automaton/seq-automaton_1.cpp"
    ```
