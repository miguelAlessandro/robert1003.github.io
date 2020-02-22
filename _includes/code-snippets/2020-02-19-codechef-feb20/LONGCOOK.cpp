#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int N = 400 + 50;

inline int weekday(int Y, int m, int d) {
  int c = Y / 100, y = Y % 100;
  int w = (y + y / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + d - 1);
  return (w % 7 + 7) % 7;
}
inline int overlap(int y) {
  int d1 = 1, w1 = weekday(y - 1, 14, d1);
  while(w1 != 5) d1++, w1 = (w1 + 1) % 7;
  int d2 = 28 + (y % 400 == 0 || (y % 4 == 0 && y % 100 != 0)), w2 = weekday(y - 1, 14, d2), cnt = 0;
  do {
    if(w2 == 0) cnt++;
    d2--, w2 = (w2 - 1 + 7) % 7;
  } while(cnt < 2);
  return d2 - d1 < 10;
}

int Y1, y2, pre[N];

int count(int y) {
  if(y < 3) return 0;
  else if(y < 9) return 1;
  return 1 + (y - 9) / 400 * 101 + pre[(y - 9) % 400];
}

void build() {
  for(int i = 9 ; i < 409 ; ++i) {
    if(i == 9) pre[0] = 1;
    else pre[i - 9] = pre[i - 9 - 1] + overlap(i);
  }
}
void init() {
  int a, b, c, d; cin >> a >> b >> c >> d;
  if(a > 2) b++;
  if(c < 2) d--;
  Y1 = b, y2 = d;
}
void solve() {
  if(Y1 > y2) cout << "0\n";
  else cout << count(y2) - count(Y1 - 1) << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  build();
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
