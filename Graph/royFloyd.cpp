FOR(k,N) FOR(i,N) FOR(j,N) {
  if(best[i][k] && best[k][j] && i!=j && (best[i][k]+best[k][j]<best[i][j] || !best[i][j])) {
      best[i][j]=best[i][k]+best[k][j];
  }
}