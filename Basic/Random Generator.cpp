mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int get_rand(int l, int r) {
    uniform_int_distribution<int> uid(l, r);
    return uid(rng);
}
vector<int> get_rand_list(int n, int l, int r) {
    vector<int> nums;
    for (int i = 0; i < n; i++) {
        nums.push_back(get_rand(l, r));
    }
    return nums;
}