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