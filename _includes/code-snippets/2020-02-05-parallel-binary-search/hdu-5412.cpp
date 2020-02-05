#include <iostream>
#include <vector>
#include <algorithm>
#include <tuple>
using namespace std;
typedef long long ll;

const int N = (int)1e5 + 5;

namespace bit {
  int b[N * 2], n;

  void init(int _n) {
    n = _n;
    fill(b, b + n + 1, 0);
  }
  inline int lowbit(int x) { return x & (-x); }
  inline void update(int x, int v) {
    for(int i = x ; i <= n ; i += lowbit(i)) b[i] += v;
  }
  inline int qry(int x) {
    int ans = 0;
    for(int i = x ; i > 0 ; i -= lowbit(i)) ans += b[i];
    return ans;
  }
  int query(int l, int r) {
    return qry(r) - qry(l - 1);
  }
}
struct Event {
  int p, x, v, t;
};
struct Query {
  int l, r, k, t, id;
};

int n, q, q2, rg, a[N], ans[N];
vector<int> num;
vector<Event> events;
vector<Query> queries;

int id(int x, vector<int>& v) {
  return lower_bound(v.begin(), v.end(), x) - v.begin() + 1;
}
void totBS(int l, int r, vector<Event>& event, vector<Query>& query) {
  /*
  cerr << "l=" << l << ", r=" << r << ": \n";
  cerr << " event: "; for(auto [p, x, v, t] : event) fprintf(stderr, "(%d,%d,%d,%d), ", p, x, v, t); cerr << '\n';
  cerr << " query: "; for(auto [l, r, k, t, id] : query) fprintf(stderr, "(%d,%d,%d,%d,%d), ", l, r, k, t, id); cerr << '\n';
  */
  if(l + 1 == r || query.empty()) {
    for(int i = 0 ; i < (int)query.size() ; ++i) ans[query[i].id] = num[l - 1];
    return;
  }

  int mid = (l + r) >> 1, i = 0, j = 0;
  vector<Event> le, re;
  vector<Query> lq, rq;
  while(i < (int)event.size() || j < (int)query.size()) {
    if(j == (int)query.size() || (i < (int)event.size() && event[i].t <= query[j].t)) {
      if(event[i].x < mid) {
        //cerr << "e: " << event[i].p << ' ' << event[i].v << '\n';
        bit::update(event[i].p, event[i].v);
        le.push_back(event[i]);
      }
      else re.push_back(event[i]);
      ++i;
    }
    else {
      int cnt = bit::query(query[j].l, query[j].r);
      //cerr << "q: " << query[j].l << ' ' << query[j].r << ' ' << cnt << '\n';
      if(cnt >= query[j].k) lq.push_back(query[j]);
      else {
        rq.push_back(query[j]);
        rq.back().k -= cnt;
      }
      ++j;
    }
  }

  for(int k = 0 ; k < (int)le.size() ; ++k) bit::update(le[k].p, -le[k].v);
  totBS(l, mid, le, lq); vector<Event> ().swap(le); vector<Query> ().swap(lq);
  totBS(mid, r, re, rq); vector<Event> ().swap(re); vector<Query> ().swap(rq);
}

bool init() {
  if(!(cin >> n)) return 0;
  num.clear();
  events.clear();
  queries.clear();
  for(int i = 1 ; i <= n ; ++i) {
    cin >> a[i];
    events.push_back({i, a[i], 1, 0});
    num.push_back(a[i]);
  }
  cin >> q; q2 = 0;
  for(int i = 1 ; i <= q ; ++i) {
    int op; cin >> op;
    if(op == 1) {
      int l, v; cin >> l >> v;
      events.push_back({l, a[l], -1, i});
      events.push_back({l, a[l]=v, 1, i});
      num.push_back(v);
    }
    else {
      int l, r, k; cin >> l >> r >> k;
      queries.push_back({l, r, k, i, q2++});
    }
  }
  sort(num.begin(), num.end());
  num.resize(unique(num.begin(), num.end()) - num.begin());
  rg = (int)num.size();
  for(int i = 0 ; i < (int)events.size() ; ++i) events[i].x = id(events[i].x, num);
  return true;
}
void solve() {
  bit::init(n);
  totBS(1, rg + 1, events, queries);
  for(int i = 0 ; i < q2 ; ++i) cout << ans[i] << '\n';
}

int main() {
  ios_base::sync_with_stdio(0), cin.tie(0);
  while(init()) solve();
}
