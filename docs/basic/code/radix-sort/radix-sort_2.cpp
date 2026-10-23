#include <iostream>
#include <string>
#include <vector>
using namespace std;

// --8<-- [start:core]
constexpr int MAXN = 1000;

int get_digit(string* arr, int i, int dig) {
  if (arr[i][dig] == '\0') return 0;
  return arr[i][dig] - 'a' + 1;
}

void MSD_radix_sort_string_base(string* arr, int* begin, int* end,
                                int digit)  // main routine
// Sort strings made of lowercase letters only
// The arguments mean all elements in [begin,end) share positions [0,digit)
// Now sort starting from position digit
// Example call: MSD_radix_sort_string(a, a + n)
// Almost the same as the previous code, so fewer comments
// To save space and time we sort an index array; comparisons still use the strings' characters
{
  if (begin >= end) return;
  static int tmp[MAXN + 5];
  static int cnt[28];
  vector<int> beg;
  beg.resize(28);
  // Q: Why 28?
  // A: 0 = null character, 1-26 = a-z, 27 = extra space (to avoid out-of-bounds)
  for (int i = 0; i < 28; i++) cnt[i] = beg[i] = 0;
  for (int* it = begin; it != end; it++) cnt[get_digit(arr, *it, digit)] += 1;
  beg[0] = 0;
  for (int i = 1; i <= 27; i++) beg[i] = beg[i - 1] + cnt[i - 1];
  for (int i = 0; i < 28; i++) cnt[i] = 0;
  for (int* it = begin; it != end; it++) {
    int bitVal = get_digit(arr, *it, digit);
    tmp[beg[bitVal] + cnt[bitVal]] = *it;
    cnt[bitVal]++;
  }
  for (int* it = begin; it != end; it++) *it = tmp[it - begin];
  // No need to recurse on the null character, so recurse on 1~26 only
  for (int i = 1; i <= 26; i++)
    MSD_radix_sort_string_base(arr, begin + beg[i], begin + beg[i + 1],
                               digit + 1);
}

int label[MAXN + 5];

void MSD_radix_sort_string(string* begin, string* end)  // entry point
{
  static string tmp[MAXN + 5];
  int n = end - begin;
  for (int i = 0; i < n; i++) {
    label[i] = i;
    tmp[i] = *(begin + i);
  }
  MSD_radix_sort_string_base(tmp, label, label + n, 0);
  for (int i = 0; i < n; i++) {
    *(begin + i) = tmp[label[i]];
  }
}

// --8<-- [end:core]

string a[MAXN + 5];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  MSD_radix_sort_string(a + 1, a + n + 1);
  for (int i = 1; i <= n; i++) cout << a[i] << "\n";
}
