???+ warning "Note"
    Everything below is based on Java JDK 8. Some details may have changed in later versions.

## Faster input and output

`Scanner` and `System.out.print` work fine at first, but they become slow on larger inputs. So we need some ways to speed up IO.

### Using Kattio + StringTokenizer for input

One of the most common ways to speed up IO is to use [Kattio.java](https://github.com/Kattis/kattio/blob/master/Kattio.java) from Kattis.[^ref1] This approach wraps `StringTokenizer` and `PrintWriter` in one class for convenience. When solving problems (if the contest/organizer allows it), you can use this template directly.

Below is the IO template to include in your code. Since the original Kattio from Kattis contains some rarely used features, the template below has been adjusted a bit (the original Kattio is licensed under MIT).

```java
class Kattio extends PrintWriter {
    private BufferedReader r;
    private StringTokenizer st;
    // standard IO
    public Kattio() { this(System.in, System.out); }
    public Kattio(InputStream i, OutputStream o) {
        super(o);
        r = new BufferedReader(new InputStreamReader(i));
    }
    // file IO
    public Kattio(String input, String output) throws IOException {
        super(output);
        r = new BufferedReader(new FileReader(input));
    }
    // returns null when there is no more input
    public String next() {
        try {
            while (st == null || !st.hasMoreTokens())
                st = new StringTokenizer(r.readLine());
            return st.nextToken();
        } catch (Exception e) {}
        return null;
    }
    public int nextInt() { return Integer.parseInt(next()); }
    public double nextDouble() { return Double.parseDouble(next()); }
    public long nextLong() { return Long.parseLong(next()); }
}
```

The code below shows simple usage of Kattio:

```java
class Test {
    public static void main(String[] args) {
        Kattio io = new Kattio();
        // string input
        String str = io.next();
        // int input
        int num = io.nextInt();
        // output
        io.println("Result");
        // make sure to close the IO stream so the output is actually written
        io.close();
    }
}
```

### Using StreamTokenizer for input

In some cases `StringTokenizer` causes MLE (Memory Limit Exceeded). Then we need to use `StreamTokenizer` for input.

```java
import java.io.*;
public class Main {
    // IO code
    public static StreamTokenizer in = new StreamTokenizer(new BufferedReader(new InputStreamReader(System.in), 32768));
    public static PrintWriter out = new PrintWriter(new OutputStreamWriter(System.out));
    public static double nextDouble() throws IOException { in.nextToken(); return in.nval; }
    public static float nextFloat() throws IOException { in.nextToken(); return (float)in.nval; }
    public static int nextInt() throws IOException { in.nextToken(); return (int)in.nval; }
    public static String next() throws IOException { in.nextToken(); return in.sval; }
    public static long nextLong() throws Exception { in.nextToken(); return (long)in.nval;}
    
    // usage example
    public static void main(String[] args) throws Exception {
        int n = nextInt();
        out.println(n);
        out.close();
    }
}
```

### Comparing the Kattio + StringTokenizer approach with the StreamTokenizer approach

1.  `StreamTokenizer` uses less memory than `StringTokenizer`. When a Java reference solution gets MLE, you can try `StreamTokenizer`. However, `StreamTokenizer` loses precision and has problems reading some data;
    -   The `StreamTokenizer` source has a `Type` that is decided by the input. If the input is a string that **starts with a digit**, such as `123oi`, it forces the type to be `double`, so reading a `String` as a `double` throws an exception;
    -   `StreamTokenizer` loses precision when reading numbers of `1e14` or larger;
2.  When using `PrintWriter`, remember to call `close()` at the end of the program to close the output stream, or call `flush()` to flush the buffer whenever you need output to appear. Otherwise the content will not be written to the console/file.
3.  `Kattio` extends the `PrintWriter` class, so a `Kattio` object has all the features of `PrintWriter` and can call `PrintWriter` methods directly to produce output, while it holds a `StringTokenizer` as a member variable. The second approach, `Main`, holds both a `StreamTokenizer` and a `PrintWriter` as member variables, so the two are used slightly differently.

In summary, `StringTokenizer` is the better choice in most cases. You can try `StreamTokenizer` in extreme MLE situations, but `StreamTokenizer` cannot handle data beyond the `int` range.

## BigInteger and number theory

`BigInteger` is Java's arbitrary-precision integer class. It makes big-number problems easy to solve.

### Initialization

There are two common ways to create a `BigInteger`:

```java
import java.io.PrintWriter;
import java.math.BigInteger;

class Main {
    static PrintWriter out = new PrintWriter(System.out);
    public static void main(String[] args) {
        BigInteger a = new BigInteger("12345678910");  // create a BigInteger from a string in decimal
        out.println(a);  // a is 12345678910 
        BigInteger b = new BigInteger("1E", 16);  // create a BigInteger from a string in the given base
        out.println(b);  // b is 30 
        out.close();
    }
}

```

### Basic operations

Below, `this` stands for the current `BigIntger`:

|             Method             |               Description               |
| :-------------------------: | :----------------------------: |
|           `abs()`           |         returns the absolute value of `this`         |
|          `negate()`         |         returns the negation of `this`         |
|    `add(BigInteger val)`    |      returns the sum of `this` and `val`      |
|  `subtract(BigInteger val)` |      returns the difference of `this` and `val`      |
|  `multiply(BigInteger val)` |      returns the product of `this` and `val`      |
|   `divide(BigInteger val)`  |      returns the quotient of `this` and `val`      |
| `remainder(BigInteger val)` |     returns the remainder of `this` divided by `val`     |
|    `mod(BigInteger val)`    |     returns `this` modulo `val`     |
|        `pow(int val)`       |      returns `this` to the power `val`      |
|    `and(BigInteger val)`    |     returns the bitwise AND of `this` and `val`     |
|     `or(BigInteger val)`    |     returns the bitwise OR of `this` and `val`     |
|           `not()`           |         returns the bitwise NOT of `this`        |
|    `xor(BigInteger val)`    |     returns the bitwise XOR of `this` and `val`    |
|      `shiftLeft(int n)`     |       returns `this` shifted left by `n` bits       |
|     `shiftRight(int n)`     |       returns `this` shifted right by `n` bits       |
|    `max(BigInteger val)`    |     returns the larger of `this` and `val`     |
|    `min(BigInteger val)`    |     returns the smaller of `this` and `val`     |
|         `bitCount()`        | returns the number of `1` bits in the binary form of `this`, not counting the sign bit |
|        `bitLength()`        |    returns the length of the binary form of `this`, not counting the sign bit    |
|     `getLowestSetBit()`     |      returns the position of the rightmost `1` bit in the binary form of `this`     |
| `compareTo(BigInteger val)` |      compares the values of `this` and `val`     |
|         `toString()`        |      returns the decimal string form of `this`     |
|    `toString(int radix)`    |  returns the string form of `this` in base `raidx` |

Usage examples:

```java
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static BigInteger a, b;
    
    static void abs() {
        out.println("abs:");
        a = new BigInteger("-123");
        out.println(a.abs());  // prints 123 
        a = new BigInteger("123");
        out.println(a.abs());  // prints 123 
    }
    
    static void negate() {
        out.println("negate:");
        a = new BigInteger("-123");
        out.println(a.negate());  // prints 123 
        a = new BigInteger("123");
        out.println(a.negate());  // prints -123 
    }
    
    static void add() {
        out.println("add:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.add(b));  // prints 246 
    }
    
    static void subtract() {
        out.println("subtract:");
        a = new BigInteger("123");
        b = new BigInteger("123");
        out.println(a.subtract(b));  // prints 0 
    }
    
    static void multiply() {
        out.println("multiply:");
        a = new BigInteger("12");
        b = new BigInteger("12");
        out.println(a.multiply(b));  // prints 144 
    }
    
    static void divide() {
        out.println("divide:");
        a = new BigInteger("12");
        b = new BigInteger("11");
        out.println(a.divide(b));  // prints 1 
    }
    
    static void remainder() {
        out.println("remainder:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.remainder(b));  // prints 2 
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.remainder(b));  // prints -2 
    }
    
    static void mod() {
        out.println("mod:");
        a = new BigInteger("12");
        b = new BigInteger("10");
        out.println(a.mod(b));  // prints 2 
        a = new BigInteger("-12");
        b = new BigInteger("10");
        out.println(a.mod(b));  // prints 8 
    }
    
    static void pow() {
        out.println("pow:");
        a = new BigInteger("2");
        out.println(a.pow(10));  // prints 1024 
    }
    
    static void and() {
        out.println("and:");
        a = new BigInteger("3");  // 11 
        b = new BigInteger("5");  // 101 
        out.println(a.and(b));  // prints 1 
    }
    
    static void or() {
        out.println("or:");
        a = new BigInteger("2");  // 10 
        b = new BigInteger("5");  // 101 
        out.println(a.or(b));  // prints 7 
    }
    
    static void not() {
        out.println("not:");
        a = new BigInteger("2147483647");  // 01111111 11111111 11111111 11111111 
        out.println(a.not());  // prints -2147483648 in binary: 10000000 00000000 00000000 00000000 
    }
    
    static void xor() {
        out.println("xor:");
        a = new BigInteger("6");  // 110 
        b = new BigInteger("5");  // 101 
        out.println(a.xor(b));  // 011 prints 3 
    }
    
    static void shiftLeft() {
        out.println("shiftLeft:");
        a = new BigInteger("1");
        out.println(a.shiftLeft(10));  // prints 1024 
    }
    
    static void shiftRight() {
        out.println("shiftRight:");
        a = new BigInteger("1024");
        out.println(a.shiftRight(8));  // prints 4 
    }
    
    static void max() {
        out.println("max:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.max(b));  // prints 6 
    }
    
    static void min() {
        out.println("min:");
        a = new BigInteger("6");
        b = new BigInteger("5");
        out.println(a.min(b));  // prints 5 
    }
    
    static void bitCount() {
        out.println("bitCount:");
        a = new BigInteger("6");  // 110 
        out.println(a.bitCount());  // prints 2 
    }
    
    static void bitLength() {
        out.println("bitLength:");
        a = new BigInteger("6");  // 110 
        out.println(a.bitLength());  // prints 3 
    }
    
    static void getLowestSetBit() {
        out.println("getLowestSetBit:");
        a = new BigInteger("8");  // 1000 
        out.println(a.getLowestSetBit());  // prints 3 
    }
    
    static void compareTo() {
        out.println("compareTo:");
        a = new BigInteger("8");
        b = new BigInteger("9");
        out.println(a.compareTo(b));  // prints -1 
        a = new BigInteger("8");
        b = new BigInteger("8");
        out.println(a.compareTo(b));  // prints 0 
        a = new BigInteger("8");
        b = new BigInteger("7");
        out.println(a.compareTo(b));  // prints 1 
    }
    
    static void toStringTest() {
        out.println("toString:");
        a = new BigInteger("15");
        out.println(a.toString());  // prints 15 
        out.println(a.toString(16));  // prints f 
    }
    
    public static void main(String[] args) {
        abs();
        negate();
        add();
        subtract();
        multiply();
        divide();
        remainder();
        mod();
        pow();
        and();
        or();
        not();
        xor();
        shiftLeft();
        shiftRight();
        max();
        min();
        bitCount();
        bitLength();
        getLowestSetBit();
        compareTo();
        toStringTest();
        out.close();
    }
}
```

### Mathematical operations

Below, `this` stands for the current `BigIntger`:

|                  Method                 |                Description                |
| :----------------------------------: | :------------------------------: |
|         `gcd(BigInteger val)`        | returns the greatest common divisor of the absolute values of `this` and `val` |
|      `isProbablePrime(int val)`      |      returns a boolean saying whether `this` is (probably) prime     |
|         `nextProbablePrime()`        |        returns the first prime greater than `this`        |
| `modPow(BigInteger b, BigInteger p)` |    returns `this` to the power `b`, modulo `p`    |
|      `modInverse(BigInteger p)`      |     returns the multiplicative inverse of `this` modulo `p`    |

Usage examples:

```java
import java.io.PrintWriter;
import java.math.BigInteger;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static BigInteger a, b, p;
    
    static void gcd() {  // greatest common divisor 
        a = new BigInteger("120032414321432144212100");
        b = new BigInteger("240231431243123412432140");
        out.println(String.format("gcd(%s,%s)=%s", a.toString(), b.toString(), a.gcd(b).toString()));  // gcd(120032414321432144212100,240231431243123412432140)=20 
    }
    
    static void isPrime() {  // checks whether the number is prime using Miller-Rabin; a larger argument gives higher accuracy and higher cost. The accuracy is (1-1/(val*2)) 
        a = new BigInteger("1200324143214321442127");
        out.println("a:" + a.toString());
        out.println(a.isProbablePrime(10) ? "a is prime" : "a is not prime");  // a is not prime 
    }
    
    static void nextPrime() {  // finds the next prime after this number 
        a = new BigInteger("1200324143214321442127");
        out.println("a:" + a.toString());
        out.println(String.format("a nextPrime is %s", a.nextProbablePrime().toString()));  // a nextPrime is 1200324143214321442199 
    }
    
    static void modPow() {  // fast exponentiation; faster than the usual version thanks to math optimizations inside 
        a = new BigInteger("2");
        b = new BigInteger("10");
        p = new BigInteger("1000");
        out.println(String.format("a:%s b:%s p:%s", a, b, p));
        out.println(String.format("a^b mod p:%s", a.modPow(b, p).toString()));//  24 
    }
    
    static void modInverse() {  // modular inverse 
        a = new BigInteger("10");
        b = new BigInteger("3");
        out.println(a.modInverse(b));  // a ^ (p-2) mod p = 1 
    }
    
    public static void main(String[] args) {
        gcd();
        isPrime();
        nextPrime();
        modPow();
        modInverse();
        out.close();
    }
}
```

For more on Miller-Rabin, see [Miller–Rabin primality test](../math/number-theory/prime.md#millerrabin-素性测试).

## Primitive types and wrapper types

### Introduction

Primitive types are not objects, so they cannot take part in object-oriented code directly. To let them do so, Java provides a wrapper class for each of the eight primitive types: `Byte`, `Double`, `Float`, `Integer`, `Long`, `Short`, `Character` and `Boolean`. They correspond as follows:

|   Primitive type  |    Wrapper type   |
| :-------: | :---------: |
|   `byte`  |    `Byte`   |
|  `short`  |   `Short`   |
| `boolean` |  `Boolean`  |
|   `char`  | `Character` |
|   `int`   |  `Integer`  |
|   `long`  |    `Long`   |
|  `float`  |   `Float`   |
|  `double` |   `Double`  |

### Differences

Here we use `int` and `Integer` as an example:

1.  `Integer` is the wrapper class of `int`, while `int` is one of Java's primitive data types.
2.  An `Integer` must be instantiated before it can be used; an `int` does not.
3.  An `Integer` is really a reference. When you `new` an `Integer`, an object is actually created, while an `int` stores its value directly.
4.  The default value of an `Integer` is `null`, and it accepts both `null` and `int` values. The default value of an `int` is 0, and it cannot hold `null`.
5.  Comparing two `Integer` variables with `==` may give a wrong result; you must use `equals()`. For `int`, you can use `==` directly.

### Boxing and unboxing

Here we use `int` and `Integer` as an example:

`Integer` is an object type and `int` is a primitive type, so you cannot assign one to the other directly. When you need to convert, turning a primitive into its wrapper type is called boxing, and the reverse is called unboxing.

```java
// primitive type
int value1 = 1;
// box into the wrapper type
Integer integer = Integer.valueOf(value1);
// unbox into the primitive type
int value2 = integer.intValue();
```

Java 5 introduced automatic boxing and unboxing:

```java
Integer integer = 1;
int value = integer;
```

???+ warning "Note"
    Although the JDK added automatic boxing and unboxing, still choose the right type when declaring variables: the wrapper type `Integer` can hold `null`, but the primitive type `int` cannot. So unboxing a wrapper whose value is `null` throws an exception. The code below shows this.
    
    ```java
    Integer integer = Integer.valueOf(null);
    integer.intValue();  // throws java.lang.NumberFormatException
    
    Integer integer = null;
    integer.intValue();  // throws java.lang.NullPointerException
    ```

## Inheritance

In object-oriented programming, creating a new design based on an existing one is called inheritance. With inheritance, a new class is not created from nothing; it is defined on top of an existing class. Through inheritance, the new class automatically gets all members of the base class, including member variables and methods, with every kind of access level, whether `public` or `private`. Clearly, defining a new class through inheritance is much simpler, faster and more convenient than writing one from scratch. Inheritance is one of the most important ways to reuse code.

In Java, the keyword for inheritance is `extends`. Java supports only single inheritance of classes, but a class can implement multiple interfaces.

In Java, every class is a subclass of the `Object` class.

When a subclass inherits from a parent class, all members of the parent class, including variables and methods, become members of the subclass, except constructors. Constructors belong only to the parent class: their name is the class name, so the parent's constructors do not exist in the subclass. Apart from that, the subclass gets all members of the parent class.

Each member has an access level. The subclass inherits all members of the parent class, but their access levels affect how the subclass can use them: some parent members become part of the subclass's public interface, while others are deeply hidden, so that even the subclass itself cannot access them directly.

The table below shows how parent-class members with each access level can be accessed in the subclass:

|    Access level of parent member   |      Meaning in the parent class      |                     Meaning in the subclass                    |
| :-----------: | :---------------: | :--------------------------------------------: |
|    `public`   |       open to all classes      |                     open to all classes                     |
|  `protected`  | accessible only to other classes in the package, the class itself and its subclasses |                accessible only to other classes in the package, the class itself and its subclasses               |
| default (no modifier, `default`) |    accessible only to other classes in the package    | if the subclass is in the same package as the parent, accessible only to other classes in the package; otherwise it is like `private` and cannot be accessed |
|   `private`   |      accessible only to the class itself     |                      not accessible                      |

## Polymorphism

In Java, when you assign an object to a variable, the object's type must match the variable's type. But because Java has inheritance, this rule becomes: **a variable can hold an object of its declared type or of any subtype of that type**.

If a type implements an interface, it can also be called a subtype of that interface.

In Java, variables that hold objects are polymorphic variables. The term "polymorphism" (literally "many forms") means a variable can hold objects of different types (its declared type or any subtype).

Polymorphic variables:

1.  Java object variables are polymorphic: they can hold objects of more than one type.
2.  They can hold objects of the declared type, or objects of subclasses of the declared type.
3.  Assigning an object of a subclass to a variable of the parent class is called upcasting.

## Generics

Generics mean that when a class is defined, the concrete types of its fields or method parameters are not fixed; the types are specified only when the class is used (or an object is created). In essence, generics are parameterized types: the data type being worked on is given as a parameter.

Generics provide compile-time type safety checks, which let the compiler detect illegal types.

## Interfaces

### Introduction

An interface in Java is an abstract type: a collection of abstract methods, usually declared with `interface`. A class inherits an interface's abstract methods by implementing the interface.

An interface is not a class. Interfaces are written much like classes, but they are different concepts. A class describes the fields and methods of objects. An interface contains methods that classes must implement.

Unless the class implementing an interface is abstract, it must define all methods of the interface.

An interface cannot be instantiated, but it can be implemented. A class that implements an interface must implement all methods described in it; otherwise the class must be declared abstract. Also, in Java an interface type can be used to declare a variable. Such a variable can be a null pointer, or be bound to an object that implements the interface.

### Differences from classes

1.  An interface cannot be used to create objects.
2.  An interface has no constructors.
3.  All methods in an interface must be abstract. Since Java 8, an interface can have non-abstract methods marked with the `default` keyword.
4.  An interface cannot contain member variables, except static and final variables.
5.  An interface is not inherited by a class; it is implemented by a class.
6.  Interfaces support multiple inheritance; classes do not.

### Declaration

```java
[visibility] interface InterfaceName [extends OtherInterfaceName] {
        // declare variables
        // abstract methods
}
```

### Implementation

```java
...implements InterfaceName[, OtherInterfaceName, OtherInterfaceName..., ...] ...
```

## Lambda expressions

### Introduction

Lambda expressions, also called closures, are the most important new feature of Java 8.

A lambda expression lets you pass a function as an argument to a method.

Lambda expressions make code shorter and more compact.

### Syntax

-   Optional type declarations: you do not need to declare parameter types; the compiler can infer them.
-   Optional parentheses around parameters: a single parameter needs no parentheses, but multiple parameters do.
-   Optional braces: if the body has only one statement, you do not need braces.
-   Optional return keyword: if the body is a single expression, the compiler returns its value automatically; with braces, you must state explicitly that the expression returns a value.

Lambda expressions are written like this:

```java
// 1. takes no parameters and returns 5
() -> 5

// 2. takes one parameter (a number) and returns twice its value
x -> 2 * x

// 3. takes 2 parameters (numbers) and returns their difference
(x, y) -> x – y

// 4. takes 2 int values and returns their sum
(int x, int y) -> x + y

// 5. takes a String object and prints it to the console, returning nothing (looks like returning void)
(String s) -> System.out.print(s)
```

For example, a custom comparator that sorts a string array by length can be written with a lambda expression like this.

```java
import java.util.Arrays;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        Arrays.sort(plants, (String first, String second) -> (first.length() - second.length()));
        for (String word : plants) {
            out.print(word + " ");
        }
        out.close();
    }
}
```

You can also use several statements in a lambda expression, as in the example below.

```java
import java.io.PrintWriter;
import java.util.Arrays;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
        Arrays.sort(plants, (first, second) ->
        {
            // the parameter types are omitted; they can be inferred from context
            int result = first.length() - second.length();
            return result;
        });
        for (String word : plants) {
            out.print(word + " ");
        }
        out.close();
    }
}
```

Here `->` is the arrow symbol: the parentheses before it receive the parameters, and what follows produces the return value (in effect, a method is being passed).

### Functional interfaces

1.  It is an interface that follows Java's interface definition.
2.  It contains exactly one abstract method.
3.  Since there is only one unimplemented method, a lambda expression can fill it in automatically.

Functional interfaces are used like this:

???+ example "Print the strings whose length is a multiple of 2"
    ```java
    import java.io.PrintWriter;
    
    public class Main {
        static PrintWriter out = new PrintWriter(System.out);
        
        public static void main(String[] args) {
            String[] plants = {"Mercury", "venus", "Earth", "Mars", "Jupiter", "Saturn", "Uranus", "Neptune"};
            Test test = s -> {  // a lambda expression as an instance of the functional interface
                if (s.length() % 2 == 0) {
                    return true;
                }
                return false;
            };
            for (String word : plants) {
                if (test.check(word)) {
                    out.print(word + " ");
                }
            }
            out.close();
        }
    }
    
    interface Test {
        public boolean check(String s);
    }
    ```

???+ example "Implement the four arithmetic operations"
    ```java
    import java.io.PrintWriter;
    
    public class Main {
        static PrintWriter out = new PrintWriter(System.out);
        
        public static double calc(double a, double b, Calculator util) {
            return util.operation(a, b);
        }
        
        public static void main(String[] args) {
            Calculator util[] = new Calculator[4];  // define an array of functional interfaces
            util[0] = (a, b) -> a + b;
            util[1] = (a, b) -> a - b;
            util[2] = (a, b) -> a * b;
            util[3] = (a, b) -> a / b;
            double a = 20, b = 15;
            for (Calculator c : util) {
                System.out.println(calc(a, b, c));
            }
            out.close();
        }
    }
    
    interface Calculator {
        public double operation(double a, double b);
    }
    ```

## Collection

`Collection` is an interface in Java, implemented by several generic container interfaces. Here, `Collection` refers to data structures that store objects.

The element type of a Java `Collection` must be an object type, not a primitive type.

Everything below relies on polymorphism in Java: each container is used through the interface it implements.

Common interfaces include `List`, `Queue`, `Set` and `Map`.

### Defining containers

When defining a generic container, you should specify the data type. If you do not, and add data freely as `Object`, the code still compiles in Java 8, but you get many warnings and risks.

For example, the following definition is safe: the container accepts only `Integer`.

```java
List<Integer> list1 = new LinkedList<>();
```

The following definition, however, causes warnings.

```java
List list = new ArrayList<>();
list.add(1);
list.add(true);
list.add(1.01);
list.add(1L);
list.add("I am String");
```

So unless you have a special need, the second way is not recommended, because the compiler cannot check whether the stored data is safe. When you read a value with `list.get(index)`, its type is unknown (everything comes back as `Object`), so you must cast it back to its original type by hand, and one mistake can cause a cast exception.

If the type is specified, such as `List<Integer>`, the compiler checks the type of the data you put in, and only integers are allowed. When declaring a collection variable you can only use wrapper types such as `List<Integer>` or your own `Class`, not primitive types such as `List<int>`.

### List

#### ArrayList

`ArrayList` is an array that grows dynamically as needed. Its default initial length is 10. When it runs out of space, it grows by a factor of $\dfrac{3}{2}$.

##### Initialization

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        List<Integer> list1 = new ArrayList<>();  // create a growable array named list1 with the default initial length (10)
        List<Integer> list2 = new ArrayList<>(30);  // create a growable array named list2 with initial length 30
        List<Integer> list3 = new ArrayList<>(list2);  // create a growable array named list3, using the elements and size of list2 as its initial value
    }
}
```

#### LinkedList

`LinkedList` is a doubly linked list.

##### Initialization

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    public static void main(String[] args) {
        List<Integer> list1 = new LinkedList<>();  // create a doubly linked list named list1 
        List<Integer> list2 = new LinkedList<>(list1);  // create a doubly linked list named list2 and add all elements of list1 to it 
    }
}
```

