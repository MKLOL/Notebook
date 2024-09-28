class SegmentTree {
public:
  ll MMAX = -1000000000LL * 1000000;
  vector<int> t;
  vll vals;
  int N;

  int get(int ret1, int ret2) {
      if (ret1 == -1) return ret2;
      if (ret2 == -1) return ret1;
      
      // UDPATE HERE IF USING SOMETHING OTHER THAN MAX
      return (vals[ret1] >= vals[ret2]) ? ret1 : ret2;
  }

  void privateUpdate(int nod, int st, int dr, int poz, ll val) {
    if (st == dr) {
      t[nod] = st;
      vals[st] = val;
      return;
    }
    int mij = (st + dr) / 2;
    if (poz <= mij) {
      privateUpdate(2 * nod, st, mij, poz, val);
    } else {
      privateUpdate(2 * nod + 1, mij + 1, dr, poz, val);
    }
    t[nod] = get(t[2*nod], t[2*nod+1]);
  }

  int privateGetMax(int nod, int st, int dr, int l, int r) {
    if (l <= st && dr <= r) {
      return t[nod];
    }
    int mij = (st + dr) / 2;
    int ret1 = -1, ret2 = -1;
    if (r > mij) ret1 = privateGetMax(nod * 2 + 1, mij + 1, dr, l, r);
    if (l <= mij) ret2 = privateGetMax(nod * 2, st, mij, l, r);

    return get(ret1, ret2);
  }

  void make(int nod, int l, int r) {
    if (l == r) {
      t[nod] = l;
    } else {
      int mid = (l + r) / 2;
      make(nod * 2, l, mid);
      make(nod * 2 + 1, mid + 1, r);
      t[nod] = get(t[2*nod], t[2*nod+1]);
    }
  }

  SegmentTree() {}

  SegmentTree(int size) : N(size) {
    t.assign(4 * N, 0);
    vals.assign(N, MMAX);
    make(1, 0, N - 1);
  }

  SegmentTree(const vll input) : vals(input) {
    N = sz(input);
    t.assign(4 * N, 0);
    make(1, 0, N - 1);
  }

  void update(int poz, ll val) {
    privateUpdate(1, 0, N - 1, poz, val);
  }

  pair<int, ll> getMax(int l, int r) { // index and value
    int ind = privateGetMax(1, 0, N - 1, l, r);
    return mp(ind, vals[ind]);
  }

  int size() {
    return N;
  }
};