class RabinKarp {
private:
  vi nr[2], pw[2];
  int p[2]= {47, 149};
  int MD[2] = {666013, 991777};
public:
  RabinKarp(string &s) {
    int N = sz(s);
    FOR(k,2) {
      nr[k].resize(N+1);
      pw[k].resize(N+1);
      pw[k][0] = 1;
      nr[k][0] = 0;
    }
    for(int i=1;i<=N;++i) {
      FOR(k,2) {
        pw[k][i] = (1LL*pw[k][i-1] * p[k]) % MD[k];
        nr[k][i] = (1LL*nr[k][i-1] * p[k] + s[i-1]) % MD[k];
      }
    }
  }
  int eq(int x, int y, int x1, int y1) {
    if(y-x != y1-x1) return 0;
    ++x, ++y, ++x1, ++y1;
    FOR(k, 2) {
      int sol1 = (1LL*nr[k][y] - (1LL*pw[k][y-x+1]*nr[k][x-1]) % MD[k] + MD[k]) % MD[k];
      int sol2 = (1LL*nr[k][y1] - (1LL*pw[k][y1-x1+1]*nr[k][x1-1]) % MD[k] + MD[k]) % MD[k];
      if(sol1 != sol2) return 0;
    }
    return 1;
  }
};