#### Common methods

Below, `this` stands for the current `List<Integer>`:

|            Method            |                Description                |
| :-----------------------: | :------------------------------: |
|          `size()`         |           returns the length of `this`          |
|     `add(Integer val)`    |      inserts `val` at the end of `this`      |
| `add(int idx, Integer e)` |   inserts `e` at position `idx` of `this`   |
|       `get(int idx)`      | returns the value at position `idx` of `this`; throws an exception if out of bounds |
| `set(int idx, Integer e)` |   sets the value at position `idx` of `this` to `e`   |

Usage examples and a comparison:

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static List<Integer> array = new ArrayList<>();
    static List<Integer> linked = new LinkedList<>();
    
    static void add() {
        array.add(1);  // time complexity is O(1) 
        linked.add(1);  // time complexity is O(1) 
    }
    
    static void get() {
        array.get(10);  // time complexity is O(1) 
        linked.get(10);  // time complexity is O(11) 
    }
    
    static void addIdx() {
        array.add(0, 2);  // worst-case time complexity is O(n)
        linked.add(0, 2);  // worst-case time complexity is O(n)
    }
    
    static void size() {
        array.size();  // time complexity is O(1)
        linked.size();  // time complexity is O(1)
    }
    
    static void set() {  // this method returns the old value at that position
        array.set(0, 1);  // time complexity is O(1)
        linked.set(0, 1);  // worst-case time complexity is O(n)
    }

}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.LinkedList;
import java.util.List;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static List<Integer> array = new ArrayList<>();
    static List<Integer> linked = new LinkedList<>();
    
    static void function1() {  // plain traversal
        for (int i = 0; i < array.size(); i++) {
            out.println(array.get(i));  // traversing the growable array: O(n)
        }
        for (int i = 0; i < linked.size(); i++) {
            out.println(linked.get(i));  // traversing the doubly linked list: O(n^2), because get(i) on a LinkedList is O(i)
        }
    }
    
    static void function2() {  // traversal with an enhanced for loop 
        for (int e : array) {
            out.println(e);
        }
        for (int e : linked) {
            out.println(e);  // both are O(n) 
        }
    }
    
    static void function3() {  // traversal with an iterator 
        Iterator<Integer> iterator1 = array.iterator();
        Iterator<Integer> iterator2 = linked.iterator();
        while (iterator1.hasNext()) {
            out.println(iterator1.next());
        }
        while (iterator2.hasNext()) {
            out.println(iterator2.next());
        }  // both are O(n) 
    }

}
```

???+ warning "Note"
    Do not delete elements from a `List` while traversing it with `for` or `foreach`; otherwise an exception is thrown.
    
    The reason is simple: `list.size()` changes, but the number of iterations already done does not. The element that was supposed to be at the next `index` moves to the current `index` because of the deletion, so the next iteration works on the element that was supposed to be two positions ahead. In the end, the loop works on the wrong elements.

### Queue

#### LinkedList

You can use `LinkedList` to implement an ordinary queue; underneath, it simulates a queue with a linked list.

##### Initialization

```java
Queue<Integer> q = new LinkedList<>();
```

`LinkedList` implements both the `List` interface and the `Deque` interface, and `Deque` extends `Queue`, so `LinkedList` can serve as both a `List` and a `Queue`.

#### ArrayDeque

You can use `ArrayDeque` to implement an ordinary queue; underneath, it simulates a queue with an array.

##### Initialization

```java
Queue<Integer> q = new ArrayDeque<>();
```

`ArrayDeque` implements the `Deque` interface, and `Deque` extends `Queue`, so `ArrayDeque` can serve as a `Queue`.

#### Differences between LinkedList and ArrayDeque as Queue implementations

1.  Data structure: both `ArrayDeque` and `LinkedList` implement Java's Deque (double-ended queue) interface. But `ArrayDeque` does not implement Java's List interface, so it cannot do operations by index.
2.  Thread safety: neither `ArrayDeque` nor `LinkedList` handles thread synchronization, so neither is thread-safe.
3.  Underlying implementation: `ArrayDeque` is based on a dynamic array, while `LinkedList` is based on a doubly linked list.
4.  Traversal speed: `ArrayDeque` uses one contiguous block of memory, so thanks to locality it hits CPU cache lines better. `LinkedList` uses scattered memory, which is unfriendly to cache lines.
5.  Operation speed: the stack and queue operations of both `ArrayDeque` and `LinkedList` take $O(1)$ time. Pushing or enqueuing into an `ArrayDeque` may trigger a resize, but by amortized analysis it is still $O(1)$.
6.  Extra memory: `ArrayDeque` has unused space outside its head and tail pointers, while `LinkedList` adds predecessor and successor pointers to every node.

#### PriorityQueue

`PriorityQueue` is a priority queue. By default it is a min-heap.

##### Initialization

```java
Queue<Integer> q1 = new PriorityQueue<>();  // min-heap
Queue<Integer> q2 = new PriorityQueue<>((x, y) -> {return y - x;});  // max-heap
```

#### Common methods

In the table below, the queue is defined as `Queue<Integer>`.

|          Method         |                     Description                     |
| :------------------: | :----------------------------------------: |
|       `size()`       |                  returns the current length of the queue                  |
|  `add(Integer val)`  |     inserts `val` into the queue; throws an exception if this violates the queue's capacity limit     |
| `offer(Integer val)` | inserts `val` into the queue; if this violates the queue's capacity limit, the insertion fails but no exception is thrown |
|      `isEmpty()`     |            checks whether the queue is empty; returns `true` if it is           |
|       `peek()`       |            returns the front element; returns `null` if the queue is empty           |
|       `poll()`       |          returns and removes the front element; returns `null` if the queue is empty          |

Usage examples and a comparison:

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Queue<Integer> q1 = new LinkedList<>();
    static Queue<Integer> q2 = new PriorityQueue<>();
    
    static void add() {  // add and offer do the same thing; the difference is whether an exception can be thrown 
        q1.add(1);  // time complexity is O(1) 
        q2.add(1);  // time complexity is O(logn) 
    }
    
    static void isEmpty() {
        q1.isEmpty();  // time complexity is O(1) 
        q2.isEmpty();  // space complexity is O(1) 
    }
    
    static void size() {
        q1.size();  // time complexity is O(1) 
        q2.size();  // returns the length of q2 
    }
    
    static void peek() {
        q1.peek();  // time complexity is O(1) 
        q2.peek();  // time complexity is O(logn) 
    }
    
    static void poll() {
        q1.poll();  // time complexity is O(1) 
        q2.poll();  // time complexity is O(logn) 
    }
}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.LinkedList;
import java.util.PriorityQueue;
import java.util.Queue;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Queue<Integer> q1 = new LinkedList<>();
    static Queue<Integer> q2 = new PriorityQueue<>();
    
    static void test() {
        while (!q1.isEmpty()) {  // complexity is O(n) 
            out.println(q1.poll());
        }
        while (!q2.isEmpty()) {  // complexity is O(nlogn) 
            out.println(q2.poll());
        }
    }

}
```

