double A[Nmax][Nmax], X[Nmax];
int k, N, M; // A[i][1] * X[1] + ... + A[i][M] * X[M] = A[i][M+1]
void gauss() {
  int i=1,j=1;
  while(i<=N && j<=M) {
    int k;
    for(k=i;k<=N;++k) if( A[k][j]<-EPS || A[k][j]>EPS) break;
    if(k==N+1) { ++j; continue; }
    if(k!=i) for(int q=1;q<=M+1;++q) swap(A[i][q],A[k][q]);
    for(int q=j+1;q<=M+1;++q) A[i][q] /= A[i][j];
    A[i][j] = 1;
    for(int u=i+1;u<=N;++u) {
      for(int q=j+1;q<=M+1;++q) A[u][q] -= A[u][j]*A[i][q];
      A[u][j]=0;
    }
    ++i; ++j;
  }
  for(int i=N;i>0;--i) {
    for(int j=1;j<=M+1;++j) {
      if(A[i][j]>EPS || A[i][j]<-EPS) {
        if(j==M+1) {} //HANDLE NO SOLUTION
        X[j] = A[i][M+1];
        for(int k=j+1;k<=M;++k) X[j] -= X[k]*A[i][k];
        break;
      }
    }
  }
}