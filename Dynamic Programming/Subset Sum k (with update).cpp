const int N = 5e3 + 5, mod = 998244353;

int waysToMake_K(vector<int> &dp, string op, int x, int k) {
    if(op == "+") { // ways to make k if x is included
        for (int i = N - 1; i >= x; i--) {
            dp[i] = dp[i] + dp[i - x];
            dp[i] = (dp[i] % mod + mod) % mod;
        }
    } else { // ways to make k if x is excluded
        for (int i = x; i < N; i++) { 
            dp[i] = dp[i] - dp[i - x];
            dp[i] = (dp[i] % mod + mod) % mod;
        }
    }
    return dp[k];
}
// initialize-> vector<int> dp(N, 0); dp[0] = 1;
