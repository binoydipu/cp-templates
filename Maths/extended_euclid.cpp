// we can use pow(a, m-2) if m is prime; else use this
int _gcd(int a, int b, int &x, int &y) {
    if(b == 0) { 
        x = 1, y = 0;
        return a;
    }
    int x1, y1;
    int d = _gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}
int inverse(int a, int m) { // a^-1 % m
    int x, y;
    int g = _gcd(a, m, x, y); // must be coprime, to get x as inverse of a
    if(g != 1) return -1;
    return (x % m + m) % m;
}