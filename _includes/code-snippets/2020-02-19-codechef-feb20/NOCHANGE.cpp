#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = (int)1e3 + 5;

ll n, p, d[N];

void print(int x, int v) {
  cout << "YES";
  for(int i = 0 ; i < x ; ++i) cout << ' ' << 0;
  cout << ' ' << v;
  for(int i = x + 1 ; i < n ; ++i) cout << ' ' << 0;
  cout << '\n';
}
void print(int x, int v, int y, int v2) {
  cout << "YES";
  for(int i = 0 ; i < x ; ++i) cout << ' ' << 0;
  cout << ' ' << v;
  for(int i = x + 1 ; i < y ; ++i) cout << ' ' << 0;
  cout << ' ' << v2;
  for(int i = y + 1 ; i < n ; ++i) cout << ' ' << 0;
  cout << '\n';
}

void init() {
  cin >> n >> p;
  for(int i = 0 ; i < n ; ++i) cin >> d[i];
}
void solve() {
  for(int i = 0 ; i < n ; ++i) {
    if(p < d[i]) {
      print(i, 1);
      return;
    }
    else if(p > d[i] && p % d[i] != 0) {
      print(i, p / d[i] + 1);
      return;
    }
  }
  int l = (d[0] == 1), r = n - (d[n - 1] == p);
  for(int i = l ; i < r ; ++i) {
    for(int j = i + 1 ; j < r ; ++j) {
      if(d[j] % d[i] == 0) continue;
      ll k;
      for(k = 1 ; (p - k * d[j]) % d[i] == 0 ; ++k);
      assert(p - k * d[j] > 0);
      print(i, (p - k * d[j]) / d[i] + 1, j, k);
      return;
    }
  }
  cout << "NO\n";
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
