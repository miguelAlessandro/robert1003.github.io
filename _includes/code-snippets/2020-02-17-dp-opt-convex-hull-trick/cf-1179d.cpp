#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;
typedef long double ld;

const int N = (int)5e5 + 5;
const ll inf = (ll)1e18;

vector<int> G[N];
ll dp[N], sz[N], n;

struct CHT {
  deque<pair<ll, ll> > dq;

  void init() {
    dq.clear();
    dq.push_back({0, inf});
  }
  inline ll value(pair<ll, ll> l, ll x) { return l.F * x + l.S; }
  inline bool better(pair<ll, ll> L, pair<ll, ll> L1, pair<ll, ll> L2) {
    return (L2.S - L.S) * (L1.F - L2.F) >= (L.F - L2.F) * (L2.S - L1.S);
  }
  ll query(ll x) {
    while(dq.size() >= 2 && value(dq[dq.size() - 1], x) > value(dq[dq.size() - 2], x)) dq.pop_back();
    return value(dq.back(), x);
  }
  void insert(pair<ll, ll> line) {
    while(dq.size() >= 2 && better(line, dq[dq.size() - 1], dq[dq.size() - 2])) dq.pop_back();
    dq.push_back(line);
  }
} cht;

inline ll square(ll x) { return x * (x - 1); }
int dfs(int u, int p) {
  sz[u] = 1;
  for(auto v : G[u]) if(v != p) sz[u] += dfs(v, u);
  return sz[u];
}
ll DP(int u, int p) {
  dp[u] = inf;
  for(auto v : G[u]) if(v != p) dp[u] = min(dp[u], DP(v, u) + square(sz[u] - sz[v]));
  if(p != 0 && (int)G[u].size() == 1) dp[u] = 0;
  return dp[u];
}
ll dfs2(int u, int p) {
  ll ans = inf;
  sort(G[u].begin(), G[u].end(), [&](auto a, auto b) { return sz[a] < sz[b]; });
  for(auto v : G[u]) if(v != p) {
    ans = min(ans, dfs2(v, u));
  }
  cht.init();
  for(auto v : G[u]) if(v != p) {
    ans = min(ans, n * n - 2LL * sz[v] * n + dp[v] + sz[v] * sz[v] + sz[v] - n + cht.query(sz[v]));
    cht.insert({2LL * sz[v], sz[v] * sz[v] + sz[v] + dp[v] - 2LL * sz[v] * n});
  }
  return ans;
}

void init() {
  cin >> n;
  for(int i = 1 ; i < n ; ++i) {
    int a, b; cin >> a >> b;
    G[a].push_back(b);
    G[b].push_back(a);
  }
}
void solve() {
  if(n == 2) {
    cout << 2 << '\n';
    return;
  }
  int root = 1;
  for(int i = 1 ; i <= n ; ++i) if((int)G[i].size() > 1) { root = i; break; }
  dfs(root, 0);
  DP(root, 0);
  cout << (ll)n * (n - 1) - dfs2(root, 0) / 2 << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
