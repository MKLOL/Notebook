ll aint[Nmax*4], up[Nmax*4];



inline void relax(int nod,int st,int dr) {
  if(!up[nod]) return; aint[nod] += up[nod];
  auto c = up[nod];
  if(st!=dr) { up[2*nod]+=c; up[2*nod+1]+=c; }
  up[nod] = 0;
}

inline void make(int nod, int st, int dr) {
  int mij = (st+dr)/2;
  relax(2 * nod, st, mij);
  relax(2 * nod + 1, mij+1,dr);
  aint[nod] = min(aint[2*nod],aint[2*nod + 1]);
}

void updatePntAux(int nod,int pnt,int st,int dr,ll val) {
  relax(nod,st,dr);
  if(st == dr) {
    aint[nod]= val;
  } else {
    int mij=(st+dr)/2;
    if(pnt<=mij) updatePntAux(2*nod,pnt,st,mij,val);
    if(pnt>mij) updatePntAux(2*nod+1,pnt,mij+1,dr,val);
    make(nod,st,dr);
  }
}

void updateAux(int nod,int ist,int idr,int st,int dr,ll val) {
  relax(nod,st,dr);
  if(ist<=st&&idr>=dr) {
    up[nod] = val; relax(nod,st,dr);
  } else {
    int mij=(st+dr)/2;
    if(ist<=mij) updateAux(2*nod,ist,idr,st,mij,val);
    if(idr>mij) updateAux(2*nod+1,ist,idr,mij+1,dr,val);
    make(nod,st,dr);
  }
}

void updatePnt(int pos, ll val) {
  if (pos > M || pos < 0) return;
  updatePntAux(1, pos, 0, M, val);
}

void update(int st,int dr,ll val) {
  if (st > dr) return;
  updateAux(1,st,dr,0,M,val);
}

ll calcAux(int nod,int ist,int idr,int st,int dr) {
  relax(nod,st,dr); ll ret = inf;
  if(ist<=st && idr>=dr) ret = aint[nod];
  else {
    ll mij=(st+dr)/2;
    if(ist<=mij) ret = min(ret, calcAux(2*nod,ist,idr,st,mij));
    if(idr>mij) ret = min(ret, calcAux(2*nod+1,ist,idr,mij+1,dr));
    make(nod,st,dr);
  }
  return ret;
}

ll calc(int st, int dr) {
  if (st > dr) return 0;
  return calcAux(1,st,dr,0,M);
}

void init(int nod,int st,int dr){
  if(st != dr){
    int mij = (st+dr)/2;
    init(2*nod,st,mij); init(2*nod+1,mij+1,dr);
    make(nod,st,dr);
  } else {
    aint[nod] = 0;
  }
}
