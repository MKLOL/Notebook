struct Edge {
  int u, v; ll cap, flow; Edge() {}
  Edge(int u, int v, ll cap): u(u), v(v), cap(cap), flow(0) {}
};
int N; vector<Edge> E;
vi d, pt, g[Nmax]; //edge indices
inline void addEdge(int u, int v, int cap) {
  E.pb(Edge(u, v, cap)); g[u].pb(E.size() - 1);
  E.pb(Edge(v, u, 0)); g[v].pb(E.size() - 1);
}
inline int BFS(int S, int T) {
  queue<int> q; q.push(S);
  fill(d.begin(), d.end(), N + 1);
  d[S] = 0;
  while(!q.empty()) {
    int u = q.front(); q.pop();
    if (u == T) break;
    for (int k: g[u]) {
      Edge &e = E[k];
      if (e.flow < e.cap && d[e.v] > d[e.u] + 1) {
        d[e.v] = d[e.u] + 1; q.push(e.v);
      }
    }
  }
  return d[T] != N + 1;
}
ll DFS(int u, int T, ll flow = -1) {
  if (u == T || flow == 0) return flow;
  for (int &i = pt[u]; i < g[u].size(); ++i) {
    Edge &e = E[g[u][i]];
    Edge &oe = E[g[u][i]^1];
    if (d[e.v] == d[e.u] + 1) {
      ll amt = e.cap - e.flow;
      if (flow != -1 && amt > flow) amt = flow;
      if (ll pushed = DFS(e.v, T, amt)) {
        e.flow += pushed; oe.flow -= pushed; return pushed;
      }
    }
  }
  return 0;
}
ll MaxFlow(int S, int T) {
  ll total = 0; pt.resize(N); d.resize(N);
  while (BFS(S, T)) {
    fill(pt.begin(), pt.end(), 0);
    while (ll flow = DFS(S, T)) total += flow;
  }
  return total;
}
