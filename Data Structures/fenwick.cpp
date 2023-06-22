int AIB[Nmax], N;
inline int zeros(int x) { return x & (-x); }
inline void add(int x, int q) {
  for (int i = x; i <= N; i += zeros(i)) AIB[i]+=q;
}
inline int comp(int x) {
  int ret = 0;
  for (int i = x; i > 0; i -= zeros(i)) ret += AIB[i];
  return ret;
}

inline int comp(int l, int r) {
  l = max(1, l);
  r = min(N, r);
  return comp(r) - comp(l-1);
}