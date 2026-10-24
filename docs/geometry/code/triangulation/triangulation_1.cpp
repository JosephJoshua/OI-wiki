// --8<-- [start:delaunay]
#include <algorithm>
#include <cmath>
#include <limits>
#include <utility>
#include <vector>

using data_t = double;

struct Point {
  data_t x, y;
  int id;
};

class Delaunay {
  // each undirected edge consists of four slots
  // even slots are the two directions in the original graph, odd slots are dual edges
  // all links store indices, to avoid iterator invalidation
  struct Edge {
    int origin, next;
  };

  std::vector<Point> p;
  std::vector<Edge> edges;
  std::vector<int> free_edges;

  // use a relative tolerance to approximate the sign
  static int sign(data_t value, data_t scale) {
    const data_t tolerance =
        16 * std::numeric_limits<data_t>::epsilon() * scale;
    return (value > tolerance) - (value < -tolerance);
  }

  static int cross(const Point& a, const Point& b, const Point& c) {
    data_t u = (b.x - a.x) * (c.y - a.y);
    data_t v = (b.y - a.y) * (c.x - a.x);
    return sign(u - v, std::abs(u) + std::abs(v));
  }

  // with a, b, c in counterclockwise order, check whether d is inside their circumcircle
  static bool in_circle(const Point& a, const Point& b, const Point& c,
                        const Point& d) {
    data_t ax = a.x - d.x, ay = a.y - d.y;
    data_t bx = b.x - d.x, by = b.y - d.y;
    data_t cx = c.x - d.x, cy = c.y - d.y;
    data_t a2 = ax * ax + ay * ay, b2 = bx * bx + by * by,
           c2 = cx * cx + cy * cy;
    data_t bc1 = bx * cy, bc2 = by * cx;
    data_t ca1 = cx * ay, ca2 = cy * ax;
    data_t ab1 = ax * by, ab2 = ay * bx;
    data_t det = a2 * (bc1 - bc2) + b2 * (ca1 - ca2) + c2 * (ab1 - ab2);
    // accumulate absolute values before subtracting, so cancellation does not make us underestimate rounding error
    data_t scale = a2 * (std::abs(bc1) + std::abs(bc2)) +
                   b2 * (std::abs(ca1) + std::abs(ca2)) +
                   c2 * (std::abs(ab1) + std::abs(ab2));
    return sign(det, scale) > 0;
  }

  static int rot(int e) { return (e & ~3) | ((e + 1) & 3); }

  static int rev(int e) { return e ^ 2; }

  int org(int e) const { return edges[e].origin; }

  int dest(int e) const { return org(rev(e)); }

  // edges with the same origin form a circular linked list in counterclockwise order
  int onext(int e) const { return edges[e].next; }

  int oprev(int e) const { return rot(onext(rot(e))); }

  // move one edge forward along the boundary of the face to the left of e
  int lnext(int e) const { return rot(onext(rev(rot(e)))); }

  bool left_of(int v, int e) const {
    return cross(p[org(e)], p[dest(e)], p[v]) > 0;
  }

  bool right_of(int v, int e) const {
    return cross(p[org(e)], p[dest(e)], p[v]) < 0;
  }

  int make_edge(int u, int v) {
    int e;
    if (free_edges.empty()) {
      e = (int)edges.size();
      edges.resize(edges.size() + 4);
    } else {
      e = free_edges.back();
      free_edges.pop_back();
    }
    edges[e] = {u, e};
    edges[e + 1] = {-1, e + 3};
    edges[e + 2] = {v, e + 2};
    edges[e + 3] = {-1, e + 1};
    return e;
  }

  // swap the successors of two edges and update the links of the dual graph
  void splice(int a, int b) {
    int alpha = rot(onext(a)), beta = rot(onext(b));
    std::swap(edges[a].next, edges[b].next);
    std::swap(edges[alpha].next, edges[beta].next);
  }

  void delete_edge(int e) {
    splice(e, oprev(e));
    splice(rev(e), oprev(rev(e)));
    e &= ~3;
    edges[e].origin = edges[e + 2].origin = -1;
    free_edges.push_back(e);
  }

  // add an edge from the end of a to the start of b
  int connect(int a, int b) {
    int e = make_edge(dest(a), org(b));
    splice(e, lnext(a));
    splice(rev(e), b);
    return e;
  }

