ll MOD, inv[Nmax], fact[Nmax], ifact[Nmax];
ll c[nmax][nmax];
void make_comb(int N) { // N ~ 10^3
  for(int i=0;i<=N;++i) {
    c[i][0] = 1;
    for(int j=1;j<=i;++j) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
  }
}
void make_fact(int N) { // N ~ 10^6
  inv[1] = fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
  for(int i=2;i<=N;++i) {
    inv[i] = (MOD - (MOD/i) * inv[MOD%i] % MOD) % MOD;
    fact[i] = (fact[i-1]*i) % MOD;
    ifact[i] = (ifact[i-1]*inv[i]) % MOD;
  }
}
ll comb(ll a, ll b) { // a,b ~ 10^6
  ll ret = (fact[a] * ifact[b]) % MOD;
  return (ret * ifact[a-b]) % MOD;
}
ll vp(ll x) { //exponent of MOD in x!
  ll z = MOD, ret = 0;
  while(z <= x) { ret += x/z; z *= MOD;}
  return ret;
}
ll f(ll x) { // x! % MOD if we ignore the MOD factors
  if(x < MOD) return fact[x];
  ll z = 1, k = 0;
  do { z *= MOD; ++k; } while (z <= x/MOD);
  ll ret = (fact[x/z] * f(x%z)) % MOD;
  if(k%2 && t%2) return (MOD-ret)%MOD;
  else return ret;
}
ll getComb(ll A, ll B) { // A, B ~ 10^18
  if(vp(A) > vp(B) + vp(A-B)) return 0;
  if(MOD==2) return 1;
  return (((f(A)*inv[f(B)])%MOD)*inv[f(A-B)])%MOD;
}
