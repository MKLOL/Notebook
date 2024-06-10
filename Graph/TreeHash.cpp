class TreeHash {
  // assumes vi g global adjacency list
public:
  int mods[2];
  vi dc[2]; // constant added in hash product for each depth
  vi viz;
  vi hashes[2]; // stores final hashes

  TreeHash() {}
  TreeHash(int N) {
    mods[0] = 998244353;
    mods[1] = 100000007;
    mt19937 rng(time(0));
    uniform_int_distribution<mt19937::result_type> dist(1,mods[0]);
    viz.resize(N+1);
    FOR(k, 2) {
      dc[k].resize(N+1);
      hashes[k].resize(N+1);
    }
    FOR(i, N+1) {
      FOR(k, 2) dc[k][i] = dist(rng);
      viz[i] = 0; 
    }
  } 

  void make_hash(int x, int d) {
    viz[x] = 1;
    FOR(k, 2) hashes[k][x] = 1;
    for(auto y: g[x]) {
      if(viz[y]) continue;
      make_hash(y, d+1);
      FOR(k, 2) {
        hashes[k][x] = 1LL * hashes[k][x] * (dc[k][d] + hashes[k][y]) % mods[k];
      }
    }
  }

  void make_hashes(int r) {
    make_hash(r, 1);
  }
};