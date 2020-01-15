#include <bits/stdc++.h>
using namespace std;

int x[4], y[4];

void init() {
  for(int i = 0 ; i < 4 ; ++i) cin >> x[i] >> y[i];
}
void solve() {
  string s = "";
  for(int i = 0 ; i < 20 ; ++i) s += "DL";
  for(int i = 0 ; i < 100 ; ++i) {
    if(i % 4 == 0) s += "UUUUU";
    else if(i % 4 == 1) s += "LLLLL";
    else if(i % 4 == 2) s += "DDDDDDDDDDDD";
    else s += "LLLLLL";
  }
  s += "RRRRRRRRDDUUURDDDDUUUUULLDDDDRRUUUU";
  cout << s.size() << '\n' << s << '\n';
}

int main() {
  int t; cin >> t;
  while(t--) {
    init();
    solve();
  }
}
