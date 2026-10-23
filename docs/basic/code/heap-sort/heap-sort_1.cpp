#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

// --8<-- [start:sort]
void sift_down(int arr[], int start, int end) {
  // Compute the indices of the parent and child
  int parent = start;
  int child = parent * 2 + 1;
  while (child <= end) {  // compare only while the child index is in range
    // First compare the two children and pick the larger one
    if (child + 1 <= end && arr[child] < arr[child + 1]) child++;
    // If the parent is larger than the child, we are done; return
    if (arr[parent] >= arr[child])
      return;
    else {  // otherwise swap parent and child, then compare the child with its children
      swap(arr[parent], arr[child]);
      parent = child;
      child = parent * 2 + 1;
    }
  }
}

void heap_sort(int arr[], int len) {
  // Sift down from the parent of the last node to build the heap (heapify)
  for (int i = (len - 1 - 1) / 2; i >= 0; i--) sift_down(arr, i, len - 1);
  // Swap the first element with the one just before the sorted part, then re-adjust the elements before it, until sorted
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    sift_down(arr, 0, i - 1);
  }
}

// --8<-- [end:sort]

int main() {
  int n;
  if (!(cin >> n) || n < 0) return 0;
  vector<int> a(n + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  heap_sort(a.data(), n);
  for (int i = 0; i < n; ++i) cout << a[i] << ' ';
  cout << '\n';
}
