#include <iostream>
#include <queue>
#include <vector>
#include <functional>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int N = (int)5e4 + 5;
const int K = 10 + 1;
const int inf = (int)1e9;

int n, m, k, n2, root1, root2, d[K][N * 3], lson[N * 3], rson[N * 3];
vector<pair<int, int> > G[N * 3];

pii build(int l, int r) {
  if(l + 1 == r) return {l, l};
  int mid = (l + r) >> 1, o1 = n2++, o2 = n2++;
  pii ls = build(l, mid); int l1 = ls.F, l2 = ls.S;
  pii rs = build(mid, r); int r1 = rs.F, r2 = rs.S;
  lson[o1] = l1; rson[o1] = r1;
  lson[o2] = l2; rson[o2] = r2;
  G[o1].push_back({l1, 0}); G[o1].push_back({r1, 0});
  G[l2].push_back({o2, 0}); G[r2].push_back({o2, 0});
  return {o1, o2};
}
void insert2(int l, int r, int ql, int qr, int v, int w, int o=root2) {
  if(ql <= l && r <= qr) {
    G[o].push_back({v, w});
    return;
  }
  int mid = (l + r) >> 1;
  if(qr <= mid) insert2(l, mid, ql, qr, v, w, lson[o]);
  else if(mid <= ql) insert2(mid, r, ql, qr, v, w, rson[o]);
  else {
    insert2(l, mid, ql, mid, v, w, lson[o]);
    insert2(mid, r, mid, qr, v, w, rson[o]);
  }
}
void insert1(int l, int r, int ql, int qr, int ql2, int qr2, int w, int o=root1) {
  if(ql <= l && r <= qr) {
    insert2(1, n + 1, ql2, qr2, o, w);
    return;
  }
  int mid = (l + r) >> 1;
  if(qr <= mid) insert1(l, mid, ql, qr, ql2, qr2, w, lson[o]);
  else if(mid <= ql) insert1(mid, r, ql, qr, ql2, qr2, w, rson[o]);
  else {
    insert1(l, mid, ql, mid, ql2, qr2, w, lson[o]);
    insert1(mid, r, mid, qr, ql2, qr2, w, rson[o]);
  }
}

void init() {
  cin >> n >> m >> k;
  for(int i = 0 ; i <= n * 3 ; ++i) G[i].clear();
  n2 = n + 1;
  pii rr = build(1, n + 1);
  root1 = rr.F, root2 = rr.S;
  while(m--) {
    int a, b, c, D, w; cin >> a >> b >> c >> D >> w;
    insert1(1, n + 1, a, b + 1, c, D + 1, w);
    insert1(1, n + 1, c, D + 1, a, b + 1, w);
  }
}
void solve() {
  for(int i = 0 ; i <= k ; ++i) fill(d[i], d[i] + n2, inf);
  d[0][1] = 0;
  priority_queue<pair<int, pii>, vector<pair<int, pii> >, greater<pair<int, pii> > > pq;
  pq.push({d[0][1], {0, 1}});
  while(!pq.empty()) {
    auto p = pq.top(); pq.pop();
    int uk = p.S.F, u = p.S.S;
    for(auto pp : G[u]) {
      int v = pp.F, w = pp.S;
      if(d[uk][u] + w < d[uk][v]) {
        d[uk][v] = d[uk][u] + w;
        pq.push({d[uk][v], {uk, v}});
      }
      if(uk < k && d[uk + 1][v] > d[uk][u]) {
        d[uk + 1][v] = d[uk][u];
        pq.push({d[uk + 1][v], {uk + 1, v}});
      }
    }
  }
  int ans = inf;
  for(int i = 0 ; i <= k ; ++i) ans = min(ans, d[i][n]);
  if(ans == inf) cout << "CreationAugust is a sb!\n";
  else cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
