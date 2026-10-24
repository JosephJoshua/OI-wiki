author: c-forrest, Enter-tainer, hhc0001, Ir1d, KingMario, ksyx, Lutra-Fs, MegaOwIer, niujiaxing, StudyingFather, Tiphereth-A, TOMWT-qwq, ZnPdCo

A **positional numeral system**, also called a **carry system**, **base system**, **positional notation** or **place-value notation**, is a numeral system that can represent every natural number with a finite set of symbols. The number of symbols a system uses is called its **radix** or **base**. A system with base $n$ is called base-$n$ ($n>1$). For example, the decimal system we use every day normally uses just the ten symbols `0, 1, 2, 3, 4, 5, 6, 7, 8, 9`. A carry is the operation "when a digit reaches the base, set it to 0 and add one to the next higher digit".

In general, a base-$n$ number is written as $(a_k\cdots a_1a_0)_n$, $(a_k\cdots a_1a_0)_{(n)}$, ${a_k\cdots a_1a_0}_{(n)}$, ${a_k\cdots a_1a_0}_{n}$ and so on. If the base is clear from context, the subscript can be dropped. Note that $a_k\cdots a_1a_0$ here is not a product of $k+1$ numbers but a sequence of digits.

A base-$k$ number $a_n\cdots a_1a_0$ has the value $a_nk^n+\cdots+a_1k^1+a_0k^0=\sum_{i=0}^n a_ik^i$. For a number $m$ whose base-$k$ representation is $a_n\cdots a_1a_0$, we have:

$$
\begin{array}{cc}
    a_0=m-q_0k,&q_0=f(m/k),\\
    a_1=q_0-q_1k,&q_1=f(q_0/k),\\
    \vdots&\vdots\\
    a_n=q_{n-1}-q_nk,&q_n=f(q_{n-1}/k)=0,\\
\end{array}
$$

where $f(x)=\lfloor x\rfloor$.

The base-$k$ representation of $n$ has length $\lceil\log_k (n+1)\rceil$.

We usually write fractions with a radix point "$.$"[^note4], negative numbers with a minus sign "$-$", and repeating decimals with a bar over the repeating part. To make long numbers easier to read, we can insert a separator every few digits (such as a space, $,$, or `'`); for example, $12~345$ means $12345$.

In computing, the most common bases are binary, octal and hexadecimal.

## Converting between bases

### From decimal to other bases

We use binary as the example here; other bases work the same way.

For the integer part, keep dividing the decimal number by $2$ until the quotient is $0$. Then read all the remainders from bottom to top; these are the digits of the binary integer part. For the fractional part, multiply it by $2$ and take the integer part of the result. Repeat with the new fractional part until the fractional part becomes $0$. Then read all the integer parts from top to bottom; these are the digits of the binary fractional part.

???+ example "Example"
    Convert $35.25$ to binary.
    
    Integer part:
    
    $$
    \begin{aligned}
        35/2&=17  &\dots 1,\\
        17/2&=8   &\dots 1,\\
        8/2&=4    &\dots 0,\\
        4/2&=2    &\dots 0,\\
        2/2&=1    &\dots 0,\\
        1/2&=0    &\dots 1.
    \end{aligned}
    $$
    
    Fractional part:
    
    $$
    \begin{aligned}
        0.25\times 2&=0.5  &\dots 0,\\
        0.5\times 2&=1     &\dots 1.
    \end{aligned}
    $$
    
    So $35.25 = (100011.01)_2$.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec"
    ```

### From other bases to decimal

Again we use binary as the example. To convert a binary number to decimal, multiply each digit by $2^i$ and add them up, where $i$ is the position of the digit, and the ones digit has position $0$.

???+ example "Example"
    Convert $(11010.01)_{2}$ to decimal.
    
    $$
    \begin{aligned}
        (11010.01)_{2}&=\phantom{+~}1\times 2^4+1\times 2^3+0\times 2^2+1\times 2^1+0\times 2^0\\
        &\phantom{=}+~0\times 2^{-1}+1\times 2^{-2} \\
                    &=26.25.
    \end{aligned}
    $$
    
    So $(11010.01)_2 = (26.25)_{10}$.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:to_dec"
    ```

