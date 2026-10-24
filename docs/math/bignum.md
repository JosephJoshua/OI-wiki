> TL;DR: grab the template at the end...

## Definition

Arbitrary-precision arithmetic, also called bignum arithmetic, uses some algorithmic structures to support operations on larger integers (numbers bigger than the language's built-in integer types).

## Introduction

Big-integer problems involve many small details, and there is a lot to be careful about when implementing them.

So today, let us build a simple calculator together.

???+ note "Task"
    Input: an expression of the form `a <op> b`.
    
    -   `a` and `b` are non-negative decimal integers with at most $1000$ digits each;
    -   `<op>` is one character (`+`, `-`, `*` or `/`) giving the operation.
    -   The integers and the operator are separated by single spaces.
    
    Output: the result.
    
    -   For `+`, `-` and `*`, output one line with the result;
    -   For `/`, output two lines: the quotient and the remainder.
    -   All results are guaranteed to be non-negative integers.

## Storage

In typical implementations, a big number is represented as a string, where each character is one decimal digit of the number. So you could say that big-integer arithmetic is really a special kind of string processing.

When we read the string, the most significant digit is at the start of the string (the small index). By convention, however, the smallest index stores the **least significant digit**, that is, we store the string reversed. The reason is that the length of a number may change, but we want digits of the same place value to stay aligned (for example, we want every ones digit at index `[0]`, every tens digit at index `[1]`, and so on). Also, addition, subtraction and multiplication usually start from the ones digit (think of long arithmetic from elementary school). All of this gives good reasons for "reversed storage".

We will keep this convention from now on. We define a constant `LEN = 1004` as the maximum length the program can hold.

With this, it is easy to write code that reads a big number:

```cpp
void clear(int a[]) {
  for (int i = 0; i < LEN; ++i) a[i] = 0;
}

void read(int a[]) {
  static char s[LEN + 1];
  scanf("%s", s);

  clear(a);

  int len = strlen(s);
  // reverse, as described above
  for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
  // s[i] - '0' is the digit that s[i] represents
  // some readers may find it easier to think of it as ord(s[i]) - ord('0')
}
```

Output goes in the reverse order of storage. Since we do not want leading zeros, we search downward from the most significant digit for the first non-zero digit, and start printing from there. The loop condition is `i >= 1` rather than `i >= 0` because when the whole number is $0$ we still want to print one character `0`.

```cpp
void print(int a[]) {
  int i;
  for (i = LEN - 1; i >= 1; --i)
    if (a[i] != 0) break;
  for (; i >= 0; --i) putchar(a[i] + '0');
  putchar('\n');
}
```

Put these together and you get a complete echo program.

??? note "`copycat.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    int main() {
      read(a);
      print(a);
    
      return 0;
    }
    ```

## The four basic operations

The four operations differ in difficulty. The simplest are big-integer addition and subtraction, followed by big-integer times small-integer (an ordinary `int`) multiplication and big-integer times big-integer multiplication, and finally big-integer by big-integer division.

We will implement all the required features in this order.

### Addition

Big-integer addition is just long addition.

![](./images/plus.svg)

That is, starting from the lowest digit, add the digits of the two numbers at the same position, and check whether the sum reaches $10$ or more. If it does, handle the carry: add $1$ to the next higher digit and subtract $10$ from the current digit.

```cpp
void add(int a[], int b[], int c[]) {
  clear(c);

  // in big-integer code, we usually make the maximum array length LEN a bit larger than any possible input
  // and skip the last few loop iterations; this saves handling many edge cases
  // since the actual input has at most 1000 digits, looping up to LEN - 1 = 1003 here is enough
  for (int i = 0; i < LEN - 1; ++i) {
    // add the digits at this position
    c[i] += a[i] + b[i];
    if (c[i] >= 10) {
      // carry
      c[i + 1] += 1;
      c[i] -= 10;
    }
  }
}
```

Combine this with the previous part and you get an addition calculator.

??? note "`adder.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN], b[LEN], c[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    void add(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] + b[i];
        if (c[i] >= 10) {
          c[i + 1] += 1;
          c[i] -= 10;
        }
      }
    }
    
    int main() {
      read(a);
      read(b);
    
      add(a, b, c);
      print(c);
    
      return 0;
    }
    ```

### Subtraction

Big-integer subtraction is just long subtraction.

![](./images/subtraction.svg)

Subtract digit by digit starting from the ones digit, and when a digit goes negative, borrow $1$ from the next higher digit. The overall idea is exactly the same as for addition.

```cpp
void sub(int a[], int b[], int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // subtract digit by digit
    c[i] += a[i] - b[i];
    if (c[i] < 0) {
      // borrow
      c[i + 1] -= 1;
      c[i] += 10;
    }
  }
}
```

Replace `add()` in the previous program with `sub()` and you have a subtraction calculator.

??? note "`subtractor.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN], b[LEN], c[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    void sub(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] - b[i];
        if (c[i] < 0) {
          c[i + 1] -= 1;
          c[i] += 10;
        }
      }
    }
    
    int main() {
      read(a);
      read(b);
    
      sub(a, b, c);
      print(c);
    
      return 0;
    }
    ```

Try it: input `1 2` and the output is `/9999999`. Hey, why did **OI Wiki** give me broken code...

In fact, the code above only handles the case where $a$ is greater than or equal to $b$. Handling the case where $a$ is smaller, that is $a<b$, is simple.

$a-b=-(b-a)$

To compute $b-a$: since $b>a$, we can call the `sub` function from the code above as `sub(b,a,c)`. To get $a-b$, just put a minus sign in front of the result.

### Multiplication

#### Big integer times small integer

Big-integer multiplication is just long... wait, wait!

First consider a simple case: one of the factors is an ordinary `int`. Is there an easy way to handle it?

An intuitive idea is to multiply each digit of $a$ directly by $b$. Numerically this is correct, but the result is not in proper decimal form, so we need to normalize it.

We normalize by handling carries digit by digit, starting from the ones digit. But the carries here can be very large, even much larger than $9$, because after multiplication each digit can be on the order of $9b$. So we can no longer just subtract $10$; instead we use the quotient and remainder of dividing by $10$. See the code comments for details, or see the figure below, which shows how the big number $1337$ is multiplied by the small number $42$.

![](./images/multiplication-short.png)

For the same reason, this method needs special care about the range of the factor $b$. If $b$ is on the same order as $10^9$ (or the upper limit of the integer type in use), be careful with big-times-small multiplication.

```cpp
void mul_short(int a[], int b, int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // multiply digit i of a directly by the factor and add it to the result
    c[i] += a[i] * b;

    if (c[i] >= 10) {
      // handle the carry
      // c[i] / 10, the quotient, is added to the next digit as the carry
      c[i + 1] += c[i] / 10;
      // and c[i] % 10, the remainder, is the value left in the current digit
      c[i] %= 10;
    }
  }
}
```

#### Big integer times big integer

If both factors are big integers, long multiplication comes into play again.

Recall that each step of long multiplication actually computes a sum of terms $a \times b_i \times 10^i$. For example, $1337 \times 42$ is computed as $1337 \times 2 \times 10^0 + 1337 \times 4 \times 10^1$.

So we can split $b$ into its digits, each of which is a small number, multiply each by $a$, shift them left to their positions, and add them up to get the answer. Of course, we also need to handle carries at the end in the same way as the example above.

![](./images/multiplication-long.png)

Note that this process is not quite the same as long multiplication. Our algorithm does not carry during each multiplication step; it keeps all results in their positions and handles all carries together at the end. This does not affect the result.

```cpp
void mul(int a[], int b[], int c[]) {
  clear(c);

  for (int i = 0; i < LEN - 1; ++i) {
    // here we directly compute digit i of the result, from low to high, and handle the carry along the way
    // iteration i adds to c[i] the sum of products a[p] * b[q] over all p + q = i
    // this has the same effect as doing the computation in the figure above and summing at the end; it is just a shorter implementation
    for (int j = 0; j <= i; ++j) c[i] += a[j] * b[i - j];

    if (c[i] >= 10) {
      c[i + 1] += c[i] / 10;
      c[i] %= 10;
    }
  }
}
```

### Division

One way to implement big-integer division is long division.

![](./images/division.svg)

Long division can actually be seen as a process of repeated subtraction. For example, the tens digit of the quotient in the figure above can be understood like this: after subtracting $12$ from $45$ three times, it becomes smaller than $12$ and we cannot subtract any more, so this digit is $3$.

To avoid redundant work, we first find the length $l_a$ of the dividend and the length $l_b$ of the divisor, and compute the quotient from high digits to low digits starting at index $l_a - l_b$. This is the same as aligning the highest digit of the first multiplication with the highest digit of the dividend when dividing by hand.

The reference program implements a function `greater_eq()` that checks whether the dividend, taking index `last_dg` as its lowest digit, can have the divisor subtracted once more and stay non-negative. Then, for each digit of the quotient, it keeps calling `greater_eq()` and, whenever the check passes, subtracts the divisor from the remainder using big-integer subtraction. This simulates long division.

```cpp
// whether the dividend a, taking index last_dg as its lowest digit, can have the divisor b subtracted once more and stay non-negative
// len is the length of the divisor b, passed to avoid recomputing it
bool greater_eq(int a[], int b[], int last_dg, int len) {
  // the remaining part of the dividend may be longer than the divisor, but by at most 1 digit, so this check is enough
  if (a[last_dg + len] != 0) return true;
  // compare digit by digit, from high to low
  for (int i = len - 1; i >= 0; --i) {
    if (a[last_dg + i] > b[i]) return true;
    if (a[last_dg + i] < b[i]) return false;
  }
  // equality also counts as possible
  return true;
}

