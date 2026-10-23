#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// --8<-- [start:sort]
// The template parameter T is the element type; it must define less-than (<)
template <typename T>
// arr is the array to search, rk is the rank to find (0-based), len is its length
T find_kth_element(T arr[], int rk, const int len) {
  if (len <= 1) return arr[0];
  // Pick a random pivot
  const T pivot = arr[rand() % len];
  // i: index of the current element
  // arr[0, j): elements less than pivot
  // arr[k, len): elements greater than pivot
  int i = 0, j = 0, k = len;
  // One pass of 3-way partitioning splits the array into:
  // elements < pivot | elements == pivot | elements > pivot
  while (i < k) {
    if (arr[i] < pivot)
      swap(arr[i++], arr[j++]);
    else if (pivot < arr[i])
      swap(arr[i], arr[--k]);
    else
      i++;
  }
  // Compare the rank with the two boundaries and recurse into the part that holds the element at sorted index k
  // If more than k elements are less than pivot, the element at sorted index k must be
  // less than pivot
  if (rk < j) return find_kth_element(arr, rk, j);
  // Otherwise, if the elements less than or equal to pivot are still not more than k,
  // the element at sorted index k must be greater than pivot
  else if (rk >= k)
    return find_kth_element(arr + k, rk - k, len - k);
  // Otherwise, pivot is the element at sorted index k
  return pivot;
}

// --8<-- [end:sort]

int main() {
  int n, k;
  if (!(cin >> n >> k) || n <= 0 || k < 0 || k >= n) return 0;
  vector<int> a(n);
  for (int& x : a) cin >> x;
  cout << find_kth_element(a.data(), k, n) << '\n';
}
