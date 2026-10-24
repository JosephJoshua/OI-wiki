A **union** is a special class type that can hold only one of its non-static data members at a time.

Unions were officially added to the entry level of the NOI syllabus in 2023.

## Defining a union

The class specifier for a union declaration looks like the declaration of a class or a [struct](./struct.md):

```cpp
union MyUnion {
  int x;
  long long y;
} x;
```

A union is defined much like a struct. With the definition above, `MyUnion` can also be used as a user-defined type. The name `MyUnion` can be omitted.

## Accessing/modifying members

Just like with a struct, you access a member with `variableName.memberName`.

The memory a union takes up is **at least** the size of its largest member, and all members **share the same memory and address**. When you assign to one member, the other members of the union are overwritten, because they share memory. In other words, a union can hold the value of only one member at a time.

For more ways to use unions, see [cppreference: Union declaration](https://zh.cppreference.com/w/cpp/language/union).
