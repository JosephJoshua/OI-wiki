A checker, also known as a [Special Judge](../special-judge.md), verifies whether an answer is valid. Testlib saves us from checking many things by hand, which makes writing one much simpler.

A checker gets the input file name, the contestant's output file name and the reference output file name from its command-line arguments, decides whether the contestant's output is correct, and returns one of the predefined verdicts:

Please read [General](./general.md) before reading the rest of this page.

## A simple example

???+ note "Problem"
    Given two integers $a,b$ ($-1000 \le a,b \le 1000$), output their sum.

This problem obviously doesn't need a checker, right? But if you really want one, you can write it like this:

```cpp
#include "testlib.h"

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);

  int pans = ouf.readInt(-2000, 2000, "sum of numbers");

  // Assume the reference output is correct and don't check its range
  // We'll see later that this isn't a good idea
  int jans = ans.readInt();

  if (pans == jans)
    quitf(_ok, "The sum is correct.");
  else
    quitf(_wa, "The sum is wrong: expected = %d, found = %d", jans, pans);
}
```

## Writing a readAns function

Suppose you have a problem whose input and output both contain many numbers, for example: given a DAG, find the longest path from $s$ to $t$ and output the path (there may be several; output any of them).

Below is an example of a **bad** checker.

### A bad implementation

```cpp
#include "testlib.h"
//
#include <map>
#include <vector>
using namespace std;

map<pair<int, int>, int> edges;

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  int n = inf.readInt();  // No need for readSpace() or readEoln()
  int m = inf.readInt();  // because the checker doesn't need to validate the input
                          // (there is a validator for that)
  for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    int w = inf.readInt();
    edges[make_pair(a, b)] = edges[make_pair(b, a)] = w;
  }
  int s = inf.readInt();
  int t = inf.readInt();

  // Read the reference output
  int jvalue = 0;
  vector<int> jpath;
  int jlen = ans.readInt();
  for (int i = 0; i < jlen; i++) {
    jpath.push_back(ans.readInt());
  }
  for (int i = 0; i < jlen - 1; i++) {
    jvalue += edges[make_pair(jpath[i], jpath[i + 1])];
  }

  // Read the contestant's output
  int pvalue = 0;
  vector<int> ppath;
  vector<bool> used(n);
  int plen = ouf.readInt(2, n, "number of vertices");  // contains at least s and t
  for (int i = 0; i < plen; i++) {
    int v = ouf.readInt(1, n, format("path[%d]", i + 1).c_str());
    if (used[v - 1])  // check that each vertex is used only once
      quitf(_wa, "vertex %d was used twice", v);
    used[v - 1] = true;
    ppath.push_back(v);
  }
  // Check the start and end vertices
  if (ppath.front() != s)
    quitf(_wa, "path doesn't start in s: expected s = %d, found %d", s,
          ppath.front());
  if (ppath.back() != t)
    quitf(_wa, "path doesn't finish in t: expected t = %d, found %d", t,
          ppath.back());
  // Check that adjacent vertices are connected by an edge
  for (int i = 0; i < plen - 1; i++) {
    if (edges.find(make_pair(ppath[i], ppath[i + 1])) == edges.end())
      quitf(_wa, "there is no edge (%d, %d) in the graph", ppath[i],
            ppath[i + 1]);
    pvalue += edges[make_pair(ppath[i], ppath[i + 1])];
  }

  if (jvalue != pvalue)
    quitf(_wa, "jury has answer %d, participant has answer %d", jvalue, pvalue);
  else
    quitf(_ok, "answer = %d", pvalue);
}
```

This checker has two main problems:

1.  It trusts that the reference output is correct. If the contestant's output is better than the reference output, it is judged WA, which is not good. Also, if the reference output is invalid, it also gives WA. In both cases, the right thing to do is to return Fail.
2.  The code that reads the reference output and the contestant's output is duplicated. In this problem, writing the reading code twice is no big deal, since it's just one `for` loop; but if a problem has complex output, your checker becomes messy. Duplicated code makes the checker much harder to maintain, and makes debugging or changing the format difficult.

The reference output and the contestant's output are actually read in exactly the same way. That is why we usually write a reading function that takes the stream as a parameter.

### A good implementation

