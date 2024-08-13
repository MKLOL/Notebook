class TopoSort {
 
  public:
  int N;
  vpi v;
  vvi g;
 
  TopoSort(int n): N(n), g(n) {}
 
  void addEdge(int x, int y) {
    v.pb({x,y});
    g[y].pb(x);
  }
 
  vi topoSort() {
    vi cnt(N);
    for(auto e : v) {
      cnt[e.fs]++;
    }
    queue<int> Q;
    vi ret;
    FOR(i, N) {
      if (cnt[i] == 0) {
        Q.push(i);
      }
    }
    while(sz(Q)) {
      auto x = Q.front(); Q.pop();
      ret.pb(x);
      for (auto n : g[x]) {
        --cnt[n];
        if (cnt[n] == 0) Q.push(n);
      }
    }
    if (sz(ret) != N) return {};
    else return ret;
  }
  
};
