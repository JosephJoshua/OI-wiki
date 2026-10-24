author: Frankaiyou, henrytbtrue, zymooll

## The C standard library

The C standard library works on character arrays `char[]`/`const char*`.

See also: [fprintf](https://zh.cppreference.com/w/c/io/fprintf), [fscanf](https://zh.cppreference.com/w/c/io/fscanf), [Null-terminated byte strings](https://zh.cppreference.com/w/c/string/byte)

-   `printf("%s", s)`: uses `%s` to print a string (character array).
-   `scanf("%s", &s)`: uses `%s` to read a string (character array).
-   `sscanf(const char *__source, const char *__format, ...)`: reads variables from the string `__source`, for example `sscanf(str,"%d",&a)`.
-   `sprintf(char *__stream, const char *__format, ...)`: writes the content of the `__format` string into `__stream`, for example `sprintf(str,"%d",i)`.
-   `strlen(const char *str)`: returns the number of characters from `str[0]` up to `'\0'`. Note that without O2 optimization, writing this call in a loop condition costs $\Theta(N)$ each time.
-   `strcmp(const char *str1, const char *str2)`: compares `str1 str2` in lexicographic order. It returns a negative value if `str1` is lexicographically smaller, `0` if they are equal, and a positive value if `str1` is lexicographically larger. Do not assume the return value is only `0`, `1` or `-1`: on every platform the sign is correct, but the values are not always `0`, `1`, `-1`.
-   `strcpy(char *str, const char *src)`: copies the characters of `src` into `str`. `str` and `src` are both pointers to the start of character arrays. The return value is `str`, which includes the null terminator `'\0'`.
-   `strncpy(char *str, const char *src, int cnt)`: copies at most `cnt` characters into `str`. If `src` ends before `cnt` characters are copied, null characters are written to `str` until a total of `cnt` characters have been written.
-   `strcat(char *str1, const char *str2)`: appends `str2` to the end of `str1`, replacing the `'\0'` at the end of `str1` with `*str2`, and returns `str1`.
-   `strstr(char *str1, const char *str2)`: if `str2` is a substring of `str1`, returns the address of the first occurrence of `str2` in `str1`; if `str2` is not a substring of `str1`, returns `NULL`.
-   `strchr(const char *str, int c)`: finds the first position of the character `c` in the string `str` and returns the address of that position. If the character is not found, returns `NULL`.
-   `strrchr(const char *str, int c)`: finds the last position of the character `c` in the string `str` and returns the address of that position. If the character is not found, returns `NULL`.

## The C++ standard library

The C++ standard library works on string objects [`std::string`](../lang/csl/string.md), and it is also compatible with character arrays.

See also: [std::basic\_string](https://zh.cppreference.com/w/cpp/string/basic_string), [std::basic\_string\_view](https://zh.cppreference.com/w/cpp/string/basic_string_view)

-   The operator `+` is overloaded. When both sides of `+` are of type `string/char/char[]/const char*`, it concatenates the two and returns the resulting string (`string`).
-   The right-hand side of the assignment operator `=` can be `const string/string/const char*/char*`.
-   The access operator `[cur]` returns a reference to the character at position `cur`.
-   The access functions `data()/c_str()` return a `const char*` pointer whose content is the same as the `string`.
-   The capacity function `size()` returns the number of characters in the string.
-   `find(ch, start = 0)` finds and returns the position of the character `ch` starting from `start`; `rfind(ch)` searches from the end and returns the position of the first `ch` it finds (both positions start from `0`) (if nothing is found, it returns `-1`).
-   `substr(start, len)` takes a substring of length `len` starting at `start` (counting from `0`) (if `len` is omitted, it takes everything up to the end of the string).
-   `append(s)` appends `s` to the end of the string.
-   `append(s, pos, n)` appends the `n` characters of the string `s` starting at `pos` to the end of the current string.
-   `replace(pos, n, s)` deletes `n` characters starting at `pos`, then inserts the string `s` at `pos`.
-   `erase(pos, n)` deletes `n` characters starting at `pos`.
-   `insert(pos, s)` inserts the string `s` at position `pos`.
-   `std::string` overloads the comparison operators, with complexity $\Theta(N)$.
