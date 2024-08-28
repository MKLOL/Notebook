ll gcd(ll a, ll b, ll &x, ll &y) {
  if(!b) {
    x=1; y=0;
    return a;
  } 
  else {
    ll x0, y0, d = gcd(b, a%b, x0, y0);
    x = y0; y = x0 - a/b *y0;
    return d;
  }
}

// Returns {{x, per1}, {y, per2}} so that ax - by = c
// x + per1 * T, y + per2 * T also solutions for any T
// Picks smallest pair so that both >= 0
pair<pll, pll> euclid(ll a, ll b, ll c) {
  ll x, y;
  ll d = gcd(abs(a), abs(b), x, y);
  if(a < 0) x = -x;
  if(b < 0) y = -y;

  // no sol, the periods should be positive, so 0 is invalid
  if(c%d) return {{0LL,0LL}, {0LL,0LL}};
 
  ll sol1 = (c/d) * x;
  ll sol2 = -(c/d) * y;

  // sol1 + per1 * T, sol2 + per2 * T also solutions
  ll per1 = abs(b)/d;
  ll per2 = abs(a)/d;

  // make them positive
  if(sol1 < 0) {
    ll ceil = (-sol1 + per1 - 1) / per1;
    sol1 += per1 * ceil;
    sol2 += per2 * ceil;
  }
  if(sol2 < 0) {
    ll ceil = (-sol2 + per2 - 1) / per2;
    sol1 += per1 * ceil;
    sol2 += per2 * ceil;
  }

  // minimize without making them negative
  ll steps = min(sol1 / per1, sol2 / per2);
  sol1 -= steps * per1;
  sol2 -= steps * per2;

  return {{sol1, per1}, {sol2, per2}};
}
