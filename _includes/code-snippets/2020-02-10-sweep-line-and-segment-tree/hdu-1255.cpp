#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <cmath>
using namespace std;
typedef long long ll;
typedef double ld;

struct Seg {
  ld l, r, y, v;

  bool operator<(const Seg& rhs) const {
    return y < rhs.y;
  }
};

const int N = (int)2e3 + 5;
const ld eps = 1e-15;

int n;
vector<ld> x;
vector<Seg> v;

namespace segtree {
  ld sum[N * 4], sum2[N * 4];
  int tag[N * 4];

  void init(int n) {
    fill(sum, sum + N * 4, 0);
    fill(sum2, sum2 + N * 4, 0);
    fill(tag, tag + N * 4, 0);
  }
  void pull(int l, int r, int o) {
    int lson = o * 2 + 1, rson = o * 2 + 2;
    if(tag[o] > 1) sum2[o] = x[r] - x[l];
    else if(l + 1 == r) sum2[o] = 0;
    else if(tag[o]) sum2[o] = sum[lson] + sum[rson];
    else sum2[o] = sum2[lson] + sum2[rson];

    if(tag[o]) sum[o] = x[r] - x[l];
    else sum[o] = (l + 1 == r ? 0 : sum[lson] + sum[rson]);
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
  ld query() {
    return sum2[0];
  }
}
int id(ld d) {
  return lower_bound(x.begin(), x.end(), d) - x.begin();
}

void init() {
  cin >> n; v.clear(); x.clear();
  for(int i = 0 ; i < n ; ++i) {
    ld l, d, r, u; cin >> l >> d >> r >> u;
    v.push_back({l, r, d, 1});
    v.push_back({l, r, u, -1});
    x.push_back(l); 
    x.push_back(r);
  }
  sort(x.begin(), x.end()); 
  x.resize(unique(x.begin(), x.end()) - x.begin());
  n = (int)x.size();
  sort(v.begin(), v.end());
  for(auto &i : v) {
    i.l = id(i.l), i.r = id(i.r);
  }
}
void solve() {
  ld ans = 0, preY = 0;
  segtree::init(n);
  for(auto i : v) {
    ans += segtree::query() * (i.y - preY);
    segtree::modify(0, n, i.l, i.r, i.v);
    preY = i.y;
  }
  cout << fixed << setprecision(2) << ans + eps << '\n';
//  cout << fixed << setprecision(2) << round(ans * 100) / 100 << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
