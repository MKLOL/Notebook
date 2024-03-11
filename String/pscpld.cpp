vi pscpld (string s) {
  string s1;
  int maxind=0,maxVal=0;
  for (int i=0;i<sz(s);++i) {
    s1 += s[i];
    if (i != sz(s)-1) {
      s1 += "*";
    }
  }

  vi val(sz(s1));

  for(int i=0;i<sz(s1);++i) {
    if(maxVal >= i) {
      int loc = maxind - (i-maxind);
      val[i] = min(val[loc],maxVal-i);
    }
    while((i - val[i] >= 0) && (i + val[i] < sz(s1)) && 
          (s1[i-val[i]] == s1[i+val[i]])) {
      ++val[i];
      if(i + val[i] > maxVal){
        maxVal = i + val[i] - 1; maxind = i;
      }
    }
  }
  
  return val;
}
