int A[Nmax][Nmax], N, M;
int rmq[lmax][lmax][Nmax][Nmax],lg[Nmax];
void genRmq() {
  for(int i=2;i<=max(N,M);++i) lg[i] = lg[i/2] + 1;
  for(int k=0;(1<<k)<=N;++k) {
    for(int l=0;(1<<l)<=M;++l) {
      for(int i=1;i+(1<<k)-1<=N;++i) {
        for(int j=1;j+(1<<l)-1<=M;++j) {
          if(!k && !l) rmq[k][l][i][j] = A[i][j];
          else if(!k) rmq[k][l][i][j] = min(rmq[k][l-1][i][j], 
                              rmq[k][l-1][i] [j+(1<<(l-1))]);
          else rmq[k][l][i][j] = min(rmq[k-1][l][i][j], 
                              rmq[k-1][l][i+(1<<(k-1))][j]);
        }
      }
    }
  }
}
int query(int xa, int ya, int xb, int yb) {//(xa,ya)topleft (xb,yb) bottomright
  int lx = lg[xb-xa+1], mx = xb+1-(1<<lx);
  int ly = lg[yb-ya+1], my = yb+1-(1<<ly);
  int ret1 = min(rmq[lx][ly][xa][ya], rmq[lx][ly][xa][my]);
  int ret2 = min(rmq[lx][ly][mx][ya], rmq[lx][ly][mx][my]);
  return min(ret1,ret2);
}