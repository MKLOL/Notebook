void dfs(int x, int lev) {
  e[++K] = x; L[K] = lev; poz[x] = K;
  for(auto y: g[x]) {
    dfs(y,lev+1); e[++K] = x; L[K] = lev;
  }
}
void preprocess_lca() {
  dfs(1,0);
  for(int i=2;i<=K;++i) Lg[i] = Lg[i/2]+1;
  for(int i=1;i<=K;++i) rmq[0][i]=i;
  for(int i=1;(1<<i) < K; ++i) {
    for(int j=1;j<=K-(1<<i);++j) {
      rmq[i][j] = rmq[i-1][j];
      if(L[rmq[i-1][j + (1<<(i-1))]] < L[rmq[i][j]]) {
        rmq[i][j] = rmq[i-1][j + (1<<(i-1))];
      }
    }
  }
}
int lca(int x, int y) {
  int a = poz[x], b = poz[y];
  if(a>b) swap(a,b); 
  int l = Lg[b-a+1], sol = rmq[l][a];
  if(L[sol] > L[rmq[l][b - (1<<l) + 1]]) {
    sol = rmq[l][b - (1<<l) + 1];
  }
  return e[sol];
}