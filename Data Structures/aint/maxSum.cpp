struct cel {
  ll mx, ind;
};

typedef ll celu;

class SegmentTree {
 
public:
  vector<cel> aint; // Segment tree array
  vector<celu> up;   // Lazy propagation array
  vll v;    // Input data array
  int N;         // Maximum size of the array
 
  // Function to apply lazy propagation
  void relax(int nod, int st, int dr) {
    // Add condition to stop propagating
    if(!up[nod]) return;
 
    // Add code to update aint[nod] using up[nod]
    aint[nod].mx += up[nod];
 
    // Add code to update up[2*nod] and up[2*nod+1]
    if (st != dr) {
      up[2*nod] += up[nod];
      up[2*nod+1] += up[nod];
    }
 
    // Clear up[nod]
    up[nod] = 0;
  }
 
  // Utility function to merge child node values
  cel get(int st, int dr, cel &left, cel &right) {
    cel ret;
    // Add code to create a cell from the left and the right ones
    if (left.mx > right.mx) {
      ret = left;
    } else {
      ret = right;
    }
    return ret;
  }
 
  void make(int nod, int st, int dr) {
    int mij = (st + dr) / 2;
    relax(nod, st, dr);
    relax(2 * nod, st, mij);
    relax(2 * nod + 1, mij + 1, dr);
    aint[nod] = get(st, dr, aint[nod*2], aint[nod*2+1]);
  }
 
  // Constructor
  SegmentTree(const vll& input) : v(input) {
    N = input.size();
    aint.resize(4 * N);
    up.resize(4 * N);
 
    init(1, 0, N - 1);
  }
 
  celu get_next(int st, int dr, int ist, int idr, celu val) {
    // Update cel for (mij+1, dr)
    return val;
  }
 
  // Function to update the segment tree
  void update(int nod, int ist, int idr, int st, int dr, celu val) {
    relax(nod, st, dr);
    if (ist <= st && idr >= dr) {
      up[nod] = val;
      relax(nod, st, dr);
    } else {
      int mij = (st + dr) / 2;
      if (ist <= mij) update(2 * nod, ist, idr, st, mij, val);
      if (idr > mij) update(2 * nod + 1, ist, idr, mij + 1, dr, get_next(st, dr, ist, idr, val));
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
        if (ist <= mij) ret = get(st, dr, ret, right);
        else ret = right;
      }
      make(nod, st, dr);
      return ret; 
    }
  }
 
  cel query(int st, int dr) {
    if (st > dr) {
      return {0,0};
    }
    return query(1, st, dr, 0, N-1);
  }
 
  void update(int st, int dr, celu val) {
    if (st > dr) return;
    //cout << st << " !" << dr << " " << val << "@@@" << endl;
    update(1, st, dr, 0, N-1, val);
  }
 
  // Function to initialize the segment tree
  void init(int nod, int st, int dr) {
    if (st == dr) {
      // add code for leaf
      aint[nod].mx = v[st];
      aint[nod].ind = st;
    } else {
      int mij = (st + dr) / 2;
      init(2 * nod, st, mij);
      init(2 * nod + 1, mij + 1, dr);
      make(nod, st, dr);
    }
  }
};
