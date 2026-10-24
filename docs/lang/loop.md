Sometimes we need to do the same thing many times. To avoid writing lots of repeated code, we use loops.

Sometimes the number of repetitions is not a constant, so we cannot just copy the code several times. In that case we must use a loop.

## The for statement

Here is the structure of a for statement:

```cpp
for (initialization; condition; update) {
  loop body;
}
```

Order of execution:

![](images/for-loop.svg)

e.g. Reading in n numbers:

```cpp
for (int i = 1; i <= n; ++i) {
  cin >> a[i];
}
```

Any of the three parts of a for statement can be left out. If the condition is left out, it is as if the condition is always true.

## The while statement

Here is the structure of a while statement:

```cpp
while (condition) {
  loop body;
}
```

Order of execution:

![](images/while-loop.svg)

e.g. Checking the 3x+1 conjecture:

```cpp
while (x > 1) {
  if (x % 2 == 1) {
    x = 3 * x + 1;
  } else {
    x = x / 2;
  }
}
```

## The do...while statement

Here is the structure of a do...while statement:

```cpp
do {
  loop body;
} while (condition);
```

Order of execution:

![](images/do-while-loop.svg)

The difference from the while statement is that do...while runs the loop body first and checks the condition afterwards.

e.g. Enumerating permutations:

```cpp
do {
  // do something...
} while (next_permutation(a + 1, a + n + 1));
```

## How the three statements relate

```cpp
// for statement

for (statement1; statement2; statement3) {
  statement4;
}

// while statement

statement1;
while (statement2) {
  statement4;
  statement3;
}
```

These are equivalent when statement4 contains no `continue` statement (see below), but the second form is rarely used.

```cpp
// while statement

statement1;
while (statement2) {
  statement1;
}

// do...while statement

do {
  statement1;
} while (statement2);
```

These two forms are also equivalent when statement1 contains no `continue` statement.

```cpp
while (1) {
  // do something...
}

for (;;) {
  // do something...
}
```

Both of these loop forever. (You can exit with `break`, see below.)

As you can see, the three statements can replace each other. In general, though, choose between them like this:

1.  If the loop has a fixed increment step (most commonly when enumerating), use a for statement;
2.  If you only know the condition for stopping the loop, use a while statement;
3.  If you would use a while statement but need to run the loop body before checking the condition, use a do...while statement. This is rarely needed; a common use is reading user input.

## The break and continue statements

The break statement exits the loop.

The continue statement skips the rest of the loop body. Here is an example of continue in a do...while statement:

```cpp
do {
  // do something...
  continue;  // equivalent to goto END;
// do something...
END:;
} while (statement);

```

Both break and continue can be used in the body of any of the three loop statements.

In general, break and continue are used to make the logic of your code clearer, for example:

```cpp
// Less clear logic, deeply nested braces

for (int i = 1; i <= n; ++i) {
  if (i != x) {
    for (int j = 1; j <= n; ++j) {
      if (j != x) {
        // do something...
      }
    }
  }
}

// Clearer logic, simple and flat braces

for (int i = 1; i <= n; ++i) {
  if (i == x) continue;
  for (int j = 1; j <= n; ++j) {
    if (j == x) continue;
    // do something...
  }
}
```

```cpp
// The for condition is complicated and hides that this is really "enumeration"

for (int i = l; i <= r && i % 10 != 0; ++i) {
  // do something...
}

// The for statement does the enumeration; break says "when to stop"

for (int i = l; i <= r; ++i) {
  if (i % 10 == 0) break;
  // do something...
}
```

```cpp
// Repeated statement, unnatural order

statement1;
while (statement3) {
  statement2;
  statement1;
}

// No repeated statement, natural order

while (1) {
  statement1;
  if (!statement3) break;
  statement2;
}
```
