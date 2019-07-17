const int MAX = 1<<20;
typedef int value;
typedef complex<double> comp;
int N, p[MAX];
comp omega[MAX], omega_tmp[MAX], a1[MAX], a2[MAX], z1[MAX], z2[MAX];
void fft(comp *a, comp *z) {
  FOR(i, N) z[i] = a[p[i]]; int t = N;
  for (int size = 1; size < N; size *= 2) {
    t /= 2; FOR(j,size) omega_tmp[j] = omega[j*t];
    for (int i = 0; i < N; i += 2*size) {
      FOR(j,size) {
        comp c = omega_tmp[j] * z[i+j+size];
        z[i+j+size] = z[i+j] - c; z[i+j] += c;
      }
    }
  }
}
void mult(value *a, value *b, value *c, int len) {
  N = 2*len; while (N & (N-1)) ++N;
  p[0] = 0; int k = 0, t = -1;
  while ((1 << k) < N) ++k;
  for(int i = 1; i < N; ++i) {
    if ((i&(i-1)) == 0) ++t;
    p[i] = p[i^(1<<t)]; p[i] |= 1 << (k-t-1);
  } 
  FOR (i, N) { a1[i] = 0; a2[i] = 0; }
  FOR (i, len) { a1[i] = double(a[i]); a2[i] = double(b[i]); }
  FOR (i, N/2) {
    omega[i] = polar(1.0, 2*M_PI/N*i);
    omega[N-i-1] = conj(omega[i]);
  }
  fft(a1, z1); fft(a2, z2);
  FOR (i, N) omega[i] = conj(omega[i]);
  FOR (i, N) a1[i] = z1[i] * z2[i] / comp(N, 0);
  fft(a1, z1);
  FOR (i, 2*len) c[i] = value(round(z1[i].real()));
}
