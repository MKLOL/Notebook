struct point {
  double x, y, z; point(){};
  point(double _x, double _y, double _z){ x=_x; y=_y; z=_z; }
  point operator+ (point p) { return point(x+p.x, y+p.y, z+p.z); }
  point operator- (point p) { return point(x-p.x, y-p.y, z-p.z); }
  point operator* (double c) { return point(x*c, y*c, z*c); }
  point operator/ (double c) { return point(x/c, y/c, z/c); }
  point operator-() const { return point(-x, -y, -z);}
  point operator%(point p) {
    return point(y*p.z-z*p.y, z*p.x-x*p.z, x*p.y-y*p.x);
  }
  double operator* (point p) { return x*p.x + y*p.y + z*p.z; }
};
inline double dist(point a, point b) { return (a-b)*(a-b); }
inline point cross(point a, point b) { return a%b;}
void makePlane(point p1, point p2, point p3, double& a, double& b, double& c, double& d) {
  point normal = cross(p2-p1, p3-p1);
  a = normal.x; b = normal.y; c = normal.z; d = -a*p1.x-b*p1.y-c*p1.z;
}
point planeProj(point p, double a, double b, double c, double d) {
  double l = (a*p.x+b*p.y+c*p.z+d)/(a*a+b*b+c*c);
  return point(p.x-a*l, p.y-b*l, p.z-c*l);
}
double planeDist(point p, double a, double b, double c, double d){
  return fabs(a*p.x + b*p.y + c*p.z + d) / sqrt(a*a + b*b + c*c);
}
double planePlaneDist(double a, double b, double c, double d1, double d2){
  return fabs(d1 - d2) / sqrt(a*a + b*b + c*c); //only if parallel
}
// square distance between point and line(0), ray(2) or segment(1)
double pointLineDist(point s1, point s2, point p, int type){
  double pd2 = dist(s1, s2); point r; if(pd2 == 0) r = s1;
  else {
    double u = (p-s1)*(s2-s1) / pd2;
    r = s1 + (s2 - s1)*u;
    if(type != 0 && u < 0.0) r = s1;
    if(type == 1 && u > 1.0) r = s2;
  }
  return dist(r, p);
}
// Squared distance between lines ab and cd
double lineLineDistance(point a, point b, point c, point d) {
  point v1 = b-a, v2 = d-c, cr = cross(v1, v2);
  if (cr * cr < eps) return pointLineDist(a,b, c, 0); //parallel
  else {
    point n = cr / sqrt(cr * cr); //direction
    return n * (c - a);
  }
}
point lineLineInters(point a, point b, point c, point d) {
  if(lineLineDistance(a,b,c,d) > eps) return point(); //don't intersect
  point v1 = b-a, v2 = d-c, v3 = c-a, cr = cross(v1, v2);
  double s = (cross(v3,v2) * cr) / (cr*cr);
  return a + (b-a)*s;
}
double signedTetrahedronVol(point A, point B, point C, point D) {
  double A11 = A.x - B.x, A12 = A.x - C.x, A13 = A.x - D.x;
  double A21 = A.y - B.y, A22 = A.y - C.y, A23 = A.y - D.y;
  double A31 = A.z - B.z, A32 = A.z - C.z, A33 = A.z - D.z;
  double det = A11*A22*A33 + A12*A23*A31 +
    A13*A21*A32 - A11*A23*A32 - A12*A21*A33 - A13*A22*A31;
  return det / 6;
}

/********* HULL *******************/
struct twoset {
  void insert(int x) { (a == -1 ? a : b) = x; }
  bool contains(int x) { return a == x || b == x; }
  void erase(int x) { (a == x ? a : b) = -1; }
  int size() { return (a != -1) + (b != -1); } int a, b;
} E[MAXN][MAXN];
struct face { point norm; double disc; int I[3];};
face make_face(int i, int j, int k, int inside_i) {
  E[i][j].insert(k); E[i][k].insert(j); E[j][k].insert(i);
  face f; f.I[0] = i; f.I[1] = j; f.I[2] = k;
  f.norm = (A[j] - A[i]) % (A[k] - A[i]); f.disc = f.norm * A[i];
  if(f.norm * A[inside_i] > f.disc) {
    f.norm = -f.norm; f.disc = -f.disc;
  }
  return f;
}
vector<face> hull3(vector<point> &A) {
  vector<face> faces; face f; memset(E, -1, sizeof(E));
  FOR(i,4) for(int j=i+1;j<4;j++) for(int k=j+1;k<4;k++) {
    faces.pb(make_face(i, j, k, 6 - i - j - k));
  }
  for(int i = 4; i < N; i++) {
    for(int j = 0; j < faces.size(); j++) {
      f = faces[j];
      if(f.norm * A[i] > f.disc) {
        E[f.I[0]][f.I[1]].erase(f.I[2]);
        E[f.I[0]][f.I[2]].erase(f.I[1]);
        E[f.I[1]][f.I[2]].erase(f.I[0]);
        faces[j--] = faces.back();
        faces.resize(faces.size() - 1);
      }
    }
    int nfaces = faces.size();
    for(int j = 0; j < nfaces; j++) {
      f = faces[j];
      for(int a = 0; a < 3; a++) for(int b = a + 1; b < 3; b++) {
        int c = 3 - a - b;
        if(E[f.I[a]][f.I[b]].size() == 2) continue;
        faces.pub(make_face(f.I[a], f.I[b], i, f.I[c]));
      }
    }
  }
  return faces;
}