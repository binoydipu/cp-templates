// For N numbers in nlogn
const int N = 1e7 + 9;

int spf[N];
void sieve() {
    for (int i = 2; i < N; i++) spf[i] = i;
    for (int i = 2; i * i < N; i++) {
        if (spf[i] == i) { // prime
            for (int j = i * i; j < N; j += i) {
                spf[j] = min(spf[j], i);
            }
        }
    }
}
vector<int> primeFactors(int n) {
    vector<int> pfs;
    while(n != 1) {
        pfs.push_back(spf[n]);
        n = n / spf[n];
    }
    return pfs;
}

// For 1 number in sqrt(n)
vector<int> primeFactors(int n) {
    vector<int> pfs;
    while(n % 2 == 0) { 
        pfs.push_back(2);
        n = n / 2;
    }
    for (int i = 3; i * i <= n; i += 2) { 
        while (n % i == 0) {
            pfs.push_back(i);
            n = n / i;
        }
    }
    if(n > 2) pfs.push_back(n);
    return pfs;
}