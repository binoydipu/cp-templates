#include<bits/stdc++.h>
using namespace std;

template <typename A, typename B>string to_string(pair<A, B> p);
template <typename A, typename B, typename C>string to_string(tuple<A, B, C> p);
template <typename A, typename B, typename C, typename D>string to_string(tuple<A, B, C, D> p);
string to_string(const string& s) { return '"' + s + '"'; }
string to_string(char c) {string s;s += c;return s; }
string to_string(const char* s) {return to_string((string) s); }
string to_string(bool b) {return (b ? "1" : "0"); }
string to_string(vector<bool> v) {bool first = true;string res = "{";for (int i = 0; i < static_cast<int>(v.size()); i++) {if (!first) {res += ", ";}first = false;res += to_string(v[i]);}res += "}";return res;}
template <size_t N>string to_string(bitset<N> v) {string res = "";for (size_t i = 0; i < N; i++) {res += static_cast<char>('0' + v[i]);}return res;}
template <typename A>string to_string(A v) {bool first = true;string res = "{";for (const auto &x : v) {if (!first) {res += ", ";}first = false;res += to_string(x);}res += "}";return res;}
template <typename A, typename B>string to_string(pair<A, B> p) {return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";}
template <typename A, typename B, typename C>string to_string(tuple<A, B, C> p) {return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";}
template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";}
template<class T> bool ckmin(T& a, const T& b) { return b < a ? a = b, 1 : 0; }
template<class T> bool ckmax(T& a, const T& b) { return a < b ? a = b, 1 : 0; }


struct Point;
string to_string(const Point& p);

// ->
void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
  cerr << " " << to_string(H);
  debug_out(T...);
}

// Print vector, deque, map, set
#define dbg(...) cerr<<"Line:"<<__LINE__<<" "<< "[" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__)
// <-


// MINE->

template<class T> using minheap = priority_queue<T, vector<T>, greater<T>>;

// Print Time
// #define time cout<<fixed<<setprecision(10); cerr<<"Time:"<<1000*((double)clock())/(double)CLOCKS_PER_SEC<<"ms\n"; 

//Print array
#define _print(v) {cerr<<"Line:"<<__LINE__<<" "<< "[" << #v << "]:"<<" [ "; for (auto &i:v){cerr<<i;cerr<<" ";}cerr<<"]";}

template <typename K, typename V>
void print(pair<K, V> p) { cerr << "(" << p.first << ", " << p.second << ")"; }

template<typename T>
void print(queue<T> v) { cerr<<"["; while(!v.empty()) { cerr<<v.front(); v.pop(); cerr<<(!v.empty() ? ", " : "]"); } }

template<typename T>
void print(stack<T> v) { cerr<<"["; while(!v.empty()) { cerr<<v.top(); v.pop(); cerr<<(!v.empty() ? ", " : "]"); } }

template<typename T>
void print(priority_queue<T> v) { cerr<<"["; while(!v.empty()) { cerr<<v.top(); v.pop(); cerr<<(!v.empty() ? ", " : "]"); } }

template <typename K, typename V>
void print(priority_queue<pair<K, V>> v) { cerr<<"["; while(!v.empty()) { print(v.top()); v.pop(); cerr<<(!v.empty() ? ", " : "]"); } }

template<typename T>
void print(minheap<T> v) { cerr<<"["; while(!v.empty()) { cerr<<v.top(); v.pop(); cerr<<(!v.empty() ? ", " : "]"); } }

// print execution time
string exec_time() { auto x = ceil(1000 * ((double)clock()) / (double)CLOCKS_PER_SEC); int z = x; return "Time:" + to_string(z) + "ms"; }

#define _Time_ exec_time()
void print(string s) { cerr << s; } 


// ->
void print_out() { cerr << endl; }

template <typename Head, typename... Tail>
void print_out(Head H, Tail... T) {
  cerr << " "; print(H);
  print_out(T...);
}

// To print stack, queue, priority queue, execution Time
#define print(...) cerr<<"Line:"<<__LINE__<<" "<< "[" << #__VA_ARGS__ << "]:", print_out(__VA_ARGS__)
// <-
