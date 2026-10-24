author: StudyingFather, NachtgeistW, countercurrent-time, Ir1d, H-J-Granger, Chrogeek, sshwy, Suyun514, hsfzLZH1, CBW2007, Xeonacid, kawa-yoiko, Konano

Competitive programming has many different types of problems.

## Traditional problems

**Traditional problems** are currently the most common type of problem in competitive programming.

The contestant submits source code. The judge has prepared some input data and the matching output data in advance as test cases[^note1]. It compiles the submitted source code[^note2], makes the program read the input data, and compares the program's output with the prepared output to decide whether the program is correct. This kind of judging is called **black-box judging**[^note3].

Each test case usually also has a time limit and a memory limit.

The time limit is a limit on how long the program runs[^note4]. The contestant's program must not run longer than the given time limit on a test case.

The memory limit is a limit on how much memory the program uses. The maximum memory the contestant's program uses while running must not exceed the given memory limit.

After the program finishes normally, its output is compared with the test case's output. Usually the comparison ignores trailing newlines at the end of the file and trailing spaces at the end of lines, and then compares the full text. For some special problems, a [Special Judge](../tools/special-judge.md) is used for the comparison.

When this process is done, the judge gives different **verdicts**[^note5] depending on how the program ran:

-   Accepted (AC): the program is accepted.
-   Compile Error (CE): the program fails to compile.
-   Wrong Answer (WA): the program finishes normally, but its output doesn't match the test case's output.
-   Presentation Error (PE): the program finishes normally, but the output format doesn't meet the requirements[^note6].
-   Runtime Error (RE): the program terminates abnormally (its exit code is not zero).
-   Time Limit Exceeded (TLE): the program runs longer than the given time limit.
-   Memory Limit Exceeded (MLE): the maximum memory the program uses exceeds the given memory limit.
-   Output Limit Exceeded (OLE): the program prints more output than the maximum allowed.

In ICPC contests, your program must get AC on every test case of a problem for the problem to count as solved. In OI contests, getting AC on a test case is enough to get that test case's points[^note7].

## Output-only problems

**Output-only problems** are problems where you submit the answers directly. They usually give you the input files and ask you to submit an archive, a folder, or plain files containing `XXX1.out`, `XXX2.out`, `XXX3.out`…`XXXn.out`.

After you submit, the judge compares your answer files with the reference answers and gives you points based on how good your answers are and how much of the task you completed.

Since output-only problems don't run your program, they have no time or memory limits.

There are generally two ways to solve these problems:

-   Work them out by hand. This is simple and direct, but it's hopeless for large data.
-   Write a program to produce the answer files.

## Interactive problems

**Interactive problems** are problems where the contestant's program must interact with a judging program to complete a task. A common case is that the contestant's program sends queries to the judging program and gets responses. The judging program may restrict the queries, or adjust its answering strategy to force as many queries as possible, which makes these problems more varied.

For a more detailed explanation of interactive problems, see [Interactive problems](./interaction.md).

There are two main ways of interacting. Although they differ quite a bit technically, there is no real difference in the nature of the algorithms they test.

### STDIO interaction

STDIO interaction (standard I/O interaction) is how online platforms such as Codeforces and AtCoder do interaction, and it is also the standard in ICPC contests. Codeforces provides a shorter [explanation (in English)](https://codeforces.com/blog/entry/45307).

???+ note "Example problem [LOJ #559. "LibreOJ Round #9" ZQC's Maze](https://loj.ac/problem/559)"
    Please note the content added at the bottom.
    
    This is an interactive problem.
    
    You are in a dark maze made of $n \times m$ squares, and you need to reach the exit of the maze to complete the maze challenge.
    
    At the start, you are at the entrance of the maze, $(1,1)$, facing right. The exit is at $(n,m)$. Any two squares in the maze are connected by exactly one path. Two adjacent squares (up, down, left or right, i.e. 4-connected) are one unit of length apart. There may be a wall between two adjacent squares; walls are very thin compared with the squares, so their thickness is ignored. The boundary of the maze has walls everywhere, and every wall is connected to the boundary. The maze is completely dark, which means you can't get any information except about $(n,m)$.
    
    To avoid getting lost in the dark, each time you move you can only start from your current square and follow the wall on your left or right, keeping your left or right hand on the wall, so that the hand on the wall moves exactly one unit of length. Note that if there is no wall on the left or right side, you can't move along that side.
    
    After too long in the dark you will become afraid, so you need to get out of the maze as early as possible. If you don't get out within the step limit, the challenge fails.

For this kind of problem, the contestant just writes queries to standard output as usual, **flushes the output buffer**, and then reads the result from standard input. Only after the contestant's program flushes its output buffer can the judging program connected to it through a pipe (called the interactor) receive the data right away. In C/C++, `fflush(stdout)` and `std::cout << std::flush` do this (printing a newline with `std::cout << std::endl` also flushes the buffer automatically, but `std::cout << '\n'` doesn't); in Pascal it's `flush(output)`.

