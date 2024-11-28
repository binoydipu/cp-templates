const int N = 1e6 + 9;

vector<int> primes;
bool is_prime[N]; 
void sieve() {
    for (int i = 2; i < N; i++) {
        is_prime[i] = true;
    }
    for (int i = 2; i * i < N; i++) {
        if (is_prime[i]) {
            for (int j = i * i; j < N; j += i) {
                is_prime[j] = false;
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (is_prime[i]) primes.push_back(i);
    }
}

// sieve with Smallest Prime Factors
int spf[N];
void sieve() {
    for (int i = 2; i < N; i++) {
        spf[i] = i;
    }
    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) { // prime
            for (int j = i * i; j < N; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
    for (int i = 2; i < N; i++) {
        if (spf[i] == i) primes.push_back(i);
    }
}