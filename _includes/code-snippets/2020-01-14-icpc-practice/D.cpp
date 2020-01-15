#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int dx[4] = {1, 0, -1, 0};
const int dy[4] = {0, 1, 0, -1};
int table[14][14], dir[14][14];
bool vis[14][14];

void init() {
  memset(table, 0, sizeof(table));
  table[3][3] = table[3][10] = table[10][3] = table[10][10] = 1;
  table[6][6] = table[6][7] = table[7][6] = table[7][7] = -1;
  table[9][2] = table[10][2] = table[9][3] = table[9][10] = table[9][11] = table[10][11] = -1;
}
void solve() {
  int t; cin >> t;
  while(t--) {
    memset(vis, 0, sizeof(vis));
    queue<pair<int, int> > q;
    int a, b; cin >> a >> b;
    q.push({a, b}); vis[a][b] = 1; dir[a][b] = -1;
    int tx = -1, ty;
    while(!q.empty()) {
      auto [x, y] = q.front(); q.pop();
      for(int i = 0 ; i < 4 ; ++i) {
        int X = x + dx[i], Y = y + dy[i];
        if(X < 1 || X > 13 || Y < 1 || Y > 13 || vis[X][Y] || table[X][Y] == -1) continue;
        vis[X][Y] = 1;
        dir[X][Y] = i;
        q.push({X, Y});
        if(table[X][Y] == 1) {
          tx = X; ty = Y; break;
        }
      }
      if(tx != -1) break;
    }
    string s;

    do {
      int dd = dir[tx][ty];
      if(dd == -1) break;
      tx -= dx[dd];
      ty -= dy[dd];
      if(dd == 0) s.push_back('D');
      else if(dd == 1) s.push_back('R');
      else if(dd == 2) s.push_back('U');
      else s.push_back('L');
    } while(true);
    reverse(s.begin(), s.end());
    cout << s.size() << '\n' << s << '\n';
  }
}

int main() {
  init();
  solve();
}
