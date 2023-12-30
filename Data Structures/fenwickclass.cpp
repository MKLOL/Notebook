class FenwickTree {
private:
    vector<int> AIB;
    int N;

    // Function to calculate the least significant bit that is set
    inline int zeros(int x) {
        return x & (-x);
    }

public:
    // Constructor to initialize the tree with given size
    FenwickTree(int size) : N(size), AIB(size + 1, 0) {
        // The AIB vector is initialized with zeros and has size N + 1
    }

    // Function to add 'q' to the element at index 'x'
    void add(int x, int q) {
        for (int i = x; i <= N; i += zeros(i)) {
            AIB[i] += q;
        }
    }

    // Function to compute the prefix sum up to 'x'
    int comp(int x) {
        int ret = 0;
        for (int i = x; i > 0; i -= zeros(i)) {
            ret += AIB[i];
        }
        return ret;
    }

    // Function to compute the range sum between 'l' and 'r'
    int comp(int l, int r) {
        l = max(1, l);
        r = min(N, r);
        return comp(r) - comp(l - 1);
    }
};
