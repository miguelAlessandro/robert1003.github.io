#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 1;

int n, m, zero;
int cntx[2][N], cnty[2][N], cnt[2][2];
int isp[N], lpf[N];
vector<pair<int, int> > pfac[N];

void dfs(int k, ll now, int sq, ll& ansx, ll& ansy) {
  if(now >= N) return;
  if(k == (int)pfac[sq].size()) {
    ll tar = (ll)sq * sq / now;
    if(tar >= N) return;
    ansx += (cnty[0][now] && cnty[1][tar]);
    ansy += (cntx[0][now] && cntx[1][tar]);
    return;
  }
  
  int a = pfac[sq][k].F, b = pfac[sq][k].S;
  for(ll i = 0, j = 1 ; i <= b ; ++i, j *= a) {
    dfs(k + 1, now * j, sq, ansx, ansy);
  }
}

void build() {
  fill(isp, isp + N, 1);
  for(int i = 2 ; i < N ; ++i) if(isp[i]) {
    lpf[i] = i;
    if((ll)i * i < N) {
      for(int j = i * i ; j < N ; j += i) isp[j] = 0, lpf[j] = i;
    }
  }
  for(int i = 2 ; i < N ; ++i) {
    map<int, int> fac;
    int j = i;
    while(j > 1) {
      fac[lpf[j]] += 2;
      j /= lpf[j];
    }
    pfac[i] = vector<pair<int, int> > (fac.begin(), fac.end());
  }
}
void init() {
  memset(cntx, 0, sizeof(cntx));
  memset(cnty, 0, sizeof(cnty));
  memset(cnt, 0, sizeof(cnt));
  zero = 0;
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
      for(int j = 0 ; j < 2 ; ++j) {
        ans += (ll)cnt[0][i] * cnt[1][j];
      }
    }
  }
  for(int i = 1 ; i < N ; ++i) {
    ll ansx = 0, ansy = 0;
    dfs(0, 1, i, ansx, ansy);
    ans += ansx * (cntx[0][i] + cntx[1][i]);
    ans += ansy * (cnty[0][i] + cnty[1][i]);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  build();
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
