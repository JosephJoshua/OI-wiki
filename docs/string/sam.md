author: GoodCoder666, abc1763613206, ksyx

## Notation

-   $\Sigma$: the alphabet. Its size is written $|\Sigma|$.
-   $s$: the string. Its length is $|s| = n$, and indices start from $0$.
-   $t_0$: the initial state.
-   $\operatorname{endpos}(t)$: the set of end positions of the substring $t$ in the string $s$.
-   $\operatorname{link}(v)$: the suffix link of state $v$.
-   $\operatorname{len}(v)$: the length of the longest substring of state $v$.
-   $\operatorname{longest}(v)$: the longest substring of state $v$.
-   $\operatorname{minlen}(v)$: the length of the shortest substring of state $v$.
-   $\operatorname{shortest}(v)$: the shortest substring of state $v$.

## Overview of the suffix automaton

The **suffix automaton** (SAM) is a powerful data structure that solves many string problems.

For example, the following string problems can all be solved in linear time with a SAM:

-   find all occurrences of one string inside another string;
-   count how many distinct substrings a given string has.

Intuitively, the SAM of a string can be seen as a compressed form of **all substrings** of the string. Notably, the SAM stores all this information in a highly compressed form. For a string of length $n$, it takes only $O(n)$ space, and it can be built in only $O(n)$ time. More precisely, for $n\ge 3$, a SAM has at most $2n-1$ nodes and $3n-4$ transitions.

## Definition

