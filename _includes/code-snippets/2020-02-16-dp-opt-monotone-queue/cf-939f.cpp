#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const int M = 100 + 5;
const int inf = (int)1e9;

int n, k, dp[2][2 * N];
struct Seg { int l, r; } seg[M];

void init() {
  cin >> n >> k;
  for(int i = 1 ; i <= k ; ++i) cin >> seg[i].l >> seg[i].r;
}
void solve() {
  // dp[i][j] = min_{ 0 <= k <= r_i - l_i } { dp[i - 1][r_i - j - k] + 1, dp[i - 1][j - k] + 2 }
  int cur = 1, ans = inf;
  fill(dp[0], dp[0] + n + 1, inf); dp[0][0] = 0;
  for(int i = 1 ; i <= k ; ++i) {
    deque<pair<int, int> > dq;
    copy(dp[cur ^ 1], dp[cur ^ 1] + n + 1, dp[cur]);
    int tt = seg[i].r - seg[i].l;
    for(int j = 0 ; j <= min(n, seg[i].r) ; ++j) {
      while(!dq.empty() && j - dq.front().F > tt) dq.pop_front();
      while(!dq.empty() && dp[cur ^ 1][j] <= dq.back().S) dq.pop_back();
      dq.push_back({j, dp[cur ^ 1][j]});
      dp[cur][j] = min(dp[cur][j], dq.front().S + 2);
    }
    dq.clear();
    for(int j = seg[i].r ; j >= 0 ; --j) {
      while(!dq.empty() && dq.front().F < seg[i].l - j) dq.pop_front();
      while(!dq.empty() && dp[cur ^ 1][seg[i].r - j] <= dq.back().S) dq.pop_back();
      dq.push_back({seg[i].r - j, dp[cur ^ 1][seg[i].r - j]});
      dp[cur][j] = min(dp[cur][j], dq.front().S + 1);
    }
    cur ^= 1;
  }
  ans = dp[cur ^ 1][n];
  if(ans == inf) cout << "Hungry\n";
  else cout << "Full\n" << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
