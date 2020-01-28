#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const ll MAX = (ll)5e16;

ll xz, yz, ax, ay, bx, by, xs, ys, t;

inline ll dis(ll x1, ll y1, ll x2, ll y2) {
  return abs(x1 - x2) + abs(y1 - y2);
}

void init() {
  cin >> xz >> yz >> ax >> ay >> bx >> by >> xs >> ys >> t;
}
void solve() {
  ll x = xz, y = yz;
  vector<pair<ll, ll> > v;
  while(1) {
    if(abs(x - xs) + abs(y - ys) <= t) v.push_back({x, y});
    x = ax * x + bx;
    y = ay * y + by;
    if(x > MAX || y > MAX) break;
  }
  ll ans = 0;
  for(int i = 0 ; i < (int)v.size() ; ++i) {
    ll cnt = 0, tim = t; x = xs, y = ys;
    for(int j = i ; j >= 0 ; --j) {
      tim -= dis(x, y, v[j].F, v[j].S);
      x = v[j].F;
      y = v[j].S;
      if(tim >= 0) cnt++;
      else break;
    }
    ans = max(ans, cnt);
    cnt = 0; tim = t; x = xs, y = ys;
    for(int j = i ; j < (int)v.size() ; ++j) {
      tim -= dis(x, y, v[j].F, v[j].S);
      x = v[j].F;
      y = v[j].S;
      if(tim >= 0) cnt++;
      else break;
    }
    ans = max(ans, cnt);
  }
  cout << ans << '\n';
}

int main() {
  init();
  solve();
}
