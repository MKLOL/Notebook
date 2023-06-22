

#define S 333 // sqrt(N)
bool cmp(pii A, pii B)
{
  if (A.fs / S != B.fs / S) return A.fs / S < B.fs / S;
  return A.sc > B.sc;
}

sort(all(qr), cmp);
int st = 0;
int dr = -1;
ll ret = 0;
for (int i=0;i<sz(qr);++i) {
  auto qc = qr[i];
  for (int q = dr+1; q <= qc.sc; ++ q) {
    addE(C[q]);
  }
  for (int q=st-1;q >= qc.fs;--q) {
    addE(C[q]);
  }
  for (int q = dr; q > qc.sc; --q) {
    remE(C[q]);
  }
  for (int q=st;q<qc.fs;++q) {
    remE(C[q]);
  }
  st = qc.fs;
  dr = qc.sc;
}