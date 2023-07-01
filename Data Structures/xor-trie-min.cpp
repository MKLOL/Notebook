void update(int nod) {
  if (nxt[nod][0] && nxt[nod][1]) {
    if (cnt[nxt[nod][0]] >= 2 && cnt[nxt[nod][1]] >= 2) {
      best[nod] = min(best[nxt[nod][0]], best[nxt[nod][1]]);
    } else if(cnt[nxt[nod][0]] >= 2) {
      best[nod] = best[nxt[nod][0]];
    } else if (cnt[nxt[nod][1]] >= 2) {
      best[nod] = best[nxt[nod][1]];
    } else if (cnt[nxt[nod][0]] >= 1 && cnt[nxt[nod][1]] >= 1) {
      best[nod] = best[nxt[nod][0]] ^ best[nxt[nod][1]];
    } else {
      best[nod] = best[nxt[nod][0]];
      if (cnt[nxt[nod][1]]) best[nod] = best[nxt[nod][1]];
    }
  } else {
    if (nxt[nod][0]) best[nod] = best[nxt[nod][0]];
    else best[nod] = best[nxt[nod][1]];
  }
}

void add(int nod, int x, int b) {
  ++cnt[nod];
  if(b == -1) {
    if (cnt[nod] == 0 || cnt[nod] >= 2) best[nod] = 0;
    if (cnt[nod] == 1) best[nod] = x;
    return;
  }
  int nb = (x&(1 << b)) ? 1 : 0;
  if (nxt[nod][nb] == 0) nxt[nod][nb]= ++NRN;
  
  add(nxt[nod][nb], x, b-1);
  update(nod);
  
}

void rem(int nod, int x, int b) {
  --cnt[nod];
  if(b == -1) {
    if (cnt[nod] == 0 || cnt[nod] >= 2) best[nod] = 0;
    if (cnt[nod] == 1) best[nod] = x;
    return;
  }
  int nb = (x&(1 << b)) ? 1 : 0;
  
  rem(nxt[nod][nb], x, b-1);
  update(nod);
}