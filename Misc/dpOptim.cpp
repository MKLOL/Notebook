/* 1. best[i] = max(best[i] + a[i]*b[j]) a increasing, b decreasing
max:q(a[i]),add(b[i],best[i]); min: q(-a[i]),add(b[i],-best[i])
2. best[i][j] = max(best[i-1][k] + b[k]*a[j]), a increasing, b decreasing
Do independently for each i
max:q(a[j]),add(b[j],best[i-1][j]);min:q(-a[j]),add(b[j],-best[i-1][j]) */
int cnt; pll h[Nmax]; //stores the lines
pll operator-(pll a, pll b) { return mp(a.fs-b.fs, a.sc-b.sc); }
inline int cw(pll a, pll b, pll c) {
  pll x = a-c, y = b-c; return x.fs*y.sc <= x.sc*y.fs; //Beware overflow
}
void add(ll a, ll b) { // Add ax+b (decreasing order of a)
  h[cnt++] = mp(a,b);
  while(cnt > 2 && cw(h[cnt-3],h[cnt-2],h[cnt-1])) {
    h[cnt-2] = h[cnt-1]; --cnt;
  }
}
long long query(long long x) { //return max ax+b
  int st = 0, dr = cnt - 2, ret = cnt-1;
  while(st <= dr) {
    int mij = (st+dr)/2;
    if(h[mij].fs * x + h[mij].sc > h[mij+1].fs*x + h[mij+1].sc) {
       ret = mij; dr = mij-1;
    } else st = mij+1;
  }
  return h[ret].fs * x + h[ret].sc;
}
/*KNUTH: d[i][j] = min(d[i][k] + d[k][j] + c[i][j]) 
DIVCONQ: d[i][j] = min(d[i-1][k] + c[k][j]), c[i][j] <= c[i][j+1]
compute(j, l, r, optL, optR) m = (l+r)/2; brut(m,optL,optR); 
compute(j,l,m-1,optL, opt[m][j]); compute(j,m+1,r, opt[m][j], optR);
*/
