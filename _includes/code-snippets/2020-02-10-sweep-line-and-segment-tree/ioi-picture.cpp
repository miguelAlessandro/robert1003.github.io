#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 10000 + 5;

namespace segtree {
  int sum[N * 8], len[N * 8], tag[N * 8];
  bool lp[N * 8], rp[N * 8];

  void pull(int l, int r, int o) {
    if(tag[o]) sum[o] = lp[o] = rp[o] = 1, len[o] = r - l;
    else if(l + 1 == r) sum[o] = len[o] = lp[o] = rp[o] = 0;
    else {
      int lson = o * 2 + 1, rson = o * 2 + 2;
      sum[o] = sum[lson] + sum[rson] - (rp[lson] && lp[rson]);
      len[o] = len[lson] + len[rson];
      lp[o] = lp[lson], rp[o] = rp[rson];
    }
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
  int qsum() {
    return sum[0];
  }
  int qlen() {
    return len[0];
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
    int l, d, r, u; cin >> l >> d >> r >> u;
    v.push_back({l, r, d, 1});
    v.push_back({l, r, u, -1});
  }
  sort(v.begin(), v.end());
}
void solve() {
  int ans = 0, preY = 0;
  for(auto i : v) {
    ans += segtree::qsum() * 2 * (i.y - preY);
    int tt = segtree::qlen();
    segtree::modify(-N, N, i.l, i.r, i.v);
    ans += abs(tt - segtree::qlen());
    preY = i.y;
  }
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
