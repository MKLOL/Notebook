int t[4*Nmax];
void update(int nod, int st, int dr, int poz, int val) {
  if(st==dr) { t[nod]=val; return; }
  int mij = (st+dr)/2;
  if(poz<=mij) update(2*nod,st,mij,poz,val);
  else update(2*nod+1,mij+1,dr,poz,val);
  t[nod] = max(t[2*nod],t[2*nod+1]);
}
int getmax(int nod, int st, int dr, int l, int r) {
  if(l<=st && dr<=r) return t[nod];
  int ret = 0; int mij = (st+dr)/2;
  if(r>mij) ret = max(ret,getmax(nod*2+1,1+mij,dr,l,r));
  if(l<=mij) ret = max(ret,getmax(nod*2,st,mij,l,r)); return ret;
}