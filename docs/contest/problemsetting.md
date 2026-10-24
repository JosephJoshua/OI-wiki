author: ouuan, Henry-ZHR, StudyingFather, ChungZH, xyf007, Cryflmind, oierlinch, xk2013awa

## Before you start setting problems

### Have a reasonable skill level

On one hand, it is hard for a person to set problems that are harder than their own level. A solid OI background helps you come up with better ideas and find good solutions. On the other hand, OI skill partly reflects OI experience: a contestant who has seen more problems will also have their own sense of what a "good problem" is.

### Be serious and responsible

Problems are set for other people to solve. Setting a problem is more about serving others than about showing off. A programming contest is a competition between contestants, not a fight between the setter and the solvers. So the goal of a problem should not be to defeat the contestants (although some protection against everyone solving everything, and good separation between skill levels, are of course very important). Instead, contestants should take something away from the contest. It is very important to spend enough time and effort learning how to set problems, and to set them seriously and responsibly.

### Be ready to spend a lot of time

If you want to set problems seriously, you will have to spend a lot of time. If you are not mentally prepared for this, the contest preparation may end up rushed and of poor quality, or you may later regret not spending that time on studying instead. But setting problems can also bring many good memories. If you are truly interested in it and well prepared, what you gain from it can make up for the time spent.

### Read this article carefully

This article walks through the whole problem-setting process from two angles: how to set a problem, and how to set it well. Anyone who wants to set problems will surely benefit from reading it carefully.

## Problem content

The idea, that is, the essential content of a problem, is the soul of the problem, and it is also the first step in setting one.

### Where ideas come from

1.  Inspiration from existing problems (but do not just copy them or strengthen them in meaningless ways, e.g. moving a sequence problem onto a cactus graph).
2.  Inspiration from topics you have learned (but do not glue unrelated topics together).
3.  Inspiration from daily life or games (but be careful not to turn a game into a huge simulation problem).
4.  For no particular reason, a problem just pops into your head.

### What kind of idea is bad

#### About duplicate problems

Duplicate problems roughly fall into three kinds: identical, nearly identical, and same solution.

-   Identical: an AC solution of one problem also gets AC on the other.
-   Nearly identical: someone who cannot solve the problem could still turn the AC code of one problem into AC code for the other.
-   Same solution: the core idea and approach are the same, but the implementation and less important details differ.

Going from bottom to top, each of these three kinds contains the one above it.

The following must not happen:

1.  Setting a problem when you know a "nearly identical" problem already exists.
2.  Setting a "nearly identical" duplicate because you did not search online and so did not know it existed.
3.  Setting a "same solution" duplicate when the original is widely known (e.g. a NOIP or NOI problem).
4.  Using a "same solution" duplicate as a non-giveaway problem in a selection exam.

The following should preferably not happen:

1.  Setting a problem when you know a duplicate that is at least "same solution" already exists.
2.  Setting a "same solution" duplicate because you did not search online and so did not know it existed.
3.  Setting a "nearly identical" duplicate under any circumstances.

Exceptions where the requirements can be relaxed:

1.  Mock contests within a school.
2.  Mock contests meant for training on a specific topic.
3.  Easy contests, or problems meant as giveaways.

#### About "nasty" problems

A "nasty problem" is a vague and subjective idea. Here we just quote some earlier discussions about it and add some of our own thoughts. This topic is very open, and everyone is welcome to share their opinions.

> A good problem should not be two problems stuck together. A good problem has its own idea, and it should highlight this idea without too much wrapping.
>
> A good problem should be novel. A truly good problem is one that inspires people to come up with new good problems.
>
> —[vfk, "The Origins of the UOJ Spirit"][1]

