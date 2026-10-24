## About Java

Java is a widely used programming language. It is **cross-platform**, **object-oriented** and supports **generic programming**. It is widely used for enterprise web applications and mobile apps.

## Installation

See [JDK](../tools/compiler.md#jdk).

## Basic syntax

### The main function

Like C/C++, Java needs a function (in object-oriented programming this is called a method) as the entry point where the program starts running.

The main function in Java has a fixed form:

```java
class Test {
    public static void main(String[] args) {
        // the program's code
    }
}
```

A packaged Java program (usually named `*.jar`) can contain many functions like this, but when the program is run, only one of them is executed. Which one is set in the `Manifest` file of the `Jar`. You usually do not need to know about this in OI contests.

### Comments

As in C/C++, Java uses `//` for single-line comments and `/* */` for multi-line comments.

### Primitive data types

|   Type name   |   Meaning  |
| :-----: | :---: |
| boolean |  boolean |
|   byte  |  byte |
|   char  |  character  |
|  double | double-precision floating point |
|  float  | single-precision floating point |
|   int   |   integer  |
|   long  |  long integer  |
|  short  |  short integer  |
|   null  |   null   |

### Declaring variables

```java
int a = 12; // declare a as an integer and assign 12 to it
String str = "Hello, OI-wiki"; // declare the string variable str
char ch = 'W';
double PI = 3.1415926;
```

### The final keyword

`final` means the value is final and cannot be changed. A variable marked `final` can be assigned only once and never changes after that.

```java
final double PI = 3.1415926;
```

### Arrays

```java
// an integer array with ten elements
// the syntax is: type[] name = new type[size]
int[] ary = new int[10];
```

### Strings

-   String is a built-in class in Java.

```java
// the simplest way to create a string variable is as follows
String a = "Hello";

// you can also create a string variable from a character array
char[] stringArray = { 'H', 'e', 'l', 'l', 'o' };
String s = new String(stringArray);
```

### Packages and imports

Every class (`Class`) in Java is placed in a package (`package`). Two classes in the same package cannot have the same name. The first line of a class file usually states which package the class belongs to. For example:

```java
package org.oi-wiki.tutorial;
```

Packages are usually named like this: `owner's top-level domain.owner's second-level domain.project name`.

Use the `import` keyword to import classes that are not in the same package as the current class. For example, the `Scanner` class used below:

```java
import java.util.Scanner;
```

To import all classes in a package, replace the class name before the semicolon at the end of this statement with `*`.

### Input

You can handle command-line input with the `Scanner` class.

```java
package org.oiwiki.tutorial;

import java.util.Scanner;

class Test {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in); // System.in is the input stream
        int a = scan.nextInt();
        double b = scan.nextDouble();
        String c = scan.nextLine();
    }
}
```

### Output

You can print variables with formatted output.

|  Symbol  |   Meaning  |
| :--: | :---: |
| `%f` |  floating point |
| `%s` | string |
| `%d` |  integer |
| `%c` |  character |

```java
class Test {
    public static void main(String[] args) {
        int a = 12;
        char b = 'A';
        double s = 3.14;
        String str = "Hello world";
        System.out.printf("%f\n", s);
        System.out.printf("%d\n", a);
        System.out.printf("%c\n", b);
        System.out.printf("%s\n", str);
    }
}
```

### Control statements

Java's control flow statements are basically the same as those of C++.

#### Selection

-   if

```java
class Test {
    public static void main(String[] args) {
        if ( /* condition */ ){
            // code here runs when the condition is true
        }
    }
}
```

-   if...else

```java
class Test {
    public static void main(String[] args) {
        if ( /* condition */ ) {
            // code here runs when the condition is true
        } else {
            // code here runs when the condition is false
        }
    }
}
```

-   if...else if...else

```java
class Test {
    public static void main(String[] args) {
        if ( /* condition */ ) {
            //code here runs when the condition is true
        } else if ( /* condition 2 */ ) {
            // code here runs when condition 2 is true
        } else {
          // code here runs when none of the conditions above is true
        }
    }
}
```

-   switch...case

```java
class Test {
    public static void main(String[] args) {
        switch ( /* expression */ ){
          case /* value 1 */:
              // this code runs when the expression equals value 1
              break; // without break, the program keeps running the following code in order until it reaches a break
          case /* value 2 */:
              // this code runs when the expression equals value 2
              break;
          default:
              // code here runs when the expression matches none of the values listed above
        }
    }
}
```

#### Loops

-   for

The `for` keyword can be used in two ways. The first is the ordinary `for` loop:

```java
class Test {
    public static void main(String[] args) {
        for ( /* initialization */; /* loop condition */; /* step run after each iteration */ ) {
            // the loop body runs while the loop condition is true
        }
    }
}
```

The second is similar to `foreach` in C++. It loops over the data in an array or collection, as if the loop variable of the first form were hidden. It looks like this:

```java
class Test {
    public static void main(String[] args) {
        for ( /* element type X */ /* element name Y */ : /* collection Z */ ) {
            // in each iteration of this block, Y is one of the elements of collection Z.
        }
    }
}
```

-   while

```java
class Test {
    public static void main(String[] args) {
        while ( /* condition */ ) {
            // the loop body runs while the condition is true
        }
    }
}
```

-   do...while

```java
class Test {
    public static void main(String[] args) {
        do {
          // the code to run
        } while ( /* loop condition */ );
    }
}
```

## Things to note

### The class name must match the file name

To compile a Java source file, the class name must match the file name; otherwise the compiler reports that it cannot find the class. The file name is usually given by the OJ.

Example:

`Add.java`

```java
class Add {
    public static void main(String[] args) {
        // ...
    }
}
```

In this file, you must use `Add` as the class name for it to compile.
