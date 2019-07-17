int N,M,L,R,K,v[Nmax],p;
vi g[Nmax];
int l[Nmax],r[Nmax],u[Nmax],was[Nmax],S;
int match(int q) {
  if(was[q]) return 0; was[q]=1;
  for(auto x : g[q]) {
    if(!r[x]) { l[q]=x; r[x]=q; return 1;}
  }
  for(auto x: g[q]) {
    if(match(r[x])) { l[q]=x; r[x]=q; return 1; }
  }
  return 0;
}
void matching() { //edges i,l[i] if l[i]>0
  int ok = 1; while(ok) {
    ok = 0; for(int i=0;i<=L;++i) was[i]=0;
    for(int i=1;i<=L;++i) { if(!l[i]) ok|= match(i); }
  }
}