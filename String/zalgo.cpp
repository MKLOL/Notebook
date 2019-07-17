// z -> int array, s2 -> char array, N, it's length. At the end have z[i]
int left=0, right=0;
for(int i=1;i<N;++i) {
  if( i > right) {
    left = i, right = i;
    while (right < N && s2[right-left] == s2[right]) ++right;
    z[i] = right - left; --right;
  } else {
    int k = i - left; if(z[k] < right-i+1) z[i] = z[k];
    else {
      left=i;
      while (right < N && s2[right - left] == s2[right]) ++right;
      z[i] = right-left; --right;
}}}
