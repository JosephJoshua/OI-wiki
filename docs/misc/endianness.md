This page gives a short introduction to the concept and types of byte order (endianness).

## Introduction

Byte order is the rule for storing program objects that span multiple bytes. It describes how the bytes of an object are arranged.

## Types

There are two byte orders: little endian and big endian.

To make the explanation easier, we use as an example a variable of type `int` located at `0x100` whose hexadecimal value is `0x01234567`. Here `0x01` is the most significant byte and `0x67` is the least significant byte.

### Little endian

Little endian means the machine stores an object in memory in order from the **least** significant byte to the **most** significant byte.

The variable mentioned above is stored like this:

| .... | 0x100 | 0x101 | 0x102 | 0x103 | .... |
| ---- | ----- | ----- | ----- | ----- | ---- |
| .... | 67    | 45    | 23    | 01    | .... |

### Big endian

Big endian means the machine stores an object in memory in order from the **most** significant byte to the **least** significant byte.

The variable mentioned above is stored like this:

| .... | 0x100 | 0x101 | 0x102 | 0x103 | .... |
| ---- | ----- | ----- | ----- | ----- | ---- |
| .... | 01    | 23    | 45    | 67    | .... |

### Differences between the two orders

In fact, neither byte order is better than the other. The names "little endian" and "big endian" come from the book *Gulliver's Travels*. In the book, two factions in Lilliput fight an endless war because they cannot agree whether to crack an egg from the little end or the big end. Just like the egg argument, the argument over which byte order to choose is not a technical one.

Of course, different byte orders cause binary data to be reversed when it is sent between different kinds of machines. To avoid this, network applications set up a standard: during transmission, data uses the agreed network byte order instead of each machine's internal representation.

## Which machines use which order

-   Little endian: x86, ARM processors running Android, iOS, and Windows

-   Big endian: Sun, PPC Mac, Internet