```cpp
// clang-format off

#include "testlib.h"
#include <map>
#include <vector>
using namespace std;

map<pair<int, int>, int> edges;
int n, m, s, t;

// This function takes a stream and reads from it,
// checks that the path is valid, and returns its length.
// When stream is ans, every stream.quitf(_wa, ...)
// and every failed readXxx() returns _fail instead of _wa.
// In other words, if the output is invalid, it returns _wa for the contestant's output stream
// and _fail for the reference output stream.
int readAns(InStream& stream) {
  // Read the output
  int value = 0;
  vector<int> path;
  vector<bool> used(n);
  int len = stream.readInt(2, n, "number of vertices");
  for (int i = 0; i < len; i++) {
    int v = stream.readInt(1, n, format("path[%d]", i + 1).c_str());
    if (used[v - 1]) {
      stream.quitf(_wa, "vertex %d was used twice", v);
    }
    used[v - 1] = true;
    path.push_back(v);
  }
  if (path.front() != s)
    stream.quitf(_wa, "path doesn't start in s: expected s = %d, found %d", s,
                 path.front());
  if (path.back() != t)
    stream.quitf(_wa, "path doesn't finish in t: expected t = %d, found %d", t,
                 path.back());
  for (int i = 0; i < len - 1; i++) {
    if (edges.find(make_pair(path[i], path[i + 1])) == edges.end())
      stream.quitf(_wa, "there is no edge (%d, %d) in the graph", path[i],
                   path[i + 1]);
    value += edges[make_pair(path[i], path[i + 1])];
  }
  return value;
}

int main(int argc, char* argv[]) {
  registerTestlibCmd(argc, argv);
  n = inf.readInt();
  m = inf.readInt();
  for (int i = 0; i < m; i++) {
    int a = inf.readInt();
    int b = inf.readInt();
    int w = inf.readInt();
    edges[make_pair(a, b)] = edges[make_pair(b, a)] = w;
  }
  int s = inf.readInt();
  int t = inf.readInt();
  
  int jans = readAns(ans);
  int pans = readAns(ouf);
  if (jans > pans)
    quitf(_wa, "jury has the better answer: jans = %d, pans = %d\n", jans,
          pans);
  else if (jans == pans)
    quitf(_ok, "answer = %d\n", pans);
  else  // (jans < pans)
    quitf(_fail, ":( participant has the better answer: jans = %d, pans = %d\n",
          jans, pans);
}
```

Notice that this way we also check that the reference output is valid. Writing checkers like this makes the program shorter and easier to understand and debug. The same approach also works for problems where the output is YES (plus a construction or similar) or NO.

???+ note "Note"
    Some constraint checks can be written more concisely with the `InStream::ensure/ensuref()` functions. For example, lines 23 to 25 of the example above can equivalently be written as:
    
    ```cpp
    stream.ensuref(!used[v - 1], "vertex %d was used twice", v);
    ```

???+ warning "Warning"
    Avoid calling the **global** functions `::ensure/ensuref()` in `readAns`. Otherwise, some contestant outputs that should be judged WA will return `_fail`, which is wrong.

## Tips and common mistakes

-   Write a `readAns` function. It really makes your checker great.

-   Always restrict the range when reading the contestant's output. If you forget to restrict some variable and it is then used as a parameter somewhere, your checker may give a wrong verdict, crash with RE, and so on.

    -   Bad example

    ```cpp
    // ....
    int k = ouf.readInt();
    vector<int> lst;
    for (int i = 0; i < k; i++)  // k = 0 and k = -5 behave the same here (the loop body never runs)
      lst.push_back(ouf.readInt());
    // But we don't want to accept a list of length -5, do we?
    // ....
    int pos = ouf.readInt();
    int x = A[pos];
    // Someone might print -42, 2147483456 or some other invalid number and make the checker RE
    ```

    -   Good example

    ```cpp
    // ....
    int k = ouf.readInt(0, n);  // an invalid length gives WA immediately instead of continuing the check and causing RE
    vector<int> lst;
    for (int i = 0; i < k; i++) lst.push_back(ouf.readInt());
    // ....
    int pos = ouf.readInt(0, (int)A.size() - 1);  // prevents out of range
    int x = A[pos];
    // ....
    ```

-   Use item names.

-   Unlike a validator, a checker doesn't need to check whitespace characters specifically. For example, for a checker that compares integers in order, we only need to check that each integer in the contestant's output equals the corresponding integer in the answer. Our checker doesn't care about format details such as whether the contestant prints one integer per line or all integers on one line.

## Usage

Usually we don't need to run it locally; the judging tool/OJ does all of this for us. But if needed, run it from the command line in the following format:

```bash
./checker <input-file> <output-file> <answer-file> [<report-file> [<-appes>]]
```

## Some predefined checkers

Very often our checker does something simple (such as checking whether the output integers are correct, or whether the output floating-point numbers meet the precision requirement). [Testlib](https://github.com/MikeMirzayanov/testlib/tree/master/checkers) already provides implementations of these checkers, and we can use them directly.

Some commonly used checkers are:

-   ncmp: compares 64-bit integers in order.
-   rcmp4: compares floating-point numbers in order, with a maximum allowed error (absolute or relative) of $10^{-4}$ (there are also checkers such as rcmp6 and rcmp9 with different precision requirements; they are used like rcmp4).
-   wcmp: compares strings (tokens without whitespace such as spaces and line breaks) in order.
-   yesno: compares YES and NO, case-insensitively.

    **This article is mainly translated from [Checkers with testlib.h - Codeforces](https://codeforces.com/blog/entry/18431). The GitHub repository of `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**
