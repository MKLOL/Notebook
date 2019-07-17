/****************** CLOSEST POINTS ********************/
vector<pair<pll,int> > v,x,y;
ll INF = 4e18;
ll dist(pll a, pll b) {
  return (a.fs - b.fs) * (a.fs - b.fs) + (a.sc - b.sc) * (a.sc - b.sc);
}
pair<ll,pii> solve(int st, int dr) {
  if (st >= dr - 1) return mp(INF,mp(0,0));
  if (dr - st == 2) {
    if (y[st] > y[st + 1]) swap(y[st], y[st + 1]);
    return mp(dist(x[st].fs, x[st + 1].fs),mp(x[st].sc, x[st+1].sc));
  }
  int mij = (st + dr) / 2;
  pair<ll,pii > ret = min(solve(st,mij),solve(mij,dr));
  merge(y.begin() + st, y.begin() + mij, y.begin() + mij, y.begin() + dr, v.begin());
  copy(v.begin(), v.begin() + (dr - st), y.begin() + st);
  int nr = 0; 
  for (int i=st; i<dr; ++i) {
    if (abs(y[i].fs.sc - x[mij].fs.fs) < ret.fs) v[nr++] = y[i];
  }
  for(int i=0;i<nr;++i) {
    for (int j=i+1; j<nr && j<=i+7; ++j) {
      ll d = dist(v[i].fs,v[j].fs);
      if(d < ret.fs) ret = mp(d,mp(v[i].sc,v[j].sc));
    }
  }
  return ret;
}
pair<ll,pii> closest_points() {
  int N = x.size(); sort(x.begin(), x.end()); v.resize(N);
  for(ll i=0;i<N;++i) y.pb( mp(mp(x[i].fs.sc, x[i].fs.fs), x[i].sc));
  return solve(0,N);
}
/****************** MAX AREA ********************/
pair<pdd,pair<pdd,pdd> > getMaxArr(vector<pdd> &v) {
  v = convex_hull(v);
  int A = 0, B = 1, C = 2, N = v.size();
  double S = 0; pdd a,b,c;
  while(true) {
    double T = arr(v[A],v[B],v[C]);
    if(T > S) {a = v[A], b = v[B], c = v[C]; S = T;}
    while(true) {
      while(T <= arr(v[A], v[B], v[(C+1) %N])) {
        C = (C+1) %N; T = arr(v[A],v[B],v[C]);
        if(T > S) {a = v[A], b = v[B], c = v[C]; S = T;}
      }
      if(T < arr(v[A], v[(B+1) %N], v[C])) {
        B = (B+1) %N; T = arr(v[A],v[B],v[C]);
        if(T > S) {a = v[A], b = v[B], c = v[C]; S = T;}
      } else break;
    }
    A = (A+1) % N; if(A == 0) break;
    if(A == B) B = (B+1) %N; if(B == C) C = (C+1) %N;
  }
  return mp(a,mp(b,c));
}
/****************** FARTHEST POINTS ********************/
pair<pdd,pdd> farthestPoints(vector<pdd> &v) {
  v = convex_hull(v); vector<pair<pdd,pdd> > A; //antipodal
  int k = 1, M = v.size();
  while(area(v[0],v[k+1],v[M-1]) > area(v[0],v[k],v[M-1])) ++k;
  int i = 0, j = k;
  //If want farthest point from each edge, do j<2*M and double array
  while(i<=k && j<M) {
    A.pb(mp(v[i],v[j]));
    while(j<M-1 && area(v[i+1],v[j+1],v[i]) > area(v[i+1],v[j],v[i])) {
      A.pb(mp(v[i],v[j])); ++j;
    }
    ++i;
  }
  pair<pdd,pdd> ret = mp(v[0],v[0]);
  for(auto p: A) {
    if(dist(p.fs,p.sc) > dist(ret.fs,ret.sc)) ret = p;
  }
  return ret;
}
/**************** TRANSFORMATIONS AND ELLIPSE ***************/
double rot[3][3] = {{cos(a),-sin(a),0},{sin(a),cos(a)},0},{0,0,1}};
double rotx[4][4] = {{1,0,0,0}, {0,cos(a),-sin(a),0}, 
{0,sin(a),cos(a)},0}, {0,0,0,1}};
double roty[4][4] = {{cos(a),0,sin(a),0}, {0,1,0,0},
{-sin(a),0,cos(a)},0},{0,0,0,1}};
double rotz[4][4] = {{cos(a),-sin(a),0,0},{sin(a),cos(a),0,0},
{0,0,1,0},{0,0,0,1}};
long double ellipseInt(long double x) {
  return b*(x*sqrt(a*a - x*x) + a*a*atan(x / sqrt(a*a - x*x))) / (2*a);
}