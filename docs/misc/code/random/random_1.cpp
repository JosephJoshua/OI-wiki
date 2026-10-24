constexpr int SEED = 5489u;

// --8<-- [start:core]

#include <ctime>
#include <iostream>
#include <random>

using namespace std;

int main() {
  mt19937 myrand(SEED);  // replace SEED with any integer, or with time(nullptr)
  cout << myrand() << endl;
  return 0;
}

// --8<-- [end:core]