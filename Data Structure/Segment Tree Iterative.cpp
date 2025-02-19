class SegmentTree {
public:
    int n;
    vector<ll> tree;
    SegmentTree(int n) : tree(2 * n + 10), n(n){};
  
    void build() {
      for (int i = 1; i <= n; i++) 
        tree[n + i] = arr[i];
      for (int i = n; i > 0; i--) 
        tree[i] = tree[i << 1] + tree[i << 1 | 1];
    }
  
    void upd(int pos, int value) {
      for (tree[pos += n] = value; pos > 1; pos >>= 1)
        tree[pos >> 1] = tree[pos] + tree[pos ^ 1]; // Range sum
    }
  
    ll query(int l, int r) { // Sum of [1, 4]
      long long res = 0;
      for (l += n, r += n + 1; l < r; l >>= 1, r >>= 1) {
        if (l & 1) res += tree[l++];
        if (r & 1) res += tree[--r];
      }
      return res;
    }
};
   
int main() {
    SegmentTree st(n);
    st.build();
    ll ans = st.query(1, 4) << "\n"; // Sum of [1, 4]
    st.update(3, 6); // Update index 3 to value of 6
}