### Deque

`Deque` is Java's double-ended queue. We usually use it for both queue operations and stack operations.

#### Main methods

In the table below, the queue is defined as `Deque<Integer>`.

|            Method            |                     Description                     |
| :-----------------------: | :----------------------------------------: |
|  `addFirst(Integer val)`  |     inserts `val` at the front; throws an exception if this violates the queue's capacity limit     |
| `offerFirst(Integer val)` | inserts `val` at the front; if this violates the queue's capacity limit, the insertion fails but no exception is thrown |
|      `removeFirst()`      |           returns and removes the front element; throws an exception if the queue is empty           |
|       `pollFirst()`       |         returns and removes the front element; returns `null` if the queue is empty        |
|       `peekFirst()`       |          returns the front element; returns `null` if the queue is empty          |
|    `push(Integer val)`    |         inserts `val` at the front; same as `addFirst`        |
|          `pop()`          |         returns and removes the front element; same as `removeFirst`        |
|         `remove()`        |          removes the front element; same as `removeFirst`          |
|          `poll()`         |           removes the front element; same as `pollFirst`           |
|   `addLast(Integer val)`  |     inserts `val` at the back; throws an exception if this violates the queue's capacity limit     |
|  `offerLast(Integer val)` | inserts `val` at the back; if this violates the queue's capacity limit, the insertion fails but no exception is thrown |
|       `removeLast()`      |           returns and removes the back element; throws an exception if the queue is empty           |
|        `pollLast()`       |         returns and removes the back element; returns `null` if the queue is empty        |
|        `peekLast()`       |          returns the back element; returns `null` if the queue is empty          |
|     `add(Integer val)`    |         inserts `val` at the back; same as `addLast`         |
|    `offer(Integer val)`   |        inserts `val` at the back; same as `offerLast`        |

