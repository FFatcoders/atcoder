#if __has_include(<atcoder/all>)
#include <atcoder/all>
using namespace atcoder;
#endif
#include <bits/stdc++.h>
using namespace std;
using namespace atcoder;
using graph = vector<vector<int>>;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<long long, long long> pll;
#define INF (int)(1e9)
#define MAXX 1.1529215e+18
#define EPS (1e-7)
#define rep(i, n) for (int i = 0; i < (int)(n); i++)
#define ALL(a) a.begin(), a.end()
#define PI acos(-1.0)
#define sz(a) a.size()
const ll MOD = 1e9 + 7;
const ll mod = 998244353;
const int MAX = 10000000;
template <typename T1, typename T2> inline bool chmin(T1 &a, T2 b) {
  if (a > b) {
    a = b;
    return 1;
  }
  return 0;
}
template <typename T1, typename T2> inline bool chmax(T1 &a, T2 b) {
  if (a < b) {
    a = b;
    return 1;
  }
  return 0;
}
template <typename T> T gcd(T a, T b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

// output
template <class t> using vc = vector<t>;
template <class t> ostream &operator<<(ostream &os, const vc<t> &v) {
  os << "{";
  for (auto e : v)
    os << e << " ";
  return os << "}";
}
template <class t> ostream &operator<<(ostream &os, const set<t> &st) {
  os << "{";
  for (auto e : st)
    os << e << ",";
  return os << "}";
}
template <class t, class u>
ostream &operator<<(ostream &os, const map<t, u> &mp) {
  for (auto [k, v] : mp)
    os << k << " " << v << endl;
  return os;
}

template <class t, class u>
ostream &operator<<(ostream &os, const pair<t, u> &p) {
  return os << "{" << p.first << " " << p.second << "}";
}

// input
template <typename T, typename U>
std::istream &operator>>(std::istream &is, pair<T, U> &pair) {
  return is >> pair.first >> pair.second;
}
template <class t> ostream &operator>>(ostream &os, const vc<t> &v) {
  for (auto e : v)
    os >> e;
  return os;
}
template <class t, class u>
ostream &operator>>(ostream &os, const pair<t, u> &p) {
  return os >> p.first >> p.second;
}
template <typename T>
std::istream &operator>>(std::istream &is, vector<T> &vec) {
  for (T &x : vec)
    is >> x;
  return is;
}

template <class T> T extgcd(T a, T b, T &x, T &y) {
  T d = a;
  if (b == 0) {
    x = 1;
    y = 0;
  } else {
    d = extgcd(b, a % b, y, x);
    y -= (a / b) * x;
  }
  return d;
}

void yesno(bool flag, string yes = "Yes", string no = "No") {
  if (flag) {
    cout << yes << endl;
  } else {
    cout << no << endl;
  }
}

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};
/* class内での演算子オーバーロード
bool operator<(const Info& another) const
{
    return age < another.age;  //年齢を比較
};*/
/*--------------------------------------------*/

struct station {
  ll l, d, k, c, to;
};

int main() {
  // cout << fixed << setprecision(10)
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N, M;
  cin >> N >> M;

  vector<vector<station>> g(N); //逆向きに辺を張る

  ll last_time = -1;

  rep(i, M) {
    ll l, d, k, c, a, b;
    cin >> l >> d >> k >> c >> a >> b;
    --a;
    --b;

    g[b].push_back(station{l, d, k, c, a});

    if (b == N - 1) {
      chmax(last_time, l + (k - 1) * d + c);
    }
  }

  if (last_time == -1) {
    rep(i, N - 1) { cout << "Unreachable" << endl; }
    return 0;
  }

  vector<ll> dist(N, __LONG_LONG_MAX__); //駅N-1からの所要時間（逆向き）

  priority_queue<pll, vector<pll>, greater<pll>> pq;
  pq.push({dist[N - 1] = 0, N - 1});

  vector<int> is_determined(N);

  while (!pq.empty()) {
    auto [cost, now] = pq.top();
    pq.pop();

    is_determined[now] = 1;

    ll real_time = last_time - cost;
    //ここまでにかかる時間はcost
    // cost以降で最初に出る電車の時刻は、
    for (const auto &[l, d, k, c, to] : g[now]) {
      if(is_determined[to]){
        continue;
      }


      if (real_time < l + c) {
        //乗れる電車がない
        continue;
      }

      ll time_to_arrive = min((real_time - l - c)  / d, k - 1) * d + l;
      //時刻real_timeから乗れる電車がtoに初めてつく時刻

      if (chmin(dist[to], last_time - time_to_arrive)) {
        pq.push({dist[to], to});
      }
    }
  }

  rep(i, N - 1) {
    cout << ((dist[i] != __LONG_LONG_MAX__) ? to_string(last_time - dist[i])
                                            : "Unreachable")
         << endl;
  }
}
