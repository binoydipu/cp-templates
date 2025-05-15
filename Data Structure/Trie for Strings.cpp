class Trie {
  private:
    static const int B = 26; // chars
    struct node {
        node *next[B];
        int prefix, words;
        node() {
            for (int i = 0; i < B; i++) next[i] = nullptr;
            prefix = words = 0;
        }
        inline bool exists(char c) {
            return next[c - 'a'] != nullptr;
        }
        inline bool create(char c, node *n) {
            next[c - 'a'] = n;
        }
        inline node* advance(char c) {
            return next[c - 'a'];
        }
    } *root;

  public:
    Trie() {
        root = new node();
    }

    void insert(string s) {
        node *cur = root;
        for(auto c : s) {
            if(!cur->exists(c)) cur->create(c, new node());
            cur = cur->advance(c);
            cur->prefix++;
        }
        cur->words++;
    }
    void remove(string s) {
        node *cur = root;
        for(auto c : s) {
            cur = cur->advance(c);
            cur->prefix--;
        }
        cur->words--;
    }
    int search(string s) {
        node *cur = root;
        for(auto c : s) {
            if(!cur->exists(c)) return 0;
            cur = cur->advance(c);
        }
        return cur->words;
    }
    int starts_with(string s) {
        node *cur = root;
        for(auto c : s) {
            if(!cur->exists(c)) return 0;
            cur = cur->advance(c);
        }
        return cur->prefix;
    }
};