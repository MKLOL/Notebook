int low[Nmax],depth[Nmax],viz[Nmax];
vi nnodes[Nmax];
vi g[Nmax];

vector<int> gx[Nmax]; // new graph, where each node is the bi-component
int CNT = 0;


map<pii,int> de; // deleted edges
void dfs(int x, int p, int dep) {
  viz[x] = 1; depth[x]=dep; low[x]=dep;
  for(auto y: g[x]) {
    if(!viz[y]) {
      dfs(y,x,dep+1); 
      low[x] = min(low[x],low[y]);
      if(low[y] > depth[x]) { // this means that edge x -> y is a bridge
        de[mp(x,y)] = 1;
        de[mp(y,x)] = 1;
      }
    } else if(y!=p) {
      low[x]=min(low[x],depth[y]);
    }
  }
}
void df(int x) {
  nnodes[CNT].pb(x);
  hc[x] = CNT;
  for(auto y : g[x]) {
    // if the edge is not a bridge
    if(de[mp(x,y)]) continue;
    if(!hc[y]) df(y);
  }
}



void biconnect() {
  for(int i=1;i<=N;++i) {
    if(!viz[i]) dfs(i,0,0);
  }
  for(int i=1;i<=N;++i) {
    // if no component
    if(!hc[i]) {
      ++CNT;
      df(i);
    }
  }
  for(int i=1;i<=N;++i) {
    for(auto y : g[i]) {
      if(hc[i] != hc[y]) {
        // if the edge doesn't exist yet
        if(!he[mp(hc[i], hc[y])]) {
          he[mp(hc[i], hc[y])] = 1;
          he[mp(hc[y], hc[i])] = 1;
          gx[hc[y]].pb(hc[i]);
          gx[hc[i]].pb(hc[y]);
        }
      }
    }
  }
}

