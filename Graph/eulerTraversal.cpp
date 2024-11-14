class EulerTraversal {
public:
  vi e; // list of nodes in the traversal
  vi lvl; // level of node
  vi L, R; // first and last occurence of node in traversal
  vvi g;

  EulerTraversal(vvi &graph, int root): g(graph) {
    poz.resize(sz(g)+1);
    FOR(i, sz(poz)) poz[i] = -1;
    dfs(root, 0);
  }

  void dfs(int x, int lev) {
    lvl[x] = lev;
    L[x] = sz(e);
    e.pb(x);

    for(auto y: g[x]) {
      if(poz[y] == -1) {
        dfs(y,lev+1);
        e.pb(x);
      }
    }
    R[x] = sz(e);
    e.pb(x);
  }
};