#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <limits>
#include <vector>

// --8<-- [start:array]
void merge(const int* a, size_t aLen, const int* b, size_t bLen, int* c) {
  size_t i = 0, j = 0, k = 0;
  while (i < aLen && j < bLen) {
    if (b[j] < a[i]) {  // <!> check b[j] < a[i] first to keep the sort stable
      c[k] = b[j];
      ++j;
    } else {
      c[k] = a[i];
      ++i;
    }
    ++k;
  }
  // Now one array is empty and the other is not; append the non-empty one to c
  for (; i < aLen; ++i, ++k) c[k] = a[i];
  for (; j < bLen; ++j, ++k) c[k] = b[j];
}

// --8<-- [end:array]

// --8<-- [start:pointer]
void merge(const int* aBegin, const int* aEnd, const int* bBegin,
           const int* bEnd, int* c) {
  while (aBegin != aEnd && bBegin != bEnd) {
    if (*bBegin < *aBegin) {
      *c = *bBegin;
      ++bBegin;
    } else {
      *c = *aBegin;
      ++aBegin;
    }
    ++c;
  }
  for (; aBegin != aEnd; ++aBegin, ++c) *c = *aBegin;
  for (; bBegin != bEnd; ++bBegin, ++c) *c = *bBegin;
}

// --8<-- [end:pointer]

// --8<-- [start:recursive]
void merge_sort(int* a, int l, int r) {
  if (r - l <= 1) return;
  // Divide
  int mid = l + ((r - l) >> 1);
  merge_sort(a, l, mid);
  merge_sort(a, mid, r);
  // Merge
  std::vector<int> tmp(r - l);  // allocate a buffer only for the range being merged
  merge(a + l, a + mid, a + mid, a + r, tmp.data());
  for (int i = l; i < r; ++i) a[i] = tmp[i - l];
}

// --8<-- [end:recursive]

// --8<-- [start:iterative]
void merge_sort(int* a, size_t n) {
  std::vector<int> tmp(n);  // merge buffer is as long as the input
  for (size_t seg = 1; seg < n; seg <<= 1) {
    for (size_t left1 = 0; left1 < n - seg;
         left1 += seg + seg) {  // n - seg: no merge needed if only one segment is left
      size_t right1 = left1 + seg;
      size_t left2 = right1;
      size_t right2 = std::min(left2 + seg, n);  // <!> mind the bound of the last segment
      merge(a + left1, a + right1, a + left2, a + right2,
            tmp.data() + left1);  // pointer-style merge
      for (size_t i = left1; i < right2; ++i) a[i] = tmp[i];
    }
  }
}

// --8<-- [end:iterative]

using namespace std;

int main() {
  int n;
  if (!(cin >> n) || n < 0) return 0;
  vector<int> a(n + 1), b(n + 1), c(n + 1);
  for (int i = 0; i < n; ++i) cin >> a[i];
  auto print = [&](const vector<int>& v) {
    for (int i = 0; i < n; ++i) cout << v[i] << ' ';
    cout << '\n';
  };
  int mid = n / 2;
  b = a;
  sort(b.begin(), b.begin() + mid);
  sort(b.begin() + mid, b.begin() + n);
  ::merge(b.data(), size_t(mid), b.data() + mid, size_t(n - mid), c.data());
  vector<int> expected = c;
  ::merge(b.data(), b.data() + mid, b.data() + mid, b.data() + n, c.data());
  if (c != expected) return 1;
  print(c);
  b = a;
  merge_sort(b.data(), 0, n);
  print(b);
  merge_sort(a.data(), size_t(n));
  print(a);
}
