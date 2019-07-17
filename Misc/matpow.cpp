vvll mul(vvll &a, vvll &b) {
  int N = sz(a), M = sz(a[0]), P = sz(b[0]);
  vvll ret(N, vll (P,0));
  FOR(i,N) FOR(j,P) FOR(k,M)
    ret[i][j] += a[i][k]*b[k][j]; ret[i][j] %= MOD;
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
