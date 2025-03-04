// Finding minimal string right-rotation to make string minimal lexicographical
int min_rotation(string s) { // O(n)
    s += s;
    int p = 0, n = s.size();
    vector<int> f(n, -1);
    for (int l = 1, r = 1; r < n; r++) {
        for (l = f[r - p - 1]; l != -1 && s[p + l + 1] != s[r]; l = f[l]) {
            if (s[l + p + 1] > s[r]) p = r - l - 1;
        }
        if (l == -1 && s[p + l + 1] != s[r]) {
            if (s[p + l + 1] > s[r]) p = r;
            f[r - p] = -1;
        } else {
            f[r - p] = l + 1;
        }
    }
    return p; // p is the starting index of min lex string; 0-indexed
}