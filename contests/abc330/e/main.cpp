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

#include <cassert>
// #define DEBUG
int main() {
  // cout << fixed << setprecision(10)
  cin.tie(0);
  ios::sync_with_stdio(false);

  int N, Q;
  cin >> N >> Q;
  vector<ll> a(N);
  cin >> a;

  map<ll, ll> cnt; // keyがvalue個ある
  set<ll> tmp_set; // aの重複をなくしたset
  for (auto i : a) {
    tmp_set.insert(i);
    cnt[i]++;
  }

  set<pll> st; //連続する列の{先頭、末尾}を要素とするset
  auto itr = tmp_set.begin();
  ll pre_first = *itr;
  ll pre_second = *itr;

  for (auto i : tmp_set) {
    if (i > pre_second + 1) {
      st.insert({pre_first, pre_second});
      pre_first = i;
    }
    pre_second = i;
  }

  st.insert({pre_first, pre_second});
  st.insert({-__LONG_LONG_MAX__, -__LONG_LONG_MAX__});
  st.insert({__LONG_LONG_MAX__, __LONG_LONG_MAX__});


  rep(_, Q) {
    int i;
    ll x;
    cin >> i >> x;
    --i;


    #ifdef DEBUG
    cout << "cnt: " << a[i] << ' ' << cnt[a[i]] << endl;
    #endif //DEBUG

    ////////////////////////////////////////////////////////////////////// a[i]を除く
    if (cnt[a[i]] == 1) {
      // stを更新する
      auto itr = st.lower_bound({a[i], -__LONG_LONG_MAX__});
      auto [f, s] = *itr;

      #ifdef DEBUG
      cout <<f<< ' ' << s << endl;
      #endif

      if (a[i] == f) { // a[i]が左端と一致
        st.erase(itr);
        if (f != s) {
          st.insert({f + 1, s});
        }
      } else{
        auto pre_itr = itr;
        --pre_itr;
        auto [pre_f, pre_s] = *pre_itr;
        #ifdef DEBUG
        cout <<pre_f<< ' ' << pre_s << endl;
        #endif

        st.erase(pre_itr);

        if (a[i] < pre_s) {
          st.insert({pre_f, a[i] - 1});
          st.insert({a[i] + 1, pre_s});
        } else { //a[i] == pre_s
          if (pre_f != pre_s) {
            st.insert({pre_f, pre_s - 1});
          }
        }
      }
    }

    #ifdef DEBUG
    for(auto i: st){
      cout << i << endl;
    }
    #endif //DEBUG

    cnt[a[i]]--;

    ////////////////////////////////////////////////////////////////////// i番目にxを加える
    if (cnt[x] == 0) {
      // stを更新する
      auto itr = st.lower_bound({x, -__LONG_LONG_MAX__});
      auto [f, s] = (*itr);

      if (x == f - 1) {
        if (itr == st.begin()) {
          st.erase(itr);
          st.insert({f - 1, s});
        } else {
          auto pre_itr = itr;
          --pre_itr;
          auto [pre_f, pre_s] = (*pre_itr);

          if(pre_s == x - 1){
            st.erase(st.find({f, s}));
            st.erase(st.find({pre_f, pre_s}));
            st.insert({pre_f, s});
          }else{
            st.erase(itr);
            st.insert({f - 1, s});
          }
        }
      } else {
        if (itr == st.begin()) {
          st.insert({x, x});
        } else {
          auto pre_itr = itr;
          --pre_itr;
          auto [pre_f, pre_s] = (*pre_itr);

          if (x == pre_s + 1) {
            st.erase(pre_itr);
            st.insert({pre_f, pre_s + 1});
          } else {
            st.insert({x, x});
          }
        }
      }
    }

    #ifdef DEBUG
    cout << endl;
    for(auto i: st){
      cout << i << endl;
    }
    cout << endl;
    #endif // DEBUG

    cnt[x]++;
    a[i] = x;
    // mex
    auto itr = st.lower_bound({0, -__LONG_LONG_MAX__});
    if ((*itr).first == 0) {
      cout << (*itr).second + 1 << endl;
    } else {
      cout << 0 << endl;
    }
    #ifdef DEBUG
    cout << endl;
    #endif // DEBUG
  }
}
