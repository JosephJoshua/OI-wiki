## Definition

The palindromic tree (EER Tree, Palindromic Tree, also called the palindromic automaton) is an efficient data structure that stores all palindromic substrings of a string. It was first published by Mikhail Rubinchik and Arseny M. Shur in 2015. It was inspired by suffix data structures such as the suffix tree. With a palindromic tree, a whole range of problems about palindromes can be solved simply and efficiently.

## Structure

A palindromic tree looks roughly like this

![](./images/pam1.png)

Like other automata, the palindromic tree consists of transition edges and suffix links (fail pointers). Each node represents one palindromic substring.

Palindromes have either odd or even length. Like in Manacher's algorithm, we could insert a character that is not in the alphabet (such as '#') as a separator to make all palindrome lengths odd, but that is too much trouble. Is there a better way?

Of course there is. The better way is to build two trees: in one tree all nodes correspond to odd-length palindromic substrings, and in the other tree all nodes correspond to even-length palindromic substrings.

As in other automata, the fail pointer of a node points to the node of the longest palindromic suffix of the palindrome that the node represents. But a transition edge does not mean appending one character to the palindrome of the original node. Instead, it means adding the same character to both the front and the back of that palindrome (this makes sense, since we need to make sure we only store palindromes).

We also need to store at each node the length len of its palindromic substring. This information lets us build the palindromic tree easily.

## Construction

The palindromic tree has two initial states, representing palindromes of length $-1$ and $0$. We can call them the odd root and the even root. They do not represent any actual string and exist only as initial states, just like the root nodes of other automata.

The fail pointer of the even root points to the odd root. We do not care about the fail pointer of the odd root, because the odd root can never fail to match (the next state reached from the odd root has length $1$, a single character, which is always a palindromic substring)

Like the suffix automaton, we build the palindromic tree incrementally.

Suppose we have built the palindromic tree for the first $p-1$ characters, and now we add the character at position $p$ of the original string to the automaton.

We start from the node of the longest palindromic substring ending at the previous character and keep following fail pointers until we find a node satisfying $s_{p}=s_{p-len-1}$, that is, the character just before this node's palindromic substring equals the character being added.

Here is the figure from the paper

![](./images/pam2.png)

By following fail pointers we find the node of A. Adding `X` on both sides gives the current palindrome (that is, `XAX`). Clearly, this node is the node in the tree of the longest palindromic substring ending at $p$. (This is also where the length $-1$ node shows its advantage: if no `X` matches, the condition becomes $s_p=s_p$ at the same position, and we naturally get the node representing the single character `X`.) At this point we check: if this node does not exist, we create it.

Then we need to find the fail pointer of the newly created node. The method is similar to the process above: starting from `A`, keep following fail pointers to find the longest palindromic suffix `XBX` of `XAX`, and set the fail pointer to the corresponding node.

Clearly, this node never needs to be created. The first $len_B$ characters and the last $len_B$ characters of `A` are the same, both `B`. By the symmetry of palindromes, the characters on both ends of the first $len_B$ characters are `X`, and the character after it is fixed to be `X`, so the node `XBX` must already exist.

If fail finds no match, we link it to the node of length $0$. Clearly this works (because it is a suffix of every node).

## Proof that the number of states is linear

### Theorem

A string $s$ has at most $|s|$ distinct palindromic substrings.

### Proof

We use mathematical induction.

-   When $|s| =1$, $s$ has only one character and only one substring, and this substring is a palindrome, so the claim holds.

-   When $|s| >1$, let $t=sc$, where $t$ is the string formed by appending a character $c$ to the end of $s$, and assume the claim holds for $s$. Consider the palindromic substrings ending at the last character $c$, and let their left endpoints in increasing order be $l_1,l_2,\dots,l_k$. Since $t[l_1..|t|]$ is a palindrome, for every position $l_1 \le p \le |t|$ we have $t[p..|t|]=t[l_1..l_1+|t|-p]$. So for $1 < i \le k$, $t[l_i..|t|]$ has already appeared in $t[1..|t|-1]$. Therefore each time we add one character, the number of distinct palindromic substrings increases by at most $1$.

By induction, the theorem holds.

So the palindromic tree has $O(|s|)$ states. Each state represents exactly one distinct palindromic substring, so exactly one transition leads to each node. Therefore the total number of transitions is also $O(|s|)$.

## Proof of correctness

