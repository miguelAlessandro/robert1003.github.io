#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
#pragma GCC target ("sse,sse2,sse3,ssse3,popcnt,abm,mmx,avx")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const ll is_query = -(1LL<<62);
struct Line {
  ll m, b;
  mutable function<const Line*()> succ;
  bool operator<(const Line& rhs) const {
    if (rhs.b != is_query) return m < rhs.m;
    const Line* s = succ();
    return s ? b - s->b < (s->m - m) * rhs.m : 0;
  }
}; // maintain upper hull for maximum
struct HullDynamic : public multiset<Line> {
  bool bad(iterator y) {
    auto z = next(y);
    if (y == begin()) {
      if (z == end()) return 0;
      return y->m == z->m && y->b <= z->b;
    }
    auto x = prev(y);
    if(z==end())return y->m==x->m&&y->b<=x->b;
    return (x->b-y->b)*(z->m-y->m)>=
            (y->b-z->b)*(y->m-x->m);
  }
  void insert_line(ll m, ll b) {
    auto y = insert({m, b});
    y->succ = [=]{return next(y)==end()?0:&*next(y);};
    if(bad(y)) {erase(y); return; }
    while(next(y)!=end()&&bad(next(y)))erase(next(y));
    while(y!=begin()&&bad(prev(y)))erase(prev(y));
  }
  ll eval(ll x) {
    auto l = *lower_bound((Line) {x, is_query});
    return l.m * x + l.b;
  }
} hull;

struct ATM {
  ll d, p, r, g;
};

ll n, c, d, dp;
vector<ATM> atm;

void init() {
  cin >> n >> c >> d; atm.resize(n);
  for(int i = 0 ; i < n ; ++i) {
    cin >> atm[i].d >> atm[i].p >> atm[i].r >> atm[i].g;
  }
  sort(atm.begin(), atm.end(), [&](auto a, auto b) { return a.d < b.d; });
}
void solve() {
  hull.insert_line(0, c);
  for(int i = 0 ; i < n ; ++i) {
    dp = hull.eval(atm[i].d) - atm[i].p;
    if(dp >= 0) hull.insert_line(atm[i].g, dp + atm[i].r - atm[i].g * (atm[i].d + 1));
  }
  cout << hull.eval(d + 1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
