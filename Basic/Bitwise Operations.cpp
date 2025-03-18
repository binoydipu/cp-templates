namespace bw {
    bool is_set(int mask, int bit) { return (mask & (1LL << bit)) != 0; }
    bool is_power_of_two(int mask) { return mask && !(mask & (mask - 1)); }
    int set_bit(int mask, int bit) { return (mask | (1LL << bit)); }
    int unset_bit(int mask, int bit) { return (mask & ~(1LL << bit)); }
    int toggle_bit(int mask, int bit) { return (mask ^ (1LL << bit)); }
    int get_bit(int mask, int bit) { return (mask >> bit) & 1; }
    int bit_count(int mask) { return __builtin_popcount(mask); }
    int bit_countll(int mask) { return __builtin_popcountll(mask); }
    int lsb(int mask) { return __builtin_ctzll(mask); }
    int msb(int mask) { return (63 - __builtin_clzll(mask)); }
    int lowest_set_bit(int mask) { return mask & -mask; }
    int clear_lowest_set_bit(int mask) { return mask & (mask - 1); }
    int bit_difference(int a, int b) { return __builtin_popcount(a ^ b); }
    long long bitwise_pairing(int x, int y) { return (1LL * x << 32) | (1LL * y); }
    pair<int, int> bitwise_unpairing(long long z) { int x = z >> 32; int y = z & 0xFFFFFFFF; return {x, y}; }
}
using namespace bw;