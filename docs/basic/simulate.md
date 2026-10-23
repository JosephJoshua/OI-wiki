This page gives a short introduction to simulation.

## Overview

Simulation means using a computer to carry out the operations a problem describes.

Simulation problems usually need a lot of code, involve many operations, and have complicated logic. Because there is so much code, bugs are often hard to find, and getting one wrong in a contest can waste a lot of time.

## Tips

When writing a simulation problem, following these suggestions may help you solve it faster:

-   Before you start coding, write down the process you need to implement on scratch paper in as much detail as you can.
-   In your code, split each part into modules as much as possible, as functions, structs, or classes.
-   For concepts that may come up repeatedly, convert them into one common form so they are easy to handle. For example, if a problem gives you times in the form "YY-MM-DD hour:minute", put the conversion into a function that turns them into seconds. This reduces confusion between different concepts.
-   Debug one piece at a time. The benefit of modular code is that you can easily debug one part on its own.
-   Keep a clear head while coding. Don't just write whatever comes to mind; follow the steps you wrote down on paper.

In fact, these steps are also very helpful for solving other kinds of problems.

## Worked example

???+ note "[Climbing Worm](https://open.kattis.com/problems/climbingworm)"
    A worm of negligible length is at the bottom of a well that is $n$ inches deep. Each time, it climbs up $u$ inches, but it must rest before it can climb again. While resting, it slides down $d$ inches. It then repeats climbing and resting. At least how many climbs does the worm need to get out of the well? If the worm reaches exactly the top of the well after a climb, we also count it as having gotten out.

??? note "Solution"
    The problem guarantees that the worm can get out, that is, $u\ge n$ or $u>d$. Under this condition, we can simply simulate it. Use a loop to repeat the worm's climbing process, and stop when the height climbed is greater than or equal to the depth of the well.

??? note "Reference code"
    === "C++"
        ```cpp
        --8<-- "docs/basic/code/simulate/simulate_1.cpp"
        ```
    
    === "Python"
        ```python
        --8<-- "docs/basic/code/simulate/simulate_1.py"
        ```
    
    === "Java"
        ```java
        --8<-- "docs/basic/code/simulate/simulate_1.java"
        ```

## Exercises

-   ["NOIP 2014" Rock-Paper-Scissors, Big Bang Edition - Universal Online Judge](https://uoj.ac/problem/15)
-   ["OpenJudge 3750" World of Warcraft](http://bailian.openjudge.cn/practice/3750/)
-   ["SDOI 2010" Pig Kingdom Kill - LibreOJ](https://loj.ac/problem/2885)
