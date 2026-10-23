#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// --8<-- [start:sort]
// The template parameter T is the element type; it must define less-than (<)
template <typename T>
// arr is the array to sort, len is its length
void quick_sort(T arr[], const int len) {
  if (len <= 1) return;
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
  // Recursively quicksort the two parts
  quick_sort(arr, j);
  quick_sort(arr + k, len - k);
}

// --8<-- [end:sort]

int main() {
  int n;
  if (!(cin >> n) || n < 0) return 0;
  vector<int> a(n + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  quick_sort(a.data(), n);
  for (int i = 0; i < n; ++i) cout << a[i] << ' ';
  cout << '\n';
}
