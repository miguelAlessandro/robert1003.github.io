#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#pragma GCC target ("avx,avx2")
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

struct ATM {
  ll d, p, r, g;
};

const int N = (int)1e5 + 5;
const ll inf = (ll)1e19;

ll n, c, d, dp[N];
vector<ATM> atm;

ll eval(pair<ll, ll>& p, ll v) {
  return p.F * v + p.S;
}
bool check(pair<ll, ll>& a, pair<ll, ll>& b, pair<ll, ll>& c) {
  return (__int128)(b.S - a.S) * (b.F - c.F) <= (__int128)(c.S - b.S) * (a.F - b.F);
}
void add(vector<pair<ll, ll> >& v, pair<ll, ll> l) {
  while((int)v.size() >= 2 && check(l, v[v.size() - 1], v[v.size() - 2])) v.pop_back();
  v.push_back(l);
}
vector<pair<ll, ll> > cdq(int l, int r) {
  if(l + 1 == r) {
    if(dp[l] >= 0) return {{atm[l].g, dp[l] - (atm[l].d + 1) * atm[l].g + atm[l].r}};
    else return {};
  }
  int m = (l + r) >> 1;
  vector<pair<ll, ll> > l1 = cdq(l, m);
  for(int i = m, j = 0 ; l1.size() && i < r ; ++i) {
    while(j + 1 < (int)l1.size() && eval(l1[j], atm[i].d) < eval(l1[j + 1], atm[i].d)) ++j;
    dp[i] = max(dp[i], eval(l1[j], atm[i].d) - atm[i].p);
  }
  vector<pair<ll, ll > > l2 = cdq(m, r);
  vector<pair<ll, ll > > l3;
  int a = 0, b = 0;
  while(a < (int)l1.size() && b < (int)l2.size()) {
    if(l1[a] < l2[b]) add(l3, l1[a++]);
    else add(l3, l2[b++]);
  }
  while(a < (int)l1.size()) add(l3, l1[a++]);
  while(b < (int)l2.size()) add(l3, l2[b++]);
  vector<pair<ll, ll> > ().swap(l1);
  vector<pair<ll, ll> > ().swap(l2);
  return l3;
}

void init() {
  cin >> n >> c >> d; atm.resize(n + 2);
  atm[0] = {0, 0, c, 0};
  for(int i = 1 ; i <= n ; ++i) {
    cin >> atm[i].d >> atm[i].p >> atm[i].r >> atm[i].g;
  }
  atm[n + 1] = {d + 1, 0, 0, 0};
  sort(atm.begin(), atm.end(), [&](auto a, auto b) { return a.d < b.d; });
}
void solve() {
  fill(dp, dp + n + 2, -inf);
  dp[0] = 0;
  cdq(0, n + 2);
  cout << dp[n + 1] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
