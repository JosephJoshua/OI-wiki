author: minghu6

Prerequisites: [Prefix function and the KMP algorithm](./kmp.md).

The KMP algorithm squeezes everything it can out of prefix matching.

The basic idea behind the BM algorithm is to match suffixes instead, which gives more information than prefix matching and allows faster jumps over characters.

## Introduction

Imagine placing our pattern string $pat$ at the left end of the text string $string$, so that their first characters line up.

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\texttt{EXAMPLE} \\
\textit{string}:\qquad\quad &\texttt{HERE IS A SIMPLE EXAMPLE} \dots \\
&\qquad\ \ \ \, \, \Uparrow
\end{aligned}
$$

We define the following here and use them throughout:

The length of $pat$ is $patlen$. In particular, for 0-indexed strings, $patlastpos=patlen-1$ is the position of the last character of $pat$;

the length of $string$ is $stringlen$, and $stringlastpos = stringlen-1$.

Suppose we know the $patlen$-th character $char$ of $string$ (the one lined up with the last character of $pat$). Let us see what information it gives us:

### Observation 1

If we know that the character $char$ does not appear in $pat$, we do not need to consider $pat$ occurring at the 1st, 2nd, ..., $patlen$-th character of $string$. We can slide $pat$ down by $patlen$ characters right away.

### Observation 2

More generally, **if the last (rightmost) occurrence of the character $char$ in $pat$ is $delta_1$ characters away from the end**,

then we can slide $pat$ forward by $delta_1$ characters without matching anything: if we slide by less than $delta_1$, the character $char$ alone cannot match, so of course the pattern $pat$ cannot match either.

So unless $char$ matches the last character of $pat$, $string$ should skip $delta_1$ characters (the same as sliding $pat$ forward by $delta_1$ characters). This gives a function $delta_1(char)$ that computes $delta_1$:

