const int N = 5e5 + 5;

class Combinatorics {
  private:
    int n;
    vector<Mint> facts;
    vector<Mint> invs;
    vector<Mint> finvs;

  public:
    Combinatorics(int _n) : n(_n), facts(_n), invs(_n), finvs(_n) {
        facts[0] = finvs[0] = 1;
        invs[1] = 1;
        for (int i = 2; i < n; i++) invs[i] =  invs[mod % i] * (-mod / i);
        for (int i = 1; i < n; i++) { 
            facts[i] = facts[i - 1] * i;
            finvs[i] = finvs[i - 1] * invs[i];
        }
    }

    inline Mint fact(int n) { return facts[n]; }
    inline Mint inv_fact(int n) { return finvs[n]; }
    inline Mint inv(int n) { return invs[n]; }

    inline Mint ncr(int n, int r) {
        return r < 0 || n < r ? Mint(0) : facts[n] * finvs[n - r] * finvs[r];
    }
    inline Mint npr(int n, int r) {
        return r < 0 || n < r ? Mint(0) : facts[n] * finvs[n - r];
    }
} C(N);

// nCr % mod; where mod is prime; O(logn)
// use for big n/r values
Mint ncr_lucas(long long n, long long r) {
    if(r > n) return 0;
    if(n < mod) return C.ncr(n, r);
    return ncr_lucas(n / mod, r / mod) * ncr_lucas(n % mod, r % mod);
}