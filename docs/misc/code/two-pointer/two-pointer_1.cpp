#include <iostream>
#include <vector>
using namespace std;

// --8<-- [start:core]
pair<bool, vector<int>> findCycle(
    vector<int>
        nxt)  // nxt[i] is the node that i points to in the singly linked list (0-indexed), -1 means it points to nothing
{
  int fast = 0, slow = 0;
  do  // first check whether there is a cycle
  {
    if (nxt[fast] == -1 || nxt[nxt[fast]] == -1) {
      return make_pair(false, vector<int>());  // no cycle
    }
    fast = nxt[nxt[fast]];
    slow = nxt[slow];
  } while (fast != slow);
  slow = 0;
  while (slow != fast)  // then find where the cycle starts
  {
    slow = nxt[slow];
    fast = nxt[fast];
  }
  vector<int> cycle;
  do  // finally collect the whole cycle
  {
    cycle.push_back(slow);
    slow = nxt[slow];
  } while (slow != fast);
  return make_pair(true, cycle);
}

// --8<-- [end:core]
int main() {
  int n;
  while (cin >> n) {
    vector<int> nxt;
    nxt.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> nxt[i];
    }
    pair<bool, vector<int>> cycle = findCycle(nxt);
    if (cycle.first) {
      cout << "Cycle:";
      for (int i = 0; i < cycle.second.size(); i++) {
        cout << " " << cycle.second[i];
      }
      cout << endl;
    } else {
      cout << "No cycle.\n";
    }
  }
}
