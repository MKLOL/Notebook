vector<int> zeroOneBFS(int start, int K) {
  vector<int> dist(N, 1010100);
  dist[start] = 0;
  deque<int> dq;
  dq.pb(start);
 
  while(!dq.empty()) {
    int u = dq.front(); 
    dq.pop_front();
    for(auto &edge : g[u]) {
      int v = edge.fs;
      int w = edge.sc > K;
      if(dist[u] + w < dist[v]) {
        dist[v] = dist[u] + w;
        if(w == 0) dq.push_front(v);
        else dq.push_back(v);
      }
    }
  }
  return dist;
}
