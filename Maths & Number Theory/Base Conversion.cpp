vector<int> base_10_to_k(int n, int k) {
    vector<int> ans;
    while(n > 0) {
        ans.push_back(n % k);
        n /= k;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

template <typename T>
int base_k_to_10(const T& digits, int k) {
    int ans = 0;
    for (auto d : digits) {
        ans = ans * k + d;
    }
    return ans;
}