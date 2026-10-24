author: cmpute, Henry-ZHR, ranwen, abc1763613206, billchenchina, chinggg, ChungZH, CoelacanthusHex, countercurrent-time, Dong Tsing-hsuen, Early0v0, Enter-tainer, F1shAndCat, Great-designer, hensier, HeRaNO, Hszzzx, imba-tjd, Ir1d, ksyx, lingxier, LovelyBuggies, Marcythm, mgt, Mooos-MoSheng, NachtgeistW, ouuan, Rottenwooood, shawlleyw, shuzhouliu, sshwy, SukkaW, Suyun514, Tiphereth-A, tLLWtG, wineee, wxh06, Xeonacid, yusancky, zyouxam, zzjjbb, jiangmuran, CuriosityQiu

## About Python

Python is an interpreted language used widely around the world. It provides efficient high-level data structures, supports simple and effective object-oriented programming, and can also be used in competitive programming.

### Strengths of Python

-   Python is an **interpreted** language: it does not need compiling or linking, which saves some steps.
-   Python is an **interactive** language: the Python interpreter supports interactive use, so you can type and run commands directly in a terminal.
-   Python is **easy to learn and use**: it provides many data structures and also supports developing large programs.
-   Python is **highly compatible**: it supports Windows, macOS and Unix.
-   Python is **very practical**: from simple input/output to scientific computing and even large web applications, you can write suitable Python programs.
-   Python **programs are short and readable**: Python code is usually shorter than code in other languages that does the same thing.
-   Python **is extensible**: Python can work with C programs (that is, CPython); you can link the Python interpreter with applications written in C, and use Python to extend and control those applications.

### Things to keep in mind when learning Python