The SAM of a string $s$ is the minimal [DFA](../misc/fsm.md#deterministic-finite-automata) that accepts all suffixes of $s$.

In other words:

-   A SAM is a directed acyclic graph. Its nodes are called **states**, and its edges are called **transitions** between states.
-   The graph has a source $t_0$, called the **initial state**; every other node can be reached from $t_0$.
-   Each **transition** is labeled with a character. All transitions leaving a node have **different** labels.
-   There are one or more **terminal states**. If we start from the initial state $t_0$ and end in a terminal state, the labels of the transitions on the path, joined together, always form a suffix of $s$. Conversely, every suffix of $s$ is formed by some path from $t_0$ to a terminal state.
-   Among all automata that satisfy the conditions above, the SAM has the fewest nodes.

The key to the SAM is exactly this minimality. In fact, simply building a [trie](./trie.md) of all suffixes of $s$ (the suffix trie) also gives a DFA that accepts all suffixes of $s$. But in the worst case, that automaton has $\Theta(n^2)$ nodes, which is too many. As the examples below show, many nodes in the DFA obtained from the trie of all suffixes are duplicates and can be merged. The SAM pushes this merging of nodes to the limit, keeping the size of the resulting DFA at $O(n)$. In this sense, the SAM is a "compressed" trie of all suffixes of the string.

### Substrings and paths

The simplest and most important property of the SAM is that it contains information about all substrings of $s$. For any path starting from the initial state $t_0$, if we write down the labels of all transitions on the path, we get a **substring** of $s$. Conversely, every substring of $s$ corresponds to some path starting from $t_0$.

To keep things simple, we say a substring **corresponds** to this path (the one that starts from $t_0$ and whose transition labels spell out the substring). Conversely, we say any path **corresponds** to the string formed by its labels.

There may be more than one path reaching a state, so we say a state corresponds to a set of strings, where each string in the set corresponds to one of these paths.

### Simple examples

Here we show the suffix automata of a few simple strings.

The initial state is shown in blue, and terminal states in green.

For the string $s=\varepsilon$:

![](./images/SAM/SA.svg)

For the string $s=\texttt{a}$:

![](./images/SAM/SAa.svg)

For the string $s=\texttt{aa}$:

![](./images/SAM/SAaa.svg)

For the string $s=\texttt{ab}$:

![](./images/SAM/SAab.svg)

For the string $s=\texttt{abb}$:

![](./images/SAM/SAabb.svg)

For the string $s=\texttt{abbb}$:

![](./images/SAM/SAabbb.svg)

In the last example, if we built the trie of all suffixes directly, the paths $\texttt{bbb}$ and $\texttt{abbb}$ would lead to different nodes. But both nodes are terminal states, and adding any further characters never gives a longer match. This means the two nodes behave the same way under the automaton's transitions, so they can be merged into one node. This gives the SAM shown in the figure. The discussion below extends this idea of merging nodes to all cases, and shows that if we merge nodes properly, the resulting SAM has only $O(n)$ nodes and transitions.

## A linear-time construction algorithm

Before describing the algorithm that builds a SAM in linear time, we need to introduce two concepts that are very important for understanding the construction, and briefly prove their properties. The end-position set $\operatorname{endpos}$ defines the nodes of the SAM (that is, it gives the necessary and sufficient condition for nodes to be merged), while the suffix link $\operatorname{link}$ is simply the natural counterpart in the SAM of the [fail pointer](./ac-automaton.md#failure-pointers) in the Aho–Corasick automaton.

### End positions `endpos`

Consider any non-empty substring $t$ of the string $s$. We write $\operatorname{endpos}(t)$ for the set of all positions in $s$ where $t$ ends (assuming characters are numbered from zero). For example, for the string $\texttt{abcbc}$, we have $\operatorname{endpos}(\texttt{bc})=\{2,4\}$.

Two substrings $t_1$ and $t_2$ may have exactly the same end positions: $\operatorname{endpos}(t_1)=\operatorname{endpos}(t_2)$. This defines an equivalence relation on the substrings of $s$. All non-empty substrings of $s$ can be divided into several **equivalence classes** by their end-position sets $\operatorname{endpos}$.

It turns out that each such equivalence class corresponds to one state of the SAM[^state-endpos]. That is, whenever two substrings have the same end positions, their paths in the SAM lead to the same state. In other words, each non-initial state of the SAM corresponds to one or more non-empty substrings with the same $\operatorname{endpos}$. In short, the states of the SAM are exactly the equivalence classes of all non-empty substrings, plus the initial state.

Let's accept this fact for now; we will build the SAM construction algorithm on it. We will also show that the result satisfies all the properties a SAM must have except minimality, and minimality follows from the [Myhill–Nerode theorem](../misc/fsm.md#myhillnerode-theorem).

From the values of $\operatorname{endpos}$ we can draw some important conclusions, which explain how the different substrings of the same state relate to each other.

???+ note "Lemma 1"
    Two non-empty substrings $u$ and $w$ of $s$ (assume $\left|u\right|\le \left|w\right|$) have the same $\operatorname{endpos}$ if and only if every occurrence of $u$ in $s$ is as a suffix of $w$.

??? note "Proof"
    The lemma clearly holds. If $u$ and $w$ have the same $\operatorname{endpos}$, then $u$ is a suffix of $w$, and it appears in $s$ only as a suffix of $w$. Conversely, by definition, if $u$ is a suffix of $w$ and appears in $s$ only as a suffix of $w$, then the two substrings have the same $\operatorname{endpos}$.

???+ note "Lemma 2"
    Consider two non-empty substrings $u$ and $w$ (assume $\left|u\right|\le \left|w\right|$). Then either $\operatorname{endpos}(u)\cap \operatorname{endpos}(w)=\varnothing$ or $\operatorname{endpos}(w)\subseteq \operatorname{endpos}(u)$, depending on whether $u$ is a suffix of $w$:
    
    $$
    \begin{cases}
    \operatorname{endpos}(w) \subseteq \operatorname{endpos}(u), & \text{if } u \text{ is a suffix of } w, \\
    \operatorname{endpos}(w) \cap \operatorname{endpos}(u) = \varnothing, & \text{otherwise}.
    \end{cases}
    $$

??? note "Proof"
    If the sets $\operatorname{endpos}(u)$ and $\operatorname{endpos}(w)$ have at least one common element, then since $u$ and $w$ end at the same position, $u$ is a suffix of $w$. So wherever $w$ occurs, the substring $u$ also occurs. Therefore $\operatorname{endpos}(w)\subseteq \operatorname{endpos}(u)$.

???+ note "Lemma 3"
    Consider an equivalence class of substrings with the same $\operatorname{endpos}$, and sort all substrings in the class by decreasing length. Then each substring is exactly $1$ shorter than the one before it, and each substring is also a suffix of the one before it. In other words, for any two substrings in the same equivalence class, the shorter one is a suffix of the longer one, and the lengths of the substrings in the class are consecutive, covering every integer in some interval.

??? note "Proof"
    If the equivalence class contains only one substring, the lemma clearly holds. Now consider equivalence classes with more than $1$ substring.
    
    By Lemma 1, of two different strings with the same $\operatorname{endpos}$, one must be longer than the other, and the shorter one is always a proper suffix of the longer one. That is, an equivalence class never contains two strings of the same length.
    
    Let $w$ be the longest string in the class and $u$ the shortest. By Lemma 1, $u$ is a proper suffix of $w$. Now consider any suffix of $w$ whose length is in the interval $[\left|u\right|,\left|w\right|]$. It is easy to see that this suffix is also in the same class, because it can only appear in $s$ as a suffix of $w$ (since the shorter suffix $u$ appears in $s$ only as a suffix of $w$). So by Lemma 1, this suffix has the same $\operatorname{endpos}$ as $w$.

In one sentence: the substrings of the same state all have different lengths, which form a run of consecutive natural numbers, and the shorter ones are always suffixes of the longer ones.

### Suffix links `link`

Consider some state $v\neq t_0$ of the SAM. We already know that state $v$ corresponds to an equivalence class of substrings with the same $\operatorname{endpos}$. If we let $w$ be the longest of these strings, then all the other strings are suffixes of $w$.

We also know that the first few suffixes of $w$ (in decreasing order of length) all belong to this equivalence class, and the other suffixes (there is at least one: the empty suffix) are in other classes. Let $t$ be the longest of those other suffixes; we then point the suffix link of $v$ to the state of the equivalence class that $t$ belongs to.

In other words, the **suffix link** $\operatorname{link}(v)$ of $v$ points to the state of the longest suffix of $w$ whose $\operatorname{endpos}$ set differs from that of $w$; this is also the longest suffix of $w$ that occurs more times in $s$ than $w$ does.

For convenience, we say that the equivalence class of the initial state $t_0$ contains only the empty string, and $\operatorname{endpos}(t_0)=\{-1,0,\ldots,\left|s\right|-1\}$.

???+ note "Lemma 4"
    All suffix links form a tree rooted at $t_0$.

??? note "Proof"
    For any state $v\neq t_0$, the state that the suffix link $\operatorname{link}(v)$ points to corresponds to strictly shorter strings (by the definition of suffix links and Lemma 3). So by following suffix links, we always reach the initial state $t_0$, which corresponds to the empty string.

???+ note "Lemma 5"
    Build a tree whose nodes are the $\operatorname{endpos}$ sets and whose edges are given by set inclusion (i.e., the $\operatorname{endpos}$ set of each child is contained in that of its parent). This tree is the same as the tree formed by the suffix links $\operatorname{link}$.

??? note "Proof"
    By Lemma 2, the $\operatorname{endpos}$ sets of any SAM form a tree (since any two sets are either disjoint or one is a subset of the other).
    
    Now consider any state $v\neq t_0$ and its suffix link $\operatorname{link}(v)$. From the definition of suffix links and Lemma 2, we get
    
    $$
    \operatorname{endpos}(v)\subsetneq \operatorname{endpos}(\operatorname{link}(v)).
    $$
    
    Note that this must be $\subsetneq$ and not $\subseteq$, because if $\operatorname{endpos}(v)=\operatorname{endpos}(\operatorname{link}(v))$, then $v$ and $\operatorname{link}(v)$ should have been merged into one node.
    
    Moreover, $\operatorname{endpos}(\operatorname{link}(v))$ is exactly the smallest $\operatorname{endpos}$ set that strictly contains $\operatorname{endpos}(v)$.

Combining this with the earlier lemmas: the tree formed by suffix links is essentially a tree of $\operatorname{endpos}$ sets.

Below is an **example** of the suffix link tree produced when building the SAM of the string $\texttt{abcbc}$. Each node is labeled with the longest substring of its equivalence class.

![](./images/SAM/SA_suffix_links.svg)

If the figure helps you build some intuition about the suffix automaton, that will make it easier to understand its construction algorithm and applications below.

???+ example "Explanation of the figure"
    -   The SAM has a longest path whose labels spell exactly the string $\texttt{abcbc}$ itself. This path starts from the initial state, and each state it passes corresponds to a prefix of $\texttt{abcbc}$ ($\varepsilon,\texttt{a},\texttt{ab},\texttt{abc},\texttt{abcb},\texttt{abcbc}$). These states are crucial in later [applications](#suffix-link-tree).
    -   The suffix link tree can be seen as what you get by "compressing" the paths along which these "prefix states" move to the root (the initial state) by following suffix links.
    
        -   Along each path, the sets of strings of the nodes form a partition of all suffixes of the corresponding prefix. For example, the path from the state labeled $\texttt{abcbc}$ to the root along suffix links is $\texttt{abcbc}\rightarrow\texttt{bc}\rightarrow\varepsilon$. Here, the node $\texttt{abcbc}$ actually corresponds to the set of strings $\{\texttt{abcbc},\texttt{bcbc},\texttt{cbc}\}$, the node $\texttt{bc}$ corresponds to $\{\texttt{bc},\texttt{c}\}$, and the node $\varepsilon$ corresponds to the empty string.
        -   Different paths may share the same node, which is why there is "compression". For example, the paths $\texttt{abc}\rightarrow\texttt{bc}\rightarrow\varepsilon$ and $\texttt{abcbc}\rightarrow\texttt{bc}\rightarrow\varepsilon$ share the node $\texttt{bc}$. This is because $\operatorname{endpos}(\texttt{bc})=\{2,4\}$: the occurrence of $\texttt{bc}$ ending at position $2$ is immediately preceded by the character $\texttt{a}$, while the one ending at position $4$ is immediately preceded by $\texttt{c}$. So when we add characters in front (i.e., move against the suffix links), the end-position set (i.e., the state) splits.
        -   The suffix link tree only needs to "compress" these suffix paths together properly, and no other nodes need to be considered. This is because every substring is a suffix of some prefix, so it must appear on one of these paths. The construction algorithm below essentially adds characters one by one, and for each new prefix builds such a suffix path and "compresses" it properly into the existing paths (i.e., without rebuilding states and transitions that already exist).
        -   The terminal states are exactly the nodes on the suffix path of the whole string $\texttt{abcbc}$.
    -   Transitions into the same state always have the same label, and their source states always lie on some (contiguous) path in the suffix link tree. For example, two states transition into state $\texttt{abcb}$: $\texttt{abc}$ and $\texttt{bc}$. They lie on the path $\texttt{abc}\rightarrow\texttt{bc}$ in the suffix link tree. Note that they correspond to the string sets $\{\texttt{abc}\}$ and $\{\texttt{bc},\texttt{c}\}$; appending the character $\texttt{b}$ to these strings gives the string set $\{\texttt{abcb},\texttt{bcb},\texttt{cb}\}$ of state $\texttt{abcb}$.
    
        -   Different states can transition into the same state after adding a character because appending a character can only reduce the set of occurrence positions, so end-position sets that were different may become the same.
    -   In the suffix link tree, the $\operatorname{endpos}$ set of each node is the union of the $\operatorname{endpos}$ sets of its children, plus at most one more position. Moreover, this new position exists if and only if the node corresponds exactly to the prefix of the original string ending at that position. In the figure, no node of the suffix link tree that is neither the root nor a leaf corresponds to a prefix of $\texttt{abcbc}$, so this case does not occur.

The suffix automaton stores information about all substrings of the string. This can be understood from two angles:

-   The SAM itself can be seen as a compressed version of the trie of all suffixes of the string. So it stores information about all prefixes of all suffixes, which amounts to all substrings of the string.
-   The suffix link tree of the SAM can be seen as a compressed version of the suffix paths of all prefixes of the string. So it stores information about all suffixes of all prefixes, which also amounts to all substrings of the string.

Both angles are useful for different problems.

### Summary

Before discussing the algorithm itself, let's summarize what we have so far and introduce some helper notation.

-   The substrings of $s$ can be divided into several equivalence classes by their end-position sets $\operatorname{endpos}$;

-   The SAM consists of the initial state $t_0$ and one state for each $\operatorname{endpos}$ equivalence class (of non-empty substrings);

-   Each state $v$ matches one or more substrings. We write $\operatorname{longest}(v)$ for the longest of them and $\operatorname{len}(v)$ for its length. Similarly, $\operatorname{shortest}(v)$ is the shortest substring, and its length is $\operatorname{minlen}(v)$. Then all strings of this state are different suffixes of $\operatorname{longest}(v)$, and their lengths cover every integer in the interval $[\operatorname{minlen}(v),\operatorname{len}(v)]$ exactly once.

-   For any state $v\neq t_0$, the suffix link is an edge to the state of the suffix of $\operatorname{longest}(v)$ with length $\operatorname{minlen}(v)-1$. All suffix links form a tree rooted at $t_0$. This tree also represents the inclusion relation between $\operatorname{endpos}$ sets.

-   For any state $v\neq t_0$, $\operatorname{minlen}(v)$ can be expressed using the suffix link $\operatorname{link}(v)$:

    $$
    \operatorname{minlen}(v)=\operatorname{len}(\operatorname{link}(v))+1.
    $$

-   If we start from any state $v_0$ and follow suffix links, we always reach the initial state $t_0$. Along the way we get a sequence of pairwise disjoint intervals $[\operatorname{minlen}(v_i),\operatorname{len}(v_i)]$, whose union is the contiguous interval $[0,\operatorname{len}(v_0)]$.

### Algorithm

Now we can discuss the algorithm that builds the SAM. It is an **online** algorithm: we add the characters of the string one by one and update the SAM accordingly at each step.

Before going into the detailed implementation, let's first use figures to get a feel for how the SAM may change when a new character $c$ is added.

???+ note "An intuitive look at the incremental construction"
    We can build the SAM of $s+c$ on top of the SAM of $s$. From the explanation of the figure above, we only need to build the suffix path of the newly added prefix (i.e., $s+c$) and compress it into the existing paths. Moreover, as described above, every node on the new suffix path must be reachable by a transition by $c$ from some node on the suffix path of the original string $s$.
    
    Let's first consider what the suffix path of $s$ may look like before adding the new character $c$, and how it transitions by $c$. The most general case is shown below:
    
    ![](./images/SAM/sam-suffix-path-1.svg)
    
    In the figure, the suffix path of the original string $s$ is $p_0\rightarrow p_1\rightarrow\cdots\rightarrow p_6\rightarrow t_0$, with suffix links shown as red arrows. Some of the nodes (namely $p_2\sim p_6$) already have transitions by $c$. Since appending the same character to consecutive suffixes again gives consecutive suffixes, the targets of these transitions form another suffix path $q_1\rightarrow q_2\rightarrow q_3\rightarrow t_0$. We can make two observations:
    
    -   On the suffix path of $s$, the nodes without a transition by $c$ must be the first few nodes. Once some node (here $p_2$) has a transition by $c$, every later node on the path also has one.
    
        **Explanation**: let $s_2=\operatorname{longest}(p_2)$. All later nodes correspond to suffixes of $s_2$. So if $s_2+c$ also appears in $s$, then any suffix of $s_2$ followed by $c$ also appears in $s$, and therefore all these nodes have transitions by $c$.
    -   The nodes that reach a node $q_i$ by $c$ always form a contiguous segment in the suffix link tree, but this segment does not have to lie entirely on the suffix path from $p_0$ to the root. In particular, only the first few nodes of the segment for the first node $q_1$ **may** be off this suffix path. For example, in the figure, node $q_1$ corresponds to the nodes $p_1'\rightarrow p_2\rightarrow p_3$, where $p_1'$ is not on the suffix path of $p_0$.
    
        **Explanation**: let $s_2=\operatorname{longest}(p_2)$. Then $s_2+c$ corresponds to $q_1$, but clearly $s_2+c\neq\operatorname{longest}(q_1)$ in the figure, since the latter is $\operatorname{longest}(p'_1)+c$. This shows that some of the strings of $q_1$ cannot be reached from $s_2$ and its suffixes. On the other hand, the strings in $q_2$ must be suffixes of $s_2+c$, so after removing the trailing $c$ they must be suffixes of $s_2$. That is, the nodes that transition by $c$ into $q_2$ must lie on the suffix path starting at $p_2$. This is also why only some nodes in the segment of the first node $q_1$ may be off the suffix path of $p_0$.
    
    For this figure, what changes if we append a character $c$ to the end of $s$ and build the corresponding suffix path? The answer is shown below:
    
    ![](./images/SAM/sam-suffix-path-2.svg)
    
    Since node $q_0$ is reached by $c$ from node $p_0$, which corresponds to the original string $s$, it corresponds to the new string $s+c$. So its suffix path $q_0\rightarrow q_1''\rightarrow q_2\rightarrow q_3\rightarrow t_0$ is the new suffix path. If a node $p_i$ on the old suffix path already has a transition by $c$, the new suffix path must also pass through the node that transition reaches, so the old nodes can be reused directly. The new suffix path has one and only one brand-new node, $q_0$, which receives the transitions from the first nodes of the old suffix path that had no transition by $c$.
    
    Besides these obvious facts, notice that the old node $q_1$ is also copied, or in other words split into two nodes $q'_1\rightarrow q_1''$. This is because the new suffix path only partly overlaps the existing paths: among the strings of the old node $q_1$, only the shorter ones (those reachable from nodes $p_2$ and $p_3$) appear on the new suffix path, while the longer ones (those reachable from node $p_1'$) do not. So the new suffix path can only pass through part of node $q_1$, and $q_1$ has to be split into two nodes to represent this. By the same reasoning, as explained above, the nodes $q_2$ and $q_3$ after $q_1$ cannot be reached from nodes off the suffix path of $p_0$, so all of their strings appear on the new suffix path, and they do not need to be split.
    
    In terms of what SAM states mean, each state is an $\operatorname{endpos}$ set. Let $i$ be the new end position when the string is extended. Then the new node $q_0$ is the end-position set $\{i\}$, the split nodes $q_1'$ and $q_1''$ correspond to the sets $\operatorname{endpos}(q_1)$ and $\operatorname{endpos}(q_1)\cup\{i\}$, and the later nodes $q_2$ and $q_3$ actually have $i$ added to their old end-position sets. That is, although $q_2$, $q_3$ and their transitions do not change, their $\operatorname{endpos}$ sets do grow.
    
    This explains the most complex, most general case (**case 3** below). In practice, the node $p'_1$ may not exist, and then no split is needed (**case 2** below). To detect this case, we only need to check whether $\operatorname{longest}(q_1)=\operatorname{longest}(p_2)+c$, i.e., $\operatorname{len}(q_1)=\operatorname{len}(p_2)+1$. It is also possible that no node on the suffix path of $p_0$ has a transition by $c$; then we only need to create $q_0$ (**case 1** below).

Now that we have the idea of adding a new suffix path, let's go through the concrete steps of the incremental construction.

#### Process

To keep the space complexity linear, we store only the values of $\operatorname{len}$ and $\operatorname{link}$ and the list of transitions of each state. We do not mark terminal states (but we will show later how to assign these marks after the SAM is built).

At first, the SAM contains only one state $t_0$, numbered $0$ (the other states are numbered $1,2,\ldots$). For convenience, we set $\operatorname{len}(t_0)=0$ and $\operatorname{link}(t_0)=-1$ for state $t_0$ ($-1$ stands for a virtual state).

Now we only need to implement the process of adding one character $c$ to the current string. The algorithm goes as follows:

???+ note "Incremental SAM construction"
    -   Let $\textit{last}$ be the state corresponding to the whole string before adding character $c$ (initially $\textit{last}=0$; the last step of the algorithm updates $\textit{last}$).
    -   Create a new state $\textit{cur}$ and set $\operatorname{len}(\textit{cur})$ to $\operatorname{len}(\textit{last})+1$. At this point the value of $\operatorname{link}(\textit{cur})$ is not yet known.
    -   Now do the following: start from state $\textit{last}$. If the current state has no transition labeled $c$, add a transition by $c$ to state $\textit{cur}$, and move the current state along its suffix link. If at some point we reach a state that already has a transition by $c$, stop and call this state $p$.
    -   **Case 1**: if no such state $p$ is found, we have reached the virtual state $-1$. Set $\operatorname{link}(\textit{cur})$ to $0$ and go to the last step.
    -   Suppose we have found a state $p$ that has a transition by $c$. Call the target state $q$. Now either $\operatorname{len}(p)+1=\operatorname{len}(q)$ or $\operatorname{len}(p)+1<\operatorname{len}(q)$.
    -   **Case 2**: if $\operatorname{len}(p)+1=\operatorname{len}(q)$, just set $\operatorname{link}(\textit{cur})$ to $q$ and go to the last step.
    -   **Case 3**: otherwise things are a bit more complex, and we need to **clone** state $q$: create a new state $\textit{clone}$ and copy all the information of $q$ except $\operatorname{len}$ (the suffix link and the transitions). Set $\operatorname{len}(\textit{clone})$ to $\operatorname{len}(p)+1$.
    
        After cloning, point the suffix link of $\textit{cur}$ to $\textit{clone}$, and also point the suffix link of $q$ to $\textit{clone}$.
    
        Finally, walk back from state $p$ along suffix links. As long as the state we pass has a transition to state $q$, redirect that transition to state $\textit{clone}$.
    -   After handling any of the three cases above, update $\textit{last}$ to state $\textit{cur}$.

If we also want to know which states are **terminal** and which are not, we can find all terminal states after building the complete SAM of $s$. To do this, start from the state of the whole string (stored in the variable $\textit{last}$) and follow its suffix links until reaching the initial state. Mark every state visited as terminal. It is easy to see that this marks exactly all suffixes of $s$, and these states are the terminal states.

Since we create only one or two new states for each character of $s$, the SAM has only a **linear number** of states. That the SAM has only a linear number of transitions, and that the whole algorithm runs in linear time, have not been explained yet; we will show them later.

#### Explanation

We now explain each step of the algorithm in detail and show that it is **correct**.

???+ note "Detailed explanation of the algorithm"
    -   A transition $(p,q)$ is called **continuous** if $\operatorname{len}(p)+1=\operatorname{len}(q)$. Otherwise, i.e., when $\operatorname{len}(p)+1<\operatorname{len}(q)$, the transition is called **non-continuous**.
    
        As the algorithm description shows, continuous and non-continuous transitions are handled differently. Continuous transitions are fixed and will never change again. In contrast, when a new character is inserted into the string, non-continuous transitions may change (the endpoint of the transition edge may change).
    -   To avoid ambiguity, we write $s$ for the string before inserting the current character $c$ into the SAM.
    -   The algorithm begins by creating a new state $\textit{cur}$, which corresponds to the whole string $s+c$. The reason for creating a new node is clear. At the same time, we also create a new equivalence class.
    -   After creating the new state, we move along suffix links from the state $\textit{last}$, which corresponds to the whole string $s$. For each state we pass, we try to add a transition by character $c$ to the new state $\textit{cur}$.
    
        However, we can only add transitions that do not conflict with existing ones. So as soon as we find an existing transition by $c$, we must stop.
    -   The simplest case is reaching the virtual state $-1$. This means we have added transitions by $c$ for all suffixes of $s$. It also means the character $c$ has never appeared in $s$ before. So the suffix link of $\textit{cur}$ is state $0$.
    -   Otherwise (cases 2 and 3), we have found an existing transition $(p,q)$. This means we are trying to add a string $x+c$ that **already exists** in the automaton (where $x=\operatorname{longest}(p)$ is a suffix of $s$, and $x+c$ has already appeared as a substring of $s$). Since we assume the automaton of $s$ is built correctly, we should not add a new transition here.
    
        The difficulty, however, is: which state should the suffix link from $\textit{cur}$ point to? We need to point it to a state whose longest string is exactly $x+c$, i.e., whose $\operatorname{len}$ is $\operatorname{len}(p)+1$. But such a state may not exist, i.e., $\operatorname{len}(q)>\operatorname{len}(p)+1$. In this case, we must create such a state by splitting state $q$.
    -   Of course, if the transition $(p,\,q)$ is continuous, then $\operatorname{len}(q)=\operatorname{len}(p)+1$. In this case everything is simple: we just point the suffix link of $\textit{cur}$ to state $q$.
    -   Otherwise the transition is non-continuous, i.e., $\operatorname{len}(q)>\operatorname{len}(p)+1$. This means state $q$ corresponds not only to the suffix $x+c$ of length $\operatorname{len}(p)+1$, but also to longer substrings of $s$. We have no choice but to split state $q$ into two sub-states, so that the first one has length $\operatorname{len}(p)+1$.
    
        How do we split a state? We **clone** state $q$ to get a state $\textit{clone}$, and set $\operatorname{len}(\textit{clone})$ to $\operatorname{len}(p)+1$. Since we don't want to change the paths through $q$, we copy all transitions of $q$ to $\textit{clone}$. We also set the suffix link of $\textit{clone}$ to the target of $q$'s suffix link, and set the suffix link of $q$ to $\textit{clone}$.
    
        After splitting the state, we set the suffix link from $\textit{cur}$ to $\textit{clone}$.
    
        In the last step, we redirect some transitions that pointed to $q$ so that they point to $\textit{clone}$. Which transitions do we need to change? It is enough to redirect the transitions corresponding to all suffixes of the string $x+c$ (where $x=\operatorname{longest}(p)$). That is, we keep moving along suffix links from node $p$ until we reach the virtual state $-1$, or until the current state's transition by $c$ no longer points to state $q$.

### Linear time complexity

We assume the alphabet size is a **constant**, i.e., searching for a transition by a character, adding a transition, and finding the next transition each take $O(1)$ time. If we store the transitions of each node both as an array of length $\left|\Sigma\right|$ (for fast lookup of a transition by label) and as a dynamic list (for fast traversal of all existing transitions), trading space for time, then the algorithm runs in $O(n)$ time[^time-complexity] and $O(n\left|\Sigma\right|)$ space.

??? note "Proof"
    Looking at the parts of the algorithm, there are three places where it is not obvious that the time is linear:
    
    -   The first is walking along the suffix links from state $\textit{last}$ and adding transitions by $c$.
    -   The second is copying the transitions when state $q$ is cloned into a new state $\textit{clone}$.
    -   The third is changing the transitions that point to $q$ so that they point to $\textit{clone}$.
    
    We use the fact that the size of the SAM (the number of states and transitions) is **linear** (the proof for the number of states is the algorithm itself; the proof for the number of transitions will be given after we implement the algorithm).
    
    So the total cost of the **first and second** parts above is clearly linear, since each operation adds, amortized, only one new transition to the automaton.
    
    It remains to bound the total cost of the **third** part, where we redirect transitions that originally pointed to $q$ to $\textit{clone}$. Let $v=\operatorname{longest}(p)$, which is a suffix of $s$. With each iteration, the length of $v$ decreases, so the starting position of $v$ as a suffix of $s$ must move to the right. Therefore, the number of times $p$ moves along a suffix link in the loop is at most the distance the starting position of $v$ as a suffix of $s$ moves to the right. Since $p$ must move at least once to end the loop, and $p$ is at least the result of moving $\textit{last}$ once along its suffix link, when the loop ends the starting position of $v$ as a suffix of $s$ is no further left than that of the string $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$. Also, when the loop ends, the starting position of $v$ as a suffix of $s$ is exactly the starting position of $v+c$ as a suffix of $s+c$, and as a suffix of $s+c$, the string $v+c$ is exactly $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{cur})))$. Since $\textit{cur}$ is the updated value of $\textit{last}$, the number of moves in the loop is at most the distance that the starting position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$, as a suffix of the current string, moves to the right before and after the update, plus one (the move needed to end the loop).
    
    Since the position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ as a suffix of the current string is monotonically increasing during the whole SAM construction[^monotone-loc], its total movement is at most $n$. This shows that the loop that changes the transitions pointing to $q$ runs at most $2n$ iterations in total, which is exactly what we needed to prove.

