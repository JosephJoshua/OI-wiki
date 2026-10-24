#include <cstdio>
#include <cstring>
#include <queue>
using namespace std;

constexpr int N = 2e5 + 6;
constexpr int LEN = 2e6 + 6;
constexpr int SIZE = 2e5 + 6;

int n;

namespace AC {
struct Node {
  int son[26];  // children
  int ans;      // match count
  int fail;     // fail pointer
  int du;       // in-degree
  int idx;

  void init() {  // initialize node
    memset(son, 0, sizeof(son));
    ans = fail = idx = 0;
  }
} tr[SIZE];

int tot;  // total number of nodes
int ans[N], pidx;

void init() {
  tot = pidx = 0;
  tr[0].init();
}

void insert(char s[], int &idx) {
  int u = 0;
  for (int i = 1; s[i]; i++) {
    int &son = tr[u].son[s[i] - 'a'];  // reference to the next child
    if (!son) son = ++tot, tr[son].init();  // if missing, insert a new node and initialize it
    u = son;                                // continue from the next node
  }
  // identical patterns may appear, so map them to the same id
  if (!tr[u].idx) tr[u].idx = ++pidx;  // first occurrence, assign a new id
  idx = tr[u].idx;  // the id of this pattern is the id of this node
}

void build() {
  queue<int> q;
  for (int i = 0; i < 26; i++)
    if (tr[0].son[i]) q.push(tr[0].son[i]);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < 26; i++) {
      if (tr[u].son[i]) {                               // child exists
        tr[tr[u].son[i]].fail = tr[tr[u].fail].son[i];  // only one fail jump needed
        tr[tr[tr[u].fail].son[i]].du++;                 // count in-degree
        q.push(tr[u].son[i]);                           // and push it into the queue
      } else
        tr[u].son[i] =
            tr[tr[u].fail]
                .son[i];  // link a missing trie state to the matching state of the fail pointer
    }
  }
}

void query(char t[]) {
  int u = 0;
  for (int i = 1; t[i]; i++) {
    u = tr[u].son[t[i] - 'a'];  // transition
    tr[u].ans++;
  }
}

void topu() {
  queue<int> q;
  for (int i = 0; i <= tot; i++)
    if (tr[i].du == 0) q.push(i);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    ans[tr[u].idx] = tr[u].ans;
    int v = tr[u].fail;
    tr[v].ans += tr[u].ans;
    if (!--tr[v].du) q.push(v);
  }
}
}  // namespace AC

char s[LEN];
int idx[N];

int main() {
  AC::init();
  scanf("%d", &n);
  for (int i = 1; i <= n; i++) {
    scanf("%s", s + 1);
    AC::insert(s, idx[i]);
    AC::ans[i] = 0;
  }
  AC::build();
  scanf("%s", s + 1);
  AC::query(s);
  AC::topu();
  for (int i = 1; i <= n; i++) {
    printf("%d\n", AC::ans[idx[i]]);
  }
  return 0;
}
