typedef complex<double> cdouble;
typedef vector<cdouble> pol;
int cmp(double a, double b) { //same as geom2d
  if(a + eps <= b) return -1; if(a <= b + eps) return 0; return 1;
}
int cmp(cdouble x, cdouble y = 0) { return cmp(abs(x), abs(y));}
pol deriv(pol &a) {
  int N = a.size(); pol ret(N-1);
  for(int i=1;i<N;++i) ret[i-1] = a[i]*cdouble(i); return ret;
}
pair<pol, cdouble> ruffini(pol &a, cdouble z) {// divide by (x-z)
  int N = a.size(); pol ret;
  if (N == 0) return mp(ret, 0); if (N == 1) return mp(ret, a[0]);
  ret.resize(N-1); ret[N-2] = a[N-1];
  for(int i=N-2;i>0;--i) ret[i-1] = ret[i]*z + a[i];
  return mp(ret, ret[0]*z + a[0]);
}
cdouble getVal(pol &a, cdouble z) { return ruffini(a,z).sc; }
cdouble find_one_root(pol &a, cdouble x) {
  pol a1 = deriv(a); pol a2 = deriv(a1);
  int N = a.size(), m = 1000;
  while (m--) {
    cdouble y0 = getVal(a,x);
    if(cmp(y0) == 0) break;
    cdouble G = getVal(a1,x) / y0;
    cdouble H = G * G - getVal(a2,x) / y0;
    cdouble R = sqrt(cdouble(N-1) * (H * cdouble(N) - G * G));
    cdouble D1 = G + R, D2 = G - R;
    cdouble A = cdouble(N) / (cmp(D1, D2) > 0 ? D1 : D2);
    x -= A; if (cmp(A) == 0) break;
  }
  return x;
}