int tr[Nmax], nw[Nmax], NR, term[Nmax], len[Nmax], to[Nmax][sigma], link[Nmax], sz = 1;
void add(string s) { // doesn't handle dups
  int cur = 0;
  for(auto c: s) {
    if(!to[cur][c - 'a']) {
        to[cur][c - 'a'] = sz++;
        len[to[cur][c - 'a']] = len[cur] + 1;
    }
    cur = to[cur][c - 'a'];
  }
  term[cur] = cur; tr[cur] = ++NR;
}
 
void push_links() {
  queue<int> Q; Q.push(0);
  while(!Q.empty()) {
    int V = Q.front(); Q.pop(); int U = link[V];
    if(!term[V]) term[V] = term[U];
    for(int c = 0; c < sigma; c++) {
      if(to[V][c]) {
          link[to[V][c]] = V ? to[U][c] : 0;
          Q.push(to[V][c]);
      } else to[V][c] = to[U][c];
    }
  }
}

void match(string s) {
  int cur = 0;
  for(auto c : s) {    
    cur = to[cur][c-'a']; int f = cur;
    while(f) {
      if(tr[f]) tr[f]; // match on tr[f]
      if(f == term[f]) f = term[link[f]];
      else f = term[f];
    }
  }
}
