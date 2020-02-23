#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const int K = 20 + 5;
const ll inf = (ll)1e15;

int n, k, a[N], cnt[N];
ll dp[K][N], sum, nl, nr;

void add(int x) {
  sum += cnt[x] * 2, cnt[x]++;
}
void sub(int x) {
  sum -= cnt[x] * 2 - 2, cnt[x]--;
}
void DP(int l, int r, int ql, int qr, int now) {
  if(l > r) return;
  int mid = l + (r - l) / 2;
  ll val = inf, pos = 0;
  while(nr < mid) add(a[++nr]);
  while(nr > mid) sub(a[nr--]);
  for(int i = ql ; i <= min(mid - 1, qr) ; ++i) {
    while(nl > i + 1) add(a[--nl]);
    while(nl < i + 1) sub(a[nl++]);
    ll ret = dp[now - 1][i] + sum;
    if(ret < val) val = ret, pos = i;
  }
  dp[now][mid] = val;
  DP(l, mid - 1, ql, pos, now);
  DP(mid + 1, r, pos, qr, now);
}

void init() {
  cin >> n >> k;
  for(int i = 1 ; i <= n ; ++i) cin >> a[i];
}
void solve() {
  fill(dp[0], dp[0] + N, inf);
  dp[0][0] = 0;
  nl = 1, nr = 0;
  for(int i = 1 ; i <= k ; ++i) DP(1, n, 0, n - 1, i);
  cout << dp[k][n] / 2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
