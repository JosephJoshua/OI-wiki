This page gives a short introduction to the two-pointer technique.

## Introduction

Two pointers is a simple yet flexible technique and idea. On its own it can easily solve some specific problems, and combined with other algorithms it has many uses.

As the name suggests, two pointers means using two pointers at the same time. On sequences and linked lists they point to positions; on trees and graphs they point to nodes. By moving them in the same direction or toward each other, we maintain or count some information.

Next, let's look at several concrete ways to use two pointers.

## Maintaining interval information

Without combining it with other data structures, the simplest pattern for maintaining interval information with two pointers is to maintain information that has some monotonicity and that is easy to update when adding or removing one element, such as the sum of positive numbers or the product of positive integers.

### Example problem 1

???+ note "Example problem 1 [LeetCode 713. Subarray Product Less Than K](https://leetcode-cn.com/problems/subarray-product-less-than-k/)"
    Given an array $\mathit{nums}$ of $n$ positive integers and an integer $k$, find the number of contiguous subarrays whose product is less than $k$.
    
    Constraints: $1 \leq n \leq 3 \times 10^4, 1 \leq nums[i] \leq 1000, 0 \leq k \leq 10^6$.

#### How it works

Call the two pointers $l$ and $r$, and keep a variable $\mathit{tmp}$ holding the product of all numbers in $[l,r]$. At first both $l$ and $r$ are at the far left. Move $r$ to the right until $\mathit{tmp}\geq k$ for the first time. Then fix $r$ and move $l$ to the right until $\mathit{tmp}\lt k$. So for each $r$, $l$ is the leftmost position it can extend to. Because products of positive integers are monotonic, the number of valid intervals with right endpoint $r$ is $r-l+1$.

#### Implementation

```cpp
int numSubarrayProductLessThanK(vector<int>& nums, int k) {
  long long ji = 1ll, ans = 0;
  int l = 0;
  for (int i = 0; i < nums.size(); ++i) {
    ji *= nums[i];
    while (l <= i && ji >= k) ji /= nums[l++];
    ans += i - l + 1;
  }
  return ans;
}
```

Maintaining interval information with two pointers can also be combined with other data structures, such as difference arrays, monotonic queues, segment trees, and persistent segment trees. Mo's algorithm also builds the two-pointer technique into an algorithm: after sorting the queries offline, it usually keeps two pointers marking the interval being processed, and updates the interval information as the pointers move step by step.

### Example problem 2

Next, here is an example that uses two pointers on a tree together with difference arrays on trees:

???+ note "Example problem 2 [Luogu P3066 Running Away From the Barn G](https://www.luogu.com.cn/problem/P3066)"
    You are given a rooted tree with $n$ nodes and weighted edges. Nodes are numbered from 1 to $n$, and node 1 is the root. You are also given a parameter $t$. For each node $u$ in the tree, find how many nodes in the subtree of $u$ are at distance at most $t$ from $u$. Constraints: $1\leq n \leq 2\times 10^5,1 \leq t \leq 10^{18},1 \leq p_i \lt i,1 \leq w_i \leq 10^{12}$

#### How it works

Traverse the whole tree with DFS from the root, using a stack to record the path from the root to the current node. Let one pointer $u$ point to the current node, and another pointer $p$ point to the shallowest node whose distance to $u$ is at most $t$. Record each node's distance to the root, and find $p$ with a binary search each time. Then $u$ contributes to every node on the path from $p$ to $u$, which can be recorded with a difference array on the tree.  
Note that you cannot simply move $p$ by brute force, or the time complexity may degrade to $O(n^2)$.

### Exercises

