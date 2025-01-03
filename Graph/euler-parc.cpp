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
      if (nxt == p) continue;
      dfs(nxt, x);
    }

    rightPos[x] = (int)euler.size();
    euler.push_back(x);
  };

  dfs(root, -1);
  return {leftPos, rightPos, euler, depth, parent};
}
