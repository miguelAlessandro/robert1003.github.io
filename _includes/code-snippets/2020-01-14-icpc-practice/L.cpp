#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

string s;

void init() {
  cin >> s;
}
void solve() {
  vector<pair<int, int> > ans;
  // remove c
  string p;
  for(int i = 0 ; i < (int)s.size() ; ++i) {
    if(s[i] == 'c') {
      if(p.empty()) return void(cout << "-1\n");
      else if(p.back() == 'a') { // ac
        ans.push_back({3, p.size() + 1});
        ans.push_back({2, p.size() + 1});
        ans.push_back({4, p.size()});
      }
      else {
        if(p.size() == 1) return void(cout << "-1\n"); // bc
        else if(p[p.size() - 2] == 'a') { // abc
          ans.push_back({4, p.size() - 1});
          p.pop_back(); p.pop_back();
        }
        else { // bbc
          ans.push_back({2, p.size() - 1});
          ans.push_back({3, p.size()});
          ans.push_back({4, p.size() + 1});
        }
      }
    }
    else p.push_back(s[i]);
  }
  swap(s, p);
  // remove b
  p.clear();
  for(int i = 0 ; i < (int)s.size() ; ++i) {
    if(s[i] == 'b') {
      if(p.empty()) return void(cout << "-1\n");
      else { // ab
        ans.push_back({2, p.size() + 1});
        ans.push_back({4, p.size()});
        p.pop_back();
      }
    }
    else p.push_back(s[i]);
  }
  swap(s, p);
  // remove a
  for(int i = 0 ; i < (int)s.size() ; ++i) {
    ans.push_back({1, 1});
    ans.push_back({2, 2});
    ans.push_back({4, 1});
  }

  cout << ans.size() << '\n';
  for(auto [a, b] : ans) cout << a << ' ' << b << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
