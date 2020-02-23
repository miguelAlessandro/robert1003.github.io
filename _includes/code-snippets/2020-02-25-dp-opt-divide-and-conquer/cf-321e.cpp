#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 4000 + 5;
const int K = 800 + 5;
const ll inf = (ll)1e18;

ll n, k, pre[N][N], dp[K][N];

inline ll cost(int a, int b) {
  a--;
  return pre[b][b] - pre[a][b] - pre[b][a] + pre[a][a];
}
void DP(int l, int r, int ql, int qr, int kk) {
  if(l > r) return;
  int mid = l + (r - l) / 2;
  ll val = inf, pos = 0;
  for(int i = ql ; i <= min(mid - 1, qr) ; ++i) {
    ll ret = dp[kk - 1][i] + cost(i + 1, mid);
    if(ret < val) val = ret, pos = i;
  }
  dp[kk][mid] = val;
  DP(l, mid - 1, ql, pos, kk);
  DP(mid + 1, r, pos, qr, kk);
}

#define getchar getchar_unlocked
#define putchar putchar_unlocked
void rit(ll &x) {
  char c;
  while(!isdigit(c=getchar()));
  x = c - '0';
  while(isdigit(c=getchar())) x = x * 10 + c - '0';
}
char buf[100];
void wit(ll x) {
  int i = 0;
  while(x > 0) buf[i++] = '0' + (x % 10), x /= 10;
  if(i == 0) return void(putchar('0'));
  while(i > 0) putchar(buf[--i]);
}
void init() {
  rit(n); rit(k);
  //cin >> n >> k;
  for(int i = 1 ; i <= n ; ++i) {
    for(int j = 1 ; j <= n ; ++j) {
      rit(pre[i][j]);
      pre[i][j] += pre[i - 1][j] + pre[i][j - 1] - pre[i - 1][j - 1];
    }
  }
}
void solve() {
  fill(dp[0], dp[0] + N, inf);
  dp[0][0] = 0;
  for(int i = 1 ; i <= k ; ++i) {
    DP(1, n, 0, n - 1, i);
  }
  cout << dp[k][n] / 2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
