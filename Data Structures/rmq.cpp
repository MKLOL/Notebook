int rmq[log][Nmax], v[Nmax], lg[Nmax], N;
void genRmq() {
  for(int i=2;i<=N;++i) lg[i] = lg[i/2]+1;
  for(int i=1;i<=N;++i) rmq[0][i] = v[i];
  for(int i=1;(1<<i)<=N;++i) {
    for(int j=1;j+(1<<i)-1<=N;++j) {
      rmq[i][j] = min(rmq[i-1][j],rmq[i-1][j+ (1<<(i-1))]);
    }
  }
}
int query(int x,int y) {
    int l = lg[y-x+1], sh = y-x+1-(1<<l);
    return min(rmq[l][x], rmq[l][x+sh]);
}