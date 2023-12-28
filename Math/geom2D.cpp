#define PI 3.141592653589793
#define eps 0.00000001
int cmp(double a, double b) {
  if(a + eps <= b) return -1; if(a < b + eps) return 0; return 1;
}
int cmp(pdd a, pdd b) {
  int t = cmp(a.fs, b.fs); if(t) return t; return cmp(a.sc,b.sc);
}
pdd in = mp(INFINITY, INFINITY); //no solution
pdd operator+(pdd a, pdd b) { return mp(a.fs+b.fs, a.sc+b.sc); }
pdd operator-(pdd a, pdd b) { return mp(a.fs-b.fs, a.sc-b.sc); }
pdd operator*(pdd a, double t) { return mp(a.fs*t, a.sc*t); }
pdd operator/(pdd a, double t) { return mp(a.fs/t, a.sc/t); }
double operator*(pdd a, pdd b) { return a.fs*b.fs + a.sc*b.sc; }
double operator%(pdd a, pdd b) { return a.fs*b.sc - a.sc*b.fs; }
bool operator<(pdd a, pdd b) { return cmp(a,b) < 0; }
bool operator==(pdd a, pdd b) { return cmp(a,b) == 0; }
double norm(pdd a) { return sqrt(a*a); }
double arg(pdd a) { return atan2(a.sc,a.fs); }
inline double dist(pdd p, pdd q) { return norm(p-q);}
inline int ccw(pdd a, pdd b, pdd c) { return cmp((a-c)%(b-c),0);}
inline double angle(pdd a, pdd b, pdd c) { //[-PI/2, PI/2]
  pdd u = a - b, v = c - b; return atan2(u % v, u * v);
}
inline int between(pdd p, pdd q, pdd r) {
  return ccw(p,q,r) == 0 && cmp((p-q)*(r-q),0) <= 0;
}
int segInters(pdd p, pdd q, pdd r, pdd s) {
  pdd A = q-p, B = s-r, C = r-p, D = s-q;
  int a = cmp(A%C,0) + 2*cmp(A%D,0);
  int b = cmp(B%C,0) + 2*cmp(B%D,0);
  if(a==3 || a==-3 || b==3 || b==-3) return false;
  if (a || b || p == r || p == s || q == r || q == s) return true;
  int t = (p<r) + (p<s) + (q<r) + (q<s);
  return t!=0 && t!=4;
}
double distToSeg(pdd p, pdd q, pdd r) { // from r to pq
  pdd A = r - q, B = r - p, C = q - p;
  double a = A * A, b = B * B, c = C * C;
  if (cmp(b, a + c) >= 0) return sqrt(a);
  else if (cmp(a, b + c) >= 0) return sqrt(b);
  else return abs(A % B) / sqrt(c); //ONLY THIS IF WHOLE LINE
}
int inPoly(pdd p, vector<pdd> &T) { // -1 border, 0 outside, 1 inside
  double a = 0; int N = T.size();
  for (int i = 0; i < N; i++) {
    if (between(T[i], p, T[(i+1) % N])) return -1;
    a += angle(T[i], p, T[(i+1) % N]);
  }
  return cmp(a,0) != 0;
}
pdd lineInters(pdd p, pdd q, pdd r, pdd s) {
  if(cmp(p-q,s-r) == 0 || cmp(p-q,r-s) == 0) return mp(INFINITY,INFINITY); 
  pdd a = q - p, b = s - r, c = mp(p % q, r % s);
  return mp(mp(a.fs, b.fs) % c, mp(a.sc, b.sc) % c) / (a % b);
}
pdd foot(pdd P, pdd A, pdd B) {
  pdd dir = B-A; pdd x = P-A;
  return (dir*((P-A)*dir))/(dir*dir) + A;
}
// Perp in Q on PQ at distance d
pair<pdd,pdd> disppt(pdd P, pdd Q, double d) {
  pdd dir = P - Q; pdd r = pdd(dir.sc, -dir.fs);
  pdd k = r * (d/norm(r)); return mp(Q + k, Q - k);
}
double area(vector<pdd> &v) {
  double ret = 0; int N = v.size();
  for(int i=0;i<N;++i) { ret += v[i]%v[(i+1)%N]; }
  return abs(ret)/2;
}
double getX(pdd v1, pdd v2, double t) { // find (x,t) on (v1,v2)
  return (t - v1.sc)*(v1.fs - v2.fs) / (v1.sc - v2.sc) + v1.fs;
}
double getY(pdd v1, pdd v2, double t) { // find (t,y) on (v1,v2)
  return (t - v1.fs)*(v1.sc - v2.sc) / (v1.fs - v2.fs) + v1.sc;
}
vector<pdd> polygIntersect(vector<pdd> &P, vector<pdd> &Q) {
  vector<pdd> R, nope;
  int m = Q.size(), n = P.size(); if (m == 0 || n == 0) return nope;
  int a = 0, b = 0, aa = 0, ba = 0, inflag = 0;
  while ((aa < n || ba < m) && aa < 2*n && ba < 2*m) {
    pdd p1 = P[a], p2 = P[(a+1) % n], q1 = Q[b], q2 = Q[(b+1) % m];
    pdd A = p2 - p1, B = q2 - q1;
    int cross = cmp(A % B, 0), ha = ccw(p2, q2, p1), hb = ccw(q2, p2, q1);
    if (cross == 0 && ccw(p1, q1, p2) == 0 && cmp(A * B,0) < 0) {
      if(between(p1, q1, p2)) R.pb(q1); if(between(p1, q2, p2)) R.pb(q2);
      if(between(q1, p1, q2)) R.pb(p1); if(between(q1, p2, q2)) R.pb(p2);
      if (R.size() < 2) return nope; inflag = 1; break;
    } else if (cross != 0 && segInters(p1, p2, q1, q2)) {
      if (inflag == 0) aa = ba = 0;
      R.pb(lineInters(p1, p2, q1, q2));
      inflag = (hb > 0) ? 1 : -1;
    }
    if (cross == 0 && hb < 0 && ha < 0) return R;
    bool t = cross == 0 && hb == 0 && ha == 0;
    if (t ? (inflag == 1) : (cross >= 0) ? (ha <= 0) : (hb > 0)) {
      if (inflag == -1) R.pb(q2); ba++; b++; b %= m;
    } else {
      if (inflag == 1) R.pb(p2); aa++; a++; a %= n;
    }
  } 
  if (inflag == 0) {
    if (inPoly(P[0], Q)) return P; if (inPoly(Q[0], P)) return Q;
  }
  R.erase(unique(R.begin(),R.end()),R.end());
  if (R.size() > 1 && R.front() == R.back()) R.pop_back();
  return R;
}
/********** CONVEX HULL CCW *********/
pdd V; int cmpv(pdd a, pdd b) { return ccw(V,a,b) > 0;}
vector<pdd> hull(vector<pdd> &a) { //graham
  vector<pdd> b; sort(a.begin(),a.end()); V = a[0];
  sort(a.begin()+1,a.end(),cmpv);
  for(int i = 0; i < a.size(); ++i) {
    while(b.size() >= 2 && ccw(b[b.size()-2],b[b.size()-1],a[i]) <= 0) {
      b.pop_back();
    }
    b.pb(a[i]);
  }
  return b;
}
vector<pdd> hull2 (vector<pdd> & a) {
  if (a.size() == 1)  return a;
  sort (a.begin(), a.end()); pdd p1 = a[0],  p2 = a.back();
  vector<pdd> up, down, b; up.pb (p1); down.pb (p1);
  for (int i=1; i<a.size(); ++i) {
    if (i==a.size()-1 || ccw (p1, a[i], p2) < 0) { //<= > for colin
      while (up.size()>=2 && ccw(up[up.size()-2], up[up.size()-1], a[i]) >= 0) {
        up.pop_back(); }
      up.pb(a[i]);
    }
    if(i==a.size()-1 || ccw (p1, a[i], p2) > 0) { //>= < for colin
      while (down.size()>=2 && ccw(down[down.size()-2], down[down.size()-1], a[i]) <= 0) {
        down.pop_back();
      }
      down.pb (a[i]);
    }
  }
  for (size_t i=0; i<down.size(); ++i) b.pb(down[i]);
  for (size_t i=up.size()-2; i>0; --i) b.pb(up[i]);
  return b;
}
/*************** CIRCLES *****************/
int between(pdd o, double r, pdd A, pdd B, pdd C) { //is B on arc AC (ccw)
  double a = arg(A - o), b = arg(B - o), c = arg(C - o);
  if(cmp(a,c) == -1) return cmp(a,b) <= 0 && cmp(b,c) <= 0;
  else return cmp(a,b) <= 0 || cmp(b,c) <= 0;
}
pair<pdd,pdd> circInters(pdd o1, double r1, pdd o2, double r2) {
  pdd dir = o2 - o1; double d = norm(dir);
  if(cmp(r1 + r2, d) == 0 || cmp(d + r2, r1) == 0 || cmp(d + r1, r2) == 0) {
    return mp(o1 + dir * r1/(r1 + r2), in); //tangent
  }
  if(cmp(r1 + r2, d) == -1 || cmp(d + r2, r1) == -1 || cmp(d + r1, r2) == -1) {
    return mp(in, in); // too far, 2nd inside 1st, 1st inside 2nd
  }
  double x = (d*d - r2*r2 + r1*r1)/(2*d); //2 intersections
  return disppt(o1, o1 + dir * x/d, sqrt(r1*r1 - x*x));
}
pair<pdd,pdd> circLine(pdd o, double r, pdd a, pdd b){
  pdd h = foot(o, a, b); double d = norm(h - o);
  if(cmp(d,0) == 0) { //line through center
    return mp( (a - o)*r/norm(a-o) + o, (b - o)*r/norm(b - o) + o);
  }
  if(cmp(d*d, r*r) == 0) return mp(h, in); //tangent
  if(cmp(d*d, r*r) == 1) return mp(in, in); //no inters
  return disppt(o, h, sqrt(r*r - d*d));
}
pdd cinv(pdd o, double r, pdd p) { //inversion of p
  pdd p0 = p - o; return o + p0 * (r*r/(p0 * p0));
}
bool inCircle(pdd o, double r, pdd p) {
  return cmp((p - o)*(p - o), r*r) <= 0;
} 
pdd circumcenter(pdd p, pdd q, pdd r) {
  pdd a = p - r, b = q - r, c = mp(a * (p + r) / 2, b * (q + r) / 2);
  return mp(c % pdd(a.sc, b.sc), pdd(a.fs, b.fs) % c) / (a % b);
}
pair<pdd,double> SpanningCircle(vector<pdd>& T) {
  int N = T.size(); random_shuffle(T.begin(),T.end());
  pair<pdd,double> C = mp(mp(0,0), 0);
  for (int i = 0; i < N; ++i) {
    if(inCircle(C.fs,C.sc,T[i])) continue;
    C = mp(T[i], 0);
    for (int j = 0; j < i; ++j) {
      if (inCircle(C.fs,C.sc, T[j])) continue;
      C = mp((T[i] + T[j]) / 2, norm(T[i] - T[j]) / 2);
      for (int k = 0; k < j; k++) {
        if (inCircle(C.fs,C.sc, T[k])) continue;
        pdd o = circumcenter(T[i], T[j], T[k]);
          C = mp(o, norm(o - T[k]));
      }
    }
  }
  return C;
}
pair<pdd, pdd> getTangents(pdd o, double r, pdd p) {
  if(inCircle(o,r,p)) return mp(in,in);
  double d = sqrt( (p-o)*(p-o) - r*r );
  double ang = arg(o-p); double ofs = atan(r/d);
  pdd dir1 = mp(cos(ang+ofs),sin(ang+ofs));
  pdd dir2 = mp(cos(ang-ofs),sin(ang-ofs));
  return mp(p + dir1*d, p + dir2*d);
}
/************************* ax + by + c = 0 **********************/
pair<pdd,double> getLine(pdd p1, pdd p2) { //points to ax+by+c=0
  double a = (p2.sc - p1.sc), b = (p1.fs - p2.fs);
  double n = sqrt(a*a+ b*b); a /= n; b /= n; //only if normalize
  double c = -(a*p1.fs + b*p1.sc); return mp(mp(a,b),c);
}
double dist(pdd p, pair<pdd,double> line) {
  double ret = abs(line.fs.fs*p.fs + line.fs.sc*p.sc + line.sc);
  ret /= norm(ret); return ret;
}
pdd lineInters(pair<pdd,double> l1, pair<pdd,double> l2) {
  double a1=l1.fs.fs, b1=l1.fs.sc, c1 = l1.sc;
  double a2=l2.fs.fs, b2=l2.fs.sc, c2 = l2.sc;
  double x, y;
  if(cmp(a1,0) == 0) {
    y = -c1 / b1;
    if(cmp(a2,0) != 0) x = (- c2 - b2*y) / a2;
    else return mp(INFINITY,INFINITY); //both vertical
  } else if(cmp(a2,0) == 0) {
    y = -c2 / b2; x = ( - c1 - b1*y) / a1;
  } else {
    b1 /= a1; b2 /= a2; c1 /= a1; c2 /= a2;
    if(cmp(b1,b2)==0) return mp(INFINITY,INFINITY); //parallel
    else y = (c2 - c1) / (b1 - b2); x = -c1 - b1*y;
  }
  return mp(x,y);
}
