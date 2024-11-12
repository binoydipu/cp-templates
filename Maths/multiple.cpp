long long multiply(long long A, long long B) { // (A * B) % mod
    long long ans = 0;
    while(B) {
        if(B & 1) ans = (ans + A) % mod;
        A = (A + A) % mod;
        B >>= 1;
    }
    return ans;
}
