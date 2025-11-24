// EULER PARC
static tuple<vector<int>, vector<int>, vector<int>, vector<int>, vector<int>>
dfs_info(const vector<vector<int>> &g, int root) {
  int n = g.size();
  vector<int> leftPos(n), rightPos(n), depth(n), parent(n, -1), euler;
  euler.reserve(2 * n);
  function<void(int,int)> dfs = [&](int x, int p) {
    depth[x] = (p == -1 ? 1 : depth[p] + 1);
    parent[x] = p;
    leftPos[x] = (int)euler.size();
    euler.push_back(x);
    for (auto nxt : g[x]) {
      if (nxt == p) continue; dfs(nxt, x);
    }
    rightPos[x] = (int)euler.size();
    euler.push_back(x);
  };
  dfs(root, -1);
  return {leftPos, rightPos, euler, depth, parent};
}
// EULER CYCLE
vector<int> eulerTour(vvpi g, int start) { // first int of the pii is the adj node, second is edge id. 
  int max_edge = 0;
  for (const auto& edges : g) {
    for (const auto& edge : edges) {
      max_edge = max(max_edge, edge.second);
    }
  }
  vector<int> isD(max_edge + 1, 0);
  vector<int> result;
  function<void(int)> dfse = [&](int x) {
    while(sz(g[x])) {
      auto n = g[x].back();
      if (isD[n.second]) g[x].pop_back();
      if (isD[n.second] == 0) {
        isD[n.second] = 1;
        g[x].pop_back();
        dfse(n.first);
      }
    }
    result.push_back(x);
  };
  dfse(start);
  return result;
}
// EULER TRAVERSAL
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
    lvl[x] = lev; L[x] = sz(e); e.pb(x);
    for(auto y: g[x]) {
      if(poz[y] == -1) {
        dfs(y,lev+1); e.pb(x);
      }
    }
    R[x] = sz(e); e.pb(x);
  }
};