#### Stack operations

```java
import java.util.ArrayDeque;
import java.util.Deque;

public class Main {
    static Deque<Integer> stack = new ArrayDeque<>();
    static int[] a = {1, 2, 3, 4, 5};
    
    public static void main(String[] args) {
        for (int v : a) {
            stack.push(v);
        }
        while (!stack.isEmpty()) { //prints 5 4 3 2 1
            System.out.println(stack.pop()); 
        }
    }
}

```

#### Double-ended queue operations

```java
import java.util.ArrayDeque;
import java.util.Deque;

public class Main {
    static Deque<Integer> deque = new ArrayDeque<>();
    
    static void insert() {
        deque.addFirst(1);
        deque.addFirst(2);
        deque.addLast(3);
        deque.addLast(4);
    }
    
    public static void main(String[] args) {
        insert();
        while (!deque.isEmpty()) { //prints 2 1 3 4
            System.out.println(deque.poll());
        }
        insert();
        while (!deque.isEmpty()) { //prints 4 3 1 2
            System.out.println(deque.pollLast());
        }
    }
}
```

### Set

`Set` is a data structure that keeps the elements in the container distinct.

#### HashSet

A `Set` whose elements are stored in no particular order.

##### Initialization

```java
Set<Integer> s1 = new HashSet<>();
```

