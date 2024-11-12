const int mod = 1e9 + 7, N = 2e5 + 5;

long long power(long long a, long long b) { // (a ^ b) % mod
    long long res = 1;
    while (b) {
        if (b & 1) res = (res * a) % mod;
        a = (a * a) % mod;
        b >>= 1;
    }
    return res;
}

struct BinomialCoefficient {
    int fact[N], invFact[N];

    BinomialCoefficient() {
        fact[0] = invFact[0] = 1;
        for (int i = 1; i < N; i++) { 
            fact[i] = 1LL * fact[i - 1] * i % mod;
        }
        invFact[N - 1] = power(fact[N - 1], mod - 2);
        for (int i = N - 2; i >= 1; i--) {
            invFact[i] = 1LL * invFact[i + 1] * (i + 1) % mod;
        }
    }
    int nCr(int n, int r) {
        if(n < r) return 0;
        return fact[n] * invFact[n - r] % mod * invFact[r] % mod;
    }
    int nPr(int n, int r) {
        if(n < r) return 0;
        return fact[n] * invFact[n - r] % mod;
    }
}bc;