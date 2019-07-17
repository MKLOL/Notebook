int N,w[Nmax],low[Nmax],depth[Nmax],comp,viz[Nmax];
vector<pii> m; //edges stack
vector<vi> c; //result
vi g[Nmax], com; //adjancency list
void dfs(int x, int p, int dep) {
  viz[x] = 1; depth[x]=dep; low[x]=dep;
  for(auto y: g[x]) {
    if(!viz[y]) {
      m.pb(mp(x,y)); dfs(y,x,dep+1); low[x] = min(low[x],low[y]);
      if(low[y] >= depth[x]) {
        ++comp; com.clear();
        while(true) {
          int t = m.back().fs, u = m.back().sc;
          if(w[t] != comp) { w[t] = comp; com.pb(t); }
          if(w[u] != comp) { w[u] = comp; com.pb(u); }
          m.pop_back(); if(t==x && u==y) break;
        }
        c.pb(com);
      }
    } else if(y!=p) low[x]=min(low[x],depth[y]);
  }
}
void biconnect() {
  for(int i=1;i<=N;++i) {
    if(!viz[i]) dfs(i,0,0);
  }
}