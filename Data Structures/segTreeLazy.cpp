class SegmentTree {
public:
    vector<int> aint; // Segment tree array
    vector<int> up;   // Lazy propagation array
    vector<int> v;    // Input data array
    int N;         // Maximum size of the array
 
    // Function to apply lazy propagation
    void relax(int nod, int st, int dr) {
        if (!up[nod]) return;
        aint[nod] += up[nod];
        if (st != dr) {
          up[2 * nod] += up[nod];
          up[2 * nod + 1] += up[nod];    
        }
        up[nod] = 0;
    }
 
    // Utility function to merge child node values
    void make(int nod, int st, int dr) {
        int mij = (st + dr) / 2;
        relax(nod, st, dr);
        relax(2 * nod, st, mij);
        relax(2 * nod + 1, mij + 1, dr);
        aint[nod] = max(aint[2 * nod], aint[2 * nod + 1]);
    }
 
    // Constructor
    SegmentTree(const vector<int>& input) : v(input) {
      N = input.size() + 5;
      aint.resize(4 * N);
      up.resize(4 * N);
      init(1, 0, N - 1);
    }
 
    SegmentTree(int Nx) {
      N = Nx + 5;
      aint.resize(4 * N);
      up.resize(4 * N);
    }
 
 
    // Function to update the segment tree
    void update(int nod, int ist, int idr, int st, int dr, int val) {
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
 
    void update(int st, int dr, int val) {
      if (st > dr) return;
      update(1, st, dr, 0, N-1, val);
    }
 
    // Function to query the sum in a range
    int query(int nod, int ist, int idr, int st, int dr) {
      relax(nod, st, dr);
      if (ist <= st && idr >= dr) {
        return aint[nod];
      } else {
        int mij = (st + dr) / 2;
        int ret = 0;
        if (ist <= mij) ret = max(ret, query(2 * nod, ist, idr, st, mij));
        if (idr > mij) ret = max(ret, query(2 * nod + 1, ist, idr, mij + 1, dr));
        make(nod, st, dr);
        return ret; 
      }
    }
 
    int query(int st, int dr) {
      return query(1, st, dr, 0, N-1);
    }
 
    // Function to initialize the segment tree
    void init(int nod, int st, int dr) {
      if (st == dr) {
        aint[nod] = v[st];
      } else {
        int mij = (st + dr) / 2;
        init(2 * nod, st, mij);
        init(2 * nod + 1, mij + 1, dr);
        make(nod, st, dr);
      }
    }
};
