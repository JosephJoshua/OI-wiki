// --8<-- [start:mul]
int mulPowerOfTwo(int n, int m) {  // compute n*(2^m)
  return n << m;
}

int divPowerOfTwo(int n, int m) {  // compute n/(2^m)
  return n >> m;
}

// --8<-- [end:mul]
// --8<-- [start:abs]
int Abs(int n) {
  return (n ^ (n >> 31)) - (n >> 31);
  /* n>>31 gets the sign of n: if n is positive, n>>31 is 0; if n is negative, n>>31 is -1
    If n is positive, n^0=n and the number is unchanged; if n is negative we have n^(-1)
    We need the two's complement of n and -1, then XOR them,
    which negates n and gives the absolute value of n minus 1; subtracting -1 then gives the absolute value */
}

// --8<-- [end:abs]
// --8<-- [start:minmax]
// if a >= b, (a - b) >> 31 is 0; otherwise it is -1
int max(int a, int b) { return (b & ((a - b) >> 31)) | (a & (~(a - b) >> 31)); }

int min(int a, int b) { return (a & ((a - b) >> 31)) | (b & (~(a - b) >> 31)); }

// --8<-- [end:minmax]
// --8<-- [start:sgn]
bool isSameSign(int x, int y) {  // except when one of them is 0
  return (x ^ y) >= 0;
}

// --8<-- [end:sgn]
// --8<-- [start:swap]
void swap(int& a, int& b) { a ^= b ^= a ^= b; }

// --8<-- [end:swap]
// --8<-- [start:get_bit]
// get bit b of a; the lowest bit is numbered 0
int getBit(int a, int b) { return (a >> b) & 1; }

// --8<-- [end:get_bit]
// --8<-- [start:unset_bit]
// set bit b of a to 0; the lowest bit is numbered 0
int unsetBit(int a, int b) { return a & ~(1 << b); }

// --8<-- [end:unset_bit]
// --8<-- [start:set_bit]
// set bit b of a to 1; the lowest bit is numbered 0
int setBit(int a, int b) { return a | (1 << b); }

// --8<-- [end:set_bit]
// --8<-- [start:flap_bit]
// flip bit b of a; the lowest bit is numbered 0
int flapBit(int a, int b) { return a ^ (1 << b); }

// --8<-- [end:flap_bit]
namespace popcnt1 {
// --8<-- [start:popcnt1]
// compute the Hamming weight of x
int popcount(int x) {
  int cnt = 0;
  while (x) {
    cnt += x & 1;
    x >>= 1;
  }
  return cnt;
}

// --8<-- [end:popcnt1]
}  // namespace popcnt1

namespace popcnt2 {
// --8<-- [start:popcnt2]
// compute the Hamming weight of x
int popcount(int x) {
  int cnt = 0;
  while (x) {
    cnt++;
    x -= x & -x;
  }
  return cnt;
}

// --8<-- [end:popcnt2]
}  // namespace popcnt2

#include <cassert>
#include <iostream>
#if defined(_MSC_VER) && !defined(__clang__)
#include <immintrin.h>
#define __builtin_popcount __popcnt
#endif

int main() {
  int a, b;
  std::cin >> a >> b;

  for (int i = 0; i < 16; i++) {
    std::cout << mulPowerOfTwo(a, i) << ' ' << divPowerOfTwo(a, i) << std::endl;
  }

  assert(Abs(-a) == a);
  assert(Abs(a) == a);

  assert(max(a, b) == (a > b ? a : b));
  assert(min(a, b) == (a < b ? a : b));

  std::cout << isSameSign(a, b) << std::endl;

  int x = a, y = b;
  swap(x, y);
  assert(x == b && y == a);

  for (int i = 0; i < 32; i++)
    std::cout << getBit(a, i) << ' ' << unsetBit(a, i) << ' ' << setBit(a, i)
              << ' ' << flapBit(a, i) << std::endl;

  assert(popcnt1::popcount(a) == __builtin_popcount(a));
  assert(popcnt2::popcount(a) == __builtin_popcount(a));

  return 0;
}
