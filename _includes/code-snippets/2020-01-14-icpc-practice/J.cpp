#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 2000 + 5;
const int M = 2000 + 5;
const int mod = (int)1e9 + 7;

int n, k, m, dp[N][M];

void init() {
  cin >> n >> k >> m;
}
void solve() {
  dp[0][0] = 1;
  for(int i = 1 ; i <= m ; ++i) {
    for(int j = 0 ; j <= k ; ++j) {
      dp[i][j] = 0;
      if(j < k) dp[i][j] = (dp[i][j] + dp[i - 1][j + 1]) % mod;
      if(j > 0) dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % mod;
    }
  }
  ll ans = 0;
  for(int i = 2 ; i <= m ; i += 2) ans = (ans + dp[i][0]) % mod;
  ans = ans * 2 % mod * n % mod;
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