#### LinkedHashSet

A `Set` that keeps insertion order.

##### Initialization

```java
Set<Integer> s2 = new LinkedHashSet<>();
```

#### TreeSet

A `Set` that keeps its elements sorted, in ascending order by default.

##### Initialization

```java
Set<Integer> s3 = new TreeSet<>();
Set<Integer> s4 = new TreeSet<>((x, y) -> {return y - x;});  // descending 
```

##### More on TreeSet

These methods are defined in `TreeSet` itself, so we cannot call them through the `Set` interface. Therefore we create the set like this:

```java
TreeSet<Integer> s3 = new TreeSet<>();
TreeSet<Integer> s4 = new TreeSet<>((x, y) -> {return y - x;});  // descending 
```

In the table below, `this` stands for the current `TreeSet<Integer>`.

|           Method          |                    Description                    |
| :--------------------: | :--------------------------------------: |
|        `first()`       |       returns the first element of `this`, or `null` if there is none       |
|        `last()`        |       returns the last element of `this`, or `null` if there is none      |
|  `floor(Integer val)`  | returns the first element of `this` less than or equal to `val`, or `null` if there is none |
| `ceiling(Integer val)` | returns the first element of `this` greater than or equal to `val`, or `null` if there is none |
|  `higher(Integer val)` |  returns the first element of `this` greater than `val`, or `null` if there is none  |
|  `lower(Integer val)`  |  returns the first element of `this` less than `val`, or `null` if there is none  |
|      `pollFirst()`     |      returns and removes the first element of `this`, or `null` if there is none     |
|      `pollLast()`      |     returns and removes the last element of `this`, or `null` if there is none     |

