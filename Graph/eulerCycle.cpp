void dfs(int x) { //isD = isDeleted
  for(auto n : g[x]) { 
    if(isD[n.sc]==0) { isD[n.sc]=1; dfs(n.fs); }
  }
  ret.pb(x); 
} // fs = node, sc = edge num