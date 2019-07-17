char s[2010000], s1[2010000];
int val[2020201],maxind,maxVal,N;
void make_sir(){
  s1[0]='*';
  for(int i=1;i<=N;++i) { s1[i*2-1]=s[i]; s1[i*2]='*';}
}
ll pscpld (char *s) {
  ll S = 0; N = strlen(s+1); make_sir();
  for(int i=1;i<2*N;++i) {
    if(maxVal >= i) {
      int loc = maxind - (i-maxind);
      val[i] = min(val[loc],maxVal-i);
    }
    while((i - val[i] >= 0) && (i + val[i] <= 2*N) && 
          (s1[i-val[i]] == s1[i+val[i]])) {
      ++val[i];
      if(i + val[i] > maxVal){
        maxVal = i + val[i]; maxind = i;
      }
    }
  }
  for(int i=1;i<2*N;++i){
    S += (val[i]+1)/2; if(s1[i]=='*') --S;
  }
  return S;
}