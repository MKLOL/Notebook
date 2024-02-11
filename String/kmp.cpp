class Kmp {
private:
  vi nx;
public:
  Kmp(string &s1) {
    nx.resize(sz(s1));
    int k = -1; nx[0] = -1;
    rep(i,1,sz(s1)) {
      while(k >= 0 && s1[k+1] != s1[i]) k = nx[k];
      if(s1[k+1] == s1[i]) ++k;
      nx[i] = k;
    } 
  }

  // s1 is pattern, s2 is big string
  vi match(string &s1, string &s2) {
    vi ret;
    int k=-1;
    for(int i=0;i<sz(s2);++i) {
      while(k >= 0 && s1[k+1] != s2[i]) k = nx[k];
      if(s1[k+1] == s2[i]) ++k; 
      if(k==sz(s1)-1) {
        k = nx[k];
        ret.pb(i-sz(s1)+1);
      }
    }
    return ret;
  }
};