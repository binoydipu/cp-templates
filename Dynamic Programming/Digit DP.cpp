int num_size, itr;
vector<int> num;
ll dp[20][10][2][2], vis[20][10][2][2];

ll fun(int i, int pre, bool tight, bool started) {
    if(i == num_size) return 1;

    ll &ret = dp[i][pre][tight][started];
    if(vis[i][pre][tight][started] == itr) return ret;

    vis[i][pre][tight][started] = itr;
    int lb = 0;
    int ub = tight ? num[i] : 9;
    ret = 0;
    
    if(started) {
        for (int d = lb; d <= ub; d++) if(d != pre) {
            ret += fun(i + 1, d, tight & (d == ub), 1);
        }
    } else {
        for (int d = lb; d <= ub; d++) {
            ret += fun(i + 1, d, tight & (d == ub), d != 0);
        }
    }
    return ret;
}

// Finds answer in range [l, r]
ll digit_dp(ll l, ll r) {
    auto get_digits = [&](int val) -> vector<int> {
        if(val == 0) return {0};
        vector<int> ans;
        while(val) {
            int cur = val % 10;
            ans.push_back(cur);
            val /= 10;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    };

    itr++;
    num = get_digits(r);
    num_size = num.size();
    ll R = fun(0, 0, 1, 0);

    itr++;
    num = get_digits(l - 1);
    num_size = num.size();
    ll L = fun(0, 0, 1, 0);

    return R - L;
}