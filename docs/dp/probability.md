author: Tiphereth-A, ShaoChenHeng, Enter-tainer, ksyx, c-forrest, StudyingFather, H-J-Granger, iamtwz, imp2002, Ir1d, kenlig, LeBronGod, Marcythm, MegaOwIer, NachtgeistW, ouuan, Patchouliys, Soohti, TianKong-y, sun2snow

## Introduction

Probability DP is used to solve problems about probabilities and expected values. It helps to know the material in [Probability & expected value](../math/probability/exp-var.md) first. In general, probability problems loop forward, while expected-value problems loop backward. If the transition equations you define have aftereffects (cyclic dependencies), you also need [Gaussian elimination](../math/numerical/gauss.md) to solve them. Probability DP is also often combined with other topics, such as [bitmask DP](./state.md) or DP transitions on trees.

## Probability DP

These problems are solved forward, that is, from the initial state toward the result. As with ordinary DP, the hard part is still describing the transition equations; these problems just wrap them in probability theory.

### Example problem

???+ example "[Codeforces 148D Bag of mice](https://codeforces.com/problemset/problem/148/D)"
    A bag holds $w$ white mice and $b$ black mice. The princess and the dragon take turns drawing mice from the bag. Whoever draws a white mouse first wins. If the bag runs out of mice and nobody has drawn a white mouse, the dragon wins. The princess draws one mouse per turn. After the dragon draws one mouse, one more mouse jumps out of the bag. Every drawn mouse and every mouse that jumps out is chosen at random. The princess goes first. Find the probability that the princess wins.

??? note "Solution"
    Let $f_{i,j}$ be the probability that the princess wins when it is her turn and the bag has $i$ white mice and $j$ black mice. Initialize the boundaries: $f_{0,j}=0$, because with no white mice left the dragon wins; $f_{i,0}=1$, because any mouse she draws is white, so the princess wins.
    Consider the transitions for $f_{i,j}$:
    
    -   The princess draws a white mouse and wins. The probability is $\dfrac{i}{i+j}$.
    -   The princess draws a black mouse, and the dragon draws a white mouse and wins. The probability is $\dfrac{j}{i+j}\cdot\dfrac{i}{i+j-1}$.
    -   The princess draws a black mouse, the dragon draws a black mouse, and a black mouse jumps out. This moves to $f_{i,j-3}$. The probability is $\dfrac{j}{i+j}\cdot\dfrac{j-1}{i+j-1}\cdot\dfrac{j-2}{i+j-2}$.
    -   The princess draws a black mouse, the dragon draws a black mouse, and a white mouse jumps out. This moves to $f_{i-1,j-2}$. The probability is $\dfrac{j}{i+j}\cdot\dfrac{j-1}{i+j-1}\cdot\dfrac{i}{i+j-2}$.
    
    Since we want the probability that the princess wins, the second case is not counted. We must also make sure the last two cases are valid, so we check the values of $i,j$: the third case needs at least 3 black mice, and the fourth case needs 1 white mouse and 2 black mice.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_1.cpp"
    ```

### Exercises

-   [POJ3071 Football](http://poj.org/problem?id=3071)
-   [CodeForces 768D Jon and Orbs](https://codeforces.com/problemset/problem/768/D)

## Expected value DP

### Example problems

???+ example "[POJ2096 Collecting Bugs](http://poj.org/problem?id=2096)"
    A piece of software has $s$ subsystems and can have $n$ kinds of bugs. A person finds one bug per day. Each bug belongs to one bug category and to one subsystem. Each bug belongs to a given subsystem with probability $\dfrac{1}{s}$ and to a given bug category with probability $\dfrac{1}{n}$. Find the expected number of days until bugs of all $n$ categories have been found and bugs have been found in all $s$ subsystems.

??? note "Solution"
    Let $f_{i,j}$ be the expected number of days to reach the target state when bugs of $i$ categories and bugs in $j$ subsystems have already been found. Here the target state is having found bugs of $n$ categories and bugs in $s$ subsystems. So $f_{n,s}=0$: the target state is already reached and no more days are needed to find bugs. We therefore start the recurrence from the target state, and the answer is $f_{0,0}$.
    
    Consider the transitions for $f_{i,j}$:
    
    -   $f_{i,j}$: the new bug belongs to one of the $i$ categories and one of the $j$ subsystems already found. The probability is $p_1=\dfrac{i}{n}\cdot\dfrac{j}{s}$.
    -   $f_{i,j+1}$: the new bug belongs to one of the $i$ categories already found, but not to any subsystem already found. The probability is $p_2=\dfrac{i}{n}\cdot(1-\dfrac{j}{s})$.
    -   $f_{i+1,j}$: the new bug does not belong to any category already found, but belongs to one of the $j$ subsystems. The probability is $p_3=(1-\dfrac{i}{n})\cdot\dfrac{j}{s}$.
    -   $f_{i+1,j+1}$: the new bug belongs neither to a category already found nor to a subsystem already found. The probability is $p_4=(1-\dfrac{i}{n})\cdot(1-\dfrac{j}{s})$.
    
    Then, by linearity of expectation, we get the transition equation:
    
    $$
    \begin{aligned}
    f_{i,j} &= p_1\cdot f_{i,j}+p_2\cdot f_{i,j+1}+p_3\cdot f_{i+1,j}+p_4\cdot f_{i+1,j+1} + 1\\
    &= \dfrac{p_2\cdot f_{i,j+1}+p_3\cdot f_{i+1,j}+p_4\cdot f_{i+1,j+1}+1}{1-p_1}
    \end{aligned}
    $$

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_2.cpp"
    ```

