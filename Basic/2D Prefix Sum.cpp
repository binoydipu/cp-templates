template <typename T>
vector<vector<T>> build_prefix_sum(const vector<vector<T>> &a) {
    int n = a.size(), m = a[1].size(); // both 1-indexed
    vector<vector<T>> ps(n, vector<T>(m, 0));
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            ps[i][j] = ps[i - 1][j] - ps[i - 1][j - 1] + ps[i][j - 1] + a[i][j];
        }
    }
    return ps;
}

// from top-left(x1, y1) to bottom-right (x2, y2);
template <typename T>
T find_sum(const vector<vector<T>> &ps, int x1, int y1, int x2, int y2) {
    return ps[x2][y2] - ps[x2][y1 - 1] - ps[x1 - 1][y2] + ps[x1 - 1][y1 - 1];
}