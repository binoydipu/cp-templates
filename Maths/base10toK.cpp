vector<int> base10tok(int n, int k) {
    vector<int> ans;
    while(n > 0) {
        ans.push_back(n % k);
        n /= k;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}