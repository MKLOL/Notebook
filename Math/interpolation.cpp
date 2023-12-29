int pw(int x, int y) {
  if(!y) return 1;
  if(y%2) return (1LL*x*pw(x, y-1)) % MOD;
  int z = pw(x, y/2);
  return (1LL*z*z)% MOD;
}
inline int inv(int x) {
  return pw(x, MOD-2);
}
inline int interpolate(vpi v, int x) {
  int ret = 0;
  int N = v.size();
  FOR(i, N) {
    int term = v[i].sc;
    FOR(j, N) {
      if(j!=i) {
        term = (1LL * term * ((x - v[j].fs +MOD) %MOD)) % MOD;
        term = (1LL * term * inv((v[i].fs - v[j].fs+MOD)%MOD)) % MOD;
      }
    }
    ret = (ret + term) % MOD;
  }
  return ret;
}
