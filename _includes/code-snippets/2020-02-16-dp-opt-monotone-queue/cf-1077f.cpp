#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = 5000 + 5;
const int inf = (int)1e9;

int n, k, x;
ll dp[N][N], a[N];

void init() {
  cin >> n >> k >> x;
  for(int i = 1 ; i <= n ; ++i) cin >> a[i];
}
void solve() {
  // dp[i][j] = max { dp[i - 1][j - 1], dp[i - 2][j - 1], ..., dp[i - k][j - 1] } + a[i]
  memset(dp, -0x3f, sizeof(dp));
  dp[0][0] = 0;
  for(int j = 1 ; j <= x ; ++j) {
    deque<pair<int, ll> > dq; 
    dq.push_back({j - 1, dp[j - 1][j - 1]});
    for(int i = j ; i <= n ; ++i) {
      while(!dq.empty() && dq.front().F < i - k) dq.pop_front();
      dp[i][j] = dq.front().S + a[i];
      while(!dq.empty() && dp[i][j - 1] >= dq.back().S) dq.pop_back();
      dq.push_back({i, dp[i][j - 1]});
    }
  }
  ll ans = -1;
  for(int i = 0 ; i < k ; ++i) ans = max(ans, dp[n - i][x]);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
