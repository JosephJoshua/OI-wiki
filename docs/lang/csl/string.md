author: johnvp22, Ir1d

## What `string` is

`std::string` is a class provided by the standard library header `<string>` (not the C library `<string.h>`). It is really an alias for `std::basic_string<char>`.

## Why use `string`

C does provide string operations, but strings can only be stored as character arrays. `string`, on the other hand, is a simple class that is easy to use, and it is widely used in OI. Compared with other STL containers, `string` also has a very good constant factor, about the same as a character array.

### `string` allocates memory dynamically

Like many STL containers, `string` allocates memory dynamically. This lets us read it directly with `std::cin`, though that is also fairly slow. It also means we do not have to worry about memory.

### `string` overloads the addition and comparison operators

The addition operator of `string` joins two strings, or a string and a character, directly. Like `std::vector`, `string` overloads the comparison operators, which also compare in lexicographic order, so we can call `std::sort` directly to sort a number of strings.

## Usage

Below are the basic operations of `string`. See the [C++ documentation](https://zh.cppreference.com/w/cpp/string/basic_string) for details.

### Declaration

```cpp
std::string s;
```

### Converting to a char array

C also has many string functions, but their parameters are all char pointers. For convenience, `string` has two member functions that convert it to a char pointer: `data()`/`c_str()` (before C++11, `c_str()` was guaranteed to end with a null character and `data()` was not; since C++11 they behave the same[^string1]). For example:

```cpp
printf("%s", s);          // not guaranteed to compile; undefined behavior
printf("%s", s.data());   // undefined before C++11; prints correctly since C++11
printf("%s", s.c_str());  // always prints correctly
```

### Getting the length

Several functions return the length of a string:

```cpp
printf("length of s is %zu", s.size());
printf("length of s is %zu", s.length());
printf("length of s is %zu", strlen(s.c_str()));
```

???+ note "Complexity of these functions"
    The complexity of `strlen()` is always linear in the length of the string.
    
    The complexity of `size()` and `length()` was not specified in C++98; C++11 specifies it as constant. But on common compilers these two functions take constant time even under C++98.

???+ warning "Warning"
    The return type of these three functions (and of the `find` function below) is `size_t` (`unsigned long`). So you should not compare these return values directly with negative numbers or do arithmetic with negative numbers. Cast them when needed.

### Finding the first occurrence of a character (or string)

`find(str,pos)` finds the first position at or after `pos` where a character/string occurs in the string (if `pos` is not given, it defaults to `0`). If there is no occurrence, it returns `string::npos` (defined as `-1`, but its type is still `size_t`/`unsigned long`).

Example:

```cpp
string s = "OI Wiki", t = "OI", u = "i";
int pos = 5;
printf("character I first occurs in s at position %lu\n", s.find('I'));
printf("character a first occurs in s at position %lu\n", s.find('a'));
printf("character a first occurs in s at position %d\n", s.find('a'));
printf("string t first occurs in s at position %lu\n", s.find(t));
printf("starting from pos, string u first occurs in s at position %lu", s.find(u, pos));
```

Output:

```text
character I first occurs in s at position 1
character a first occurs in s at position 18446744073709551615 // this is size_t(-1); the exact value depends on the platform.
character a first occurs in s at position -1 // cast to int, it prints -1 as expected
string t first occurs in s at position 0
starting from pos, string u first occurs in s at position 6
```

### Taking a substring

`substr(pos, len)` returns the string made of at most `len` characters starting at position `pos` (if the suffix starting at `pos` is shorter than `len`, it returns that suffix).

Example:

```cpp
string s = "OI Wiki", t = "OI";
printf("the substring of at most three characters starting at the 4th character of s is %s\n",
       s.substr(3, 3).c_str());
printf("the substring of at most three characters starting at the 2nd character of t is %s",
       t.substr(1, 3).c_str());
```

Output:

```text
the substring of at most three characters starting at the 4th character of s is Wik
the substring of at most three characters starting at the 2nd character of t is I
```

### Inserting/erasing characters (or strings)

`insert(index,count,ch)` and `insert(index,str)` are the common insertion functions. The first inserts the character `ch` `count` times in a row at `index`; the second inserts the string `str` at `index`.

`erase(index,count)` deletes `count` characters starting at (and including) position `index` (if `count` is not given, it deletes every character from position `index` onward).

Example:

```cpp
string s = "OI Wiki", t = " Wiki";
char u = '!';
s.erase(2);
printf("after deleting everything from the 3rd character of s, the string is %s\n", s.c_str());
s.insert(2, t);
printf("after inserting string t at the 3rd character of s, the string is %s\n", s.c_str());
s.insert(7, 3, u);
printf("after inserting string u 3 times in a row at the 8th character of s, the string is %s",
       s.c_str());
```

Output:

```text
after deleting everything from the 3rd character of s, the string is OI
after inserting string t at the 3rd character of s, the string is OI Wiki
after inserting string u 3 times in a row at the 8th character of s, the string is OI Wiki!!!
```

### Replacing characters (or strings)

`replace(pos,count,str)` and `replace(first,last,str)` are the common replacement functions. The first replaces the substring of `count` characters starting at `pos` with `str`. The second replaces the substring that starts at `first` (inclusive) and ends at `last` (exclusive) with `str`, where `first` and `last` are both iterators.

Example:

```cpp
string s = "OI Wiki";
s.replace(2, 5, "");
printf("after replacing characters 3 to 7 of s with an empty string, the string is %s\n", s.c_str());
s.replace(s.begin(), s.begin() + 2, "NOI");
printf("after replacing the first two characters of s with NOI, the string is %s", s.c_str());
```

Output:

```text
after replacing characters 3 to 7 of s with an empty string, the string is OI
after replacing the first two characters of s with NOI, the string is NOI
```

## References and notes

[^string1]: [C++ standard draft \[basic.string\]](https://eel.is/c++draft/basic.string#general-3)
