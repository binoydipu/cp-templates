struct Node {
    Node *nxt[26]; // 26 (a - z)
    int pref, words; // current prefix & words cnt
    Node() {
        for (int i = 0; i < 26; i++) nxt[i] = NULL;
        pref = words = 0;
    }
    bool exists(char ch) { // link already created
        return (nxt[ch - 'a'] != NULL);
    }
    void create(char ch, Node *node) { // create new link
        nxt[ch - 'a'] = node;
    }
};
class Trie {
private: Node *root;
public: 
    Trie() {
        root = new Node();
    }
    void insert(string word) {
        Node *cur = root;
        for (auto &ch : word) {
            if(!cur->exists(ch)) { 
                cur->create(ch, new Node());
            }
            cur = cur->nxt[ch - 'a']; 
            cur->pref++;
        }
        cur->words++;
    }
    void remove(string word) {
        Node *cur = root;
        for (auto &ch : word) {
            cur = cur->nxt[ch - 'a'];
            cur->pref--;
        }
        cur->words--;
    }
    int search(string word) {
        Node *cur = root;
        for (auto &ch : word) {
            if(!cur->exists(ch)) {
                return false;
            }
            cur = cur->nxt[ch - 'a']; 
        }
        return cur->words;
    }
    int startsWith(string prefix) {
        Node *cur = root;
        for (auto &ch : prefix) {
            if(!cur->exists(ch)) {
                return false;
            }
            cur = cur->nxt[ch - 'a']; 
        }
        return cur->pref;
    }
};