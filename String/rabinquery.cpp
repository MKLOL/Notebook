class RabinKarp {
private:
  vi primes{47, 149, 97, 101, 271};
  vi mods{666013, 991777, 160117, 362561, 760289};

public:
  int num, N;
  vvi nr, pw;
  vi p, MD;

  RabinKarp(string &s, int nm=2, bool random = true) {
    assert(nm <= 5);
    num = nm;
    N = sz(s);
    nr.resize(num);
    pw.resize(num);

    if(random) {
      mt19937 rng(time(0));
      shuffle(all(primes), rng);
      shuffle(all(mods), rng);
    }
    FOR(k, num) {
      p.pb(primes[k]);
      MD.pb(mods[k]);
    }

    FOR(k,num) {
      nr[k].resize(N+1);
      pw[k].resize(N+1);
      pw[k][0] = 1;
      nr[k][0] = 0;
    }
    for(int i=1;i<=N;++i) {
      FOR(k,num) {
        pw[k][i] = (1LL*pw[k][i-1] * p[k]) % MD[k];
        nr[k][i] = (1LL*nr[k][i-1] * p[k] + s[i-1]) % MD[k];
      }
    }
  }
  int eq(int x, int y, int x1, int y1) {
    // slightly faster than calling query because early return 0 if not equal
    if(y-x != y1-x1) return 0;
    ++x, ++y, ++x1, ++y1;
    FOR(k, num) {
      int sol1 = (1LL*nr[k][y] - (1LL*pw[k][y-x+1]*nr[k][x-1]) % MD[k] + MD[k]) % MD[k];
      int sol2 = (1LL*nr[k][y1] - (1LL*pw[k][y1-x1+1]*nr[k][x1-1]) % MD[k] + MD[k]) % MD[k];
      if(sol1 != sol2) return 0;
    }
    return 1;
  }
  pii query(int x, int y) {     // use only if num == 2
    assert (num == 2);
    ++x; ++y;
    int k = 0;
    int sol1 = (1LL*nr[k][y] - (1LL*pw[k][y-x+1]*nr[k][x-1]) % MD[k] + MD[k]) % MD[k]; 
    k = 1;
    int sol2 = (1LL*nr[k][y] - (1LL*pw[k][y-x+1]*nr[k][x-1]) % MD[k] + MD[k]) % MD[k];
    return mp(sol1, sol2);
  }
  vi queryVec(int x, int y) { // slower cause vector
    vi ret;
    ++x; ++y;
    FOR(k, num) {
      ret.pb((1LL*nr[k][y] - (1LL*pw[k][y-x+1]*nr[k][x-1]) % MD[k] + MD[k]) % MD[k]);
    }
    return ret;
  }
};