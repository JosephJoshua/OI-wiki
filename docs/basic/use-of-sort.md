This page gives a short introduction to the uses of sorting.

## Understanding the data

Sorting data helps us understand its features and makes later analysis and visualization easier. Think of everyday examples like dictionaries and menus: if they were not arranged in some order, it would take people much longer to find what they need.

Computers have to handle large amounts of data. Once the data is sorted, people can design the rest of the processing based on the data's features and their needs.

## Lowering the time complexity

Sorting the data first can lower the time complexity needed to solve a problem. This is usually a trade of space for time. If a sorted list needs to be analyzed many times, paying the cost of sorting just once is well worth it, because every later analysis can save a lot of time.

???+ note "Example: check whether a given sequence has equal elements"
    Consider a sequence of numbers. You need to check whether any two of its elements are equal.
    
    A naive approach is to check every pair of numbers and see whether the two are equal. This takes $O(n^2)$ time.
    
    Instead, we can sort the sequence first. Then it is easy to see that if two numbers are equal, they must be next to each other in the new sequence. So we only need one $O(n)$ scan over the new sequence.
    
    The total time complexity is that of sorting, $O(n\log n)$.

## Preprocessing for searching

Sorting is the preprocessing step that [binary search](./binary.md) needs. After sorting, binary search can find a given element in the sequence in $O(\log n)$ time.
