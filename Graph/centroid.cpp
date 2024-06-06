// assumes a global vi g[Nmax] adjancency list

class CentroidDecomp {
public:  
  vi viz; // reuse with depth in centroid tree
  vi dl; // deleted nodes (past centroids)
  vi sz; // size of subtree in current state (after deleting some centroids)

  CentroidDecomp(int N) {
    viz.resize(N+1);
    dl.resize(N+1);
    sz.resize(N+1);
  }

  void dfs_sz(int x, int d) { // node and depth
    viz[x] = d;
    sz[x] = 1;
  
    for(auto y: g[x]) {
      if(viz[y] != d && !dl[y]) {
        dfs_sz(y, d);
        sz[x] += sz[y];
      }
    }
  }

  int findc(int x, int N) { // find centroid if total size is N
    int c = x;
    for(auto y: g[x]) {
      if(sz[x] < sz[y] || dl[y]) continue; // skip parent / delted
      if(sz[y] > N/2) {
        c = findc(y, N);
        break;
      }
    }
    return c;
  }

  void callback(int c) {
    // ADD CODE HERE
    // c is current centroid, dl[x] means node was deleted
  }

  int decomp(int r, int N, int d) {
    dfs_sz(r, d);
    int c = findc(r, N);
    dl[c] = 1;

    callback(c);

    for(auto x: g[c]) {
      if(!dl[x]) {
        int c2 = decomp(x, sz[x], d+1); // next centroids
      }
    }

    return c;
  }
};