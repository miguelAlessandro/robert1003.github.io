#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;

namespace segtree {
  struct Line {
    mutable ll k, m, p;
    bool operator<(const Line& o) const { return k < o.k; }
    bool operator<(ll x) const { return p < x; }
  };
  struct LineContainer : multiset<Line, less<>> {
    // (for doubles, use inf = 1/.0, div(a,b) = a/b)
    const ll inf = LLONG_MAX;
    ll div(ll a, ll b) { // floored division
      return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
      if (y == end()) { x->p = inf; return false; }
      if (x->k == y->k) x->p = x->m > y->m ? inf : -inf;
      else x->p = div(y->m - x->m, x->k - y->k);
      return x->p >= y->p;
    }
    void add(ll k, ll m) {
      auto z = insert({k, m, 0}), y = z++, x = y;
      while (isect(y, z)) z = erase(z);
      if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
      while ((y = x) != begin() && (--x)->p >= y->p)
        isect(x, erase(y));
    }
    ll query(ll x) {
      assert(!empty());
      auto l = *lower_bound(x);
      return l.k * x + l.m;
    }
  } cht[N * 4];

  void insert(int l, int r, int q, ll m, ll b, int o=0) {
    cht[o].add(-m, -b);
    if(l + 1 == r) return;
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(q < mid) insert(l, mid, q, m, b, lson);
    else insert(mid, r, q, m, b, rson);
  }
  ll query(int l, int r, int ql, int qr, ll x, int o=0) {
    if(ql <= l && r <= qr) {
      return cht[o].query(x);
    }
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(qr <= mid) return query(l, mid, ql, qr, x, lson);
    else if(mid <= ql) return query(mid, r, ql, qr, x, rson);
    else return max(query(l, mid, ql, mid, x, lson), query(mid, r, mid, qr, x, rson));
  }
}

ll n, a[N], sum[N];

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) {
    cin >> a[i], sum[i] = sum[i - 1] + a[i];
    segtree::insert(1, n + 1, i, a[i], a[i] * i - sum[i]);
  }
}
void solve() {
  int q; cin >> q;
  while(q--) {
    ll x, y; cin >> x >> y;
    cout << sum[y] - segtree::query(1, n + 1, y - x + 1, y + 1, x - y) << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
