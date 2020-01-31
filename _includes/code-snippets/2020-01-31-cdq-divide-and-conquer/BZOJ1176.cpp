#include <iostream>
#include <vector>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)2e6 + 5;

namespace bit {
  ll b[N], n;

  void init(int _n) {
    n = _n;
    fill(b, b + n + 1, 0);
  }
  inline int lowbit(int x) { return x & (-x); }
  void update(int x, int v) {
    if(x == 0) return;
    for(int i = x ; i <= n ; i += lowbit(i)) b[i] += v;
  }
  ll query(int x) {
    ll ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += b[i];
    return ans;
  }
}
struct Node {
  int t, x, y, v, i, sgn;
};

vector<Node> v;
vector<ll> ans;
int s, w;

void cdq(int l, int r) {
  if(l + 1 == r) return;
  int m = (l + r) >> 1;
  cdq(l, m); cdq(m, r);
  vector<Node> tmp;
  vector<pair<int, ll> > his;
  int a = l, b = m;
  while(a < m && b < r) {
    if(v[a].x <= v[b].x) {
      bit::update(v[a].y, v[a].v);
      his.push_back({v[a].y, -v[a].v});
      tmp.push_back(v[a++]);
    }
    else {
      ans[v[b].i] += v[b].sgn * (bit::query(v[b].y) + (ll)s * v[b].x * v[b].y);
      tmp.push_back(v[b++]);
    }
  }
  while(a < m) tmp.push_back(v[a++]);
  while(b < r) {
    ans[v[b].i] += v[b].sgn * (bit::query(v[b].y) + (ll)s * v[b].x * v[b].y);
    tmp.push_back(v[b++]);
  }
  for(int i = l ; i < r ; ++i) v[i] = tmp[i - l];
  for(int i = 0 ; i < (int)his.size() ; ++i) bit::update(his[i].F, his[i].S);
  vector<Node> ().swap(tmp);
  vector<pair<int ,ll> > ().swap(his);
}

void init() {
  cin >> s >> w;
  bit::init(w);
  v.clear(); ans.clear();
  ans.push_back(0);
  int op, i = 0; cin >> op;
  while(op != 3) {
    if(op == 1) {
      int x, y, a; cin >> x >> y >> a;
      v.push_back({i, x, y, a, 0, 0});
    }
    else {
      int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
      v.push_back({i, x1 - 1, y1 - 1, 0, (int)ans.size(), 1});
      v.push_back({i, x1 - 1, y2, 0, (int)ans.size(), -1});
      v.push_back({i, x2, y1 - 1, 0, (int)ans.size(), -1});
      v.push_back({i, x2, y2, 0, (int)ans.size(), 1});
      ans.push_back(0);
    }
    cin >> op, ++i;
  }
}
void solve() {
  cdq(0, (int)v.size());
  for(int i = 1 ; i < (int)ans.size() ; ++i) cout << ans[i] << '\n';
}


int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
