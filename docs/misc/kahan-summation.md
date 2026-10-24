## Introduction

The **Kahan summation** algorithm, also called compensated summation, is an algorithm that **reduces the error when adding up a sequence of finite-precision floating-point numbers**. It does this mainly by keeping a separate variable that accumulates the error (usually named $c$).

The algorithm was found mainly by William Kahan in the 1960s. Since Ivo Babuška also came up with a similar algorithm independently, Kahan summation is also called Kahan–Babuška summation.

## Rounding error

In computer programs, we have to approximate real numbers with a finite number of digits. Most computers today use the floating-point numbers defined by [IEEE-754](https://en.wikipedia.org/wiki/IEEE_754) for this. A number like $\frac{1}{3}$ cannot be represented exactly with finitely many digits, so in IEEE-754 some of its digits must be rounded off (truncated). This **rounding error** (rounding off error) is a characteristic of floating-point computation.

In floating-point addition, commutativity holds but associativity does not. That is, $a+b = b+a$ but $(a+b)+c \neq a+(b+c)$. So when adding a sequence of floating-point numbers, we can add them one by one from left to right, or, keeping the original order, add them in pairs. The second method is somewhat slower and needs more memory, and is often used by the built-in summation functions of some languages, but its result is more accurate.

To get a more accurate floating-point sum, we use the Kahan summation algorithm.

When computing $S_{new}=S_{old}+a$ (where $a$ is a value from the sequence), define the value actually added to $S$ as $a_{eff}=S_{new}-S_{old}$. If $a_{eff}$ is larger than $a$, there was an upward rounding error; if $a_{eff}$ is smaller than $a$, there was a downward rounding error. The rounding error is defined as $E_{roundoff} = a_{eff} - a$. The value that corrects this rounding error is then $a-a_{eff}$, the negative of $E_{roundoff}$. Let $c$ be the variable that compensates for the lost low-order bits; then $c_{new} = c_{old} + (a - a_{eff})$.

## How it works

Kahan summation mainly uses a separate variable to accumulate the error. In the reference code below, $sum$ is the final sum that is returned. $c$ is the variable that compensates for the lost low-order bits (the part that was rounded off), and it is the essential variable of Kahan summation.

Because $sum$ is large and $y$ is small, the low-order digits of $y$ are lost. $(t - sum)$ cancels the high-order part of $y$, and subtracting $y$ then recovers the negative (the low-order part of $y$). So algebraically $c$ is always zero. In the next iteration, the lost low-order part is added back to $y$.

## Implementation

??? note "Reference code"
    ```cpp
    float kahanSum(vector<float> nums) {
      float sum = 0.0f;
      float c = 0.0f;
      for (auto num : nums) {
        float y = num - c;
        float t = sum + y;
        c = (t - sum) - y;
        sum = t;
      }
      return sum;
    }
    ```

## Exercises

In OI, Kahan summation is mainly a helper tool that gives results with smaller error.

???+ note "Example problem [CodeForces Contest 800 Problem A. Voltage Keepsake](https://codeforces.com/contest/800/problem/A)"
    There are $n$ devices used at the same time. Device $i$ uses $a_{i}$ units of power per second. The usage is continuous: in $\lambda$ seconds, the device uses $\lambda \times a_{i}$ units of power. Device $i$ currently stores $b_{i}$ units of power. Every device can store any amount of power. There is one charger that can be plugged into any single device. The charger adds $p$ units of power per second to the device. The charging is continuous: if a device is plugged in for $\lambda$ seconds, it gains $\lambda \times p$ units of power. You can switch which device is charging at any moment (including real-valued times), and switching takes no time. Find the maximum time you can use the devices before one of them reaches $0$ units of power.

???+ note "Example problem [CodeForces Contest 504 Problem B. Misha and Permutations Summation](https://codeforces.com/problemset/problem/504/B)"
    Define the sum of two permutations $p$ and $q$ of the numbers $0, 1, \cdots, (n - 1)$ as $Perm((Ord(p)+Ord(q))\bmod n!)$, where $Perm(x)$ is the $x$-th lexicographic permutation of $0, 1, \cdots, (n-1)$ (counting from zero), and $Ord(p)$ is the lexicographic index of the permutation $p$. For example, $Perm(0) = (0, 1, \cdots , n - 2, n - 1)$, $Perm(n! - 1) = (n - 1, n-2,\cdots, 1,0))$. Misha has two permutations $p$ and $q$; find their sum.

## Summation in programming languages

Python's standard library provides the exactly rounded summation function [fsum](https://docs.python.org/3/library/math.html#math.fsum), which returns an accurate floating-point sum of the values in an iterable. It avoids loss of precision by tracking multiple intermediate partial sums using Shewchuk's algorithm.

In Julia, the default implementation of the [sum](https://docs.julialang.org/en/v1/base/collections/#Base.sum) function uses pairwise summation, for high accuracy and good performance. The external library function [sum\_kbn](http://www.jlhub.com/julia/manual/en/function/sum_kbn) provides the Neumaier variant for cases that need higher accuracy; see [KahanSummation.jl](https://github.com/JuliaMath/KahanSummation.jl).

## References and notes

1.  [Kahan\_summation\_algorithm - Wikipedia](https://en.wikipedia.org/wiki/Kahan_summation_algorithm)
2.  [Kahan summation - Rosetta Code](https://rosettacode.org/wiki/Kahan_summation)
3.  [VK Cup Round 2 + Codeforces Round 409 Announcement](https://codeforces.com/blog/entry/51577)
4.  [Rounding off errors in Java - GeeksforGeeks](https://www.geeksforgeeks.org/rounding-off-errors-java/)