  // return the hull edges starting at the leftmost and rightmost vertices, with the outer face on the right and left respectively
  // ranges are [l, r); the recursion only handles ranges with at least two points
  std::pair<int, int> divide(int l, int r) {
    if (r - l == 2) {
      int a = make_edge(l, l + 1);
      return {a, rev(a)};
    }
    if (r - l == 3) {
      int a = make_edge(l, l + 1), b = make_edge(l + 1, l + 2);
      splice(rev(a), b);
      int turn = cross(p[l], p[l + 1], p[l + 2]);
      if (turn == 0) return {a, rev(b)};  // if collinear, only connect adjacent points
      int c = connect(b, a);
      if (turn > 0) return {a, rev(b)};
      return {rev(c), c};
    }

    int m = l + (r - l) / 2;
    auto left = divide(l, m), right = divide(m, r);
    int ldo = left.first, ldi = left.second;
    int rdi = right.first, rdo = right.second;
    // starting from the hull edges returned by the recursion, walk along the hulls to find the lower common tangent
    while (true) {
      if (left_of(org(rdi), ldi)) {
        ldi = lnext(ldi);
      } else if (right_of(org(ldi), rdi)) {
        rdi = onext(rev(rdi));
      } else {
        break;
      }
    }
    int base = connect(rev(rdi), ldi);  // base points from the right side to the left side
    if (org(ldi) == org(ldo)) ldo = rev(base);
    if (org(rdi) == org(rdo)) rdo = base;

    while (true) {
      // candidate edges come from the ordered circular adjacency lists, so we only need the predecessor or successor of the current edge
      int lcand = onext(rev(base));
      if (right_of(dest(lcand), base)) {
        while (in_circle(p[dest(base)], p[org(base)], p[dest(lcand)],
                         p[dest(onext(lcand))])) {
          int next = onext(lcand);
          delete_edge(lcand);
          lcand = next;
        }
      }
      int rcand = oprev(base);
      if (right_of(dest(rcand), base)) {
        while (in_circle(p[dest(base)], p[org(base)], p[dest(rcand)],
                         p[dest(oprev(rcand))])) {
          int prev = oprev(rcand);
          delete_edge(rcand);
          rcand = prev;
        }
      }
      bool lvalid = right_of(dest(lcand), base);
      bool rvalid = right_of(dest(rcand), base);
      if (!lvalid && !rvalid) break;  // reached the upper common tangent
      if (!lvalid || (rvalid && in_circle(p[dest(lcand)], p[org(lcand)],
                                          p[org(rcand)], p[dest(rcand)]))) {
        base = connect(rcand, rev(base));
      } else {
        base = connect(rev(base), rev(lcand));
      }
    }
    return {ldo, rdo};
  }

 public:
  // points must be distinct, and ids must be distinct
  void init(std::vector<Point> points) {
    p = std::move(points);
    edges.clear();
    free_edges.clear();
    std::sort(p.begin(), p.end(), [](const Point& a, const Point& b) {
      return a.x < b.x || (a.x == b.x && a.y < b.y);
    });
    if (p.size() >= 2) divide(0, (int)p.size());
  }

  // each undirected edge is returned once; endpoints are labeled with the original input ids
  std::vector<std::pair<int, int>> getEdge() const {
    std::vector<std::pair<int, int>> result;
    for (int e = 0; e < (int)edges.size(); e += 4) {
      if (org(e) != -1) result.emplace_back(p[org(e)].id, p[dest(e)].id);
    }
    return result;
  }
};

// --8<-- [end:delaunay]

#include <iostream>

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  if (!(std::cin >> n)) return 0;
  std::vector<Point> points(n);
  for (int i = 0; i < n; ++i) {
    std::cin >> points[i].x >> points[i].y;
    points[i].id = i;
  }
  Delaunay dt;
  dt.init(std::move(points));
  auto edges = dt.getEdge();
  for (auto& edge : edges) {
    if (edge.first > edge.second) std::swap(edge.first, edge.second);
  }
  std::sort(edges.begin(), edges.end());
  std::cout << edges.size() << '\n';
  for (const auto& edge : edges) {
    std::cout << edge.first << ' ' << edge.second << '\n';
  }
}
