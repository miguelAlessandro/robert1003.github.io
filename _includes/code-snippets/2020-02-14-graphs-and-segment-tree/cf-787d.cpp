#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;
const ll inf = (ll)1e18;

vector<pair<int, int> > G[N * 3];
int n, q, s, n2, ls[N * 3], rs[N * 3];
ll d[N * 3];

pair<int, int> build(int l, int r) {
  if(l + 1 == r) return {l, l};
  int mid = (l + r) >> 1, o1 = n2++, o2 = n2++;
  auto [l1, l2] = build(l, mid);
  auto [r1, r2] = build(mid, r);
  G[o1].push_back({l1, 0}); G[o1].push_back({r1, 0});
  ls[o1] = l1; rs[o1] = r1;
  G[l2].push_back({o2, 0}); G[r2].push_back({o2, 0});
  ls[o2] = l2; rs[o2] = r2;
  return {o1, o2};
}
void insert1(int l, int r, int ql, int qr, int u, int w, int o) {
  if(ql <= l && r <= qr) {
    G[u].push_back({o, w});
    return;
  }
  int mid = (l + r) >> 1;
  if(qr <= mid) insert1(l, mid, ql, qr, u, w, ls[o]);
  else if(mid <= ql) insert1(mid, r, ql, qr, u, w, rs[o]);
  else {
    insert1(l, mid, ql, mid, u, w, ls[o]);
    insert1(mid, r, mid, qr, u, w, rs[o]);
  }
}
void insert2(int l, int r, int ql, int qr, int v, int w, int o) {
  if(ql <= l && r <= qr) {
    G[o].push_back({v, w});
    return;
  }
  int mid = (l + r) >> 1;
  if(qr <= mid) insert2(l, mid, ql, qr, v, w, ls[o]);
  else if(mid <= ql) insert2(mid, r, ql, qr, v, w, rs[o]);
  else {
    insert2(l, mid, ql, mid, v, w, ls[o]);
    insert2(mid, r, mid, qr, v, w, rs[o]);
  }
}

void init() {
  cin >> n >> q >> s;
  n2 = n + 1;
  auto [root1, root2] = build(1, n + 1);
  while(q--) {
    int op = 1; cin >> op;
    if(op == 1) {
      int u, v, w; cin >> u >> v >> w;
      G[u].push_back({v, w});
    }
    else if(op == 2) {
      int u, l, r, w; cin >> u >> l >> r >> w;
      insert1(1, n + 1, l, r + 1, u, w, root1);
    }
    else {
      int v, l, r, w; cin >> v >> l >> r >> w;
      insert2(1, n + 1, l, r + 1, v, w, root2);
    }
  }
}
void solve() {
  fill(d, d + n2, -1);
  d[s] = 0;
  priority_queue<pair<ll, int>, vector<pair<ll, int> >, greater<pair<ll, int> > > pq;
  pq.push({d[s], s});
  while(!pq.empty()) {
    auto [_, u] = pq.top(); pq.pop();
    for(auto [v, w] : G[u]) {
      if(d[u] + w < d[v] || d[v] == -1) {
        d[v] = d[u] + w;
        pq.push({d[v], v});
      }
    }
  }
  for(int i = 1 ; i <= n ; ++i) cout << d[i] << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
