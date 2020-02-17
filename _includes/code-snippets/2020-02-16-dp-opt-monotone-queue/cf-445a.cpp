#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;

ll n, c, cnt[N], dp[N];

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) {
    ll x; cin >> x; cnt[x]++;
    c = max(c, x);
  }
}
void solve() {
  // dp[i] = max { dp[i - 1], cnt[i] * i + max_{j, j < i - 1} { dp[j] } }
  dp[0] = 0;
  ll mx = 0, ans = 0;
  for(int i = 1 ; i <= c ; ++i) {
    dp[i] = max(dp[i - 1], cnt[i] * i + mx);
    mx = max(mx, dp[i - 1]);
    ans = max(ans, dp[i]);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
