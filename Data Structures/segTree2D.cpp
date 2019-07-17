int N, val[4*Nmax];
vector<ll> AIB[4*Nmax];
vector<ll> v[4*Nmax];
inline int zeros(int x) { return x & (-x); }
inline void Add(int nod, int x, int q){
  for(int i=x ;i < AIB[nod].size(); i+= zeros(i)) AIB[nod][i] += q;
}
ll comp(int nod, int x){
  ll ret = 0;
  if(AIB[nod].size() == 0) return 0;
  for(int i=x;i>0;i-=zeros(i)) ret += AIB[nod][i];
  return ret;
}
void init(int nod, int st, int dr){
  if(dr - st == 0){
    v[nod].pb(val[st]);
    AIB[nod].resize(v[nod].size()+1);
    Add(nod,1,1);
  } else {
    int mij = (st+dr) / 2;
    init(nod*2, st, mij); init(nod*2+1, mij+1, dr);
    v[nod].resize(v[nod*2].size() + v[nod*2+1].size());
    merge(v[nod*2].begin(), v[nod*2].end(), v[nod*2 +1].begin(), v[nod*2+1].end(),v[nod].begin());
    AIB[nod].resize(v[nod].size()+1);
    for(int i=1;i<AIB[nod].size();++i) Add(nod, i, 1);
  }
}
int getInd(int nod, int x){
  int ret = -1, st = 0, dr = v[nod].size() -1;
  while(st <= dr ){
    int mij = (st+dr)/2;
    if(v[nod][mij] <= x) { st = mij + 1; ret = mij; } 
    else dr = mij - 1;
  }
  return ret+1;
}
int K; ll retV = 0; // calc between ist,idr and k,l
int calc(int nod,int ist, int idr, int st, int dr, int k, int l) { 
  if (K == 0 && k > l) return 0;
  if(ist <= st && idr >= dr){
    retV += comp(nod,getInd(nod,l)) - comp(nod,getInd(nod,k-1));
  } else {
    int mij = (st+dr)/2;
    if (ist <= mij) calc(nod*2,ist,idr,st,mij,k,l);
    if (idr > mij) calc(nod*2+1,ist,idr,mij+1,dr,k,l);
  }
}