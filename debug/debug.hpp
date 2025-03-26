#ifdef LOCAL

#include<bits/stdc++.h>
using namespace std;

// VS Code colors for the terminal
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define MAGENTA "\033[0;35m"
#define CYAN "\033[0;36m"
#define WHITE "\033[0;37m"
#define RESET "\033[0m"

template <typename A, typename B>
string to_string(pair<A, B> p);

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p);

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p);

template <typename A>
string to_string(queue<A> v);

template <typename A>
string to_string(stack<A> v);

template <typename A>
string to_string(priority_queue<A> v);

template <typename A>
string to_string(priority_queue<A, vector<A>, greater<A>> v);

string to_string(const string& s) {
    return '"' + s + '"';
}

string to_string(const char* s) {
    return to_string((string) s);
}

string to_string(char c) {
    return "'" + string(1, c) + "'";
}

string to_string(bool b) {
    return (b ? "true" : "false");
}

string to_string(vector<bool> v) {
    bool first = true;
    string res = "{";
    for (int i = 0; i < static_cast<int>(v.size()); i++) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v[i]);
    }
    res += "}";
    return res;
}

template <size_t N>
string to_string(bitset<N> v) {
    string res = "";
    for (size_t i = 0; i < N; i++) {
        res += static_cast<char>('0' + v[i]);
    }
    return res;
}

template <typename A>
string to_string(A v) {
    bool first = true;
    string res = "{";
    for (const auto &x : v) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(x);
    }
    res += "}";
    return res;
}

template <typename A>
string to_string(queue<A> v) {
    bool first = true;
    string res = "[";
    while(!v.empty()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v.front());
        v.pop();
    }
    res += "]";
    return res;
}

template <typename A>
string to_string(stack<A> v) {
    bool first = true;
    string res = "[";
    while(!v.empty()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v.top());
        v.pop();
    }
    res += "]";
    return res;
}

template <typename A>
string to_string(priority_queue<A> v) {
    bool first = true;
    string res = "[";
    while(!v.empty()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v.top());
        v.pop();
    }
    res += "]";
    return res;
}

template <typename A>
string to_string(priority_queue<A, vector<A>, greater<A>> v) {
    bool first = true;
    string res = "[";
    while(!v.empty()) {
        if (!first) {
            res += ", ";
        }
        first = false;
        res += to_string(v.top());
        v.pop();
    }
    res += "]";
    return res;
}

template <typename A, typename B>
string to_string(pair<A, B> p) {
    return "(" + to_string(p.first) + ", " + to_string(p.second) + ")";
}

template <typename A, typename B, typename C>
string to_string(tuple<A, B, C> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ")";
}

template <typename A, typename B, typename C, typename D>
string to_string(tuple<A, B, C, D> p) {
    return "(" + to_string(get<0>(p)) + ", " + to_string(get<1>(p)) + ", " + to_string(get<2>(p)) + ", " + to_string(get<3>(p)) + ")";
}

void debug_out() { cerr << endl; }

template <typename Head, typename... Tail>
void debug_out(Head H, Tail... T) {
    cerr << " " << to_string(H);
    debug_out(T...);
}

string __Time() {
    auto x = ceil(1000 * ((double)clock()) / (double)CLOCKS_PER_SEC);
    int z = x;
    return YELLOW + to_string(z) + "ms" + RESET;
}

#define _Time_ __Time()
#define START_TIMER auto __start_time = chrono::high_resolution_clock::now();
#define END_TIMER cerr << "Line:" << __LINE__ << YELLOW << " Execution Time: " << chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - __start_time).count() << "ms" << RESET << endl;

#define dbg(...) cerr << "Line:" << __LINE__ << " [" << #__VA_ARGS__ << "]:", debug_out(__VA_ARGS__);

#else
#define dbg(...) 42
#define START_TIMER
#define END_TIMER
#define _TIME_
#define RED
#define RED
#define GREEN
#define YELLOW
#define BLUE
#define MAGENTA
#define CYAN
#define WHITE
#define RESET
#endif
