int binary_search(int val) { //array A of size N
  int i, step;
  for (step = 1; step < N; step <<= 1);
  for (i = 0; step; step >>= 1) {
    if (i + step < N && A[i + step] <= val) i += step;
  }
  return i;
}
// BITS BETWEEN: number of bits between 0 and x that are set to 1 at position b. 
ll calc(ll x, ll b) {
  ll cl = 1LL << (b + 1); ll cp = x / cl;
  ll ret = cp * (1LL << b); ll r = x % cl;
  if (r >= (1LL << b)) ret += r - (1LL << b) + 1;
  return ret;
}
// MATRIX POWER
vvll mul(vvll &a, vvll &b) {
  int N = sz(a), M = sz(a[0]), P = sz(b[0]);
  vvll ret(N, vll (P,0));
  FOR(i,N) FOR(j,P) FOR(k,M) {
    ret[i][j] += a[i][k]*b[k][j]; ret[i][j] %= MOD;
  }
  return ret;
}
vvll matpw(vvll &v, long long k) {
  int N = sz(v); vvll ret(N, vll(N,0));
  for(int i=0;i<N;++i) ret[i][i] = 1;
  for(int i=0;(1LL<<i) <= k; ++i) {
    if((1LL<<i)&k) ret = mul(ret, v); v = mul(v,v);
  }
  return ret;
}
// RANDOM 
mt19937 rng(time(0));
uniform_int_distribution<mt19937::result_type> d(1,6); // distribution in range [1, 6]
d(rng) // gets the number
// SET 
// Function to return an iterator to the exact element
set<int>::iterator findExact(set<int>& s, int element) {
  return s.find(element);
}
// Function to return an iterator to the smallest element larger than the input element
set<int>::iterator findNextLarger(set<int>& s, int element) {
  return s.upper_bound(element);
}
// Function to return an iterator to the largest element smaller than the input element
set<int>::iterator findNextSmaller(set<int>& s, int element) {
  auto it = s.lower_bound(element);
  return (it != s.begin()) ? prev(it) : s.end();
}
// TERNARY: F is some concave function, find max
double ternarySearch(double left, double right) {
  while(abs(right - left) > EPS) {
    long double lt = left + (right - left) / 3.0;
    long double rt = right - (right - left) / 3.0;
    if (F(lt) < F(rt)) left = lt;
    else right = rt; //reverse if convex and min
  }
  return (left + right) / 2.0;
}
// UTIL
struct cmp {
  bool operator()(piii a, piii b) { return a.fs > b.fs;}
};
priority_queue<piii, vector<piii>, cmp> pq;
namespace std {
  template <>
  struct hash<pii> {
  public:
    size_t operator()(pair<int, int> x) const throw() {
      size_t h = x.fs + x.sc * 1145; return h;
    }
  };
}
for (int news=state; news; news=state&(news-1))//all subsets of state

