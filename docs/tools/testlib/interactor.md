An interactor talks to the contestant's program in interactive problems. For an introduction to interactive problems, see [Problem types - Interactive problems](../../contest/problems.md#).

???+ note "Note"
    Testlib supports only Codeforces-style interactive problems, where two programs interact. It does not support NOI-style problems where the contestant writes functions that interact with other functions.

Please read [General](./general.md) before reading the rest of this page.

Testlib provides interactors with a special stream `std::fstream tout`. It is a log stream: you can write to it in the interactor and read it with `ouf` in the checker.

In the interactor, we read the test data from `inf`, write the standard input of the contestant's program (and the reference solution) to `stdout` (online), read the contestant's output from `ouf` (online), and read the reference output from `ans` (online).

If the interactor returns ok, the checker (if there is one) takes over and checks whether the answer is valid.

## Usage

Windows:

```bat
interactor.exe <Input_File> <Output_File> [<Answer_File> [<Result_File> [-appes]]],
```

Linux:

```bash
./interactor.out <Input_File> <Output_File> [<Answer_File> [<Result_File> [-appes]]],
```

## A simple example

???+ note "Problem"
    The interactor picks a random integer in $[1,10^9]$. Write a program that guesses it. You may ask about an integer in $[1,10^9]$ at most $50$ times.
    
    The interactor replies:
    
    `1`: the query equals the answer; your program should stop asking.
    
    `0`: the query is less than the answer.
    
    `2`: the query is greater than the answer.

Note that in this problem we don't need `ans`, because we don't need to compare against the reference output; in other problems you may need to.

```cpp
int main(int argc, char** argv) {
  registerInteraction(argc, argv);
  int n = inf.readInt();  // the chosen number
  cout.flush();           // flush the buffer
  int left = 50;
  bool found = false;
  while (left > 0 && !found) {
    left--;
    int a = ouf.readInt(1, 1000000000);  // query
    if (a < n)
      cout << 0 << endl;
    else if (a > n)
      cout << 2 << endl;
    else
      cout << 1 << endl, found = true;
    cout.flush();
  }
  if (!found) quitf(_wa, "couldn't guess the number with 50 questions");
  ouf.readEof();
  quitf(_ok, "guessed the number with %d questions!", 50 - left);
}
```

**This article is mainly translated from [Interactors with testlib.h - Codeforces](https://codeforces.com/blog/entry/18455). The GitHub repository of `testlib.h` is [MikeMirzayanov/testlib](https://github.com/MikeMirzayanov/testlib).**
