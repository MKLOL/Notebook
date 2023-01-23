struct cmp {
  bool operator()(piii a, piii b) { return a.fs > b.fs;}
};
priority_queue<piii, vector<piii>, cmp> pq;
namespace std {
  template <>
  struct hash<pii> {
  public:
    size_t operator()(pair<int, int> x) const throw() {
      size_t h = x.fs + x.sc * 1145; return h;
    }
  };
}
for (int news=state; news; news=state&(news-1))//all subsets of state


CYGWIN stack since ubuntu for windows doesn't let ulimit yet.

g++.exe -Wl,--stack,900000000 a.cpp && ./a.exe < test.in > test.out

OSX:
g++-9 -Wl,-stack_size -Wl,100000000 test.cpp && ./a.out


Java location openwebstart for topcoder sec. (remove MD5).
Usually in .cache do find . | grep java.security
./.cache/icedtea-web/jvm-cache/eclipse-temurin_11.0.13/conf/security/java.security

# How to run a for multi threaded

#Commands:
g++-12 -O2 -fopenmp -Wl,-stack_size -Wl,10000000000 cf1.cpp && time ./a.out test.in
export OMP_STACKSIZE=101010100

#pragma omp parallel for collapse(3) schedule(dynamic, 4)
for (int i=0;i<N;++i) {
  for (int j=0;j<N;++j) {
    for (int k=0;k<N;++k) {
      if (i >= j || j >= k) continue;
      #pragma omp critical
      {
        ret += make(i,1,j,1,k,1);
      }
    }
  }
}

extra info:
The integer after collapse (i.e., 2 in this example) identifies how many loops to be parallelized