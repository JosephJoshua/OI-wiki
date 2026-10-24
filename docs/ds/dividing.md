author: Xarfa

## Introduction

The partition tree is a data structure for finding the $K$-th largest value in a range. Both its constant factor and its difficulty to understand are much lower than those of a persistent segment tree. Since the partition tree is built around the "$K$-th largest", it is a data structure based on sorting.

Prerequisite: [persistent segment tree](persistent-seg.md#persistent-segment-tree-chairman-tree)

## Process

### Building the tree

Building a partition tree is fairly simple, though more involved than building some other trees.

![](./images/dividing-1.svg)

As shown in the figure, each level has an array that looks unordered. In fact, every number marked in red **goes to the left child**. What is the rule? Compare it with **the median of this level**: if it is less than or equal to the median, it goes left; otherwise it goes right. But note: the rule is not strictly **less than or equal goes left, otherwise right**, because the median value may appear more than once, and it also depends on whether $N$ is odd or even. The code below shows a neat trick for this; refer to it.

We cannot sort every level each time. That would be too slow, not just in its constant factor but even in theoretical complexity. To find medians, a single sort is enough. Why? For example, the median of $l,r$ is just `num[mid]` in the sorted array.

Two key arrays:

tree\[log(N),N]: the tree itself. It stores all the values, with space complexity $O(n\log n)$.
toleft\[log(N),n]: for each level, the number of elements among 1\~i that go to the left child. Note that this is a prefix sum.

???+ note "Implementation"
    ```pascal
    procedure Build(left,right,deep:longint); // left,right are the range endpoints, deep is the level
    var
      i,mid,same,ls,rs,flag:longint; // flag is used to balance the counts on the two sides
    begin
      if left=right then exit; // reached the bottom
      mid:=(left+right) >> 1;
      same:=mid-left+1;
      for i:=left to right do 
        if tree[deep,i]<num[mid] then
          dec(same);
      
      ls:=left; // pointer to the next slot in the left child
      rs:=mid+1; // pointer to the next slot in the right child
      for i:=left to right do
      begin
        flag:=0;
        if (tree[deep,i]<num[mid])or((tree[deep,i]=num[mid])and(same>0)) then // condition for going left
        begin
          flag:=1; tree[deep+1,ls]:=tree[deep,i]; inc(ls);
          if tree[deep,i]=num[mid] then // balance the counts on the two sides
            dec(same);
        end
        else
        begin
          tree[deep+1,rs]:=tree[deep,i]; inc(rs);
        end;
        toleft[deep,i]:=toleft[deep,i-1]+flag;
      end;
      Build(left,mid,deep+1); // continue
      Build(mid+1,right,deep+1);
    end;
    ```

### Query

First, a quick word about the persistent segment tree. When finding the $K$-th smallest value in a range with a persistent segment tree, we compare against $K$: going left, we just go left; going right, we subtract the count on the left. The partition tree works the same way.

The hard part of the query is **shrinking the range**. In the figure below, we query $3$ to $7$, so on the next level we only need to query $2$ to $3$. We define $[\text{left},\text{right}]$ as the shrunken range (the target range), and $[l,r]$ is still the range of the current node. Why mark the target range? Because it is **what decides whether the answer is on the left or on the right**.

![](./images/dividing-2.svg)

???+ note "Implementation"
    ```pascal
    function Query(left,right,k,l,r,deep:longint):longint;
    var
      mid,x,y,cnt,rx,ry:longint;
    begin
      if left=right then // writing l=r is also fine, because the target range must contain the answer
        exit(tree[deep,left]);
      mid:=(l+r) >> 1;
      x:=toleft[deep,left-1]-toleft[deep,l-1]; // number going to the left child from l to left
      y:=toleft[deep,right]-toleft[deep,l-1]; // number going to the left child from l to right
      ry:=right-l-y; rx:=left-l-x; // ry is the number going to the right child from l to right, rx the number from l to left
      cnt:=y-x; // number going to the left child from left to right
      if cnt>=k then // standard persistent segment tree reasoning
        Query:=Query(l+x,l+y-1,k,l,mid,deep+1) // l+x shrinks the left bound, l+y-1 shrinks the right bound. In the figure above, this drops nodes 1 and 2.
      else
        Query:=Query(mid+rx+1,mid+ry+1,k-cnt,mid+1,r,deep+1); // also shrinking the range, just on the right side. Remember to subtract cnt from k.
    end;
    ```

## Properties

Time complexity: one query takes only $O(\log n)$, so $m$ queries take $O(m\log n)$.

Space complexity: we only need to store $O(n\log n)$ numbers.

Measured results: persistent segment tree: $1482 \text{ms}$, partition tree: $889 \text{ms}$. (Non-recursive, with a fairly small constant factor.)

## Applications of the partition tree

Example problem: [Luogu P3157 [CQOI2011] Dynamic Inversions](https://www.luogu.com.cn/problem/P3157)

> Problem summary: given a permutation of $n$ elements ($n\leq 10^5$) and m queries ($m\leq 5\times 10^4$), each query deletes one number from the permutation. After each deletion, output the number of inversions in the permutation.

This problem can be solved with CDQ in $\Theta(n\log^2n)$ time and $\Theta(n)$ space, and CDQ also has a very good constant factor.

If the problem were forced online, it would usually be solved with a tree-in-tree, a Fenwick tree of persistent segment trees. The time complexity is $\Theta(n\log^2n)$ and the space complexity is $\Theta(n\log^2n)$. The constant factor is a bit large, but it also passes.

With a partition tree, we can solve the problem online in $\Theta(n\log^2n)$ time and $\Theta(n\log n)$ space, with a much smaller constant factor than the tree-in-tree solution (roughly the same as CDQ).

???+ warning "Note"
    To make the implementation easier, this article splits a large array into two smaller arrays by the middle position. In other words, the partition tree below works like merge sort rather than quicksort. The large array at the top level is sorted, and the bottom level is the original array.

For each node in the partition tree, we call it a right node if and only if it is sent to the right child on the next level, that is, it is one of the numbers that come later in the original array. Left nodes are defined similarly. If the top level is sorted when building the tree, then, just like counting inversions with merge sort, the number of inversions of the array is the total number of right nodes before each left node.

Now consider deletion. Deleting a left node decreases the number of inversions of the whole array by the number of right nodes before it, and deleting a right node decreases it by the number of left nodes after it. So we can dynamically maintain "the number of right nodes before each left node" and "the number of left nodes after each right node". This is easy to do with Fenwick trees.

Note that when maintaining these with Fenwick trees, we may only count contributions inside the same block of the partition tree and must not leave the block. There is a fairly neat way to handle this with Fenwick trees.

The index range of each block of the partition tree always has the form $[c\times 2^k+1,(c+1)\times 2^k]$, as listed below (the code never deals with the bottom level of the partition tree, so we only list up to the second-to-last level):

    [0001 0010] [0011 0100] [0101 0110] [0111 1000] [1001 1010] [1011 1100] [1101 1110] [1111 10000]  lev=1
    [0001 0010 0011 0100]   [0101 0110 0111 1000]   [1001 1010 1011 1100]   [1101 1110 1111 10000]    lev=2
    [0001 0010 0011 0100 0101 0110 0111 1000]       [1001 1010 1011 1100 1101 1110 1111 10000]        lev=3
    [0001 0010 0011 0100 0101 0110 0111 1000 1001 1010 1011 1100 1101 1110 1111 10000]                lev=4

Recall how a Fenwick tree works: when jumping up, we do `x += lowbit(x)` each time. If we can make sure we never leave the block while jumping up, we only affect values inside the block. Queries work similarly.

To make sure we stay inside the block while jumping up, we only need $lowbit(x)<2^{lev}$ to hold at every jump.

Jumping down is handled in a completely different way. With 0-indexing, the indices of each block have the form $[c\times 2^k,(c+1)\times 2^k)$. So shifting an index right by k tells us which block it is in. When jumping down, just check at every step whether we have left the block.

Note that a Fenwick tree implemented this way may access indices up to the power of 2 closest to n, so the array size cannot be just n.

Since we update on $\log n$ levels, and an update on level $k$ takes $\Theta(k)$ time, the final time complexity is $\Theta(n\log n+m\log^2n)$.

Code:

```cpp
--8<-- "docs/ds/code/dividing/dividing_1.cpp"
```

## Afterword

Reference blog post: [link](https://blog.csdn.net/littlewhite520/article/details/70250722).
