int par[Nmax],h[Nmax]
int findx(int x) {
  int R = x, y; while(par[R] != R) R = par[R];
  while(par[x] != x) { y = par[x]; par[x] = R; x = y;}
  return R;
}
void unite(int x, int y) {
  x = findx(x); y = findx(y); if (x == y) return;
  if(h[x] > h[y]) { par[y] = x; h[x] += h[y]; }
  else { par[x] = y; h[y] += h[x]; }
}