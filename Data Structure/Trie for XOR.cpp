struct Node {
    Node *nxt[2];
    int pref; // number of elements with this prefix
    Node() {
        nxt[0] = nxt[1] = NULL;
        pref = 0;
    }
    bool exists(int bit) { // link already created
        return (nxt[bit] != NULL);
    }
    void create(int bit, Node *node) { // create new link
        nxt[bit] = node;
    }
};
class Trie {
private: Node *root;
public: 
    Trie() {
        root = new Node();
    }
    void insert(int num) {
        Node *cur = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(!cur->exists(bit)) { 
                cur->create(bit, new Node());
            }
            cur = cur->nxt[bit]; 
            cur->pref++;
        }
    }
    void remove(int num) {
        Node *cur = root;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            cur = cur->nxt[bit];
            cur->pref--;
        }
    }
    int maxXor(int num) { // returns max of trie ^ num
        Node *cur = root;
        int ans = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(cur->exists(!bit) && cur->nxt[!bit]->pref > 0) {
                ans = ans | (1 << i);
                cur = cur->nxt[!bit];
            } else {
                cur = cur->nxt[bit];
            }
        }
        return ans;
    }
    int minXor(int num) { // returns min of trie ^ num
        Node *cur = root;
        int ans = 0;
        for (int i = 31; i >= 0; i--) {
            int bit = (num >> i) & 1;
            if(cur->exists(bit) && cur->nxt[bit]->pref > 0) {
                cur = cur->nxt[bit];
            } else {
                ans = ans | (1 << i);
                cur = cur->nxt[!bit];
            }
        }
        return ans;
    }
};