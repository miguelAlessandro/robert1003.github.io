#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)1.5e5 + 5;
const int M = 300 + 5;
const ll inf = (ll)1e18;

int n, m, d;
struct Event { int a, b, t; } events[M];
ll dp[2][N];

void init() {
  cin >> n >> m >> d;
  for(int i = 1 ; i <= m ; ++i) cin >> events[i].a >> events[i].b >> events[i].t;
  sort(events + 1, events + 1 + m, [&](auto x, auto y) { return x.t < y.t; });
  events[0] = {0, 0, 0};
}
void solve() {
  // dp[i][j] = b_i - |a_i - j| + max_{ |k-j| <= d * (t_i - t_{i - 1}) } { dp[i - 1][k] }
  int cur = 1;
  for(int i = 1 ; i <= m ; ++i) {
    ll tt = events[i].t - events[i - 1].t, k = 1;
    deque<pair<int, ll> > dq;
    for(int j = 1 ; j <= n ; ++j) {
      while(!dq.empty() && abs(dq.front().F - j) > tt * d) dq.pop_front();
      while(k <= n && abs(k - j) <= tt * d) {
        while(!dq.empty() && dp[cur ^ 1][k] > dq.back().S) dq.pop_back();
        dq.push_back({k, dp[cur ^ 1][k]}), k++;
      }
      dp[cur][j] = (ll)events[i].b - abs(events[i].a - j) + dq.front().S;
    }
    cur ^= 1;
  }
  ll ans = -inf;
  for(int i = 1 ; i <= n ; ++i) ans = max(ans, dp[cur ^ 1][i]);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
