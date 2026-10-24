author: aofall, greyqz, Ir1d, Link-cute, Marcythm, ouuan, Shen-Linwood, sshwy, StudyingFather

## Arithmetic operators

| Operator       | Meaning        |
| -------------- | -------------- |
|  `+` (unary)   | Unary plus     |
|  `-` (unary)   | Negation       |
|  `*` (binary)  | Multiplication |
|  `/`           | Division       |
|  `%`           | Modulo         |
|  `+` (binary)  | Addition       |
|  `-` (binary)  | Subtraction    |

??? note "Unary and binary operators"
    A unary operator acts on a single operand, while a binary operator acts on two. For example, the plus sign in `1 + 2` is a binary operator with the two operands `1` and `2`. C++ also has exactly one ternary operator, `?:`.

Among the arithmetic operators there are two unary operators (plus and negation) and five binary operators (multiplication, division, modulo, addition and subtraction). The unary operators have the highest precedence.

The modulo operator `%` gives the remainder when one integer is divided by another.

When `-` is a binary operator it means subtraction, as in `2-1`; when it is a unary operator it means negation, as in `-1`.

It is used like this:

 `op=x-y*z` 

The value of `op` follows the usual order of operations from math: higher-precedence operations come first, operations with the same precedence are done according to their associativity, and parentheses raise precedence.

### Type conversion in arithmetic

