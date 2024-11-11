class Aho {
public:
  static const int sigma = 26; // alphabet size 
  static const int off = 'a'; // first letter
  int nodes; // nodes
  int NR = 0; // terminal nodes

  vi tr; //
  vi term; //
  vi link; // fail edge
  vvi to; // edges
  // ADD MORE CUSTOM THINGS MAYBE (e.g. node->index, index->node, counters)

  void _new_node_update() {
    tr.pb(0);
    term.pb(0);
    link.pb(0);
    to.pb(vi(sigma, 0));
    // ADD MORE CUSTOM THINGS MAYBE
  }
 
  Aho() {
    nodes = 1;
    _new_node_update();
  }
 
  void add(string &s, int val) {
    int cur = 0; // root
    for(auto c: s) {
      if(!to[cur][c - off]) {
        to[cur][c - off] = nodes++;
        _new_node_update();
      }
      cur = to[cur][c - off];
    }
    term[cur] = cur;
    tr[cur] = ++NR;
    // ADD MORE CUSTOM THINGS MAYBE

  }
   
  void push_links() {
    queue<int> Q;
    Q.push(0);
    while(!Q.empty()) {
      int V = Q.front();
      Q.pop();
      int U = link[V];
      if(!term[V]) term[V] = term[U];
      FOR(c, sigma) {
        if(to[V][c]) {
          link[to[V][c]] = V ? to[U][c] : 0;
          Q.push(to[V][c]);
        } else {
          to[V][c] = to[U][c];
        }
      }
    }
  }

  void process_match(int node, int poz) {
    // ADD CUSTOM LOGIC
  }
 
  void match(string &s) {
    int cur = 0;
    FOR(i, sz(s)) {
      char c = s[i];
      cur = to[cur][c-off];
      int f = cur;
      while(f) {
        if(tr[f]) {
          process_match(f, i);
        }
        if(f == term[f]) f = term[link[f]];
        else f = term[f];
      }
    }
  }
};