inline int64_t mul_mod(int64_t x, int64_t y, int64_t m) {
    int64_t q = int64_t(static_cast<long double>(x) * y / m);
    int64_t res = x * y - q * m; 
    return (res + m) % m;
}
template <const int64_t MOD = (int64_t)1e18>
int64_t power(int64_t a, int64_t b) {
    int64_t res = 1 % MOD;
    for (; b; b >>= 1) {
        if (b & 1) res = mul_mod(res, a, MOD);
        a = mul_mod(a, a, MOD);
    }
    return res;
}