### Grader interaction

Grader interaction is common in international OI contests such as IOI and APIO (especially contests run on the CMS platform).

???+ note "Example problem [UOJ #206. [APIO2016] Gap](https://uoj.ac/problem/206)"
    There are $N$ strictly increasing non-negative integers $a_1,a_2,\cdots,a_N (0\leq a_1<a2<\cdots<a_N\leq 10^{18})$. You need to find the largest value among $a_{i+1}−a_i (0\leq i\leq N−1)$.
    
    Your program can't read this integer sequence directly, but it can query information about the sequence through the given function. For details of the query function, see the implementation details section below for the language you use.
    
    You need to implement a function that returns the maximum of $a_{i+1}−a_i (0\leq i\leq N−1)$.

For this kind of problem, the contestant only writes one specific function to complete some task, and it interacts by calling several given helper functions. To make local testing easier, the problem provides a header file and a sample judging program `grader.cpp` (for Pascal, a library `graderlib`). The contestant compiles their own program together with `grader.cpp` to get an executable.

```sh
g++ grader.cpp my_solution.cpp -o my_solution -Wall -O2
./my_solution   # run the program
```

The compiled program behaves like a program for a traditional problem. It opens a fixed file, reads the data in a fixed format, calls the function the contestant wrote, and prints the result and some information (for example, the number of queries and whether the answer is correct) to standard output.

During actual judging, the contestant's program is compiled with a different `grader.cpp`. This `grader.cpp` calls the contestant's function in a similar way and records the score. Usually all global symbols in this version of `grader.cpp` are made `static`, so you can't break it by using conflicting names. In any case, any attempt to get around the grader's restrictions leads to disqualification.

### Differences

An obvious advantage of STDIO interaction is that it supports any programming language. But the time spent on input and output easily becomes the bottleneck of the problem design, so sometimes the difference in time efficiency between programs can't be distinguished. Grader interaction is the opposite: since function calls are cheap, it often allows on the order of $10^6$ queries, but its weakness is the restriction on languages.

If you design problems or host a contest yourself, you need to weigh and compare the two carefully.

## Communication problems

**Communication problems** are problems where two contestant programs need to communicate and cooperate to complete a task. The first program receives the input of the problem and produces some output. The input of the second program is related to the output of the first (sometimes passed unchanged as a parameter, sometimes processed by the judge first), and it must produce the solution to the problem.

Examples of communication problems include [UOJ #178. New Year's Greeting Telegram](https://uoj.ac/problem/178), [#454. [UER #8] Snowball Fight](https://uoj.ac/problem/454), and so on.

How to test locally varies a lot depending on how the problem is set up. Common approaches include:

-   Typing the input by hand
-   Writing a helper program that converts the first program's output into the second program's input
-   Connecting the standard input/output of the two programs with a two-way pipe

Because judging platforms have limited support for communication problems, so far they have mostly appeared only in the IOI series and in contests hosted by a few online platforms such as UOJ. It is still an area waiting to be explored.

## Function-completion problems

**Function-completion problems** are problems where the contestant has to complete a program. You can think of them as interactive problems where the problem gives the contestant's code and asks you to write the helper functions.

They usually come in these forms:

-   You are given a program and told where the code block you complete will be inserted.
-   No program is given; instead, the input is passed as parameters of the function you submit.

This kind of problem is common on [LeetCode](https://leetcode.com/) and [PTA](https://pintia.cn/problem-sets).

## Other types

???+ note "Example problem [Quine](https://loj.ac/problem/4)"
    Write a program that prints its own source code.
    
    The code must contain at least ten visible characters.

This is a classic problem, but it is hard to support on most OJs.

??? note "Reference code"
    **Note**: the source code does not include the first line below (that is, `// clang-format off`).
    
    ```cpp
    // clang-format off
    #include<cstdio>
    
    char *s={"#include<cstdio>%cchar *s={%c%s%c};%cint main(){printf(s,10,34,s,34,10);return 0;}"};
    
    int main(){printf(s,10,34,s,34,10);return 0;}
    ```

## References and notes

[^note1]: Because of technical and resource limits, in most cases the test cases of a problem can't cover all data that fits the constraints.

[^note2]: For interpreted languages like Python, the interpreter runs the program directly.

[^note3]: In reality, judges are implemented in a much more complicated way; this is only a rough description of the judging process.

[^note4]: More precisely, it is usually the program's user-mode CPU time.

[^note5]: Most of these verdicts also apply to other types of problems.

[^note6]: Most judges count PE as WA.

[^note7]: Some test cases may give partial points. If the contestant completes part of the task on a test case, or the output is correct but not optimal, they can get a certain fraction of the points.
