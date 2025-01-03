vpi getMin(vpi &v) {
  vpi ret(sz(v));
  for (int i=0;i<sz(v);++i) {
    if (i == 0) ret[i].fs = 0;
    else if (v[i] > v[i-1]) {
      ret[i].fs = i;
    } else {
      int pos = i-1;
      while(pos>=0 && v[pos] > v[i]) {
        pos = ret[pos].fs - 1;
      }
      if (pos == -1 ||v[pos] < v[i]) ++pos; 
      ret[i].fs = pos;
    }
  }
  for (int i=sz(v)-1;i>=0;--i) {
    if (i == sz(v)-1) ret[i].sc = sz(v)-1;
    else if (v[i] > v[i+1]) {
      ret[i].sc = i;
    } else {
      int pos = i+1;
      while(pos < sz(v)-1 && v[pos] > v[i]) {
        pos = ret[pos].sc + 1;
      }
      if (pos == sz(v) || v[pos] < v[i]) --pos; 
      ret[i].sc = pos;
    }
  }
  return ret;
}
 
vpi getMax(vpi &v) {
  vpi ret(sz(v));
  for (int i=0;i<sz(v);++i) {
    if (i == 0) ret[i].fs = 0;
    else if (v[i] < v[i-1]) {
      ret[i].fs = i;
    } else {
      int pos = i-1;
      while(pos>=0 && v[pos] < v[i]) {
        pos = ret[pos].fs - 1;
      }
      if (pos == -1 || v[pos] > v[i]) ++pos; 
      ret[i].fs = pos;
    }
  }
  for (int i=sz(v)-1;i>=0;--i) {
    if (i == sz(v)-1) ret[i].sc = sz(v)-1;
    else if (v[i] < v[i+1]) {
      ret[i].sc = i;
    } else {
      int pos = i+1;
      while(pos < sz(v)-1 && v[pos] < v[i]) {
        pos = ret[pos].sc + 1;
      }
      if (pos == sz(v) || v[pos] > v[i]) --pos; 
      ret[i].sc = pos;
    }
  }
  return ret;
}
