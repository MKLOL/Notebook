int aint[Nmax*4], up[Nmax*4], v[Nmax];

inline void relax(int nod,int st,int dr) {
  if(!up[nod]) return; aint[nod] += up[nod];
  auto c = up[nod];
  if(st!=dr) { up[2*nod]+=c; up[2*nod+1]+=c; }
  up[nod] = 0;
}

inline void make(int nod, int st, int dr) {
  int mij = (st+dr)/2;
  relax(2 * nod);
  relax(2 * nod + 1);
  aint[nod] = aint[2*nod] + aint[2*nod + 1];
}

void update(int nod,int ist,int idr,int st,int dr,ll val) {
  relax(nod,st,dr);
  if(ist<=st&&idr>=dr) {
    up[nod] = val; relax(nod,st,dr);
  } else {
    int mij=(st+dr)/2;
    if(ist<=mij) update(2*nod,ist,idr,st,mij,val);
    if(idr>mij) update(2*nod+1,ist,idr,mij+1,dr,val);
    make(nod,st,dr);
  }
}
int calc(int nod,int ist,int idr,int st,int dr) {
  relax(nod,st,dr); int ret = 0;
  if(ist<=st && idr>=dr) ret += aint[nod];
  else {
    ll mij=(st+dr)/2;
    if(ist<=mij) ret += calc(2*nod,ist,idr,st,mij);
    if(idr>mij) ret += calc(2*nod+1,ist,idr,mij+1,dr);
    make(nod,st,dr);
  }
  return ret;
}
void init(int nod,int st,int dr){
  if(st != dr){
    int mij = (st+dr)/2;
    init(2*nod,st,mij); init(2*nod+1,mij+1,dr);
    make(nod,st,dr);
  } else {
    aint[nod] = v[st];
  }
}