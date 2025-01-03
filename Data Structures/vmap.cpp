template <typename Key, typename Value>
class vmap {
private:
  vector<pair<Key, Value>> data;
  Value defaultValue;
  bool sorted;
 
  void ensureSorted() {
    if (!sorted) {
      sort(data.begin(), data.end(), [](const pair<Key, Value>& a, const pair<Key, Value>& b) {
        return a.first < b.first;
      });
      sorted = true;
    }
  }
 
public:
  vmap(const Value& defaultValue = Value{}) : defaultValue(defaultValue), sorted(false) {}
 
  void add(const Key& key, const Value& value = Value{}) {
    data.emplace_back(key, value);
    sorted = false;
  }
 
  Value& operator[](const Key& key) {
    ensureSorted();
    auto it = lower_bound(data.begin(), data.end(), key, [](const pair<Key, Value>& a, const Key& b) {
      return a.first < b;
    });
    if (it != data.end() && it->first == key) {
      return it->second;
    }
    return defaultValue;
  }
 
  typename vector<pair<Key, Value>>::iterator find(const Key& key) {
    ensureSorted();
    auto it = lower_bound(data.begin(), data.end(), key, [](const pair<Key, Value>& a, const Key& b) {
      return a.first < b;
    });
    if (it != data.end() && it->first == key) {
      return it;
    }
    return data.end();
  }
 
  class Iterator {
  private:
    typename vector<pair<Key, Value>>::iterator it;
 
  public:
    explicit Iterator(typename vector<pair<Key, Value>>::iterator itr) : it(itr) {}
 
    pair<Key, Value>& operator*() {
      return *it;
    }
 
    pair<Key, Value>* operator->() {
      return &(*it);
    }
 
    Iterator& operator++() {
      ++it;
      return *this;
    }
 
    Iterator operator++(int) {
      Iterator temp = *this;
      ++it;
      return temp;
    }
 
    bool operator==(const Iterator& other) const {
      return it == other.it;
    }
 
    bool operator!=(const Iterator& other) const {
      return it != other.it;
    }
  };
 
  Iterator begin() {
    ensureSorted();
    return Iterator(data.begin());
  }
 
  Iterator end() {
    ensureSorted();
    return Iterator(data.end());
  }
 
  void print() const {
    for (const auto& entry : data) {
      cout << entry.first << ": " << entry.second << endl;
    }
  }
};
