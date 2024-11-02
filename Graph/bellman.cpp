ll inf = 1000000000LL * 1000000000;

class Graph {
public:
  int Nx;
  vector<ll> d, cnt;
  vector<vector<pll>> g;

  queue<int> q;

  Graph(int n): Nx(n), d(n+1, inf), cnt(n+1, 0), g(n+1) {}

  void addEdge(int x, int y, ll cost) {
    g[x].push_back({y, cost});
  }

  void bellman(int r) {
    d[r] = 0;
    q.push(r);

    while(!q.empty()) {
      int x = q.front();
      ++cnt[x]; 
      if(cnt[x] > Nx) return; 
      q.pop();
      for(auto p: g[x]) {
        ll y = p.fs, c = p.sc;
        if(d[y] > d[x] + c) { 
          d[y] = d[x] + c;
          q.push(y);
        }
      }
    }
  }
};