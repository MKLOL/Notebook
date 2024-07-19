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
