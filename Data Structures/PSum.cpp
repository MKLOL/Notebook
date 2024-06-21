class PSum {
public:
  vector<ll> sm;

  // Constructor that initializes the vector with size N
  PSum(int N) : sm(N) {}

  // Constructor that initializes with a given vector and calculates the prefix sums
  PSum(const vll &v) {
    sm = v;
    make();
  }

  void add(int pos, ll val) {
    sm[pos] += val;
  }

  void add(vll &v) {
    for (size_t i = 0; i < v.size(); ++i) {
      sm[i] += v[i];
    }
  }

  void make() {
    for (size_t i = 1; i < sm.size(); ++i) {
      sm[i] += sm[i - 1];
    }
  }

  // Function to get the sum of elements in the range [start, end]
  ll sum(int start, int end) {
    start = max(start, 0);
    end = min(end, static_cast<int>(sm.size()) - 1);

    if (start == 0) {
      return sm[end];
    }
    return sm[end] - sm[start - 1];
  }
};
