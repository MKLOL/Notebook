struct entry {
  int nr[2], p;
} L[Nmax];
int P[LMax][Nmax], N, i, stp, cnt;
bool cmp(const entry &a, const entry &b) {
  return a.nr[0] == b.nr[0] ? (a.nr[1] < b.nr[1]) : (a.nr[0] < b.nr[0]);
}
int lcp(int x, int y) {
  int k, ret = 0; if (x == y) return N - x;
  for (k = stp - 1; k >= 0 && x < N && y < N; --k) {
    if (P[k][x] == P[k][y]) {
      x += 1 << k; y += 1 << k; ret += 1 << k;
    }
  } 
  return ret;
}
void suffArr(string A) {
  int N = a.size();
  for(int i=0;i<N;++i) P[0][i] = A[i] - 'a';
  for (stp = 1, cnt = 1; cnt >> 1 < N; ++stp, cnt <<= 1) {
    for (i = 0; i < N; ++i) {
      L[i].p = i; L[i].nr[0] = P[stp - 1][i];
      L[i].nr[1] = i + cnt < N ? P[stp - 1][i + cnt] : -1;
    }
    sort(L, L + N, cmp);
    for (i = 0; i < N; ++i)
      P[stp][L[i].p] = i > 0 && L[i].nr[0] == L[i - 1].nr[0] &&
          L[i].nr[1] == L[i - 1].nr[1] ? P[stp][L[i - 1].p] : i;
  }
}
