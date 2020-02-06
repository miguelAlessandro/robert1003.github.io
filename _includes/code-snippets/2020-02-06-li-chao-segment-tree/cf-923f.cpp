#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int C = (int)1e5 + 5;
const int N = (int)1e5 + 5;
const ll inf = (ll)1e18;

struct Line {
  ll m, b;
  ll operator()(ll x) { return m * x + b; }
};
struct Node {
  Line seg;
  Node *lson, *rson;
  Node(Line _seg): seg(_seg), lson(0), rson(0) {} 
};
void insert(int l, int r, Line seg, Node* o) {
  if(l + 1 == r) {
    if(seg(l) < o->seg(l)) o->seg = seg;
    return;
  }
  int mid = (l + r) >> 1;
  if(seg.m < o->seg.m) swap(seg, o->seg);
  if(o->seg(mid) > seg(mid)) {
    swap(seg, o->seg);
    if(o->rson) insert(mid, r, seg, o->rson);
    else o->rson = new Node(seg);
  }
  else {
    if(o->lson) insert(l, mid, seg, o->lson);
    else o->lson = new Node(seg);
  }
}
ll query(int l, int r, int x, Node* o) {
  if(l + 1 == r) return o->seg(x);
  int mid = (l + r) >> 1;
  if(x < mid && o->lson) return min(o->seg(x), query(l, mid, x, o->lson));
  else if(o->rson) return min(o->seg(x), query(mid, r, x, o->rson));
  return o->seg(x);
}
void del(Node* o) {
  if(o->lson) del(o->lson);
  if(o->rson) del(o->rson);
  delete o;
}
void merge(Node* dest, Node* o) {
  if(o->seg.m != 0 || o->seg.b != inf) insert(-C, C, o->seg, dest);
  if(o->lson) merge(dest, o->lson);
  if(o->rson) merge(dest, o->rson);
}

ll n, a[N], b[N], dp[N];
vector<int> G[N];

pair<int, Node*> dfs(int u, int p) {
  int sz = 0; Node* root = new Node({0, inf});
  for(auto v : G[u]) if(v != p) {
    auto [szz, son] = dfs(v, u);
    if(sz < szz) swap(root, son);
    merge(root, son);
    del(son);
    sz += szz;
  }
  dp[u] = (sz ? query(-C, C, a[u], root) : 0);
  insert(-C, C, {b[u], dp[u]}, root);
  return {sz + 1, root};
}

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) cin >> a[i];
  for(int i = 1 ; i <= n ; ++i) cin >> b[i];
  for(int i = 1 ; i < n ; ++i) {
    int u, v; cin >> u >> v;
    G[u].push_back(v);
    G[v].push_back(u);
  }
}
void solve() {
  dfs(1, 0);
  for(int i = 1 ; i <= n ; ++i) cout << dp[i] << ' ';
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}