???+ example "['NOIP2016' Changing Classrooms](http://uoj.ac/problem/262)"
    Niuniu has classes in $n$ time slots. The class in slot $i$ is held in classroom $c_i$, and he can apply to move it to classroom $d_i$; the application succeeds with probability $p_i$. He may apply for at most $m$ classes. After the class in slot $i$ ends, he must walk to the classroom of slot $i+1$. You are given a graph of $v$ classrooms and $e$ roads, and moving costs stamina. Choose which classes to apply for so that the expected total stamina spent walking between classrooms is minimized; that is, find the minimum expected total distance.

??? note "Solution"
    For this connected undirected graph, first compute all shortest paths with Floyd's algorithm, which makes the later transitions easy. Treat each move as one stage (going from slot $i$ to slot $i+1$ is one move). At each step, with probability $p_i$ he goes to $d_i$ (but only $m$ of all the $d_i$ can be chosen), and with probability $1-p_i$ he goes to $c_i$. We want the minimum expected total distance after all $n$ stages.
    
    Define $f_{i,j,0/1}$ as the minimum expected total distance at time slot $i$, where $j$ change requests have been used so far (including this slot), and in this slot we do apply (1) or do not apply (0) to change classrooms. The answer is then $\min \{f_{n,i,0},f_{n,i,1}\} ,i\in[0,m]$. Note the boundary $f_{1,0,0}=f_{1,1,1}=0$.
    
    Consider the transitions for $f_{i,j,0/1}$:
    
    -   If we do not apply in this stage, i.e. $f_{i,j,0}$: it may come from a state where we did not apply last time, giving $f_{i-1,j,0}+w_{c_{i-1},c_{i}}$. It may also come from a state where we applied last time; using conditional probability and the law of total probability we get $f_{i-1,j,1}+w_{d_{i-1},c_{i}}\cdot p_{i-1}+w_{c_{i-1},c_{i}}\cdot (1-p_{i-1})$. So the transition equation is:
    
    $$
    \begin{aligned}
    f_{i,j,0}=min(f_{i-1,j,0}+w_{c_{i-1},c_{i}},f_{i-1,j,1}+w_{d_{i-1},c_{i}}\cdot p_{i-1}+w_{c_{i-1},c_{i}}\cdot (1-p_{i-1}))
    \end{aligned}
    $$
    
    -   If we apply in this stage, i.e. $f_{i,j,1}$: similarly, it may come from a state where we did not apply last time, or from one where we applied. Whenever a change does not happen, multiply by $(1-p_i)$; whenever it does, multiply by $p_i$. Just enumerate all possible cases and compute. We won't list every transition here; after the previous case, these transitions should be easy to write down.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_3.cpp"
    ```

Comparing these two problems, we see that for expected-value DP, whether the problem asks for a single value or for an optimum affects how the transitions are derived. But whether DP is used for probabilities or expected values, it always relies on probability knowledge and on writing down and simplifying formulas. The details you need to think about when writing the transition equations are also similar.

### Exercises

-   [HDU3853 LOOPS](https://acm.hdu.edu.cn/showproblem.php?pid=3853)
-   [HDU4035 Maze](https://acm.hdu.edu.cn/showproblem.php?pid=4035)
-   ['SCOI2008' Bonus Level](https://www.luogu.com.cn/problem/P2473)

## DP with aftereffects

### Example problem

???+ example "[CodeForces 24D Broken robot](https://codeforces.com/problemset/problem/24/D)"
    You are given an $n \times m$ grid. A robot starts at row $x$, column $y$. At each step the robot chooses, with equal probability, to stay where it is, move one step left, move one step right, or move one step down. If the robot is on the border, it never moves outside the grid. Find the expected number of steps for the robot to reach the last row.

??? note "Solution"
    When $m=1$, at each step the robot stays put with probability $\dfrac{1}{2}$ and moves down one cell with probability $\dfrac{1}{2}$, so the answer is $2\cdot (n-x)$.
    Let $f_{i,j}$ be the expected number of steps for the robot to reach row $n$ starting from row i, column j. The final state is $f_{n,j}=0$.
    Since the robot chooses with equal probability to stay, move left, move right or move down, consider the transitions for $f_{i,j}$:
    
    -   $f_{i,1}=\dfrac{1}{3}\cdot(f_{i+1,1}+f_{i,2}+f_{i,1})+1$
    -   $f_{i,j}=\dfrac{1}{4}\cdot(f_{i,j}+f_{i,j-1}+f_{i,j+1}+f_{i+1,j})+1$
    -   $f_{i,m}=\dfrac{1}{3}\cdot(f_{i,m}+f_{i,m-1}+f_{i+1,m})+1$
    
    Between rows, the robot can only move down, so there are no aftereffects. Within a row, the robot can move left and right, which can create cycles, so there are aftereffects.
    Rearranging the equations gives:
    
    -   $2f_{i,1}-f_{i,2}=3+f_{i+1,1}$
    -   $3f_{i,j}-f_{i,j-1}-f_{i,j+1}=4+f_{i+1,j}$
    -   $2f_{i,m}-f_{i,m-1}=3+f_{i+1,m}$
    
    Since the recurrence runs backward, every $f_{i+1,j}$ is already known.
    There are $m$ columns, so the right-hand side is a column vector with $m$ rows, and the left-hand side is a matrix with $m$ rows and $m$ columns. Using the augmented matrix gives a matrix with $m$ rows and $m+1$ columns, and [Gaussian elimination](../math/numerical/gauss.md) then gives the answer.

??? note "Reference code"
    ```cpp
    --8<-- "docs/dp/code/probability/probability_4.cpp"
    ```

### Exercises

-   [HDU 4418 Time Travel](https://acm.hdu.edu.cn/showproblem.php?pid=4418)
-   ['HNOI2013' Random Walk](https://loj.ac/problem/2383)

## References

[kuangbin's summary of probability DP (Chinese)](https://www.cnblogs.com/kuangbin/archive/2012/10/02/2710606.html)
