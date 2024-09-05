class Mo {
private:
  vector<piii> qr; // queries (ind, (left, right))
  vi C; // input array
  int S; // sqrt

  bool static cmp(piii Ax, piii Bx) {
    auto A = Ax.sc;
    auto B = Bx.sc;
    if (A.fs / S != B.fs / S) return A.fs / S < B.fs / S;
    return A.sc > B.sc;
  }

  void addS(ll x) { 
    // add C[x] to start
  }

  void remS(ll x) { 
    // remove C[x] from start
  }

  void addE(ll x) {
    // add C[x] to end
  }

  void remE(ll x) {
    // remove C[x] from end
  }

public:
  vll rez; // result, ordered by original index in query array

  Mo(const vector<piii>& q, const vi& v, int N) : qr(q), C(v) {
    S = sqrt(N);
    rez.resize(sz(q));
    sort(all(qr), cmp);
    int st = 0;
    int dr = -1;

    for (int i=0;i<sz(qr);++i) {
      auto qc = qr[i].sc;
      for (int q = dr+1; q <= qc.sc; ++ q) {
        addE(C[q]);
      }
      for (int q=st-1;q >= qc.fs;--q) {
        addS(C[q]);
      }
      for (int q = dr; q > qc.sc; --q) {
        remE(C[q]);
      }
      for (int q=st;q<qc.fs;++q) {
        remS(C[q]);
      }
      st = qc.fs;
      dr = qc.sc;

      rez[qr[i].fs] = cur;
    }
  }
};