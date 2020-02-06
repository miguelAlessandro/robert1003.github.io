#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const int C = (int)1e5 + 5;
const int T = 10;
const int M = 350; // sqrt(10^5)
const ll inf = (ll)1e19;

namespace segtree {
  struct Poly {
    ll a, b, c, d = inf;
    ll operator()(ll x) { return a * x * x * x + b * x * x + c * x + d; }
  } a[T][C * 4];
  int t = -1;

  void insert(int l, int r, Poly poly, int o=0) {
    if(l + 1 == r) {
      if(poly(l) < a[t][o](l)) a[t][o] = poly;
      return;
    }
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    bool b1 = poly(mid) < a[t][o](mid), b2 = poly(l) < a[t][o](l);
    if(b1) swap(poly, a[t][o]);
    if(b1 != b2) insert(l, mid, poly, lson);
    else insert(mid, r, poly, rson);
  }
  ll query(int l, int r, int x, int o=0) {
    if(l + 1 == r) return a[t][o](x);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(x < mid) return min(a[t][o](x), query(l, mid, x, lson));
    else return min(a[t][o](x), query(mid, r, x, rson));
  }
}

ll ans[M];

void init() {
  int n; cin >> n;
  fill(ans, ans + M, inf);
  segtree::t++;
  while(n--) {
    int a, b, c, d; cin >> d >> c >> b >> a;
    segtree::Poly p = {a, b, c, d};
    segtree::insert(M, C, p);
    for(int i = 0 ; i < M ; ++i) ans[i] = min(ans[i], p(i));
  }
}
void solve() {
  int q; cin >> q;
  while(q--) {
    int x; cin >> x;
    if(x < M) cout << ans[x] << '\n';
    else cout << segtree::query(M, C, x) << '\n';
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}

