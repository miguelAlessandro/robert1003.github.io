#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)2e5 + 5;
const int M = (int)1e6 + 5;
const int inf = (int)1e9;

set<pair<int, int> > G[N];
int n, k, sz[N], exist[M], edgecnt[M], tt;

int dfs(int u, int p) {
  sz[u] = 1;
  for(auto it : G[u]) if(it.first != p) {
    sz[u] += dfs(it.first, u);
  }
  return sz[u];
}
int centroid(int u, int p, int nn) {
  for(auto it : G[u]) if(it.first != p) {
    if(sz[it.first] > nn / 2) return centroid(it.first, u, nn);
  }
  return u;
}
int dfs2(int u, int p, int d, int cnt, int t, vector<pair<int, int> >& v) {
  int want = k - d, ans = inf;
  if(want >= 0 && exist[want] == t) {
    ans = min(ans, cnt + edgecnt[want]);
  }
  if(d <= k) {
    v.push_back({d, cnt});
    for(auto it : G[u]) if(it.first != p) {
      ans = min(ans, dfs2(it.first, u, d + it.second, cnt + 1, t, v));
    }
  }
  return ans;
}
int Solve(int u, int p) {
  int nn = dfs(u, p);
  int c = centroid(u, p, nn);
  int ans = inf;

  int t = ++tt;
  exist[0] = t; edgecnt[0] = 0;
  for(auto it : G[c]) { // dfs one subtree at a time
    vector<pair<int, int> > tmp;
    ans = min(ans, dfs2(it.first, c, it.second, 1, t, tmp));
    for(auto itt : tmp) {
      if(exist[itt.first] != t || (exist[itt.first] == t && edgecnt[itt.first] > itt.second)) {
        exist[itt.first] = t;
        edgecnt[itt.first] = itt.second;
      }
    }
  }
  vector<pair<int, int> > tmp(G[c].begin(), G[c].end());
  for(auto it : tmp) {
    G[c].erase(it); G[it.first].erase({c, it.second});
    ans = min(ans, Solve(it.first, c));
  }

  return ans;
}

void init() {
  cin >> n >> k;
  for(int i = 1 ; i < n ; ++i) {
    int u, v, w; cin >> u >> v >> w;
    G[u].insert({v, w});
    G[v].insert({u, w});
  }
}
void solve() {
  tt = 0;
  int ans = Solve(0, -1);
  cout << (ans == inf ? -1 : ans) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
