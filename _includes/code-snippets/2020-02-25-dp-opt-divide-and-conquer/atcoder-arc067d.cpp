#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 5000 + 5;
const int lgN = 13;
const int M = 200 + 5;
const ll inf = (ll)1e18;

int n, m, B[M][N][lgN];
ll dp[N], A[N];

ll query(int x, int l, int r) {
  int k = __lg(r - l + 1);
  return max(B[x][l][k], B[x][r - (1 << k) + 1][k]);
}
ll calc(int l, int r) {
  ll sum = 0;
  for(int i = 1 ; i <= m ; ++i) sum += query(i, l, r);
  return sum - (A[r] - A[l]);
}
void DP(int l, int r, int ql, int qr) {
  if(l > r) return;
  int mid = l + (r - l) / 2;
  ll val = -inf, pos = 0;
  for(int i = ql ; i <= min(mid, qr) ; ++i) {
    ll ret = calc(i, mid);
    if(ret > val) val = ret, pos = i;
  }
  dp[mid] = val;
  DP(l, mid - 1, ql, pos);
  DP(mid + 1, r, pos, qr);
}

void init() {
  cin >> n >> m;
  for(int i = 2 ; i <= n ; ++i) cin >> A[i], A[i] += A[i - 1];
  for(int i = 1 ; i <= n ; ++i) {
    for(int j = 1 ; j <= m ; ++j) cin >> B[j][i][0];
  }
  for(int k = 1 ; k <= m ; ++k) {
    for(int j = 1 ; (1 << j) <= n ; ++j) {
      for(int i = 1 ; i + (1 << j) - 1 <= n ; ++i) {
        B[k][i][j] = max(B[k][i][j - 1], B[k][i + (1 << (j - 1))][j - 1]);
      }
    }
  }
}
void solve() {
  DP(1, n, 1, n);
  ll ans = -inf;
  for(int i = 1 ; i <= n ; ++i) ans = max(ans, dp[i]);
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
