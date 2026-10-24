author: Ir1d, cjsoft, Lans1ot

A **struct** can be seen as a bundle of several pieces called member elements.

You can think of it as a user-defined data type.

???+ note "Note"
    The `struct` described on this page is different from `struct` in C. In C++, `struct` was extended into a class specifier similar to [`class`](./class.md).

## Defining a struct

```cpp
struct Object {
  int weight;
  int value;
} e[array_length];

const Object a;
Object b, B[array_length], tmp;
Object *c;
```

The example above defines a struct named `Object` with two member elements, `value` and `weight`, both of type `int`.

After the `}`, it defines the constant `a`, the variable `b`, the variable `tmp`, the array `B` and the pointer `c`, all of type `Object`. You can use the same pattern to define constants, variables, pointers, arrays and so on for any existing type.

*About pointers: you don't have to master them right now.*

### Defining pointers

To define a pointer to a built-in type, write it the same way as any ordinary pointer.

To define a pointer to a struct, use `StructName*` in the definition.

```cpp
struct Edge {
  /*
  ...
  */
  Edge* nxt;
};
```

This is just an example; don't worry about what it actually means.

## Accessing/modifying members

You access a member with `variableName.memberName`. For example, `cout << var.v` prints the `v` member of `var`.

You can also use `pointerName->memberName` or `(*pointerName).memberName`. For example, `(*ptr).v = tmp` or `ptr->v = tmp` sets the member `v` of the struct that the struct pointer `ptr` points to to `tmp`.

## Why do we need structs?

First of all, all roads lead to Rome: you can get the same effect without structs. But a struct explicitly bundles member elements (usually variables in competitive programming) together. For example, the `Object` struct here puts `value` and `weight` together (the real meaning of this struct is the weight and value of one item). The benefit is that it restricts how the member elements are used.  
Imagine you don't use a struct and have two arrays `value[]` and `Value[]`. It is easy to mix them up. With a struct, you are less likely to use the wrong variable.

Also, different structs (struct types, such as the `Object` struct) or different struct variables (struct instances, such as the `e` array above) can have members with the same name (such as `tmp.value` and `b.value`). Members with the same name are independent of each other (each has its own memory; for example, changing `tmp.value` does not affect the value of `b.value`).  
The benefit is that you can use the same or similar variable names to describe things. For example, `Object` has the member variable `value`; we can also define a `Car` struct that has a `value` member too. Without structs, we might have to define arrays with different names, such as `valueOfObject[]` and `valueOfCar[]`, to tell them apart.

*If you want to describe something in more detail, you can also define member functions. See [Classes](./class.md) for details.*

## More operations?

See [Classes](./class.md).

## Caveats

To make memory access more efficient, the compiler may align members at certain byte positions when it lays out a struct in memory. This means there can be unused gaps inside the struct. So a struct may take up more space than the total size of all its members.

## References

1.  [Class - zh.cppreference.com](https://zh.cppreference.com/w/cpp/language/class)
2.  [Data structures - cplusplus.com](http://www.cplusplus.com/doc/tutorial/structures/)
3.  [Alignment - Microsoft Docs](https://docs.microsoft.com/zh-cn/cpp/cpp/alignment-cpp-declarations)
