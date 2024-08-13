class UnionFind {
public:
  vector<int> par;
  vector<int> h;
  int size;

  // Constructor
  UnionFind(int size) : size(size) {
    par.resize(size);
    h.resize(size, 1);
    for (int i = 0; i < size; ++i) {
      par[i] = i;
    }
  }

  // Find operation with path compression
  int find(int x) {
    int R = x, y;
    while (par[R] != R) {
      R = par[R];
    }
    while (par[x] != x) {
      y = par[x];
      par[x] = R;
      x = y;
    }
    return R;
  }

  // Union operation by rank
  int unite(int x, int y) {
    x = find(x);
    y = find(y);
    if (x == y) return 0;

    if (h[x] > h[y]) {
      par[y] = x;
      h[x] += h[y];
    } else {
      par[x] = y;
      h[y] += h[x];
    }
    return 1;
  }

  // Clear operation - reset to initial values
  void clear() {
    for (int i = 0; i < size; ++i) {
      par[i] = i;
      h[i] = 1;
    }
  }
};
