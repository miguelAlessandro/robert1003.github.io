#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int main() {
  int n; cin >> n; int a[n];
  for(int i = 0 ; i < n ; ++i) cin >> a[i];
  ll ans = 0;
  for(int i = 0 ; i < (1 << n) ; ++i) {
    ll sum = 0;
    for(int j = 0 ; j < n ; ++j) if(i & (1 << j)) sum |= a[j];
    ans += sum;
  }
  cout << ans << '\n';
}
