const int SZ = 1e6 + 5;
int is_prime[SZ];
void sieve() {
    int maxN = 1e6;
    is_prime[0] = is_prime[1] = 1;
    // is_prime[x] == 0 means prime number
    for(int i = 2; i * i <= maxN; i++) {
        if(is_prime[i] == 0) {
            for(int j = i * i; j <= maxN; j += i) {
                is_prime[j] = 1;
            }
        }
    } 
}