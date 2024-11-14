class Kmp {
public:
  vi nx;
  string p; //pattern

  Kmp(string &s) p(s) {
    nx.resize(sz(s));
    int k = -1; nx[0] = -1;
    rep(i,1,sz(s)) {
      while(k >= 0 && s[k+1] != s[i]) k = nx[k];
      if(s[k+1] == s[i]) ++k;
      nx[i] = k;
    } 
  }

  vi match(string &s) {
    vi ret;
    int k=-1;
    for(int i=0;i<sz(s);++i) {
      while(k >= 0 && p[k+1] != s[i]) k = nx[k];
      if(p[k+1] == s[i]) ++k; 
      if(k==sz(p)-1) {
        k = nx[k];
        ret.pb(i-sz(p)+1);
      }
    }
    return ret;
  }
};