Take the figure above as an example. When adding the current character `X`, by the proof of the linear number of states, we only need to find the longest palindromic suffix containing the last character `X`, which is `XAX`. Then we find the longest palindromic suffix `XBX` of `XAX` and set up the suffix link. The state of `XBX` already exists in the palindromic tree. The palindromic suffixes containing the last character are exactly `XAX`, `XBX` itself, and all ancestors of its state in the fail tree.

When building the palindromic tree of $s$, let $n=|s|$. Clearly, all operations other than following fail pointers take $O(n)$ in total.

When adding a character, starting from the previous step, each jump along a fail pointer decreases the depth of the current node in the fail tree by $1$, while setting the fail link increases the depth by only 1 (but when fail is $0$ (that is, the condition only holds at $-1$), the depth is effectively $+2$ relative to $-1$).

Since only $n$ characters are added, the depth increases only $n$ times, so there are at most $2n$ fail jumps.

So the time complexity of building the palindromic tree of $s$ is $O(|s|)$.

## Applications

### Number of distinct palindromic substrings

From the proof of the linear number of states, it is easy to see that the number of distinct palindromic substrings of a string equals the number of states of the palindromic tree (excluding the odd root and the even root).

### Number of occurrences of palindromic substrings

Build the palindromic tree and count occurrences in the same way as with a suffix automaton.

When building the palindromic tree, nodes are inserted in topological order. So we only need to go through all states in reverse order and add the occurrence count of each state to that of the state its fail pointer points to.

