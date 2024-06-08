class TwoSAT {
public:
  int N; // number of literals
  vi s, c, sol, viz, vz;
  vvi g, gt, v; // graph and reverse graph
 
  TwoSAT(int sz) { // number of literals
    N = sz;

    c.resize(N * 2 + 2);
    sol.resize(N * 2 + 2);
    viz.resize(N * 2 + 2);
    vz.resize(N * 2 + 2);
    g.resize(N * 2 + 2);
    gt.resize(N * 2 + 2);
    v.resize(N * 2 + 2);
  }
 
  void dfs(int x) {

    viz[x] = 1; 
    for(auto y: g[x]) 
      if(!viz[y]) 
        dfs(y); 
    s.pb(x);
  }
  
  void dfs2(int x, int comp) {
    viz[x] = 0; c[x] = comp; v[comp].push_back(x);
    for(auto y: gt[x]) if(viz[y]) dfs2(y,comp);
  }
  
  // negation
  int ng(int x) { if(x%2) return x-1; return x+1;}
  
  // assign val to node x
  bool f(int x, int val) {
    vz[x] = 1;
    for(auto y: v[x]) {
      if(sol[y] && sol[y]!=val) return false; sol[y] = val;
    }
    for(auto y: v[x]) {
      y = ng(y); if(sol[y] && sol[y]!=3-val) return false;
      if(!sol[y]) return f(c[y],3-val);
    }
    return true;
  }
 
  bool sat() {
    int comp = 0;
    for(int i=2;i<=2*N+1;++i) if(!viz[i]) dfs(i);
    for(int i=sz(s)-1;i>=0;--i) if(viz[s[i]]) dfs2(s[i],++comp);
    for(int i=1;i<=comp;++i) if(!vz[i]) if(!f(i,1)) return false;
    return true;
  }
 
  // add (x OR y), s 0 normal,1 negation
  void add_disj(int x, int sx, int y, int sy) {
    g[2*x+(1-sx)].push_back(2*y+sy);
    g[2*y+(1-sy)].push_back(2*x+sx);
    gt[2*y+sy].push_back(2*x+(1-sx));
    gt[2*x+sx].push_back(2*y+(1-sy));
  }
 
  void clear() {
    FOR(i, 2*N+2) {
      viz[i] = vz[i] = sol[i] = c[i] = 0;
      v[i].clear();
      g[i].clear();
      gt[i].clear();
 
    }
  }
};