Of course, if the alphabet size is not a constant and we don't want to pay $O(n\left|\Sigma\right|)$ space, the SAM's time complexity is not linear. The transitions out of a node then need to be stored in a balanced tree that supports fast lookup and insertion. So if $\Sigma$ is the alphabet and $\left|\Sigma\right|$ its size, the asymptotic time complexity of the algorithm is $O(n\log\left|\Sigma\right|)$ and the space complexity is $O(n)$.

### Implementation

First, we implement a data structure that stores all the information about the transitions of a state. If needed, you can add a terminal mark or other information here. We use a `map` to store the list of transitions, which lets us process the whole string with $O(n)$ total space and $O(n\log\left|\Sigma\right|)$ time. Of course, when the alphabet size $\left|\Sigma\right|=K$ is a small constant (such as 26), it is more convenient to declare `next` as `int[K]`.

```cpp
struct state {
  int len, link;
  std::map<char, int> next;
};
```

The SAM itself is stored in an array of `state` structs. We keep the current size of the automaton `sz` and the variable `last`, the state corresponding to the whole current string.

```cpp
constexpr int MAXLEN = 100000;
state st[MAXLEN * 2];
int sz, last;
```

We define a function to initialize the SAM (create a SAM with only the initial state).

```cpp
void sam_init() {
  for (int i = 0; i < sz; i++) st[i].next.clear();
  st[0].len = 0;
  st[0].link = -1;
  sz = 1;
  last = 0;
}
```

