// F is some concave function
double ternarySearch(double left, double right) {//finds max
  while(abs(right - left) > EPS) {
    long double lt = left + (right - left) / 3.0;
    long double rt = right - (right - left) / 3.0;
    if (F(lt) < F(rt)) left = lt;
    else right = rt; //reverse if convex and min
  }
  return (left + right) / 2.0;
}