#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;

struct Line {
  mutable ll m, b, p;
  bool operator<(const Line& o) const { return m < o.m; }
  bool operator<(ll x) const { return p < x; }
};

struct LineContainer : multiset<Line, less<>> {
  // (for doubles, use inf = 1/.0, div(a,b) = a/b)
  const ll inf = LLONG_MAX;
  ll div(ll a, ll b) { // floored division
    return a / b - ((a ^ b) < 0 && a % b);
  }
  bool isect(iterator x, iterator y) {
    if (y == end()) { x->p = inf; return false; }
    if (x->m == y->m) x->p = x->b > y->b ? inf : -inf;
    else x->p = div(y->b - x->b, x->m - y->m);
    return x->p >= y->p;
  }
  void add(ll m, ll b) {
    auto z = insert({m, b, 0}), y = z++, x = y;
    while (isect(y, z)) z = erase(z);
    if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
    while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
  }
  ll query(ll x) {
    assert(!empty());
    auto l = *lower_bound(x);
    return l.m * x + l.b;
  }
} cht;

ll n, a[N], sum[N], pre[N], dp[N];

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) {
    cin >> a[i];
    sum[i] = sum[i - 1] + a[i];
    pre[i] = pre[i - 1] + a[i] * i;
  }
}
void solve() {
  ll ans = pre[n];
  for(int i = 2 ; i <= n ; ++i) {
    // dp[i] = max(dp[i], pre[n] + sum[i - 1] - sum[j - 1] - a[i] * i + a[i] * j);
    cht.add(i - 1, -sum[i - 2]);
    dp[i] = pre[n] + sum[i - 1] - a[i] * i + cht.query(a[i]);
    ans = max(ans, dp[i]);
  }
  cht.clear();
  for(int i = n - 1 ; i >= 1 ; --i) {
    // dp[i] = max(dp[i], pre[n] - sum[j] + sum[i] - a[i] * i + a[i] * j);
    cht.add(i + 1, -sum[i + 1]);
    dp[i] = pre[n] + sum[i] - a[i] * i + cht.query(a[i]);
    ans = max(ans, dp[i]);
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
