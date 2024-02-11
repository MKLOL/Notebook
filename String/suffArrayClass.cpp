class SuffixArray {
private:
  vi norm,cnt,w,tmp;
  int N,lim;
public:
  vi sa,lcp;
  SuffixArray(string &s) {
    N = s.size();
    sa.resize(N);
    norm.resize(N);
    w.resize(N);
    tmp.resize(N);
    lcp.resize(N);
    lim = max(N,26)+10;
    cnt.resize(lim);

    FOR(i,lim) cnt[i] = 0;
    FOR(i,N) {
      norm[i] = s[i]-'a'+1;
      ++cnt[norm[i]];
    }
    FOR(i, lim) {
      if(i) cnt[i] += cnt[i-1]; 
    }
    FOR(i,N) {
      sa[--cnt[norm[i]]] = i;
    }
 
    for(int k=1; 2*k < N;k*=2) {
 	  // sort by second
      FOR(i,k) w[i] = N-i-1;
      int ind = k;
      FOR(i,N) {
        if(sa[i] >= k) w[ind++] = sa[i]-k;
      }
      //sort by first
      FOR(i,lim) cnt[i] = 0;
      FOR(i,N) {
        ++cnt[norm[i]];
      }
      FOR(i,lim) {
        if(i) cnt[i] += cnt[i-1];
      }
      for(int i=N-1;i>=0;--i) {
        sa[--cnt[norm[w[i]]]] = w[i];
      }
      // renormalize
      FOR(i,N) {
        if(!i) {tmp[i] = 1; continue;}
        int val1 = sa[i]+k >= N ? 0: norm[sa[i]+k];
        int val2 = sa[i-1]+k >= N ? 0: norm[sa[i-1]+k];
        if(norm[sa[i]] == norm[sa[i-1]] && val1 == val2) {
          tmp[sa[i]] = tmp[sa[i-1]];  
        } else {
          tmp[sa[i]] = tmp[sa[i-1]]+1;
        }
      } 
      norm = tmp;
    }
    FOR(i,N) w[sa[i]] = i;
    int len = 0;
    FOR(i,N) {
      if(w[i] == N-1) {len = 0; lcp[w[i]] = 0; continue;}
      int j = sa[w[i]+1];
      while (i+len < N && j+len < N && s[i+len]==s[j+len]) ++len;
      lcp[w[i]] = len;
      if(len) --len;
    }
  }
};