Example problem: [APIO 2014 — Palindromes](https://www.luogu.com.cn/problem/P3649)

Define the existence value of a substring of $s$ as the number of times it occurs in $s$ multiplied by its length. For a given string $s$, find the largest existence value among all palindromic substrings.

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/pam/pam_1.cpp"
    ```

### Minimum palindromic partition

> Given a string $s(1\le |s| \le 10^5)$, find the smallest $k$ such that there exist $s_1,s_2,\dots,s_k$ where every $s_i(1\le i \le k)$ is a palindrome and concatenating $s_1,s_2, \dots ,s_k$ in order gives $s$.

Consider dynamic programming. Let $dp[i]$ be the minimum number of parts for the prefix of $s$ of length $i$. A transition only needs to enumerate all palindromes ending at the $i$-th character

$$
dp[i]=1+\min_{ s[j+1..i] \text{ is a palindrome} } dp[j]
$$

Since a string can have up to $O(n^2)$ palindromic substrings, the algorithm above takes $O(n^2)$ time, which is too slow. To speed up the transitions, we now give some lemmas.

Let $pre(s,i)$ denote the prefix of $s$ of length $i$, and $suf(s,i)$ the suffix of length $i$.

Period: if $0< p \le |s|$ and $\forall 1 \le i \le |s|-p,s[i]=s[i+p]$, then $p$ is called a period of $s$.

Border: if $0 \le r < |s|$ and $pre(s,r)=suf(s,r)$, then $pre(s,r)$ is called a border of $s$.

Relation between periods and borders: $t$ is a border of $s$ if and only if $|s|-|t|$ is a period of $s$.

???+ note "Proof"
    If $t$ is a border of $s$, then $pre(s,|t|)=suf(s,|t|)$, so $\forall 1\le i \le |t|, s[i]=s[|s|-|t|+i]$, and therefore $|s|-|t|$ is a period of $s$.
    
    If $|s|-|t|$ is a period of $s$, then $\forall 1 \le i \le |s|-(|s|-|t|)=|t|,s[i]=s[|s|-|t|+i]$, so $pre(s,|t|)=suf(s,|t|)$, and therefore $t$ is a border of $s$.

#### Lemma 1

Let $t$ be a suffix of a palindrome $s$. Then $t$ is a border of $s$ if and only if $t$ is a palindrome.

???+ note "Proof"
    For $1 \le i \le |t|$, since $s$ and $t$ are palindromes, $s[i]=s[|s|-i+1]=s[|s|-|t|+i]$, so $t$ is a border of $s$.
    
    For $1 \le i \le |t|$, since $t$ is a border of $s$, $s[i]=s[|s|-|t|+i]$; since $s$ is a palindrome, $s[i]=s[|s|-i+1]$. So $s[|s|-i+1]=s[|s|-|t|+i]$, and therefore $t$ is a palindrome.

In the figure below, positions with the same color hold the same characters.

![](./images/pam3.png)

#### Lemma 2

Let $t$ be a border of a string $s$ ($|s|\le 2|t|$). Then $s$ is a palindrome if and only if $t$ is a palindrome.

???+ note "Proof"
    If $s$ is a palindrome, then by Lemma $1$, $t$ is also a palindrome.
    
    If $t$ is a palindrome, since $t$ is a border of $s$, $\forall 1 \le i \le |t|, s[i]=s[|s|-|t|+i]=s[|s|-i+1]$. Since $|s| \le 2|t|$, $s$ is also a palindrome.

#### Lemma 3

Let $t$ be a border of a palindrome $s$. Then $|s|-|t|$ is a period of $s$, and $|s|-|t|$ is the smallest period of $s$ if and only if $t$ is the longest proper palindromic suffix of $s$.

#### Lemma 4

Let $x$ be a palindrome, $y$ the longest proper palindromic suffix of $x$, and $z$ the longest proper palindromic suffix of $y$. Let $u,v$ be the strings with $x=uy,y=vz$. Then the following three properties hold

1.  $|u| \ge |v|$;

2.  If $|u| > |v|$, then $|u| > |z|$;

3.  If $|u| = |v|$, then $u=v$.

![](./images/pam4.png)

???+ note "Proof"
    1.  By the corollary of Lemma $3$, $|u|=|x|-|y|$ is the smallest period of $x$, and $|v|=|y|-|z|$ is the smallest period of $y$. Suppose for contradiction that $|u| < |v|$. Since $y$ is a suffix of $x$, $u$ is a period of both $x$ and $y$, but $|v|$ is the smallest period of $y$, a contradiction. So $|u| \ge |v|$.
    2.  Since $y$ is a border of $x$, $v$ is a prefix of $x$. Let $w$ be the string with $x=vw$ (as in the figure below), where $z$ is a border of $w$. Suppose for contradiction that $|u| \le |z|$. Then $|zu| \le 2|z|$, so by Lemma $2$, $w$ is a palindrome, and by Lemma $1$, $w$ is a border of $x$. But since $|u| > |v|$, $|w| > |y|$, a contradiction. So $|u| > |z|$.
    3.  $u,v$ are both prefixes of $x$ and $|u|=|v|$, so $u=v$.
    
    ![](./images/pam5.png)

#### Corollary

When all palindromic suffixes of $s$ are sorted by length, they can be split into $\log |s|$ arithmetic progressions.

???+ note "Proof"
    Let the lengths of all palindromic suffixes of $s$, sorted in increasing order, be $l_1,l_2,\dots,l_k$. For any $2 \le i \le k-1$, if $l_{i}-l_{i-1}=l_{i+1}-l_{i}$, then $l_{i-1},l_{i},l_{i+1}$ form an arithmetic progression. Otherwise $l_{i}-l_{i-1}\neq l_{i+1}-l_{i}$, and by Lemma $4$, $l_{i+1}-l_{i}>l_{i}-l_{i-1}$ and $l_{i+1}-l_{i}>l_{i-1}$, so $l_{i+1}>2l_{i-1}$. So whenever the difference between the lengths of two adjacent pairs of palindromic suffixes changes, the larger length must be at least double the smaller one. Clearly, doubling can happen at most $O(\log |s|)$ times, so the lengths of the palindromic suffixes of $s$ can be split into $\log |s|$ arithmetic progressions.

This corollary can also be proved with the weak periodicity lemma: group all borders of the longest palindromic suffix of $s$ by length $x$, $x \in [2^0,2^1),[2^1,2^2),\dots,[2^k,n)$, and consider the longest border in each of these $\log |s|$ groups. For a detailed proof, see Jin Ce's "Selected Topics in String Algorithms" and Chen Sunli's 2019 IOI China national team candidate paper "Algorithms for Substring Period Queries and Their Applications".

With this result, we can now think about how to speed up the $dp$ transitions.

#### Optimization

Each node $u$ of the palindromic tree needs to store two more values, $diff[u]$ and $slink[u]$. $diff[u]$ is the difference in length between the palindromes of node $u$ and $fail[u]$, that is, $len[u]-len[fail[u]]$. $slink[u]$ is the first node $v$ reached by following fail pointers up from $u$ such that $diff[v] \neq diff[u]$; in other words, it is the shortest node in the arithmetic progression containing $u$.

By the result proved above, if we jump up using $slink$ pointers, each time we append a character we only need $O(\log |s|)$ jumps. So we can store the sum of the $dp$ values (in the original problem, the $\min$) of all palindromes in one arithmetic progression at the node of the longest palindrome in that progression.

Let $g[v]$ be the sum of the $dp$ values over the arithmetic progression containing $v$, where $v$ is the longest node in that progression. Then $g[v]=\sum_{slink[x]=slink[v]} dp[i-len[x]]$, where $i$ is the current index.

Now let us see how to update the arrays $g$ and $dp$. Take the figure below as an example. Suppose we are at the $i$-th character and the corresponding node in the palindromic tree is $x$. $g[x]$ is the sum of the $dp$ values at the three orange positions (the shortest palindrome, $slink[x]$, belongs to the next arithmetic progression). The previous occurrence of $fail[x]$ is at $i-diff[x]$ (it ends at $i-diff[x]$), and the $dp$ values included in $g[fail[x]]$ are at the blue positions. So $g[x]$ actually equals $g[fail[x]]$ plus the $dp$ value at one extra position, which is $i-(len[slink[x]]+diff[x])$. Finally we use $g[x]$ to update $dp[i]$, which finishes the contribution of this arithmetic progression. Then we keep jumping to $slink[x]$ and repeat the process. For the details, see the example code.

![](./images/pam6.png)

Finally, the correctness of the method above relies on this fact: if $x$ and $fail[x]$ belong to the same arithmetic progression, then the previous occurrence of $fail[x]$ is at $i-diff[x]$.

???+ note "Proof"
    By Lemma $1$, $fail[x]$ is a border of $x$, so it occurs at $i-diff[x]$.
    
    Suppose $fail[x]$ occurs at some position $j$ in $(i-diff[x],i)$. Since $x$ and $fail[x]$ belong to the same arithmetic progression, $2|fail[x]| \ge x$. This extra $fail[x]$ overlaps the $fail[x]$ at $i-diff[x]$; call the overlap $w$, and let $u$ be the string with $uw=fail[x]$. In the same way as in Lemma $1$, we can prove that $w$ is a palindrome, and the prefix $s[i-len[x]+1..j]=uwu$ of $x$ is also a palindrome. This contradicts the fact that $fail[x]$ is the longest palindromic prefix (suffix) of $x$.

Example problem: [Codeforces 932G Palindrome Partition](https://codeforces.com/problemset/problem/932/G)

Given a string $s$, split $s$ into $t_1, t_2, \dots, t_k$, where $k$ is even and $t_i=t_{k-i+1}$. Count the number of such partitions.

??? note "Solution"
    Build the string $t= s[0]s[n - 1]s[1]s[n - 2]s[2]s[n - 3] \dots s[n / 2 - 1]s[n / 2]$. The problem is equivalent to counting the partitions of $t$ into even-length palindromes. Change the transition above into a sum and only update the $dp$ array at even positions. The time complexity is $O(n \log n)$ and the space complexity is $O(n)$.

??? note "Reference code"
    ```cpp
    --8<-- "docs/string/code/pam/pam_2.cpp"
    ```

## Example problems

-   [Longest Double Palindrome](https://www.luogu.com.cn/problem/P4555)

-   [Cheerleading Rehearsal](https://www.luogu.com.cn/problem/P1659)

-   [SHOI 2011 — Double Palindrome](https://www.luogu.com.cn/problem/P4287)

-   [HDU 5421 Victor and String](https://acm.hdu.edu.cn/showproblem.php?pid=5421)

-   [CodeChef Palindromeness](https://www.codechef.com/LTIME23/problems/PALPROB)

## Further reading

-   [EERTREE: An Efficient Data Structure for Processing Palindromes in Strings](https://arxiv.org/pdf/1506.04862)

-   [Palindromic tree](http://adilet.org/blog/palindromic-tree/)

-   Weng Wentao, "The Palindromic Tree and Its Applications", 2017 IOI China National Team Candidate Papers

-   Chen Sunli, "Algorithms for Substring Period Queries and Their Applications", 2019 IOI China National Team Candidate Papers

-   Jin Ce, "Selected Topics in String Algorithms"

-   [A bit more about palindromes](https://codeforces.com/blog/entry/19193)

-   [A Subquadratic Algorithm for Minimum Palindromic Factorization](https://arxiv.org/pdf/1403.2431.pdf)
