class NormVec {
private:
  vector<ll> v;
  int offset = 1;
 
public:
  void add(ll x) {
    v.push_back(x);
  }


  void make() {
    v.push_back(LLONG_MAX);
    v.push_back(LLONG_MIN);
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
  }


  int getEqual(ll x) {
    auto it = lower_bound(v.begin(), v.end(), x);
    if (*it == x) {
      return it - v.begin() + offset;
    }
    return -1;
  }


  int larger(ll x) {
    auto it = upper_bound(v.begin(), v.end(), x);
    return it - v.begin() + offset;
  }


  int largereq(ll x) {
    int a = getEqual(x);
    if (a != -1) return a;
    return larger(x);
  }


  int smaller(ll x) {
    auto it = lower_bound(v.begin(), v.end(), x);
    if (it == v.begin()) {
      return -1;
    }
    return (it - 1) - v.begin() + offset;
  }


int smallereq(ll x) {
    int a = getEqual(x);
    if (a != -1) return a;
    return smaller(x);
  }
};


