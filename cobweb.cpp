// https://acm.timus.ru/problem.aspx?space=1&num=1671
// đầu tiên union_set tất cả  các thread không có trong danh sách queyry, sau đó tìm số thành phần liên thông
// query offline, truy vấn ngược từ cuối lên đầu
// với mỗi query, kiểm tra xem 2 thằng ở thread đó có  cùng thành phần  liên thông không(bằng dsu)
// nếu khác  thành  phần liên thông thì trừ đi 1 vào số thành phần  liên thông ban đầu đã tính
// query update ngược rồi xuất ra

#include <bits/stdc++.h>

using namespace std;

const int M = 1e5 + 5;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  int n, m;
  cin >> n >> m;
  vector<int> par(n), rnk(n, 0);
  iota(begin(par), end(par), 0);
  vector<pair<int, int>> thread(m);
  for (auto& [i, j] : thread) cin >> i >> j, --i, --j;
  int Q;
  cin >> Q;
  vector<int> q(Q);
  bitset<M> has;
  for (int& i : q) {
    cin >> i; --i;
    has[i] = true;
  }
  function<int(int)> root = [&](int v) {
    return v == par[v] ? v : par[v] = root(par[v]);
  };
  auto uniset = [&](int a, int b) {
    a = root(a);
    b = root(b);
    if (a == b)
      return;
    if (rnk[a] < rnk[b])
      swap(a, b);
    par[b] = a;
    rnk[a] += rnk[a] == rnk[b];
  };
  for (int i = 0; i < m; i++) {
    if (!has[i]) {
      uniset(thread[i].first, thread[i].second);
    }
  }
  bitset<M> cc;
  for (int i = 0; i < n; i++) {
    cc[root(i)] = true;
  }
  int ncc = cc.count();
  int minus = 0;
  list<int> ans;
  reverse(begin(q), end(q));
  for (int i : q) {
    ans.push_front(ncc);
    if (root(thread[i].first) != root(thread[i].second))
      ncc -= 1;
    uniset(thread[i].first, thread[i].second);
  }
  for (int i : ans)
    cout << i << ' ';
  return 0;
}
