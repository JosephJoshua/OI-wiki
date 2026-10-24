This article explains how segment trees handle range chmin/chmax operations and historical extreme values, as described by Ji Ruyi in his [2016 Chinese National Training Team paper](https://github.com/OI-wiki/libs/blob/master/%E9%9B%86%E8%AE%AD%E9%98%9F%E5%8E%86%E5%B9%B4%E8%AE%BA%E6%96%87/%E5%9B%BD%E5%AE%B6%E9%9B%86%E8%AE%AD%E9%98%9F2016%E8%AE%BA%E6%96%87%E9%9B%86.pdf) (this technique is often called "Segment Tree Beats").

## Range chmin/chmax

Roughly speaking, a range chmin/chmax operation replaces every number in the range $[l,r]$ with its $\max$ or $\min$ with $x$, that is, $a_i=\max(a_i,x)$ or $a_i=\min(a_i,x)$.

???+ note "[HDU5306 Gorgeous Sequence](https://acm.hdu.edu.cn/showproblem.php?pid=5306)"
    Maintain a sequence $a$ and perform the following operations:
    
    1.  `0 l r t`: $\forall l\le i\le r,~ a_i=\min(a_i,t)$.
    2.  `1 l r`: output $\max\limits_{i=l}^r a_i$.
    3.  `2 l r`: output $\sum\limits_{i=l}^r a_i$.
    
    There are multiple test cases, with $T\le 100,~\sum n,\sum m\le 10^6$.

Taking the range $\min$ only changes the numbers larger than $t$. So the operation no longer targets the whole range, but "the numbers in this range that are larger than $t$". This suggests the following idea: each node stores the range maximum $Max$, the second maximum (strictly smaller) $Se$, the range sum $Sum$, and the count $Cnt$ of the maximum. Now consider taking the range $\min$ with $t$.

1.  If $Max\le t$, clearly $t$ has no effect, so return directly;
2.  If $Se<t < Max$, then $t$ only updates the maximum values of the current range. We add $Cnt(t-Max)$ to the range sum, set $Max$ to $t$, and put a tag on the node.
3.  If $t\le Se$, we do not know how many numbers need updating. So our strategy is to recurse downward by brute force, and then push the information back up.

What is the complexity of this algorithm? Using potential analysis, it can be shown to be $O(m\log n)$. See the paper for the detailed analysis.

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_1.cpp"
```

???+ note "[BZOJ4695 The Fakest Female Contestant](https://loj.ac/p/6565)"
    Maintain a sequence $a$ and perform the following operations:
    
    1.  `1 l r x`: $\forall l\le i\le r,~ a_i=a_i+x$.
    2.  `2 l r x`: $\forall l\le i\le r,~ a_i=\max(a_i,x)$.
    3.  `3 l r x`: $\forall l\le i\le r,~ a_i=\min(a_i,x)$.
    4.  `4 l r`: output $\sum\limits_{i=l}^r a_i$.
    5.  `5 l r`: output $\max\limits_{i=l}^r a_i$.
    6.  `6 l r`: output $\min\limits_{i=l}^r a_i$.
    
    $n,m\le 5\times 10^5,~|a_i|\le 10^8$. All operations of type $1$ have $|x|\le 10^3$, and the other operations have $|x|\le10^8$.

In the same way, we maintain the maximum, second maximum, count of the maximum, minimum, second minimum, count of the minimum, and the range sum. Besides this information, we also need tags for range $\max$, range $\min$ and range add. Compared with the previous problem, this raises the question of the order in which tags are pushed down. We use the following strategy:

1.  The range-add tag has the highest priority, and the other two tags have equal priority.
2.  When we add $v$ to a node, besides using $v$ to update the stored information and the node's range-add tag, we also use this v to update the range-$\max$ and range-$\min$ tags.
3.  When we take the $\min$ of a node with $v$ (ignoring the brute-force recursion here and assuming the tag can be applied), besides updating the stored information, we compare it with the range-$\max$ tag. If $v$ is smaller than the range-$\max$ tag, then all numbers will end up as v, so we set the range-$\max$ tag to $v$ as well. Otherwise we leave it alone.
4.  Taking the range $\max$ with v works the same way.

When maintaining the information, if the range has only one or two numbers, the value sets may overlap. For example, one number may be both the maximum and the second minimum. This needs special handling.

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_2.cpp"
```

Ji Ruyi proved that the complexity of this algorithm is $O(m\log^2 n)$.

???+ note "Mzl loves segment tree"
    There are two sequences $A,B$, and initially all numbers in $B$ are $0$. The operations to maintain are:
    
    1.  Range $\min$ on $A$
    2.  Range $\max$ on $A$
    3.  Range add on $A$
    4.  Query a range sum of $B$
    
    After each operation, whenever the value of $A_i$ changes, add $1$ to $B_i$. $n,m\le 3\times 10^5$.

First consider the easiest operation, range add. As long as $x\neq 0$, every number in the range changes, so we just do a range add of 1 on B.

For range chmin/chmax operations, notice that applying and pushing down tags corresponds one-to-one with changes to array $B$. In essence, you split the numbers of the sequence into three classes, maximum, minimum, and neither, and maintain each separately (you just never build the sets of maxima and minima explicitly, but that does not get in the way). So whenever you apply a tag, you also update the information of $B$ (note: you do not put a tag on $B$! You update the information!). When querying, you query on $A$, and while pushing down tags you also update $B$'s information. Once you reach the needed nodes, return $B$'s information. In essence, this hands the information about extreme values over to $B$ to maintain. You still have to handle overlapping value sets.

???+ note "[CTSN loves segment tree](https://www.luogu.com.cn/problem/U180387)"
    Maintain two sequences $a,b$ and perform the following operations:
    
    1.  `1 l r x`: $\forall l\le i\le r,~ a_i=\min(a_i,x)$.
    2.  `2 l r x`: $\forall l\le i\le r,~ b_i=\min(b_i,x)$.
    3.  `3 l r x`: $\forall l\le i\le r,~ a_i=a_i+x$.
    4.  `4 l r x`: $\forall l\le i\le r,~ b_i=b_i+x$.
    5.  `5 l r`: output $\max\limits_{i=l}^r (a_i+b_i)$.
    
    $n,m\le 3\times 10^5,~|a_i|,|b_i|,|x|\le 10^9$.

We split the candidate answers $A_i+B_i$ in the range $[l,r]$ into four classes: $A_i,B_i$ are both not the range maxima of sequences $A,B$; $A_i$ is the range maximum of sequence $A$ but $B_i$ is not the range maximum of sequence $B$; $A_i$ is not the range maximum of sequence $A$ but $B_i$ is the range maximum of sequence $B$; $A_i,B_i$ are both the range maxima of sequences $A,B$. Call the best values of these classes $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$. We also maintain the range maximum and second maximum of sequences $A,B$ as usual. When pushing down range-add tags and $\min$ tags, the maxima and second maxima of $A,B$ are handled the same way as in the two examples above. A $\min$ tag on $A$ affects $C_{1,1}$ and $C_{1,0}$, and a tag on $B$ affects $C_{1,1}$ and $C_{0,1}$. Adding to $A,B$ affects all of $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$. Just watch out for the edge cases where $C_{0,0},C_{1,0},C_{0,1}$ do not exist (for example, in a range $[i,i]$ only the maxima of $A,B$ and $C_{1,1}$ exist).

Next, consider how to maintain $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ in pushup. After updating the maxima of $A,B$, we check whether the left and right children's maxima of $A,B$ equal the current node's maxima of $A,B$. We explain using the left child; the right child is handled the same way:

-   If the left child's maxima of $A,B$ both equal the current node's maxima of $A,B$, the left child's $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ contribute to the current node's $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ respectively.
-   If the left child's $A$ maximum equals the current node's $A$ maximum but the $B$ maxima differ, the left child's $C_{1,0},C_{1,1}$ contribute to the node's $C_{1,0}$, and $C_{0,0},C_{0,1}$ contribute to the node's $C_{0,0}$.
-   If the left child's $A$ maximum differs from the current node's $A$ maximum but the $B$ maxima are equal, the left child's $C_{0,1},C_{1,1}$ contribute to the node's $C_{0,1}$, and $C_{0,0},C_{1,0}$ contribute to the node's $C_{0,0}$.
-   If the left child's maxima of $A,B$ both differ from the current node's maxima of $A,B$, the left child's $C_{0,0},C_{1,0},C_{0,1},C_{1,1}$ only contribute to the node's $C_{0,0}$.

The answer to a range query is $\max(C_{0,0},C_{1,0},C_{0,1},C_{1,1})$.

Since we need to maintain both range $\min$ and range add, the complexity is still $O(m\log^2 n)$.

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_4.cpp"
```

### Summary

In this section we gave four example problems, covering the maintenance of basic range chmin/chmax operations, handling the priority of several tags, the idea of splitting values into classes, and maintaining several classes at once. In essence, the basic idea behind range chmin/chmax is to maintain information for each class of values separately and merge it efficiently. In the next section, we look at problems about historical extreme values.

## Historical extreme values

### Historical extremes are not persistence

Note that the historical-value problems in this section are different from so-called persistent data structures. We call this special kind of problem a historical extreme value problem. These problems fall into three kinds.

#### Historical maximum

Simply put, the historical maximum of a position is the largest number that has ever appeared at that position. Formally, we define an auxiliary array $B$ that starts out identical to $A$. After each operation on $A$, we take the $\max$ over the whole array:

$$
\forall i\in[1,n],\ B_i=\max(B_i,A_i)
$$

Then we call $B_i$ the historical maximum of this position,

#### Historical minimum

The definition is similar to the historical maximum: after each operation on $A$, we take the $\min$ over the whole array. Then we call $B_i$ the historical minimum of this position,

#### Historical version sum

The auxiliary array $B$ starts out all $0$. After each operation, we add the whole array $A$ onto array $B$

$$
\forall i\in[1,n], \ B_i=B_i+A_i
$$

We call $B_i$ the historical version sum at position $i$.

Next, we discuss historical extreme value problems in four categories.

### Problems that can be handled with tags

???+ note "[CPU Monitoring](https://www.luogu.com.cn/problem/P4314)"
    Sequences $A,B$ start out the same:
    
    1.  Range assign $x$ on $A$
    2.  Range add $x$ on $A$
    3.  Query a range $\max$ of $A$
    4.  Query a range $\max$ of $B$
    
    After each operation, we update $\forall i\in [1,n],\ B_i=\max(B_i,A_i)$. $n,m\le 10^5$.

Ignore operation 1 for now. Then there is only range add, and we maintain a tag $Add$ for the value added to the current range. This tag handles range $\max$. Next consider the historical range $\max$. We define a tag $Pre$, meaning: the historical maximum of the $Add$ tag during the lifetime of this tag.

This definition may be a bit vague, so let us first explain the lifetime of a tag. A tag goes through this process:

1.  It is created at node $u$.
2.  While node $u$ receives several new tags, it merges with them (tags of the same kind)
3.  The tag of node $u$ is pushed down to $u$'s children, and $u$'s tag is cleared

We say the lifetime of node $u$'s tag runs from step 1 up to just before step 3. When two tags are merged, they become one tag, and their lifetimes merge too (the earlier creation time is taken as the start of the lifetime). An equivalent way to say it: the lifetime is the period from the last time this node's tag was pushed down until now.

Why define a lifetime? With this concept we can prove: during the lifetime of a node's tag, none of its children change at all, and they keep the state they had before this lifetime began. The reason is simple: during this period no tags are pushed down.

So we can be sure that the maximum historical $Add$ during the current tag's lifetime can be applied to the tags and information of the children, because the children's tags and information have not changed during this period. So when we push the tag of $u$ down to its child $s$, it is easy to see that

$$
Pre_s=\max(Pre_s,Pre_u+Add_s),Add_s=Add_u+Add_s
$$

The information is updated in a similar way, using the corresponding tags.

Next, consider operation 1.

A range assign turns all numbers into one value. After that, whether we add to or assign the range, all numbers in the range stay equal (unless we end the current tag's lifetime by pushing the tag down). So we can treat every tag after the first range assign as a range assign tag. In other words, a tag's lifetime splits roughly into two stages:

1.  A merge of several add tags, with no assign tag received yet.
2.  Assign tags, with no add tags as such (add tags are turned into assign tags)

So we split the node's Pre tag into $(P_1,P_2)$. $P_1$ is the largest add tag in the first stage, and $P_2$ is the largest assign tag in the second stage. With a similar method, we can push down tags and update information for this. The time complexity is $O(m\log n)$ (note that this problem has no range chmin/chmax with $x$!)

```cpp
--8<-- "docs/ds/code/seg-beats/seg-beats_3.cpp"
```
