namespace kmp {
  template<typename T>
  vector<int> build_nx(const T &s1) {
    vector<int> nx(s1.size());
    int k = -1;
    nx[0] = -1;
    for (size_t i = 1; i < s1.size(); ++i) {
      while (k >= 0 && s1[k + 1] != s1[i]) k = nx[k];
      if (s1[k + 1] == s1[i]) ++k;
      nx[i] = k;
    }
    return nx;
  }

  template<typename T>
  vector<int> match(const T &s1, const T &s2) {
    vector<int> nx = build_nx(s1);
    vector<int> ret;
    int k = -1;
    for (size_t i = 0; i < s2.size(); ++i) {
      while (k >= 0 && s1[k + 1] != s2[i]) k = nx[k];
      if (s1[k + 1] == s2[i]) ++k;
      if (k == static_cast<int>(s1.size()) - 1) {
        ret.push_back(static_cast<int>(i - s1.size() + 1));
        k = nx[k];
      }
    }
    return ret;
  }
};