### Converting between binary, octal and hexadecimal

One octal digit can be written as 3 binary digits (because $2^3 = 8$), and one hexadecimal digit can be written as 4 binary digits ($2^4 = 16$). The reverse works the same way.

## Method of complements

See also: [ones' complement and two's complement](../bit.md#integers-and-bit-sequences)

The **method of complements** represents negative numbers using positive numbers, so that subtraction can be done with the same algorithm, circuit or mechanism as addition of positive numbers. It is widely used in the design of calculators and computers to simplify their structure.

For an $n$-digit base-$b$ number $a$, its **radix complement** (called the $b$'s complement) is $b^n-a$, and its **diminished radix complement** (called the $(b-1)$'s complement) is $b^n-1-a$. In binary, the radix complement is called the two's complement, and the diminished radix complement is called the ones' complement. In decimal, the radix complement is called the ten's complement, and the diminished radix complement is called the nine's complement. Other bases follow the same pattern.

For $n$-digit base-$b$ numbers $x,y$, we can compute $x-y$ in the following ways (if the result has more than $n$ digits, drop the high digits):

1.  Take the diminished radix complement of $x$, $x'=b^n-1-x$, and compute $x'+y=b^n-1-x+y$. The diminished radix complement of this result is the answer.
2.  Take the diminished radix complement of $y$, $y'=b^n-1-y$, and compute $x+y'=b^n-1+x-y$. Adding one gives the answer.
3.  Take the radix complement of $x$, $x'=b^n-x$, and compute $x'+y=b^n-x+y$. The radix complement of this result is the answer.
4.  Take the radix complement of $y$, $y'=b^n-y$, and compute $x+y'=b^n+x-y$. This is the answer.

Also, for base-$k$ numbers, let $d=k-1$. Then $\cdots dd=:\overline{d}=\sum_{i=0}^{\infty} dk^i=-1$. So for an $n$-digit number $x$ whose radix complement has base-$k$ representation $a_{n-1}\cdots a_1a_0$, the expression $\overline{d}a_{n-1}\cdots a_1a_0$ equals $\sum_{i=0}^{n-1}a_ik^i+\sum_{i=n}^{\infty} dk^i=k^n-x+(-k^n)=-x$. This idea of "numbers with infinitely many digits" can be generalized to [**$p$-adic numbers**](https://en.wikipedia.org/wiki/P-adic_number).

There is also an interesting theorem about complements and repeating decimals:

???+ note "Midy's theorem"
    Let $a$ be a positive integer and $p$ a positive prime, and let the base-$b$ representation of $a/p$ be $0.\overline{a_1a_2\cdots a_l}$, where $l$ is the (shortest) period length. If $l$ is even[^note5], say $l=2k$, then $a_1a_2\cdots a_k$ is the diminished radix complement of $a_{k+1}a_{k+2}\cdots a_{2k}$, that is:
    
    -   $a_i+a_{i+k}=b$,
    -   $a_1a_2\cdots a_k+a_{k+1}a_{k+2}\cdots a_{2k}=b^k-1$.
    
    More generally, if $l$ has a nontrivial factor $k$, say $l=nk$, then $\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}$ is a multiple of $b^k-1$.

??? example "Example"
    For $1/19=0.\overline{052~631~578~947~368~421}=0.\overline{032~745}_{(8)}$, we have:
    
    -   $052~631~578+947~368~421=999~999~999$,
    -   $052+631+578+947+368+421=3\times 999$,
    -   $032_{(8)}+745_{(8)}=777_{(8)}$,
    -   $03_{(8)}+27_{(8)}+45_{(8)}=77_{(8)}$.

??? note "Proof"
    For $a,b,p,l,n,k$ as in the theorem, it is easy to see that $1\leq a<p$, $b>1$ and $(a,p)=(b,p)=1$.
    
    For integers $0\leq i<l$, let $f(i)=b^i\cdot a/p-\lfloor b^i\cdot a/p\rfloor$. Then
    
    $$
    0<f(i)=0.\overline{a_{i+1}a_{i+2}\cdots a_{nk}a_1a_2\cdots a_i}<1 \implies 0<pf(i)<p.
    $$
    
    Note that $pf(i)\in\mathbf{N}_+$ and $pf(i)\equiv ab^i\pmod p$, so $pf(i)=ab^i\bmod p$.
    
    Let $S_n=\sum_{i=0}^{n-1}f(ik)=\sum_{i=0}^{n-1}0.\overline{a_{ik+1}a_{ik+2}\cdots a_{nk}a_1a_2\cdots a_{ik}}$. We can "swap" digit blocks between these fractions (for example, $0.\overline{{\color{Orchid}{14}}{\color{RoyalBlue}{28}}{\color{YellowGreen}{57}}}+0.\overline{{\color{RoyalBlue}{28}}{\color{YellowGreen}{57}}{\color{Orchid}{14}}}+0.\overline{{\color{YellowGreen}{57}}{\color{Orchid}{14}}{\color{RoyalBlue}{28}}}=0.\overline{\color{Orchid}{141414}}+0.\overline{\color{RoyalBlue}{282828}}+0.\overline{\color{YellowGreen}{575757}}=0.\overline{\color{Orchid}{14}}+0.\overline{\color{RoyalBlue}{28}}+0.\overline{\color{YellowGreen}{57}}=14/99+28/99+57/99=1$), so
    
    $$
    \begin{aligned}
        S_n&=\sum_{i=0}^{n-1}0.\overline{a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}}\\
        &=\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}/\left(b^k-1\right),
    \end{aligned}
    $$
    
    and therefore
    
    $$
    pS_n=p\sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}/\left(b^k-1\right)= \sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right),
    $$
    
    which gives
    
    $$
    \sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}=\left(b^k-1\right)\frac{\sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right)}{p}.
    $$
    
    If $p\mid \left(b^k-1\right)$, note that
    
    $$
    \left(b^k-1\right)a/p=a_1a_2\cdots a_k.\overline{a_{k+1}a_{k+2}\cdots a_{nk}a_1a_2\cdots a_k}-0.\overline{a_{1}a_{2}\cdots a_{nk}},
    $$
    
    so $a_{k+1}a_{k+2}\cdots a_{nk}a_1a_2\cdots a_k=a_{1}a_{2}\cdots a_{nk}$, and hence $a_1a_2\cdots a_k=a_{k+1}a_{k+2}\cdots a_{2k}=\dots=a_{(n-1)k+1}a_{(n-1)k+2}\cdots a_{nk}$, that is, $0.\overline{a_1a_2\cdots a_l}=0.\overline{a_1a_2\cdots a_k}$. This contradicts the definition of $l$, so $p\nmid \left(b^k-1\right)$.
    
    Therefore there is a positive integer $c=\dfrac{\sum_{i=0}^{n-1} \left(ab^{ik}\bmod p\right)}{p}$ such that
    
    $$
    \sum_{i=0}^{n-1}a_{ik+1}a_{ik+2}\cdots a_{(i+1)k}=c\left(b^k-1\right).
    $$

