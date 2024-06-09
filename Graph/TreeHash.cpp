// TODO: consider 2 mods

class TreeHash {
  // assumes vi g global adjacency list
public:
  int hMOD;
  vi dc; // constant added in hash product for each depth
  vi viz;
  vi hashes; // stores final hashes

  TreeHash() {}
  TreeHash(int N) {
    hMOD = 1000000007;
    mt19937 rng(time(0));
    uniform_int_distribution<mt19937::result_type> dist(1,hMOD);
    viz.resize(N+1);
    dc.resize(N+1);
    hashes.resize(N+1);
    FOR(i, N+1) {
      dc[i] = dist(rng);
      viz[i] = 0; 
    }
  } 

  void make_hash(int x, int d) {
    viz[x] = 1;
    int hash = 1;
    for(auto y: g[x]) {
      if(viz[y]) continue;
      make_hash(y, d+1);
      hash = 1LL * hash * (dc[d] + hashes[y]) % hMOD;
    }
    hashes[x] = hash;
  }

  void make_hashes(int r) {
    make_hash(r, 1);
  }
};