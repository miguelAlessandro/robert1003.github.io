#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = 1000 + 5;

int n;
map<pair<int, int>, int> m;
vector<int> mx_path[N], mn_path[N];

void check(int x) {
  if(x == -2) while(1);
}
int ask(int x, int y) {
  if(m.count({x, y})) return m[{x, y}];
  cout << 1 << ' ' << x + 1 << ' ' << y + 1 << endl;
  int ans; cin >> ans; check(ans);
  return m[{x, y}] = m[{y, x}] = ans - 1;
}

pair<int, int> dfs(int x) {
  if(x >= n) return {x - n, x - n};
  pair<int, int> l = dfs(x * 2), r = dfs(x * 2 + 1);
  int mn = ask(l.F, r.F), mx = ask(l.S, r.S);
  mx = (mx == l.S ? r.S : l.S);
  mn_path[mn].push_back(mn ^ l.F ^ r.F);
  mx_path[mx].push_back(mx ^ l.S ^ r.S);
  return {mn, mx};
}

void init() {
  cin >> n; check(n);
  m.clear();
  for(int i = 0 ; i < n ; ++i) mx_path[i].clear(), mn_path[i].clear();
}
void solve() {
  int a, d; tie(a, d) = dfs(1);
  int b = mn_path[a][0];
  for(int i = 1 ; i < (int)mn_path[a].size() ; ++i) {
    b = (ask(b, mn_path[a][i]) == b ? b : mn_path[a][i]);
  }
  int c = mx_path[d][0]; 
  for(int i = 1 ; i < (int)mx_path[d].size() ; ++i) {
    c = (ask(c, mx_path[d][i]) == c ? mx_path[d][i] : c);
  }
  cout << 2 << ' ' << a + 1 << ' ' << b + 1 << ' ' << c + 1 << ' ' << d + 1 << endl;
}

int main() {
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
