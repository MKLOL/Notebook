pll contToFrac(vector<ll> &a, int start) {
  if(start >= a.size()-1) return mp(a[start],1);
  pll p = contToFrac(a,start+1);
  return reduce(a[start] * p.fs + p.sc, p.fs);
}
vector<ll> fracToCont(pll frac) {
  vector<ll> ret; ll A = frac.fs, B = frac.sc;
  while(true) {
    if(B == 0 || (A < B && ret.size()!= 0) ) break; ret.pb(A/B);
    ll newA = B, newB = A%B; A = newA; B = newB;
  }
  return ret;
}