void div(int a[], int b[], int c[], int d[]) {
  clear(c);
  clear(d);

  int la, lb;
  for (la = LEN - 1; la > 0; --la)
    if (a[la - 1] != 0) break;
  for (lb = LEN - 1; lb > 0; --lb)
    if (b[lb - 1] != 0) break;
  if (lb == 0) {  // the divisor cannot be zero
    puts("> <");
    return;
  }

  // c is the quotient
  // d is the remaining part of the dividend; when the algorithm ends it is the remainder
  for (int i = 0; i < la; ++i) d[i] = a[i];
  for (int i = la - lb; i >= 0; --i) {
    // compute digit i of the quotient
    while (greater_eq(d, b, i, lb)) {
      // if we can subtract, subtract
      // this part is a big-integer subtraction
      for (int j = 0; j < lb; ++j) {
        d[i + j] -= b[j];
        if (d[i + j] < 0) {
          d[i + j + 1] -= 1;
          d[i + j] += 10;
        }
      }
      // increase this digit of the quotient by 1
      c[i] += 1;
      // go back to the start of the loop and check again
    }
  }
}
```

## Basics complete!

Combine the implementations of the four operations above, and you get the calculator program from the beginning.

??? note "`calculator.cpp`"
    ```cpp
    #include <cstdio>
    #include <cstring>
    
    constexpr int LEN = 1004;
    
    int a[LEN], b[LEN], c[LEN], d[LEN];
    
    void clear(int a[]) {
      for (int i = 0; i < LEN; ++i) a[i] = 0;
    }
    
    void read(int a[]) {
      static char s[LEN + 1];
      scanf("%s", s);
    
      clear(a);
    
      int len = strlen(s);
      for (int i = 0; i < len; ++i) a[len - i - 1] = s[i] - '0';
    }
    
    void print(int a[]) {
      int i;
      for (i = LEN - 1; i >= 1; --i)
        if (a[i] != 0) break;
      for (; i >= 0; --i) putchar(a[i] + '0');
      putchar('\n');
    }
    
    void add(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] + b[i];
        if (c[i] >= 10) {
          c[i + 1] += 1;
          c[i] -= 10;
        }
      }
    }
    
    void sub(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] - b[i];
        if (c[i] < 0) {
          c[i + 1] -= 1;
          c[i] += 10;
        }
      }
    }
    
    void mul(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        for (int j = 0; j <= i; ++j) c[i] += a[j] * b[i - j];
    
        if (c[i] >= 10) {
          c[i + 1] += c[i] / 10;
          c[i] %= 10;
        }
      }
    }
    
    bool greater_eq(int a[], int b[], int last_dg, int len) {
      if (a[last_dg + len] != 0) return true;
      for (int i = len - 1; i >= 0; --i) {
        if (a[last_dg + i] > b[i]) return true;
        if (a[last_dg + i] < b[i]) return false;
      }
      return true;
    }
    
    void div(int a[], int b[], int c[], int d[]) {
      clear(c);
      clear(d);
    
      int la, lb;
      for (la = LEN - 1; la > 0; --la)
        if (a[la - 1] != 0) break;
      for (lb = LEN - 1; lb > 0; --lb)
        if (b[lb - 1] != 0) break;
      if (lb == 0) {
        puts("> <");
        return;
      }
    
      for (int i = 0; i < la; ++i) d[i] = a[i];
      for (int i = la - lb; i >= 0; --i) {
        while (greater_eq(d, b, i, lb)) {
          for (int j = 0; j < lb; ++j) {
            d[i + j] -= b[j];
            if (d[i + j] < 0) {
              d[i + j + 1] -= 1;
              d[i + j] += 10;
            }
          }
          c[i] += 1;
        }
      }
    }
    
    int main() {
      read(a);
    
      char op[4];
      scanf("%s", op);
    
      read(b);
    
      switch (op[0]) {
        case '+':
          add(a, b, c);
          print(c);
          break;
        case '-':
          sub(a, b, c);
          print(c);
          break;
        case '*':
          mul(a, b, c);
          print(c);
          break;
        case '/':
          div(a, b, c, d);
          print(c);
          print(d);
          break;
        default:
          puts("> <");
      }
    
      return 0;
    }
    ```

## Big integers with digit packing

### Introduction

In ordinary big-integer addition, subtraction and multiplication, we split the numbers into individual digits and compute with them.

For example, when computing $8192\times 42$ with big-times-big multiplication, we actually compute $(8000+100+90+2)\times(40+2)$.

When there are many digits, the numbers are split into many pieces, and big-integer arithmetic becomes slower.

Is there a way to optimize this?

Note that the way we split the number does not affect the final result, so we can merge several digits together.

### How it works

Using the same example, if we split the number every two digits, we get $(8100+92)\times 42$.

This split does not change the final result, but because there are fewer pieces, the computation is faster.

From the point of view of [number bases](./numeral-sys/base.md), we compute in a larger base (splitting every two digits as above can be seen as computing in base $100$), which reduces the number of digits involved and makes the computation faster.

This is the idea of **digit packing** for big integers.

Below is the code for addition with digit packing, to further illustrate how it is implemented:

??? note "Reference implementation of addition with digit packing"
    ```cpp
    // the arrays a, b, c here all hold numbers in base p
    // when printing the final answer, convert the number to decimal
    void add(int a[], int b[], int c[]) {
      clear(c);
    
      for (int i = 0; i < LEN - 1; ++i) {
        c[i] += a[i] + b[i];
        if (c[i] >= p) {  // in ordinary big-integer arithmetic, p=10
          c[i + 1] += 1;
          c[i] -= p;
        }
      }
    }
    ```

### Efficient long division with digit packing

When using digit packing, if we still estimate each quotient digit with the method above, there will be many trial subtractions and the constant factor will be huge. For example, in base 10000, each digit needs 5000 trial subtractions on average, which is an unacceptably large constant. So we need a more efficient way to estimate quotient digits.

We can use double as a helper. Suppose the dividend has 4 digits $a_4,a_3,a_2,a_1$ and the divisor has 3 digits $b_3,b_2,b_1$. Then we only need to estimate one quotient digit: in base $base$, estimate it with $\dfrac{a_4 base + a_3}{b_3 + b_2 base^{-1} + (b_1+1)base^{-2}}$. For more digits, just wrap the one-digit version in a loop. Since the divisor takes part in the estimate with 3 digits of precision, the estimated quotient q' and the actual quotient q are guaranteed to satisfy $q-1 \le q' \le q$, so in the worst case each digit needs only two trials. At the same time, $base^3$ must fit in the precision of double, that is $base^3 < 2^{53}$. So when using this method, it is best not to use a base above 32768; otherwise the lack of precision can easily cause errors and wrong results.

Also, since the estimated quotient is always at most the actual quotient, there is room for further optimization. In the vast majority of cases each digit is estimated only once. Then, when estimating the next digit, the result may be at least base because of the error in the previous digit, but that does not matter; we just handle all carries together at the end. For example, with base 10, to compute $395081/9876$ the estimation steps are:

1.  First, the estimate gives $3950/988=3$, so $395081-(9876 \times 3 \times 10^1) = 98801$. There is an error in this step, but we ignore it and move on.
2.  Estimating again on the remainder 98801 gives $9880/988=10$, so $98801-(9876 \times 10 \times 10^0) = 41$, which is the final remainder.
3.  Add up the results of the estimates and handle the carries: $3 \times 10^1 + 10 \times 10^0 = 40$ is the exact quotient.

The method looks simple, but it is easy to get the implementation wrong. So below is an implementation that has been checked many times and is known to be correct, for your reference. The details to watch out for are written in the comments.

??? note "Reference implementation of efficient long division with digit packing"
    ```cpp
    // full template and implementation: https://baobaobear.github.io/post/20210228-bigint1/
    // subtract b times mul, shifted left by offset; used for division
    BigIntSimple &sub_mul(const BigIntSimple &b, int mul, int offset) {
      if (mul == 0) return *this;
      int borrow = 0;
      // unlike plain subtraction, borrow can be large, so we cannot write it the same way as subtraction
      for (size_t i = 0; i < b.v.size(); ++i) {
        borrow += v[i + offset] - b.v[i] * mul - BIGINT_BASE + 1;
        v[i + offset] = borrow % BIGINT_BASE + BIGINT_BASE - 1;
        borrow /= BIGINT_BASE;
      }
      // if there is still a borrow, keep handling it
      for (size_t i = b.v.size(); borrow; ++i) {
        borrow += v[i + offset] - BIGINT_BASE + 1;
        v[i + offset] = borrow % BIGINT_BASE + BIGINT_BASE - 1;
        borrow /= BIGINT_BASE;
      }
      return *this;
    }
    
    BigIntSimple div_mod(const BigIntSimple &b, BigIntSimple &r) const {
      BigIntSimple d;
      r = *this;
      if (absless(b)) return d;
      d.v.resize(v.size() - b.v.size() + 1);
      // precompute the reciprocal of the top three digits of the divisor plus 1: if the top three digits are a3,a2,a1
      // then db is the reciprocal of a3+a2/base+(a1+1)/base^2, and finally each quotient digit is estimated by multiplication
      // this works within int32 range when BIGINT_BASE<=32768
      // but even with int64, it only works when BIGINT_BASE<=131072 (limited by the precision of double)
      // it guarantees that the estimate q' and the actual result q satisfy q'<=q<=q'+1
      // so each quotient digit needs only one trial on average, as long as carries are handled together afterward
      // to use a larger base, you need a different way to estimate quotient digits
      double t = (b.get((unsigned)b.v.size() - 2) +
                  (b.get((unsigned)b.v.size() - 3) + 1.0) / BIGINT_BASE);
      double db = 1.0 / (b.v.back() + t / BIGINT_BASE);
      for (size_t i = v.size() - 1, j = d.v.size() - 1; j <= v.size();) {
        int rm = r.get(i + 1) * BIGINT_BASE + r.get(i);
        int m = std::max((int)(db * rm), r.get(i + 1));
        r.sub_mul(b, m, j);
        d.v[j] += m;
        if (!r.get(i + 1))  // check whether the highest digit is already 0, to avoid extreme cases
          --i, --j;
      }
      r.trim();
      // fix the ones digit of the result
      int carry = 0;
      while (!r.absless(b)) {
        r.subtract(b);
        ++carry;
      }
      // fix the carry of every digit
      for (size_t i = 0; i < d.v.size(); ++i) {
        carry += d.v[i];
        d.v[i] = carry % BIGINT_BASE;
        carry /= BIGINT_BASE;
      }
      d.trim();
      d.sign = sign * b.sign;
      return d;
    }
    
    BigIntSimple operator/(const BigIntSimple &b) const {
      BigIntSimple r;
      return div_mod(b, r);
    }
    
    BigIntSimple operator%(const BigIntSimple &b) const {
      BigIntSimple r;
      div_mod(b, r);
      return r;
    }
    ```

## Karatsuba multiplication

Let $n$ be the number of digits of the big numbers. Then big-times-big long multiplication takes $O(n^2)$ time. This section introduces an algorithm with better time complexity. It was proposed by the Soviet (Russian) mathematician Anatoly Karatsuba and is a divide-and-conquer algorithm.

Consider two large decimal integers $x$ and $y$, each with $n$ digits (leading zeros allowed). Pick any $0 < m < n$ and write

$$
\begin{aligned}
x &= x_1 \cdot 10^m + x_0, \\
y &= y_1 \cdot 10^m + y_0, \\
x \cdot y &= z_2 \cdot 10^{2m} + z_1 \cdot 10^m + z_0,
\end{aligned}
$$

where $x_0, y_0, z_0, z_1 < 10^m$. Then

$$
\begin{aligned}
z_2 &= x_1 \cdot y_1, \\
z_1 &= x_1 \cdot y_0 + x_0 \cdot y_1, \\
z_0 &= x_0 \cdot y_0.
\end{aligned}
$$

Observe that

$$
z_1 = (x_1 + x_0) \cdot (y_1 + y_0) - z_2 - z_0,
$$

So to compute $z_1$, we only need to compute $(x_1 + x_0) \cdot (y_1 + y_0)$ and subtract $z_0$ and $z_2$.

This formula is the core of the Karatsuba algorithm: it turns a multiplication problem of length $n$ into $3$ subproblems of smaller length. If we take $m = \left\lceil \dfrac n 2 \right\rceil$ and let $T(n)$ be the time Karatsuba's algorithm takes to multiply two $n$-digit integers, then $T(n) = 3 \cdot T \left(\left\lceil \dfrac n 2 \right\rceil\right) + O(n)$, and by the master theorem $T(n) = \Theta(n^{\log_2 3}) \approx \Theta(n^{1.585})$.

The whole process can be implemented recursively. For clarity, the code below uses the Karatsuba algorithm to multiply polynomials, and handles all the carries at the end.

??? note "karatsuba_mulc.cpp"
    ```cpp
    int *karatsuba_polymul(int n, int *a, int *b) {
      if (n <= 32) {
        // when the size is small, compute directly to avoid the overhead of further recursion
        int *r = new int[n * 2 + 1]();
        for (int i = 0; i <= n; ++i)
          for (int j = 0; j <= n; ++j) r[i + j] += a[i] * b[j];
        return r;
      }
    
      int m = n / 2 + 1;
      int *r = new int[m * 4 + 1]();
      int *z0, *z1, *z2;
    
      z0 = karatsuba_polymul(m - 1, a, b);
      z2 = karatsuba_polymul(n - m, a + m, b + m);
    
      // compute z1
      // temporary change, restored after the computation
      for (int i = 0; i + m <= n; ++i) a[i] += a[i + m];
      for (int i = 0; i + m <= n; ++i) b[i] += b[i + m];
      z1 = karatsuba_polymul(m - 1, a, b);
      for (int i = 0; i + m <= n; ++i) a[i] -= a[i + m];
      for (int i = 0; i + m <= n; ++i) b[i] -= b[i + m];
      for (int i = 0; i <= (m - 1) * 2; ++i) z1[i] -= z0[i];
      for (int i = 0; i <= (n - m) * 2; ++i) z1[i] -= z2[i];
    
      // combine z0, z1, z2 to get the result
      for (int i = 0; i <= (m - 1) * 2; ++i) r[i] += z0[i];
      for (int i = 0; i <= (m - 1) * 2; ++i) r[i + m] += z1[i];
      for (int i = 0; i <= (n - m) * 2; ++i) r[i + m * 2] += z2[i];
    
      delete[] z0;
      delete[] z1;
      delete[] z2;
      return r;
    }
    
    void karatsuba_mul(int a[], int b[], int c[]) {
      int *r = karatsuba_polymul(LEN - 1, a, b);
      memcpy(c, r, sizeof(int) * LEN);
      for (int i = 0; i < LEN - 1; ++i)
        if (c[i] >= 10) {
          c[i + 1] += c[i] / 10;
          c[i] %= 10;
        }
      delete[] r;
    }
    ```

??? note "About `new` and `delete`"
    See [memory pool](../contest/common-tricks.md#内存池).

However, this implementation has a problem: in base $b$, each coefficient of the polynomial can reach the order of $n \cdot b^2$, which may cause integer overflow in an implementation with digit packing. If instead we handle carries during the polynomial multiplication, $x_1 + x_0$ and $y_1 + y_0$ can reach $2 \cdot b^m$, adding one more digit (and if we compute $x_1 - x_0$ instead, we have to handle negative numbers specially). So you need to choose the implementation based on the actual use case.

## Efficient big-integer multiplication with polynomials

If the numbers reach $10^{10^5}$ or larger, ordinary big-integer multiplication may exceed the time limit. This section introduces how to speed up such multiplication with polynomials.

An $n$-digit decimal integer $a$ can be viewed as a polynomial $A=a_{0} 10^0+a_{1} 10^1+\cdots+a_{n-1} 10^{n-1}$ whose coefficients are all integers less than $10$. This turns the multiplication of two integers into the multiplication of two polynomials.

Ordinary polynomial multiplication still takes $O(n^2)$ time, but it can be sped up with algorithms from the polynomial section such as the [fast Fourier transform](poly/fft.md) and the [number theoretic transform](poly/ntt.md), bringing the time complexity down to $O(n\log n)$.

## Wrapper classes

[Here](https://paste.ubuntu.com/p/7VKYzpC7dn/) is a ready-made big integer class, and [here](https://github.com/Baobaobear/MiniBigInteger/blob/main/bigint_tiny.h) is a very small implementation that supports dynamic length and the four basic operations.

??? note "Here is another template"
    ```cpp
    constexpr int MAXN = 9999;
    // MAXN is the largest number stored in one digit
    constexpr int MAXSIZE = 10024;
    // MAXSIZE is the number of digits
    constexpr int DLEN = 4;
    
    // DLEN is how many decimal digits are packed into one
    struct Big {
      int a[MAXSIZE], len;
      bool flag;  // marks the sign '-'
    
      Big() {
        len = 1;
        memset(a, 0, sizeof a);
        flag = false;
      }
    
      Big(const int);
      Big(const char*);
      Big(const Big&);
      Big& operator=(const Big&);
      Big operator+(const Big&) const;
      Big operator-(const Big&) const;
      Big operator*(const Big&) const;
      Big operator/(const int&) const;
      // TODO: Big / Big;
      Big operator^(const int&) const;
      // TODO: Big ^ Big;
    
      // TODO: bitwise operations for Big;
    
      int operator%(const int&) const;
      // TODO: Big ^ Big;
      bool operator<(const Big&) const;
      bool operator<(const int& t) const;
      void print() const;
    };
    
    Big::Big(const int b) {
      int c, d = b;
      len = 0;
      // memset(a,0,sizeof a);
      CLR(a);
      while (d > MAXN) {
        c = d - (d / (MAXN + 1) * (MAXN + 1));
        d = d / (MAXN + 1);
        a[len++] = c;
      }
      a[len++] = d;
    }
    
    Big::Big(const char* s) {
      int t, k, index, l;
      CLR(a);
      l = strlen(s);
      len = l / DLEN;
      if (l % DLEN) ++len;
      index = 0;
      for (int i = l - 1; i >= 0; i -= DLEN) {
        t = 0;
        k = i - DLEN + 1;
        if (k < 0) k = 0;
        g(j, k, i) t = t * 10 + s[j] - '0';
        a[index++] = t;
      }
    }
    
    Big::Big(const Big& T) : len(T.len) {
      CLR(a);
      f(i, 0, len) a[i] = T.a[i];
      // TODO: overload this?
    }
    
    Big& Big::operator=(const Big& T) {
      CLR(a);
      len = T.len;
      f(i, 0, len) a[i] = T.a[i];
      return *this;
    }
    
    Big Big::operator+(const Big& T) const {
      Big t(*this);
      int big = len;
      if (T.len > len) big = T.len;
      f(i, 0, big) {
        t.a[i] += T.a[i];
        if (t.a[i] > MAXN) {
          ++t.a[i + 1];
          t.a[i] -= MAXN + 1;
        }
      }
      if (t.a[big])
        t.len = big + 1;
      else
        t.len = big;
      return t;
    }
    
    Big Big::operator-(const Big& T) const {
      int big;
      bool ctf;
      Big t1, t2;
      if (*this < T) {
        t1 = T;
        t2 = *this;
        ctf = true;
      } else {
        t1 = *this;
        t2 = T;
        ctf = false;
      }
      big = t1.len;
      int j = 0;
      f(i, 0, big) {
        if (t1.a[i] < t2.a[i]) {
          j = i + 1;
          while (t1.a[j] == 0) ++j;
          --t1.a[j--];
          // WTF?
          while (j > i) t1.a[j--] += MAXN;
          t1.a[i] += MAXN + 1 - t2.a[i];
        } else
          t1.a[i] -= t2.a[i];
      }
      t1.len = big;
      while (t1.len > 1 && t1.a[t1.len - 1] == 0) {
        --t1.len;
        --big;
      }
      if (ctf) t1.a[big - 1] = -t1.a[big - 1];
      return t1;
    }
    
    Big Big::operator*(const Big& T) const {
      Big res;
      int up;
      int te, tee;
      f(i, 0, len) {
        up = 0;
        f(j, 0, T.len) {
          te = a[i] * T.a[j] + res.a[i + j] + up;
          if (te > MAXN) {
            tee = te - te / (MAXN + 1) * (MAXN + 1);
            up = te / (MAXN + 1);
            res.a[i + j] = tee;
          } else {
            up = 0;
            res.a[i + j] = te;
          }
        }
        if (up) res.a[i + T.len] = up;
      }
      res.len = len + T.len;
      while (res.len > 1 && res.a[res.len - 1] == 0) --res.len;
      return res;
    }
    
    Big Big::operator/(const int& b) const {
      Big res;
      int down = 0;
      gd(i, len - 1, 0) {
        res.a[i] = (a[i] + down * (MAXN + 1)) / b;
        down = a[i] + down * (MAXN + 1) - res.a[i] * b;
      }
      res.len = len;
      while (res.len > 1 && res.a[res.len - 1] == 0) --res.len;
      return res;
    }
    
    int Big::operator%(const int& b) const {
      int d = 0;
      gd(i, len - 1, 0) d = (d * (MAXN + 1) % b + a[i]) % b;
      return d;
    }
    
    Big Big::operator^(const int& n) const {
      Big t(*this), res(1);
      int y = n;
      while (y) {
        if (y & 1) res = res * t;
        t = t * t;
        y >>= 1;
      }
      return res;
    }
    
    bool Big::operator<(const Big& T) const {
      int ln;
      if (len < T.len) return true;
      if (len == T.len) {
        ln = len - 1;
        while (ln >= 0 && a[ln] == T.a[ln]) --ln;
        if (ln >= 0 && a[ln] < T.a[ln]) return true;
        return false;
      }
      return false;
    }
    
    bool Big::operator<(const int& t) const {
      Big tee(t);
      return *this < tee;
    }
    
    void Big::print() const {
      printf("%d", a[len - 1]);
      gd(i, len - 2, 0) { printf("%04d", a[i]); }
    }
    
    void print(const Big& s) {
      int len = s.len;
      printf("%d", s.a[len - 1]);
      gd(i, len - 2, 0) { printf("%04d", s.a[i]); }
    }
    
    char s[100024];
    ```

## Exercises

-   [NOIP 2012 King's Game](https://loj.ac/problem/2603)
-   [SPOJ - Fast Multiplication](http://www.spoj.com/problems/MUL/en/)
-   [SPOJ - GCD2](http://www.spoj.com/problems/GCD2/)
-   [UVa - Division](https://uva.onlinejudge.org/index.php?option=onlinejudge&page=show_problem&problem=1024)
-   [UVa - Fibonacci Freeze](https://uva.onlinejudge.org/index.php?option=com_onlinejudge&Itemid=8&page=show_problem&problem=436)
-   [Codeforces - Notepad](http://codeforces.com/contest/17/problem/D)

## References and links

1.  [Karatsuba algorithm - Wikipedia](https://en.wikipedia.org/wiki/Karatsuba_algorithm)
