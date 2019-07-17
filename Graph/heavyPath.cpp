int N,M,q,x,y,K;
int poz[Nmax],v[Nmax],nr[Nmax],l[Nmax],p[Nmax],cmp[Nmax],viz[Nmax];
vector<int> g[Nmax], c[Nmax];
//Segment tree stuff
vector<vector<int> > t;
void update(int comp, int nod, int st, int dr, int c, int d) {
  if(st==dr) { t[comp][nod]=d; return; }
  int mij = (st+dr)/2;
  if(c<=mij) update(comp,2*nod,st,mij,c,d);
  else update(comp,2*nod+1,mij+1,dr,c,d);
  t[comp][nod] = max(t[comp][2*nod],t[comp][2*nod+1]);
}
int getmax(int comp, int nod, int st, int dr, int c, int d) {
  int ret = 0;
  if(c<=st && dr<=d) return t[comp][nod];
  int mij = (st+dr)/2;
  if(d>mij) ret = max(ret,getmax(comp,nod*2+1,1+mij,dr,c,d));
  if(c<=mij) ret = max(ret,getmax(comp,nod*2,st,mij,c,d));
  return ret;
}
inline int query_val(int comp, int st, int dr) {
  return getmax(comp, 1, 1, c[comp].size(), st+1, dr+1);
}
//Available queries
inline void update_val(int comp, int poz, int val) {
  update(comp, 1, 1, c[comp].size(), poz+1, val);
  v[c[comp][poz]] = val;
}
int find_max(int x, int y) {
  if(cmp[x] == cmp[y]) return query_val(cmp[x],min(poz[x],poz[y]),max(poz[x],poz[y]));
  int px = p[c[cmp[x]][0]], py = p[c[cmp[y]][0]];
  if(l[px] < l[py]) { swap(x,y); swap(px,py); }
  int M = query_val(cmp[x],0,poz[x]);
  return max(M, find_max(px,y));
}
//Preprocessing
void dfs(int x) {
  viz[x] = 1; nr[x] = 1;
  int ind = -1, nrc = -1;
  for(auto y: g[x]) {
    if(viz[y]) continue;
    l[y] = l[x] + 1; p[y] = x; dfs(y);
    if(nr[y] > nrc) { ind = y; nrc = nr[y]; }
    nr[x] += nr[y];
  }
  if(nrc == -1) {
    vector<int> C; C.pb(x);
    ++K; c[K] = C; cmp[x] = K;
  } else {
    c[cmp[ind]].pb(x); cmp[x] = cmp[ind];
  }
}
void heavy_path(int r) {
  l[r] = 1; dfs(r);
  for(int i=1;i<=K;++i) {
    reverse(c[i].begin(),c[i].end());
    for(int j=0;j<c[i].size();++j) poz[c[i][j]] = j;
  }
  t.resize(K+10);
  for(int i=1;i<=K;++i) t[i].resize(4*c[i].size()+10,0);
  for(int i=1;i<=N;++i) update_val(cmp[i],poz[i],v[i]);
}