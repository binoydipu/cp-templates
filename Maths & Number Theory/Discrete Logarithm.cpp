#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

// baby step - giant step
// returns minimum integer x such that a^x = b (mod m)
// a and m are co-prime
ll discrete_log(ll a, ll b, ll m) {
    static const ll inf = 2e9;
    ll n = (ll) sqrt (m + .0) + 1;
    ll pw = 1;
    for (ll i = 0; i < n; ++i) pw = 1LL * pw * a % m;
    gp_hash_table<ll, ll> vals;
    for (ll p = 1, cur = pw; p <= n; ++p) {
        if (!vals[cur]) vals[cur] = p;
        cur = 1LL * cur * pw % m;
    }
    ll ans = inf;
    for (ll q = 0, cur = b; q <= n; ++q) {
        if (vals.find(cur) != vals.end()) {
            long long nw = 1LL * vals[cur] * n - q;
            if (nw < ans) ans = nw;
        }
        cur = (1LL * cur * a) % m;
    }
    if (ans == inf) ans = -1;
    return ans;
}
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1; y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
ll inverse(ll a, ll m) {
    ll x, y;
    ll g = extended_euclid(a, m, x, y);
    if (g != 1) return -1;
    return (x % m + m) % m;
}
// discrete log but a and m may not be co-prime
ll discrete_log_noncoprime(ll a, ll b, ll m) {
    if (a == 0 && b == 0) return 1;
    if (m == 1) return 0;
    if (b == 1) return 0;
    if (__gcd(a, m) == 1) return discrete_log(a, b, m);
    ll g = __gcd(a, m);
    if (b % g != 0)  return -1;
    ll p = inverse(a / g, m / g);
    ll nw = discrete_log_noncoprime(a, 1LL * b / g * p % (m / g), m / g);
    if (nw == -1) return -1;
    return nw + 1;
}