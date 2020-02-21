#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;

int n, target, a[N], c[N];
map<int, int> b;

void init() {
  cin >> n;
  target = 0;
  b.clear();
  for(int i = 1 ; i <= n ; ++i) {
    int x; cin >> x; 
    target ^= x;
    a[i] = x;
  }
  for(int i = 1 ; i <= n ; ++i) {
    int x; cin >> x;
    target ^= x;
    b[x]++;
  }
}
void solve() {
  for(int i = 1 ; i <= n ; ++i) {
    int want = a[i] ^ target;
    if(!b[want]) { cout << "-1\n"; return; }
    c[i] = want;
    b[want]--;
  }
  for(int i = 1 ; i <= n ; ++i) cout << c[i] << " \n"[i == n];
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