Code example:

```java
import java.util.TreeSet;

public class Main {
    static int[] a = {4,7,1,2,3,6};
    
    public static void main(String[] args) {
        TreeSet<Integer> set = new TreeSet<>();
        for(int v:a) {
            set.add(v);
        }
        Integer a2 = set.first();
        System.out.println(a2); //prints 1
        Integer a3 = set.last();
        System.out.println(a3); //prints 7
        Integer a4 = set.floor(5);
        System.out.println(a4); //prints 4
        Integer a5 = set.ceiling(6);
        System.out.println(a5); //prints 6
        Integer a6 = set.higher(7);
        System.out.println(a6); //prints null
        Integer a7 = set.lower(2);
        System.out.println(a7); //prints 1
        Integer a8 = set.pollFirst();
        System.out.println(a8); //prints 1
        Integer a9 = set.pollLast();
        System.out.println(a9); //prints 7
    }
}
```

#### Common Set methods

|            Method            |                   Description                   |
| :-----------------------: | :------------------------------------: |
|          `size()`         |                returns the size of the current set               |
|     `add(Integer val)`    |              inserts `val` into the set              |
|  `contains(Integer val)`  |            checks whether the set contains the element `val`            |
|   `addAll(Collection e)`  |          adds all elements of container `e` to the current set         |
| `retainAll(Collection e)` | removes the elements of the current set that do not appear in container `e`, i.e. takes the intersection of the current set and `e` |
| `removeAll(Collection e)` |  removes the elements of the current set that appear in container `e`, i.e. takes the difference of the current set and `e` |

