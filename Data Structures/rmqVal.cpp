template<typename T>
class SparseTable {
private:
  vector<vector<T>> rmq;  // Stores values
  vector<T> v;
  vector<int> lg;
  int N, log;

  // Function to generate the RMQ table
  void genRmq() {
    for (int i = 2; i <= N; ++i) {
      lg[i] = lg[i / 2] + 1;
    }
    FOR(i, N) {
      rmq[0][i] = v[i];
    }
    for (int j = 1; (1 << j) <= N; ++j) {
      for (int i = 0; i + (1 << j) - 1 < N; ++i) {
        rmq[j][i] = min(rmq[j - 1][i], rmq[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
 
public:
  // Constructor to initialize the table with given size and values
  SparseTable(const vector<T>& values) : v(values) {
    N = v.size();
    log = static_cast<int>(log2(N)) + 1;
    rmq.assign(log, vector<int>(N));
    lg.assign(N + 1, 0);
    genRmq();
  }

  // Function to query the min value in the range [x, y]
  T query(int x, int y) {
    int l = lg[y - x + 1];
    int sh = y - x + 1 - (1 << l);
    return min(rmq[l][x], rmq[l][x + sh]);
  }
};