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
