#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;

const int N = (int)1e5 + 5;

int n, s, m, n2, d[N * 5], lson[N * 5], rson[N * 5], val[N];
int root1, root2, in[N * 5];
vector<pii> G[N * 5];

pii build(int l, int r) {
  if(l + 1 == r) return {l, l};
  int mid = (l + r) >> 1, o1 = n2++, o2 = n2++;
  auto [l1, l2] = build(l, mid);
  auto [r1, r2] = build(mid, r);
  lson[o1] = l1, rson[o1] = r1; lson[o2] = l2, rson[o2] = r2;
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

void init() {
  cin >> n >> s >> m;
  while(s--) {
    int p, x; cin >> p >> x; val[p] = d[p] = x;
  }
  n2 = n + 1;
  auto _ = build(1, n + 1); root1 = _.F, root2 = _.S;
  while(m--) {
    int l, r, k; cin >> l >> r >> k;
    for(int i = 0 ; i < k ; ++i) {
      int x; cin >> x;
      if(l < x) insert2(1, n + 1, l, x, n2, 0);
      G[n2].push_back({x, 1});
      l = x + 1;
    }
    if(l <= r) insert2(1, n + 1, l, r + 1, n2, 0);
    n2++;
  }
}
void solve() {
  for(int i = 1 ; i < n2 ; ++i) {
    for(auto [v, w] : G[i]) in[v]++;
  }
  queue<int> q;
  for(int i = 1 ; i < n2 ; ++i) {
    if(!d[i]) d[i] = 1, val[i] = (int)1e9;
    if(!in[i]) q.push(i);
  }
  while(!q.empty()) {
    int u = q.front(); q.pop();
    for(auto [v, w] : G[u]) {
      d[v] = max(d[v], d[u] + w);
      if(val[v] != (int)1e9 && val[v] < d[v]) { cout << "NIE\n"; return; }
      if(!--in[v]) q.push(v);
    }
  }
  for(int i = 1 ; i <= n ; ++i) {
    if(in[i] || d[i] > (int)1e9) { cout << "NIE\n"; return; }
  }
  cout << "TAK\n";
  for(int i = 1 ; i <= n ; ++i) {
    cout << d[i] << " \n"[i == n];
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
