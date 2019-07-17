// number type for coordinates, and its maximum value
typedef long long ntype;
const ntype inf = numeric_limits<ntype>::max();
struct point {
  ntype x, y;
  point(ntype xx = 0, ntype yy = 0) : x(xx), y(yy) {}
};
bool operator==(const point &a, const point &b) {
  return a.x == b.x && a.y == b.y;
}
int cmpx(const point &a, const point &b) { return a.x < b.x; }
int cmpy(const point &a, const point &b) { return a.y < b.y; }
ntype dist(const point &a, const point &b) {
  ntype dx = a.x-b.x, dy = a.y-b.y;
  return dx*dx + dy*dy;
}
struct bbox { //bounding box
  ntype x0, x1, y0, y1;  
  bbox() : x0(inf), x1(-inf), y0(inf), y1(-inf) {}
  void compute(const vector<point> &v) {
    for (int i = 0; i < v.size(); ++i) {
      x0 = min(x0, v[i].x); x1 = max(x1, v[i].x);
      y0 = min(y0, v[i].y); y1 = max(y1, v[i].y);
    }
  }
  //distance between a point and this box, 0 if inside
  ntype distance(const point &p) {
    if (p.x < x0) {
      if (p.y < y0) return dist(point(x0, y0), p); 
      else if (p.y > y1) return dist(point(x0, y1), p);
      else return dist(point(x0, p.y), p);
    } else if (p.x > x1) {
      if (p.y < y0) return dist(point(x1, y0), p);
      else if (p.y > y1) return dist(point(x1, y1), p);
      else return dist(point(x1, p.y), p);
    } else {
      if (p.y < y0) return dist(point(p.x, y0), p);
      else if (p.y > y1) return dist(point(p.x, y1), p);
      else return 0;
    }
  }
};
struct kdnode {
  bool leaf; point pt; //if only has one point
  bbox bound;  
  kdnode *left, *right; // two children of this kd-node
  kdnode() : leaf(false), left(0), right(0) {}
  ~kdnode() { if (left) delete left; if (right) delete right; }
  ntype intersect(const point &p) { return bound.distance(p); }
  void construct(vector<point> &vp) {
    bound.compute(vp);
    if (vp.size() == 1) {
      leaf = true; pt = vp[0];
    } else { // split on largest coord
      if (bound.x1-bound.x0 >= bound.y1-bound.y0) {
        sort(vp.begin(), vp.end(), cmpx);
      } else {
        sort(vp.begin(), vp.end(), cmpy);
      }
      int half = vp.size()/2;
      vector<point> vl(vp.begin(), vp.begin()+half);
      vector<point> vr(vp.begin()+half, vp.end());
      left = new kdnode(); left->construct(vl);
      right = new kdnode(); right->construct(vr);            
    }
  }
};
struct kdtree {
  kdnode *root;
  kdtree(const vector<point> &vp) {
    vector<point> v(vp.begin(), vp.end());
    root = new kdnode(); root->construct(v);
  }
  ~kdtree() { delete root; } 
  ntype search(kdnode *node, const point &p) {// nearest neighbour
    if (node->leaf) {
      if (p == node->pt) return inf; // if not want dupl
      else return dist(p, node->pt);
    }
    ntype bleft = node->left->intersect(p);
    ntype bright = node->right->intersect(p);
    if (bleft < bright) {
      ntype best = search(node->left, p);
      if (bright < best) best = min(best, search(node->right, p));
      return best;
    } else {
      ntype best = search(node->right, p);
      if (bleft < best) best = min(best, search(node->left, p));
      return best;
    }
  }
  ntype nearest(const point &p) { return search(root, p); }
};