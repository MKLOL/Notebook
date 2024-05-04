// N ~ 10^6
class Combinations {
public:
  vector<mint> inv, fact, ifact;

  Combinations(int N) {
    inv.resize(N+10), fact.resize(N+10), ifact.resize(N+10);
    inv[1] = fact[0] = fact[1] = ifact[0] = ifact[1] = 1;
    for(int i=2;i<=N;++i) {
      inv[i] = inv[MOD%i] * (MOD - MOD/i);
      fact[i] = fact[i-1]*i;
      ifact[i] = ifact[i-1]*inv[i];
    }
  }
  // a > b
  mint comb(ll a, ll b) {
    if(a < b) return mint(0);
    return fact[a] * ifact[b] * ifact[a-b];
  }
};

// N ~ 10^3
ll c[nmax][nmax];
void make_comb(int N) {
  for(int i=0;i<=N;++i) {
    c[i][0] = 1;
    for(int j=1;j<=i;++j) c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
  }
}
