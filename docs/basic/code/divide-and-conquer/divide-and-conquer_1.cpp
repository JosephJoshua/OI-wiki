#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

template <typename T>
void merge(vector<T>& a, int front, int mid, int end) {
  vector<T> tmp(end - front + 1);
  std::merge(a.begin() + front, a.begin() + mid + 1, a.begin() + mid + 1,
             a.begin() + end + 1, tmp.begin());
  std::copy(tmp.begin(), tmp.end(), a.begin() + front);
}

// --8<-- [start:sort]
// Merge sort without recursion
template <typename T>
void merge_sort(vector<T>& a) {
  int n = a.size();
  for (int seg = 1; seg < n; seg = seg + seg)
    for (int start = 0; start < n - seg; start += seg + seg)
      merge(a, start, start + seg - 1, std::min(start + seg + seg - 1, n - 1));
}

// Merge sort with recursion
template <typename T>
void merge_sort(vector<T>& a, int front, int end) {
  if (front >= end) return;
  int mid = front + (end - front) / 2;
  merge_sort(a, front, mid);
  merge_sort(a, mid + 1, end);
  merge(a, front, mid, end);
}

// --8<-- [end:sort]

int main() {
  int n;
  if (!(cin >> n) || n < 0) return 0;
  vector<int> a(n);
  for (int i = 0; i < n; ++i) cin >> a[i];
  vector<int> b = a;
  merge_sort(b, 0, n - 1);
  for (int x : b) cout << x << ' ';
  cout << '\n';
  merge_sort(a);
  for (int i = 0; i < n; ++i) cout << a[i] << ' ';
  cout << '\n';
}
