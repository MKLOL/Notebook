class RMQmin {
private:
    vector<vector<int>> rmq;
    vector<int> v, lg;
    int N, log;
 
    // Custom function to calculate the logarithm base 2 of an integer
    int log2(int x) {
        int res = 1;
        while (x >>= 1) res++;
        return res;
    }
 
    // Function to generate the RMQ table
    void genRmq() {
        for (int i = 2; i <= N; ++i) {
            lg[i] = lg[i / 2] + 1;
        }
        for (int i = 0; i < N; ++i) {
            rmq[0][i] = v[i];
        }
        for (int i = 1; (1 << i) <= N; ++i) {
            for (int j = 0; j + (1 << i) - 1 < N; ++j) {
                rmq[i][j] = min(rmq[i - 1][j], rmq[i - 1][j + (1 << (i - 1))]);
            }
        }
    }
 
public:
    // Constructor to initialize the table with given size and values
    RMQmin() {};
    RMQmin(const vector<int>& values) : v(values) {
        N = v.size(); // Assuming 1-based indexing
        log = log2(N) + 1;
        rmq.assign(log + 1, vector<int>(N + 1));
        lg.assign(N + 1, 0);
        genRmq();
    }
 
    // Function to query the minimum value in the range [x, y]
    int query(int x, int y) {
        int l = lg[y - x + 1], sh = y - x + 1 - (1 << l);
        return min(rmq[l][x], rmq[l][x + sh]);
    }
};

class SuffixArray {
  public:
  vi sa,lcp,rev;
  RMQmin rq; 
  int lcpf(int x, int y) {
    x = rev[x]; y = rev[y];
    if (x > y) {
      swap(x,y);
    }
    if (x == y) return sz(sa) - x;
    return rq.query(x,y-1);
  }
  SuffixArray(string &s) {
    vi norm,cnt,w,tmp;
    int N = s.size();
    sa.resize(N); norm.resize(N); w.resize(N);
    tmp.resize(N); lcp.resize(N); rev.resize(N);
    int lim = max(N,256)+10; cnt.resize(lim);

    FOR(i,N) {
      norm[i] = s[i]+1;
      ++cnt[norm[i]];
    }
    FOR(i, lim) if(i) cnt[i] += cnt[i-1]; 
    FOR(i,N) sa[--cnt[norm[i]]] = i;
    
 
    for(int k=1; k < N;k*=2) {
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
    FOR(i, sz(sa)) {
      rev[sa[i]] = i;
    }
    rq = RMQmin(lcp);
  }
};
