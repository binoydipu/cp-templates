/**
 *    author:   Binoy Barman
 *    created:  2025-03-04 18:26:57
**/

#include<bits/stdc++.h>
#ifdef LOCAL
#include "debug/debug.hpp"
#else
#define dbg(...) 42
#define print(...) 42
#endif
using namespace std;
using ll = long long;
const int mod = 1e9 + 7;
const int inf = 1e9;

#define int long long
#define nl '\n'
#define all(v) v.begin(), v.end()
#define Testcase_Handler int tts, tc = 1; cin >> tts; hell: while(tts--)
#define uniq(v) sort(all(v)), v.resize(distance(v.begin(), unique(v.begin(), v.end())))
#define loop(index, _start, _end) for (int index = (_start), _step = (_start) <= (_end) ? 1 : -1; index != (_end) + _step; index += _step)
template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;
template<typename T> istream& operator>>(istream& in, vector<T>& a) {for(auto &x : a) in >> x; return in;};
template<typename T> ostream& operator<<(ostream& out, vector<T>& a) {bool first = true;for(auto &x : a) {if(!first) out << ' ';first = false;out << x;}return out;};

namespace Dark_Lord_Binoy {
inline void init() {
    ios::sync_with_stdio(false); 
    cin.tie(nullptr);

    #ifdef LOCAL
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    #endif
}
}

int32_t main() {
    Dark_Lord_Binoy::init();
    Testcase_Handler {
        
    }

    print(_Time_);
    return 0;
}
