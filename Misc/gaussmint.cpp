template<int MOD>
struct ModInt {
  unsigned x;
  ModInt() : x(0) { }
  ModInt(signed sig) : x(sig) {  }
  ModInt(signed long long sig) : x(sig%MOD) { }
  int get() const { return (int)x; }
  ModInt pow(ll p) { ModInt res = 1, a = *this; while (p) { if (p & 1) res *= a; a *= a; p >>= 1; } return res; }
 
  ModInt &operator+=(ModInt that) { if ((x += that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator-=(ModInt that) { if ((x += MOD - that.x) >= MOD) x -= MOD; return *this; }
  ModInt &operator*=(ModInt that) { x = (unsigned long long)x * that.x % MOD; return *this; }
  ModInt &operator/=(ModInt that) { return (*this) *= that.pow(MOD - 2); }
 
  ModInt operator+(ModInt that) const { return ModInt(*this) += that; }
  ModInt operator-(ModInt that) const { return ModInt(*this) -= that; }
  ModInt operator*(ModInt that) const { return ModInt(*this) *= that; }
  ModInt operator/(ModInt that) const { return ModInt(*this) /= that; }
  bool operator<(ModInt that) const { return x < that.x; }
  friend ostream& operator<<(ostream &os, ModInt a) { os << a.x; return os; }
};
typedef ModInt<998244353> mint;
#define Nmax 555

mint A[Nmax][Nmax], X[Nmax];
int k; // A[i][1] * X[1] + ... + A[i][M] * X[M] = A[i][M+1]
void gauss(int N, int M) {
  int i=0,j=0;
  while(i<N && j<M) {
    int k;
    for(k=i;k<N;++k) if( A[k][j].x ) break;
    if(k==N) { ++j; continue; }
    if(k!=i) for(int q=0;q<=M;++q) swap(A[i][q],A[k][q]);
    for(int q=j+1;q<=M;++q) A[i][q] /= A[i][j];
    A[i][j] = 1;
    for(int u=i+1;u<N;++u) {
      for(int q=j+1;q<=M;++q) A[u][q] -= A[u][j]*A[i][q];
      A[u][j]=0;
    }
    ++i; ++j;
  }
  for(int i=N-1;i>=0;--i) {
    for(int j=0;j<=M;++j) {
      if(A[i][j].x) {
        if (j == M) {} //HANDLE NO SOLUTION
        X[j] = A[i][M];
        for(int k=j+1;k<M;++k) X[j] -= X[k]*A[i][k];
        break;
      }
    }
  }