// Finds longest palindrome keeping i- as center,
// for even length-palindrome # in center, for odd- some char in center
struct Manacher {
    vector<int> p;
    // max length palindrome, and center of it
    int max_len, max_cen;

    Manacher(string _s) { // O(n)
        string s;
        for(auto c : _s) s += string("#") + c;
        s += "#";
        int n = s.length();
        p.assign(n, 1);
        int l = 1, r = 1; max_len = 0;
        for (int i = 1; i < n; i++) {
            p[i] = max(0LL, min(r - i, p[l + r - i]));
            while(i + p[i] < n && i - p[i] >= 0 && s[i + p[i]] == s[i - p[i]]) {
                p[i]++;
            }
            if(i + p[i] > r) {
                l = i - p[i];
                r = i + p[i];
            }
            if(max_len < p[i] - 1) { 
                max_len = p[i] - 1, max_cen = i / 2 - (max_len % 2 == 0); 
            }
        }
    }
    // 0 - indexed. odd starts at center, even starts after center at #
    int get_longest(int cen, bool odd) {
        int pos = 2 * cen + 1 + (!odd);
        return p[pos] - 1;
    }
    bool is_palindrome(int l, int r) { // 0 - indexed
        return (r - l + 1) <= get_longest((l + r) / 2, l % 2 == r % 2);
    }
    // Finds the left and right indices of a palindrome centered at cen
    pair<int, int> get_bounds(int cen, bool odd) {
        int pos = 2 * cen + 1 + (!odd), len = p[pos] - 1;
        int left = cen - len / 2 + (!odd), right = cen + len / 2;
        return {left, right};
    }
};