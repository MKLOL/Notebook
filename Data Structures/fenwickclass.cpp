template<typename T>
class FenwickTree {
private:
  vector<T> AIB;
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
  void add(int x, T q) {
    for (int i = x; i <= N; i += zeros(i)) {
      AIB[i] += q;
    }
  }


  // Function to compute the prefix sum up to 'x'
  T comp(int x) {
    T ret = 0;
    for (int i = x; i > 0; i -= zeros(i)) {
      ret += AIB[i];
    }
    return ret;
  }


  // Function to compute the range sum between 'l' and 'r'
  T comp(int l, int r) {
    l = max(1, l);
    r = min(N, r);
    return comp(r) - comp(l - 1);
  }


  int gle(T x) {
    T sum = 0;
    int pos = 0;


    // Find the largest power of 2 less than or equal to N using bit manipulation
    int largestPower = 1;
    while (largestPower <= N) {
      largestPower <<= 1;
    }
    largestPower >>= 1;


    // Start from the largest power of 2 that is less than or equal to N
    for (int i = largestPower; i > 0; i >>= 1) {
      // Check if the position plus the current power of 2 is within the bounds
      // and if including this part would not exceed the sum x
      if (pos + i <= N && sum + AIB[pos + i] <= x) {
        sum += AIB[pos + i]; // update the sum to include this part
        pos += i;            // move the position forward by the power of 2
      }
    }


    return pos; // This position is the largest index with cumulative sum <= x
  }
};
