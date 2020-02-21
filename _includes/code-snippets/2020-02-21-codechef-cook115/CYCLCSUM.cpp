#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e6 + 5;
const ll inf = (ll)1e15;

namespace segtree {
  struct Node {
    ll lsum, msum, rsum, ans;
  } a[N * 4];

  void init(int n) {
    for(int i = 0 ; i <= n * 4 ; ++i) {
      a[i] = {-inf, -inf, -inf, -inf};
    }
  }
  Node merge(Node x, Node y) {
    Node z;
    z.lsum = max(x.lsum, x.msum + y.lsum);
    z.msum = x.msum + y.msum;
    z.rsum = max(x.rsum + y.msum, y.rsum);
    z.ans = max(x.rsum + y.lsum, max(x.ans, y.ans));
    return z;
  }
  void modify(int l, int r, int q, ll v, int o=0) {
    if(l + 1 == r) {
      a[o] = {v, v, v, v};
      return;
    }
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(q < mid) modify(l, mid, q, v, lson);
    else modify(mid, r, q, v, rson);
    a[o] = merge(a[lson], a[rson]);
  }
  Node query(int l, int r, int ql, int qr, int o=0) {
    if(ql <= l && r <= qr) return a[o];
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(qr <= mid) return query(l, mid, ql, qr, lson);
    else if(mid <= ql) return query(mid, r, ql, qr, rson);
    else {
      return merge(query(l, mid, ql, mid, lson), query(mid, r, mid, qr, rson));
    }
  }
}

int n, a[N];

void init() {
  cin >> n;
  segtree::init(n * 2);
  for(int i = 1 ; i <= n ; ++i) {
    cin >> a[i];
    segtree::modify(1, n * 2 + 1, i, a[i]);
    segtree::modify(1, n * 2 + 1, i + n, a[i]);
  }
}
void solve() {
  for(int i = 1 ; i <= n ; ++i) {
    cout << segtree::query(1, n * 2 + 1, i, i + n).ans << " \n"[i == n];
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
