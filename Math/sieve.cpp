class Sieve {
public:
  vi fp; // first prime (i == fp[i] means it's prime itself)
  vi primes; // all primes <= N
  vi nump; // num unique primes
  Sieve(int N) {
    fp.resize(N+10);
    nump.resize(N+10);
    for(int i=2;i<=N;++i) {
      if(!fp[i]) {
        primes.pb(i);
        for(int j=i;1LL*i*j<=N;++j) {
          if(!fp[i*j]) fp[i*j] = i;
          ++nump[i*j];
        }
        fp[i] = i;
      }
    }
  }
  vpi getPrimes(int x) { // prime decomp of x
    vpi ret;
    while(x > 1) {
      int p = fp[x], cnt = 0;
      while(x % p == 0) {
        x /= p; ++cnt;
      }
      ret.pb(mp(p, cnt));
    }
    return ret;
  }
  bool isPrime(int x) {
    return fp[x] == x;
  }
};
