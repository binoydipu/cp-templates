// Euler's totient function, also known as phi-function Φ(n) , 
// counts the number of integers between 1 and n inclusive, which are coprime to n.
void phi_1_to_n(int n) { // O(loglogn)
    vector<int> phi(n + 1);
    for (int i = 0; i <= n; i++) phi[i] = i;

    for (int i = 2; i <= n; i++) {
        if (phi[i] == i) {
            for (int j = i; j <= n; j += i)
                phi[j] -= phi[j] / i;
        }
    }
}

// for 1 number only
int phi(int n) { // O(sqrt(n))
    int ans = n;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            while (n % p == 0) { n /= p; }
            ans -= ans / p;
        }
    }
    if (n > 1) { ans -= ans / n; }
    return ans;
}