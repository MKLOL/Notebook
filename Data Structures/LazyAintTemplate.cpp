struct cel {};
class SegmentTree {  
public:
  vector<cel> aint; // Segment tree array
  vector<ll> up;   // Lazy propagation array
  vector<ll> v;    // Input data array
  int N;         // Maximum size of the array
  void relax(int nod, int st, int dr) {
    if (!up[nod]) return;
    // Add code to update aint[nod] using up[nod]
    if (st != dr) {
      up[2 * nod]; // Add code to update up[2*nod]
      up[2 * nod + 1]; // Add code to update up[2*nod+1]
    }
    up[nod] = 0;
  }
  cel get(cel &left, cel &right) {
    cel ret; // create cel from left and right
    return ret;
  }
  void make(int nod, int st, int dr) {
    int mij = (st + dr) / 2; relax(nod, st, dr);
    relax(2 * nod, st, mij);
    relax(2 * nod + 1, mij + 1, dr);
    aint[nod] = get(aint[nod*2], aint[nod*2+1]);
  }
  SegmentTree(const vector<ll>& input) : v(input) {
    N = input.size();
    aint.resize(4 * N);
    up.resize(4 * N);
    init(1, 0, N - 1);
  }
  // Function to update the segment tree
  void update(int nod, int ist, int idr, int st, int dr, ll val) {
    relax(nod, st, dr);
    if (ist <= st && idr >= dr) {
      up[nod] = val;
      relax(nod, st, dr);
    } else {
      int mij = (st + dr) / 2;
      if (ist <= mij) update(2 * nod, ist, idr, st, mij, val);
      if (idr > mij) update(2 * nod + 1, ist, idr, mij + 1, dr, val);
      make(nod, st, dr);
    }
  }
  // Function to query the sum in a range
  cel query(int nod, int ist, int idr, int st, int dr) {
    relax(nod, st, dr);
    if (ist <= st && idr >= dr) {
      return aint[nod];
    } else {
      int mij = (st + dr) / 2;
      cel ret;
      if (ist <= mij) ret = query(2 * nod, ist, idr, st, mij);
      if (idr > mij) {
        auto right = query(2 * nod + 1, ist, idr, mij + 1, dr);
        if (ist <= mij) ret = get(ret, right);
        else ret = right;
      }
      make(nod, st, dr);
      return ret; 
    }
  }
  cel query(int st, int dr) {
    return query(1, st, dr, 0, N-1);
  }
  void update(int st, int dr, ll val) {
    if (st > dr) return;
    update(1, st, dr, 0, N-1, val);
  }
  void init(int nod, int st, int dr) {
    if (st == dr) {
      // add code for leaf
    } else {
      int mij = (st + dr) / 2;
      init(2 * nod, st, mij);
      init(2 * nod + 1, mij + 1, dr);
      make(nod, st, dr);
    }
  }
};
