#define MOD 998244353
template<int MODX>
struct ModInt {
  ll x;
  ModInt() : x(0) { }
  ModInt(signed sig) : x(((sig%MODX)+MODX)%MODX) {  }
  ModInt(signed long long sig) : x(((sig%MODX)+MODX)%MODX) { }
  int get() const { return (int)x; }
  ModInt pow(ll p) { ModInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }
 
  static int inv(int a, int m) {
    int g = m, x = 0, y = 1;
    while(a != 0) {
      int q = g / a;
      g %= a; swap(g, a);
      x -= q * y; swap(x, y);
    } 
    return x < 0? x + m : x;
  }

  ModInt inv() const { return ModInt(inv(x, MODX)); }
  ModInt operator-() const { return ModInt(x? MODX-x : 0); }
  ModInt& operator++() { x++; if(x == MODX) x = 0; return *this; }
  ModInt& operator--() { if(x == 0) x = MODX; x--; return *this; }
  ModInt operator++(int) { ModInt a = *this; ++*this; return a; }
  ModInt operator--(int) { ModInt a = *this; --*this; return a; }
  ModInt& operator+=(const ModInt& o) { x += o.x; if (x >= MODX) x -= MODX; return *this; }
  ModInt& operator-=(const ModInt& o) { x -= o.x; if (x < 0) x += MODX; return *this; }
  ModInt& operator*=(const ModInt& o) { x = (ll(x) * o.x) % MODX; return *this; }
  ModInt& operator/=(const ModInt& o) { return *this *= o.inv(); }
  friend ModInt operator+(const ModInt& a, const ModInt& b) { ModInt res = a; res += b; return res; }
  friend ModInt operator-(const ModInt& a, const ModInt& b) { ModInt res = a; res -= b; return res; }
  friend ModInt operator*(const ModInt& a, const ModInt& b) { ModInt res = a; res *= b; return res; }
  friend ModInt operator/(const ModInt& a, const ModInt& b) { ModInt res = a; res /= b; return res; }
  friend bool operator==(const ModInt& a, const ModInt& b) { return a.x == b.x; }
  friend bool operator!=(const ModInt& a, const ModInt& b) { return a.x != b.x; }
  friend bool operator<(const ModInt& a, const ModInt& b) { return a.x < b.x; }
  friend bool operator>(const ModInt& a, const ModInt& b) { return a.x > b.x; }
  friend bool operator<=(const ModInt& a, const ModInt& b) { return a.x <= b.x; }
  friend bool operator>=(const ModInt& a, const ModInt& b) { return a.x >= b.x; }
  ModInt operator^(ll p) {
    if(p < 0) return inv() ^ -p;
    ModInt a = *this, res{1}; while(p > 0) {
      if(p & 1) res *= a;
      p >>= 1; if(p > 0) a *= a;
    }
    return res;
  }

  friend istream& operator>>(istream& in, ModInt& m) { ll x_; in >> x_; m = ModInt(x_); return in; } 
  friend ostream& operator<<(ostream& os, const ModInt& m) { return os << m.x; }
};

typedef ModInt<MOD> mint;

namespace NTT {
  const int FFT_CUTOFF = 150;
  vector<mint> roots = {0, 1};
  vector<int> bit_order;
  int max_size = 1; mint root = 2;

  auto find_root = []() {
    int order = MOD-1;
    while(~order & 1) order >>= 1, max_size <<= 1;
    while((root ^ max_size) != 1 or (root ^ max_size/2) == 1) root++;
    return 'W';
  }();

  void prepare_roots(int n) {
    if(sz(roots) >= n) return;
    int len = __builtin_ctz(sz(roots));
    roots.resize(n);
    while(n > 1 << len) {
      mint z = root ^ max_size >> len + 1;
      for(int i = 1 << len-1; i < 1 << len; i++) {
          roots[i << 1] = roots[i];
          roots[i << 1 | 1] = roots[i] * z;
      }
      len++;
    }
  }

  void reorder_bits(int n, vector<mint>& a) {
    if(sz(bit_order) != n) {
      bit_order.assign(n, 0);
      int len = __builtin_ctz(n);
      for(int i = 0; i < n; i++) {
        bit_order[i] = (bit_order[i >> 1] >> 1) + ((i & 1) << len-1);
      }
    }
    for(int i = 0; i < n; i++) {
      if(i < bit_order[i]) swap(a[i], a[bit_order[i]]);
    }
  }

  void fft(int n, vector<mint>& a) {
    assert(n <= max_size);
    prepare_roots(n); reorder_bits(n, a);
    for(int len = 1; len < n; len <<= 1) {
      for(int i = 0; i < n; i += len << 1) {
        for(int j = 0; j < len; j++) {
          mint even = a[i + j];
          mint odd = a[i + len + j] * roots[len + j];
          a[i + j] = even + odd; a[i + len + j] = even - odd;
        }
      }
    }
  }

  template<typename T>
  vector<mint> multiply(const vector<T>& a, const vector<T>& b, bool trim = true) {
    int n = sz(a), m = sz(b);
    if(n == 0 or m == 0) return vector<mint>{0};

    if(min(n, m) < FFT_CUTOFF) {
      vector<mint> res(n + m - 1);
      for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
          res[i + j] += mint(a[i]) * mint(b[j]);
        }
      }
      if(trim) {
        while(!res.empty() && res.back() == 0) res.pop_back();
      }
      return res;
    }

    int N = [](int x) { while(x & x-1) x = (x | x-1) + 1; return x; }(n + m - 1);
    vector<mint> fa(all(a)), fb(all(b));
    fa.resize(N); fb.resize(N);

    bool equal = fa == fb;
    fft(N, fa);

    if(equal) fb = fa;
    else fft(N, fb);

    mint inv_N = mint(N) ^ -1;
    for(int i = 0; i < N; i++) fa[i] *= fb[i] * inv_N;
    reverse(fa.begin() + 1, fa.end());

    fft(N, fa);
    fa.resize(n + m - 1);

    if(trim) {
      while(!fa.empty() && fa.back() == 0) fa.pop_back();
    }

    return fa;
  }

  template<typename T>
  vector<mint> expo(const vector<T>& a, int e, bool trim = true) {
    int n = sz(a);
    int N = [](int x) { while(x & x-1) x = (x | x-1) + 1; return x; }((n-1) * e + 1);
    vector<mint> fa(all(a)); fa.resize(N);

    fft(N, fa);

    mint inv_N = mint(N) ^ -1;
    for(int i = 0; i < N; i++)
      fa[i] = (fa[i] ^ e) * inv_N;
    reverse(fa.begin() + 1, fa.end());

    fft(N, fa);
    fa.resize((n-1) * e + 1);

    if(trim) {
      while(!fa.empty() && fa.back() == 0) fa.pop_back();
    }
    return fa;
  }
} // namespace NTT
