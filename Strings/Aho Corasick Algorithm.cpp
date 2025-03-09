#include<bits/stdc++.h>
using namespace std;

vector<int> pattern_freq;

// builds a Finite State Automaton on the pattern strings, has failure links in case of no match
// able to process a text in linear time to generate count of patterns in the text
class AhoCorasick {
  private:
    struct Node {
        vector<int> pattern_ends; // stores string (id's) that ends here
        map<char, int> next; // original links

        int suf_link; // suffix link index, aka. failure link. points at longest prefix(of any pattern) that is suffix of current prefix
        int out_link; // output link, nearest ancestor of *this where an input pattern ended which is also a suffix link of *this.
    
        Node() : suf_link(-1), out_link(-1) {}
    };

  public:
    vector<Node> nodes;
    int root; // means "" empty string
    int P, N; // no of patterns, nodes
    
    AhoCorasick() : root(0), P(0), N(1) { 
        nodes.emplace_back();
    }
    void add_pattern (const string& pattern) {
        int u = root;
        for (auto c : pattern) {
            if(!nodes[u].next.count(c)) {
                nodes[u].next[c] = N++;
                nodes.emplace_back();
            }
            u = nodes[u].next[c];
        }
        nodes[u].pattern_ends.push_back(P++); // P-th patterns ends here
    }
    // builds suffix/fail links and output links after adding the patterns
    void build() {
        queue<int> Q;
        Q.push(root);
        nodes[root].suf_link = -1;
        while(!Q.empty()) {
            int v = Q.front();
            Q.pop();
            for (auto it : nodes[v].next) {
                int u = it.second;
                char c = it.first;
                // setting suffix/fail links
                int link = nodes[v].suf_link;
                while(link != -1 && !nodes[link].next.count(c)) link = nodes[link].suf_link; // no real link, go to suffix links
                if(link != -1) nodes[u].suf_link = nodes[link].next[c];
                else nodes[u].suf_link = root;
                // setting output links
                nodes[u].out_link = nodes[nodes[u].suf_link].pattern_ends.empty()
                                    ? nodes[nodes[u].suf_link].out_link
                                    : nodes[u].suf_link;
                // merging patters ends for faster traversal
                if(nodes[u].out_link != -1) {
                    nodes[u].pattern_ends.insert(
                        nodes[u].pattern_ends.end(),
                        nodes[nodes[u].out_link].pattern_ends.begin(),
                        nodes[nodes[u].out_link].pattern_ends.end());
                }
                Q.push(u);
            }
        }
        pattern_freq.resize(P, 0);
    }
    int advance (int u, char c) {
        while(u != -1 && !nodes[u].next.count(c)) u = nodes[u].suf_link;
        if(u == -1) u = root;
        else u = nodes[u].next[c];
        return u;
    }
    void traverse (const string& text) {
        int u = root;
        for(auto c : text) {
            u = advance(u, c);
            for (auto id : nodes[u].pattern_ends) pattern_freq[id]++; // id-th pattern ends at u
        }
    }
};
int32_t main() {
    AhoCorasick aho;
    aho.add_pattern("abc");
    aho.add_pattern("bcd");
    aho.add_pattern("efg");
    aho.build();

    aho.traverse("xyzabcdefghiabcabcabcj");

    for(auto x : pattern_freq) cout << x << " ";
    return 0;
}