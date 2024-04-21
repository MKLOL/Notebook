int lcm(int a, int b) { return a / __gcd(a,b) * b; }

int fi[Nmax];
void makeFi(int lim) {
  fi[1] = 1; for(int i=2;i<=lim;++i) fi[i] = i-1;
  for(int i=2;i<=lim;++i) {
    for(int j=2;i*j<=lim;++j) fi[i*j] -= fi[i];
  }
}

// Euclid extins
int gcd(int a, int b, int &x, int &y) {
  if(!b) { x=1; y=0; return a; } 
  else {
    int x0, y0, d = gcd(b,a%b,x0,y0);
    x = y0; y = x0 - a/b *y0; return d;
  }
}
pair<int,int> euclid(int a, int b, int c) { //ax - by = c;
  int x, y, sol1, sol2; int d = gcd(a,b,x,y);
  if(c%d) return mp(0,0); //no sol
  else { sol1 = (c/d)*x; sol2 = -(c/d)*y; }
  //only if want minimal
  while(sol1 < 0 || sol2 < 0) { sol1 += b/d; sol2 += a/d;}
  while(sol1 >= b/d || sol2 >= a/d) { sol1 -= b/d; sol2 -= a/d;}
  return mp(sol1,sol2);
}
int inversmod(int a, int b) { //inverse of a mod b
  int x,y; gcd(a,b,x,y);
  if(x<0) { int k = (-x-1)/b + 1; x += k*b;}
  return x%b;
}
ll mulmod(ll a,ll b,ll c) {// a*b mod c
  ll x = 0, y=a%c;
  while(b > 0){ if(b%2 == 1) x = (x+y)%c; y = (y*2)%c; b /= 2; }
  return x%c;
}
vector<int> linSolver(int a, int b, int c) { //ax = b (mod c)
  vector<int> sol; int d = __gcd(a,c);
  pair<int, int> e = euclid(a,c,d);
  int x = e.fs, y = e.sc;
  if(b%d == 0) {
    x = ((b/d * x) % c + c) % c;
    for(int i=0;i<d;++i) {
      sol.pb(((x + c/d * i)%c + c)%c );
    }
  }
  return sol;
}

// Chinese remainder theorem x = a1 mod m1, x = a2 mod m2
pair<int,int> crt(int a1, int m1, int a2, int m2) {
  int d = gcd(m1,m2);
  pair<int,int> p = euclid(m1,m2,d);
  int s = p.fs, t = -p.sc;
  if (a1 % d != a2 % d) return make_pair(0, -1);
  int x = (s * a2 * m1 + t * a1 * m2) % (m1*m2);
  x = (x + m1*m2) % (m1*m2);
  return mp(x/d, m1*m2/d);
}
// x = a[i] (mod m[i]) also returns period (lcm)
pair<int,int> chinese(vector<int> &a, vector<int> &m) {
  pair<int,int> ret = mp(a[0], m[0]);
  for (int i = 1; i < a.size(); ++i) {
    ret = crt(ret.fs, ret.sc, a[i], m[i]); if (ret.sc == -1) break;
  }
  return ret;
}

// Fancy comb A, B ~ 10^18, MOD ~ 10^6 didn't test in a while tho
ll vp(ll x) { //exponent of MOD in x!
  ll z = MOD, ret = 0;
  while(z <= x) { ret += x/z; z *= MOD;}
  return ret;
}
ll inv[Nmax], fact[Nmax];
void make_fact(int N) {
  inv[1] = fact[0] = fact[1] = 1;
  for(int i=2;i<=N;++i) {
    inv[i] = (MOD - (MOD/i) * inv[MOD%i] % MOD) % MOD;
    fact[i] = (fact[i-1]*i) % MOD;
  }
}
ll f(ll x) { // x! % MOD if we ignore the MOD factors
  if(x < MOD) return fact[x];
  ll z = 1, k = 0;
  do { z *= MOD; ++k; } while (z <= x/MOD);
  ll ret = (fact[x/z] * f(x%z)) % MOD;
  if(k%2 && t%2) return (MOD-ret)%MOD;
  else return ret;
}
ll getComb(ll A, ll B) {
  if(vp(A) > vp(B) + vp(A-B)) return 0;
  if(MOD==2) return 1;
  return (((f(A)*inv[f(B)])%MOD)*inv[f(A-B)])%MOD;
}
