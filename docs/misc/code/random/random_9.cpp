
constexpr int SEED = 5489;

// --8<-- [start:core]

#include <iostream>
#include <random>
#include <vector>

using namespace std;

struct myrand {
  vector<unsigned int> vec;
  int l, j, k, cur;

  template <class URBG>
  myrand(int l, int j, int k, URBG &&rng) {
    this->l = l;
    this->j = j;
    this->k = k;
    cur = 0;
    for (int i = 0; i < l; i++) {
      vec.push_back(rng());  // first generate the first few elements of the sequence some other way
    }
  }

  unsigned int next() {
    vec[cur] = vec[(cur - j + l) % l] * vec[(cur - k + l) % l];
    // unsigned is used here so values are automatically taken modulo 2^32
    return vec[cur++];
  }
};

// the last one can be replaced by another random number generator, with your own seed
myrand rnd(11, 4, 7, mt19937(SEED));

int main() {
  unsigned int x = rnd.next();
  cout << x << endl;
  return 0;
}

// --8<-- [end:core]
