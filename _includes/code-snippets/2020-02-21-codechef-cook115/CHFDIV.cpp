#pragma GCC optimize ("no-stack-protector,O3,unroll-loops")
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int M = (int)1e9 + 7;

ll n, k;

unsigned long long gcd(unsigned long long u, unsigned long long v)
{
    int shift;
    if (u == 0) return v;
    if (v == 0) return u;
    shift = __builtin_ctzll(u | v);
    u >>= __builtin_ctzll(u);
    do {
        v >>= __builtin_ctz(v);
        if (u > v) {
            unsigned long long t = v;
            v = u;
            u = t;
        }
        v = v - u;
    } while (v != 0);
    return u << shift;
}

void init() {
  cin >> n >> k;
}
void solve() {
  ll ans = 1;
  for(ll i = 2 ; i <= n ; ++i) {
    ll g = gcd(i, k), j = i;
    while(1) {
      if(g == 1 || j == 1) break;
      while(j % g == 0) j /= g;
      g = gcd(j, g);
    }
    ans = ans * j % M;
  }
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
