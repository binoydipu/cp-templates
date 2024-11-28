int maxSubArraySum(vector<int> &a) {
    int left = 0, right = 0, j = 0, n = a.size();
    int maxSum = INT_MIN, cur = 0;
    for(int i = 0; i < n; i++) {
        cur += a[i];
        if(maxSum < cur) {
            maxSum = cur;
            left = j;
            right = i;
        }
        if(cur < 0) {
            cur = 0;
            j = i + 1;
        }
    }
    // return {maxSum, {left, right}}; // {sum, {start index, end index}}
    return maxSum;
};