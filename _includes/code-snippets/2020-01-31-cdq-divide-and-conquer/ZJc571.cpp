#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct Pt {
  int x, y, z, i;
};

const int N = (int)1e5 + 5;

struct BIT {
  int b[N], n;

  void init(int _n) {
    n = _n;
    for(int i = 0 ; i <= n ; ++i) b[i] = 0;
  }
  inline int lowbit(int x) { return x & (-x); }
  void update(int x, int v) {
    for(int i = x ; i <= n ; i += lowbit(i)) b[i] += v;
  }
  int query(int x) {
    int ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += b[i];
    return ans;
  }
} bit;

vector<Pt> v;
int n, ans[N];

void cdq(int l, int r) {
  if(l + 1 == r) return;
  int m = (l + r) >> 1;
  cdq(l, m); cdq(m, r);
  int a = l, b = m, sum = 0;
  // need to record the modifications on BIT in order to reset it. The complexity will be $O(N^2)$ if we resetting it brute-forcely.
  vector<int> record;
  // temporary array for merge sort
  vector<Pt> tmp;
  while(a < m && b < r) {
    if(v[a].y > v[b].y) bit.update(v[a].z, 1), sum++, record.push_back(v[a].z), tmp.push_back(v[a++]);
    else ans[v[b].i] += sum - bit.query(v[b].z), tmp.push_back(v[b++]);
  }
  while(a < m) tmp.push_back(v[a++]);
  while(b < r) ans[v[b].i] += sum - bit.query(v[b].z), tmp.push_back(v[b++]);
  for(int i = l ; i < r ; ++i) v[i] = tmp[i - l];
  // reset BIT
  for(auto i : record) bit.update(i, -1);
  // release used memory
  vector<int> ().swap(record);
  vector<Pt> ().swap(tmp);
}

void init() {
  cin >> n;
  for(int i = 0 ; i < n ; ++i) {
    int a, b, c; cin >> a >> b >> c;
    v.push_back({a, b, c, i});
  }
  bit.init(n);
}
void solve() {
  // As we require > not >=
  sort(v.begin(), v.end(), [&](auto a, auto b) { 
      return (a.x == b.x ? (a.y == b.y ? a.z < b.z : a.y < b.y) : a.x > b.x); 
  }); 
  cdq(0, n);
  for(int i = 0 ; i < n ; ++i) cout << ans[i] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  init();
  solve();
}
