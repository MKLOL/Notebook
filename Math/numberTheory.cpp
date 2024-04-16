int fp[Nmax]; //fp = first prime, i == fp[i] means prime
int np[Nmax]; //np = num primes
vi makeSieve(int lim) {
  vi ret;
  for(int i=2;i<=lim;++i) {
    if(!fp[i]) {
      ret.pb(i);
      for(int j=i;i*j<=lim;++j) {
        if(!fp[i*j]) fp[i*j] = i;
        ++np[j];
      }
      fp[i] = i;
    }
  }
  return ret;
}
vi getPrimes(int x) {
  vi ret;
  while(x > 1) {
    int p = fp[x];
    ret.pb(p);
    while(x % p == 0) x /= p;
  }
  return ret;
}

int fi[Nmax];
void makeFi(int lim) {
  fi[1] = 1; for(int i=2;i<=lim;++i) fi[i] = i-1;
  for(int i=2;i<=lim;++i) {
    for(int j=2;i*j<=lim;++j) fi[i*j] -= fi[i];
  }
}

int lcm(int a, int b) { return a / __gcd(a,b) * b; }
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
// x = a1 mod m1, x = a2 mod m2
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