-   The Python versions mainly in use today are Python 3.7 and later. Python 2, and Python 3.6 and earlier, are [no longer supported](https://devguide.python.org/versions/#unsupported-versions), but are still used by some old systems and code. This article **covers the newer versions of Python**. If you run into Python 2 code, you can try the [`2to3`](https://docs.python.org/zh-cn/3/library/2to3.html) tool to convert it to Python 3 code.
-   Python's design philosophy and syntax are **quite different from some other languages**. It hides many low-level details, which gives it a practical and elegant style.
-   Python is a highly dynamic interpreted language, so **its programs run relatively slowly**, especially when you use its built-in `for` loop. When using Python, try to use built-in functions like `filter` and `map`, or [list comprehension](https://www.pythonforbeginners.com/basics/list-comprehensions-in-python) syntax, to improve performance.

## Setting up the environment

See [Python 3](../tools/compiler.md#python-3). Alternatively:

-   Windows: you can also get Python quickly and for free from the Microsoft Store.

-   macOS/Linux: most Linux distributions already come with Python. If you only want to learn Python syntax and have no other development needs, you don't need to install Python separately.

    ???+ warning "Note"
        On some systems where Python is installed by default (that is, through a package manager), such as Unix systems, you should run `python3` in the terminal to open the Python 3 interpreter.[^ref1]

You can also use tools such as venv, conda and Nix to manage Python toolchains and packages, creating isolated virtual environments to avoid dependency problems.

As an interpreted language, Python runs programs differently from C++. This difference is often hidden when you program in an IDE, so we want to point out the different ways to run a program here.

When you type `python3` on the command line or have just opened IDLE, you are actually in an interactive programming environment, also called a "REPL" ("read-eval-print loop"). Beginners can type statements here and see the results immediately, which makes it very easy to check syntax. We will use this form a lot later in this article.

But to write a complete program, you'd better create a new text file (usually with the extension `.py`) and then run `python3 filename.py` on the command line to run the code and see the result.

### Python versions on some platforms

| System/version          | Python version            |
| ----------------------- | ------------------------- |
| Noi Linux 2.0           | 3.8.0, Include requests   |
| Luogu judge             | 3.11.5, NumPy 1.25.2      |
| Hydro-based OJs         | 3.8.0+ Include NumPy      |
| Ubuntu 22.04 (built-in) | 3.10.4                    |
| Microsoft Store         | latest stable release     |

???+ warning "Note"
    This table was accurate when this article was written (2025/01/15). We recommend checking again on the relevant platforms.

In China, the main mirrors of Python **source code** are the [Beijing Jiaotong University Free and Open Source Software Mirror](https://mirror.bjtu.edu.cn/python/) and the [Huawei Open Source Mirror](https://repo.huaweicloud.com/python/). You can try downloading Python installers there.

## Installing third-party libraries with `pip`

Much of Python's vitality comes from its rich third-party libraries. When writing practical programs, "calling a library" is routine, and `pip` is the preferred tool for installing third-party libraries. Since Python 3.4, it has been included in the Python binary installers by default.

Third-party libraries for `pip` are mainly hosted on the [Python Package Index (PyPI)](https://pypi.org/), and you can also specify other hosting platforms. For how to use them, see guides such as [PyPI mirror help - Tsinghua University Open Source Software Mirror](https://mirrors.tuna.tsinghua.edu.cn/help/pypi/). You can find more PyPI mirrors on [MirrorZ](https://mirrorz.org/list/pypi).

???+ info "Installing a package from the Tsinghua University open source mirror"
    ```sh
    pip install -i https://mirrors.tuna.tsinghua.edu.cn/pypi/web/simple <some-package>
    ```

## Basic syntax

Python's syntax is concise and easy to understand, and there are many official and third-party documents and tutorials. Here we only introduce some language features that are useful for OIers. You can learn more from tutorials such as the [Python documentation](https://docs.python.org/zh-cn/3/) and the [Python Wiki](https://wiki.python.org/moin/).

### Comments

Comments do not affect how code runs, but they make code easier to understand and use.

```python
# A line starting with the # character is a single-line comment

"""
A string spanning multiple lines is wrapped in
triple quotes (three single quotes or three double quotes),
and is also often used as a comment
"""
```

Adding comments does not affect the code. We encourage you to add comments to make your code easier to understand and use.

### Basic data types

#### Everything is an object

In Python, you don't need to declare variable names or types in advance. You create variables of any type just by assigning to them:

```pycon
>>> x = -3  # no semicolon needed at the end of a statement
>>> x
-3
>>> f = 3.1415926535897932384626; f  # you can still add a semicolon if you really want; here it saves a line
3.141592653589793
>>> s1 = "O"
>>> s1  # in Python, double quotes and single quotes do the same thing
'O'
>>> b = 'A' == 65  # 'A' and 65 are different data types, so they are not equal
>>> b  # True and False are both capitalized
False
>>> True + 1 == 2 and not False != 0  # Python expressions mostly use words, but symbols are supported too
True
```

This doesn't mean Python has no concept of types. In fact, the interpreter infers variable types automatically from assignments and operations. You can use the built-in function `type()` to see the types of these variables:

```pycon
>>> type(x)
<class 'int'>
>>> type(f)
<class 'float'>
>>> type(s1)  # note: don't name a string str, or the str object gets overwritten
<class 'str'>
>>> type(b)
<class 'bool'>
```

???+ note "What are [**built-in functions**](https://docs.python.org/zh-cn/3/library/functions.html)?"
    In C/C++, many common functions are spread across different header files. The Python interpreter, however, has many useful general-purpose functions built in, and you can use them directly without even noticing they exist. This brings a small problem: these built-in functions mostly have common English words as names, so you need to avoid giving your own variables the same names, or you may get strange results.

As we can see, Python has built-in integer, floating-point, string and boolean types, similar to `int`, `float`, `string` and `bool` in C++. But there are some clear differences. For example, there is no `char` character type and no `double` type (but `float` actually corresponds to double precision in C). If you need more precise floating-point arithmetic, you can use the [decimal](https://docs.python.org/zh-cn/3/library/decimal.html) module from the standard library. If you need complex numbers, Python also has a built-in `complex` type (which also means you'd better not name a variable `complex`).
You can see that all these types start with `class`, and this is the key way Python differs from C++. All data in a Python program is represented by objects or relations between objects. Functions are objects, and types themselves are objects too:

```pycon
>>> type(int)
<class 'type'>
>>> type(pow)  # built-in function for powers, introduced later
<class 'builtin_function_or_method'>
>>> type(type)  # type() is also a built-in function, but a bit special; look it up if you're curious
<class 'type'>
```

You may find these ideas hard to grasp and not very useful at first, so we won't go deeper for now. You may slowly get a feel for them in the examples later. Python objects provide powerful methods. When programming, we should prefer to work around objects rather than procedures, which makes our code more compact and clear.

#### Arithmetic

Some people say you can use the Python installed on your system as a versatile calculator, and that's true.  
In interactive mode, you can type an expression after the `>>>` prompt. Just like most other languages (such as C++), you can use the operators `+`, `-`, `*`, `/` and `%` on numbers, and use `()` for grouping. Try it yourself; here we only show the parts that differ a lot from C++:

```pycon
>>> 5.0 * 6  # arithmetic on floats gives a float
30.0
>>> 15 / 3  # unlike C/C++, division always returns a float
5.0
>>> 5 / 100000  # too many digits, so the result is shown in scientific notation
5e-05
>>> 5 // 3 # integer division (floor division) rounds down and gives an integer
1
>>> -5 // 3 # follows rounding down; note this differs from C/C++
-2
>>> 5 % 3 # modulo
2
>>> -5 % 3 # the result of modulo with a negative number is always non-negative, which also differs from C/C++, but both satisfy (a//b)*b+(a%b)==a 
1
>>> x = abs(-1e4)  # built-in function for absolute value
>>> x += 1  # there are no increment/decrement operators
>>> x  # scientific notation gives a float by default
10001.0
```

From the examples above, you can see that division (`/`) always returns a float (in Python 2 it returns an integer). If you want an integer or rounded-down result, use integer division (`//`). As in C++, you can use modulo (`%`) to compute remainders, and scientific notation looks the same.

In particular, Python uses `**` for powers, and the built-in `pow(a, b, mod)` provides an efficient implementation of [fast exponentiation](../math/binary-exponentiation.md).

```pycon
>>> 3 ** 4 # power
81
>>> 2 ** 512
13407807929942597099574024998205846127479365820592393377723561443721764030073546976801874298166903427690031858186486050853753882811946569946433649006084096
>>> pow(2, 512, int(1e4)) # a fast way to compute 2**512 % 10000; 1e4 is a float, so convert it to int
4096
>>> 2048 ** 2048 # try big integers in IDLE?
>>> 0.1 + 0.1 + 0.1 - 0.3 == 0.  # as in C/C++, don't compare floats for equality directly
False
```

#### Checking data types

For a variable, `type(object)` returns its type. For example, `type(8)` and `type('a')` are `<class 'int'>` and `<class 'str'>`.

#### [Basic input and output](https://docs.python.org/zh-cn/3/tutorial/inputoutput.html)

Input and output in Python are mainly done with the built-in functions `input()` and `print()`. `print()` works very intuitively:

```pycon
>>> a = [1,2,3]; print(a[-1])  # prints a newline at the end by default
3
>>> print(ans[0], ans[1])  # can print any number of variables, separated by spaces by default
1 2
>>> print(a[0], a[1], end='')  # set end='' so there is no newline at the end
1 2>>>
>>> print(a[0], a[1], sep=', ')  # set sep=', ' to change the separator
1, 2
>>> print(str(a[0]) + ', ' + str(a[1]))  # same output as above, but joined by hand into one string
```

The `input()` function behaves like `getline()` in C++: it reads a whole line as a string, without the newline at the end.

```pycon
>>> s = input('Enter some numbers: '); s  # when debugging, you can pass a string to input() as a prompt
Enter some numbers: 1 2 3 4 5 6
'1 2 3 4 5 6'
```

#### Strings

Python 3 provides a powerful string type based on [Unicode](https://docs.python.org/zh-cn/3/howto/unicode.html#unicode-howto). It works much like `string` in C++, and ideas such as escape characters are the same. Besides `+` for concatenation and indexing, it also supports `*` with a number to repeat a string, and the `in` operator.

```pycon
>>> s1 = "O"  # both single and double quotes can wrap strings, which sometimes saves escape characters
>>> s1 += 'I-Wiki'  # double quotes are recommended, to match C++ 
>>> 'OI' in s1  # checking for a substring is easy
True
>>> len(s1)  # like s.length() in C++, but more general
7
>>> s2 = """ Thanks for reading
... Please contribute!
"""   # strings in triple quotes can span multiple lines
>>> s1 + s2 
'OI-Wiki Thanks for reading\nPlease contribute!'
>>> print(s1 + s2)  # here we use the print() function to print the string
OI-Wiki Thanks for reading
Please contribute!
>>> s2[2] * 2 + s2[3] + s2[-1]  # negative indices count from the right; adding len(s) gives the same index, like residues mod n
'hha!'
>>> s1[0] = 'o'  # str is immutable and cannot be modified in place; in fact += also creates a new object
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
TypeError: 'str' object does not support item assignment
```

Python supports several compound data types that group values together. The most common is `list`, written as comma-separated values in square brackets. For example, `[1, 2, 3]` and `['a','b','c']` are both lists.

Besides indexing, strings also support *slicing*, which is very cleverly designed. The format is `s[inclusive start:exclusive end:step]`:

```pycon
>>> s = 'OI-Wiki Thanks for reading\nPlease contribute!'
>>> s[:8]  # if the start is omitted, start from the beginning
'OI-Wiki '
>>> s[8:14]  # the beauty of half-open ranges: the length is 14-8=6, and it joins seamlessly with the previous slice
'Thanks'
>>> s[-4:]  # if the end is omitted, go to the end
'ute!'
>>> s[8:14:2]  # step of 2
'Tak'
>>> s[::-1]  # with step -1, you get the reversed string
'!etubirtnoc esaelP\ngnidaer rof sknahT ikiW-IO'
>>> s  # but the original string is unchanged
'OI-Wiki Thanks for reading\nPlease contribute!'
```

In recent Python 3 versions, strings are Unicode, which means Python strings support many languages.[^ref2] In Python, you can use the built-in function `ord()` to convert a Unicode character to its Unicode code point, and the built-in function `chr()` for the reverse. In C/C++, the `char` type can also be converted to and from its ASCII code.

To convert a number to a string, use the built-in function `str()`; for the reverse, use `int()` and `float()`. You can compare this to type casts in C/C++, except that the parentheses go around the argument as part of a function call rather than around the type.

Python's string type has many powerful methods, including finding the index and count of a character, changing case, and so on. We won't list them all here. We strongly recommend reading the [official documentation](https://docs.python.org/zh-cn/3/library/stdtypes.html#text-sequence-type-str) to get familiar with the common methods. When you need to manipulate strings, consider these methods first instead of doing it all yourself.

### Creating arrays

Students coming from C++ may be confused about how to create arrays in Python. Here we introduce the syntax for making "arrays" in Python. Note that what we introduce are really several [sequence types](https://docs.python.org/zh-cn/3/library/stdtypes.html#iterator-types). They are fundamentally different from C arrays and closer to `vector` in C++.

#### Using `list`

A list (`list`) is probably the most commonly used and most powerful sequence type in Python. A list can hold elements of any type, including nested lists, which fits the definition of a "generalized list" in data structures. Be careful not to confuse it with the doubly linked list [`list`](./csl/sequence-container.md#list) in the C++ STL; that is why this article says "list" rather than `list`, to avoid misunderstanding.

```pycon
>>> []  # create an empty list; note that lists use square brackets
[]
>>> nums = [0, 1, 2, 3, 5, 8, 13]; nums  # initialize a list; note the whole list can be printed directly
[0, 1, 2, 3, 5, 8, 13]
>>> nums[0] = 1; nums  # supports index access and modifying elements
[1, 1, 2, 3, 5, 8, 13]
>>> nums.append(nums[-2]+nums[-1]); nums  # append() is like vector's push_back(), and neither returns a value
[1, 1, 2, 3, 5, 8, 13, 21]
>>> nums.pop()  # pops and returns the last element, so it can be used as a stack; you can also give a position, the default is the end
21
>>> nums.insert(0, 1); nums  # like vector's insert(position, val)
[1, 1, 1, 2, 3, 5, 8, 13]
>>> nums.remove(1); nums  # removes an element by value (only the first occurrence); raises an error if it doesn't exist
[1, 1, 2, 3, 5, 8, 13]
>>> len(nums)  # length of the list, like vector's size(), but len() is a built-in function
7
>>> nums.reverse(); nums  # reverses in place
[13, 8, 5, 3, 2, 1, 1]
>>> sorted(nums)  # get a sorted list
[1, 1, 2, 3, 5, 8, 13]
>>> nums  # but the original list is not sorted
[13, 8, 5, 3, 2, 1, 1]
>>> nums.sort(); nums  # sorts in place; you can pass the parameter key as the sort criterion
[1, 1, 2, 3, 5, 8, 13]
>>> nums.count(1)  # like std::count()
2
>>> nums.index(1)  # returns the index of the first occurrence of the value; raises an error if it doesn't exist
0
>>> nums.clear(); nums  # like vector's clear()
```

The examples above show how lists resemble `vector`. Operations commonly used on `vector` usually have matching list methods. However, some, like `len()` and `sorted()`, appear as built-in functions, while STL algorithm functions such as `find()`, `count()`, `max_element()`, `sort()` and `reverse()` become object methods in Python, so be careful to tell them apart. For more methods, see [More on Lists](https://docs.python.org/zh-cn/3/tutorial/datastructures.html#more-on-lists) in the official documentation. Below we show some powerful features of lists as Python's basic sequence type:

Python supports several compound data types that group values together. The most common is `list`, written as comma-separated values in square brackets. For example, `[1, 2, 3]` and `['a','b','c']` are both lists.

```pycon
>>> lst = [1, '1'] + ["2", 3.0]  # adding lists directly creates a new list
>>> lst  # storing different types here only shows that it's possible; it's not good practice
[1, '1', '2', 3.0]
>>> 3 in lst  # a handy membership test; strings have it too, and also support substring tests
True
>>> [1, '1'] in lst  # only tests for a single member; it won't find a "subsequence"
False
>>> lst[1:3] = [2, 3]; lst  # slice assignment; the original list is modified
[1, 2, 3, 3.0]
>>> lst[::-1]  # get a new reversed list
[3.0, 3, 2, 1]
>>> lst *= 2; lst  # repeat by multiplying with a number
[1, 2, 3, 3.0, 1, 2, 3, 3.0]
>>> del lst[4:]; lst  # can also write lst[4:] = []; the del statement can do more than delete sequence elements
[1, 2, 3, 3.0]
```

The examples above show some common operations on lists as sequences. Many operations, such as slicing, work the same as on strings. But strings are "immutable sequences" while lists are "mutable sequences", so you can modify lists flexibly with slices. In C/C++ we often process character arrays with loops. Below we show how to use ["list comprehensions"](https://docs.python.org/3/tutorial/datastructures.html#list-comprehensions) to convert between strings and lists:

```pycon
>>> # create an integer array over [65, 70); range is also a type, think of it as a half-open range; the optional third argument is the step
>>> nums = list(range(65,70))  # remember to wrap range in list()
[65, 66, 67, 68, 69]
>>> lst = [chr(x) for x in nums]  # the typical structure of a list comprehension: [exp for var in iterable if cond]
>>> lst  # the two lines above can be merged into [chr(x) for x in range(65,70)]
['A', 'B', 'C', 'D', 'E']
>>> s = ''.join(lst); s # join the list's elements with the empty string '' to make a new string
'ABCDE'
>> list(s)  # make a list of characters from a string
['A', 'B', 'C', 'D', 'E']
>>> # if you didn't know about s.lower(), you might write an old-wine-in-new-bottles expression like this
>>> ''.join([chr(ord(ch) - 65 + 97) for ch in s if ch >= 'A' and ch <= 'Z'])  
'abcde'
```

Below are some scenarios that are more common in OI, such as two-dimensional "arrays":

```pycon
>>> vis = [[0] * 3] * 3  # make a 3*3 array of all zeros
>>> vis 
[[0, 0, 0], [0, 0, 0], [0, 0, 0]]
>>> vis[0][0] = 1; vis  # why were the other rows modified too?
[[1, 0, 0], [1, 0, 0], [1, 0, 0]]
>>> # first, look at assigning a 1D list
>>> a1 = [0, 0, 0]; a2 = a1; a3 = a1[:]  # a list can also be assigned directly to a new variable
>>> a1[0] = 1; a1  # modify list a1; looks normal
[1, 0, 0]
>>> a2  # why did a2 change too?
[1, 0, 0]
>>> a3  # a3 did not change
[0, 0, 0]
>>> id(a1) == id(a2) and id(a1) != id(a3)  # the built-in id() gives an object's "identity", similar to an address; the same address means the same object
True
>>> vis2 = vis[:]  # copy the 2D list
>>> vis[0][1] = 2; vis  # vis is modified in bulk
>>> [[1, 2, 0], [1, 2, 0], [1, 2, 0]]
>>> vis2  # vis2 is a slice copy, but it was still changed
>>> [[1, 2, 0], [1, 2, 0], [1, 2, 0]]
>>> id(vis) != id(vis2)  # vis and vis2 are not the same object
True
>>> # vis2 is not a reference to vis, but its rows point to the same objects
>>> [id(vis[i]) == id(vis2[i]) for i in range(3)]
[True, True, True]
>>> # look back at the 2D list itself
>>> [id(x) for x in vis]  # the actual numbers will differ from these, but the three values are always equal, meaning it's the same object three times
[139760373248192, 139760373248192, 139760373248192]
```

Here is an important fact: assignment in Python only passes a reference; it does not create a new value. You can create variables of different types, assign them to new variables, and check that both have the same identity. It's just that so far we have only introduced one mutable type, the list. When you assign a new value to an immutable type such as a number or string, a new object is actually created, so the two variables don't affect each other. But lists are mutable, so when we modify an element of one list, the other list is modified too, because both point to the same object. Creating 2D arrays is similar: in the example, creating a 2D list with multiplication repeats the 1D list `[0]*3` three times, so an operation on one of these lists affects the other two as well. Worse still, when you assign a 2D list to another variable, even copying with a slice only makes a "shallow copy": its elements still point to the same objects. To fix this, use [`deepcopy`](https://docs.python.org/3/library/copy.html) from the standard library, or avoid assigning whole 2D lists. Fortunately, it's fairly easy to avoid creating repeated lists when creating a 2D list; just use a "list comprehension":

```pycon
>>> vis1 = [[0] * 3 for _ in range(3)]  # it's a convention to name an unused loop counter with an underscore _
>>> # but in the REPL, _ refers to the result of the previous expression by default, so you can also use a double underscore
>>> vis1
[[0, 0, 0], [0, 0, 0], [0, 0, 0]]
>>> [id(x) for x in vis1]  # the actual numbers will differ from these, but the three values are always different, meaning three different objects
[139685508981248, 139685508981568, 139685508981184]
>>> vis1[0][0] = 1
[[1, 0, 0], [0, 0, 0], [0, 0, 0]]
>>> a2[0][0] = 10  # access and assign in a 2D array
```

We introduced list comprehensions before explaining loops because Python is a highly dynamic interpreted language, so its programs have a lot of extra overhead. In particular, **for loops in Python are extremely slow**. So if you want good performance in Python, use list comprehensions as much as possible, or built-in functions such as `filter` and `map` that work on a whole sequence directly to avoid loops. Of course, this still depends on the specific problem.

#### Using NumPy

??? note "What is NumPy"
    [NumPy](https://numpy.org/) is a well-known Python library for scientific computing that provides high-performance numerical and matrix operations. When testing algorithm prototypes, you can use NumPy to avoid hand-writing sorting, finding maximums and so on. NumPy's core data structure is `ndarray`, an n-dimensional array that is stored contiguously in memory and has a fixed length. Also, NumPy's core is written in C, so it is very efficient. Note, however, that it is not part of the standard library. You can install it with `pip install numpy`, but it is not guaranteed to be available in OI contest environments (see [Python versions](#python-versions-on-some-platforms) at the beginning of this article).

The code below shows how to use NumPy to create and access multi-dimensional arrays.

```pycon
>>> import numpy as np  # look up what import means and how to use it yourself
>>> np.empty(3) # make an empty array of size 3; note it is not initialized to 0
array([0.00000000e+000, 0.00000000e+000, 2.01191014e+180])
>>> np.zeros((3, 3)) # make a 3*3 array initialized to 0
array([[0., 0., 0.],
       [0., 0., 0.],
       [0., 0., 0.]])
>>> a1 = np.zeros((3, 3), dtype=int) # make a 3×3 integer array
>>> a1[0][0] = 1 # access and assign
>>> a1[0, 0] = 1 # a friendlier syntax
>>> a1.shape # the shape of the array
(3, 3)

>>> a1[:2, :2] # the submatrix of the first two rows and first two columns, no copy
array([[1, 0],
       [0, 0]])

>>> a1[:, [0, 2]] # get columns 1 and 3, no copy
array([[1, 0],
       [0, 0],
       [0, 0]])
>>> np.max(a1) # get the maximum of the array
1
>>> a1.flatten() # flatten the array
array([1, 0, 0, 0, 0, 0, 0, 0, 0])

>>> np.sort(a1, axis = 1) # sort the array along each row and return the result
array([[0, 0, 1],
       [0, 0, 0],
       [0, 0, 0]])
>>> a1.sort(axis = 1) # sort the array along each row in place
```

#### Using `array`

[`array`](https://docs.python.org/zh-cn/3/library/array.html) is an efficient numeric array provided by the Python standard library. It compactly represents arrays of basic-type values, but it doesn't support nested arrays, and few people use it. We just mention it here in passing.

Unless stated otherwise, "array" later in this article usually means "list".

### [Input and output](https://docs.python.org/zh-cn/3/tutorial/inputoutput.html)

Input and output in Python are mainly done with the built-in functions `input()` and `print()`. We introduced them earlier; below are more advanced uses.

#### Formatted output

Competitive programming usually only needs basic number and string output, and `print()` is mostly enough. You only need formatted string output when you have to control the number of decimal places. There are three ways to format. The first and oldest uses the `printf()`-style `%` operator; the second uses the [`format` function](https://docs.python.org/3/library/string.html#formatstrings); the third is the [f-string](https://docs.python.org/zh-cn/3/tutorial/inputoutput.html#formatted-string-literals) added in Python 3.6, which is the most concise, but the Python version in a contest environment is not guaranteed to be new enough. For a detailed explanation, see [this page](https://www.python-course.eu/python3_formatted_output.php). Although the `format()` method is recommended, to keep things close to C, below we only show the old style that is similar to `printf()`:

```pycon
>>> pi = 3.1415926; print('%.4f' % pi)   # the format is %[flags][width][.precision]type
3.1416
>>> '%.4f - %8f = %d' % (pi, 0.1416, 3)  # multiple arguments on the right go in (); as you'll see later, this is actually a "tuple" 
'3.1416 - 0.141600 = 3'
```

#### The `split()` function

The `input()` function behaves like `getline()` in C++: it reads a whole line as a string, without the newline at the end. But in competitive programming, the input often has several numbers on one line. So you need the string's `split()` method together with a list comprehension to get a list of numbers. Below, using "read n numbers and compute their average" as an example, we show how to read n numbers into an "array":

```pycon
>>> s = input('Enter some numbers: '); s  # when debugging, you can pass a string to input() as a prompt
Enter some numbers: 1 2 3 4 5 6
'1 2 3 4 5 6'
>>> a = s.split(); a
['1', '2', '3', '4', '5', '6']
>>> a = [int(x) for x in a]; a
[1, 2, 3, 4, 5, 6]
>>> # the input steps above can be written in one line: a = [int(x) for x in input().split()]
>>> sum(a) / len(a)  # sum() is a built-in function
3.5
```

Sometimes each line of input has a fixed number of values, such as the start, end and weight of an edge. With only the method above, you'd have to read an array each time and then assign by index. Instead, you can use Python's "unpacking" to assign several variables at once:

```pycon
>>> u, v, w = [int(x) for x in input().split()]
1 2 4
>>> print(u,v,w)
1 2 4
```

Problems often have N lines of input. We haven't covered the most basic loop statements yet, but Python's powerful sequence operations can handle multi-line input without loops. Below, suppose we read the start points, end points and weights of the edges into three separate arrays:

```pycon
>>> N = 4; mat = [[int(x) for x in input().split()] for i in range(N)]
1 3 3 
1 4 1 
2 3 4 
3 4 1 
>>> mat  # first read a 2D array row by row
[[1, 3, 3], [1, 4, 1], [2, 3, 4], [3, 4, 1]]
>>> u, v, w = map(list, zip(*mat))   
# * unpacks mat into its inner lists
# zip() groups corresponding elements of several lists into tuples and returns an iterator
# map(list, iterable) turns each element of the sequence (here a tuple) into a list
>>> print(u, v, w)  # the iterator from map() is unpacked directly and assigned to u, v, w
[1, 1, 2, 3] [3, 4, 3, 4] [3, 1, 4, 1]
```

The program above actually reads an N-row, 3-column matrix and then transposes it into a 3-row, N-column matrix, that is, an outer list containing 3 lists. Finally, the 3 lists representing start points, end points and weights are assigned to u, v and w. The built-in function [`zip()`](https://docs.python.org/zh-cn/3/library/functions.html#zip) combines corresponding elements of several equal-length sequences into "tuples" to make a new sequence. `map()` is actually a functional programming operation: it applies a given function to the elements of the sequence produced by `zip()`; here it uses `list()` to turn tuples into lists. You can practice using `*`, [`zip()`](https://docs.python.org/zh-cn/3/library/functions.html#zip) and [`map()`](https://docs.python.org/zh-cn/3/library/functions.html#map) to understand what they mean. Note that in Python 3, `zip()` and `map()` no longer return lists but iterators. We won't explain the differences here; you can think of an iterator as something that produces the elements of a list one by one, and wrapping an iterator in `list()` produces a list.

#### [Reading and writing files](https://docs.python.org/3/reference/compound_stmts.html#the-with-statement)

The Python built-in function [`open()`](https://docs.python.org/3/library/functions.html#open) is used to read and write files. To make sure a file is closed properly even if an error happens while reading or writing, we only introduce the safe way using the [`with`](https://docs.python.org/3/reference/compound_stmts.html#the-with-statement) statement:

```python
a = []
with open("in.txt") as f:
    N = int(f.readline())  # read N from the first line
    a[len(a) :] = [[int(x) for x in f.readline().split()] for i in range(N)]

with open("out.txt", "w") as f:
    f.write("1\n")
```

There are many file reading/writing functions for different situations. Since OI contests don't yet support Python, we skip them here.

### [Control flow](https://docs.python.org/zh-cn/3/tutorial/controlflow.html)

Although we have learned many Python features, all the Python code so far has been single-line statements. This hides a major difference in code style between Python and C. First, Python uses indentation instead of `{}` to mark blocks. If the indentation isn't aligned, you get an error right away, and mixing tabs and spaces also gives an error. Second, a line that starts a block, such as an `if` or `for` statement, must end with a colon `:`. This helps readability, but you may miss the freedom of C. After all, it's annoying to realign code by hand when indentation gets lost while copying and pasting.

#### Loops

List comprehensions can do bulk operations efficiently in one line, but sometimes we've been trying a bit too hard to squeeze code into one line. In many situations you still have to use loops. So let's use reading multiple lines of data again as an example to show how loops are written in Python:

```python
# note that from now on we no longer use the REPL; copy the multi-line data yourself
u, v, w = ([] for i in range(3))  # assign multiple variables
for i in range(4):  # assume 4 lines of input here
    _u, _v, _w = [int(x) for x in input().split()]
    u.append(_u), v.append(_v), w.append(_w)
    # you can't do something like cin >> u[i] >> v[i] >> w[i], because it would go past the list's current length
    # you could initialize all-zero lists of length MAXN, but then you'd have to remember the real length and delete extra elements
print(u, v, w)
```

Note that the for loop in Python is quite different from C/C++. It works like the ["range-based for loop"](./new.md#基于范围的-for-循环) introduced in C++ 11: it really iterates over the elements of a sequence. For example, to loop over array indices you iterate over `range(len(lst))` instead of actually defining start and end conditions, so it is less flexible than in C/C++.

Below we use a while loop to show how to read input when the number of lines is unknown:

```python
u, v, w = [], [], []  # assign multiple variables, same as above
s = input()  # note that in Python an assignment statement can't be put in a condition
while s:  # you can't do while(!scanf()) like in C
    # concatenating with slices avoids append(); note the list comprehension contains nested lists
    u[len(u) :], v[len(v) :], w[len(w) :] = [[int(x)] for x in s.split()]
    s = input()
# Python 3.8 introduced the walrus operator, which saves two lines, but contest environments probably don't support it
while s := input():
    u[len(u) :], v[len(v) :], w[len(w) :] = [[int(x)] for x in s.split()]
print(u, v, w)
```

#### Conditionals

These are mostly the same as in C/C++. The differences in form are shown in the example below. Also note that the assignment operator is not allowed in conditions (in Python 3.8 and later you can use [`:=`](https://www.python.org/dev/peps/pep-0572/)), and that [there is no switch statement](https://docs.python.org/zh-cn/3/faq/design.html#why-isn-t-there-a-switch-or-case-statement-in-python).

```python
# no parentheses around the condition
if 4 >= 3 > 2 and 3 != 5 == 5 != 7:
    print("Comparison operators can be chained")
    x = None or [] or -2
    print("&&  ||  !", "AND  OR  NOT", "and or not", sep="\n")
    print("Using and/or well can save lines")
    if not x:
        print("Negative numbers are also True, so this line does not run")
    elif x & 1:
        print("Use elif, not else if\n" "Bitwise operators are like C; even & 1 gives 0, so this line does not run")
    else:
        print("There is also a ternary operator") if x else print("Mind the structure")
```

#### Exception handling

C++ has [try blocks](https://zh.cppreference.com/w/cpp/language/try_catch) for exception handling, but they are almost never used in contests. In Python, however, the [EAFP](https://docs.python.org/zh-cn/3/glossary.html#term-eafp) style is common, so code may use [`try-except`](https://docs.python.org/zh-cn/3/reference/compound_stmts.html#the-try-statement) statements a lot. We'll use it again when introducing the `dict` structure later. Here is an example:

```python
s = "OI-wiki"
pat = "NOIP"
x = s.find(pat)  # find() returns -1 if not found
try:
    y = s.index(pat)  # index() raises an error if not found
    print(y)  # this line is skipped
except ValueError:
    print("Not found")
    try:
        print(y)  # y is not defined at this point, so another error is raised
    except NameError as e:
        print("Cannot print y")
        print("Reason:", e)
```

### Built-in containers

Python has many powerful built-in container types. Only by using them fluently and knowing their characteristics can you make Python really useful in competitive programming. Besides `list` (list), covered in detail above, there are also `tuple` (tuple), [`dict`](https://docs.python.org/zh-cn/3/library/stdtypes.html#mapping-types-dict) (dictionary) and `set` (set).

You can think of a tuple simply as an immutable list. But be careful about what "immutable" means: if an element of a tuple is of a mutable type, such as a list, you can still modify that list's values. The tuple stores a reference to the list, so the tuple itself hasn't changed. The advantages of tuples are their low overhead and that they are "[hashable](https://docs.python.org/zh-cn/3/glossary.html)", which is very useful when creating dictionaries and sets.

```python
tup = tuple([[1, 2], 4])  # get a tuple from a list
# same as tup = ([1,2], 4)
tup[0].append(3)
print(tup)
a, b = 0, "I-Wiki"  # assigning multiple variables is actually tuple unpacking
print(id(a), id(b))
b, a = a, b
print(id(a), id(b))  # you should see that the ids of a and b have now swapped
# this shows even more that in Python, variables are more like names; assignment just makes them refer to objects
```

A dictionary is like [`map`](./csl/associative-container.md#map) in the C++ STL (don't confuse it with Python's built-in function [`map()`](https://docs.python.org/zh-cn/3/library/functions.html#map)) and stores key-value pairs. It looks similar to [JSON](https://docs.python.org/3/library/json.html), but in JSON keys must be strings in double quotes, while dictionaries are more flexible and powerful: any hashable object can be a key. Note that dictionaries changed quite a bit over several Python versions, including the order of their elements; explore this yourself.

```python
dic = {"key": "value"}  # basic form
dic = {chr(i): i for i in range(65, 91)}  # map uppercase letters to their ASCII codes; mind how it parses
dic = dict(zip([chr(i) for i in range(65, 91)], range(65, 91)))  # same effect as above
dic = {dic[k]: k for k in dic}  # swap keys and values; for k in dic iterates over its keys
dic = {v: k for k, v in dic.items()}  # same as the line above; dic.items() stores each key-value pair as a tuple
dic = {
    k: v for k, v in sorted(dic.items(), key=lambda x: -x[1])
}  # sort the dictionary by value in descending order, using a lambda expression

print(dic["A"])  # returns the item in dic with key 'A'; here the value is 65
dic["a"] = 97  # set d[key] to value; if key isn't in the dictionary, it's simply inserted
if "b" in dic:  # LBYL (Look Before You Leap) style
    print(dic["b"])  # this errors if the key isn't in the dictionary, so check first
else:
    dic["b"] = 98

# classic scenario: counting occurrences
# a new key isn't in the dictionary yet and needs extra handling
try:  # EAFP (Easier to Ask for Forgiveness than Permission) style
    cnter[key] += 1
except KeyError:
    cnter[key] = 1
```

A set is like [`set`](./csl/associative-container.md#set) in the C++ STL: it doesn't store duplicate elements, and you can think of it as a dictionary that only stores keys. Note that both sets and dictionaries use `{}`, but `{}` by itself creates an empty dictionary, not an empty set. We won't give an example here.

### Writing functions

Defining a function in Python doesn't require parameter or return types, which quietly reduces the amount of code OI contestants have to write

```python
def add(a, b):
    return a + b  # the advantage of dynamic typing: a and b can also be strings


def add_no_swap(a, b):
    print("in func #1:", id(a), id(b))
    a += b
    b, a = a, b
    print("in func #2:", id(a), id(b))  # a, b are swapped
    return a, b  # returning multiple values really returns a tuple, which can be unpacked


lst1 = [1, 2]
lst2 = [3, 4]
print("outside func #1:", id(lst1), id(lst2))
add_no_swap(lst1, lst2)
# outside the function, lst1 and lst2 were not swapped
print("outside func #2:", id(lst1), id(lst2))
# but their values did change
print(lst1, lst2)
```

#### Default arguments

Function parameters in Python are very flexible: there are keyword arguments, variadic arguments and more. But these features aren't very useful in competitive programming, so here we only cover default arguments, because C++ has default arguments too, and in Python they can easily trip you up. Consider the following code.

```python
def append_to(element, to=[]):
    to.append(element)
    return to


lst1 = append_to(12)
lst2 = append_to(42)
print(lst1, lst2)

# you might expect the output to be [12] [42]
# but the actual output is [12, 42] [12, 42]
```

This happens because the value of a default argument is assigned only once, when the function is defined. For mutable objects (such as lists, dictionaries and sets), all calls share the same object: `lst1` and `lst2` both actually point to the same default list object in memory. So after the second call, the contents of this shared list have become `[12, 42]`. Therefore the default value of a function argument should be an immutable object; using `None` as a placeholder is a best practice:

```python
def append_to(element, to=None):
    if to is None:
        to = []
    to.append(element)
    return to


lst1 = append_to(12)
lst2 = append_to(42)
print(lst1, lst2)

# the output is [12] [42]
```

#### Type annotations

Python is a dynamically type-checked language that handles types in a flexible but implicit way. The Python interpreter checks types only at run time, and it allows a variable's type to change at run time. As the saying goes, "dynamic typing is fun now, refactoring is a nightmare later". Some errors in a program may only show up at run time:

```pycon
>>> if False:
...     1 + "two"  # This line never runs, so no TypeError is raised
... else:
...     1 + 2
...
3

>>> 1 + "two"  # Now this is type checked, and a TypeError is raised
TypeError: unsupported operand type(s) for +: 'int' and 'str'
```

Python 3.5 introduced type annotations, which let you set the types of function parameters and return values. But they are only hints and don't actually restrict anything; you need static checkers (such as [PyCharm](https://www.jetbrains.com/pycharm/) and [Mypy](http://mypy-lang.org/)) to catch such errors. So they are of limited value, and OIers only need to know about them. You can annotate a function's parameters and return value like this:

```python
def headline(
    text,  # type: str
    width=80,  # type: int
    fill_char="-",  # type: str
):  # type: (...) -> str
    return f"{text.title()}".center(width, fill_char)


print(headline("type comments work", width=40))
```

Besides function parameters, variables can also be annotated. You can look at `__annotations__` to see all the type annotations in a function. Variable annotations give Python a feature of static languages: declaration separate from assignment:

```pycon
>>> nothing: str
>>> nothing
NameError: name 'nothing' is not defined

>>> __annotations__
{'nothing': <class 'str'>}
```

## Decorators

A decorator is a function that takes a function or method as its only argument and returns a new function or method that wraps the decorated one and adds some extra functionality. In short, it lets you add functionality to a function without changing the function's code. For more, see the [official documentation](https://docs.python.org/3/glossary.html#term-decorator).

Some decorators are very useful in contests, such as [`lru_cache`](https://docs.python.org/3/library/functools.html#functools.lru_cache), which automatically adds memoization to a function. It's very handy for recursive algorithms:

`@lru_cache(maxsize=128,typed=False)`

-   It takes 2 parameters: `maxsize` and `typed`. If you don't pass them, `maxsize` defaults to 128 and `typed` defaults to `False`.
-   `maxsize` is the capacity of the LRU cache, that is, the maximum number of results the decorated method can cache. If it is 128, the decorated method can cache at most 128 return values; if `maxsize` is `None`, it can cache an unlimited number of results.
-   If `typed` is `True`, function arguments of different types are cached separately. For example, `f(3)` and `f(3.0)` are cached twice.

Here is an example of using `lru_cache` to speed up computing Fibonacci numbers:

```python
@lru_cache(maxsize=None)
def fib(n):
    if n < 2:
        return n
    return fib(n - 1) + fib(n - 2)
```

## Common built-in libraries

Here are some built-in libraries that may be useful for writing algorithms. Search for usage details yourself or read the [official documentation](https://docs.python.org/3/library/index.html).

| Library                                                             | Purpose                                     |
| ------------------------------------------------------------------- | ------------------------------------------- |
| [`array`](https://docs.python.org/3/library/array.html)             | fixed-type arrays                           |
| [`argparse`](https://docs.python.org/3/library/argparse.html)       | command-line argument parsing               |
| [`bisect`](https://docs.python.org/3/library/bisect.html)           | binary search                               |
| [`collections`](https://docs.python.org/3/library/collections.html) | data structures like ordered dicts, deques  |
| [`fractions`](https://docs.python.org/3/library/fractions.html)     | rational numbers                            |
| [`heapq`](https://docs.python.org/3/library/heapq.html)             | heap-based priority queues                  |
| [`io`](https://docs.python.org/3/library/io.html)                   | file streams, in-memory streams             |
| [`itertools`](https://docs.python.org/3/library/itertools.html)     | iterators                                   |
| [`math`](https://docs.python.org/3/library/math.html)               | math functions                              |
| [`os.path`](https://docs.python.org/3/library/os.html)              | system paths, etc.                          |
| [`random`](https://docs.python.org/3/library/random.html)           | random numbers                              |
| [`re`](https://docs.python.org/3/library/re.html)                   | regular expressions                         |
| [`struct`](https://docs.python.org/3/library/struct.html)           | converting between structs and binary data  |
| [`sys`](https://docs.python.org/3/library/sys.html)                 | system information                          |

## Comparing C++ and Python through an example problem

??? note "[Example problem: Luogu P4779 [Template] Single-Source Shortest Paths (Standard Version)](https://www.luogu.com.cn/problem/P4779)"
    Given a graph with $n(1 \leq n \leq 10^5)$ vertices and $m(1 \leq m \leq 2\times 10^5)$ directed edges with non-negative weights, compute the distance from $s$ to every vertex. It is guaranteed that every vertex can be reached from $s$.

### Declaring constants

=== "C++"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    #include <vector>
    using namespace std;
    constexpr int N = 1e5 + 5, M = 2e5 + 5;
    ```

=== "Python"
    ```python
    try:  # import the priority queue module
        import Queue as pq  # python version < 3.0
    except ImportError:
        import queue as pq  # python3.*
    
    N = int(1e5 + 5)
    M = int(2e5 + 5)
    INF = 0x3F3F3F3F
    ```

### Declaring the forward-star struct and other variables

=== "C++"
    ```cpp
    struct qxx {
      int nex, t, v;
    };
    
    qxx e[M];
    int h[N], cnt;
    
    void add_path(int f, int t, int v) { e[++cnt] = qxx{h[f], t, v}, h[f] = cnt; }
    
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    int dist[N];
    ```

=== "Python"
    ```python
    class qxx:  # forward-star class (struct)
        def __init__(self):
            self.nex = 0
            self.t = 0
            self.v = 0
    
    
    e = [qxx() for i in range(M)]  # linked list
    h = [0 for i in range(N)]
    cnt = 0
    
    dist = [INF for i in range(N)]
    q = pq.PriorityQueue()  # define the priority queue; by default a min-heap on the first element
    
    
    def add_path(f, t, v):  # add an edge to the forward star
        # to modify global variables, declare them with global
        global cnt, e, h
        # output statement for debugging; use a tuple for multiple variables
        # print("add_path(%d,%d,%d)" % (f,t,v))
        cnt += 1
        e[cnt].nex = h[f]
        e[cnt].t = t
        e[cnt].v = v
        h[f] = cnt
    ```

### Dijkstra's algorithm

=== "C++"
    ```cpp
    void dijkstra(int s) {
      memset(dist, 0x3f, sizeof(dist));
      dist[s] = 0, q.push(make_pair(0, s));
      while (q.size()) {
        pii u = q.top();
        q.pop();
        if (dist[u.second] < u.first) continue;
        for (int i = h[u.second]; i; i = e[i].nex) {
          const int &v = e[i].t, &w = e[i].v;
          if (dist[v] <= dist[u.second] + w) continue;
          dist[v] = dist[u.second] + w;
          q.push(make_pair(dist[v], v));
        }
      }
    }
    ```

=== "Python"
    ```python
    def nextedgeid(u):  # a generator, can be used in a for loop
        i = h[u]
        while i:
            yield i
            i = e[i].nex
    
    
    def dijkstra(s):
        dist[s] = 0
        q.put((0, s))
        while not q.empty():
            u = q.get()  # get also removes the element from the heap
            if dist[u[1]] < u[0]:
                continue
            for i in nextedgeid(u[1]):
                v = e[i].t
                w = e[i].v
                if dist[v] <= dist[u[1]] + w:
                    continue
                dist[v] = dist[u[1]] + w
                q.put((dist[v], v))
    ```

### Main function

=== "C++"
    ```cpp
    int n, m, s;
    
    int main() {
      scanf("%d%d%d", &n, &m, &s);
      for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_path(u, v, w);
      }
      dijkstra(s);
      for (int i = 1; i <= n; i++) printf("%d ", dist[i]);
      return 0;
    }
    ```

=== "Python"
    ```python
    if __name__ == "__main__":
        # read several integers from one line. Note that it reads the whole line
        n, m, s = map(int, input().split())
        for i in range(m):
            u, v, w = map(int, input().split())
            add_path(u, v, w)
    
        dijkstra(s)
    
        for i in range(1, n + 1):
            print(dist[i], end=" ")
    
        print()
    ```

### Full code

=== "C++"
    ```cpp
    #include <cstdio>
    #include <cstring>
    #include <queue>
    #include <vector>
    using namespace std;
    constexpr int N = 1e5 + 5, M = 2e5 + 5;
    
    struct qxx {
      int nex, t, v;
    };
    
    qxx e[M];
    int h[N], cnt;
    
    void add_path(int f, int t, int v) { e[++cnt] = qxx{h[f], t, v}, h[f] = cnt; }
    
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<pii>> q;
    int dist[N];
    
    void dijkstra(int s) {
      memset(dist, 0x3f, sizeof(dist));
      dist[s] = 0, q.push(make_pair(0, s));
      while (q.size()) {
        pii u = q.top();
        q.pop();
        if (dist[u.second] < u.first) continue;
        for (int i = h[u.second]; i; i = e[i].nex) {
          const int &v = e[i].t, &w = e[i].v;
          if (dist[v] <= dist[u.second] + w) continue;
          dist[v] = dist[u.second] + w;
          q.push(make_pair(dist[v], v));
        }
      }
    }
    
    int n, m, s;
    
    int main() {
      scanf("%d%d%d", &n, &m, &s);
      for (int i = 1; i <= m; i++) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        add_path(u, v, w);
      }
      dijkstra(s);
      for (int i = 1; i <= n; i++) printf("%d ", dist[i]);
      return 0;
    }
    ```

=== "Python"
    ```python
    try:  # import the priority queue module
        import Queue as pq  # python version < 3.0
    except ImportError:
        import queue as pq  # python3.*
    
    N = int(1e5 + 5)
    M = int(2e5 + 5)
    INF = 0x3F3F3F3F
    
    
    class qxx:  # forward-star class (struct)
        def __init__(self):
            self.nex = 0
            self.t = 0
            self.v = 0
    
    
    e = [qxx() for i in range(M)]  # linked list
    h = [0 for i in range(N)]
    cnt = 0
    
    dist = [INF for i in range(N)]
    q = pq.PriorityQueue()  # define the priority queue; by default a min-heap on the first element
    
    
    def add_path(f, t, v):  # add an edge to the forward star
        # to modify global variables, declare them with global
        global cnt, e, h
        # output statement for debugging; use a tuple for multiple variables
        # print("add_path(%d,%d,%d)" % (f,t,v))
        cnt += 1
        e[cnt].nex = h[f]
        e[cnt].t = t
        e[cnt].v = v
        h[f] = cnt
    
    
    def nextedgeid(u):  # a generator, can be used in a for loop
        i = h[u]
        while i:
            yield i
            i = e[i].nex
    
    
    def dijkstra(s):
        dist[s] = 0
        q.put((0, s))
        while not q.empty():
            u = q.get()
            if dist[u[1]] < u[0]:
                continue
            for i in nextedgeid(u[1]):
                v = e[i].t
                w = e[i].v
                if dist[v] <= dist[u[1]] + w:
                    continue
                dist[v] = dist[u[1]] + w
                q.put((dist[v], v))
    
    
    # run these commands if you run this Python code directly (not imported as a module or the like)
    if __name__ == "__main__":
        # read several integers from one line. Note that it reads the whole line
        n, m, s = map(int, input().split())
        for i in range(m):
            u, v, w = map(int, input().split())
            add_path(u, v, w)
    
        dijkstra(s)
    
        for i in range(1, n + 1):
            # both output syntaxes work
            print("{}".format(dist[i]), end=" ")
            # print("%d" % dist[i],end=' ')
    
        print()  # newline at the end
    ```

## Reference documentation

1.  [Python Documentation](https://www.python.org/doc/)
2.  [Official Python tutorial (Chinese)](https://docs.python.org/zh-cn/3/tutorial/)
3.  [Learn Python3 In Y Minutes](https://learnxinyminutes.com/docs/python3/)
4.  [Real Python Tutorials](https://realpython.com/)
5.  [Liao Xuefeng's Python tutorial](https://www.liaoxuefeng.com/wiki/1016959663602400/)
6.  [GeeksforGeeks: Python Tutorials](https://www.geeksforgeeks.org/python-programming-language/)

## References and notes

[^ref1]: [2. Using the Python Interpreter - Python 3 documentation](https://docs.python.org/zh-cn/3/tutorial/interpreter.html#id1)

[^ref2]: [Unicode HOWTO - Python 3 documentation](https://docs.python.org/zh-cn/3/howto/unicode.html#the-string-type)
