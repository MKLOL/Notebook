int N, d[Nmax], viz[Nmax];
vector<pii> g[Nmax];
priority_queue<pii> pq;
void dijkstra(int r) {
  for(int i=1;i<=N;++i) d[i] = inf;
  d[r] = 0; pq.push(mp(0,r));
  while(!pq.empty()) {
    int x = pq.top().sc; pq.pop(); viz[x] = 1;
    for(auto a: g[x]) {
      int y = a.fs, c = a.sc;
      if(!viz[y]) {
        if(d[y] > c + d[x]) {
          d[y] = c + d[x]; pq.push(mp(-d[y],y));
        }
      }
    }
  }
}