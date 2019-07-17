#define Pmax 19
#define MOD 5767169 //magic: MOD-1 must be multiple of 2^Pmax
#define GEN1 177147 //magic: root of order 2^Pmax mod MOD
#define GEN2 5087924 //magic: inverse of GEN1
#define Nmax 530000
vi v1,v2,B; int k=1, z[2][Nmax], b[Nmax];
int powy(int x, int y) {
  if(!y) return 1; int z = powy(x,y/2);
  z = (1LL*z*z) % MOD; if(y%2) z = (1LL*z*x) % MOD;
  return z;
}
//start: index, inc: divisions, rev0 fft , rev1 reverse fft
void fft(vector<int> &v, int start, int inc, int rev) {
  if(inc==k) return; //we done 
  fft(v,start,inc*2,rev); //compute first half
  fft(v,start+inc,inc*2,rev); //compute second half
  int nr = k/inc, Z = 1, zN = z[rev][nr];
  for(int i=0;i<nr/2;++i) {
    int x = (1LL*Z*v[start + (2*i+1)*inc]) % MOD; 
    b[start+i*inc] = (v[start + 2*i*inc] + x) % MOD;
    b[start+(i+nr/2)*inc] = (v[start + 2*i*inc] - x + MOD) % MOD;
    Z = (1LL*Z*zN)%MOD; //Z is current root
  }
  for(int i=0;i<nr;++i) {
    v[start+i*inc] = b[start+i*inc];
  }
}
void preprocess_fft(vector<int> &v1, vector<int> &v2) {
  int pw = 0; //smallest power of 2 greater than degree
  int N = v1.size(), M = v2.size(), deg = M+N;
  while(k<deg) { k*=2; ++pw; } //smallest pw2 >= final degree
  for(int i=N;i<k;++i) v1.pb(0);
  for(int i=M;i<k;++i) v2.pb(0);
  int r1 = GEN1, r2 = GEN2; //square until roots of order 2^pw
  for(int i=pw;i<Pmax;++i) {
    r1 = (1LL*r1*r1) % MOD; r2 = (1LL*r2*r2) % MOD;
  }
  for(int nr=k;nr>=1;nr/=2) { //primitives 2^nr
    z[0][nr] = r1; z[1][nr] = r2; // 1 / z0
    r1 = (1LL*r1*r1) % MOD; r2 = (1LL*r2*r2) % MOD;
  }
}
vector<int> multiply(vector<int> &v1, vector<int> &v2) {
  preprocess_fft(v1, v2);
  vi ret;
  fft(v1,0,1,0); fft(v2,0,1,0);
  for(int i=0;i<k;++i) ret.pb((1LL*v1[i]*v2[i])%MOD);
  fft(ret,0,1,1);
  int inv = powy(k,MOD-2);
  for(int i=0;i<k;++i) ret[i] = (1LL*ret[i]*inv) % MOD;
  return ret;
}