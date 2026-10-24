#include <iostream>
constexpr int N = 16;
int is_working[N] = {0};  // whether each job is assigned
int tm[N][N];             // time needed to finish each job
int cost_time_total_min;  // minimum total time to finish the n jobs

// i is the person index, count is the total cost so far
void work(int i, int count, int n) {
  // if i exceeds the number of jobs, assignment is done; and if count is less
  // than the previous cost_time_total_min, update cost_time_total_min
  if (i > n && count < cost_time_total_min) {
    cost_time_total_min = count;
    return;
  }
  // backtracking
  if (count < cost_time_total_min) {
    // j is the job index
    for (int j = 1; j <= n; j++) {
      // if the job is not assigned, is_working = 0
      if (is_working[j] == 0) {
        // assign the job, is_working = 1
        is_working[j] = 1;
        // move on to person i + 1
        work(i + 1, count + tm[i][j], n);
        // after one round, go back to the previous person and reassign this job
        // reset is_working[j] to 0
        is_working[j] = 0;
      }
    }
  }
}

using std::cin;
using std::cout;

int main() {
  cin.tie(nullptr)->sync_with_stdio(false);
  int n;
  cin >> n;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cin >> tm[i][j];
    }
    cost_time_total_min += tm[i][i];
  }
  work(1, 0, n);
  cout << cost_time_total_min << '\n';
  return 0;
}
