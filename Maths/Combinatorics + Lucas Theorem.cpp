const int N = 1e6 + 3, mod = 1e6 + 3;

template <const int32_t MOD>
struct modint {
  int32_t value;
  modint() = default;
  modint(int32_t value_) : value(value_) {}
  inline modint<MOD> operator + (modint<MOD> other) const { int32_t c = this->value + other.value; return modint<MOD>(c >= MOD ? c - MOD : c); }
  inline modint<MOD> operator - (modint<MOD> other) const { int32_t c = this->value - other.value; return modint<MOD>(c <    0 ? c + MOD : c); }
  inline modint<MOD> operator * (modint<MOD> other) const { int32_t c = (int64_t)this->value * other.value % MOD; return modint<MOD>(c < 0 ? c + MOD : c); }
  inline modint<MOD> & operator += (modint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
  inline modint<MOD> & operator -= (modint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
  inline modint<MOD> & operator *= (modint<MOD> other) { this->value = (int64_t)this->value * other.value % MOD; if (this->value < 0) this->value += MOD; return *this; }
  inline modint<MOD> operator - () const { return modint<MOD>(this->value ? MOD - this->value : 0); }
  modint<MOD> pow(uint64_t k) const { modint<MOD> x = *this, y = 1; for (; k; k >>= 1) { if (k & 1) y *= x; x *= x; } return y; }
  modint<MOD> inv() const { return pow(MOD - 2); }  // MOD must be a prime
  inline modint<MOD> operator /  (modint<MOD> other) const { return *this *  other.inv(); }
  inline modint<MOD> operator /= (modint<MOD> other)       { return *this *= other.inv(); }
  inline bool operator == (modint<MOD> other) const { return value == other.value; }
  inline bool operator != (modint<MOD> other) const { return value != other.value; }
  inline bool operator < (modint<MOD> other) const { return value < other.value; }
  inline bool operator > (modint<MOD> other) const { return value > other.value; }
};
template <int32_t MOD> modint<MOD> operator * (int32_t value, modint<MOD> n) { return modint<MOD>(value) * n; }
template <int32_t MOD> modint<MOD> operator * (int64_t value, modint<MOD> n) { return modint<MOD>(value % MOD) * n; }
template <int32_t MOD> istream & operator >> (istream & in, modint<MOD> &n) { return in >> n.value; }
template <int32_t MOD> ostream & operator << (ostream & out, modint<MOD> n) { return out << n.value; }

using Mint = modint<mod>;

struct Combinatorics {
    int n; vector<Mint> fact, inv, invFact;
    Combinatorics(int _n) : n(_n), fact(_n), inv(_n), invFact(_n) {
        fact[0] = invFact[0] = 1;
        inv[1] = 1;
        for (int i = 2; i < n; i++) inv[i] =  inv[mod % i] * (-mod / i);
        for (int i = 1; i < n; i++) { 
            fact[i] = fact[i - 1] * i;
            invFact[i] = invFact[i - 1] * inv[i];
        }
    }
    inline Mint ncr(int n, int r) {
        return r < 0 || n < r ? 0 : fact[n] * invFact[n - r] * invFact[r];
    }
    inline Mint npr(int n, int r) {
        return r < 0 || n < r ? 0 : fact[n] * invFact[n - r];
    }
} C(N);

// nCr % mod; where mod is prime; O(logn)
Mint ncr_lucas(long long n, long long r) {
    if(r > n) return 0;
    if(n < mod) return C.ncr(n, r);
    return ncr_lucas(n / mod, r / mod) * ncr_lucas(n % mod, r % mod);
}