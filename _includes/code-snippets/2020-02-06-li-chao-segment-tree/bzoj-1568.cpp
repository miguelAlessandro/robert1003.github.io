#include <iostream>
using namespace std;
typedef long long ll;
typedef long double ld;

const int C = (int)5e4 + 5;

namespace segtree {
  struct Line {
    ld m, b;
    ld operator()(ld x) { return m * x + b; }
  } a[C * 4];
  
  void insert(int l, int r, Line seg, int o=0) {
    if(l + 1 == r) {
      if(seg(l) > a[o](l)) a[o] = seg;
      return;
    }
    int mid= (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(a[o].m > seg.m) swap(a[o], seg);
    if(a[o](mid) < seg(mid)) {
      swap(a[o], seg);
      insert(l, mid, seg, lson);
    }
    else insert(mid, r, seg, rson);
  }
  ld query(int l, int r, int x, int o=0) {
    if(l + 1 == r) return a[o](x);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(x < mid) return max(a[o](x), query(l, mid, x, lson));
    else return max(a[o](x), query(mid, r, x, rson));
  }
}

void init() {
}
void solve() {
  int q; cin >> q;
  while(q--) {
    string s; cin >> s;
    if(s[0] == 'P') {
      ld b, m; cin >> b >> m;
      segtree::insert(1, C, {m, b - m});
    }
    else {
      int x; cin >> x;
      cout << (int)(segtree::query(1, C, x) / 100) << '\n';
    }
  }
}

int main() {
  ios_base::sync_with_stdio(0);
  init();
  solve();
}
