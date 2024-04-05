class SegmentTree {
public:
    vector<ll> t, vals;
    int N;
private:
    void privateUpdate(int nod, int st, int dr, int poz, ll val) {
        if(st == dr) {
            t[nod] = st;
            vals[st] = val;
            return;
        }
        int mij = (st + dr) / 2;
        if(poz <= mij) {
            privateUpdate(2 * nod, st, mij, poz, val);
        } else {
            privateUpdate(2 * nod + 1, mij + 1, dr, poz, val);
        }
        t[nod] = (vals[t[nod * 2]] > vals[t[nod * 2 + 1]]) ? t[nod * 2] : t[nod * 2 + 1];
    }
 
    ll privateGetMax(int nod, int st, int dr, int l, int r) {
        if(l <= st && dr <= r) {
            return t[nod];
        }
        int mij = (st + dr) / 2;
        int ret1 = -1, ret2 = -1;
        if(r > mij) ret1 = privateGetMax(nod * 2 + 1, mij + 1, dr, l, r);
        if(l <= mij) ret2 = privateGetMax(nod * 2, st, mij, l, r);
 
        if(ret1 == -1) return ret2;
        if(ret2 == -1) return ret1;
        return (vals[ret1] > vals[ret2]) ? ret1 : ret2;
    }
 
public:
    SegmentTree(int size) : N(size) {
        t.assign(4 * N, 0);
        vals.assign(4 * N, -1000000000LL*1000000);
    }
 
    void update(int poz, ll val) {
        privateUpdate(1, 0, N - 1, poz, val);
    }
 
    ll getMaxVal(int l, int r) {
        return vals[privateGetMax(1, 0, N - 1, l, r)];
    }
    ll getMaxPos(int l, int r) {
        return privateGetMax(1, 0, N - 1, l, r);
    }
 
    int size() {
      return N;
    }
};
