#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;

namespace bit {
  ll n, b[N];
  
  void init(int _n) {
    n = _n;
    fill(b, b + n + 1, 0);
  }
  inline int lowbit(int x) { return x & (-x); }
  void update(int x, int v) {
    for(int i = x ; i <= n ; i += lowbit(i)) b[i] += v;
  }
  ll query(int x) {
    ll ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += b[i];
    return ans;
  }
}
struct Node {
  int t, v, id, i;

  bool operator<(const Node& rhs) const { return t > rhs.t; }
};

vector<Node> Q;
vector<ll> ans;
ll invcnt;

void cdq(int l, int r, int op) {
  if(l + 1 == r) return;
  int m = (l + r) >> 1;
  cdq(l, m, op); cdq(m, r, op);
  vector<Node> tmp;
  vector<int> his;
  int a = l, b = m, sum = 0;
  while(a < m && b < r) {
    if((!op && Q[a].v > Q[b].v) || (op && Q[a].v < Q[b].v)) {
      bit::update(Q[a].id, 1), sum++;
      his.push_back(Q[a].id);
      tmp.push_back(Q[a++]);
    }
    else {
      ans[Q[b].i] += (op ? sum : 0) - (op ? 1 : -1) * bit::query(Q[b].id);
      tmp.push_back(Q[b++]);
    }
  }
  while(a < m) tmp.push_back(Q[a++]);
  while(b < r) {
    ans[Q[b].i] += (op ? sum : 0) - (op ? 1 : -1) * bit::query(Q[b].id);
    tmp.push_back(Q[b++]);
  }
  for(int i = l ; i < r ; ++i) Q[i] = tmp[i - l];
  for(int i = 0 ; i < (int)his.size() ; ++i) bit::update(his[i], -1);
  vector<Node> ().swap(tmp);
  vector<int> ().swap(his);
}

void init() {
  int n, m; cin >> n >> m;
  vector<int> v(n + 1), pos(n + 1);
  for(int i = 1 ; i <= n ; ++i) cin >> v[i], pos[v[i]] = i;
  // get initial invcnt
  bit::init(n);
  invcnt = 0; int sum = 0;
  for(int i = 1 ; i <= n ; ++i) {
    invcnt += sum - bit::query(v[i]);
    bit::update(v[i], 1), sum++;
  }
  bit::init(n);
  // process query
  ans.push_back(0);
  for(int i = 0 ; i < m ; ++i) {
    int x; cin >> x;
    Q.push_back({i, x, pos[x], i + 1});
    ans.push_back(0);
    pos[x] = 0;
  }
  for(int i = 1 ; i <= n ; ++i) if(pos[i]) Q.push_back({m, i, pos[i], 0});
}
void solve() {
  sort(Q.begin(), Q.end());
  cdq(0, (int)Q.size(), 0);
  sort(Q.begin(), Q.end());
  cdq(0, (int)Q.size(), 1);
  for(int i = 1 ; i < (int)ans.size() ; ++i) {
    cout << invcnt << '\n';
    invcnt -= ans[i];
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
