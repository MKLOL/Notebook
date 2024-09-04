template<typename T>
class RMQmax {
private:
    vector<vector<int>> rmq;  // Stores indices
    vector<T> v;
    vector<int> lg;
    int N, log;
 
    // Function to compare indices based on the values in v
    // Returns true if the value at index x should be preferred over the value at index y
    bool cmp(int x, int y) {
        return v[x] >= v[y];  // Default comparison for max; change to <= for min
    }

    // Function to generate the RMQ table
    void genRmq() {
        for (int i = 2; i <= N; ++i) {
            lg[i] = lg[i / 2] + 1;
        }
        for (int i = 0; i < N; ++i) {
            rmq[0][i] = i;  // Initialize with the index itself
        }
        for (int j = 1; (1 << j) <= N; ++j) {
            for (int i = 0; i + (1 << j) - 1 < N; ++i) {
                int left = rmq[j - 1][i];
                int right = rmq[j - 1][i + (1 << (j - 1))];
                rmq[j][i] = cmp(left, right) ? left : right;
            }
        }
    }
 
public:
    // Constructor to initialize the table with given size and values
    RMQmax(const vector<T>& values) : v(values) {
        N = v.size();
        log = static_cast<int>(log2(N)) + 1;
        rmq.assign(log, vector<int>(N));
        lg.assign(N + 1, 0);
        genRmq();
    }
 
    // Function to query the index of the minimum value in the range [x, y]
    int query(int x, int y) {
        int l = lg[y - x + 1];
        int sh = y - x + 1 - (1 << l);
        int left = rmq[l][x];
        int right = rmq[l][x + sh];
        return cmp(left, right) ? left : right;
    }
};
 