???+ note "Corollary"
    For $b,n,k,p$ as above,
    
    $$
    \sum_{i=0}^{n-1} b^{ik}\equiv 0\pmod p.
    $$

## Generalized numeral systems

In a standard positional system, the base $b$ is always a fixed positive number, and each digit is chosen from $b$ different symbols to represent a non-negative number (ignoring the radix point and minus sign). In fact, many numeral systems share similar features but do not fully follow these rules. We call them **generalized numeral systems** or **non-standard positional numeral systems**. Below are some common ones.

### Bijective numeration

A standard positional system is not a bijection with the numbers it represents; for example, $1$, $01$ and $001$ all represent the same number[^note1]. A **bijective numeral system**, on the other hand, is a bijection with the numbers it represents.

Bijective base-$k$ ($k\geq 1$) uses the digit set $\{1,2,\dots,k\}$ to represent each number uniquely, by these rules:

1.  The empty string represents $0$;
2.  A non-empty string $a_n\cdots a_1a_0$ represents $a_nk^n+\cdots+a_1k^1+a_0k^0=\sum_{i=0}^n a_ik^i$.

For a positive number $m$ whose bijective base-$k$ representation is $a_n\cdots a_1a_0$, we have:

$$
\begin{array}{cc}
    a_0=m-q_0k,&q_0=f(m/k),\\
    a_1=q_0-q_1k,&q_1=f(q_0/k),\\
    \vdots&\vdots\\
    a_n=q_{n-1}-q_nk,&q_n=f(q_{n-1}/k)=0,\\