Finally, here is the main function: it appends one character to the current string and updates the automaton built so far accordingly.

???+ note "Implementation"
    ```cpp
    void sam_extend(char c) {
      int cur = sz++;
      st[cur].len = st[last].len + 1;
      int p = last;
      while (p != -1 && !st[p].next.count(c)) {
        st[p].next[c] = cur;
        p = st[p].link;
      }
      if (p == -1) {
        st[cur].link = 0;
      } else {
        int q = st[p].next[c];
        if (st[p].len + 1 == st[q].len) {
          st[cur].link = q;
        } else {
          int clone = sz++;
          st[clone].len = st[p].len + 1;
          st[clone].next = st[q].next;
          st[clone].link = st[q].link;
          while (p != -1 && st[p].next[c] == q) {
            st[p].next[c] = clone;
            p = st[p].link;
          }
          st[q].link = st[cur].link = clone;
        }
      }
      last = cur;
    }
    ```

As mentioned before, if you trade memory for time (space complexity $O(n\left|\Sigma\right|)$, where $\left|\Sigma\right|$ is the alphabet size), you can build a SAM for any alphabet size in $O(n)$ time[^time-complexity]. But then you need to store, for each state, an array of size $\left|\Sigma\right|$ (to quickly find the transition for a character) and a list of all existing transitions (to quickly traverse them).

