class Graph {
public:
  int L, R;
  vvi g;
  vi l, r, was;

  // left nodes 0..L-1
  // right nodes 0..R-1
  // g has edges from L to R
  Graph(int Lx, int Rx) {
    L = Lx;
    R = Rx;
    clear();
  }

  void clear() {
    l.resize(L);
    r.resize(R);
    was.resize(L);
    g.resize(L);
    FOR(i, L) {
      l[i] = -1;
      g[i].clear();
    }
    FOR(i, R) {
      r[i] = -1;
    }
  }

  void addEdge(int x, int y) {
    g[x].pb(y);
  }

  int match(int q) {
    if(was[q]) return 0; 
    was[q] = 1;

    for(auto x : g[q]) {
      if(r[x] == -1) {
        l[q] = x;
        r[x] = q;
        return 1;
      }
    }

    for(auto x: g[q]) {
      if(r[x] != -1 && match(r[x])) {
        l[q] = x;
        r[x] = q;
        return 1;
      }
    }
    return 0;
  }

  //edges i, l[i] if l[i] != -1
  vpi matching() { 
    int ok = 1; 
    while(ok) {
      ok = 0; 
      FOR(i, L) was[i]=0;

      FOR(i, L) {
        if(l[i] == -1) ok |= match(i);
      }

    }
    vpi ret;
    FOR(i, L) {
      if(l[i] != -1) ret.pb(mp(i, l[i]));
    }
    return ret;
  }
};