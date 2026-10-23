#include <iostream>
#include <vector>
using namespace std;
// --8<-- [start:core]
constexpr unsigned MAXN = 1000;  // number of values to sort
constexpr unsigned RADIX = 10;   // radix
constexpr unsigned powRADIX[10] = {1,         10,        100,     1000,
                                   10000,     100000,    1000000, 10000000,
                                   100000000, 1000000000};  // powers of RADIX

unsigned get_digit(unsigned value, int digit)  // get the digit at position `digit`
{
  return (value / powRADIX[digit]) % RADIX;
}

void MSD_radix_sort(unsigned* begin, unsigned* end, int digit)
// All elements in [begin,end) share the same leading digits (in base 10)
// Only the last `digit` digits (positions digit-1 down to 0) still need sorting
// Example call: MSD_radix_sort(a,a+n,10)
{
  if (begin >= end)  // empty range
  {
    return;
  }
  /**Counting sort (just one way to write it)**/
  static unsigned cnt[RADIX + 1],
      tmp[MAXN + 5];  // recursion levels never use cnt,tmp at the same
                      // time (each level finishes before calling the next), so
                      // making them static saves space
  vector<unsigned> beg;
  beg.resize(RADIX + 1);  // accesses to beg may conflict, so use a local variable
  for (int i = 0; i <= RADIX; i++) {
    cnt[i] = beg[i] = 0;  // clearing is a good habit
  }
  for (unsigned* it = begin; it != end; it++)  // count
  {
    int bitVal = get_digit(*it, digit - 1);
    cnt[bitVal] += 1;
  }
  beg[0] = 0;  // compute where each digit value starts (offset)
  for (int i = 1; i <= RADIX; i++) {
    beg[i] = beg[i - 1] + cnt[i - 1];
  }
  // We also compute beg[RADIX] so the range for i is simply [beg[i],beg[i+1])
  // without worrying about beg[i+1] going out of bounds
  for (int i = 0; i < RADIX; i++) {
    cnt[i] = 0;
  }
  for (unsigned* it = begin; it != end; it++)  // put the counting sort result into tmp
  {
    unsigned bitVal = get_digit(*it, digit - 1);  // get the digit at position digit - 1
    // Going in the original order, this is element number cnt[bitVal]+1 with bitVal at position digit-1
    tmp[beg[bitVal] + cnt[bitVal]] = *it;
    cnt[bitVal]++;
  }
  for (unsigned* it = begin; it != end; it++)  // copy tmp back into the original array
  {
    *it = tmp[it - begin];
  }
  /**Recursively sort each bucket by the next digit**/
  if (digit == 1)  // already the lowest digit
  {
    return;
  }
  for (int i = 0; i < RADIX; i++)  // recursively sort by the next digit
  {
    MSD_radix_sort(begin + beg[i], begin + beg[i + 1], digit - 1);
  }
}

// --8<-- [end:core]
unsigned a[MAXN + 5];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) cin >> a[i];
  MSD_radix_sort(a + 1, a + n + 1, 10);
  for (int i = 1; i <= n; i++) cout << a[i] << " \n"[i == n];
}