```java
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Set<Integer> s1 = new HashSet<>();
    static Set<Integer> s2 = new LinkedHashSet<>();
    
    static void add() {
        s1.add(1);
    }
    
    static void contains() {  // checks whether the set contains the value 2; returns true if so, false otherwise 
        s1.contains(2);
    }
    
    static void test1() {  // union of s1 and s2 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.addAll(s2);
    }
    
    static void test2() {  // intersection of s1 and s2 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.retainAll(s2);
    }
    
    static void test3() {  // difference: s1 - s2 
        Set<Integer> res = new HashSet<>();
        res.addAll(s1);
        res.removeAll(s2);
    }
}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.HashSet;
import java.util.LinkedHashSet;
import java.util.Set;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    static Set<Integer> s1 = new HashSet<>();
    static Set<Integer> s2 = new LinkedHashSet<>();
    
    static void test() {
        for (int key : s1) {
            out.println(key);
        }
        out.close();
    }
}
```

### Map

`Map` is a data structure that stores key-value pairs `<Key, Value>`, where each `Key` is unique.

#### HashMap

A `Map` whose entries are stored in no particular order.

##### Initialization

```java
Map<Integer, Integer> map1 = new HashMap<>();
```

#### LinkedHashMap

A `Map` that keeps insertion order.

##### Initialization

```java
Map<Integer, Integer> map2 = new LinkedHashMap<>();
```

#### TreeMap

A `Map` that keeps its `key`s sorted, in ascending order by default.

##### Initialization

```java
Map<Integer, Integer> map3 = new TreeMap<>();
Map<Integer, Integer> map4 = new TreeMap<>((x, y) -> {return y - x;});  // descending
```

#### Common methods

Below, `this` stands for the current `Map<Integer, Integer>`:

|                Method                |               Description              |
| :-------------------------------: | :---------------------------: |
| `put(Integer key, Integer value)` |   inserts `<key, value>` into `this`  |
|              `size()`             |         returns the size of `this`         |
|     `containsKey(Integer key)`    | checks whether `this` has an element whose key is `key` |
|         `get(Integer key)`        |  returns the value of the element of `this` whose key is `key`  |
|             `keySet()`            |     returns the keys of all elements of `this` as a set    |

Usage examples:

```java
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;
import java.util.TreeMap;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    static Map<Integer, Integer> map1 = new HashMap<>();
    static Map<Integer, Integer> map2 = new LinkedHashMap<>();
    static Map<Integer, Integer> map3 = new TreeMap<>();
    static Map<Integer, Integer> map4 = new TreeMap<>((x,y)->{return y-x;});
    
    static void put(){  // put the element with key 1 and value 1
        map1.put(1, 1);
    }
    static void get(){  // return the value for key 1
        map1.get(1);
    }
    static void containsKey(){  // check whether there is a key-value pair with key 1
        map1.containsKey(1);
    }
    static void KeySet(){
        map1.keySet();
    }
}
```

#### Traversal

```java
import java.io.PrintWriter;
import java.util.HashMap;
import java.util.Map;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    static Map<Integer, Integer> map1 = new HashMap<>();
    
    static void print() {
        for (int key : map1.keySet()) {
            out.println(key + " " + map1.get(key));
        }
    }
}
```

Of course, the key and value types can be changed too. For example, a `Map` can also be defined as:

```java
Map<String, Set<Integer>> map = new HashMap<>();
```

## Arrays

`Arrays` is a utility class in `java.util` for working with arrays. All its methods are static and can be called directly through the class name.

### Arrays.sort()

`Arrays.sort()` sorts an array. Its main overloads are:

```java
import java.util.Arrays;
import java.util.Comparator;

public class Main {
    static int[] a = new int[10];
    static Integer[] b = new Integer[10];
    static int firstIdx, lastIdx;
    
    public static void main(String[] args) {
        Arrays.sort(a);  // 1 
        Arrays.sort(a, firstIdx, lastIdx);  // 2 
        Arrays.sort(b, new Comparator<Integer>() {  // 3 
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        Arrays.sort(b, firstIdx, lastIdx, new Comparator<Integer>() {  // 4 
            @Override
            public int compare(Integer o1, Integer o2) {
                return o2 - o1;
            }
        });
        // Since Java 8 has lambda expressions, the third and fourth overloads can also be written as 
        Arrays.sort(b, (x, y) -> {  // 5 
            return y - x;
        });
        Arrays.sort(b, (x, y) -> {  // 6 
            return y - x;
        });
    }
}
```

Meaning of each numbered overload:

1.  Sorts array `a`, in ascending order by default.
2.  Sorts the given part of array `a`, in ascending order by default. The range sorted is the half-open interval `[firstIdx, lastIdx)`.
3.  Sorts array `a` in a custom order. Second argument `-` first argument gives descending order; first argument `-` second argument gives ascending order. When you use a custom comparator, the element type of the array must be an object type.
4.  Sorts the given part of array `a` in a custom order. The range sorted is the half-open interval `[firstIdx, lastIdx)`. When you use a custom comparator, the element type of the array must be an object type.
5.  Same as 3, but shorter thanks to a lambda expression.
6.  Same as 4, but shorter thanks to a lambda expression.

