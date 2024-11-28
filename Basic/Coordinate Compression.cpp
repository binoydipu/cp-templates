template <typename T> vector<T> Compression (vector<T>& a) {
    int n = a.size();
    vector<T> d = a;
    sort(d.begin(), d.end());
    d.resize(unique(d.begin(), d.end()) - d.begin());
    for (int i = 0; i < n; i++) {
        a[i] = lower_bound(d.begin(), d.end(), a[i]) - d.begin() + 1;
    }
    return d; // Original value of a[i] is d[a[i]] 
}