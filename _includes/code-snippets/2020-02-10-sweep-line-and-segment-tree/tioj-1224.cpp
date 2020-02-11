#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e6 + 5;

namespace segtree {
  int sum[N * 4], tag[N * 4];

  void pull(int l, int r, int o) {
    if(tag[o]) sum[o] = r - l;
    else sum[o] = (l + 1 == r ? 0 : sum[o * 2 + 1] + sum[o * 2 + 2]);
  }
  void modify(int l, int r, int ql, int qr, int v, int o=0) {
    if(ql <= l && r <= qr) {
      tag[o] += v;
    }
    else {
      int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
      if(qr <= mid) modify(l, mid, ql, qr, v, lson);
      else if(mid <= ql) modify(mid, r, ql, qr, v, rson);
      else {
        modify(l, mid, ql, mid, v, lson);
        modify(mid, r, mid, qr, v, rson);
      }
    }
    pull(l, r, o);
  }
  int query() {
    return sum[0];
  }
}

struct Seg {
  int l, r, y, v;

  bool operator<(const Seg& rhs) const {
    return y < rhs.y;
  }
};

int n;
vector<Seg> v;

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    int l, r, d, u; cin >> l >> r >> d >> u;
    v.push_back({l, r, d, 1});
    v.push_back({l, r, u, -1});
  }
  sort(v.begin(), v.end());
}
void solve() {
  ll ans = 0, preY = 0;
  for(auto [ql, qr, y, val] : v) {
    ans += segtree::query() * (y - preY);
    segtree::modify(0, 1000000, ql, qr, val);
    preY = y;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
