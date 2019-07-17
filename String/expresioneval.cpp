string gb; vector<vector<string>> ops;
// is operation op, at location loc, when the string is st,dr
int is(string op, int loc,int st,int dr) {
  if(loc + op.size() - 1 > dr) return 0;
  int ok = 1;
  for(int i=0;i<op.size() && ok;++i) {
    if(gb[i+loc] != op[i]) ok = 0;
  }
  return ok;
}
int make(string op,int x,int y) { // make the operations
  if(op == "+") return x+y; return 0;
}
// evals substring(st,dr), when we should only check lvl forward
int eval(int st,int dr, int lvl) {
  for(int t = lvl;t<ops.size();++t) {
    int par = 0;
    for(int i = dr;i>=st;--i) {
      if(gb[i] == '(') ++ par; if(gb[i] == ')') -- par;
      if(par) continue;
      for(auto op : ops[t]) {
        if(is(op,i,st,dr)) {
          return make(op,eval(st,i-1,t),eval(i+op.size(),dr,t));
        }
      }
    }
  }
  if(gb[st] == '(') return eval(st+1,dr-1,0);
  return getnum(st,dr);
}
void init() { //add operations in order, call at main start
  ops.pb(vector<string>({"+","-"}));
  ops.pb(vector<string>({"/","%","*"}));
}
int eval(string &s) {
  gb = "";
  for(auto c : s) if(c != ' ') gb.pb(c);
  int ret = eval(0,gb.size()-1,0);
  return ret;
}