#include <bits/stdc++.h>
#define PB push_back
using namespace std;
typedef long long ll;

const int N = 20000 + 5;
const int M = (int)3e6 + 10;
const int inf = (int)1e9;

struct Dinic{
  static const int MXN = M;
  struct Edge{ int v,f,re; };
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
    //for (int i=0; i<n; i++) E[i].clear();
  }
  void add_edge(int u, int v, int f){
    E[u].PB({v,f,(int)E[v].size()});
    E[v].PB({u,0,(int)E[u].size()-1});
  }
  bool BFS(){
    for (int i=0; i<n; i++) level[i] = -1;
    queue<int> que;
    que.push(s);
    level[s] = 0;
    while (!que.empty()){
      int u = que.front(); que.pop();
      for (auto &it : E[u]){
        if (it.f > 0 && level[it.v] == -1){
          level[it.v] = level[u]+1;
          que.push(it.v);
        }
      }
    }
    return level[t] != -1;
  }
  int DFS(int u, int nf){
    if (u == t) return nf;
    int res = 0;
    for (auto &it : E[u]){
      if (it.f > 0 && level[it.v] == level[u]+1){
        int tf = DFS(it.v, min(nf,it.f));
        res += tf; nf -= tf; it.f -= tf;
        E[it.v][it.re].f += tf;
        if (nf == 0) return res;
      }
    }
    if (!res) level[u] = -1;
    return res;
  }
  int flow(int res=0){
    while ( BFS() )
      res += DFS(s,2147483647);
    return res;
  }
} flow;

struct Node {
  int l, r, v;
};

int n, m, s, t, tot;
vector<Node> seg[N];

namespace segtree {
  int id[N * 4], tag[N * 4];
  inline void pull(int o) {
    id[o] = ++tot;
    if(!tag[o * 2 + 1]) flow.add_edge(id[o], id[o * 2 + 1], inf);
    if(!tag[o * 2 + 2]) flow.add_edge(id[o], id[o * 2 + 2], inf);
  }
  void build(int l, int r, int o=0) {
    if(l + 1 == r) return void(id[o] = n + l);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    build(l, mid, lson);
    build(mid, r, rson);
    pull(o);
  }
  void modify(int l, int r, int ql, int qr, int v, int o=0) {
    if(ql <= l && r <= qr) return void(tag[o] += v);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(ql < mid) modify(l, mid, ql, qr, v, lson);
    if(qr > mid) modify(mid, r, ql, qr, v, rson);
    pull(o);
  }
}

void init() {
  cin >> n >> m;
  tot = 2 * n + 1, s = 0, t = 2 * n + 1;
  for(int i = 1 ; i <= m ; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    seg[y1].push_back({x1, x2 + 1, 1});
    seg[y2 + 1].push_back({x1, x2 + 1, -1});
  }
}
void solve() {
  for(int i = 1 ; i <= n ; ++i) {
    flow.add_edge(s, i, 1);
    flow.add_edge(i + n, t, 1);
  }
  segtree::build(1, n + 1);
  for(int i = 1 ; i <= n ; ++i) {
    for(auto [l, r, v] : seg[i]) segtree::modify(1, n + 1, l, r, v);
    if(!segtree::tag[0]) flow.add_edge(i, segtree::id[0], inf);
  }
  flow.init(tot + 1, s, t);
  cout << flow.flow() << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
