#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)3e5 + 5;
const int M = (int)1e9 + 7;

ll n, A[N], leaf[N], deg[N], a[N], cnt[N];
ll ans = 0, all;
vector<int> G[N];

void dfs(int u, int p) {
  leaf[u] = 0;
  for(auto v : G[u]) if(v != p) {
    dfs(v, u);
    leaf[u] += leaf[v];
  }
  if(leaf[u] == 0) leaf[u] = 1;
}
void dfs2(int u, int p) {
  ll sum = 0, sum2 = 0;
  for(auto v : G[u]) if(v != p) {
    dfs2(v, u);
    sum += (ll)leaf[v] * (leaf[v] - 1) / 2;
    sum2 += leaf[v];
  }
  cnt[u] = 0;
  if(G[u].size() > 1) {
    cnt[u] += (ll)(all - leaf[u]) * sum2 + ((ll)leaf[u] * (leaf[u] - 1) / 2 - sum);
  }
  else {
    cnt[u] += all - 1;
  }
}

void init() {
  cin >> n;
  for(int i = 1 ; i <= n ; ++i) cin >> A[i], G[i].clear(), deg[i] = 0;
  for(int i = 1 ; i < n ; ++i) {
    int x, y; cin >> x >> y;
    G[x].push_back(y);
    G[y].push_back(x);
    deg[x]++;
    deg[y]++;
  }
}
void solve() {
  if(n == 1) {
    cout << "0\n";
    return;
  }
  if(n == 2) {
    cout << (A[1] + A[2]) % M << '\n';
    return;
  }
  int root = 0;
  for(int i = 1 ; i <= n ; ++i) if(deg[i] > 1) {
    root = i;
    dfs(i, 0); // calculate # of leaves rooted at i
    break;
  }
  assert(root > 0);
  all = leaf[root];
  dfs2(root, 0); // calculate # of leaves paths
  // sort 1, 2, ..., n by cnt_i
  vector<int> v;
  for(int i = 1 ; i <= n ; ++i) v.push_back(i);
  sort(v.begin(), v.end(), [&](int i, int j) { return cnt[i] < cnt[j]; });
  sort(A + 1, A + 1 + n, [&](auto i, auto j) { return i < j; });
  ans = 0;
  for(int i = 1 ; i <= n ; ++i) ans = (ans + cnt[v[i - 1]] % M * A[i] % M) % M;
  cout << ans << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
