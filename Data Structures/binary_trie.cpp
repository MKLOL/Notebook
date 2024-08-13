
class Trie {
private:
  static const int MAX_BIT = 30; // Maximum bits for 31-bit integers
  vector<pair<int, int>> nxt; // Next index for 0 and 1 bit as a pair
  vector<int> cnt; // Count of numbers passing through a node
  int node_count; // Number of nodes currently in the trie

public:
  Trie() : node_count(1) { // Starts with one node (root)
    nxt.push_back({0, 0});
    cnt.push_back(0);
  }

  void add(int x) {
    int nod = 0;
    for (int i = MAX_BIT; i >= 0; --i) {
      int bit = (x >> i) & 1;
      if (bit) {
        if (nxt[nod].second == 0) {
          nxt[nod].second = node_count++;
          nxt.push_back({0, 0});
          cnt.push_back(0);
        }
        nod = nxt[nod].second;
      } else {
        if (nxt[nod].first == 0) {
          nxt[nod].first = node_count++;
          nxt.push_back({0, 0});
          cnt.push_back(0);
        }
        nod = nxt[nod].first;
      }
      cnt[nod]++;
    }
  }

  void remove(int x) {
    int nod = 0;
    vector<int> path;
    for (int i = MAX_BIT; i >= 0; --i) {
      int bit = (x >> i) & 1;
      nod = bit ? nxt[nod].second : nxt[nod].first;
      path.push_back(nod);
    }
    for (int id : path) {
      cnt[id]--;
      assert(cnt[id] >= 0); // Ensure no negative counts
    }
  }

  int max_xor(int x) {
    int nod = 0, max_xor = 0;
    for (int i = MAX_BIT; i >= 0; --i) {
      int bit = (x >> i) & 1;
      int opposite_bit = bit ^ 1;
      int next_node = opposite_bit ? nxt[nod].second : nxt[nod].first;
      if (next_node != 0 && cnt[next_node] > 0) {
        max_xor |= (1 << i);
        nod = next_node;
      } else {
        nod = opposite_bit ? nxt[nod].first : nxt[nod].second;
      }
    }
    return max_xor;
  }

  int min_xor(int x) {
    int nod = 0, min_xor = 0;
    for (int i = MAX_BIT; i >= 0; --i) {
      int bit = (x >> i) & 1;
      int next_node = bit ? nxt[nod].second : nxt[nod].first;
      if (next_node != 0 && cnt[next_node] > 0) {
        nod = next_node;
      } else {
        min_xor |= (1 << i);
        nod = bit ? nxt[nod].first : nxt[nod].second;
      }
    }
    return min_xor;
  }
};
