author: sshwy

A balanced bracket sequence is a string made up only of $($ and $)$ such that:

-   The empty string $\varepsilon$ is a balanced bracket sequence.
-   If $s$ is a balanced bracket sequence, then $(s)$ is also a balanced bracket sequence.
-   If $s,t$ are both balanced bracket sequences, then $st$ is also a balanced bracket sequence.

For example, $(())()$ is a balanced bracket sequence, but $)()$ is not.

Sometimes there are several different kinds of brackets, as in $[()]\{\}$. Such variant bracket sequences are defined in a similar way to plain bracket sequences.

This article introduces classic problems about bracket sequences.

Note: in English, a left bracket is usually called an opening bracket, and a right bracket is called a closing bracket.

## Checking whether a sequence is balanced

The classic way to check whether $s$ is a balanced bracket sequence uses a greedy idea. The same algorithm also works for variant bracket sequences.

We maintain a stack and go through $i=1,2,\ldots,|s|$ in order:

-   If $s_i$ is a closing bracket, the stack is not empty, and the top of the stack is the opening bracket that matches $s_i$, pop the top of the stack.
-   Otherwise, push $s_i$ onto the stack.

After scanning all of $s$, if the stack is empty, then $s$ is a balanced bracket sequence; otherwise it is not. The time complexity is $O(n)$.

## Counting balanced bracket sequences

Let us find the number $f_n$ of balanced bracket sequences $s$ of length $2n$. Enumerate the position of the bracket that matches $s_1$; say it is $2i+2$. This splits the whole sequence into two shorter balanced bracket sequences. Therefore

$$
f_n=\sum_{i=0}^{n-1}f_if_{n-i-1}
$$

This is exactly the recurrence of the Catalan numbers. In other words, $f_n=\frac{1}{n+1}\binom{2n}{n}$.

Of course, counting variant balanced bracket sequences works in a similar way. If there are $k$ different kinds of brackets, then $f'_n=\frac{1}{n+1}\binom{2n}{n}k^n$.

## Next sequence in lexicographic order

Given a balanced bracket sequence $s$, we want to find the balanced bracket sequence that comes right after $s$ among all balanced bracket sequences of length $|s|$ sorted in increasing lexicographic order. In this problem, an opening bracket is considered lexicographically smaller than a closing bracket, and we do not consider variant bracket sequences.

We need to find the largest $i$ such that $s_i$ is an opening bracket. Then we change it into a closing bracket and rebuild the part $s[i+1,|s|]$. In addition, $i$ must satisfy: the number of opening brackets in $s[1,i-1]$ is **greater than** the number of closing brackets.

Suppose that after $s_i$ becomes a closing bracket, $s[1,i]$ has $k$ more opening brackets than closing brackets. Then we turn the last $k$ characters of $s$ into closing brackets, and fill $s[i+1,|s|-k]$ in the form $((\dots(())\dots))$, because this filling is lexicographically smallest.

The time complexity of this algorithm is $O(n)$.

??? note "Reference implementation"
    ```cpp
    bool next_balanced_sequence(string& s) {
      int n = s.size();
      int depth = 0;
      for (int i = n - 1; i >= 0; i--) {
        if (s[i] == '(')
          depth--;
        else
          depth++;
    
        if (s[i] == '(' && depth > 0) {
          depth--;
          int open = (n - i - 1 - depth) / 2;
          int close = n - i - 1 - open;
          string next =
              s.substr(0, i) + ')' + string(open, '(') + string(close, ')');
          s.swap(next);
          return true;
        }
      }
      return false;
    }
    ```

## Computing the lexicographic rank

Given a balanced bracket sequence $s$, we want to find its rank in lexicographic order.

We count the number of bracket sequences $p$ that are lexicographically smaller than $s$.

Suppose $p_i<s_i$ and $\forall 1\le j<i,p_j=s_i$. Clearly $p_i$ is an opening bracket and $s_i$ is a closing bracket. Enumerate $i$ (with $s_i$ a closing bracket), and suppose $p[1,i]$ has $k$ more opening brackets than closing brackets. Then we need to count the bracket sequences of length $|s|-i$ that have $k$ unmatched closing brackets and no unmatched opening brackets.

Let $f(i,j)$ be the number of bracket sequences of length $i$ that have $j$ unmatched closing brackets and no unmatched opening brackets.

By enumerating the first character of the bracket sequence, we get the transition for $f$: $f(i,j) = f(i-1,j-1)+f(i-1,j+1)$, with initial value $f(0,0)=1$. In fact, $f$ is [OEIS - A053121](http://oeis.org/A053121).

This way we can compute the lexicographic rank in $O(|s|^2)$.

For variant bracket sequences the method is similar, except that for each $s_i$ we need to consider all characters smaller than it (in the algorithm above, no character is smaller than the opening bracket, so we only considered the case where $s_i$ is a closing bracket).

Also, using the array $f$, we can find the balanced bracket sequence with lexicographic rank $k$ as well.

**This page is mainly translated from the blog post <http://e-maxx.ru/algo/bracket_sequences> and its English translation [Balanced bracket sequences](https://cp-algorithms.com/combinatorics/bracket_sequences.html). The Russian version is licensed under Public Domain + Leave a Link; the English version is licensed under CC-BY-SA 4.0.**