$$
\begin{array}{ll}
\textbf{int}\ delta1(\textbf{char}\ char) \\
\qquad \textbf{if}\ \text{char is not in pat || char is the last character of pat} \\
\qquad\qquad\textbf{return}\ patlen \\
\qquad \textbf{else} \\
\qquad\qquad\textbf{return}\ patlastpos-i\quad\textbf{//}\ \text{i is the position of the last occurrence of char in pat, i.e. pat[i]=char}
\end{array}
$$

Note that this table clearly only needs to be computed up to position $patlastpos-1$.

Now suppose $char$ matches the last character of $pat$. Then we check whether the character before $char$ matches the second-to-last character of $pat$:

If it does, we keep moving back until the whole pattern $pat$ matches (then we have found a match of $pat$ in $string$);

or, after matching the last $m$ characters of $pat$, we may get a mismatch at the $(m+1)$-th character from the end. Then we want to slide $pat$ forward to the next position where a match is possible, and of course we want to slide as far as we can.

### Observation 3(a)

As mentioned in **Observation 2**, after matching the last $m$ characters of $pat$, if there is a mismatch at the $(m+1)$-th character from the end, then to line up the mismatched character in $string$ with the corresponding character of $pat$,

we need to slide $pat$ forward by $k$ characters. That means we should move our attention $k+m$ characters ahead (to the character of $string$ lined up with the end of $pat$ after sliding by $k$).

Since $k=delta_1-m$,

our attention should jump $delta_1-m+m = delta_1$ characters ahead along $string$.

However, we may be able to skip even more characters. Read on.

### Observation 3(b)

Suppose we know that the next $m$ characters of $string$ match the last $m$ characters of $pat$. Call this substring $subpat$.

We also know that the mismatched character $char$ in $string$ is followed by a substring matching $subpat$. If $subpat$ also appears in $pat$ before the position corresponding to the mismatched character, we can slide $pat$ down some distance,

so that this earlier $subpat$ in $pat$ (a plausible reoccurrence, abbreviated pr below) lines up with the $subpat$ in $string$. If $pat$ contains several such $subpat$, following the right-to-left order of suffix matching, take the first one (the rightmost plausible reoccurrence, abbreviated rpr below).

Suppose $pat$ now slides down by $k$ characters (the distance between the $subpat$ at the end of $pat$ and its rightmost plausible reoccurrence). Then our attention should move $k+m$ characters ahead along $string$. We call this distance $delta_2(j)$:

Let $rpr(j)$ be the position of the rightmost plausible reoccurrence of $subpat=pat[j+1\dots patlastpos]$ when the mismatch happens at $pat[j]$, with $rpr(j) < j$ (this is only a simple definition; the algorithm design section below discusses it more precisely). Then clearly $k=j-rpr(j),\ m=patlastpos-j$.

So we have:

$$
\begin{array}{ll}
\textbf{int}\ delta2(\textbf{int}\ j) \quad\textbf{//}\ \text{j is the position in pat matched against the mismatched character} \\
\qquad\qquad\textbf{return}\ patlastpos-rpr(j) \\
\end{array}
$$

So on a mismatch, we can move our attention on $string$ forward by $\max(delta_1,delta_2)$ characters.

## Process

The arrow points to the mismatched character $char$:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \, \, \Uparrow
\end{aligned}
$$

$\texttt{F}$ does not appear in $pat$. By **Observation 1**, $pat$ moves down by $patlen$ characters, that is, 7 characters:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\quad\ \ \, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \, \, \qquad\quad\ \ \ \Uparrow
\end{aligned}
$$

By **Observation 2**, we need to move $pat$ down by 4 characters to line up the hyphens:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\quad\ \ \, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad \Uparrow
\end{aligned}
$$

Now *char*: $\texttt{T}$ matches, so we move the pointer on $string$ one step left and keep matching:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\quad\ \ \, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\quad\ \, \Uparrow
\end{aligned}
$$

By **Observation 3(a)**, $\texttt{L}$ is a mismatch. Since $\texttt{L}$ is not in $pat$, $pat$ moves down by $k=delta_1-m=7-1=6$ characters, and the pointer on $string$ moves down by $delta_1=7$ characters:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\qquad\qquad\ \ \,\, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad\qquad\ \ \ \, \, \Uparrow
\end{aligned}
$$

Now $char$ again matches the last character $\texttt{T}$ of $pat$. The pointer on $string$ moves left and matches $\texttt{A}$, then moves left again and finds a mismatch at the character $\texttt{-}$:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\qquad\qquad\ \ \,\, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad\quad\ \ \ \,\, \Uparrow
\end{aligned}
$$

Intuitively, by **Observation 3(b)**, we move $pat$ down by $k=5$ characters so that the suffix $\texttt{AT}$ lines up. This slide gives the largest move of the pointer on $string$: $delta_2=k+patlastpos-j=5+6-4=7$, so the pointer on $string$ slides down by 7 characters.

Formally, at this point $delta_1=7-1-2=4,\ delta_2=7, \max(delta_1,delta_2)= 7$,
which formally supports the jump from **Observation 3(b)**:

$$
\begin{aligned}
\textit{pat}:\qquad\qquad &\qquad\qquad\qquad\qquad\qquad\quad \;\, \texttt{AT-THAT} \\
\textit{string}:\ \ \ \dots\ &\texttt{WHICH-FINALLY-HALTS.--AT-THAT-POINT} \dots \\
&\qquad\ \ \ \; \qquad\qquad\qquad\qquad\qquad\quad \ \ \; \Uparrow
\end{aligned}
$$

Now every character of $pat$ equals the corresponding character of $string$, so we have found a match of $pat$ in $string$. It took only 14 accesses to $string$: 7 of them are the comparisons needed for any successful match ($patlen=7$), and the other 7 let us skip 22 characters.

## Algorithm design

### The original matching algorithm

#### Explanation

Here is a string matching algorithm that uses $delta_1$ and $delta_2$:

$$
\begin{array}{ll}
i \gets patlastpos. \\
j \gets patlastpos. \\
\textbf{loop}\\
\qquad \textbf{if}\ j < 0 \\
\qquad \qquad \textbf{return}\ i+1 \\
\\
\qquad \textbf{if}\ string[i]=pat[j] \\
\qquad \qquad j \gets j-1 \\
\qquad \qquad i \gets i-1 \\
\qquad \qquad \textbf{continue} \\
\\
\qquad i \gets i+max(delta_1(string[i]), delta_2(j)) \\
\\
\qquad \textbf{if}\ i > stringlastpos \\
\qquad \qquad \textbf{return}\ false \\
\qquad j \gets patlastpos \\
\end{array}
$$

If the algorithm above returns $\textbf{return}\ false$, $pat$ is not in $string$. If it returns a number, that is the position of the first (leftmost) occurrence of $pat$ in $string$.

Now let us describe more carefully the function $rpr(j)$ that $delta_2$ relies on.

By the definition above, $rpr(j)$ is the position of the rightmost plausible reoccurrence of the substring $subpat=pat[j+1\dots patlastpos]$ before $pat[j]$, when the mismatch happens at $pat(j)$.

That is, we need to find the best $k$ such that $pat[k\dots k+patlastpos-j-1]=pat[j+1\dots patlastpos]$. There are also two special cases to consider:

1.  When $k<0$, it is as if a virtual prefix were added in front of $pat$. This is still consistent with the principle of the $delta_2$ jump.
2.  When $k>0$, if $pat[k-1]=pat[j]$, then this $pat[k\dots k+patlastpos-j-1]$ cannot be a plausible reoccurrence of $subpat$.
    The reason is that $pat[j]$ is the mismatched character, so after sliding $pat$ down by $k$ characters, suffix matching would still fail at $pat[k-1]$.

There are also two constraints to note:

1.  $k < j$. When $k=j$, we have $pat[k]=pat[j]$, and a character that mismatches $pat[j]$ also mismatches $pat[k]$.
2.  Since $delta_2(patlastpos)= 0$, we define $rpr(patlastpos) = patlastpos$.

#### Process

Understanding $rpr(j)$ is the core of implementing the Boyer–Moore algorithm, so we go through two examples in detail:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8} \\
\textit{pat}:\qquad\qquad\ \  &\texttt{A B C X X X A B C} \\
\textit{rpr(j)}:\qquad\quad\  \  &\texttt{5 4 3 2 1 0 2 1 8} \\
\textit{sgn}:\qquad\qquad\ \   &\texttt{- - - - - - - - +}
\end{aligned}
$$

For $rpr(0)$, $subpat$ is $\texttt{BCXXXABC}$. The rightmost plausible reoccurrence before $pat[0]$ can only be $\texttt{[(BCXXX)ABC]XXXABC}$, so the position of the rightmost plausible reoccurrence is -5, that is, $rpr(j)=-5$;

For $rpr(1)$, $subpat$ is $\texttt{CXXXABC}$. The rightmost plausible reoccurrence before $pat[1]$ is $\texttt{[(CXXX)ABC]XXXABC}$, so $rpr(j)=-4$;

For $rpr(2)$, $subpat$ is $\texttt{XXXABC}$. The rightmost plausible reoccurrence before $pat[2]$ is $\texttt{[(XXX)ABC]XXXABC}$, so $rpr(j)=-3$;

For $rpr(3)$, $subpat$ is $\texttt{XXABC}$. The rightmost plausible reoccurrence before $pat[3]$ is $\texttt{[(XX)ABC]XXXABC}$, so $rpr(j)=-2$;

For $rpr(4)$, $subpat$ is $\texttt{XABC}$. The rightmost plausible reoccurrence before $pat[4]$ is $\texttt{[(X)ABC]XXXABC}$, so $rpr(j)=-1$;

For $rpr(5)$, $subpat$ is $\texttt{ABC}$. The rightmost plausible reoccurrence before $pat[5]$ is $\texttt{[ABC]XXXABC}$, so $rpr(j)=0$;

For $rpr(6)$, $subpat$ is $\texttt{BC}$. Since $string[0]=string[6]$, that is, $string[0]$ equals the mismatched character $string[6]$, $string[0\dots 2]$ is not a valid plausible reoccurrence of $subpat$. So the rightmost plausible reoccurrence is $\texttt{[(BC)]ABCXXXABC}$, and $rpr(j)=-2$;

For $rpr(7)$, $subpat$ is $\texttt{C}$. In the same way, since $string[7]=string[1]$, $string[1\dots 2]$ is not a valid plausible reoccurrence of $subpat$. The rightmost plausible reoccurrence is $\texttt{[(C)]ABCXXXABC}$, so $rpr(j)=-1$;

For $rpr(8)$, by the definition of $delta_2$, $rpr(patlastpos)=patlastpos$, so $rpr(8)=8$.

Now look at another example:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8} \\
\textit{pat}:\qquad\qquad\ \ &\texttt{A B Y X C D E Y X} \\
\textit{rpr(j)}:\qquad\quad\  \  &\texttt{8 7 6 5 4 3 2 1 8} \\
\textit{sgn}:\qquad\qquad\ \   &\texttt{- - - - - - + - +}
\end{aligned}
$$

