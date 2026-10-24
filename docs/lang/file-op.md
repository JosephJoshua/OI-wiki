author: Ir1d, cqnuljs, akakw1, MingqiHuang, Chrogeek, henrytbtrue, Planet6174, StudyingFather

## What a file is

A file is a collection of related data gathered for some purpose. C/C++ treats every file as an ordered stream of bytes, and every file ends with an **end-of-file marker** (EOF). To work with a file, a program must first open it. Once a file is opened (remember to close any file you open), it is associated with a stream. Here a stream is simply a sequence of bytes.

C/C++ divides files into text files and binary files. Text files are plain text files (the important kind); binary files are files in special formats, executable files and so on.

## Steps for working with a file

1. Open the file: point a file pointer at it and decide how to open it;  
2. Read from and write to the file (these are the main operations used in contests; other operations are not covered for now);  
3. Close the file when you are done with it.

## The `freopen` function

### Introduction

This function redirects a given input/output stream to a file in a given mode. It is declared in the header `stdio.h (cstdio)`. It lets you change where input and output go without changing the rest of your code, but you should make sure the stream is reliable when you use it.

It has three main modes: read, write and append.

### Syntax

```cpp
FILE* freopen(const char* filename, const char* mode, FILE* stream);
```

### Parameters

-   `filename`: the name of the file to open
-   `mode`: the mode to open the file in, i.e. the access permissions
-   `stream`: a file pointer, usually a standard file stream (`stdin/stdout`) or the standard error stream (`stderr`)
-   Return value: a file pointer to the opened file

### File open modes (optional reading)

-   `r`: open the file read-only. The file must exist. Only reading is allowed **(common)**
-   `r+`: open the file for reading and writing. The file must exist. Reading and writing are allowed
-   `rb`: open a binary file read-only. The file must exist. Only reading is allowed
-   `rb+`: open a binary file for reading and writing. The file must exist. Reading and writing are allowed
-   `rt+`: open a text file for reading and writing. Reading and writing are allowed
-   `w`: open the file write-only. If the file does not exist it is created; otherwise its contents are erased. Only writing is allowed **(common)**
-   `w+`: open the file for reading and writing. If the file does not exist it is created; otherwise its contents are erased. Reading and writing are allowed
-   `wb`: open a binary file write-only. If the file does not exist it is created; otherwise its contents are erased. Only writing is allowed
-   `wb+`: open a binary file for reading and writing. If the file does not exist it is created; otherwise its contents are erased. Reading and writing are allowed
-   `a`: open the file write-only. If the file does not exist it is created. Written data is appended to the end of the file (the EOF marker is kept)
-   `a+`: open the file for reading and writing. If the file does not exist it is created. Written data is appended to the end of the file (the EOF marker is not kept)
-   `at+`: open a text file for reading and writing. Written data is appended to the end of the file
-   `ab+`: open a binary file for reading and writing. Written data is appended to the end of the file

### Usage

Reading from a file:

```cpp
freopen("data.in", "r", stdin);
// data.in is the name of the file to read; put it in the same directory as the executable
```

Writing to a file:

```cpp
freopen("data.out", "w", stdout);
// data.out is the name of the output file, in the same directory as the executable
```

Closing the standard input/output streams

```cpp
fclose(stdin);
fclose(stdout);
```

??? note "Note"
    Functions such as `printf/scanf/cin/cout` use `stdin/stdout` by default. After `stdin/stdout` are redirected, these functions read from and write to the redirected files.

### Template

```cpp
#include <cstdio>
#include <iostream>

int main(void) {
  freopen("data.in", "r", stdin);
  freopen("data.out", "w", stdout);
  /*
  The code in between does not need to change; just use cin and cout as usual
  */
  fclose(stdin);
  fclose(stdout);
  return 0;
}
```

## The `fopen` function (optional reading)

This function is mostly the same as `freopen`. It opens the given file and returns a pointer to the opened file.

### Function prototype

```cpp
FILE* fopen(const char* path, const char* mode)
```

The parameters mean the same as in `freopen`.

### Read/write functions you can use (basic)

-   `fread/fwrite`
-   `fgetc/fputc`
-   `fscanf/fprintf`
-   `fgets/fputs`

### Usage

```cpp
FILE *in, *out;  // define file pointers
in = fopen("data.in", "r");
out = fopen("data.out", "w");
/*
do what you want to do
*/
fclose(in);
fclose(out);
```

## C++ file streams `ifstream/ofstream`

### Usage

Reading from a file:

```cpp
ifstream fin("data.in");
// data.in is the relative or absolute path of the file to read
```

Writing to a file:

```cpp
ofstream fout("data.out");
// data.out is the relative or absolute path of the output file
```

Closing the standard input/output streams

```cpp
fin.close();
fout.close();
```

### Template

```cpp
#include <fstream>
using namespace std;  // both types are in the std namespace

ifstream fin("data.in");
ofstream fout("data.out");

int main(void) {
  /*
  In the code in between, just change cin to fin and cout to fout
  */
  fin.close();
  fout.close();
  return 0;
}
```

## References

1.  *Xinxixue Aosai Yibentong* (an informatics olympiad textbook)
