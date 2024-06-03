int nxt[2010100][26];
pii vx[2010100];
int NRQ=0;
void add(int nod, string &s, int pos, int val, int ind) {
    if (vx[nod] > mp(val, ind) || vx[nod] == mp(0,0)) {
        vx[nod] = {val, ind};
    }
    if (sz(s) == pos) {
        return;
    }
    int p = s[pos]-'a';
    if (nxt[nod][p] == 0) {
        nxt[nod][p] = ++NRQ;
    }
    add(nxt[nod][p],s,pos+1, val, ind);
}

int find(int nod, string &s, int pos) {
    if (sz(s) == pos) {
        return vx[nod].sc;
    }
    int p = s[pos]-'a';
    if (nxt[nod][p] == 0) {
        return vx[nod].sc;
    }
    return find(nxt[nod][p], s, pos+1);
}
