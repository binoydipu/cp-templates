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