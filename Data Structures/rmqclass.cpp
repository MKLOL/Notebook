class SparseTable {
private:
  vector<vector<int>> rmq;
  vector<int> v, lg;
  int N, log;

  // Custom function to calculate the logarithm base 2 of an integer
  int log2(int x) {
    int res = 0;
    while (x >>= 1) res++;
    return res;
  }

  // Function to generate the RMQ table if it represents values
  void genRmq() {
    for (int i = 2; i <= N; ++i) {
      lg[i] = lg[i / 2] + 1;
    }
    FOR(i,N) {
      rmq[0][i] = v[i];
    }
    for (int i = 1; (1 << i) <= N; ++i) {
      for (int j = 0; j + (1 << i) - 1 < N; ++j) {
        rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
      }
    }
  }

  // Function to generate the RMQ table if it represents indexes
  void genRmqIndex() {
    for (int i = 2; i <= N; ++i) {
      lg[i] = lg[i / 2] + 1;
    }
    FOR(i,N) {
      rmq[0][i] = i;
    }
    for (int i = 1; (1 << i) <= N; ++i) {
      for (int j = 0; j + (1 << i) - 1 < N; ++j) {
        int sh = j + (1 << (i - 1));
        if(v[rmq[i - 1][j]] <= v[rmq[i - 1][sh]] ) {
          rmq[i][j] = rmq[i - 1][j];
        } else {
          rmq[i][j] = rmq[i - 1][sh];
        }
      }
    }
  }

public:
  SparseTable() {}

  // Constructor to initialize the table with given size and values
  SparseTable(const vector<int>& values) : v(values) {
    N = sz(v);
    log = log2(N) + 1;
    rmq.assign(log + 1, vi(N));
    lg.assign(N + 1, 0);
    genRmq(); // use genRmqIndex to track index instead of values
  }

  // Function to query the minimum value in the range [x, y]
  // assumes genRmq init
  int query(int x, int y) {
    int l = lg[y - x + 1], sh = y - x + 1 - (1 << l);
    return min(rmq[l][x], rmq[l][x + sh]);
  }

  // Function to query the index of the min value in the range [x, y]
  // assumes genRmqIndex init
  int queryIndex(int x, int y) {
    int l = lg[y - x + 1], sh = y - x + 1 - (1 << l);
    if(v[rmq[l][x]] <= v[rmq[l][x + sh]]) {
      return rmq[l][x];
    } else {
      return rmq[l][x + sh];
    }
  }
};
