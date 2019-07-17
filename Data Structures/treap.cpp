typedef struct item * pitem;
struct item {
  int cnt, value, prior, key; bool rev; pitem l, r;
  item(int prior, int value) : cnt(1), rev(false), prior(prior), value(value), l(NULL), r(NULL) {}
};
int cnt(pitem t) { return t ? t->cnt : 0; }
void upd_cnt(pitem it) { if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1; }
void push(pitem it) {
  if (it && it->rev) {
    it->rev = false; swap(it->l, it->r);
    if (it->l) it->l->rev ^= true;
    if (it->r) it->r->rev ^= true;
  }
}
void merge(pitem &t, pitem l, pitem r) {
  push(l); push(r); if (!l || !r) t = l ? l : r;
  else if (l->prior > r->prior) merge(l->r, l->r, r), t = l;
  else merge(r->l, l, r->l), t = r; upd_cnt(t);
}
void split(pitem t, pitem & l, pitem & r, int key, int add = 0) {
  if (!t) return void (l = r = 0);
  push (t); int cur_key = cnt(t->l) + add;
  if (key <= cur_key) split(t->l, l, t->l, key, add), r = t;
  else split(t->r, t->r, r, key, add + cnt(t->l) + 1), l = t;
  upd_cnt(t);
}
void split (pitem t, int key, pitem & l, pitem & r) {
  push(t); if (!t) l = r = NULL; 
  else if (key < t->key) split (t->l, key, l, t->l),  r = t;
  else split (t->r, key, t->r, r),  l = t; upd_cnt(t);
}
void reverse(pitem t, int l, int r) {
  if(l > r) return; pitem t1, t2, t3;
  split(t, t1, t2, l); split(t2, t2, t3, r-l+1);
  t2->rev ^= true; merge(t, t1, t2); merge(t, t, t3);
}
void output (pitem t) {
  if (!t)  return; push (t); output (t->l);
  printf ("%d", t->value); output (t->r);
}
void erase (pitem & t, int key) {
  push(t); if (t->key == key) merge (t, t->l, t->r);
  else erase (key < t->key ? t->l : t->r, key); upd_cnt(t);
}
void insert (pitem & t, pitem it) {
  push(t); if (!t) { t = it; return;};
  if (it->prior > t->prior) split (t, it->key, it->l, it->r),  t = it;
  else insert (it->key < t->key ? t->l : t->r, it);
}
pitem cur =  new item(rand(), s[i] - 'a'); if (root) merge(root, root, cur);
else root = cur; reverse(root, x,y); 
