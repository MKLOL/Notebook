vi make(const string& s) {
    int N = s.size();
    vi z(N, 0); // Initialize z vector with N elements, all set to 0
    int left = 0, right = 0;
    for(int i = 1; i < N; ++i) {
        if(i > right) {
            left = i, right = i;
            while (right < N && s[right - left] == s[right]) ++right;
            z[i] = right - left; --right;
        } else {
            int k = i - left;
            if(z[k] < right - i + 1) z[i] = z[k];
            else {
                left = i;
                while (right < N && s[right - left] == s[right]) ++right;
                z[i] = right - left; --right;
            }
        }
    }
    return z;
}
