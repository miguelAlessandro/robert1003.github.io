#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;
const int M = (int)1e9 + 7;

struct Doll {
  int out, in;
};

int n, n2, root, s, t, lson[N * 3], rson[N * 3], in_pre[N], in[N * 3];
ll d[N * 3], cnt[N * 3];
vector<Doll> doll;
vector<pair<int, int> > G[N * 3];

int build(int l, int r) {
  int mid = (l + r) >> 1, o = n2++;
  if(l + 1 == r) {
    G[o].push_back({l, -doll[l].out});
  }
  else {
    lson[o] = build(l, mid); G[o].push_back({lson[o], 0});
    rson[o] = build(mid, r); G[o].push_back({rson[o], 0});
  }
  return o;
}
void insert(int l, int r, int ql, int qr, int u, int w, int o=root) {
  if(ql <= l && r <= qr) {
    G[u].push_back({o, w});
    return;
  }
  int mid = (l + r) >> 1;
  if(qr <= mid) insert(l, mid, ql, qr, u, w, lson[o]);
  else if(mid <= ql) insert(mid, r, ql, qr, u, w, rson[o]);
  else {
    insert(l, mid, ql, mid, u, w, lson[o]);
    insert(mid, r, mid, qr, u, w, rson[o]);
  }
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    int a, b; cin >> a >> b; doll.push_back({a, b});
  }
  sort(doll.begin(), doll.end(), [&](auto a, auto b) { return a.out < b.out; });
  n2 = n; root = build(0, n);
  s = n2++, t = n2++;
  for(int i = 0 ; i < n ; ++i) {
    Doll target = {doll[i].in, (int)1e9};
    int j = upper_bound(doll.begin(), doll.end(), target, [&](auto a, auto b) { return a.out < b.out; }) - doll.begin();
    if(j > 0) {
      insert(0, n, 0, j, i, doll[i].in);
      in_pre[0]++; in_pre[j]--;
    }
    else G[i].push_back({t, doll[i].in});
  }
  int in_deg = 0;
  for(int i = 0 ; i < n ; ++i) {
    in_deg += in_pre[i];
    if(in_deg == 0) G[s].push_back({i, 0});
  }
}
void solve() {
  for(int i = 0 ; i < n2 ; ++i) {
    for(auto [v, w] : G[i]) in[v]++;
  }
  vector<int> topo;
  queue<int> q;
  for(int i = 0 ; i < n2 ; ++i) if(!in[i]) q.push(i);
  while(!q.empty()) {
    int u = q.front(); q.pop(); topo.push_back(u);
    for(auto [v, w] : G[u]) {
      if(!--in[v]) q.push(v);
    }
  }
  fill(d, d + n2, (ll)1e18); d[s] = 0;
  for(auto u : topo) {
    for(auto [v, w] : G[u]) d[v] = min(d[v], d[u] + w);
  }
  cnt[s] = 1;
  for(auto u : topo) {
    for(auto [v, w] : G[u]) if(d[v] == d[u] + w) cnt[v] = (cnt[u] + cnt[v]) % M;
  }
  cout << cnt[t] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
