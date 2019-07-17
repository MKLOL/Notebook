// maximize cx, Ax <= b and x >= 0, A = Mxy, b size M, c size y
typedef long double DOUBLE;
typedef vector<DOUBLE> VD;
typedef vector<VD> VVD;
typedef vector<int> VI;
DOUBLE inf = -numeric_limits<DOUBLE>::infinity();
const DOUBLE EPS = 1e-9;

struct LPSolver {
  int m, n;
  VI B, y; //slack variables, actual variables
  VVD D; //canonical form
  LPSolver(const VVD &A, const VD &b, const VD &c) {
    m = b.size(); n = c.size(); y = VI(n+1);
    B = VI(m); D = VVD(m+2,VD(n+2));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) D[i][j] = A[i][j];
    }
    for (int i = 0; i < m; i++) { 
      B[i] = n + i; D[i][n] = -1; D[i][n + 1] = b[i]; 
    }
    for (int j = 0; j < n; j++) { 
      y[j] = j; D[m][j] = -c[j]; 
    }
    y[n] = -1; D[m + 1][n] = 1;
  }
  void Pivot(int r, int s) {
    double inv = 1.0 / D[r][s];
    for (int i = 0; i < m + 2; i++) {
      if (i == r) continue;
      for (int j = 0; j < n + 2; j++) {
        if (j == s) continue;
        D[i][j] -= D[r][j] * D[i][s] * inv;
      }
    }
    for (int j = 0; j < n + 2; j++) {
      if (j != s) D[r][j] *= inv;
    }
    for (int i = 0; i < m + 2; i++) {
      if (i != r) D[i][s] *= -inv;
    }
    D[r][s] = inv; swap(B[r], y[s]);
  }
  bool Simplex(int phase) {
    int x = phase == 1 ? m + 1 : m;
    while (true) {
      int s = -1;
      for (int j = 0; j <= n; j++) {
        if (phase == 2 && y[j] == -1) continue;
        if (s == -1 || D[x][j] < D[x][s] || D[x][j] == D[x][s] && y[j] < y[s]) s = j;
      }
      if (D[x][s] > -EPS) return true;
      int r = -1;
      for (int i = 0; i < m; i++) {
        if (D[i][s] < EPS) continue;
        if (r == -1 || D[i][n + 1] / D[i][s] < D[r][n + 1] / D[r][s] ||
          (D[i][n + 1] / D[i][s]) == (D[r][n + 1] / D[r][s]) && B[i] < B[r]) r = i;
      }
      if (r == -1) return false;
      Pivot(r, s);
    }
  }
  DOUBLE Solve(VD &x) {
    int r = 0;
    for (int i = 1; i < m; i++) {
      if (D[i][n + 1] < D[r][n + 1]) r = i;
    }
    if (D[r][n + 1] < -EPS) {
      Pivot(r, n); 
      if (!Simplex(1) || D[m + 1][n + 1] < -EPS) return inf;
      for (int i = 0; i < m; i++) if (B[i] == -1) {
        int s = -1;
        for (int j = 0; j <= n; j++) {
          if (s == -1 || D[i][j] < D[i][s] || D[i][j] == D[i][s] && y[j] < y[s]) {
            s = j;
          }
        }
        Pivot(i, s);
      }
    }
    if (!Simplex(2)) return inf;
    x = VD(n);
    for (int i = 0; i < m; i++) if (B[i] < n) x[B[i]] = D[i][n + 1];
    return D[m][n + 1];
  }
};