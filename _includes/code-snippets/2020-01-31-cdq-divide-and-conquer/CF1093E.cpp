#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;

namespace bit {
  int n, b[N];

  void init(int _n) {
    n = _n;
    fill(b, b + n + 1, 0);
  }
  inline int lowbit(int x) { return x & (-x); }
  void update(int x, int v) {
    if(x == 0) return;
    for(int i = x ; i <= n ; i += lowbit(i)) b[i] += v;
  }
  int query(int x) {
    int ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += b[i];
    return ans;
  }
}
struct Node {
  int t, x, y, i, sgn, v;
};

vector<Node> Q;
vector<int> ans;

void cdq(int l, int r) {
  if(l + 1 == r) return;
  int m = (l + r) >> 1;
  cdq(l, m); cdq(m, r);
  vector<Node> tmp;
  vector<pair<int, int> > his;
  int a = l, b = m;
  while(a < m || b < r) {
    if(b == r || (a < m && Q[a].x <= Q[b].x)) {
      bit::update(Q[a].y, Q[a].v);
      his.push_back({Q[a].y, Q[a].v});
      tmp.push_back(Q[a++]);
    }
    else {
      ans[Q[b].i] += Q[b].sgn * bit::query(Q[b].y);
      tmp.push_back(Q[b++]);
    }
  }
  for(auto [x, v] : his) bit::update(x, -v);
  for(int i = l ; i < r ; ++i) Q[i] = tmp[i - l];
  vector<Node> ().swap(tmp);
  vector<pair<int, int> > ().swap(his);
}

void init() {
  int n, m; cin >> n >> m;
  bit::init(n);
  vector<int> a(n + 1), b(n + 1), pos(n + 1);
  for(int i = 1 ; i <= n ; ++i) cin >> a[i], pos[a[i]] = i;
  for(int i = 1 ; i <= n ; ++i) cin >> b[i];
  Q.clear();
  ans.push_back(0);
  for(int i = 1 ; i <= n ; ++i) Q.push_back({(int)Q.size(), pos[b[i]], i, 0, 0, 1});
  while(m--) {
    int op; cin >> op;
    if(op == 1) {
      int la, ra, lb, rb; cin >> la >> ra >> lb >> rb;
      Q.push_back({(int)Q.size(), ra, rb, (int)ans.size(), 1, 0});
      Q.push_back({(int)Q.size(), la - 1, rb, (int)ans.size(), -1, 0});
      Q.push_back({(int)Q.size(), ra, lb - 1, (int)ans.size(), -1, 0});
      Q.push_back({(int)Q.size(), la - 1, lb - 1, (int)ans.size(), 1, 0});
      ans.push_back(0);
    }
    else {
      int x, y; cin >> x >> y;
      Q.push_back({(int)Q.size(), pos[b[x]], x, 0, 0, -1});
      Q.push_back({(int)Q.size(), pos[b[y]], y, 0, 0, -1});
      swap(b[x], b[y]);
      Q.push_back({(int)Q.size(), pos[b[x]], x, 0, 0, 1});
      Q.push_back({(int)Q.size(), pos[b[y]], y, 0, 0, 1});
    }
  }
}
void solve() {
  cdq(0, (int)Q.size());
  for(int i = 1 ; i < (int)ans.size() ; ++i) cout << ans[i] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
