int NRN,rez,d[Nmax],p[Nmax],viz[Nmax],inq[Nmax];
vector<pii> mc;
vi v,f,c, m[Nmax];
queue<int> q;
inline void add(int x) {
  if(inq[x]) return; inq[x] = viz[x] = 1; q.push(x);
}
inline int pop() {
  int x = q.front(); q.pop(); inq[x] = 0; // delete for bfs
  return x;
}
inline void reset_stuff(int S) {
  for(int i = 0; i <= NRN; ++i) {
    viz[i] = inq[i] = 0; d[i] = inf;
  } d[S] = 0;
}
inline void addEdge(int x,int y,int cap, int cost) {
  NRN = max(NRN,x); NRN = max(NRN,y);
  c.pb(cap); v.pb(cost); f.pb(0);
  m[x].pb(sz(mc)); mc.pb(mp(x,y));
  c.pb(0); f.pb(0); v.pb(-cost);
  m[y].pb(sz(mc)); mc.pb(mp(y,x));
}

inline int bfs(int S, int D) {
  reset_stuff(S); add(S);
  while(!q.empty()) {
    int x = pop(); if(x==D) continue;
    for(auto y : m[x]) {
      int ve = mc[y].sc;
      if(f[y] < c[y] && d[ve] > d[x] + v[y]) {
        add(ve); p[ve] = y; d[ve] = d[x] + v[y];
      }
    }
  }
  return viz[D];
}
pii update(int S, int D) {
  int ret = 0, retc = 0, flux = inf, curr = D;
  while(curr!=S) {
    int muc = p[curr], par = mc[p[curr]].fs;
    if(c[muc] - f[muc] < flux) flux = c[muc] - f[muc];
    if(!flux) break; curr = par;
  }
  curr = D;
  while(curr!=S) {
    int edg = p[curr], par = mc[p[curr]].fs;
    f[edg] += flux; f[edg^1] -= flux; curr = par;
  }
  ret += flux; retc += flux*d[D]; return mp(ret, retc);
}
pii flow(int S, int D) {
  int ret = 0, retc = 0;
  while(true) {
    if(!bfs(S, D)) break;
    pii u = update(S,D); ret += u.fs, retc += u.sc;
  }
  return mp(ret, retc);
}
