class LCAFinder {
public:
  vi e, L, poz;
  SparseTable rmq;
  vvi g;

  LCAFinder(vvi &graph, int root): g(graph) {
    poz.resize(sz(graph)+1);
    FOR(i, sz(poz)) poz[i] = -1;
    preprocessLca(root);
  }

  void preprocessLca(int root) {
    dfs(root, 0);
    rmq = SparseTable(L);
  }

  void dfs(int x, int lev) {
    poz[x] = sz(e);
    e.pb(x);
    L.pb(lev); 

    for(auto y: g[x]) {
      if(poz[y] == -1) {
        dfs(y,lev+1);
        e.pb(x);
        L.pb(lev);
      }
    }
  }

  int lca(int x, int y) {
    int a = poz[x], b = poz[y];
    if(a>b) swap(a,b);
    int sol = rmq.queryIndex(a,b);
    return e[sol];
  }

  int dist(int x, int y) {
    int a = poz[x], b = poz[y];
    if(a>b) swap(a,b);
    int sol = rmq.queryIndex(a,b);
    return L[a] + L[b] - 2* L[sol];
  }
};