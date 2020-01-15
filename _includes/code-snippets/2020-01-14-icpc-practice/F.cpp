#include <bits/stdc++.h>
using namespace std;

const int N = 5000 + 5;

struct Pt {
  int x, y;

  Pt(int _x=0, int _y=0):x(_x), y(_y){};
  Pt operator-(const Pt& rhs) const { return Pt(x - rhs.x, y - rhs.y); }
};

int n, a[N], r[N], topo[N], in[N], vis[N], cnt;
Pt pos[N];
vector<int> G[N];

bool dfs(int u) {
  vis[u] = -1;
  for(auto v : G[u]) {
    if(vis[v] == -1) return 0;
    if(vis[v] == 0 && !dfs(v)) return 0;
  }
  topo[cnt--] = u;
  vis[u] = 1;
  return 1;
}
bool view(int i, int j) {
  Pt tj = pos[j] - pos[i];
  long double deg = atan2(tj.y, tj.x) * 180 / 3.141592653589793;
  int aa = a[i] + r[i], bb = a[i] - r[i];
  if(aa <= 359 && aa >= 0 && bb <= 359 && bb >= 0) {
    if(deg < 0) deg += 360;
  }
  else if(aa >= 360) deg += 360;
  return deg >= (long double)bb - 1e-9 && deg <= (long double)aa + 1e-9;
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) cin >> pos[i].x >> pos[i].y >> a[i] >> r[i];
}
void solve() {
  for(int i = 0 ; i < n ; ++i) {
    for(int j = 0 ; j < n ; ++j) if(i != j) {
      if(view(i, j)) G[i].push_back(j), in[j]++;
    }
  }
  cnt = n - 1;
  for(int i = 0 ; i < n ; ++i) if(in[i] == 0) {
    if(!dfs(i)) {
      cout << "-1\n"; return;
    }
  }
  if(cnt > -1) {
    cout << "-1\n"; return;
  }
  for(int i = 0 ; i < n ; ++i) cout << topo[i] + 1 << " \n"[i == n - 1];
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
