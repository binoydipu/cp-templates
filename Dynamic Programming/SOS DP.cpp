const int LOG = 20, MAX = (1 << LOG), mod = 1e9 + 7;
// O(LOG x 2^LOG), dp stores frequency
// Frequency of submasks of 'mask' added to freq of 'mask'; 1->0,1 and 0->0
void addSubSets(vector<int> &dp) {
    for(int bit = 0; bit < LOG; bit++) {
        for(int mask = 0; mask < MAX; mask++) {
            if(mask & (1 << bit)) {
                dp[mask] += dp[mask ^ (1 << bit)];
            }
        }
    }
}
// Frequency of submasks of 'mask' removed from freq of 'mask'
void removeSubSets(vector<int> &dp) {
    for(int bit = 0; bit < LOG; bit++) {
        for(int mask = MAX - 1; mask >= 0; mask--) {
            if(mask & (1 << bit)) {
                dp[mask] -= dp[mask ^ (1 << bit)];
            }
        }
    }
}
// Frequency of 'mask' added to freq of submasks; 1->1 and 0->0,1
void addSuperSets(vector<int> &dp) {
    for(int bit = 0; bit < LOG; bit++) {
        for(int mask = MAX - 1; mask >= 0; mask--) {
            if(mask & (1 << bit)) {
                dp[mask ^ (1 << bit)] += dp[mask];
            }
        }
    }
}
// Frequency of 'mask' removed from freq of submasks
void removeSuperSets(vector<int> &dp) {
    for(int bit = 0; bit < LOG; bit++) {
        for(int mask = 0; mask < MAX; mask++) {
            if(mask & (1 << bit)) {
                dp[mask ^ (1 << bit)] -= dp[mask];
            }
        }
    }
}