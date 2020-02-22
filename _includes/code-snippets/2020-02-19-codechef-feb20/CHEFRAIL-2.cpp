#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 1;
const int sqN = 320;

int n, m, cntx[2][N], cnty[2][N], cnt[2][2], zero;

inline int gcd(int a, int b) {
  return !b ? a : gcd(b, a % b);
}

void init() {
  zero = 0;
  memset(cnt, 0, sizeof(cnt));
  memset(cntx, 0, sizeof(cntx));
  memset(cnty, 0, sizeof(cnty));
  cin >> n >> m;
  for(int i = 0 ; i < n ; ++i) {
    int a; cin >> a;
    if(a > 0) cntx[0][a]++, cnt[0][0]++;
    else if(a < 0) cntx[1][-a]++, cnt[0][1]++;
    else zero++;
  }
  for(int i = 0 ; i < m ; ++i) {
    int a; cin >> a;
    if(a > 0) cnty[0][a]++, cnt[1][0]++;
    else if(a < 0) cnty[1][-a]++, cnt[1][1]++;
    else zero++;
  }
}
void solve() {
  ll ans = 0;
  if(zero) {
    for(int i = 0 ; i < 2 ; ++i) {
      for(int j = 0 ; j < 2 ; ++j) ans += (ll)cnt[0][i] * cnt[1][j];
    }
  }
  for(int i = 1 ; i < sqN ; ++i) {
    for(int j = 1 ; j < sqN ; ++j) {
      int g = gcd(i, j), mx = max(i, j);
      if(g != 1) continue;
      for(int k = 1 ; (ll)k * mx * mx < N ; ++k) {
        ans += (cntx[0][k * i * j] + cntx[1][k * i * j]) * (cnty[0][k * i * i] && cnty[1][k * j * j]);
        ans += (cnty[0][k * i * j] + cnty[1][k * i * j]) * (cntx[0][k * i * i] && cntx[1][k * j * j]);
      }
    }
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
