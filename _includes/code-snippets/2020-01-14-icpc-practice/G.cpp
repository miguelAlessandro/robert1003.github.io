#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const ll inf = (ll)2e18;

namespace segtree {
  struct Node {
    ll alive, a, b, mn;

    Node(){}
    Node(ll _alive, ll _a, ll _b, ll _mn): alive(_alive), a(_a), b(_b), mn(_mn) {}
  } node[N * 4];
  int n;

  void init(int _n) {
    n = _n;
  }
  void pull(int o) {
    int lson = o * 2 + 1, rson = o * 2 + 2;
    node[o].alive = node[lson].alive + node[rson].alive;
    node[o].a = node[lson].a + node[rson].a;
    node[o].mn = min(node[lson].mn, node[lson].a + node[rson].mn);
  }
  void modify(int l, int r, Node v, int x, int o=0) {
    if(l + 1 == r) return void(node[o] = v);
    int lson = o * 2 + 1, rson = o * 2 + 2, mid = (l + r) / 2;
    if(x < mid) modify(l, mid, v, x, lson);
    else modify(mid, r, v, x, rson);
    pull(o);
  }
  void kill(int l, int r, ll sum, ll x, int o=0) {
    if(l + 1 == r) {
      if(sum + node[o].mn < x) node[o] = Node(0, 0, inf, inf);
      return;
    }
    int lson = o * 2 + 1, rson = o * 2 + 2, mid = (l + r) / 2;
    if(sum + node[lson].a + node[rson].mn < x) kill(mid, r, sum + node[lson].a, x, rson); // R first
    if(sum + node[lson].mn < x) kill(l, mid, sum, x, lson); // L second
    pull(o);
  }
  int feed(int l, int r, ll sum, ll x, int o=0) {
    if(l + 1 == r) {
      if(sum + node[o].a <= x) return node[o].alive;
      return 0;
    }
    int lson = o * 2 + 1, rson = o * 2 + 2, mid = (l + r) / 2;
    if(sum + node[lson].a > x) return feed(l, mid, sum, x, lson);
    else return node[lson].alive + feed(mid, r, sum + node[lson].a, x, rson);
  }
}

int n;

void init() {
  cin >> n; segtree::init(n);
  for(int i = 0 ; i < n ; ++i) {
    ll a, b; cin >> a >> b;
    segtree::modify(1, n + 1, segtree::Node(1, a, b, a + b), i + 1);
  }
}
void solve() {
  int q; cin >> q;
  while(q--) {
    int op; cin >> op;
    if(op == 1) {
      ll x; cin >> x;
      ll b = segtree::node[0].alive - segtree::feed(1, n + 1, 0, x), tmp = segtree::node[0].alive;
      segtree::kill(1, n + 1, 0, x);
      ll a = tmp - segtree::node[0].alive;
      cout << a << ' ' << b << '\n';
    }
    else {
      ll a, b, c; cin >> a >> b >> c;
      segtree::modify(1, n + 1, segtree::Node(1, a, b, a + b), c);
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
