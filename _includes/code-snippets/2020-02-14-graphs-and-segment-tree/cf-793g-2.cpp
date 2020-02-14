#include <bits/stdc++.h>
#define PB push_back
using namespace std;
typedef long long ll;

struct Dinic{
  static const int MXN = (int)2e6;
  struct Edge{ int v,f,re; };
  int n,s,t,level[MXN];
  vector<Edge> E[MXN];
  void init(int _n, int _s, int _t){
    n = _n; s = _s; t = _t;
//    for (int i=0; i<n; i++) E[i].clear();
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
}flow;

struct Node {
  int l, r, y, v;
  
  bool operator<(const Node& rhs) const {
    return y < rhs.y;
  }
};

int n, q, s, t, tot;
vector<Node> seg;

namespace segtree {
  static const int N = (int)1e4 + 5;
  static const int inf = (int)1e9;
  int id[N * 4], id2[N * 4], tag[N * 4];
  void pull(int o, int lson, int rson) {
    id[o] = tot++;
    if(!tag[lson]) flow.add_edge(id[o], id[lson], inf);
    if(!tag[rson]) flow.add_edge(id[o], id[rson], inf);
  }
  void build1(int l, int r, int o=0) {
    if(l + 1 == r) return void(id[o] = n + l);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    build1(l, mid, lson);
    build1(mid, r, rson);
    pull(o, lson, rson);
  }
  void build2(int l, int r, int o=0) {
    if(l + 1 == r) return void(id2[o] = l);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    id2[o] = tot++;
    build2(l, mid, lson);
    build2(mid, r, rson);
    flow.add_edge(id2[lson], id2[o], inf);
    flow.add_edge(id2[rson], id2[o], inf);
  }
  void build(int l, int r) {
    build1(l, r);
    build2(l, r);
  }
  void modify1(int l, int r, int ql, int qr, int v, int o=0) {
    if(ql <= l && r <= qr) return void(tag[o] += v);
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(ql < mid) modify1(l, mid, ql, qr, v, lson);
    if(mid < qr) modify1(mid, r, ql, qr, v, rson);
    pull(o, lson, rson);
  }
  void modify2(int l, int r, int ql, int qr, int o=0) {
    if(ql <= l && r <= qr) return void(flow.add_edge(id2[o], id[0], inf));
    int mid = (l + r) >> 1, lson = o * 2 + 1, rson = o * 2 + 2;
    if(ql < mid) modify2(l, mid, ql, qr, lson);
    if(mid < qr) modify2(mid, r, ql, qr, rson);
  }
  void modify(int l, int r, int ql1, int qr1, int v, int ql2, int qr2) {
    if(!tag[0] && ql2 < qr2) modify2(l, r, ql2, qr2);
    modify1(l, r, ql1, qr1, v);
  }
}

void init() {
  cin >> n >> q;
  for(int i = 0 ; i < q ; ++i) {
    int x1, y1, x2, y2; cin >> x1 >> y1 >> x2 >> y2;
    seg.push_back({x1, x2 + 1, y1, 1});
    seg.push_back({x1, x2 + 1, y2 + 1, -1});
  }
  sort(seg.begin(), seg.end());
}
void solve() {
  tot = 2 * n + 2, s = 0, t = 2 * n + 1;
  for(int i = 1 ; i <= n ; ++i) {
    flow.add_edge(s, i, 1);
    flow.add_edge(i + n, t, 1);
  }
  segtree::build(1, n + 1);
  int preY = 1;
  for(auto [l, r, y, v] : seg) {
    segtree::modify(1, n + 1, l, r, v, preY, y);
    preY = y;
  }
  if(preY < n + 1) segtree::modify2(1, n + 1, preY, n + 1);
  flow.init(tot, s, t);
  cout << flow.flow() << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
