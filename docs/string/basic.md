author: Ir1d, ouuan, qinggniq, i-Yirannn, minghu6

## Definitions

### Alphabet

An **alphabet** (character set) $\Sigma$ is a set with a [total order](../math/order-theory.md#偏序集) on it. That is, any two different elements $\alpha$ and $\beta$ of $\Sigma$ can be compared: either $\alpha<\beta$ or $\beta<\alpha$. The elements of the alphabet $\Sigma$ are called characters.

### String

A **string** $S$ is a sequence of $n\ (n\ge 0)$ characters placed one after another. $n$ is called the length of $S$ and is written $|S|$. In particular, when $n=0$, $S$ contains no characters. It is called the **empty string** and is written $\varepsilon$.

If string indices start from $1$, the $i$-th character of $S$ is written $S[i]$;

if string indices start from $0$, the $i$-th character of $S$ is written $S[i-1]$.

### Substring

A **substring** $S[i..j]$, $i≤j$, of a string $S$ is the part of $S$ from $i$ to $j$, that is, the string formed by $S[i],S[i+1],\ldots,S[j]$ in order.

Sometimes $S[i..j]$ with $i>j$ is also used to denote the empty string $\varepsilon$.

### Subsequence

A **subsequence** of a string $S$ is a sequence formed by taking some elements out of $S$ without changing their relative order, that is, $S[p_1],S[p_2],\ldots,S[p_k]$ with $1\le p_1< p_2<\cdots< p_k\le|S|$ and $k\ge 0$.

### Suffix

A **suffix** is a special substring that starts at some position $i$ and runs to the end of the string. The suffix of $S$ that starts at $i$ is written $\textit{Suffix(S,i)}$, that is, $\textit{Suffix(S,i)}=S[i..|S|-1]$.

A **proper suffix** is a suffix of $S$ other than $S$ itself.

For example, all suffixes of the string `abcabcd` are `{ε, d, cd, bcd, abcd, cabcd, bcabcd, abcabcd}`, and its proper suffixes are `{ε, d, cd, bcd, abcd, cabcd, bcabcd}`.

### Prefix

A **prefix** is a special substring that starts at the beginning of the string and ends at some position $i$. The prefix of $S$ that ends at $i$ is written $\textit{Prefix(S,i)}$, that is, $\textit{Prefix(S,i)}=S[0..i]$.

A **proper prefix** is a prefix of $S$ other than $S$ itself.

For example, all prefixes of the string `abcabcd` are `{ε, a, ab, abc, abca, abcab, abcabc, abcabcd}`, and its proper prefixes are `{ε, a, ab, abc, abca, abcab, abcabc}`.

### Lexicographic order

Compare two strings by using the $i$-th character as the $i$-th key. The empty character is smaller than every character in the alphabet (that is, $a< aa$).

### Palindrome

A **palindrome** is a string that reads the same forwards and backwards, that is, a string $s$ with $\forall 1\le i\le|s|, s[i]=s[|s|+1-i]$.

### Hamming distance

The **Hamming distance** is a distance between two strings of equal length. It is the number of positions at which the corresponding characters of the two strings differ.

A simple way to think about it: XOR the two strings, and the number of $1$s in the result is their Hamming distance.

## Storing strings

-   Store it in a `char` array and mark the end of the string with the null character `\0` (a C-style string).
-   Use the [`string` class](../lang/csl/string.md) from the C++ standard library.
-   A string constant can be written as a string literal (a string enclosed in double quotes).
