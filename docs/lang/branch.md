By default, a program runs its code in order. Sometimes we want to run certain statements only in some cases, and that is what branches are for. Choosing the right branch statement can make a program more efficient.

## if statements

### Basic if statement

Here is the structure of a basic if statement.

```cpp
if (condition) {
  body;
}
```

An if statement evaluates the condition. If the result is true (nonzero), it runs the body; otherwise it does not.

If the body has only one statement, you can leave out the braces.

### if...else statement

```cpp
if (condition) {
  body1;
} else {
  body2;
}
```

The if...else statement is similar to the if statement; else does not need its own condition. When the condition of the if is satisfied, the statements in the if run; when it is not, the statements in the else run. Again, when a body has only one statement, you can leave out the braces.

### else if statement

```cpp
if (condition1) {
  body1;
} else if (condition2) {
  body2;
} else if (condition3) {
  body3;
} else {
  body4;
}
```

The else if statement combines if and else. It checks several conditions and picks a different branch of statements. The final else does not need a condition. For example, if condition 1 is true, body 1 runs; if condition 3 is true while conditions 1 and 2 are both false, body 3 runs; only when all conditions are false does body 4 run.

In fact, this statement is just the first if's else clause containing a single if statement, with the braces left out and everything put together. If the conditions are parallel alternatives, writing it this way makes the logic of the code clearer.

Logically, it is roughly like this passage:

> When solving a quadratic equation in one variable, the relation between the roots and the discriminant is:
>
> -   If ($\Delta<0$)
>     the equation has no real solution;
> -   Otherwise, if ($\Delta=0$)
>     the equation has two equal real solutions;
> -   Otherwise
>     the equation has two distinct real solutions;

## switch statement

```cpp
switch (selector) {
  case label1:
    body1;
  case label2:
    body2;
  default:
    body3;
}
```

When a switch statement runs, it first evaluates the selector, then picks the matching label based on its value and starts running from that label. The selector must be an expression of integer type, and every label must be a constant of integer type. For example:

```cpp
int i = 1;  // Here i has type int, which meets the requirement of an integer-type expression

switch (i) {
  case 1:
    cout << "OI WIKI" << endl;
}
```

```cpp
char i = 'A';

// Here i has type char, but char
// is also an integer type, so it meets the requirement of an integer-type expression
switch (i) {
  case 'A':
    cout << "OI WIKI" << endl;
}
```

In a switch statement you also need to add break statements where needed to stop execution. Otherwise, after a case is selected, the statements in all following cases and in default will also run. See the example below.

```cpp
char i = 'B';

switch (i) {
  case 'A':
    cout << "OI" << endl;
    break;

  case 'B':
    cout << "WIKI" << endl;

  default:
    cout << "Hello World" << endl;
}
```

The code above prints `WIKI` and `Hello World`. If you don't want the statements in the branches below to run, you need break, as in the example below.

```cpp
char i = 'B';

switch (i) {
  case 'A':
    cout << "OI" << endl;
    break;

  case 'B':
    cout << "WIKI" << endl;
    break;

  default:
    cout << "Hello World" << endl;
}
```

The code above prints WIKI. Because of the break, the statements after it do not run. The last branch does not need a break, because there are no statements after it.

The entry labels must not repeat, but they can be in any order. In other words, the order of the labels does not matter, and the cases (including default) can appear in any order. For example:

```cpp
char i = 'B';

switch (i) {
  case 'B':
    cout << "WIKI" << endl;
    break;

  default:
    cout << "Hello World" << endl;
    break;

  case 'A':
    cout << "OI" << endl;
}
```

You may optionally add braces to the case clauses of a switch. Note, however, that if you need to define variables inside a switch statement, the braces are required. For example:

```cpp
char i = 'B';

switch (i) {
  case 'A': {
    int i = 1, j = 2;
    cout << "OI" << endl;
    ans = i + j;
    break;
  }

  case 'B': {
    int qwq = 3;
    cout << "WIKI" << endl;
    ans = qwq * qwq;
    break;
  }

  default: {
    cout << "Hello World" << endl;
  }
}
```

??? note "How to think about switch"
    Above we used terms like "case clause" a lot. In fact, in the underlying implementation a switch is equivalent to a group of jump statements. That is also why tricks like Duff's Device exist; if you are curious, you can look into it yourself.
