#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;

int n, q, state[N][2];

bool block(int r) {
  bool ans = false;
  for(int i = r - 1 ; i <= r  ; ++i) {
    for(int j = r - 1 ; j <= r ; ++j) {
      ans |= (state[i][0] & state[j][1]);
    }
  }
  return ans;
}
bool reach() {
  return (!state[n][0] & !state[n][1]) | (!state[n - 1][1] & !state[n][1]);
}

void init() {
  cin >> n >> q;
}
void solve() {
  int cnt = n - 1;
  while(q--) {
    int r, c; cin >> c >> r; c--;
    if(state[r][c] == 0) {
      int cc = block(r) + block(r + 1);
      state[r][c] = 1;
      cnt -= (block(r) + block(r + 1)) - cc;
    }
    else {
      int cc = block(r) + block(r + 1);
      state[r][c] = 0;
      cnt += cc - (block(r) + block(r + 1));
    }
    cout << (cnt == n - 1 && reach() ? "Yes\n" : "No\n");
  }
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