## More properties

### Number of states

For a string $s$ of length $n$, the number of states in its SAM is **at most**  $2n-1$ (assuming $n\ge 2$).

??? note "Proof"
    The algorithm itself proves this. At the start, the automaton has one state; the first and second iterations each create only one node, and each of the remaining $n-2$ steps creates at most $2$ states.
    
    But we can also **prove** this bound **without using the algorithm**. If $s$ consists of a single repeated character, the number of states is $n+1$ and the claim is obvious; so assume $s$ has at least two distinct characters. Recall that the number of states equals the number of distinct $\operatorname{endpos}$ sets. These $\operatorname{endpos}$ sets form a tree (a parent's $\operatorname{endpos}$ set contains its children's). Let's modify this tree slightly: whenever it has an internal node with only one child (which means the child's set misses at least one position of its parent's set), we create a set containing these missing positions as another child. In the end we get a tree in which every internal node has more than one child, and there are at most $n$ leaves. Such a tree has at most $2n-1$ nodes, so the original number of distinct $\operatorname{endpos}$ sets is also at most $2n-1$.
    
    The string $\texttt{abbb} \cdots \texttt{bbb}$ reaches this bound: from the third iteration on, the algorithm splits one state in every iteration, ending with exactly $2n-1$ states.

### Number of transitions

For a string $s$ of length $n$, the number of transitions in its SAM is **at most**  $3n-4$ (assuming $n\ge 3$).

??? note "Proof"
    First we bound the number of continuous transitions. Consider the spanning tree of the automaton made of the longest paths from state $t_0$ to every state. This spanning tree contains only continuous edges, so there are fewer of them than states, i.e., at most $2n-2$ edges.
    
    Now we bound the number of non-continuous transitions. Let $(p,\,q)$ be a non-continuous transition with character $c$. Take its corresponding string $u+c+w$, where $u$ corresponds to the longest path from the initial state to $p$, and $w$ corresponds to the longest path from $q$ to any terminal state. On one hand, the strings $u+c+w$ for different non-continuous transitions are all different (since $u$ consists only of continuous transitions, the first non-continuous transition along $u+c+w$ is exactly $(p,\,q)$). On the other hand, by the definition of terminal states, every string of the form $u+c+w$ is a suffix of the whole string $s$. Since $s$ has only $n$ non-empty suffixes, and no string of the form $u+c+w$ equals $s$ (because the path of $s$ contains only continuous transitions), the total number of non-continuous transitions is at most $n-1$.
    
    Adding these two bounds gives an upper bound of $3n-3$. However, the maximum number of states only occurs in cases like $\texttt{abbb} \cdots \texttt{bbb}$, and there the number of transitions is clearly less than $3n-3$.
    
    So we get a tighter upper bound on the number of transitions of a SAM: $3n-4$. The string $\texttt{abbb} \cdots \texttt{bbbc}$ reaches this bound.

### Suffix link tree

Although we build a SAM to get its states and transitions, the suffix links $\operatorname{link}$ and the lengths $\operatorname{len}$ of the longest substrings recorded during construction are often more important in applications than the SAM's transitions, and can even be used on their own without the transitions.

While building the SAM, we keep updating the state $\textit{last}$. It corresponds to the string before (after) each added character, i.e., to every prefix of the whole string $s$. Let $v_i$ be the state of the $i$-th prefix; this gives $n$ states $v_0,v_1,\cdots,v_{n-1}$. Also, let the initial state $t_0$ be $v_{-1}$, corresponding to the empty prefix. For now we call these states "prefix nodes".

As mentioned in Lemma 4, all states and all suffix links form a tree rooted at $t_0$ with edges pointing toward the root. This tree is called the **suffix link tree** (Chinese OI contestants also often call it the **parent tree**). It records information about all suffixes of all prefixes of the string, i.e., about all substrings.

The suffix link tree has the following properties:

-   The string of an ancestor is always a suffix of the string of a descendant.
-   The $\operatorname{endpos}$ set of each node is exactly the set of indices $i$ of all "prefix nodes" $v_i$ in its subtree.
-   The $\operatorname{endpos}$ set of an ancestor in the suffix link tree always strictly contains the $\operatorname{endpos}$ set of a descendant.
-   The value of $\operatorname{len}$ at each node is exactly the length of the longest common suffix of the prefixes of all "prefix nodes" $v_i$ in its subtree.
-   Except for the root $t_0$, the number of distinct substrings of each node is its $\operatorname{len}$ value minus its parent's $\operatorname{len}$ value, i.e., $\operatorname{len}(v)-\operatorname{len}(\operatorname{link}(v))$.

These properties have many applications. For example, the longest common suffix of the $i$-th and $j$-th prefixes is the longest string of the LCA of $v_i$ and $v_j$.

Finally, the suffix link tree of a string $s$ has the same structure as the [suffix tree](./suffix-tree.md) of its reverse $s_R$. This is often used to build suffix trees offline.

## Applications

