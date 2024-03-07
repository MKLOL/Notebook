// return the number of bits between 0 and x that are set to 1 at position b. 
ll calc(ll x, ll b) {
    ll cl = 1LL << (b + 1);
    ll cp = x / cl;
    ll ret = cp * (1LL << b);

    ll r = x % cl;
    if (r >= (1LL << b)) {
        ret += r - (1LL << b) + 1;
    }

    return ret;
}
