#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int n, s, k;
set<int> v;

void init() {
  cin >> n >> s >> k;
  v.clear();
  for(int i = 0 ; i < k ; ++i) {
    int a; cin >> a; v.insert(a);
  }
}
void solve() {
  for(int i = 0 ; i <= 1000 ; ++i) {
    int l = max(1, s - i), r = min(n, s + i);
    if(!v.count(l) || !v.count(r)) {
      cout << i << '\n';
      return;
    }
  }
  assert(0);
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
