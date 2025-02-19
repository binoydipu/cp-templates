const int N = 1e6 + 5;

int B, a[N];
int block[N]; // sum

void build(int n) { // 0-indexed
    B = sqrt(n); // block size
    int total_blocks = (n + B - 1) / B;

    for (int b_id = 0; b_id < total_blocks; b_id++) {
        int l = b_id * B;
        int r = min(n, (b_id + 1) * B);
        for (int i = l; i < r; i++) {
            block[b_id] += a[i];
        }
    }
}

void add(int i, int val) {
    int b_id = i / B;
    a[i] += val;
    block[b_id] += val;
}

int get(int l, int r) { // 0-indexed, O(√n)
    int bl = l / B, br = r / B, ans = 0;

    if(bl == br) {
        for (int i = l; i <= r; i++) {
            ans += a[i];
        }
    } else {
        for (int i = l; i < (bl + 1) * B; i++) {
            ans += a[i];
        }
        for (int i = br * B; i <= r; i++) {
            ans += a[i];
        }
        for (int b_id = bl + 1; b_id < br; b_id++) {
            ans += block[b_id];
        }
    }
    return ans;
}
