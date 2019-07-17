int par[Nmax][Lmax],N,M, lg[Nmax], lvl[Nmax];
vi g[Nmax];
void dfs(int nod, int lev){
  lvl[nod] = lev;
  for(auto x: g[nod])
  if(!lvl[x]) { par[x][0] = nod; dfs(x, lev+1); }
}
int lca(int x,int y){
  if(lvl[x] < lvl[y]) swap(x,y);
  int log1=1, log2=1;
  for(;(1<<log1) < lvl[x]; ++log1);
  for(;(1<<log2) < lvl[y]; ++log2);
  for(int k = log1; k >= 0; --k){
    if(lvl[x] - (1 << k) >= lvl[y]) x = par[x][k];
  }
  if (x == y) return x;
  for(int k=log2; k>=0 ;--k) {
    if(par[x][k] && par[x][k] != par[y][k]){
      x = par[x][k]; y = par[y][k];
    }
  }
  return par[x][0];
}
void preprocessLca() {
  dfs(1,1);
  for(int k=1; (1<<k) <= N; ++k){
    for(int i=1;i<=N;++i){
      par[i][k] = par[par[i][k-1]][k-1];
    }
  }
}