[LeetCode 1438. Longest Continuous Subarray With Absolute Diff Less Than or Equal to Limit](https://leetcode-cn.com/problems/longest-continuous-subarray-with-absolute-diff-less-than-or-equal-to-limit/)

## Subsequence matching

???+ note "Example problem 3 [LeetCode 524. Longest Word in Dictionary through Deleting](https://leetcode-cn.com/problems/longest-word-in-dictionary-through-deleting/)"
    Given a string $s$ and an array of strings $\mathit{dictionary}$, find and return the longest string in the dictionary that can be obtained by deleting some characters of $s$.

### How it works

Problems like this require matching a string $t$ against $s$ to decide whether $t$ is a subsequence of $s$. To do this, put one pointer $i$ at the start of $s$ and another pointer $j$ at the start of $t$. If $s[i]=t[j]$, the $j$-th character of $t$ has found its first match in $s$, and we can move on to check the rest, so we increase both $i$ and $j$ by one. If they are not equal, the $j$-th character of $t$ is still unmatched, so we only increase $i$ and keep searching in the rest of $s$. At the end, if $j$ has moved past the last character, the whole string has been matched, meaning $t$ is a subsequence of $s$; otherwise it is not.

### Implementation

```cpp
string findLongestWord(string s, vector<string>& dictionary) {
  sort(dictionary.begin(), dictionary.end());
  int mx = 0, r = 0;
  string ans = "";
  for (int i = dictionary.size() - 1; i >= 0; i--) {
    r = 0;
    for (int j = 0; j < s.length(); ++j) {
      if (s[j] == dictionary[i][r]) r++;
    }
    if (r == dictionary[i].length()) {
      if (r >= mx) {
        mx = r;
        ans = dictionary[i];
      }
    }
  }
  return ans;
}
```

This method, where two pointers point into different objects and compare them step by step, can also be used in some DP problems.

## Using the order of a sequence

Often, two pointers on a sequence work correctly because of some property of the sequence. The most common one is that the sequence is sorted.

???+ note "Example problem 4 [LeetCode 167. Two Sum II - Input Array Is Sorted](https://leetcode-cn.com/problems/two-sum-ii-input-array-is-sorted/)"
    Given an integer array `numbers` that is already **sorted in ascending order**, find two numbers in it that add up to the target number `target`.

### How it works

This is a classic application of two pointers. Binary search also works conveniently, but it adds an extra $\log{n}$ factor to the time complexity, and the code is less concise.

Here is the two-pointer approach. We need to find two numbers, and they cannot be at the same position, so one must be on the left and the other on the right. Since their sum is fixed, the larger the smaller number is, the smaller the larger number is. With these properties in mind, we can approach them from both ends.

First, assume the answer is positions 1 and n. If $num[1]+num[n]\gt \mathit{target}$, we need to make one of the elements smaller. But $\mathit{num}[1]$ cannot get any smaller, so we decrease the pointer at $n$ by one to make the larger number smaller.

Similarly, if $num[1]+num[n]\lt \mathit{target}$, we need to make one of the elements larger. But $\mathit{num}[n]$ cannot get any larger, so we increase the pointer at 1 by one to make the smaller number larger.

In general, suppose the two pointers are at $l$ and $r$ with $l\lt r$. If $num[l]+num[r]\gt \mathit{target}$, decrease $r$ by one; if $num[l]+num[r]\lt \mathit{target}$, increase $l$ by one. This way $l$ keeps moving right and $r$ keeps moving left, until each of them reaches one of the answer positions.

### Implementation

```cpp
vector<int> twoSum(vector<int>& numbers, int target) {
  int r = numbers.size() - 1, l = 0;
  vector<int> ans;
  ans.clear();
  while (l < r) {
    if (numbers[l] + numbers[r] > target)
      r--;
    else if (numbers[l] + numbers[r] == target) {
      ans.push_back(l + 1), ans.push_back(r + 1);
      return ans;
    } else
      l++;
  }
  return ans;
}
```

In merge sort, merging two sorted arrays in $O(n+m)$ time is also a two-pointer method that relies on the arrays being sorted.

### Exercises

[LeetCode 15. 3Sum](https://leetcode-cn.com/problems/3sum/)

## Finding a cycle in a singly linked list

### How it works

There are several ways to find a cycle in a singly linked list. The fast and slow pointer method is one of the simplest, and we describe it here.

First, point both pointers at the head of the list. Move one pointer one step at a time and the other two steps at a time. If they meet, there is a cycle; otherwise there is none. The time complexity is $O(n)$.

If there is a cycle, how do we find where it starts?

Let's write down some equations. When they meet, suppose the slow pointer has taken $k$ steps in total, $l$ of them on the cycle (when the fast and slow pointers meet on the cycle, the slow pointer has not yet gone around it once). The fast pointer has taken $2k$ steps. Let the cycle length be $C$. Then

$$
\begin{align}
& \ 2 k=n \times C+l+(k-l) \\
& \ k=n \times C \\
\end{align}
$$

At the first meeting, $n$ takes the smallest positive integer value, 1. That is, $k=C$. Using this equation, after the two pointers meet, move one of them back to the head of the list and let both move one step at a time. The place where they meet again is the start of the cycle.

### Implementation

```cpp
--8<-- "docs/misc/code/two-pointer/two-pointer_1.cpp:core"
```

The time complexity is $O(n)$.
