// For N numbers in nlogn
const int N = 2e5 + 9;

vector<int> divisors[N];
void sieve() { // O(nlogn)
    for (int i = 1; i < N; i++) {
        for (int j = i; j < N; j += i) {
            divisors[j].push_back(i);
        }
    }
}

// For 1 number in sqrt(n)
vector<int> divisors(int n) {
    vector<int> divs;
    for(int i = 1; i * i <= n; i++) {
        if(n % i == 0) {
            if(n / i == i) divs.push_back(i);
            else {
                divs.push_back(i);
                divs.push_back(n / i);
            }
        }
    }
    sort(divs.begin(), divs.end()); 
    return divs;
}