// returns gcd(a,b) and modifies (x,y) to solve-> ax + by = gcd⁡(a,b)
ll extended_euclid(ll a, ll b, ll &x, ll &y) {
    if(b == 0) { 
        x = 1, y = 0;
        return a;
    }
    ll x1, y1;
    ll d = extended_euclid(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
// finds x such that x % m1 = a1, x % m2 = a2. m1 and m2 may not be coprime
// here, x is unique modulo m = lcm(m1, m2). returns (x, m). on failure, m = -1.
pair<ll, ll> CRT(ll a1, ll m1, ll a2, ll m2) {
    ll p, q; // m1.p + m2.q = 1;
    ll g = extended_euclid(m1, m2, p, q);
    if(a1 % g != a2 % g) return make_pair(0, -1); // there is no x that can satisfy both congruences.
    ll m = m1 / g * m2;
    p = (p % m + m) % m;
    q = (q % m + m) % m;
    return make_pair((a1 * (m2 / g) % m * q % m + a2 * (m1 / g) % m * p % m) % m, m);
}