class Graph {

  public:
  int Nx;
  vector<ll> d, viz;
  vector<vector<pll>> g;

  Graph(int n): Nx(n), d(n+1, inf), viz(n+1, 0), g(n+1) {}

  void addEdge(int x, int y, ll cost) {
    g[x].push_back({y, cost});
  }

  void runDijkstra(const vector<int>& s) {
    priority_queue<pll, vector<pll>, greater<pll>> pq;
    for (int i = 1; i <= Nx; ++i) d[i] = inf;
    fill(viz.begin(), viz.end(), 0);

    for (int x : s) {
      d[x] = 0;
      pq.push({0, x});
    }

    while (!pq.empty()) {
      ll x = pq.top().second;
      pq.pop();
      if (viz[x]) continue;
      viz[x] = 1;
      
      for (const auto& a : g[x]) {
        ll y = a.first, c = a.second;
        if (d[y] > d[x] + c) {
            d[y] = d[x] + c;
            pq.push({d[y], y});
        }
      }
    }
  }
  void runDijkstra(int s) {
    runDijkstra({s});
  }
};
