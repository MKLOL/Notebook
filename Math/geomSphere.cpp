#define PI 3.14159265358979
double R = 6370.0; //earth
double rad(double x) { return x * PI / 180.0;}
double ang(double x) { return x * 180.0 / PI;}
double dist(pdd a, pdd b) {
  if(a == b) return 0;
  double v = sin(a.fs)*sin(b.fs) + cos(a.fs) * cos(b.fs) * cos(a.sc - b.sc);
  return acos(v);
}
struct cel {
  double x,y,z;
  cel(double lat, double lon) {
    x = cos(lat) * cos(lon); y = cos(lat) * sin(lon); z = sin(lat);
  }
  cel(double a1, double a2, double a3) { x = a1, y = a2, z = a3; }
  inline cel operator^(cel c1) { //cross
    return cel(y*c1.z - c1.y * z, c1.x * z - c1.z * x, c1.y * x - c1.x * y);
  }
  inline cel operator*(double cx) { return cel(cx*x,cx*y,cx*z); }
  double mag() { return sqrt(x*x + y*y + z*z); }
  pdd rev() {
    double lat = asin(z); double tmp = cos(lat);
    double sgn = asin(y/tmp); double lon = acos(x / tmp);
    if(sgn < 0) lon = 2 * PI - lon; return mp(lat,lon);
  }
}; 
int inside(pdd a, pdd b, pdd c) {
  return abs(dist(a,b) + dist(a,c) - dist(b,c)) <= 0.000001;
}
pdd inter(pdd a, pdd b, pdd c, pdd d) {
  cel p1(a.fs,a.sc); cel p2(b.fs,b.sc);
  cel p3(c.fs,c.sc); cel p4(d.fs,d.sc);
  cel v1 = p1 ^ p2; cel v2 = p3 ^ p4;
  v1 = v1 * (1.0 / v1.mag()); v2 = v2 * (1.0 / v2.mag());
  cel d1 = v1 ^ v2; d1 = d1 * (1.0 / d1.mag());
  cel d2 = d1 * (-1);
  pdd x1 = d1.rev(), x2 = d2.rev();
  if(inside(x1,a,b) && inside(x1,c,d)) return x1;
  if(inside(x2,a,b) && inside(x2,c,d)) return x2;
  return mp(inf,inf);
}