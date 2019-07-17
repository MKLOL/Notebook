#define Nmax 101010
#define p1 47
#define p2 149
#define MOD1 666013
#define MOD2 991777
int nr1[Nmax],pow1[Nmax],pow2[Nmax],nr2[Nmax],nrfin;
char car[Nmax]; // string we want to hash, STARTING FROM 1
int N,M;
void make() {
  pow1[0]=1,pow2[0]=1;
  for(int i=1;i<=N;++i) {
    pow1[i]=(1LL*pow1[i-1]*p1)%MOD1;
    pow2[i]=(1LL*pow2[i-1]*p2)%MOD2;
    nr1[i]=((1LL*nr1[i-1]*p1)%MOD1 + car[i])%MOD1;
    nr2[i]=((1LL*nr2[i-1]*p2)%MOD2 + car[i])%MOD2;
  }
}
int querry(int x,int y,int x1,int y1,int debug) {
  int sol1,sol2,sol12,sol22;
  sol1=1LL*(nr1[y]-(1LL*pow1[y-x+1]*nr1[x-1])%MOD1+MOD1)%MOD1;
  sol2=1LL*(nr1[y1]-(1LL*pow1[y1-x1+1]*nr1[x1-1])%MOD1+MOD1)%MOD1;
  sol12=(nr2[y]-(1LL*pow2[y-x+1]*nr2[x-1])%MOD2+MOD2)%MOD2;
  sol22=(nr2[y1]-(1LL*pow2[y1-x1+1]*nr2[x1-1])%MOD2+MOD2)%MOD2;
  if(sol1==sol2 && sol12 == sol22) return 1; return 0;
}