For $rpr(0)$, $subpat$ is $\texttt{BYXCDEYX}$. The rightmost plausible reoccurrence before $pat[0]$ can only be $\texttt{[(BYXCDEYX)]ABYXCDEYX}$, so the position of the rightmost plausible reoccurrence is -8, that is, $rpr(j)=-8$;

For $rpr(1)$, $subpat$ is $\texttt{YXCDEYX}$. The rightmost plausible reoccurrence before $pat[1]$ can only be $\texttt{[(YXCDEYX)]ABYXCDEYX}$, so $rpr(j)=-7$;

For $rpr(2)$, $subpat$ is $\texttt{XCDEYX}$. The rightmost plausible reoccurrence before $pat[2]$ can only be $\texttt{[(XCDEYX)]ABYXCDEYX}$, so $rpr(j)=-6$;

For $rpr(3)$, $subpat$ is $\texttt{CDEYX}$. The rightmost plausible reoccurrence before $pat[3]$ can only be $\texttt{[(CDEYX)]ABYXCDEYX}$, so $rpr(j)=-5$;

For $rpr(4)$, $subpat$ is $\texttt{DEYX}$. The rightmost plausible reoccurrence before $pat[4]$ can only be $\texttt{[(DEYX)]ABYXCDEYX}$, so $rpr(j)=-4$;

For $rpr(5)$, $subpat$ is $\texttt{EYX}$. The rightmost plausible reoccurrence before $pat[5]$ can only be $\texttt{[(EYX)]ABYXCDEYX}$, so $rpr(j)=-3$;

For $rpr(6)$, $subpat$ is $\texttt{YX}$. Since $string[2\dots 3]=string[7\dots 8]$ and $string[6]\neq string[1]$, the rightmost plausible reoccurrence before $pat[6]$ is $\texttt{AB[YX]CDEYX}$, so $rpr(j)=2$;

For $rpr(7)$, $subpat$ is $\texttt{X}$. Although $string[3]=string[8]$, we also have $string[2] = string[7]$, so the rightmost plausible reoccurrence before $pat[7]$ is $\texttt{[X]ABYXCDEYX}$, and $rpr(j)=-1$;

For $rpr(8)$, by the definition of $delta_2$, $rpr(patlastpos)=patlastpos$, so $rpr(8)=8$.

### An improvement to the matching algorithm

Finally, in practice, an estimated 80% of the search time is spent on the jumps from **Observation 1**: $string[i]$ does not match $pat[patlastpos]$, and we jump a whole $patlen$ to the next attempt.

So we can optimize this case specially:

We define $delta0$:

