#include <vector>
#include <algorithm>

using namespace std;

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

    // Function to generate the RMQ table
    void genRmq() {
        for (int i = 2; i <= N; ++i) {
            lg[i] = lg[i / 2] + 1;
        }
        for (int i = 1; i <= N; ++i) {
            rmq[0][i] = v[i];
        }
        for (int i = 1; (1 << i) <= N; ++i) {
            for (int j = 1; j + (1 << i) - 1 <= N; ++j) {
                rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

public:
    // Constructor to initialize the table with given size and values
    SparseTable(const vector<int>& values) : v(values) {
        N = v.size() - 1; // Assuming 1-based indexing
        log = log2(N) + 1;
        rmq.assign(log + 1, vector<int>(N + 1));
        lg.assign(N + 1, 0);
        genRmq();
    }

    // Function to query the minimum value in the range [x, y]
    int query(int x, int y) {
        int l = lg[y - x + 1], sh = y - x + 1 - (1 << l);
        return min(rmq[l][x], rmq[l][x + sh]);
    }
};
