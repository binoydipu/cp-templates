vector<int> digits(int n) {
    vector<int> ans;
    while(n) {
        int cur = n % 10;
        ans.push_back(cur);
        n /= 10;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}