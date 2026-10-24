This section introduces basic computability and complexity theory. It is of limited use in OI (but it does help a little: if you meet an NP-hard problem, you can assume it has no polynomial-time solution). You can read it out of interest, or as preparation for later study.

Many results in this article are stated without proof. If you are interested, you can look up the proofs yourself.

Prerequisites: [time complexity](../basic/complexity.md).

## Problems

### Languages

An **alphabet** is a non-empty finite set. The elements of this set are called **symbols** (characters).

Let $\Sigma^\ast$ be the set of strings formed by concatenating a non-negative number of symbols from $\Sigma$. A **language** over the alphabet $\Sigma$ is a subset of $\Sigma^\ast$.

Note that a "language" here is an abstract concept. Strings in the usual sense form languages, and the set of all directed acyclic graphs can also be a language (there is a bijection between 01 strings and directed graphs; you don't need to know the details).

Since any language can be converted into the form of 01 strings, below we assume $\Sigma=\{0, 1\}$ unless stated otherwise.

### Decision problems

A decision problem is a problem that can only be answered YES or NO. In essence it asks whether a string belongs to a language: $f:\Sigma^\ast\rightarrow\{0, 1\}, f(x)=1\iff x\in L$ is a decision problem over the alphabet $\Sigma$ and the language $L$. For example, "decide whether a graph is a directed acyclic graph" is a decision problem.

Because they are so simple, decision problems are often the objects studied in computability and complexity theory. In this article, "problem" means "decision problem" unless stated otherwise. Of course, some statements can easily be extended to other problems.

A language can also stand for the decision problem "decide whether a string belongs to this language". So "language" and "problem" can be treated as synonyms.

### Function problems

The answer to a function problem is not just YES/NO; it can be a number or something else. For example, "find the sum of two numbers" is a function problem.

Any function problem can be turned into a decision problem. For example, "find the sum of two numbers" can be turned into "decide whether the sum of two numbers equals a third number".

A decision problem can also be turned into a function problem: compute the indicator function of the decision problem, i.e. the $f$ in the definition of decision problems above.

## Turing machines

### Deterministic Turing machines

Unless stated otherwise, "Turing machine" usually means "deterministic Turing machine", and that is also the case in this article.

There are many different definitions of Turing machines. We pick one of them here; Turing machines under other definitions usually have the same computational power as this one.

A Turing machine is a machine that operates on a tape divided into cells and extending infinitely in both directions. It has an internal state and a head that can modify the tape and move along it.

Formally, a Turing machine is a 7-tuple $M=\langle Q,\Gamma,b,\Sigma,\delta,q_0,F\rangle$, where:

-   $Q$ is a finite non-empty **set of states**;
-   $\Gamma$ is a finite non-empty **tape alphabet**;
-   $b\in\Gamma$ is the **blank symbol**, the only symbol allowed to occur on the tape infinitely often during the computation;
-   $\Sigma\subseteq(\Gamma\setminus\{b\})$ is the **set of input symbols**, the symbols that may appear on the initial tape (i.e. the input);
-   $q_0\in Q$ is the **initial state**;
-   $F\subseteq Q$ is the set of **accepting states**. If a Turing machine halts in an accepting state, we say the contents of the initial tape are **accepted** by the machine.
-   $\delta :(Q\setminus F)\times \Gamma \not \to Q\times \Gamma \times \{L,R\}$ is a partial function (a function defined only on a subset of its domain) called the **transition function**. If $\delta$ is undefined for the current state, the Turing machine halts.

The Turing machine starts from the initial state at the start of the tape. At each step, it acts based on its current internal state $x$ and the symbol $y$ in the tape cell under the head: if $\delta(x, y)$ is undefined, it halts; otherwise, if $\delta(x, y)=(a, b, c)$, it changes its internal state to $a$, changes the symbol in the cell under the head to $b$, and moves one cell left if $c$ is $L$ or one cell right if $c$ is $R$.

Actually, you don't need to know the details of how a Turing machine works; an intuitive understanding is enough.

The output of Turing machine $M$ on input $x$ is written $M(x)$ ($M(x)=1$ if and only if $M$ accepts $x$, and $M(x)=0$ if and only if $M$ halts in a finite number of steps on input $x$ and does not accept $x$). The parentheses may also contain several arguments separated by commas; in practice you can add a symbol to the alphabet to act as the comma separating the arguments.

The time complexities of solving a problem on a Turing machine and on a von Neumann computer differ by at most a polynomial factor, so Turing machines can be used as the model of computation when studying complexity classes.

### Non-deterministic Turing machines

A non-deterministic Turing machine is a kind of Turing machine. It differs from a deterministic Turing machine as follows: at each step a deterministic Turing machine can move to only one state, while a non-deterministic Turing machine can move to several states "at the same time", computing in several "branches" in parallel. As soon as any one of these "branches" halts in an accepting state, the non-deterministic Turing machine accepts the input.

In fact, any deterministic Turing machine can simulate, in exponential time, what a non-deterministic Turing machine does in polynomial time, using something like iterative deepening search.

In real-world terms, a deterministic Turing machine is like a single-core processor that only supports serial processing, while a non-deterministic Turing machine is like an ideal multi-core processor that supports unlimited parallel processing.

### Multi-tape Turing machines

A standard Turing machine can only operate on one tape, but for convenience this article studies multi-tape Turing machines. In a $k$-tape Turing machine, one tape is a read-only input tape, the other $k-1$ tapes can be read and written, and one of these $k-1$ tapes is used for output.

A multi-tape Turing machine must have a finite number of tapes.

The space used by a multi-tape Turing machine is the number of cells its heads visit on the tapes other than the input tape.

### Encoding Turing machines

Turing machines can be encoded by natural numbers. That is, there is a surjective function $f:\mathbb{N}\to\mathbb{M}$ such that every natural number corresponds to a Turing machine, and every Turing machine has infinitely many encodings. So a set of Turing machines can be a language.

Write $M_{\alpha}$ for the Turing machine encoded by the natural number $\alpha$.

### Universal Turing machine

There exists a Turing machine $\mathcal U$ such that:

1.  If $M_{\alpha}$ halts in finite time on input $x$, then $\mathcal{U}(x, \alpha)=M_{\alpha}(x)$; otherwise $\mathcal{U}(x, \alpha)$ does not halt in finite time;
2.  If for every $x\in\{0, 1\}^\ast$, $M_\alpha$ halts within $T(|x|)$ time on input $x$, then for every $x\in\{0, 1\}^\ast$, $\mathcal{U}(x, \alpha)$ halts within $O(T(|x|)\log T(|x|))$ time.

In other words, there is a universal Turing machine that can simulate any Turing machine, and it is slower than the simulated machine only by a logarithmic factor of its running time.

## Computability

### Uncomputable problems

For a decision problem, if there is a Turing machine that always halts in a finite number of steps and decides the problem correctly, the problem is **Turing-computable**. Otherwise it is **Turing-uncomputable**.

Since Turing machines can be encoded by natural numbers, there are countably infinitely many Turing machines. But there are uncountably infinitely many languages (sets of binary strings), and each Turing machine decides at most one language. So Turing-uncomputable problems must exist.

### The halting problem

The halting problem is a classic Turing-uncomputable problem: given $\alpha$ and $x$, decide whether $M_{\alpha}$ halts in a finite number of steps on input $x$.

??? note "Proof that the halting problem is Turing-uncomputable"
    Define the function $\mathsf{UC}:\{0,1\}^\ast\to\{0,1\}$ as:
    
    $$
    \mathsf{UC}(\alpha)=\begin{cases}0&M_\alpha(\alpha)=1\\1&\text{otherwise}\end{cases}
    $$
    
    We first prove that $\mathsf{UC}$ is Turing-uncomputable:
    
    Suppose there is a Turing machine $M_{\beta}$ that computes $\mathsf{UC}$. By the definition of $\mathsf{UC}$, $\mathsf{UC}(\beta)=1\iff M_\beta(\beta)\neq 1$. But since $M_{\beta}$ computes $\mathsf{UC}$, $M_{\beta}(\beta)=\mathsf{UC}(\beta)$. This is a contradiction, so the assumption is false: no Turing machine can compute $\mathsf{UC}$.
    
    Let $M_{\mathsf{HALT}}$ be a Turing machine that solves the halting problem, where $M_{\mathsf{HALT}}(x,\alpha)$ is the answer to whether $M_\alpha$ halts in a finite number of steps on input $x$. Then we can build a Turing machine $M_{\mathsf{UC}}$ that computes $\mathsf{UC}$:
    
    $M_\mathsf{UC}$ first calls $M_\mathsf{HALT}(α,α)$. If it outputs $0$, then $M_\mathsf{UC}(α)=1$. Otherwise, $M_\mathsf{UC}$ simulates the computation with the universal Turing machine to get the answer.
    
    Since $\mathsf{UC}$ is Turing-uncomputable, $M_\mathsf{HALT}$ does not exist. In other words, the halting problem is Turing-uncomputable.

## The Church–Turing thesis

The Church–Turing thesis states that if a class of problems can be solved by an effective method, then this class of problems can be solved by some Turing machine.

Here, an "effective method" must satisfy:

1.  It consists of a finite number of clear instructions;
2.  When used to solve any one problem in the class, it must finish in a finite number of steps and give the correct answer.

This thesis has not been proved, but it is a basic axiom of the theory of computation.

## Complexity classes

There are many complexity classes. This article only introduces a small number of the more common ones.

### R and RE

For a language $L$ and a Turing machine $M$, if $M$ halts in a finite number of steps on every input and $M(x)=1\iff x\in L$, we say $M$ **decides** $L$.

For a language $L$ and a Turing machine $M$, if $M$ halts in a finite number of steps on every input that belongs to $L$, and $M(x)=1\iff x\in L$, we say $M$ **recognizes** $L$.

The complexity class $\mathsf R$ is the set of languages that can be decided by some Turing machine, i.e. all Turing-computable languages.

The complexity class $\mathsf{RE}$ is the set of languages that can be recognized by some Turing machine. $\mathsf{RE}$ is also called the class of recursively enumerable languages.

From the definitions, $\mathsf{R}\subseteq\mathsf{RE}$.

### DTIME

If there is a deterministic Turing machine that decides a language and halts within $O(f(|x|))$ time on every input $x$, then the language belongs to the class $\mathsf{DTIME}(f(n))$.

### P

The complexity class $\mathsf P$ is the set of decision problems that can be solved by a deterministic Turing machine in polynomial time, that is:

$$
\mathsf{P}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{DTIME}(n^k)
$$

Linear programming, computing the greatest common divisor, and the decision version of finding a maximum matching in a graph are all problems in $\mathsf P$.

### EXPTIME

The complexity class $\mathsf{EXPTIME}$ is the set of decision problems that can be solved by a deterministic Turing machine in exponential time, that is:

$$
\mathsf{EXPTIME}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{DTIME}(2^{n^k})
$$

A weakened version of the halting problem, "given the encoding of a Turing machine and a positive integer $k$, decide whether the machine halts within $k$ steps", is a problem in $\mathsf{EXPTIME}$. This is because solving it takes $O(k)$ time, while the number $k$ can be encoded as a binary string of length $O(\log k)$.

### NTIME

If there is a non-deterministic Turing machine that decides a language and halts within $O(f(|x|))$ time on every input $x$, then the language belongs to the class $\mathsf{NTIME}(f(n))$.

### NP

The complexity class $\mathsf{NP}$ is the set of decision problems that can be solved by a non-deterministic Turing machine in polynomial time, that is:

$$
\mathsf{NP}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{NTIME}(n^k)
$$

Every problem in $\mathsf P$ is in $\mathsf{NP}$. For more problems in $\mathsf{NP}$, see NPC problems and NP-intermediate problems below.

#### NP-hard

If every problem in $\mathsf{NP}$ can be reduced to a problem $H$ in polynomial time, then $H$ is NP-hard.

In other words, if an NP-hard problem $H$ could be solved in one unit of time, then every problem in $\mathsf{NP}$ could be solved in a polynomial number of time units.

#### NP-complete

If a problem is both in $\mathsf{NP}$ and NP-hard, it is NP-complete, also called an NPC problem.

Some classic NPC problems: the decision version of the traveling salesman problem, the decision version of the maximum independent set problem, the decision version of the minimum vertex cover problem, the decision version of the longest path problem, the decision version of 0-1 integer programming, the set cover problem, the graph coloring problem, the knapsack problem, the 3-dimensional matching problem, and the decision version of the maximum cut problem.

The function versions of NPC problems are often NP-hard. For example, "decide whether a graph contains a clique of size $k$" is both in $\mathsf{NP}$ and NP-hard, so it is NPC. Its function version, "find the maximum clique of a graph", is not NPC, but it is still NP-hard.

Similarly, other complexity classes also have "XX-complete" problems. For example, every problem in $\mathsf{EXPTIME}$ can be reduced in polynomial time to an EXPTIME-complete problem.

#### co-NP

A problem is in $\mathsf{co-NP}$ if and only if its complement is in $\mathsf{NP}$. If you think of a "problem" as a "language", and a "language" as a subset of $\Sigma^\ast$, the "complement" makes sense.

For example, "given $n$ subsets, decide whether you can choose $k$ of them that cover the whole set" is an NPC problem, and its complement, "given $n$ subsets, decide whether no choice of $k$ of them covers the whole set", is a problem in $\mathsf{co-NP}$. If the answer to the first problem is "yes", that gives a counterexample to the second problem, so the answer to the second problem is "no".

#### NP-intermediate

If a problem is in $\mathsf{NP}$ but is neither in $\mathsf{P}$ nor NPC, it is called NP-intermediate.

As far as we currently know, graph isomorphism, discrete logarithm and integer factorization may be NP-intermediate.

Ladner's theorem states that if $\mathsf{P}\ne\mathsf{NP}$, then NP-intermediate problems must exist.

### NEXPTIME

The complexity class $\mathsf{NEXPTIME}$ is the set of decision problems that can be solved by a non-deterministic Turing machine in exponential time, that is:

$$
\mathsf{NEXPTIME}=\bigcup\limits_{k\in\mathbb{N}}\mathsf{NTIME}(2^{n^k})
$$

### #P

Problems in $\mathsf{\#P}$ are not decision problems but counting problems related to $\mathsf{NP}$: counting the number of solutions of a problem in $\mathsf{NP}$ is a problem in $\mathsf{\#P}$. In other words, counting on how many branches a string is accepted by a non-deterministic Turing machine that always halts in polynomial time is a problem in $\mathsf{\#P}$.

Counting the matchings or perfect matchings of a general graph or a bipartite graph is #P-complete. The corresponding decision problem is "decide whether a graph has a (perfect) matching".

### DSPACE

If there is a deterministic Turing machine that decides a language within $O(f(|x|))$ space on input $x$, then the language belongs to the class $\mathsf{DSPACE}(f(n))$.

-   $\mathsf{REG}=\mathsf{DSPACE}(O(1))$, the regular languages, i.e. the languages that finite automata can decide.

-   $\mathsf{L}=\mathsf{DSPACE}(O(\log n))$. Note that the space used by a Turing machine does not include the space taken by the input.

-   $\mathsf{PSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{DSPACE}(n^k)$

-   $\mathsf{EXPSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{DSPACE}(2^{n^k})$

### NSPACE

If there is a non-deterministic Turing machine that decides a language within $O(f(|x|))$ space on input $x$, then the language belongs to the class $\mathsf{NSPACE}(f(n))$.

-   $\mathsf{REG}=\mathsf{DSPACE}(O(1))=\mathsf{NSPACE}(O(1))$

-   $\mathsf{NL}=\mathsf{NSPACE}(O(\log n))$

-   $\mathsf{CSL}=\mathsf{NSPACE}(O(n))$, the context-sensitive languages.

-   $\mathsf{PSPACE}=\mathsf{NPSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{NSPACE}(n^k)$

-   $\mathsf{EXPSPACE}=\mathsf{NEXPSPACE}=\bigcup\limits_{k\in\mathbb N}\mathsf{NSPACE}(2^{n^k})$

## Polynomial time

Simply put, if there is a positive number $k$ such that an algorithm's time complexity is $O(n^k)$ (note: not $\Theta(n^k)$), where $n$ is the problem size (the length of the input), the algorithm is said to run in **polynomial time**. If a problem can be solved by a polynomial-time algorithm (on a deterministic Turing machine), the problem belongs to the complexity class $\mathsf{P}$.

Polynomial time can be divided into strongly polynomial time and weakly polynomial time. There is also pseudo-polynomial time.

### Strongly polynomial time

First we define a model of computation called the arithmetic model. In the arithmetic model, arithmetic operations between numbers (addition, subtraction, multiplication, division, comparison) take unit time (i.e. $O(1)$ time, regardless of the size of the numbers).

An algorithm runs in **strongly polynomial time** if, in the arithmetic model, its number of operations is polynomial in the count of numbers in the input, and its space complexity is polynomial in the input size (not the count of numbers). Since arithmetic operations in a general model of computation can be done in time polynomial in the input size (i.e. the logarithm of the numbers' magnitude), a strongly polynomial-time algorithm is always polynomial-time.

Generally speaking, the time complexity of a strongly polynomial-time algorithm does not depend on the range of values.

### Weakly polynomial time

An algorithm that runs in polynomial time but not strongly polynomial time runs in **weakly polynomial time**.

For example, the Euclidean algorithm for the greatest common divisor runs in $O(\log a + \log b)$ time ($a$ and $b$ are the sizes of the input numbers), which is weakly polynomial time.

### Pseudo-polynomial time

An algorithm whose running time is polynomial in the range of values runs in **pseudo-polynomial time**. A pseudo-polynomial-time algorithm may or may not be polynomial-time. It may fail to be polynomial-time because representing a positive integer of size $n$ usually needs only $O(\log n)$ bits, so an algorithm that is polynomial in the range of values is often exponential in the input length. Although by definition a pseudo-polynomial-time algorithm may also be polynomial-time, when we say an algorithm runs in pseudo-polynomial time, we usually mean it is not polynomial-time.

For example, the knapsack problem is NP-hard, but it has a pseudo-polynomial-time solution based on dynamic programming.

If an NPC/NP-hard problem has a pseudo-polynomial-time solution, it is called **weakly NPC**/**weakly NP-hard**. If an NPC/NP-hard problem has no pseudo-polynomial-time solution assuming $\mathsf{P} \ne \mathsf{NP}$, it is called **strongly NPC**/**strongly NP-hard**.

## Constructible functions

### Time-constructible functions

Sometimes we want a Turing machine to know how much time it has used, for example to force it to halt after $T(n)$ steps of computation. But if computing $T(n)$ itself takes more than $T(n)$ time, this is impossible. To avoid this trouble, we define time-constructible functions.

If there is a Turing machine $M$ that, on input $1^n$ ($n$ ones), halts within $O(f(n))$ time and outputs the binary representation of $f(n)$ (note that the output here is not accept/reject but a string, which can be written on the tape), then $f(n)$ is a **time-constructible function**.

Since reading the input takes $O(n)$ time, no non-constant function that is $o(n)$ is time-constructible.

### Space-constructible functions

Space-constructible functions can be defined in a similar way.

If there is a Turing machine $M$ that, on input $1^n$ ($n$ ones), halts within $O(f(n))$ space and outputs the binary representation of $f(n)$, then $f(n)$ is a **space-constructible function**.

## Relationships between complexity classes

### Time hierarchy theorem

#### Deterministic time hierarchy theorem

If $f(n)$ is a time-constructible function, then:

$$
\mathsf {DTIME}\left(o\left({\frac {f(n)}{\log f(n)}}\right)\right)\subsetneq \mathsf {DTIME}(f(n))
$$

The deterministic time hierarchy theorem gives $\mathsf{P}\subsetneq\mathsf{EXPTIME}$.

??? note "Proof of the deterministic time hierarchy theorem"
    Define the language $L=\{(x, y)|\mathcal{U}((x, y), x)\text{ halts and rejects within }f(|x|+|y|)\text{ time}\}$. Since $f(n)$ is time-constructible, we can decide $L$ by computing according to the definition, in $O(f(|x|+|y|))$ time, so $L\in\mathsf{DTIME}(f(n))$.
    
    Now suppose $L\in\mathsf{DTIME}(o\left({\dfrac {f(n)}{\log f(n)}}\right))$, and let $M_z$ be the Turing machine that decides $L$ in $o\left({\dfrac {f(n)}{\log f(n)}}\right)$ time.
    
    Let the running time of the universal Turing machine $\mathcal{U}(x, z)$ in terms of $x$ be $g(|x|)$. From the discussion of the universal Turing machine above, $g(n)=o(f(n))$. So when $y$ is large enough, $g(|z|+|y|)<f(|z|+|y|)$.
    
    Let $y'$ be a large enough $y$. Then $\mathcal{U}((z, y'), z)$ must halt within $f(|z|+|y'|)$ time, so $M_z(z, y')\ne M_z(z, y')$, a contradiction. So the assumption is false, which proves the deterministic time hierarchy theorem.

#### Non-deterministic time hierarchy theorem

If $g(n)$ is a time-constructible function and $f(n+1)=o(g(n))$, then $\mathsf{NTIME}(f(n))\subsetneq\mathsf{NTIME}(g(n))$.

The non-deterministic time hierarchy theorem gives $\mathsf{NP}\subsetneq\mathsf{NEXPTIME}$.

### Space hierarchy theorem

If $f(n)$ is a space-constructible function and $f(n)=\Omega(\log n)$, then $\mathsf{SPACE}(o(f(n)))\subsetneq\mathsf{SPACE}(f(n))$.

Here $\mathsf{SPACE}$ can stand for either $\mathsf{DSPACE}$ or $\mathsf{NSPACE}$.

The space hierarchy theorem gives $\mathsf{PSPACE}\subsetneq\mathsf{EXPSPACE}$.

### Savitch's theorem

A deterministic Turing machine can simulate a non-deterministic Turing machine using the square of the space the latter uses (though it may take much more time). That is:

If $f(n)=\Omega(\log n)$, then:

$$
\mathsf{NSPACE}\left(f\left(n\right)\right)\subseteq \mathsf {DSPACE}\left(\left(f\left(n\right)\right)^2\right)
$$

Corollary: $\mathsf{PSPACE}=\mathsf{NPSPACE}$, $\mathsf{EXPSPACE}=\mathsf{NEXPSPACE}$.

### P?=NP

Whether the complexity classes $\mathsf{P}$ and $\mathsf{NP}$ are equal is a famous open problem in computational complexity theory.

If $\mathsf{P}=\mathsf{NP}$, then $\mathsf{NP}=\mathsf{co-NP}$, but not the other way round (there is currently no method to prove $\mathsf{P}=\mathsf{NP}$ from $\mathsf{NP}=\mathsf{co-NP}$).

???+ note "Why is NP?=co-NP not obvious?"
    Since an $\mathsf{NP}$ problem and its corresponding $\mathsf{co-NP}$ problem have opposite answers, it is easy to think: for a $\mathsf{co-NP}$ problem, I just flip the output of the non-deterministic Turing machine that solves its complement, and that solves the $\mathsf{co-NP}$ problem, so $\mathsf{NP}=\mathsf{co-NP}$.
    
    In fact, the method above does solve the $\mathsf{co-NP}$ problem, but it does not give a non-deterministic Turing machine that solves it: a Turing machine that flips the output of a non-deterministic Turing machine is not itself a non-deterministic Turing machine. A non-deterministic Turing machine accepts if some branch accepts, and rejects only if all branches reject. Flipping its output means accepting only when all branches agree and rejecting when one branch does, which no longer fits the definition of a non-deterministic Turing machine. So being able to solve the $\mathsf{co-NP}$ problem with such a machine does not make it an $\mathsf{NP}$ problem.

If $\mathsf{P}=\mathsf{NP}$, we also get $\mathsf{EXPTIME}=\mathsf{NEXPTIME}$.

If $\mathsf{P}\ne\mathsf{NP}$, then NP-intermediate is non-empty.

## References

1.  [Computational Complexity (1): Automata and Regular Languages](https://lingerois.com/p/%E8%AE%A1%E7%AE%97%E5%A4%8D%E6%9D%82%E6%80%A71-%E8%87%AA%E5%8A%A8%E6%9C%BA%E4%B8%8E%E6%AD%A3%E5%88%99%E8%AF%AD%E8%A8%80/);

2.  [Computational Complexity (2): Turing Machines and Computability](https://lingerois.com/p/%E8%AE%A1%E7%AE%97%E5%A4%8D%E6%9D%82%E6%80%A72-%E5%9B%BE%E7%81%B5%E6%9C%BA%E4%B8%8E%E5%8F%AF%E8%AE%A1%E7%AE%97%E6%80%A7/);

3.  Related entries on [Wikipedia](https://en.wikipedia.org/) and the references cited in those entries.
