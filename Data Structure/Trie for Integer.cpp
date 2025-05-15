class Trie {
  private:
    static const int B = 31; // bits
    struct node {
        node *next[2];
        int prefix, cnt;
        node() {
            next[0] = next[1] = nullptr;
            prefix = cnt = 0;
        }
        inline bool exists(int bit) {
            return next[bit] != nullptr;
        }
        inline bool create(int bit, node *n) {
            next[bit] = n;
        }
        inline node* advance(int bit) {
            return next[bit];
        }
    } *root;

  public:
    Trie() {
        root = new node();
    }

    void insert(int x) {
        node *cur = root;
        for (int i = B; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if(!cur->exists(bit)) cur->create(bit, new node());
            cur = cur->advance(bit);
            cur->prefix++;
        }
        cur->cnt++;
    }
    int search(int x) {
        node *cur = root;
        for (int i = B; i >= 0; i--) {
            int bit = (x >> i) & 1;
            cur = cur->advance(bit);
            cur->prefix;
        }
        return cur->cnt;
    }
    int max_xor(int x) { // max of trie ^ x
        node *cur = root;
        int ans = 0;
        for (int i = B; i >= 0; i--) {
            int bit = (x >> i) & 1;
            if(cur->exists(!bit) && cur->next[!bit]->prefix > 0) {
                ans = ans | (1 << i);
                cur = cur->advance(!bit);
            } else {
                cur = cur->advance(bit);
            }
        }
        return ans;
    }
};