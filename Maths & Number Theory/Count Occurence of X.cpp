// cnt of x in n!
int find_x_count_fact(int n, int x) {
    if (n < 0) return 0;
    int count = 0;
    for (int i = x; n / i >= 1; i *= x) {
        count += n / i;
    }
    return count;
}
// cnt of x in n
int find_x_count(int n, int x) {
    if (n < 0) return 0;
    int count = 0;
    while(n % x == 0) {
        count++;
        n /= x;
    }
    return count;
}