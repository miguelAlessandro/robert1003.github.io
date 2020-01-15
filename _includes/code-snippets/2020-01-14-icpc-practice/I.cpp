#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e6 + 5;

int n, nxt[N], pa[N], cnt[N]; 
string s;

void parse(int l, int r, int p) {
  int id = 0, i;
  for(i = l ; i <= r && isdigit(s[i]) ; ++i) id = id * 10 + (s[i] - '0');
  pa[id] = p;
  for(i ; i <= r ; ++i) {
    parse(i + 1, nxt[i] - 1, id);
    i = nxt[i];
  }
}

void init() {
  cin >> n >> s;
}
void solve() {
  int cc = 0;
  for(int i = 0 ; i < (int)s.size() ; ++i) {
    if(s[i] == '(') cnt[cc] = i, cc++;
    else if(s[i] == ')') {
      cc--;
      nxt[cnt[cc]] = i;
    }
  }
  parse(0, (int)s.size() - 1, 0);
  for(int i = 1 ; i <= n ; ++i) cout << pa[i] << " \n"[i == n];
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
