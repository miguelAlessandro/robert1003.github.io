#pragma GCC optimize ("O3,no-stack-protector,unroll-loops")
#include <algorithm>
#include <iostream>
#include <vector>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)5e5 + 5;
const int M = (int)1e9 + 7;

int n, n2, root;
vector<int> G[N * 2], G2[N * 2], stk;
vector<ll> v;
vector<pair<ll, ll> > bomb;
int pre[N * 2], low[N * 2], scc[N * 2], vis[N * 2], lef[N * 2], rig[N * 2], clk, cnt;

namespace graph {
  struct Node {
    int l, r, ls, rs;
  } a[N * 2];

  int build(int l, int r) {
    if(l + 1 == r) {
      a[l] = {l, r, -1, -1};
      return l;
    }
    int mid = (l + r) >> 1, o = n2++, lson = build(l, mid), rson = build(mid, r);
    G[o].push_back(lson);
    G[o].push_back(rson);
    a[o] = {l, r, lson, rson};
    return o;
  }
  void insert(int l, int r, int ql, int qr, int u, int o=root) {
    if(ql <= l && r <= qr) {
      if(u != o) G[u].push_back(o);
      return;
    }
    int mid = (l + r) >> 1, lson = a[o].ls, rson = a[o].rs;
    if(qr <= mid) insert(l, mid, ql, qr, u, lson);
    else if(mid <= ql) insert(mid, r, ql, qr, u, rson);
    else {
      insert(l, mid, ql, mid, u, lson);
      insert(mid, r, mid, qr, u, rson);
    }
  }
  void tarjan(int u) {
    pre[u] = low[u] = ++clk; vis[u] = 1;
    stk.push_back(u);
    for(int i = 0 ; i < (int)G[u].size() ; ++i) {
      int v = G[u][i];
      if(!pre[v]) {
        tarjan(v);
        low[u] = min(low[u], low[v]);
      }
      else if(vis[v]) {
        low[u] = min(low[u], pre[v]);
      }
    }
    if(low[u] == pre[u]) {
      lef[cnt] = n, rig[cnt] = 0;
      while(1) {
        int x = stk.back(); stk.pop_back();
        lef[cnt] = min(lef[cnt], a[x].l);
        rig[cnt] = max(rig[cnt], a[x].r);
        scc[x] = cnt;
        if(x == u) break;
      }
      ++cnt;
    }
  }
  void buildG2() {
    for(int u = 0 ; u < n2 ; ++u) {
      for(int i = 0 ; i < (int)G[u].size() ; ++i) {
        int v = G[u][i];
        if(scc[u] != scc[v]) G2[scc[u]].push_back(scc[v]);
      }
    }
    for(int u = 0 ; u < cnt ; ++u) {
      sort(G2[u].begin(), G2[u].end());
      G2[u].resize(unique(G2[u].begin(), G2[u].end()) - G2[u].begin());
    }
  }
  void dfs(int u) {
    vis[u] = 1;
    for(int i = 0 ; i < (int)G2[u].size() ; ++i) {
      int v = G2[u][i];
      if(!vis[v]) dfs(v);
      lef[u] = min(lef[u], lef[v]);
      rig[u] = max(rig[u], rig[v]);
    }
  }
  int query(int u) {
    return rig[scc[u]] - lef[scc[u]];
  }
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    ll x, r; cin >> x >> r;
    bomb.push_back({x, r});
    v.push_back(x);
  }
  n2 = n;
  root = graph::build(0, n);
  for(int i = 0 ; i < n ; ++i) {
    int l = lower_bound(v.begin(), v.end(), bomb[i].F - bomb[i].S) - v.begin();
    int r = upper_bound(v.begin(), v.end(), bomb[i].F + bomb[i].S) - v.begin();
    graph::insert(0, n, l, r, i);
  }
}
void solve() {
  graph::tarjan(root);
  graph::buildG2();
  fill(vis, vis + cnt, 0);
  for(int i = 0 ; i < cnt ; ++i) if(!vis[i]) graph::dfs(i);
  int ans = 0;
  for(int i = 0 ; i < n ; ++i) ans = (ans + (ll)graph::query(i) * (i + 1)) % M;
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

