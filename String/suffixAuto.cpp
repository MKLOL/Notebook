unordered_map<char, int> h[200100];
int len[200100],lnk[200100],last,curr,nr;
long long add_char(char c) {
  long long ret = 0;
  curr = ++nr; len[curr] = len[last] + 1; int p = last;
  while(p !=-1 && !h[p][c]){h[p][c] = curr; p = lnk[p];}
  if(p==-1) {
    lnk[curr] = 0; ret += len[curr];
  } else {
    int q = h[p][c];
    if(len[q] == len[p]+1) {
      lnk[curr] = q; ret += (len[curr] - len[q]);
    } else {
      int clone = ++nr; 
      len[clone] = len[p] + 1; lnk[clone] = lnk[q];
      ret += (len[clone] - len[lnk[q]]); h[clone] = h[q];
      while(p!=-1 && h[p][c] == q) {
        h[p][c] = clone; p = lnk[p];
      }
      ret -= (len[q] - len[lnk[q]]); lnk[q] = clone;
      ret += (len[q] - len[lnk[q]]); lnk[curr] = clone;
      ret += (len[curr] - len[clone]);
    }
  }
  last = curr; return ret; 
}
void suffix_automaton(string &s) {
  last = 0, curr = 0, nr = 0; len[0] = 0; lnk[0] = -1;
  for(auto c: s) add_char(c); //also counts new suffixes
}