\end{array}
$$

where $f(x)=\lceil x\rceil-1$.

For example, Microsoft Excel's column labels use bijective base-$26$.

Bijective numeration includes the [unary system](https://en.wikipedia.org/wiki/Unary_numeral_system). In unary, a non-empty string consists only of $1$s, and its length is the number it represents.

Similar to the discussion under [method of complements](#method-of-complements), in bijective base-$k$ with $k>1$, let $d=k-1$. Then $\cdots dd=:\overline{d}=\sum_{i=0}^{\infty} dk^i=-1$, and so $\overline{d}k=0$. So if the bijective base-$k$ representation of $x$ is $a_{n-1}\cdots a_1a_0$, then $\overline{d}ka_{n-1}\cdots a_1a_0$ represents $-x$.

Here are some properties of bijective base-$k$ numbers:

-   There are $k^l$ numbers of length $l\geq 0$.
-   For $k\geq 2$, the bijective base-$k$ representation of $n$ has length $\lfloor\log_k (n+1)(k-1)\rfloor$.
-   For $k\geq 2$, if the base-$k$ representation of $n$ contains no $0$, then its base-$k$ and bijective base-$k$ representations are the same.

Converting bijective base-$k$ to decimal uses the same code as converting base-$k$ to decimal. Below is a reference implementation for converting decimal to bijective base-$k$.

???+ note "Implementation"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec_bi"
    ```

### Signed-digit representation

Some positional systems allow negative digits, such as [balanced ternary](./balanced-ternary.md).

### Gray code

Main article: [Gray code](./gray-code.md)

Gray code, also called **cyclic binary code** or **reflected binary code** (RBC), is a special binary numeral system often used for error checking.

### Non-positive bases

We know that a base-$k$ number $a_n\cdots a_1a_0$ has the value $\sum_{i=0}^n a_ik^i$. With a small change, we can define a base-$(-k)$ number ${a_n\cdots a_1a_0}_{(-k)}$ to mean $\sum_{i=0}^n a_i(-k)^i$, where $a_n,\dots,a_1,a_0\in \{0,1,\dots,k-1\}$. For example, $12345_{(-10)}=8265_{(10)}$. This is called a [**negative-base system**](https://en.wikipedia.org/wiki/Negative_base).

Similarly, we can define a [**complex-base system**](https://en.wikipedia.org/wiki/Complex-base_system), such as the [**base-$2\mathrm{i}$ system**](https://en.wikipedia.org/wiki/Quater-imaginary_base) (quater-imaginary base, quater-imaginary numeral system). We can also define a [**non-integer base of numeration**](https://en.wikipedia.org/wiki/Non-integer_base_of_numeration) to represent real numbers as **$\beta$-expansions**, and so on.

### Mixed radix

In a standard positional system, every digit has the same base. A mixed-radix system lets each digit have a different base. The most common use of mixed radix is timekeeping: hours use base $24$, while minutes and seconds use base $60$.

In base $b$, $a_n\cdots a_1a_0$ represents $\sum_{i=0}^n a_ib^i$. In a mixed-radix system, it represents $\sum_{i=0}^n a_i\prod_{j=0}^{i-1}b_j$, where $b_j$ is the base of digit $a_j$.

In competitive programming, the most common mixed-radix system is the [**factorial number system**](https://en.wikipedia.org/wiki/Factorial_number_system). A number in it can be written ${a_n\cdots a_1a_0}_{~!}$ and represents $\sum_{i=0}^na_i i!$[^note2]. For its uses in competitive programming, see [Lehmer code / Cantor expansion](../permutation.md#rank).

???+ note "Implementation (decimal to factorial base)"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:from_dec_factorial"
    ```

???+ note "Implementation (factorial base to decimal)"
    ```cpp
    --8<-- "docs/math/code/base/base_1.cpp:to_dec_factorial"
    ```

## Implementation in C++

For non-negative numbers, C++ writes an integer literal as `<prefix><digits><suffix>`, where `<digits>` and `<suffix>` may both be empty. `<suffix>` gives the type of the literal; for example, `u` or `U` means the literal is `unsigned`, and `l` or `L` means it is `long`. For `<prefix>`:

-   If `<prefix>` is `0x` or `0X`, the literal is hexadecimal, and the characters in `<digits>` must be chosen from `0, 1, 2, 3, 4, 5, 6, 7, 8, 9, a, A, b, B, c, C, d, D, e, E, f, F`. For example, `0x1234ABCD` is $\text{1234ABCD}_{(16)}=305~441~741$;
-   If `<prefix>` is `0`, the literal is octal, and the characters in `<digits>` must be chosen from `0, 1, 2, 3, 4, 5, 6, 7`. For example, `01234567` is $1234567_{(8)}=342391$;[^note3]
-   If `<prefix>` is `1`, `2`, `3`, `4`, `5`, `6`, `7`, `8` or `9`, the literal is decimal, and the characters in `<digits>` must be chosen from `0, 1, 2, 3, 4, 5, 6, 7, 8, 9`;
-   Since C++14, if `<prefix>` is `0b` or `0B`, the literal is binary, and the characters in `<digits>` must be chosen from `0, 1`. For example, `0b11001010` is $11001010_{(2)}=202$.

## References and notes

-   [Positional notation - Wikipedia](https://en.wikipedia.org/wiki/Positional_notation)
-   [Method of complements - Wikipedia](https://en.wikipedia.org/wiki/Method_of_complements)
-   [Non-standard positional numeral systems - Wikipedia](https://en.wikipedia.org/wiki/Non-standard_positional_numeral_systems)
-   [Bijective numeration - Wikipedia](https://en.wikipedia.org/wiki/Bijective_numeration)
-   [Midy's theorem - Wikipedia](https://en.wikipedia.org/wiki/Midy%27s_theorem)
-   [N3472 - Binary Literals in the C++ Core Language](https://www.open-std.org/jtc1/sc22/wg21/docs/papers/2012/n3472.pdf)

[^note1]: The zeros before the highest non-zero digit are called [**leading zeros**](https://en.wikipedia.org/wiki/Leading_zero). Similarly, we can define [**trailing zeros**](https://en.wikipedia.org/wiki/Trailing_zero).

[^note2]: The base of $a_i$ is $i+1$, and $0\leq a_i\leq i$. Note that $(n+1)!-n!=n\cdot n!$, so the factorial-base representation of a number is unique once leading zeros are removed.

[^note3]: `0` itself is an octal literal.

[^note4]: Some regions use "$,$" as the decimal point.

[^note5]: For $a=1$, the primes satisfying this condition in decimal form the sequence [A028416](https://oeis.org/A028416).