For binary arithmetic operators, if the two operands have the same type, no [type conversion](./var.md#type-conversion) happens, and the result has the same type as the operands. Otherwise a type conversion happens so that both operands have the same type. For the conversion rules, see [type conversion](./var.md#type-conversion).

For example, for an integer (`int`) variable $x$ and a double-precision floating-point (`double`) variable $y$:

-  `x/3` gives an integer;
-  `x/3.0` gives a double;
-  `x/y` gives a double;
-  `x*1/3` gives an integer;
-  `x*1.0/3` gives a double;

## Bitwise operators

See also: [Bitwise operations](../math/bit.md#bitwise-operations).

| Operator       | Meaning      |
| -------------- | ------------ |
|  `~`           | Bitwise NOT  |
|  `&` (binary)  | Bitwise AND  |
|  `|`           | Bitwise OR   |
|  `^`           | Bitwise XOR  |
|  `<<`          | Left shift   |
|  `>>`          | Right shift  |

For what the bitwise operations mean, see the [bitwise operations](../math/bit.md) page. Note that bitwise operators have lower precedence than arithmetic operators (except NOT), and bitwise AND, OR and XOR are even lower than the comparison operators (see the [C++ operator precedence table](#c-operator-precedence-table)). So be careful when using them, and add parentheses where needed.

A shift has undefined behavior in the following cases:

1.  The right operand (the shift amount) is negative;
2.  The right operand is greater than or equal to the number of bits in the left operand;

For example, for a variable `a` of type `int32_t`, both `a<<-1` and `a<<32` are undefined.

When left-shifting a signed non-negative number, you must make sure the result fits in the original type; otherwise the behavior is also undefined.[^note1] Left-shifting a negative number is undefined too.[^note2]

For a right shift, the extra bits on the right are dropped. The left side is more complicated: for unsigned numbers, $0$ is filled in on the left[^note3]; for signed numbers, the highest bit (which is the sign bit: $0$ for non-negative, $1$ for negative) is filled in[^note4].

## Increment/decrement operators

Sometimes we need to increase a variable by 1 (increment) or decrease it by 1 (decrement). This is where the increment operator `++` and the decrement operator `--` come in.

The increment/decrement operators can go before or after a variable. Before the variable it is called prefix, and after it is called postfix. When used on their own, there is no difference between prefix and postfix. But if you use the value of the expression, you need to be careful; see the example below. For more details, see the examples in [references](./reference.md).

```cpp
i = 100;

op1 = i++;  // op1 = 100; first op1 = i, then i = i + 1

i = 100;

op2 = ++i;  // op2 = 101; first i = i + 1, then assign to op2

i = 100;

op3 = i--;  // op3 = 100; first assign to op3, then i = i - 1

i = 100;

op4 = --i;  // op4 = 99; first i = i - 1, then assign to op4
```

## Compound assignment operators

Compound assignment operators are really shorthand for longer expressions. They are the compound arithmetic operators `+=`, `-=`, `*=`, `/=`, `%=` and the compound bitwise operators `&=`, `|=`, `^=`, `<<=`, `>>=`.

For example, `op = op + 2` can be written as `op += 2`, `op = op - 2` as `op -= 2`, and `op= op * 2` as `op *= 2`.

## The conditional operator

The conditional operator can be seen as shorthand for an `if` statement. In `a ? b : c`, if the expression `a` is true, the result of the conditional expression is `b`; otherwise it is `c`.
## Comparison operators

| Operator | Meaning                  |
| -------- | ------------------------ |
|  `>`     | Greater than             |
|  `>=`    | Greater than or equal to |
|  `<`     | Less than                |
|  `<=`    | Less than or equal to    |
|  `==`    | Equal to                 |
|  `!=`    | Not equal to             |

Pay special attention to the difference between the equality operator `==` and the assignment operator `=`. This matters most in conditions.

 `if (op=1)` and `if (op==1)` look similar, but they do very different things. The first assigns to op; since the assigned value is non-zero, which counts as true, the condition is always satisfied and does not test anything. Only the second one actually tests the value of `op`.

## Logical operators

| Operator | Meaning     |
| -------- | ----------- |
|  `&&`    | Logical AND |
|  `||`    | Logical OR  |
|  `!`     | Logical NOT |

```cpp
Result = op1 && op2;  // Result is true when both op1 and op2 are true

Result = op1 || op2;  // Result is true when at least one of op1 and op2 is true

Result = !op1;  // Result is true when op1 is false
```

The **built-in** operators `&&` and `||` use short-circuit evaluation (if the result is already known after evaluating the first operand, the second is not evaluated). Overloaded versions don't have this property and always evaluate both operands.

## The comma operator

The comma operator separates several expressions. The separated expressions are evaluated one by one from left to right, and the value of the whole expression is the value of the last one. The comma operator has the **lowest** precedence of all operators.

```cpp
exp1, exp2, exp3;  // the final value is the result of exp3.

Result = 1 + 2, 3 + 4, 5 + 6;
// Result gets the value 3, not 11, because the assignment operator "="
// has higher precedence than the comma operator, so the assignment happens before the comma operation.

Result = (1 + 2, 3 + 4, 5 + 6);

// To make Result get the result of the comma operation, wrap the whole expression in parentheses to raise its precedence; then
// Result gets the value 11.
```

## Member access operators

| Operator       | Meaning                            |
| -------------- | ---------------------------------- |
|  `[]`          | Array subscript                    |
|  `.`           | Object member                      |
|  `&` (unary)   | Address-of / get a reference       |
|  `*` (unary)   | Indirection / dereference          |
|  `->`          | Member through a pointer           |

These operators access an object's members or memory. All of them except the last can be overloaded. For more on `&`, `*` and `->`, read the [pointers](./pointer.md) and [references](./reference.md) tutorials. Two rarely used operators, `.*` and `->*`, are left out here; for how to use them, see the [C++ language reference](https://zh.cppreference.com/w/cpp/language/operator_member_access).

```cpp
auto result1 = v[1];  // get the object at index 2 in v
auto result2 = p.q;   // get member q of object p
auto result3 = p -> q;  // get member q of the object that pointer p points to; same as (*p).q
auto result4 = &v;      // get a pointer to v
auto result5 = *v;      // get the object that pointer v points to
```

## C++ operator precedence table

Adapted from [C++ operator precedence - cppreference](https://zh.cppreference.com/w/cpp/language/operator_precedence).

| Operator | Description | Example | Overloadable? |
| :------------------: | :------: | :----------------------------------------------------------: | :--: |
|       **Level 1**       |          |                                                              |      |
|         `::`         |  Scope resolution  |                       `Class::age = 2;`                      | No |
|       **Level 2**       |          |                                                              |      |
|         `++`         |  Postfix increment  |           `for (int i = 0; i < 10; i++) cout << i;`          |  Yes |
|         `--`         |  Postfix decrement  |           `for (int i = 10; i > 0; i--) cout << i;`          |  Yes |
|   `type()  type{}`   |  Functional cast  |           `unsigned int a = unsigned(3.14);`                | Yes |
|         `()`         |   Function call   |                        `isdigit('1')`                        |  Yes |
|         `[]`         |  Array subscript  |                        `array[4] = 2;`                       |  Yes |
|          `.`         |  Member access on an object |                        `obj.age = 34;`                       | No |
|         `->`         |  Member access through a pointer |                       `ptr->age = 34;`                       |  Yes |
|   **Level 3** (right-to-left)  |          |                                                              |      |
|         `++`         |  Prefix increment  |             `for (i = 0; i < 10; ++i) cout << i;`            |  Yes |
|         `--`         |  Prefix decrement  |             `for (i = 10; i > 0; --i) cout << i;`            |  Yes |
|          `+`         |    Unary plus    |                         `int i = +1;`                        |  Yes |
|          `-`         |    Negation    |                         `int i = -1;`                        |  Yes |
|          `!`         |   Logical NOT   |                        `if (!done) …`                       |  Yes |
|          `~`         |   Bitwise NOT   |                       `flags = ~flags;`                      |  Yes |
|       `(type)`       |  C-style cast  |                 `int i = (int) floatNum;`             |  Yes |
|          `*`         |   Dereference   |                     `int data = *intPtr;`                    |  Yes |
|          `&`         |   Address-of   |                    `int *intPtr = &data;`                    |  Yes |
|       `sizeof`       |  Size in memory  |    `int size = sizeof floatNum; int size = sizeof(float);`   | No |
|         `new`        | Dynamic allocation of an object |  `long *pVar = new long; MyClass *ptr = new MyClass(args);`  |  Yes |
|       `new []`       | Dynamic allocation of an array |                 `long *array = new long[n];`                 |  Yes |
|       `delete`       | Dynamic deallocation of an object |                        `delete pVar;`                        |  Yes |
|      `delete []`     | Dynamic deallocation of an array |                      `delete [] array;`                      |  Yes |
|       **Level 4**    |          |                                                              |      |
|         `.*`         |  Pointer-to-member access on an object |                       `obj.*var = 24;`                       | No |
|         `->*`        |  Pointer-to-member access through a pointer |                       `ptr->*var = 24;`                      |  Yes |
|       **Level 5**    |          |                                                              |      |
|          `*`         |    Multiplication    |                       `int i = 2 * 4;`                       |  Yes |
|          `/`         |    Division    |                    `float f = 10.0 / 3.0;`                   |  Yes |
|          `%`         | Remainder (modulo) |                      `int rem = 4 % 3;`                      |  Yes |
|       **Level 6**    |          |                                                              |      |
|          `+`         |    Addition    |                       `int i = 2 + 3;`                       |  Yes |
|          `-`         |    Subtraction    |                       `int i = 5 - 1;`                       |  Yes |
|       **Level 7**    |          |                                                              |      |
|         `<<`         |    Left shift   |                    `int flags = 33 << 1;`                    |  Yes |
|         `>>`         |    Right shift   |                    `int flags = 33 >> 1;`                    |  Yes |
|       **Level 8**     |          |                                                              |      |
|         `<=>`         | Three-way comparison  |                `if ((i <=> 42) < 0) ...`                      |  Yes |
|       **Level 9**     |          |                                                              |      |
|          `<`         |    Less than    |                      `if (i < 42) ...`                      |  Yes |
|         `<=`         |   Less than or equal to   |                      `if (i <= 42) ...`                     |  Yes |
|          `>`         |    Greater than    |                      `if (i > 42) ...`                      |  Yes |
|         `>=`         |   Greater than or equal to   |                      `if (i >= 42) ...`                     |  Yes |
|       **Level 10**       |          |                                                              |      |
|         `==`         |    Equal to    |                      `if (i == 42) ...`                     |  Yes |
|         `!=`         |    Not equal to   |                      `if (i != 42) ...`                     |  Yes |
|       **Level 11**      |          |                                                              |      |
|          `&`         |   Bitwise AND   |                     `flags = flags & 42;`                    |  Yes |
|       **Level 12**      |          |                                                              |      |
|          `^`         |   Bitwise XOR  |                     `flags = flags ^ 42;`                    |  Yes |
|       **Level 13**      |          |                                                              |      |
|          `|`         |   Bitwise OR   |                     `flags = flags | 42;`                    |  Yes |
|       **Level 14**      |          |                                                              |      |
|         `&&`         |   Logical AND  |              `if (conditionA && conditionB) ...`             |  Yes |
|   **Level 15**         |          |                                                              |      |
|         `||`         |   Logical OR  |              `if (conditionA || conditionB) ...`             |  Yes |
|   **Level 16** (right-to-left) |          |                                                              |      |
|         `? :`        |   Conditional operator  |                   `int i = a > b ? a : b;`                   | No |
|        `throw`       |   Throw an exception   |                  `throw EClass("Message");`                  | No |
|          `=`         |    Assignment    |                         `int a = b;`                         |  Yes |
|         `+=`         |   Add and assign  |                           `a += 3;`                          |  Yes |
|         `-=`         |   Subtract and assign  |                           `b -= 4;`                          |  Yes |
|         `*=`         |   Multiply and assign  |                           `a *= 5;`                          |  Yes |
|         `/=`         |   Divide and assign  |                           `a /= 2;`                          |  Yes |
|         `%=`         |   Modulo and assign  |                           `a %= 3;`                          |  Yes |
|         `<<=`        |  Left shift and assign |                        `flags <<= 2;`                        |  Yes |
|         `>>=`        |  Right shift and assign |                        `flags >>= 2;`                        |  Yes |
|         `&=`         |  Bitwise AND and assign  |                     `flags &= new_flags;`                    |  Yes |
|         `^=`         |  Bitwise XOR and assign |                     `flags ^= new_flags;`                    |  Yes |
|         `|=`         |  Bitwise OR and assign  |                     `flags |= new_flags;`                    |  Yes |
|       **Level 17**      |          |                                                              |      |
|          `,`         |   Comma  |          `for (i = 0, j = 0; i < 10; i++, j++) ...`          |  Yes |

Note that the table does not list operators such as `const_cast`, `static_cast`, `dynamic_cast`, `reinterpret_cast`, `typeid`, `sizeof...`, `noexcept` and `alignof`, because they are used just like function calls, so there is no ambiguity.

## References and notes

[^note1]: Before C++20: if the original value has a signed type and the shifted result fits in the unsigned version of that type, the result is [converted](../lang/var.md#type-conversion) to the corresponding signed value; otherwise the behavior is undefined. For unsigned numbers, a left shift drops the bits shifted out of the result type. Since C++20, `a << b` is defined as $a\cdot 2^b$ modulo $2^N$ (where $N$ is the bit width of the result type). That is, for both signed and unsigned numbers, a left shift simply drops the bits shifted out of the result type (i.e. an [arithmetic/logical left shift](../math/bit.md#shifts)).

[^note2]: Before C++20. For the behavior since C++20, see[^note1].

[^note3]: That is, a [logical right shift](../math/bit.md#shifts).

[^note4]: That is, an [arithmetic right shift](../math/bit.md#shifts). Before C++20, signed right shift was implementation-defined, and most implementations used an arithmetic right shift. Since C++20, `a >> b` is defined as $\lfloor a/2^b\rfloor$, so right-shifting a signed number is an arithmetic right shift.