???+ note "What `Arrays.sort()` uses underneath"
    1.  When the element type of the array passed to `Arrays.sort` is a primitive type (`byte`, `short`, `char`, `int`, `long`, `double`, `float`), it uses `DualPivotQuicksort` (dual-pivot quicksort) by default, which can take $O(n^2)$ time in the worst case.
    2.  When the element type is not a primitive type, it uses `legacyMergeSort` and `TimSort` (merge sort) by default, which take $O(n\log n)$ time.

You can verify this with the following code:

???+ example "[Codeforces 1646B - Quality vs Quantity](https://codeforces.com/problemset/problem/1646/B)"
    There are $n$ integers. You need to split them into two groups. Is it possible for one group to have fewer elements than the other but a larger sum?

??? note "Example code"
    ```java
    import java.io.BufferedReader;
    import java.io.IOException;
    import java.io.InputStreamReader;
    import java.io.PrintWriter;
    import java.util.Arrays;
    import java.util.StringTokenizer;
    
    public class Main {
        static class FastReader {
            StringTokenizer st;
            BufferedReader br;
            
            public FastReader() {
                br = new BufferedReader(new InputStreamReader(System.in));
            }
            
            String next() {
                while (st == null || !st.hasMoreElements()) {
                    try {
                        st = new StringTokenizer(br.readLine());
                    } catch (IOException e) {
                        e.printStackTrace();
                    }
                }
                return st.nextToken();
            }
            
            int nextInt() {
                return Integer.parseInt(next());
            }
            
            long nextLong() {
                return Long.parseLong(next());
            }
            
            double nextDouble() {
                return Double.parseDouble(next());
            }
            
            String nextLine() {
                String str = "";
                try {
                    str = br.readLine();
                } catch (IOException e) {
                    e.printStackTrace();
                }
                return str;
            }
        }
        
        static PrintWriter out = new PrintWriter(System.out);
        static FastReader in = new FastReader();
        
        static void solve() {
            int n = in.nextInt();
            // changing the array type here from Integer to int leads to TLE
            Integer[] a = new Integer[n + 10];
            for (int i = 1; i <= n; i++) {
                a[i] = in.nextInt();
            }
            Arrays.sort(a, 1, n + 1);
            long left = a[1];
            long right = 0;
            int x = n;
            for (int i = 2; i < x; i++, x--) {
                left = left + a[i];
                right = right + a[x];
                if (right > left) {
                    out.println("YES");
                    return;
                }
            }
            out.println("NO");
        }
        
        public static void main(String[] args) {
            int t = in.nextInt();
            while (t-- > 0) {
                solve();
            }
            out.close();
        }
    }
    ```

### Arrays.binarySearch()

`Arrays.binarySearch()` does a binary search over a contiguous range of an array. The array must be sorted. The time complexity is $O(\log_n)$. Its main overloads are:

```java
import java.util.Arrays;

public class Main {
    static int[] a = new int[10];
    static Integer[] b = new Integer[10];
    static int firstIdx, lastIdx;
    static int key;
    
    public static void main(String[] args) {
        Arrays.binarySearch(a, key);  // 1 
        Arrays.binarySearch(a, firstIdx, lastIdx, key);  // 2 
    }
}
```

The source code is:

```java
private static int binarySearch0(int[] a, int fromIndex, int toIndex, int key) {
    int low = fromIndex;
    int high = toIndex - 1;
    
    while (low <= high) {
        int mid = (low + high) >>> 1;
        int midVal = a[mid];
        
        if (midVal < key)
            low = mid + 1;
        else if (midVal > key)
            high = mid - 1;
        else
            return mid; // key found
    }
    return -(low + 1);  // key not found.
}
```

Meaning of each numbered overload:

1.  Binary searches array a for `key`. If it exists, returns its index. If not, returns a negative number.
2.  Binary searches array a for `key` within the half-open range `[firstIdx,lastIdx)`. If it exists, returns its index. If not, returns a negative number.

### Arrays.fill()

`Arrays.fill()` sets the elements in a contiguous part of an array to the same value. It takes the array, `fromIndex`, `toIndex` and the value to fill with. After it runs, every element in the half-open range `[firstIdx,lastIdx)` of the array equals the fill value.

## Collections

`Collections` is a utility class in `java.util` for working with collections. All its methods are static and can be called directly through the class name.

### Collections.sort()

`Collections.sort()` works by copying all elements into an array, calling `Arrays.sort()` on it, and then writing the sorted elements back into the original collection. Since the elements of a Java `Collection` are always objects, it always uses merge sort.

This method cannot sort only a given range of the collection.

The source code underneath:

```java
default void sort(Comparator<? super E> c) {
    Object[] a = this.toArray();
    Arrays.sort(a, (Comparator) c);
    ListIterator<E> i = this.listIterator();
    for (Object e : a) {
        i.next();
        i.set((E) e);
    }
}
```

### Collections.binarySearch()

`Collections.binarySearch()` does a binary search over a given range of a collection. It works the same as `Arrays.binarySearch()`.

```java
Collections.binarySearch(list, key);
```

This method cannot search only a given range.

### Collections.swap()

`Collections.swap()` swaps the elements at two given positions of a collection.

```java
 Collections.swap(list, i, j);
```

## Miscellaneous

### Comparing numeric values

In Java, for plain numeric (primitive) types, `-0.0 = 0.0`. For object types, however, `-0.0 != 0.0`. This causes trouble if you try to count distinct slopes with a `Set`. One fix is to add `0.0` to every slope before putting it into the `Set`.

```java
import java.io.PrintWriter;

public class Main {
    static PrintWriter out = new PrintWriter(System.out);
    
    static void A() {
        Double a = 0.0;
        Double b = -0.0;
        out.println(a.equals(b));  // false 
    }
    
    static void B() {
        Double a = 0.0;
        Double b = -0.0 + 0.0;
        out.println(a.equals(b));  // true 
    }
    
    static void C() {
        double a = 0.0;
        double b = -0.0;
        out.println(a == b);  // true 
    }
    
    
    public static void main(String[] args) {
        A();
        B();
        C();
        out.close();
    }
}
```

## References

[^ref1]: [Input & Output - USACO Guide](https://usaco.guide/general/input-output?lang=java#method-3---io-template)
