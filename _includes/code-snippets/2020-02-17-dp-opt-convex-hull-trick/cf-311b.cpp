#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const ll inf = (ll)1e18;

int n, m, p, d[N];
ll pre[N], preD[N], dp[2][N];
struct Cat { int h, t; ll et; } cats[N];

ll value(pair<ll, ll> line, ll x) {
  return line.F * x + line.S;
}
bool better(pair<ll, ll> L, pair<ll, ll> L1, pair<ll, ll> L2) {
  return (L1.S - L.S) * (L1.F - L2.F) <= (L2.S - L1.S) * (L.F - L1.F);
}

void init() {
  cin >> n >> m >> p;
  for(int i = 2 ; i <= n ; ++i) cin >> d[i], preD[i] = preD[i - 1] + d[i];
  for(int i = 1 ; i <= m ; ++i) {
    cin >> cats[i].h >> cats[i].t;
    cats[i].et = cats[i].t - preD[cats[i].h]; // assume >= 0
  }
  sort(cats + 1, cats + 1 + m, [&](auto a, auto b) { return a.et < b.et; });
  for(int i = 1 ; i <= m ; ++i) pre[i] = pre[i - 1] + cats[i].et;
}
void solve() {
  fill(dp[0], dp[0] + N, inf);
  fill(dp[1], dp[1] + N, inf);
  int cur = 1;
  ll ans = inf;
  for(int j = 1 ; j <= p ; ++j) {
    deque<pair<ll, ll> > dq; // <a, b>: ax + b
    dq.push_back({0, 0});
    for(int i = 1 ; i <= m ; ++i) {
      while(dq.size() >= 2 && value(dq[0], cats[i].et) > value(dq[1], cats[i].et)) dq.pop_front();
      dp[cur][i] = i * cats[i].et - pre[i] + value(dq.front(), cats[i].et);
      pair<ll, ll> line = {-i, dp[cur ^ 1][i] + pre[i]};
      while(dq.size() >= 2 && better(line, dq[dq.size() - 1], dq[dq.size() - 2])) dq.pop_back();
      dq.push_back(line);
    }
    ans = min(ans, dp[cur][m]);
    cur ^= 1;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
