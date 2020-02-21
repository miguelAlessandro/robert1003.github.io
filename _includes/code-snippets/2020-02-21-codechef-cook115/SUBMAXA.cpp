#pragma GCC optimize ("O3,unroll-loops,no-stack-protector")
#pragma GCC target ("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;
typedef long long ll;

const int N = (int)2e6 + 5;

int n;
ll d[N]; // difference array of difference array
pair<int, int> a[N][20];

inline pair<ll, int> rmq(int l, int r) {
  int k = __lg(r - l + 1);
  return max(a[l][k], a[r - (1 << k) + 1][k]);
}
inline void modify(int l, int r, int v) {
  d[l] += v; d[r + 1] -= v;
}

// faster i/o
#define getchar getchar_unlocked
#define putchar putchar_unlocked
void rit(int &x) {
  char c;
  while(!isdigit(c=getchar()));
  x = c - '0';
  while(isdigit(c=getchar())) x = x * 10 + c - '0';
}
char buf[10000];
void wit(ll x) {
  int i = 0;
  while(x > 0) {
    buf[i++] = '0' + x % 10;
    x /= 10;
  }
  if(i == 0) putchar('0');
  else {
    while(i > 0) putchar(buf[--i]);
  }
}
void init() {
  rit(n);
  for(int i = 1 ; i <= n ; ++i) {
    rit(a[i][0].F); a[i + n][0].F = a[i][0].F;
    a[i][0].S = i; a[i + n][0].S = i + n;
  }
  // build rmq table
  for(int j = 1 ; (1 << j) <= n ; ++j) { // only need length until n (not 2*n)
    for(int i = 1 ; i + (1 << j) - 1 <= 2 * n ; ++i) {
      a[i][j] = max(a[i][j - 1], a[i + (1 << (j - 1))][j - 1]);
    }
  }
}
void solve() {
  fill(d, d + 1 + n, 0);
  auto p = rmq(1, n);
  int mx = p.first, pos = p.second;
  modify(1, n, mx);
  queue<pair<int, int> > q; 
  q.push({pos + 1, pos + n - 1});
  while(!q.empty()) {
    auto pp = q.front(); q.pop();
    int l = pp.F, r = pp.S;
    if(l > r) continue;
    auto p = rmq(l, r);
    int mx = p.first, pos = p.second;
    int cc = min(pos - l + 1, r - pos + 1);
    modify(1, cc, mx);
    modify(r - l + 2 - cc + 1, r - l + 2, -mx);
    q.push({l, pos - 1}); 
    q.push({pos + 1, r}); 
  }
  for(int i = 1 ; i <= n ; ++i) d[i] += d[i - 1]; // recover difference array
  for(int i = 1 ; i <= n ; ++i) d[i] += d[i - 1]; // recover array
  for(int i = 1 ; i <= n - 1 ; ++i) {
    wit(d[i]);
    putchar(' ');
  }
  wit(d[n]);
  putchar('\n');
}

int main() {
  int t; rit(t);
  while(t--) {
    init();
    solve();
  }
}
