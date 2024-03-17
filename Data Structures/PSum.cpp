class PSum {
public:
    vector<ll> sm;

    PSum(int N) : sm(N) {}
    void add(int pos, ll val) {
        sm[pos] += val;
    }
    void add(vll &v) {
        FOR(i, sz(v)) {
            sm[i] += v[i];
        }
    }

    void make() {
        ll sum = 0;
        rep(i,1,sz(sm)) {
            sm[i] += sm[i-1];
        }
    }

    // Function to get the sum of elements in the range [start, end]
    ll sum(int start, int end) {
        start = max(start, 0);
        end = min(end, sz(sm)-1);

        if (start == 0) {
            return sm[end];
        }
        return sm[end] - sm[start - 1];
    }
};
