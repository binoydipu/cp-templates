const int MAXN = 1e5 + 5;
int gn[MAXN]; // Grundy num

// Allowed moves (customize per problem)
inline vector<int> get_moves(int n) {
    vector<int> moves;
    for (int d : {1, 3, 4}) {
        if (n >= d) moves.push_back(n - d);
    }
    return moves;
}

// Use if upper limit is known
// int mex(const vector<int>& v) {
//     static bool vis[128];
//     for (int x : v) if (x < 128) vis[x] = true;
//     int m = 0; while (m < 128 && vis[m]) m++;
//     for (int x : v) if (x < 128) vis[x] = false;
//     return m;
// }

int mex(vector<int> v) {
    sort(v.begin(), v.end());
    int m = 0;
    for (int x : v) {
        if (x == m) m++;
        else if (x > m) break;
    }
    return m;
}

// Compute Grundy number with memoization
int grundy(int n) {
    if (~gn[n]) return gn[n];

    vector<int> reachable;
    for (int nxt : get_moves(n)) {
        reachable.push_back(grundy(nxt));
    }
    return gn[n] = mex(reachable);
}

// XOR of all Grundy numbers for multi-pile game
int compute_nim_sum(const vector<int>& piles) {
    int xorsum = 0;
    for (int pile : piles) xorsum ^= grundy(pile);
    return xorsum;
}

// memset(gn, -1, sizeof gn); gn[0] = 0;
// e.g. if from 5, can reach these 3 states: -> 4, 2, and 1
// gn[5] = MEX({ gn[4], gn[4], gn[1] })
// gn[n] = 0: losing state, gn[n] = +ve: winning state
