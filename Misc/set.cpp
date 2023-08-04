// Function to return an iterator to the exact element
set<int>::iterator findExact(set<int>& s, int element) {
    return s.find(element);
}

// Function to return an iterator to the smallest element larger than the input element
set<int>::iterator findNextLarger(set<int>& s, int element) {
    return s.upper_bound(element);
}

// Function to return an iterator to the largest element smaller than the input element
set<int>::iterator findNextSmaller(set<int>& s, int element) {
    auto it = s.lower_bound(element);
    return (it != s.begin()) ? prev(it) : s.end();
}