author: Enter-tainer, Falicitas, HeRaNO, iamtwz, ImpleLee, Tiphereth-A, Xeonacid, Yanjun-Zhao

## Definition

Balanced ternary, also called symmetric ternary, is a non-standard positional numeral system.

Ordinary ternary numbers use the digits `0`, `1`, `2`, while balanced ternary uses the digits `-1`, `0`, `1`. Its base is also `3` (since there are three possible digit values). Since `-1` is awkward to write as a single digit, we use the letter `Z` in place of `-1`.

## Explanation

Here are a few examples:

| Decimal | Balanced ternary | Decimal | Balanced ternary |
| --- | ----- | --- | ----- |
| `0` | `0`   | `5` | `1ZZ` |
| `1` | `1`   | `6` | `1Z0` |
| `2` | `1Z`  | `7` | `1Z1` |
| `3` | `10`  | `8` | `10Z` |
| `4` | `11`  | `9` | `100` |

Negative numbers are easy to write in this system: just flip the digits of the positive number (`Z` becomes `1`, and `1` becomes `Z`).

| Decimal  | Balanced ternary |
| ---- | ----- |
| `-1` | `Z`   |
| `-2` | `Z1`  |
| `-3` | `Z0`  |
| `-4` | `ZZ`  |
| `-5` | `Z11` |

It is easy to see that the leading digit of a negative number is `Z`, and the leading digit of a positive number is `1`.

## Process

To convert a number `x` to balanced ternary, first write it in standard ternary. In standard ternary every digit is `0`, `1` or `2`. Go through the digits starting from the lowest. Skip any `0` or `1`. If you see a `2`, turn it into `Z` and add `1` to the next digit. If you see a `3`, turn it into `0` and add `1` to the next digit.

### Example 1

Convert `64` to balanced ternary.

First, write the number in standard ternary:

$$
\text 64_{10} = 02101_3
$$

Process the digits starting from the one with the smallest effect on the number (the lowest digit):

-   `101` is skipped (because `0` and `1` are allowed in balanced ternary);
-   `2` becomes `Z`, and the digit to its left gets `1` added, giving `1Z101`;
-   `1` is skipped, giving `1Z101`.

The final result is `1Z101`.

Let's convert it back to decimal:

$$
\texttt {1Z101}=81 \times 1 +27 \times (-1) + 9 \times 1 + 3 \times 0 + 1 \times 1 = 64_{10}
$$

### Example 2

Convert `237` to balanced ternary.

First, write the number in standard ternary:

$$
\text 237_{10} = 22210_3
$$

-   `0` and `1` are skipped (because `0` and `1` are allowed in balanced ternary);
-   `2` becomes `Z`, and the digit to its left gets `1` added, giving `23Z10`;
-   `3` becomes `0`, and the digit to its left gets `1` added, giving `30Z10`;
-   `3` becomes `0`, and the digit to its left (which is `0` by default) gets `1` added, giving `100Z10`;
-   `1` is skipped, giving `100Z10`.

The final result is `100Z10`.

Let's convert it back to decimal:

$$
\texttt{100Z10} = 243 \cdot 1 + 81 \cdot 0 + 27 \cdot 0 + 9 \cdot (-1) + 3 \cdot 1 + 1 \cdot 0 = 237_{10}
$$

## Properties

For a balanced ternary number $X_3$, multiplying each digit $x_i$ by its weight $3^i$ and adding up gives a unique decimal number $Y_{10}$.

But does each decimal number $Y_{10}$ **correspond to exactly one balanced ternary number**?

The answer is yes. This property is called the uniqueness of balanced ternary.

???+ note "Proof"
    We prove it **by contradiction**:
    
    Suppose that for some decimal number $Y_{10}$ there are two **different balanced ternary numbers**  $A_3,B_3$ that both equal $Y_{10}$ when converted to decimal. We need to show $A_3 = B_3$. Consider the cases:
    
    1.  If $Y_{10}=0$, clearly $A_3 = B_3 = 0_3$, which contradicts the assumption.
    2.  If $Y_{10}>0$:
    
        -   Number the digits of $A_3$ and $B_3$ from low to high. Let $a_i$ be the $i$-th digit of $A_3$ and $b_i$ the $i$-th digit of $B$. There must be some $i$ with $a_i\neq b_i$. Digits $i-1,i-2,\dots,0$ do not matter for the proof. So shift $A_3,B_3$ right by $i$ digits to get $A_3',B_3'$; the original problem is equivalent to proving $A_3'=B_3'$.
        -   For digit $0$ of $A_3',B_3'$, $a_0 \neq b_0$. Assume $b_0 > a_0$ (the case $a_0>b_0$ is the same). Then clearly $b_0 - a_0 \in \{1,2\}$. The digits $i=1,2,3,\dots$ of $A_3'$ contribute $S_1 = a_1 \times 3^1 + a_2 \times 3^2+ \dots$ to its value, and the digits $i=1,2,3,\dots$ of $B_3'$ contribute $S_2 = b_1 \times 3^1 + b_2 \times 3^2 + \dots$ to its value. Since $A_3' = B_3'$, we get $S_1 - S_2 = b_0 - a_0$. $S_1,S_2$ share the factor $3$, but $b_0 - a_0$ is not divisible by $3$, which contradicts the assumption. So $A_3'\neq B_3'$
    3.  If $Y_{10}<0$, the proof is the same as for $Y_{10}>0$.
    
    Therefore every decimal number $Y_{10}$ corresponds to exactly one balanced ternary number $X_3$.

## Exercises

[Topcoder SRM 604 PowerOfThree](https://archive.topcoder.com/ProblemStatement/pm/12917)

**Parts of this page are translated from the article [Троичная сбалансированная система счисления](http://e-maxx.ru/algo/balanced_ternary) and its English translation [Balanced Ternary](https://cp-algorithms.com/algebra/balanced-ternary.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