Example: [XR-1 Conan's Family](https://www.luogu.com.cn/problem/P5346). The two halves of the solution are completely disconnected. The first half is [Template: suffix sorting on a tree](https://www.luogu.com.cn/problem/P5353), and the second half is a classic tree problem. Even if the vertex weights of the tree were given arbitrarily as input, you could still do the second half. The two halves have no connection.

> One kind of OI problem is mainly math. Both the statement and the solution look like a math problem, and the solution does not involve any algorithmic topic. Such OI problems are called pure math problems.
>
> —[Wang Tianyi, "On the Harm of Off-Topic Problems"][2]

Classic example: [NOIP 2017 Xiaokai's Puzzle](https://uoj.ac/problem/329)

What makes math problems in OI different from other math problems, and what reflects the nature of OI, is that the point of an OI math problem is usually not **what** the answer is, but how to compute it **faster**. If a problem mainly tests "how to compute it" rather than "how to compute it quickly", such a math problem is usually not suitable for OI.

> Some off-topic problems involve university physics, so contestants are lost when facing physics topics they have never seen, which creates a knowledge barrier.
>
> —[Wang Tianyi, "On the Harm of Off-Topic Problems"][2]

Classic example: [Tsinghua Training Camp 2015 Polygon Goes to Sea](https://uoj.ac/problem/159)

Not just physics: OI problems should not rely too much on knowledge from other subjects. If they do, they should explain it in detail, and knowledge from other subjects should not become a major obstacle to solving the problem.

> A good problem, whatever its difficulty, should have its own thinking difficulty. It should require contestants to think and discover some properties.
>
> The code of a good problem can be long, but it must not be long because of forced nesting or extra conditions. It should be naturally long, so that people feel the code for this problem simply should be this long.
>
> —[Wang Tianyi, "On the Harm of Off-Topic Problems"][2]

Classic examples: [SDOI 2010 Pig Kingdom Kill](https://loj.ac/problem/2885), [National Training Team Mutual Test 2015 Future Program: Modified](https://uoj.ac/problem/98)

In ordinary OI contests, thinking difficulty should make up the main part. Of course, engineering-style problems like those on Day 2+ of THUWC/THUSC have their reasons to exist: besides testing algorithm design, those camps also aim to test engineering coding and documentation-reading skills that connect with university study. But in ordinary OI contests, the focus should still be on algorithm design and thinking.

## Problem statement

### Use LaTeX for formulas

There are many LaTeX tutorials online, for example:

-   [Getting started with LaTeX](../tools/latex.md#图表)
-   [A complete list of LaTeX math formulas](https://www.luogu.com.cn/blog/IowaBattleship/latex-gong-shi-tai-quan)
-   [Various LaTeX commands and symbols](https://blog.csdn.net/anxiaoxi45/article/details/39449445)

When using it, please follow the [formatting rules for LaTeX formulas](../intro/format.md).

### Background

The background story should be as short as possible. When it is long, it should be kept separate from the problem description.

You must absolutely avoid a background that seriously gets in the way of understanding the problem.

If needed, you can provide two versions: a description combined with the background, and a short plain description.

### Description

In short, the description needs to be **clear and easy to understand**.

Every definition in the statement that might not be understood should be explained. Undefined concepts should not appear out of nowhere. For example, in [CF1172D Nauuo and Portals](https://codeforces.com/problemset/problem/1172/D), you must explain in the statement what a "portal" is.

Each concept in the statement should be described with a single word. For example, you should not say "fee" in one place and "cost" in another.

You should not use words in a meaning different from their original or common meaning without explanation. For example, you should not use "path" to mean a single edge without saying so.

You need to make sure your statement does not contradict itself. For example, in [CF1173A Nauuo and Votes](https://codeforces.com/problemset/problem/1173/A), "?" is not counted as a kind of "result" because "?" means "there are more than one possible results".

You need to make sure your statement cannot be misread in a way that is still self-consistent, even if that reading goes against common sense and nobody would normally think that way. For example, in [CF1172D Nauuo and Portals](https://codeforces.com/problemset/problem/1172/D), "walk into" is carefully defined and distinguished from "teleport" to rule out this reading: going through a portal can take you to another portal, and arriving at a portal teleports you, so you would keep jumping back and forth.

Reading the description from start to end, the reader should understand every sentence, as well as the task and its requirements. Any confusion should be cleared up at the latest in the very next paragraph, not several paragraphs later. The reader should not have to look at the input/output format to understand the problem, let alone guess it from the samples. For example, in [GuOJ Round #1 Cirno's Ice and Snow Banquet](https://github.com/OI-wiki/problemset/blob/master/contest/online/GuOJ/OI%20Archive%20-%20GuOJ1171.pdf), the goal of the problem, "the maximum amount of water the Misty Lake can finally receive", first appears in the output format. Together with the misleading sentence "Reimu can of course quickly compute the total cost of cleaning all the streams", this makes the problem easy to misread, which is not acceptable. The goal should be stated in the description. (This example also has the problem of the background seriously getting in the way of understanding.) The same mistake appears in [CF1423(4)N Bubblesquare Tokens](https://codeforces.com/problemset/problem/1423/N), where the goal "friend pairs and number of tokens each of them gets on behalf of their friendship" first appears in the output format.

### Input and output format

The input and output format just needs to be clear and **complete**. There are no rigid rules. I personally suggest following CF problems when writing the input/output format; for details see [Notes for CF problem setters][3].

To make things easier for contestants, the input/output format should preferably state the meaning of each variable, unless the meaning is too long to explain in one sentence (in that case you can say "see the description for its meaning").

Note in particular: if the output contains real numbers, please try to use an [SPJ](#special-judge) to bound the allowed error, instead of requiring "round to x decimal places".

"Round to x decimal places" can require unlimited precision. For example, suppose you require three decimal places and the true answer is $0.0015$. Then any error of any size that makes the computed answer smaller than $0.0015$ leads to a wrong output, even if the computed answer is $0.00149999\cdots$.

If you cannot use an SPJ, make sure the required precision is finite. For example: please output the answer rounded to three decimal places. Let the reference answer be $ans$. The data guarantees that for every $x$ with $\frac{|x-ans|}{\max(1,ans)}<10^{-9}$, $x$ rounds to the same result as $ans$.

Some sentences you can use as references:

```latex
The first line of input contains three positive integers $n$, $m$, $k$ ($1\le n,m\le 2\cdot 10^5$, $1\le k\le 100$) — $n$ is the length of the sequence, $m$ is the number of operations, and the meaning of $k$ is given in the description.
```

```latex
The second line of input contains $n$ non-negative integers $a_1,a_2,\ldots,a_n$ ($1\le a_i\le 10^9$) — the given sequence.
```

```latex
The $i$-th of the next $m$ lines contains two positive integers $l_i$ and $r_i$ ($1\le l_i\le r_i\le n$), meaning that the $i$-th operation is performed on the interval $[l_i,r_i]$.
```

```latex
Each of the next $n-1$ lines contains two positive integers $u$ and $v$ ($1\le u,v\le n$), meaning that $u$ and $v$ are connected by an edge.

It is guaranteed that the given edges form a tree.
```

```latex
The only line of input contains a non-empty string of lowercase English letters, whose length does not exceed $10^6$.
```

```latex
The second line of input contains a real number $x$ with at most three digits after the decimal point ($-10^6\le x\le 10^6$); its meaning is given in the description.
```

```latex
Output one real number. Your output is considered correct if its absolute or relative error compared with the reference answer is less than $10^{-6}$.
```

```latex
The second line of output contains $n$ positive integers describing the plan you constructed — the $i$-th number is the index of the $i$-th card you play.

If there are multiple valid answers, you may output any of them.
```

???+ note "Generating input data with a random number generator inside the contestant's code"
    Some problems have very large input. To keep reading time from being too long, they ask contestants to generate the data inside their code with a given data generator, instead of reading it from standard input or a file.
    
    This approach needs careful thought, because it has many drawbacks:
    
    -   It may add randomness to the data that the intended solution does not need, or make it hard to construct specific data
    -   It may make the input format harder to understand
    -   If the random number generator is poorly packaged, even learning how to use the generator may be hard
    -   If a contestant does not use the language recommended by the setter, they may need to write their own data generator
    
    This approach is usually used to keep reading time from being too long. So one alternative is to provide a fast enough [input/output optimization](./io.md) template, so that everyone's reading time is about the same. Then even if reading takes long, it will not affect the difference in running time between contestants. Another solution is to wrap the problem as a function-call (rather than I/O) interactive problem. Even if the algorithm itself involves no interaction, an interactive problem can make reading time the same for everyone. IOI uses this approach and makes every problem interactive. However, both approaches limit the languages contestants can use, and the setter has to manually support each allowed language.
    
    Going back to the root of the issue, you can also ask whether such huge input is really necessary, whether smaller input could achieve the same goal, and whether it is really necessary to fail solutions with a slightly worse complexity than the intended one.

### Constraints

According to CF's rules, the constraints should be written in the input format, but in China they are often written at the end of the problem.

The easiest mistake in the constraints is incompleteness. Every number and every string in the input should be clearly bounded. The sample input/output format sentences above already show some correct ways to write constraints.

Common omissions in constraints:

1.  The word "integer" itself.
2.  The statement only says "integer" rather than "positive integer", and the constraints only give an upper bound with no lower bound.
3.  No character set is given for a string.
4.  No number of decimal places is given for a real number.
5.  Some variables have no range at all.

You need to make sure the reference solution passes **every possible test** that satisfies the constraints in the statement.

???+ note "About \"the data is guaranteed to be randomly generated\""
    Some problems say "the data is guaranteed to be randomly generated". Often this is not the best choice, because "randomly generated" does not clearly restrict the data, which makes it hard to know the exact constraints or to provide hack data.
    
    Usually, "the data is guaranteed to be randomly generated" can be replaced by the data property the solution actually needs. For example, a randomly generated tree can often be replaced by a bound on the tree's height.
    
    If you really must guarantee randomly generated data, you should specify exactly how it is generated. For example, is a tree generated by picking random parents, or by generating a random Prüfer sequence?
    
    Note that non-deterministic algorithms are different from algorithms that rely on random data. The former get the correct answer with high probability on any input, while the latter get the correct answer on most inputs but cannot get it on certain specific inputs.

### Samples

The samples should be reasonably strong and catch some simple mistakes. Someone who misread the problem should be able to discover this from the samples.

For a problem with several kinds of operations, every kind of operation should appear in the samples.

For a problem with several kinds of output (such as [CF1173A Nauuo and Votes](https://codeforces.com/problemset/problem/1173/A)), every kind of output should appear in the samples. Exception: problems that ask whether a solution exists even though there is actually always one.

### Sample explanations

The more complex and harder to understand the description is, the more detailed the sample explanation should be.

The easier the problem is, the more detailed the sample explanation should be.

A detailed sample explanation can come with pictures.

Large samples do not need an explanation.

To be considerate to color-blind readers, it is best not to make colors necessary for understanding the sample explanation. You can use colored pictures to make the explanation look nicer, but if you must use colors to convey essential information, it is best not to use red with yellow or red with green.

## Time limits, memory limits and partial points

Time and memory limits exist to fail solutions with the wrong complexity. (Of course, they also keep judging from taking too long. For example, an interactive problem that only limits the number of queries and not the time complexity still has a time limit.)

So in principle, the time limit should be as large as possible while still not letting wrong solutions pass.

In general, the time limit should satisfy the following:

1.  At least twice the running time of the std (reference solution) in the worst case.
2.  If the contest allows Java, Java should be able to pass.
3.  Wrong solutions should not pass (unless they really cannot be failed, or you want to let a certain wrong solution pass).

To let solutions with a large constant factor pass while still failing wrong ones, you can usually increase both the constraints and the time limit. But note that sometimes the intended solution gets a much larger constant when the constraints grow (due to cache effects and other mysterious issues). In that case, increasing the constraints may not widen the time gap between the intended and the wrong solutions.

In formats with partial points, you can also use graded data and data with slightly smaller constraints, so that good wrong solutions and intended solutions with large constants do not pass but still get a fairly high partial score.

Note that when the constraints are below $5\cdot 10^5$, you should consider whether a solution using [SIMD instructions](https://ouuan.github.io/post/n方过百万-暴力碾标算——指令集优化的基础使用) can pass.

Usually the memory limit should be large enough, unless a solution with better space complexity is truly clever and it is worth failing solutions with worse space complexity. In that case, consider adding a subtask with a looser memory limit. Note that if you do not want to fail solutions that use a lot of memory, data structure problems usually need a large memory limit.

> A good problem should have selection power and separate skill levels well. It should have at least 4 levels of partial points, so that beginners can get points and strong contestants can show their strength.
>
> —vfk, "The Origins of the UOJ Spirit"

Partial points generally come in two kinds: smaller constraints and special properties.

Smaller constraints should usually have several levels. Even if you cannot think of a solution with a certain complexity, you can still consider giving that complexity its own level. In general, to avoid punishing constant factors, you can add a level whose limits are half of the maximum.

"The data is graded" is better replaced by several levels of partial points.

Partial points for special properties depend on the specific problem. Ideally, a special-property subtask should guide contestants toward the intended solution. Unlike smaller-constraint subtasks, if you do not know a solution aimed at a special property, it is best not to give that property its own level. For example, the $k=1$ subtask of [CTS 2019 Random Cube](https://loj.ac/problem/3119) was criticized by many people during the problem explanation, who said it got in the way of thinking about the intended solution.

If the scoring differs from the default (e.g. bundling tests into subtasks in an ordinary OI-format contest), you must state it in the statement.

Phrases like "XX% of the data satisfies XX" are not recommended, especially when the constraints involve several variables. For example, "$30\%$ of the data satisfies $n \le 1000$" and "$40\%$ of the data satisfies $m \le 100$" might describe properties of $70\%$ of the data, or of only $40\%$ of it. In general, subtasks or a constraints table are a better choice.

## Making test data

Generating data is a necessary step in setting problems, and it is also needed for stress testing. With a few data-generation tricks, making data becomes easier and the data you make becomes stronger.

### Generating random data

#### Generating random numbers

See the [random functions](../misc/random.md) page.

Note in particular: when generating numbers with a range larger than what the random function returns, **do not** use something like `rand() * rand()`. Numbers generated this way are very unevenly distributed.

Also, it is recommended to use [testlib](../tools/testlib/generator.md) to make data when setting problems. It guarantees that the same seed gives the same random numbers on different platforms, and the seed is generated automatically from the command-line arguments.

#### Generating a random permutation

You can use `std::shuffle` from the STL, like `std::shuffle(a, a + n, rng)`, where `rng` is a random number generator, e.g. `std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count())`.

Please **do not** use `std::random_shuffle`. It was deprecated in C++14 and removed in C++17.

#### Generating a random interval

A common wrong method: pick the left endpoint $l$ randomly in $[1,n]$, then pick the right endpoint $r$ randomly in $[l, n]$. Intervals generated this way lean to the right.

A more correct method (recommended): generate two random numbers in $[1, n]$, use the smaller one as the left endpoint and the larger one as the right endpoint.

A truly uniform method: generate a random number $x$ in $[0, n]$. If $x = 0$, generate a random number $y$ in $[1, n]$ and use the interval $[y, y]$; otherwise use the "more correct method".

#### Generating a random tree

A common method is: for each node $i$ from $2$ to $n$, choose its parent randomly from $[1,i-1]$. The tree generated this way is not uniformly random, and its expected height is $O(\log n)$.

Another random method: choose the parent of $i$ randomly from $[i\cdot low, i\cdot high]$. With good choices of $low$ and $high$, this can make fairly strong trees.

A truly uniform method uses the [Prüfer sequence](../graph/prufer.md): first generate a random Prüfer sequence, then build the tree from it. With this method, the expected height of the tree is $O(\sqrt n)$.

In addition, you can generate a random permutation to relabel the nodes or shuffle the order of the edges.

### Constructing data

#### Problems about intervals

Common constructions: very short intervals (in particular, all single points), and very long intervals (in particular, all equal to the whole sequence).

#### Problems that need factorization

As many prime factors as possible, counted with multiplicity: powers of $2$.

As many distinct prime factors as possible: the product of the first few primes.

As many divisors as possible: see sequence [A002182](http://oeis.org/A002182) on OEIS.

#### Problems that need the greatest common divisor

Making the two numbers two consecutive terms of the [Fibonacci sequence](../math/combinatorics/fibonacci.md) makes the Euclidean algorithm reach its worst-case time complexity.

#### Tree problems

Common constructions:

-   A chain
-   A star
-   A complete binary tree
-   A complete binary tree where each node is replaced by a chain of length $\sqrt n$
-   A star with a chain hanging off it
-   A chain with some single nodes hanging off it
-   A tree of height $d$ with $d>1$, whose root has two children: the left subtree is a chain of length $d-1$, and the right subtree is such a tree of height $d-1$.

If you are not in an exam, you can also use [Tree-Generator](https://github.com/ouuan/Tree-Generator) to generate all kinds of trees.

### Generating data in batches

The author recommends command-line arguments plus a bat/sh script.

For example:

`gen.cpp`:

```cpp
#include "testlib.h"

using namespace std;

int n, m, k;
vector<int> p;

int main(int argc, char* argv[]) {
  registerGen(argc, argv, 1);

  int i;

  n = atoi(argv[1]);
  m = atoi(argv[2]);
  k = rnd.next(1, n);

  for (i = 1; i <= n; ++i) p.push_back(i);

  shuffle(p.begin(), p.end());
  // shuffle using rnd.next()

  printf("%d %d %d\n", n, m, k);
  for (i = 0; i < n; ++i) {
    printf("%d%c", p[i], " \n"[i == n - 1]);
    // Use a string as an array: spaces in between, a newline at the end. A common trick when making data
  }

  return 0;
}
```

`gen_scripts.bat`:

```bat
gen 10 10 > 1.in
gen 1 1 > 2.in
gen 100 200 > 3.in
gen 2000 1000 > 4.in
gen 100000 100000 > 5.in
```

The benefit is that you only need one generator for all the different tests, and you can easily change the parameters of any test.

### Requirements for test data

The data should include the minimum and maximum value of every parameter.

The data should include all kinds of edge cases.

When using subtasks, the data (both input and output) should preferably cover every part of the value range, not just the maximum of the constraints.

To keep special-case checks aimed at specific constructions from passing, you can combine different constructions in one test, or make most of the data constructed and mix in a small random part.

The data should include all kinds of constructions, even if you do not know which wrong solution would fail on them. (In formats where points are given per test, handle this with care.)

Of course, if you know a wrong solution with a correctness problem (one that a normal person could think of and write), try your best to fail it.

Note in particular: if integer overflow is possible, you must fail solutions that overflow. In formats with partial points, people who forget to use long long should not get the same score as brute force, or even lower.

If there are pretests, the pretests should be as strong as possible (while being as few as possible). In other words, the pretests should include every known way to break wrong solutions for the problem (using as few tests as possible).

If you want a small number of FSTs (failed system tests) rather than none, you should still keep the pretests strong, because in a real contest unexpected mistakes are very likely to appear, leading to far more FSTs than expected.

### Data format

Here are some common format requirements for input data, which can serve as a general reference:

> 1.  Use the line-ending format of the judging environment.
> 2.  The last line of the file ends with a newline, i.e. the last character of the whole file must be `\n`.
> 3.  No line starts or ends with whitespace.
> 4.  There is never more than 1 space in a row.

Data generated on Windows usually uses `\r\n` line endings, while mainstream judging systems run on Linux, which uses `\n`. If a program on Linux reads data with Windows line endings, line breaks may be handled incorrectly when reading strings, so the program may give different results in different environments. If you compare, on Linux, output generated on Linux with a reference output generated on Windows, they may differ because of the line endings. To keep program behavior consistent, all data must be converted to the line-ending format of the environment where programs run.

Usually you can generate data with Linux line endings in these ways:

1.  Generate the data directly on Linux.
2.  Convert the input and output files with the [`dos2unix`](https://dos2unix.sourceforge.io/) tool, which is included in toolchains such as Cygwin and MinGW.
3.  Open the output file in binary mode and use `\n` line endings.
4.  Write your own tool based on the `dos2unix.cpp` code on [this page](https://help.luogu.com.cn/manual/luogu/problem/testcase-format#附录windows-环境下造数据注意事项).

## Special Judge

[Tutorial on writing an SPJ](../tools/special-judge.md)

Problems that ask for a construction and problems that output floating-point numbers are the two most common kinds that need an SPJ. Other problems may also need one depending on the situation. On CF, every problem must use a testlib-based checker. For example, when a problem asks for several integers, the built-in ncmp checker of testlib is used, so contestants can print any whitespace (spaces or newlines).

Checkers are usually written with testlib. A checker has to handle all kinds of invalid output and must be extremely robust. It is very hard to write a good checker without testlib.

When writing a checker, pay attention to these two points:

1.  You need to handle all kinds of invalid output, so check that every variable you read is in its valid range (`readInt(minvalue, maxvalue)`). For example, a variable that will be used as an array index during checking must have its range checked, or the array may be accessed out of bounds. Sometimes this causes RE, and sometimes it may even be judged as AC.
2.  In principle, a checker should not check whitespace (that is, it should not use `readSpace()`, `readEoln()` or `readEof()`; note that testlib automatically checks for extra output).

## Editorials

An editorial should be understandable to everyone expected to take part in the contest. So official editorials need to be more detailed than ordinary ones.

### About partial points

For problems with partial points, the editorial can also describe the solutions for the partial points.

### About topics

The topics used in the solution should be stated clearly. For topics whose difficulty is close to that of the problem, it is best to give learning material for the topic (e.g. a link to a blog post).

### About definitions

Concepts should not appear out of nowhere in an editorial.

For example, a DP editorial should clearly explain what the state means.

### About details

If an implementation detail is clever, it is best to write it out. Otherwise "see the code for details" is fine. If you say "see the code for details", it is best to add some comments to the code.

### Reference solution

It is best to remove redundant parts from the reference solution. For example, some editorials keep a full define template (with lots of defines and common functions to code faster, often used in online contests like CF), and most of it is never used. This is not good.

If some implementation details are not explained in the editorial, it is best to add a reasonable number of comments.

## Contests

### The difficulty stated in the contest announcement must be honest

> Remember that authors tend to underestimate the difficulty of their problems.
>
> —A reminder on the Codeforces PROPOSE A PROBLEM page

Setters can easily misjudge the difficulty of their problems. So if you state the contest difficulty in the announcement, think carefully. It is best to have others test the problems and evaluate them in advance.

### Distributing difficulty across problems

In mock contests styled after Chinese OI, it is usually enough that the overall difficulty of the three problems matches the contest's intended difficulty.

In online contests like CF/AtCoder, you should try to make the difficulty increase from problem to problem (though misjudged difficulty often makes this not quite achievable), and try to avoid big difficulty gaps. You can reduce a difficulty gap by splitting one problem into an easy and a hard version (two subtasks), but subtasks need careful thought. Many people dislike subtasks in the CF format ([Are subtasks evil?](https://codeforces.com/blog/entry/71700)), for reasons including but not limited to:

-   Due to the contest format, solving the easy version first and then the hard version may give less penalty and a higher total score
-   The points given to subtasks are often not proportional to their difficulty
-   Often the easy version is not a proper problem on its own (it is not interesting)
-   Often the solution to the easy version does not help in finding the intended solution to the hard version

### Distributing topics across problems

A contest should cover a broad range of topics (except, of course, contests for training on a specific topic).

Classic counterexample: CTS2019, which covered dynamic programming, expected value, combinatorial counting, the inclusion–exclusion principle, polynomials and other topics.

> I had to pick six problems out of five, I really had no choice.
>
> —The reason given by the CTS2019 problem selector, who did not receive enough problem submissions

## Problem-setting platforms

### Polygon

Polygon is a very powerful platform for setting problems collaboratively. It is the first choice for collaborative problem setting for any website (use the package feature to export to sites that do not support Polygon), and it is also a good choice when setting problems alone (especially across different devices). For how to use it, see [Introduction to Polygon](../tools/polygon.md).

### Codeforces

Codeforces is one of the world's best-known competitive programming websites, with high-quality problems. It is very suitable for setters who have some experience, want to improve further, and want to set a high-quality problemset. The downside is that review is slow (usually several months), but you can start preparing problems during the review (with the risk that a problem gets rejected and the preparation is wasted).

#### Eligibility to set problems

-   Blue rating and at least 25 rated contests;
-   Purple rating and at least 15 rated contests;
-   Orange rating and at least 5 rated contests;
-   Red rating or legendary (black-red) rating.

#### Submitting a contest proposal

Once you are eligible, you can see the [Propose a contest/problems](http://codeforces.com/proposals/new-contest) button in the sidebar.

Click it, first write a contest proposal (under PROPOSE A CONTEST), then write problem proposals and add them to the contest.

Once the problems are decided, you can mark the contest proposal "open to review" (submit it for review).

#### Preparing problems on Polygon

See [Introduction to Polygon](../tools/polygon.md).

#### Contacting the coordinators

Contacting the coordinators serves two purposes:

1.  Speeding up the review.
2.  Once preparation starts, the coordinators give advice and help.

The official way to contact them is to submit a request as a proposal in the proposal system. After a coordinator starts reviewing, discussion happens as comments below the proposal.

In practice, if your proposal has not been reviewed for a long time, you can consider messaging a coordinator privately (CF actually says "Don't send private messages or emails to coordinators", but 300iq said in a [comment](http://codeforces.com/blog/entry/64077#comment-478933) that you may message him privately).

### Comet OJ

[Comet OJ link](https://www.cometoj.com/)

No longer active (as of November 2021, the last contest was held in January 2020).

Problem-setting application: <https://info.cometoj.com/contests/Questionnaire_IssuerInfo/>

### CodeChef

An Indian competitive programming platform with three contest formats: Long Challenge, which lasts 10 days and includes a challenge problem; Cook-Off, a 2.5-hour ICPC-style contest; and LunchTime, a 3-hour IOI-style contest.

Problem setter FAQ: <https://www.codechef.com/wiki/faq-problem-setters>

Problem-setting guide: <https://www.codechef.com/problemsetting>

### AtCoder

A Japanese competitive programming platform. Contact for problem setting: <contest@atcoder.jp>.

### UOJ & LOJ

Chinese online judges that do not hold many contests.

### Luogu

Staff who set problems need a certain level of award certification. After creating a contest, the person in charge submits an application in the [ticket system](https://www.luogu.com.cn/ticket).

Rules for public contests: <https://help.luogu.com.cn/rules/academic/opencontest-standard>

## References

1.  [vfk, "The Origins of the UOJ Spirit"][1]

2.  [Wang Tianyi, "On the Harm of Off-Topic Problems"][2]

3.  [Notes for CF problem setters][3] ([image version accessible from China](https://github.com/OI-wiki/libs/blob/master/topic/rules.jpg))

4.  [Self-cultivation of a CF problem setter][4]

This article was moved here by the author from [ouuan's problem-setting guidelines](https://ouuan.github.io/post/ouuan-的出题规范/), with some changes and additions.

[1]: https://vfleaking.blog.uoj.ac/blog/909 "vfk, The Origins of the UOJ Spirit"

[2]: https://github.com/OI-wiki/libs/blob/master/topic/7-%E7%8E%8B%E5%A4%A9%E6%87%BF-%E8%AE%BA%E5%81%8F%E9%A2%98%E7%9A%84%E5%8D%B1%E5%AE%B3.ppt "Wang Tianyi, On the Harm of Off-Topic Problems"

[3]: https://docs.google.com/document/d/e/2PACX-1vRhazTXxSdj7JEIC7dp-nOWcUFiY8bXi9lLju-k6vVMKf4IiBmweJoOAMI-ZEZxatXF08I9wMOQpMqC/pub "Notes for CF problem setters"

[4]: https://github.com/OI-wiki/libs/blob/master/topic/CF%E5%87%BA%E9%A2%98%E4%BA%BA%E7%9A%84%E8%87%AA%E6%88%91%E4%BF%AE%E5%85%BB.md "Self-cultivation of a CF problem setter"
