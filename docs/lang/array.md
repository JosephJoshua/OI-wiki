An array is a container that stores objects of the same type. The objects stored in an array have no names; you access them by their position. The size of an array is fixed, and you cannot change its length freely.

## Defining an array

An array is declared in the form `a[d]`, where `a` is the name of the array and `d` is the number of elements in it. The value of `d` must be known at compile time, which means `d` must be an integral constant expression.

```cpp
unsigned int d1 = 42;
const int d2 = 42;
int arr1[d1];  // Error: d1 is not a constant expression
int arr2[d2];  // OK: arr2 is an array of length 42
```

You cannot assign one array directly to another:

```cpp
int arr1[3];
int arr2 = arr1;  // Error
arr2 = arr1;      // Error
```

You should define large arrays as global variables whenever you can. Local variables are created on the stack, and an array that is too large (larger than the stack size) will overflow the stack and cause a runtime error (RE). If you declare the array in global scope, it is created in the static storage area instead.

## Accessing array elements

You can access the elements of an array with the subscript operator `[]`. Array indices (the values inside the square brackets) start at 0. For example, an array with 10 elements has indices 0 to 9, not 1 to 10. In OI, however, for convenience we usually make the array a little bigger, skip the first element, and start accessing elements from index 1.

Example 1: read an integer $n$ from standard input, then read $n$ numbers and store them in an array. Here $n\leq 1000$.

```cpp
#include <iostream>
using namespace std;

int arr[1001];  // The index range of array arr is [0, 1001)

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
  }
}
```

Example 2: (continuing Example 1) sum the elements of array `arr` and print the sum. The sum of all elements in the array is at most $2^{31} - 1$.

```cpp
#include <iostream>
using namespace std;

int arr[1001];

int main() {
  int n;
  cin >> n;
  for (int i = 1; i <= n; ++i) {
    cin >> arr[i];
  }

  int sum = 0;
  for (int i = 1; i <= n; ++i) {
    sum += arr[i];
  }

  printf("%d\n", sum);
  return 0;
}
```

### Out-of-bounds indices

An array index $\mathit{idx}$ must satisfy $0\leq \mathit{idx}< \mathit{size}$. If the index is outside this range, the behavior is undefined and can have unpredictable results, such as a segmentation fault or changes to variables you did not mean to touch.

## Multidimensional arrays

A multidimensional array is really an "array of arrays": the elements of the outer array are themselves arrays. A two-dimensional array needs two dimensions to define it: the length of the array and the length of each element. To access a two-dimensional array, you write two indices:

```cpp
int arr[3][4];  // An array of length 3 whose elements are "arrays of length 4
                // with int elements"
arr[2][1] = 1;  // Access the two-dimensional array
```

We often use nested for loops to process two-dimensional arrays.

Example: read two numbers $n$ and $m$ from standard input, the height and width of a black-and-white picture, with $n,m\leq 1000$. Each of the next $n$ lines has $m$ space-separated numbers, giving the brightness at each position. We now read this picture and store it in a two-dimensional array.

```cpp
const int MAXN = 1001;
int pic[MAXN][MAXN];
int n, m;

cin >> n >> m;
for (int i = 1; i <= n; ++i)
  for (int j = 1; j <= m; ++j) cin >> pic[i][j];
```

In the same way, you can define three-dimensional, four-dimensional and even higher-dimensional arrays.
