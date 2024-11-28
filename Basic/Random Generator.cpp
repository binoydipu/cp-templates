mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
int getRand(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
vector<int> generateRandomNumbers(int n, int l, int r) {
    std::vector<int> randomNumbers;
    for (int i = 0; i < n; ++i) {
        randomNumbers.push_back(getRand(l, r));
    }
    return randomNumbers;
}

cout<<fixed<<setprecision(10);
cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n"; 