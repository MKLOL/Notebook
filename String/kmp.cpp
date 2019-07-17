void make() {
  int k = -1; nx[0] = -1;
  for(int i=1;i<sz(s1);++i) {
    while(k >= 0 && s1[k+1] != s1[i]) k = nx[k];
    if(s1[k+1] == s1[i]) ++k; nx[i] = k;
  }
}
void match() {
  int k=-1;
  for(int i=0;i<sz(s2);++i) {
    while(k >= 0 && s1[k+1] != s2[i]) k = nx[k];
    if(s1[k+1] == s2[i]) ++k; 
    if(k==sz(s1)-1) k = nx[k]; // match on i - sz(s1)
  }
}