Let's now look at some problems that can be solved with a SAM. For simplicity, assume the alphabet size $|\Sigma|$ is a constant. This lets us treat adding a character and traversal as constant-time operations.

### Checking whether a string occurs

???+ example "Problem"
    Given a text $T$ and several patterns $P$, check whether each string $P$ occurs as a substring of $T$.

??? note "Solution"
    Build the suffix automaton of the text $T$ in $O(\left|T\right|)$ time. To check whether a pattern $P$ occurs in $T$, start from $t_0$ and follow the transitions (edges) given by the characters of $P$. If at some point there is no transition to follow, $P$ is not a substring of $T$. If we can process the whole string $P$ this way, then the pattern occurs in $T$.
    
    For each string $P$, the algorithm takes $O(\left|P\right|)$ time. In addition, it also finds the length of the longest prefix of $P$ that occurs in the text.

### Number of distinct substrings

???+ example "Problem"
    Given a string $S$, count its distinct substrings.

??? note "Solution 1"
    Build the suffix automaton of $S$.
    
    Each substring of $S$ corresponds to a path in the automaton. So the number of distinct substrings equals the number of distinct non-empty paths in the automaton starting at $t_0$.
    
    Since a SAM is a directed acyclic graph, the number of distinct paths can be computed with dynamic programming. Let $d_{v}$ be the number of paths starting at state $v$ (including the path of length zero). Then we have the recurrence:
    
    $$
    d_{v}=1+\sum_{w:(v,w,c)\in \text{SAM}}d_{w}
    $$
    
    That is, $d_{v}$ equals $1$ plus the sum of $d$ over the targets of all transitions of $v$, where $(v,w,c)\in \text{SAM}$ means the suffix automaton has a transition from $v$ to $w$ by $c$.
    
    So the number of distinct substrings is $d_{t_0}-1$ (subtracting the empty substring).
    
    The total time complexity is $O(\left|S\right|)$.

??? note "Solution 2"
    Another way is to use the suffix link tree after building the suffix automaton. The number of substrings of each node is $\operatorname{len}(v)-\operatorname{len}(\operatorname{link}(v))$; just sum this over all nodes except $t_0$.
    
    The total time complexity is still $O(\left|S\right|)$.

