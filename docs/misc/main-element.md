author: SDLTF, Ethkuil

## Problem

Given a sequence of $n$ elements, where some element $a$ is guaranteed to appear **strictly more than**  $n/2$ times, find that element.

## Approach

### Offline algorithm

If we know the whole sequence from the start, a natural idea is to count how many times each element appears; the one that appears more than $n/2$ times is the majority element. We can use a bucket to count each element and output the one with a count greater than $n/2$.

But this uses a bucket for counting, which is not space-efficient. Clearly, if the sequence has a majority element, then after sorting, the $(\lfloor n/2\rfloor+1)$-th element must be the majority element, and [`nth_element`](https://en.cppreference.com/w/cpp/algorithm/nth_element.html) can find it. This finds the majority element in linear time without extra space.

### Online algorithm

Sometimes we need to process streaming data online. Then we need an algorithm that doesn't know all the data in advance, but works out the answer step by step using only the data given so far. The **Boyer–Moore majority vote algorithm** [^ref1] is an algorithm that solves the majority element problem online.

Since the majority element appears more than $n/2$ times, if we keep cancelling one majority element against one element different from it, the majority element must be what is left at the end. Based on this observation, we can design an online algorithm that does this cancelling. Let the two variables `val` and `cnt` be the current majority candidate and how many copies of the candidate would remain after such cancelling so far. Initially `cnt` is set to $0$. Take elements from the stream one at a time. If `cnt` is currently $0$, the candidate has been completely cancelled, so the recorded `val` cannot be the majority element, and we make the current element the candidate. Then check whether the current element equals the candidate: if it does, increase `cnt` by $1$; if not, this element cancels out with one copy of the candidate, so decrease `cnt` by $1$. Repeat until the stream is exhausted; `val` is then the majority element.

???+ warning "Note"
    If the data has no majority element, the result of this algorithm is wrong. To check whether the sequence has a majority element, read the stream again, count how many times `val` appears, and check whether it exceeds $n/2$.
    
    To read the stream again, you can reset the input position indicator using library functions such as [`std::basic_istream<CharT,Traits>::seekg`](https://en.cppreference.com/w/cpp/io/basic_istream/seekg) (stream input) or [`rewind`](https://en.cppreference.com/w/c/io/rewind) and [`fseek`](https://en.cppreference.com/w/c/io/fseek) (C-style input).

## Example problems

???+ example "[Luogu P2397 yyy loves Maths VI (mode)](https://www.luogu.com.cn/problem/P2397)"
    Find the majority element of the given sequence.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/main-element/main-element_1.cpp"
    ```

???+ example "[LeetCode 229. Majority Element II](https://leetcode.cn/problems/majority-element-ii)"
    Given an integer array of size $n$, find all elements that appear more than $\lfloor n/3\rfloor$ times.

??? note "Reference code"
    ```cpp
    --8<-- "docs/misc/code/main-element/main-element_2.cpp:core"
    ```

## References

[^ref1]: [Boyer–Moore majority vote algorithm - Wikipedia (Chinese)](https://zh.wikipedia.org/zh-cn/%E5%A4%9A%E6%95%B0%E6%8A%95%E7%A5%A8%E7%AE%97%E6%B3%95)
