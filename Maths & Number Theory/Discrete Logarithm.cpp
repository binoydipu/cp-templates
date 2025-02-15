#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// baby step - giant step algo; a and m are co-prime
// returns minimum integer x such that a^x = b (mod m)
int discrete_log(int a, int b, int m) { // O(√m)
    a %= m, b %= m;
    int n = (int) sqrt(m + .0) + 1;
    int an = 1; // x = np - q; a^np = b × a^q (mod m);
    for (int i = 0; i < n; i++) an = 1LL * an * a % m;
    gp_hash_table<int, int> vals;
    for (int q = 0, cur = b; q <= n; q++) {
        vals[cur] = q;
        cur = 1LL * cur * a % m;
    }
    for (int p = 1, cur = 1; p <= n; p++) {
        cur = 1LL * cur * an % m; // (a^n)^p
        if(vals.find(cur) != vals.end()) {
            return n * p - vals[cur];
        }
    }
    return -1; // does not exist
}