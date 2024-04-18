auto random_address = [] { char *p = new char; delete p; return (uint64_t) p; };
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count() * (random_address() | 1));
 
using hash_t = uint64_t;
 
// When P = 2^32 - 13337, both P and (P - 1) / 2 are prime.
const hash_t HASH_P = (unsigned) -13337;
const int HASH_COUNT = 2;
 
// Avoid multiplication bases near 0 or P - 1.
uniform_int_distribution<hash_t> MULT_DIST(0.1 * HASH_P, 0.9 * HASH_P);
const hash_t HASH_MULT[HASH_COUNT] = {MULT_DIST(rng), MULT_DIST(rng)};
 
vector<unsigned> hash_pow[HASH_COUNT] = {{1}, {1}};
 
struct string_hash {
    static inline unsigned fast_mod(uint64_t x, unsigned m = HASH_P) {
#if !defined(_WIN32) || defined(_WIN64)
        return x % m;
#endif
        // Optimized mod for Codeforces 32-bit machines.
        // x must be less than 2^32 * m for this to work, so that x / m fits in a 32-bit integer.
        unsigned x_high = x >> 32, x_low = (unsigned) x;
        unsigned quot, rem;
        asm("divl %4\n"
            : "=a" (quot), "=d" (rem)
            : "d" (x_high), "a" (x_low), "r" (m));
        return rem;
    }
 
    vector<unsigned> _prefix_hash[HASH_COUNT];
 
    string_hash() {
        build(string());
    }
 
    template<typename T_string>
    string_hash(const T_string &str) {
        build(str);
    }
 
    int length() const {
        return (int) _prefix_hash[0].size() - 1;
    }
 
    template<typename T>
    void add_char(const T &c) {
        for (int h = 0; h < HASH_COUNT; h++) {
            _prefix_hash[h].push_back(fast_mod(HASH_MULT[h] * _prefix_hash[h].back() + c));
 
            if (hash_pow[h].size() < _prefix_hash[h].size())
                hash_pow[h].push_back(fast_mod(HASH_MULT[h] * hash_pow[h].back()));
        }
    }
 
    template<typename T_string>
    void build(const T_string &str) {
        for (int h = 0; h < HASH_COUNT; h++)
            _prefix_hash[h] = {0};
 
        for (auto &c : str)
            add_char(c);
    }
 
    hash_t _single_hash(int h, int start, int end) const {
        hash_t start_hash = (hash_t) _prefix_hash[h][start] * hash_pow[h][end - start];
        return fast_mod(_prefix_hash[h][end] + HASH_P * HASH_P - start_hash + hash_pow[h][end - start]);
    }
 
    hash_t substring_hash(int start, int end) const {
        return _single_hash(0, start, end) + (HASH_COUNT > 1 ? _single_hash(1, start, end) << 32 : 0);
    }
 
    bool equal(int start1, int start2, int length) const {
        return substring_hash(start1, start1 + length) == substring_hash(start2, start2 + length);
    }
};
 