$$
\begin{array}{ll}
\textbf{int}\ delta0(\textbf{char}\ char) \\
\qquad \textbf{if}\ char=pat[patlastpos] \\
\qquad\qquad \textbf{return}\ large\ \ \text{// large is an integer with large>stringlastpos+patlen} \\
\qquad \textbf{return}\ delta1(char)
\end{array}
$$

Replacing $delta_1$ with $delta0$ gives the improved matching algorithm:

$$
\begin{array}{ll}
i \gets patlastpos \\
\textbf{loop} \\
\qquad\textbf{if} \ i > stringlastpos \\
\qquad\qquad\textbf{return}\ false\\
\\
\qquad\textbf{while}\ i < stringlen \\
\qquad\qquad i \gets i+delta0(string(i)) \ \ \text{// unless string[i] matches the last character of pat, slide by at most patlen }\\\
\qquad\textbf{if}\ i \leqslant\ large \qquad\qquad\qquad\qquad \text{// no character of string matched the last character of pat}\ \\
\qquad\qquad\textbf{return}\ false\\
\\
\qquad i \gets i-large \\
\qquad j \gets patlastpos. \\
\qquad\textbf{while}\ j \geqslant\ 0 \ and \  string[i]=pat[j]\\
\qquad \qquad j \gets j-1 \\
\qquad \qquad i \gets i-1 \\
\\
\qquad \textbf{if}\ j < 0 \\
\qquad \qquad \textbf{return}\ i+1 \\
\qquad i \gets i+max(delta_1(string[i]), delta_2(j)) \\
\\
\end{array}
$$

Here $large$ plays several roles. First, like the Horspool algorithm introduced later, it allows fast bad-character jumps. Second, it helps detect whether the search is finished.

With this improvement, the jumps from **Observation 1** no longer need the extra computation of $delta_2$ each time, which noticeably speeds up string search over ordinary alphabets.

## Building delta2 in detail

### Introduction

In the October 1977 issue of *Communications of the ACM*, the paper by Boyer and Moore[^bm] only described the static table for $delta_2$,

and the details of how to build $delta_2$ were discussed in the KMP paper[^kmp] that Knuth, Morris and Pratt jointly published in *SIAM Journal on Computing* in June 1977.

### Naive algorithm

Before introducing Knuth's algorithm for building $delta_2$, here is a naive algorithm that follows directly from the definition and works for small inputs:

1.  For each position `i` in the range `[0, patlen)`, determine the range of possible reoccurrence positions from the length of `subpat`, namely `[-subpatlen, i]`;
2.  Compare the possible reoccurrence positions character by character from right to left, and find the rightmost reoccurrence of $subpat$ that meets the requirements of $delta_2$;
3.  Finally, do not forget to set $delta_2(lastpos)= 0$.

???+ note "Implementation"
    ```Rust
    use std::cmp::PartialEq;
    
    pub fn build_delta_2_table_naive(p: &[impl PartialEq]) -> Vec<usize> {
        let patlen = p.len();
        let lastpos = patlen - 1;
        let mut delta_2 = vec![];
        
        for i in 0..patlen {
            let subpatlen = (lastpos - i) as isize;
            
            if subpatlen == 0 {
                delta_2.push(0);
                break;
            }
            
            for j in (-subpatlen..(i + 1) as isize).rev() {
                // subpat matches
                if (j..j + subpatlen)
                .zip(i + 1..patlen)
                .all(|(rpr_index, subpat_index)| {
                    if rpr_index < 0 {
                        return true;
                    }
                    
                    if p[rpr_index as usize] == p[subpat_index] {
                        return true;
                    }
                    
                    false
                })
                && (j <= 0 || p[(j - 1) as usize] != p[i])
                {
                    delta_2.push((lastpos as isize - j) as usize);
                    break;
                }
            }
        }
        
        delta_2
    }
    ```

Here are some necessary notes on Rust language features, which also apply to later code:

-   `usize` and `isize` are unsigned and signed integers with the same number of bytes as a memory pointer. On a 32-bit machine they are `u32` and `i32`; on a 64-bit machine they are `u64` and `i64`.
-   Arrays, vectors and slices are indexed with `usize` values (since this is random memory access and indices cannot be negative). So when we need negative values we use `isize`, but when indexing we must use `usize`. That is why you see the `as` keyword used for explicit conversion between the two.
-   `impl PartialEq` is just used for generics, so the code supports both `Unicode` `char` and binary `u8`.

Clearly, the time complexity of this brute-force algorithm is $O(n^3)$.

### Efficient algorithm

Next we introduce an efficient algorithm with $O(n)$ time complexity, which needs $O(n)$ extra space.

Knuth proposed this construction in 1977, but his original version had a flaw: for some $pat$ it does not produce a $delta_2$ that matches the definition.

Rytter fixed this in a paper[^rytter] published in *SIAM Journal on Computing* in 1980. Here is the algorithm for building $delta_2$:

First, since the definition of $delta_2$ is fairly complicated, we classify by where $subpat$ reoccurs and handle each class separately. This is the key idea behind an efficient implementation.

From the farthest reoccurrence to the nearest, that is, from the largest offset to the smallest, the classes are:

1.  The whole reoccurrence of $subpat$ lies completely to the left of $pat$, for example $\texttt{[(EYX)]ABYXCDEYX}$. Here $delta_2(j) = patlastpos\times 2 - j$;

2.  Part of the reoccurrence of $subpat$ lies to the left of $pat$, and part of it is the head of $pat$, for example $\texttt{[(XX)ABC]XXXABC}$. Here $patlastpos < delta_2(j) < patlastpos\times 2 - j$;
    We also put the boundary case where $subpat$ lies entirely at the head of $pat$ in this class (depending on the implementation, it could also go in the next class), for example $\texttt{[ABC]XXXABC}$. Here $patlastpos = delta_2(j)$;

3.  The reoccurrence of $subpat$ lies completely inside $pat$, for example $\texttt{AB[YX]CDEYX}$. Here $delta_2(j) < patlastpos$.

Now let us discuss how to compute these three cases efficiently:

#### Case 1

This is the simplest case. It takes only one pass, and we can initialize $delta_2$ at the same time.

#### Case 2

When does the reoccurrence of $subpat$ lie partly to the left of $pat$ and partly at the head of $pat$? It happens when some suffix of $subpat$ equals some prefix of $pat$.

Take the earlier example:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8} \\
\textit{pat}:\qquad\qquad\ \  &\texttt{A B C X X X A B C} \\
\end{aligned}
$$

For the reoccurrence $\texttt{[(XX)ABC]XXXABC}$ of $delta_2(3)$, a suffix of $subpat$ $\texttt{XXABC}$ equals a prefix of pat, namely $\texttt{ABC}$.

In fact, the key to computing both case 2 and case 3 is computing and using the prefix function.

As long as $j$ is chosen so that $subpat$ contains this equal suffix, we get a case-2 reoccurrence of $subpat$. In the example, we just need $j \leqslant 5$,

and when $j = 5$, it is the boundary case where $subpat$ lies entirely at the head of $pat$.

We can compute $delta_2(j)$ in this case:

Let the length of this pair of equal prefix and suffix be $\textit{prefixlen}$. We know $subpatlen = patlastpos - j$, so the part to the left of $pat$ has length $subpatlen-\textit{prefixlen}$,

and $rpr(j) = -(subpatlen-\textit{prefixlen})$. So $delta_2(j) = patlastpos - rpr(j) = patlastpos \times 2 - j - \textit{prefixlen}$.

There may be several pairs of equal prefixes and suffixes after it, for example:

$$
\begin{aligned}
\textit{j}:\qquad\qquad\quad\ \ &\texttt{0 1 2 3 4 5 6 7 8 9} \\
\textit{pat}:\qquad\qquad\ \  &\texttt{A B A A B A A B A A} \\
\end{aligned}
$$

For $j\leq2$ there is $\texttt{ABAABAA}$, for $2< j \leq 5$ there is $\texttt{ABAA}$, and for $5<j\leq8$ there is $\texttt{A}$.

The flaw in Knuth's algorithm is that it only considered the longest pair. In fact we must consider every case where a suffix of $subpat$ equals a prefix of $pat$. This is the same as finding every proper suffix of $pat$ that equals a proper prefix, and then, in decreasing order of length, computing different values of $delta_2(j)$ for each range of $j$.

We use the prefix function and apply its transition equation backwards, $j^{(n)} = \pi[j^{(n-1)}-1]$, to get the lengths of all equal proper prefixes and suffixes of $pat$. Start from $\pi[patlastpos]$ as the length of the longest pair, then apply the transition equation to get the length of the next longest equal proper prefix and suffix.

This completes the computation of $delta_2$ for case 2.

#### Case 3

The reoccurrence of $subpat$ lies inside $pat$ (not including the head of $pat$). That is, we search for $subpat$ in $pat[0\dots patlastpos-1]$ from right to left.

If we solved this with the BM algorithm itself, we would get a recursive BM implementation for case 3, with the stopping condition $patlen \leqslant  2$.

Also, by the definition of $delta_2$, the character just before (to the left of) the found reoccurrence of $subpat$ must differ from the character just before the $subpat$ that is the suffix of $pat$.

This suggests computing case 3 with a process similar to computing the prefix function, just with left and right swapped:

-   Two pointers point to the left end of the substring and to the position of the "prefix" of the substring's longest common prefix-suffix. They move from right to left. While the two characters they point to are equal, they keep moving, which means the "prefix" grows;
-   When the two characters differ, the part that was equal so far meets the requirement of $delta_2$ for a reoccurrence. Then we move the pointer at the "prefix" position back until the characters are equal again or it goes out of bounds.

Like the prefix function, this needs a helper array for moving back. We can reuse the space of the prefix array generated while computing case 2.

### Implementation

??? note "Implementation of the above"
    ```rust
    use std::cmp::PartialEq;
    use std::cmp::min;
    
    pub fn build_delta_2_table_improved_minghu6(p: &[impl PartialEq]) -> Vec<usize> {
        let patlen = p.len();
        let lastpos = patlen - 1;
        let mut delta_2 = Vec::with_capacity(patlen);
        
        // case 1
        // delta_2[j] = lastpos * 2 - j
        for i in 0..patlen {
            delta_2.push(lastpos * 2 - i);
        }
        
        // case 2
        // lastpos <= delata2[j] = lastpos * 2 - j
        let pi = compute_pi(p);  // compute the prefix function
        let mut i = lastpos;
        let mut last_i = lastpos; // only for initialization
        while pi[i] > 0 {
            let start;
            let end;
            
            if i == lastpos {
                start = 0;
            } else {
                start = patlen - pi[last_i];
            }
            
            end = patlen - pi[i];
            
            for j in start..end {
                delta_2[j] = lastpos * 2 - j - pi[i];
            }
            
            last_i = i;
            i = pi[i] - 1;
        }
        
        // case 3
        // delata2[j] < lastpos
        let mut j = lastpos;
        let mut t = patlen;
        let mut f = pi;
        loop {
            f[j] = t;
            while t < patlen && p[j] != p[t] {
                // use min so that later backtracking cannot overwrite earlier data
                delta_2[t] = min(delta_2[t], lastpos - 1 - j);
                t = f[t];
            }
            
            t -= 1;
            if j == 0 {
                break;
            }
            j -= 1;
        }
        
        // no real meaning, only for a complete definition
        delta_2[lastpos] = 0;
        
        delta_2
    }
    ```

## The Galil rule: improving the worst case for multiple matches

### Finding multiple matches with suffix-matching algorithms

The search algorithms so far only find the first match of $pat$ in $string$. There are many different approaches for finding all matches of $pat$ in $string$. The core question is: how can we use the information from characters already matched successfully to bring the worst-case time complexity down to linear?

In the original approach, after a successful match, the pointer on $string$ simply slides forward by $patlen$ and suffix matching starts again. In the worst case this goes back to $O(mn)$ time (by convention, $m$ is $patlen$ and $n$ is $stringlen$; the same below).

An extreme example: $pat$: $\texttt{AAA}$, $string$: $\texttt{AAAAA}\dots$.

One method Knuth proposed for this is to use a "finite" set of states to remember $patlen$ characters. This algorithm guarantees that each character of $string$ is compared at most once. The cost is that this "finite" number of states may be quite large: for a $pat$ whose characters are all different, it needs $\dfrac{1}{2}m^{2}+m$ states.

Below we introduce the Galil algorithm[^galil-rule], which is simple and needs no extra preprocessing.

### The Galil rule

Suppose $pat$ is a prefix of the string $UUUU\dots$ formed by repeating some substring $U$ n times. Then we call $U$ a period of $pat$.

For example, $pat: \texttt{ABCABCAB}$ is a prefix of $\texttt{ABCABCABC}$, which repeats $\texttt{ABC}$. So the length $3$ of $\texttt{ABC}$ is a period length of this $pat$, that is, $pat$ satisfies $pat[i] = pat[i+3]$.

$pat$ always has at least one period, of length equal to its own length. Let $k$ be the length of the shortest period, $k\leq patlen$.

During the search, if $pat$ has just matched successfully, then by the property of periods we only need to slide forward by $k$ characters on $string$ and check whether these $k$ characters match. That directly tells us whether there is another match of $pat$.

To compute the length of this shortest period, suppose we know a pair of equal prefix and suffix of $pat$ with length $\textit{prefixlen}$. Then $pat[i] = pat[i+(patlen-\textit{prefixlen})]$, which gives a period of length $patlen-\textit{prefixlen}$.

When we know the longest pair of equal prefix and suffix of $pat$, we get the shortest period of $pat$.

The length of the longest equal prefix and suffix, $\pi[patlastpos]$, is already computed while building $delta_2$. So without any extra preprocessing time or space, we can improve the worst-case time complexity of the suffix-matching algorithm to linear.

??? note "Final implementation of the BM search algorithm with the optimizations above"
    ```rust
    #[cfg(target_pointer_width = "64")]
    const LARGE: usize = 10_000_000_000_000_000_000;
    
    #[cfg(not(target_pointer_width = "64"))]
    const LARGE: usize = 2_000_000_000;
    
    pub struct BMPattern<'a> {
        pat_bytes: &'a [u8],
        delta_1: [usize; 256],
        delta_2: Vec<usize>,
        k: usize  // length of the shortest period of pat
    }
    
    impl<'a> BMPattern<'a> {
        // ...
        
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let stringlen = string_bytes.len();
            let patlen = self.pat_bytes.len();
            let pat_last_pos = patlen - 1;
            let mut string_index = pat_last_pos;
            let mut pat_index;
            let l0 =  patlen - self.k;
            let mut l = 0;
            
            while string_index < stringlen {
                let old_string_index = string_index;
                
                while string_index < stringlen {
                    string_index += self.delta0(string_bytes[string_index]);
                }
                if string_index < LARGE {
                    break;
                }
                
                string_index -= LARGE;
                
                // if string_index moved, at least one failed match happened since the last successful match.
                // in that case, reset the offset for the Galil rule's second match to zero.
                if old_string_index < string_index {
                    l = 0;
                }
                
                pat_index = pat_last_pos;
                
                while pat_index > l && string_bytes[string_index] == self.pat_bytes[pat_index] {
                    string_index -= 1;
                    pat_index -= 1;
                }
                
                if pat_index == l && string_bytes[string_index] == self.pat_bytes[pat_index] {
                    result.push(string_index - l);
                    
                    string_index += pat_last_pos - l + self.k;
                    l = l0;
                } else {
                    l = 0;
                    string_index += max(
                        self.delta_1[string_bytes[string_index] as usize],
                        self.delta_2[pat_index],
                    );
                }
            }
            
            result
        }
    }
    ```

### How the worst case affects performance in practice

In practice, the theoretical worst case rarely hurts performance. Even in tests on random text over a tiny alphabet of size 4, the effect of this worst case is too small to observe.

So unless it is designed well, using the Galil rule can slightly slow down average performance. But for some extreme $pat$ and $string$, such as the example $pat$: $\texttt{AAA}$, $string$: $\texttt{AAAAA}\dots$, applying the Galil rule really does make it several times faster.

## Improved algorithms

### Simplified Boyer–Moore algorithm

The most complicated part of the BM algorithm is building the $delta_2$ table (the good-suffix table). In practice, though, matching performance over ordinary alphabets depends mainly on the $delta_1$ table (the bad-character table). So a simplified BM algorithm appeared that uses only the $delta_1$ table. Its performance is usually very close to the original.

### Boyer–Moore–Horspool algorithm

The Horspool algorithm is also based on the bad-character rule. It applies $delta_1$ to the character lined up with the end of $pat$. The effect is similar to the improvement to the original matching algorithm above, and it usually performs better than the original version.

???+ note "Implementation"
    ```rust
    pub struct HorspoolPattern<'a> {
        pat_bytes: &'a [u8],
        bm_bc: [usize; 256],
    }
    
    impl<'a> HorspoolPattern<'a> {
        // ...
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let stringlen = string_bytes.len();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let mut string_index = pat_last_pos;
            
            while string_index < stringlen {
                if &string_bytes[string_index-pat_last_pos..string_index+1] == self.pat_bytes {
                    result.push(string_index-pat_last_pos);
                }
                
                string_index += self.bm_bc[string_bytes[string_index] as usize];
            }
            
            result
        }
    }
    ```

### Boyer–Moore–Sunday algorithm

The Sunday algorithm also uses the bad-character rule, but goes one step further than Horspool: it looks directly at the character right after the one lined up with the end of $pat$.

Implementing it only needs a small change to the $delta_1$ table, as if it were built on a $pat$ of length $patlen+1$.

The Sunday algorithm is a practical choice in general: it is among the simplest to implement and has some of the best average performance, usually a bit better than Horspool and BM.

???+ note "Implementation"
    ```rust
    pub struct SundayPattern<'a> {
        pat_bytes: &'a [u8],
        sunday_bc: [usize; 256],
    }
    
    impl<'a> SundayPattern<'a> {
        // ...
        fn build_sunday_bc(p: &'a [u8]) -> [usize; 256] {
            let mut sunday_bc_table = [p.len() + 1; 256];
            
            for i in 0..p.len() {
                sunday_bc_table[p[i] as usize] = p.len() - i;
            }
            
            sunday_bc_table
        }
        
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let stringlen = string_bytes.len();
            let mut string_index = pat_last_pos;
            
            while string_index < stringlen {
                if &string_bytes[string_index - pat_last_pos..string_index+1] == self.pat_bytes {
                    result.push(string_index - pat_last_pos);
                }
                
                if string_index + 1 == stringlen {
                    break;
                }
                
                string_index += self.sunday_bc[string_bytes[string_index + 1] as usize];
            }
            
            result
        }
    }
    ```

### BMHBNFS algorithm

This algorithm combines Horspool and Sunday. It is the `find` algorithm used in CPython's implementation of the `stringlib` module[^b5s]. Below we call it B5S for short.

The basic idea of B5S is:

1.  Following suffix matching, first check whether the characters at position $patlastpos$ are equal. If they are, check whether the characters at positions $0\dots patlastpos-1$ are equal. If they are still equal, we have found a match;

2.  If a mismatch happens at either stage, go to the jump stage;

3.  In the jump stage, first check whether the character right after position $patlastpos$ is in $pat$. If it is not, slide right by $patlen+1$ directly. This makes the most of the Sunday algorithm;

    If this character is in $pat$, do a Horspool jump using $delta_1$ on the character at $patlastpos$.

Depending on whether saving time or saving space is the main goal, the algorithm has very different implementations.

#### Time-saving version

???+ note "Implementation"
    ```rust
    pub struct B5STimePattern<'a> {
        pat_bytes: &'a [u8],
        alphabet: [bool;256],
        bm_bc: [usize;256],
        k: usize
    }
    
    impl<'a> B5STimePattern<'a> {
        pub fn new(pat: &'a str) -> Self {
            assert_ne!(pat.len(), 0);
            
            let pat_bytes = pat.as_bytes();
            let (alphabet, bm_bc, k) = B5STimePattern::build(pat_bytes);
            
            B5STimePattern { pat_bytes, alphabet, bm_bc, k }
        }
        
        fn build(p: &'a [u8]) -> ([bool;256], [usize;256], usize)  {
            let mut alphabet = [false;256];
            let mut bm_bc = [p.len(); 256];
            let lastpos = p.len() - 1;
            
            for i in 0..lastpos {
                alphabet[p[i] as usize] = true;
                bm_bc[p[i] as usize] = lastpos - i;
            }
            
            alphabet[p[lastpos] as usize] = true;
            
            (alphabet, bm_bc, compute_k(p))
        }
        
        pub fn find_all(&self, string: &str) -> Vec<usize> {
            let mut result = vec![];
            let string_bytes = string.as_bytes();
            let pat_last_pos = self.pat_bytes.len() - 1;
            let patlen = self.pat_bytes.len();
            let stringlen = string_bytes.len();
            let mut string_index = pat_last_pos;
            let mut offset = pat_last_pos;
            let offset0 = self.k - 1;
            
            while string_index < stringlen {
                if string_bytes[string_index] == self.pat_bytes[pat_last_pos] {
                    if &string_bytes[string_index-offset..string_index] == &self.pat_bytes[pat_last_pos-offset..pat_last_pos] {
                        result.push(string_index-pat_last_pos);
                        
                        offset = offset0;
                        
                        // Galil rule
                        string_index += self.k;
                        continue;
                    }
                }
                
                if string_index + 1 == stringlen {
                    break;
                }
                
                offset = pat_last_pos;
                
                if !self.alphabet[string_bytes[string_index+1] as usize] {
                    string_index += patlen + 1;  // sunday
                } else {
                    string_index += self.bm_bc[string_bytes[string_index] as usize];  // horspool
                }
            }
            
            result
        }
    }
    ```

This version of B5S performs very well. Among the suffix-matching algorithms introduced so far, it is usually the fastest.

#### Space-saving version

This is also implemented in CPython's `stringlib`. It uses two integers to approximately replace the character table and $delta_1$, which saves a lot of space:

1.  Replace the character table (alphabet) with a simple Bloom filter

    ???+ note "Implementation"
        ```rust
        pub struct BytesBloomFilter {
            mask: u64,
        }
        
        impl BytesBloomFilter {
            pub fn new() -> Self {
                SimpleBloomFilter {
                    mask: 0,
                }
            }
            
            fn insert(&mut self, byte: &u8) {
                (self.mask) |= 1u64 << (byte & 63);
            }
            
            fn contains(&self, char: &u8) -> bool {
                (self.mask & (1u64 << (byte & 63))) != 0
            }
        }
        ```

    A Bloom filter is a `Set`-like data structure designed to save a great deal of storage by giving up some accuracy (and, in practice, some running time). It may report an item that is not in the set as present (false positives, FP), but it never reports an item that is in the set as absent (false negatives, FN). So using it may lose the largest possible jump because of FP, but it never skips characters that should have matched because of FN.

    In theory, the "Bloom filter" above has an FP probability of about 0.5 when $pat$ is 50 bytes long, and about 0.15 when $pat$ is 10 bytes long.

    This is not a standard Bloom filter, though. First, it does not use a real hash function; it is just a character mapping that maps a byte 0-255 to the number formed by its low six bits.

    But since we are searching characters in memory, this simplification matters a lot. Even with [xxHash](https://cyan4973.github.io/xxHash/), the fastest known non-cryptographic hash algorithm, the computation would take an order of magnitude longer.

    Also, when pat is under 30 bytes, getting the best FP probability would need more than one hash function. But that is not worth it, because an array of two `u128` numbers is already enough to build a character table for the full character set.

2.  Use $delta_1(pat[patlastpos])$ instead of the whole $delta_1$

    Looking at $delta_1$, the most common mismatch is when the very first character compared in suffix matching does not match, and that is where $delta_1$ is used most. So let `skip = delta1(pat[patlastpos])`.

    On a mismatch in the first stage, slide down by `skip` characters directly. On a mismatch in the second stage, since we do not have the full $delta_1$, we can only slide down by one character.

    ???+ note "Implementation"
        ```rust
        pub struct B5SSpacePattern<'a> {
            pat_bytes: &'a [u8],
            alphabet: BytesBloomFilter,
            skip: usize,
        }
        
        impl<'a> B5SSpacePattern<'a> {
            pub fn new(pat: &'a str) -> Self {
                assert_ne!(pat.len(), 0);
                
                let pat_bytes = pat.as_bytes();
                let (alphabet, skip) = B5SSpacePattern::build(pat_bytes);
                
                B5SSpacePattern { pat_bytes, alphabet, skip}
            }
            
            fn build(p: &'a [u8]) -> (BytesBloomFilter, usize)  {
                let mut alphabet = BytesBloomFilter::new();
                let lastpos = p.len() - 1;
                let mut skip = p.len();
                
                for i in 0..p.len()-1 {
                    alphabet.insert(&p[i]);
                    
                    if p[i] == p[lastpos] {
                        skip = lastpos - i;
                    }
                }
                
                alphabet.insert(&p[lastpos]);
                
                (alphabet, skip)
            }
            
            pub fn find_all(&self, string: &'a str) -> Vec<usize> {
                let mut result = vec![];
                let string_bytes = string.as_bytes();
                let pat_last_pos = self.pat_bytes.len() - 1;
                let patlen = self.pat_bytes.len();
                let stringlen = string_bytes.len();
                let mut string_index = pat_last_pos;
                
                while string_index < stringlen {
                    if string_bytes[string_index] == self.pat_bytes[pat_last_pos] {
                        if &string_bytes[string_index-pat_last_pos..string_index] == &self.pat_bytes[..patlen-1] {
                            result.push(string_index-pat_last_pos);
                        }
                        
                        if string_index + 1 == stringlen {
                            break;
                        }
                        
                        if !self.alphabet.contains(&string_bytes[string_index+1]) {
                            string_index += patlen + 1;  // sunday
                        } else {
                            string_index += self.skip;  // horspool
                        }
                    } else {
                        if string_index + 1 == stringlen {
                            break;
                        }
                        
                        if !self.alphabet.contains(&string_bytes[string_index+1]) {
                            string_index += patlen + 1;  // sunday
                        } else {
                            string_index += 1;
                        }
                    }
                
                }
                
                result
            }
        }
        ```

    This version is not as fast as the earlier suffix-matching algorithms, but the gap is small, and it still beats KMP. It owes this to its excellent space usage of at most two `u64` integers.

## Theoretical analysis

Below is how the algorithms perform over a general alphabet. The vertical axis is roughly the execution cost (cost is the cost of a mismatch after successfully matching m characters; skip is the probability of sliding down by k characters on a mismatch); smaller is better. The horizontal axis is the length of the pattern pat:

![Performance comparison of string search algorithms](./images/BM/plot256.svg)

Performance over a small alphabet (DNA base sequences {A, C, T, G}):

![Performance comparison of string search algorithms over a small alphabet](./images/BM/plot4.svg)

In summary, over larger alphabets, such as in everyday search, the Boyer–Moore family performs very well, mainly thanks to the character jumps from the $delta_1$ table;

on the other hand, over smaller alphabets, $delta_1$ helps less, and the value of $delta_2$ shows.

If some extra space is available, the full Boyer–Moore algorithm with $O(m)$ space complexity is more general and gives the best overall performance.

## References and notes

[^bm]: [The 1977 Boyer–Moore algorithm paper](https://dl.acm.org/doi/10.1145/359842.359859)

[^kmp]: [The 1977 KMP algorithm paper](https://epubs.siam.org/doi/abs/10.1137/0206024)

[^rytter]: [Rytter's 1980 paper correcting Knuth](https://epubs.siam.org/doi/10.1137/0209037)

[^galil-rule]: [The 1979 paper introducing the Galil algorithm](https://doi.org/10.1145%2F359146.359148)

[^b5s]: [Introduction to the B5S algorithm](http://effbot.org/zone/stringlib.htm#BMHBNFS)
