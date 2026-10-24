#include <cstdint>
#include <vector>
using i32 = int32_t;
using u32 = uint32_t;

class dsu {
  // p[i] < 0 means i is a root, and its subtree size is -p[i]
  // p[i] >= 0 means i is not a root, and its parent is p[i]
  std::vector<i32> p;

 public:
  // nodes are numbered from 0 to sz-1
  explicit dsu(u32 sz) : p(sz, -1) {}

  i32 find(u32 x) { return p[x] < 0 ? (i32)x : p[x] = find((u32)p[x]); }

  u32 size(u32 x) { return (u32)-p[(u32)find(x)]; }

  bool same_root(u32 x, u32 y) { return find(x) == find(y); }

  bool merge(u32 x, u32 y) {
    if ((x = (u32)find(x)) == (y = (u32)find(y))) return false;
    if (p[x] > p[y]) std::swap(x, y);  // union by size
    p[x] += p[y], p[y] = (i32)x;
    return true;
  }
};