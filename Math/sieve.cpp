class Sieve {
private:
  vi fp; // first prime (i == fp[i] means it's prime itself)
public:
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
  vi getPrimes(int x) { // all primes dividing x
    vi ret;
    while(x > 1) {
      int p = fp[x];
      ret.pb(p);
      while(x % p == 0) x /= p;
    }
    return ret;
  }
  bool isPrime(int x) {
    return fp[x] == x;
  }
};
