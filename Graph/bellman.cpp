vector<pii> g[Nmax];
int N,cnt[Nmax],d[Nmax];
queue<int> q;
void bellman(int r) {
  for(int i=1;i<=N;++i) d[i] = inf; d[r] = 0; q.push(r);
  while(!q.empty()) {
    int x = q.front(); ++cnt[x]; 
    if(cnt[x] > N) return; q.pop();
    for(auto p: g[x]) {
      int y = p.fs, c = p.sc;
      if(d[y] > d[x] + c) { d[y] = d[x] + c; q.push(y); }
    }
  }
}