vi g[Nmax],stack,viz,low,iss,aux;
vector<vi> comp;
int k,index=1,N,M,x,y;
void df(int x){
  viz[x] = index; low[x] = index;
  stack[++k] = x; iss[x] = 1; ++index;
  for(auto n : g[x]){
    if(viz[n] == 0){
      df(n); low[x] = min(low[x],low[n]);
    } else if(iss[n]) low[x] = min(low[x],low[n]);
  }
  if(low[x] == viz[x]){
    aux.clear();
    do {
      aux.pb(stack[k]); iss[stack[k]] = 0; --k;
    } while(stack[k+1] != x);
    comp.pb(aux);
  }
}
void init(){
  stack.resize(N+10); viz.resize(N+10);
  iss.resize(N+10); low.resize(N+10);
  for(int i=1;i<=N;++i) {
    if(!viz[i]) df(i);
  }
}