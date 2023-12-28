vi g[Nmax],stk,viz,low,iss,aux;
vector<vi> comp;
int N, k, indx=1;
void df(int x){
  viz[x] = indx; low[x] = indx;
  stk[++k] = x; iss[x] = 1; ++indx;
  for(auto n : g[x]){
    if(viz[n] == 0){
      df(n); low[x] = min(low[x],low[n]);
    } else if(iss[n]) low[x] = min(low[x],low[n]);
  }
  if(low[x] == viz[x]){
    aux.clear();
    do {
      aux.pb(stk[k]); iss[stk[k]] = 0; --k;
    } while(stk[k+1] != x);
    comp.pb(aux);
  }
}
void init(){
  stk.clear(); stk.resize(N+10);
  viz.clear(); viz.resize(N+10);
  iss.clear(); iss.resize(N+10);
  low.clear(); low.resize(N+10);
  aux.clear();
  comp.clear();
  k=0; indx=1;
  for(int i=1;i<=N;++i) {
    if(!viz[i]) df(i);
  }
}
