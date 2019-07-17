int N,s[2*Nmax],curr,c[2*Nmax],sol[2*Nmax]; //value of i = sol[2*i]
vector<int> g[2*Nmax],gt[2*Nmax],v[2*Nmax];
int viz[2*Nmax],vz[2*Nmax];
void dfs(int x) {
  viz[x] = 1; for(auto y: g[x]) if(!viz[y]) dfs(y); s[++curr] = x;
}
void dfs2(int x, int comp) {
  viz[x] = 0; c[x] = comp; v[comp].push_back(x);
  for(auto y: gt[x]) if(viz[y]) dfs2(y,comp);
}
inline int ng(int x) { if(x%2) return x-1; return x+1;}
bool f(int x, int val) {
  vz[x] = 1;
  for(auto y: v[x]) {
    if(sol[y] && sol[y]!=val) return false; sol[y] = val;
  }
  for(auto y: v[x]) {
    y = ng(y); if(sol[y] && sol[y]!=3-val) return false;
    if(!sol[y]) return f(c[y],3-val);
  }
  return true;
}
inline bool sat() {
  int comp = 0;
  for(int i=2;i<=2*N+1;++i) if(!viz[i]) dfs(i);
  for(int i=curr;i>=1;--i) if(viz[s[i]]) dfs2(s[i],++comp);
  for(int i=1;i<=comp;++i) if(!vz[i]) if(!f(i,1)) return false;
  return true;
}
inline void add_disj(int x, int sx, int y, int sy) {//s 0 normal,1 negation
  g[2*x+(1-sx)].push_back(2*y+sy);
  g[2*y+(1-sy)].push_back(2*x+sx);
  gt[2*y+sy].push_back(2*x+(1-sx));
  gt[2*x+sx].push_back(2*y+(1-sy));
}