Example problems: [[Template] Suffix Automaton](https://www.luogu.com.cn/problem/P3804), [SDOI2016 Generating Spells](https://loj.ac/problem/2033)

### Total length of all distinct substrings

???+ example "Problem"
    Given a string $S$, compute the total length of all its distinct substrings.

??? note "Solution 1"
    This is similar to the previous problem, but now the DP has two parts: the number of distinct substrings $d_{v}$ and their total length $ans_{v}$.
    
    We already showed how to compute $d_{v}$ in the previous problem. The value of $ans_{v}$ can be computed with the following recurrence:
    
    $$
    ans_{v}=\sum_{w:(v,w,c)\in \text{SAM}}(d_{w}+ans_{w})
    $$
    
    We take the answer of each neighbor $w$ and add $d_{w}$ (since each substring starting from state $v$ gains one character).
    
    The time complexity of the algorithm is still $O(\left|S\right|)$.

??? note "Solution 2"
    We can also use the suffix link tree. The sum of the lengths of all suffixes of the longest substring of each node is
    
    $$
    \dfrac{\operatorname{len}(v)\times (\operatorname{len}(v)+1)}{2},
    $$
    
    and subtracting the same value for its $\operatorname{link}$ node gives the node's net contribution. Just sum this over all nodes except $t_0$.
    
    The total time complexity is still $O(\left|S\right|)$.

### The k-th smallest substring in lexicographic order

???+ example "Problem"
    Given a string $S$ and several queries. Each query gives a number $K_i$; find the $K_i$-th smallest substring in lexicographic order among all distinct substrings of $S$.

??? note "Solution"
    The idea grows out of the previous two problems. The $K_i$-th smallest substring in lexicographic order corresponds to the $K_i$-th smallest non-empty path in the SAM in lexicographic order. So after computing the number of paths from each state, we can easily find the $K_i$-th smallest path starting from the root of the SAM.
    
    Preprocessing takes $O(\left|S\right|)$ time, and each query takes $O(\left|ans\right|\cdot\left|\Sigma\right|)$ (where $ans$ is the answer to the query and $\left|\Sigma\right|$ is the alphabet size).

??? info "Side note"
    Although this is a classic suffix automaton problem, since it involves lexicographic order, it is actually most convenient to solve with a suffix array.

Example problems: [SPOJ - SUBLEX](https://www.spoj.com/problems/SUBLEX/), [TJOI2015 String Theory](https://loj.ac/problem/2102)

### Minimum cyclic shift

???+ example "Problem"
    Given a string $S$, find its lexicographically smallest cyclic shift.

??? note "Solution"
    It is easy to see that the string $S+S$ contains all cyclic shifts of $S$ as substrings.
    
    So the problem reduces to finding the smallest path of length $\left|S\right|$ in the suffix automaton of $S+S$. This can be done in a straightforward way: start from the initial state and greedily follow the smallest character.
    
    The total time complexity is $O(\left|S\right|)$.

### Number of occurrences

???+ example "Problem"
    Given a text $T$ and several queries. Each query gives a pattern $P$; answer how many times $P$ occurs as a substring of $T$.

??? note "Solution 1"
    Using the suffix link tree, a DFS can precompute the size of the $\operatorname{endpos}$ set of every node.
    
    Every "prefix node" starts with a set size of $1$, and every other node starts with $0$. Then, going back up along the suffix links from the bottom, add the set sizes of all children to each parent (don't forget the parent's own initial value). The resulting value at each node is the size of its $\operatorname{endpos}$ set. The set sizes of different children can simply be added because each $v_i$ appears in only one subtree, so nothing is counted twice.
    
    To answer a query, find the node of the pattern $P$ in the automaton. If it exists, the answer is the size of that node's $\operatorname{endpos}$ set; otherwise the answer is $0$.
    
    Preprocessing takes $O(|T|)$ time, and each query takes $O(|P|)$ time.

??? note "Solution 2"
    Build the suffix automaton of the text $T$.
    
    Next, preprocess: for each state $v$ of the automaton, compute $cnt_{v}$ equal to the size of the set $\operatorname{endpos}(v)$. In fact, all substrings of the same state $v$ occur the same number of times in $T$, which equals the number of positions in the set $\operatorname{endpos}$.
    
    However, we cannot build the sets $\operatorname{endpos}$ explicitly, so we only consider their sizes $cnt$.
    
    To compute these values, we do the following. For each state, if it was not created by cloning (and it is not the initial state $t_0$), initialize its $cnt$ to 1. Then go through all states in decreasing order of length $\operatorname{len}$, and add the current value $cnt_{v}$ to the state its suffix link points to, i.e.:
    
    $$
    cnt_{\operatorname{link}(v)}+=cnt_{v}
    $$
    
    After this, the answer for every state is correct.
    
    Why is this correct? There are exactly $\left|T\right|$ states not created by cloning (excluding $t_0$), and the first $i$ of them are created when we insert the first $i$ characters, each corresponding to one end position. So we initialize the $cnt$ of these states to $1$ and the $cnt$ of all other states to $0$.
    
    Then for each $v$ we do: $cnt_{\operatorname{link}(v)}+=cnt_{v}$. The meaning behind this is that if the strings of state $v$ occur $cnt_{v}$ times, then all their suffixes end at exactly the same places, so they also occur $cnt_{v}$ times.
    
    Why don't we count anything twice in this process (i.e., count some position twice)? Because we add the positions of a state to only **one** other state, so a state cannot pass its positions to another state twice through two different routes.
    
    So we can compute $cnt$ for all states in $O(\left|T\right|)$ time.
    
    Finally, to answer a query we just look up $cnt_{t}$, where $t$ is the state of the pattern; if the pattern does not exist, the answer is $0$. Each query takes $O(\left|P\right|)$ time.

### Position of the first occurrence

???+ example "Problem"
    Given a text $T$ and several queries. Each query asks for the position of the first occurrence of a string $P$ in $T$ (the starting position of $P$).

??? note "Solution 1"
    Using the suffix link tree, a DFS can precompute the minimum of the $\operatorname{endpos}$ set of every node.
    
    Every "prefix node" $v_i$ starts with the value $i$, and every other node starts with $\infty$. Then, going back up along the suffix links from the bottom, each parent takes the minimum of its own value and the values of all its children (don't forget the parent's own initial value). The resulting value at each node is the minimum of its $\operatorname{endpos}$ set.
    
    To answer a query, find the node of the pattern $P$ in the automaton. If it exists, the answer is that node's value minus $|P|-1$; otherwise there is no answer.
    
    Preprocessing takes $O(|T|)$ time, and each query takes $O(|P|)$ time.

??? note "Solution 2"
    Build a suffix automaton. We precompute the position $\operatorname{firstpos}$ for every state of the SAM. That is, for each state $v$ we want the position $\operatorname{firstpos}[v]$ where the first occurrence of this state ends. In other words, we want to find the smallest element of each set $\operatorname{endpos}$ in advance (clearly we cannot maintain all $\operatorname{endpos}$ sets explicitly).
    
    To maintain these positions $\operatorname{firstpos}$, we extend the function `sam_extend()`. When we create a new state $\textit{cur}$, we set:
    
    $$
    \operatorname{firstpos}(\textit{cur})=\operatorname{len}(\textit{cur})-1.
    $$
    
    When we clone node $q$ into $\textit{clone}$, we set:
    
    $$
    \operatorname{firstpos}(\textit{clone})=\operatorname{firstpos}(q).
    $$
    
    (because the only other option, $\operatorname{firstpos}(\textit{cur})$, is clearly too large).
    
    Then the answer to a query is $\operatorname{firstpos}(t)-\left|P\right|+1$, where $t$ is the state of the string $P$. Each query takes only $O(\left|P\right|)$ time.

### All occurrence positions

???+ example "Problem"
    Same as above, but this time we need to find all positions where the pattern $P$ occurs in the text $T$.

??? note "Solution 1"
    After finding the node of the pattern $P$, use the suffix link tree: traverse its subtree and output every "prefix node" found.
    
    Each query takes $O(|P|)+O(\textit{answer}(P))$, where $\textit{answer}(P)$ is the number of answers to this query. Following the [proof that the number of states is linear](#number-of-states), we can show that the size of a subtree of the suffix link tree is at most twice the size of the node's $\operatorname{endpos}$ set, so traversing the subtree takes $O(\textit{answer}(P))$.

??? note "Solution 2"
    Again we build the suffix automaton of the text $T$. As in the previous problem, we compute the position $\operatorname{firstpos}$ for every state.
    
    If $t$ is the state of the pattern $P$, then clearly $\operatorname{firstpos}(t)$ is one of the answers. We have found the state of $P$ in the automaton. What other positions do we need? Exactly those of the states whose strings have $P$ as a suffix. In other words, we need to find all states from which state $t$ can be reached via suffix links.
    
    So to solve this problem, for each state we store a list of the suffix links pointing to it. The answer to a query consists of the $\operatorname{firstpos}$ values of all states we can find from state $t$ by a DFS or BFS using only reversed suffix links.
    
    Preprocessing takes $O(|T|)$, and each query takes $O(|P|+\textit{answer}(P))$.
    
    We never visit a state twice (each state has only one suffix link, so there cannot be two different paths to the same state).
    
    We only need to consider two different states that may have the same $\operatorname{firstpos}$ value. This happens only when one state was cloned from the other. However, this does not affect the complexity analysis. Following the [proof that the number of states is linear](#number-of-states), the number of such states with suffix $P$ is at most $2\textit{answer}(P)$.
    
    In addition, we can remove duplicate positions by ignoring the $\operatorname{firstpos}$ values of cloned nodes. In fact, each occurrence position in the subtree of $t$ corresponds to exactly one non-cloned state. So if we keep a flag `is_clone` for each state indicating whether it was cloned, we can simply skip the cloned states and output the $\operatorname{firstpos}$ values of all the other states.
    
    Here is a rough implementation:
    
    ```cpp
    struct state {
      bool is_clone;
      int first_pos;
      std::vector<int> inv_link;
      // some other variables
    };
    
    // after building the SAM
    for (int v = 1; v < sz; v++) st[st[v].link].inv_link.push_back(v);
    
    // output all occurrence positions
    void output_all_occurrences(int v, int P_length) {
      if (!st[v].is_clone) cout << st[v].first_pos - P_length + 1 << endl;
      for (int u : st[v].inv_link) output_all_occurrences(u, P_length);
    }
    ```

### Shortest string that does not occur

???+ example "Problem"
    Given a string $S$ and a fixed alphabet, find a shortest string that does not occur in $S$.

??? note "Solution"
    We do dynamic programming on the suffix automaton of $S$.
    
    Suppose we have already processed part of the substring and are now at state $v$. We want the minimum number of characters we need to add to hit a missing transition; call this number $d_v$ for node $v$.
    
    Computing $d_{v}$ is very simple. If at least one character of the alphabet has no transition from $v$, then $d_{v}=1$. Otherwise adding one character is not enough, and we take the minimum over all transitions:
    
    $$
    d_{v}=1+\min_{w:(v,w,c)\in \text{SAM}}d_{w}
    $$
    
    The answer is $d_{t_0}$, and the string itself can be recovered by tracing back through the computed array $d$.

### Longest common substring of two strings

???+ example "Problem"
    Given two strings $S$ and $T$, find their longest common substring. A common substring is a string $X$ that occurs as a substring in both $S$ and $T$.

??? note "Solution"
    Build the suffix automaton of $S$.
    
    Now we process $T$. For each prefix of $T$, we look for the longest suffix of that prefix that occurs in $S$. In other words, for each position in $T$, we want the length of the longest common substring of $S$ and $T$ ending at that position.
    
    To do this, we use two variables: the **current state**  $v$ and the **current length**  $l$. These two variables describe the currently matched part: its length and its state.
    
    Initially $v=t_0$ and $l=0$, i.e., the match is the empty string.
    
    Now let's describe how to add a character $T_{i}$ and recompute the answer for it:
    
    -   If there is a transition from $v$ by the character $T_{i}$, we just follow it and increase $l$ by one.
    -   If there is no such transition, we need to shorten the currently matched part, which means following the suffix link:
    
        $$
        v=\operatorname{link}(v)
        $$
    
        At the same time, we need to shorten the current length. Clearly we should set $l$ to $\operatorname{len}(v)$, because the longest string of the state we reach after following this suffix link is a substring.
    -   If there is still no transition by this character, we keep following suffix links and decreasing $l$ until we find a transition, or reach the initial state $t_0$ and it has no such transition either (which means the character $T_{i}$ never occurs in $S$; then $v=l=0$).
    
    Clearly, the answer to the problem is the maximum of all values of $l$.
    
    This part takes $O(\left|T\right|)$ time, because in each move we either increase $l$ by one, or move along suffix links several times, each time decreasing $l$.
    
    Implementation:
    
    ```cpp
    string lcs(const string &S, const string &T) {
      sam_init();
      for (int i = 0; i < S.size(); i++) sam_extend(S[i]);
    
      int v = 0, l = 0, best = 0, bestpos = 0;
      for (int i = 0; i < T.size(); i++) {
        while (v && !st[v].next.count(T[i])) {
          v = st[v].link;
          l = st[v].len;
        }
        if (st[v].next.count(T[i])) {
          v = st[v].next[T[i]];
          l++;
        }
        if (l > best) {
          best = l;
          bestpos = i;
        }
      }
      if (best == 0) return "";
      return T.substr(bestpos - best + 1, best);
    }
    ```

Example problem: [SPOJ Longest Common Substring](https://www.spoj.com/problems/LCS/en/)

### Longest common substring of several strings

???+ example "Problem"
    Given $k$ strings $S_i$, find their longest common substring, i.e., a string $X$ that occurs as a substring in every string.

??? note "Solution 1"
    Concatenate all the strings into one longer string $T$, separating them with special characters $D_i$ (one character per string):
    
    $$
    T=S_1+D_1+S_2+D_2+\cdots+S_k+D_k.
    $$
    
    Then build the suffix automaton of $T$.
    
    Now we need to find in the automaton a string that occurs in every string $S_i$, and the added special characters help with this. If $S_j$ contains a substring $X$, then from the node $t$ of the substring $X$ there must be a path that reaches $D_j$ without passing through any other special character $D_1,\cdots,D_{j-1},D_{j+1},\cdots,D_k$. For a common substring $X$, such a path must exist for every special character $D_j$.
    
    So we need to compute reachability: for each state of the automaton and each character $D_i$, whether such a path exists. This is easy to compute with DFS or BFS plus dynamic programming. After that, the answer is the longest among the strings $\operatorname{longest}(v)$ of all states $v$ that can reach every special character.

??? note "Solution 2"
    Let $S_1$ be the **shortest** string, and build its SAM. Use the algorithm for the longest common substring of two strings to compute the longest common substring length of $S_1$ with each of the other strings. During matching, each time we add a character of the string $S_j$ being matched, we move on the SAM accordingly, so we can directly record, for each state of the SAM, the length of the longest substring of $S_j$ that it matches **during the matching process**.
    
    During matching, whenever we reach a state of the SAM, we have also matched all of its ancestors in the suffix link tree, but the match lengths of those ancestors have not been updated. So after finishing the matching of $S_j$, we need to update from the bottom up along the suffix links, passing the longest match of each child up to its parent. Note that the longest match length recorded at a parent cannot exceed its own $\operatorname{len}$ value. This gives, for each state of the SAM of $S_1$, the length of the longest substring of $S_j$ it **can actually match**.
    
    Finally, match each of $S_2,\cdots,S_k$ once, and for each state of the SAM take the minimum of the actually matched lengths. This gives, for each state of the SAM, the length of the longest common substring of $S_2,\cdots,S_k$ it can actually match. Then go over all states of the SAM; the maximum is the length of the longest common substring of these $k$ strings.
    
    The time complexity of the algorithm is $O(\sum_i |S_i|)$. Although the SAM of $S_1$ is traversed $k$ times, since $|S_1|$ is the smallest, $k|S_1|\le \sum_i |S_i|$, and the dominant term is still the matching process going through all strings.

Example problem: [SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)

## Exercises

-   [[Template] Suffix Automaton](https://www.luogu.com.cn/problem/P3804)
-   [SDOI2016 Generating Spells](https://loj.ac/problem/2033)
-   [SPOJ - SUBLEX](https://www.spoj.com/problems/SUBLEX/)
-   [TJOI2015 String Theory](https://loj.ac/problem/2102)
-   [SPOJ Longest Common Substring](https://www.spoj.com/problems/LCS/en/)
-   [SPOJ Longest Common Substring II](https://www.spoj.com/problems/LCS2/)
-   [Codeforces 1037H Security](https://codeforces.com/problemset/problem/1037/H)
-   [Codeforces 666E Forensic Examination](https://codeforces.com/problemset/problem/666/E)
-   [HDU4416 Good Article Good sentence](https://acm.hdu.edu.cn/showproblem.php?pid=4416)
-   [HDU4436 str2int](https://acm.hdu.edu.cn/showproblem.php?pid=4436)
-   [HDU6583 Typewriter](https://acm.hdu.edu.cn/showproblem.php?pid=6583)
-   [Codeforces 235C Cyclical Quest](https://codeforces.com/problemset/problem/235/C)
-   [CTSC2012 Familiar Articles](https://www.luogu.com.cn/problem/P4022)
-   [NOI2018 Your Name](https://uoj.ac/problem/395)

## Further reading

First, here are some of the earliest papers related to the SAM:

-   A. Blumer, J. Blumer, A. Ehrenfeucht, D. Haussler, R. McConnell. Linear Size Finite Automata for the Set of All Subwords of a Word. An Outline of Results. \[1983]
-   A. Blumer, J. Blumer, A. Ehrenfeucht, D. Haussler. The Smallest Automaton Recognizing the Subwords of a Text. \[1984]
-   Maxime Crochemore. Optimal Factor Transducers. \[1985]
-   Maxime Crochemore. Transducers and Repetitions. \[1986]
-   A. Nerode. Linear automaton transformations. \[1958]

This topic can also be found in some more recent resources and in many books on string algorithms:

-   Maxime Crochemore, Wojciech Rytter. Jewels of Stringology. \[2002]
-   Bill Smyth. Computing Patterns in Strings. \[2003]
-   Bill Smyth. Методы и алгоритмы вычислений на строках (Russian translation of the previous book). \[2006]

There are also some other materials:

-   "Suffix Automaton", Chen Lijie.
-   "Extending the Suffix Automaton to Tries", Liu Yanyi.
-   "The Suffix Automaton and Its Applications", Zhang Tianyang.
-   <https://www.cnblogs.com/zinthos/p/3899679.html>
-   <https://codeforces.com/blog/entry/20861>
-   <https://zhuanlan.zhihu.com/p/25948077>

**This page is mainly translated from the blog post [Суффиксный автомат](http://e-maxx.ru/algo/suffix_automata) and its English translation [Suffix Automaton](https://cp-algorithms.com/string/suffix-automaton.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**

[^state-endpos]: The reason each state must be exactly one $\operatorname{endpos}$ equivalence class is really the Myhill–Nerode theorem mentioned in the next paragraph. In short, if two strings $t$ and $u$ have different $\operatorname{endpos}$ sets, they cannot correspond to the same state of the SAM: the paths from the same state to terminal states are always the same, which means the ways to append characters to $t$ and $u$ to reach the end of $s$ are also the same, and this says exactly that $t$ and $u$ have the same end positions in $s$. Conversely, whenever two strings $t$ and $u$ have the same $\operatorname{endpos}$ set, they can be mapped to the same state of the SAM. Why this works is the content of the proof of the Myhill–Nerode theorem, which we won't go into here. But the discussion here at least convinces us that putting strings with the same $\operatorname{endpos}$ set into the same state gives a SAM that is minimal, since no further merging of nodes is possible.

[^time-complexity]: If we don't use an extra list to record the existing transitions of each state, and instead store all possible transitions (whether they exist or not) in an array and copy the whole array when cloning a node, then the time complexity is also $O(n\left|\Sigma\right|)$.

[^monotone-loc]: What the main text does not explain is whether the position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ is also monotonically (weakly) increasing in cases 1 and 2. Case 1 is easy to check: after the update, $\operatorname{link}(\textit{last})=t_0$, and $\operatorname{link}(\operatorname{link}(\textit{last}))$ is the virtual state $-1$; we can regard its string as the empty string at the end of the current string, whose position takes the maximum value. In case 2, the transition is continuous, which means $\operatorname{longest}(q) = \operatorname{longest}(p)+c$. However, appending a new character to a substring only makes it harder for it to appear in the string. That is, when the end-position set of the suffix of $\operatorname{longest}(p)$ of length $\operatorname{len}(\operatorname{link}(p))$ strictly contains $\operatorname{endpos}(p)$, the end-position set of the suffix of $\operatorname{longest}(q)$ of length $\operatorname{len}(\operatorname{link}(p))+1$ may still equal $\operatorname{endpos}(q)$. Therefore $\operatorname{len}(\operatorname{link}(q))\le\operatorname{len}(\operatorname{link}(p))+1$, i.e., the starting position of $\operatorname{longest}(\operatorname{link}(p))$ as a suffix of $s$ is never greater than the starting position of $\operatorname{longest}(\operatorname{link}(q))$ as a suffix of $s+c$. Also, when we first find a state $p$ with a transition by $c$, we must have moved at least once, which means the starting position of $\operatorname{longest}(\operatorname{link}(p))$ as a suffix of $s$ is no less than the starting position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ as a suffix of $s$. Finally, $\operatorname{longest}(\operatorname{link}(q))=\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{cur})))$. This shows that in case 2, the position of $\operatorname{longest}(\operatorname{link}(\operatorname{link}(\textit{last})))$ is also monotonically (weakly) increasing.
