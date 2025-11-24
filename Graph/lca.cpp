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
        e.pb(x); L.pb(lev);
      }
    }
  }
  int lca(int x, int y) {
    int a = poz[x], b = poz[y]; if(a>b) swap(a,b);
    int sol = rmq.queryIndex(a,b); return e[sol];
  }
  int dist(int x, int y) {
    int a = poz[x], b = poz[y]; if(a>b) swap(a,b);
    int sol = rmq.queryIndex(a,b);
    return L[a] + L[b] - 2* L[sol];
  }
};
// LCA LOG
class LCAFinder {
public:
  vector<vector<int>> g, par;
  vector<int> lvl;
  int N, L;
  void dfs(int node, int level) {
    lvl[node] = level;
    for (int x : g[node]) if (lvl[x] == -1) { par[x][0] = node; dfs(x, level + 1); }
  }
  void preprocessLca(int root) {
    lvl.assign(N, -1); L = 0; for (int i = 1; i <= N; i <<= 1) L++;
    par.assign(N, vector<int>(L, -1));
    dfs(root, 0);
    for (int k = 1; k < L; ++k) for (int i = 0; i < N; ++i) if (par[i][k-1] != -1) par[i][k] = par[par[i][k-1]][k-1];
  }
  LCAFinder(vector<vector<int>> graph, int root) : g(graph) {
    N = g.size(); preprocessLca(root);
  }
  int lca(int x, int y) {
    if (lvl[x] < lvl[y]) swap(x, y);
    for (int k = L - 1; k >= 0; --k) if (lvl[x] - (1 << k) >= lvl[y]) x = par[x][k];
    if (x == y) return x;
    for (int k = L - 1; k >= 0; --k) if (par[x][k] != par[y][k]) { x = par[x][k]; y = par[y][k]; }
    return par[x][0];
  }
  int dist(int x, int y) {
    int z = lca(x, y); return lvl[x] + lvl[y] - 2 * lvl[z];
  }
  int preLca(int x, int y) {
    int lcaNode = lca(x, y); if (x == lcaNode) return x;
    for (int k = L - 1; k >= 0; --k) if (par[x][k] != -1 && lvl[par[x][k]] > lvl[lcaNode]) x = par[x][k];
    return x;
  }
};
