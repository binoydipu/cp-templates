/**
 *    author:   Binoy Barman
 *    created:  2025-03-23 23:29:58
**/

#include<bits/stdc++.h>
using namespace std;

template <typename T>
class List {
  private:
    struct node {
        T val;
        node *l = nullptr, *r = nullptr;
        node() : val(0) {}
        node(const T& _val) : val(_val) {}

        bool operator<(const node& other) const {
            return val < other.val;
        }
    };

    node* create(const T& __v) {
        try {
            node *n = new node(__v);
            return n;
        }
        catch(const bad_alloc& e) {
            cerr << "Memory allocation failed: " << e.what() << '\n';
            return nullptr;
        }
    }

    node *front, *back;
    int N;

    class Iterator {
      private:
        node* cur;

      public:
        Iterator() : cur(nullptr) {}
        explicit Iterator(node* ptr) : cur(ptr) {}
  
        T &operator*() { return cur->val; }
        T* operator->() { return &(cur->val); }
        node* get() const { return cur; }

        Iterator& operator++() {
            if(cur) cur = cur->r;
            return *this;
        }
        Iterator operator++(int32_t) {
            Iterator temp = *this;
            ++(*this);
            return temp;
        }
        Iterator& operator--() {
            if(cur) cur = cur->l;
            return *this;
        }
        Iterator operator--(int32_t) {
            Iterator temp = *this;
            --(*this);
            return temp;
        }
        bool operator==(const Iterator &other) const { return cur == other.cur; }
        bool operator!=(const Iterator &other) const { return cur != other.cur; }
        explicit operator bool() const { return cur != nullptr; }
    };

    class ReverseIterator {
      private:
        node* cur;

      public:
        ReverseIterator() : cur(nullptr) {}
        explicit ReverseIterator(node* ptr) : cur(ptr) {}

        T &operator*() { return cur->val; }
        T* operator->() { return &(cur->val); }
        node* get() const { return cur; }

        ReverseIterator& operator++() {
            if(cur) cur = cur->l;
            return *this;
        }
        ReverseIterator operator++(int32_t) {
            ReverseIterator temp = *this;
            ++(*this);
            return temp;
        }
        ReverseIterator& operator--() {
            if(cur) cur = cur->r;
            return *this;
        }
        ReverseIterator operator--(int32_t) {
            ReverseIterator temp = *this;
            --(*this);
            return temp;
        }
        bool operator==(const ReverseIterator &other) const { return cur == other.cur; }
        bool operator!=(const ReverseIterator &other) const { return cur != other.cur; }
        explicit operator bool() const { return cur != nullptr; }
    };

    node* merge(node* left, node* right, bool _assending) {
        if (!left) return right;
        if (!right) return left;

        if ((_assending && left->val <= right->val) || (!_assending && left->val >= right->val)) {
            left->r = merge(left->r, right, _assending);
            left->r->l = left;
            left->l = nullptr;
            return left;
        } else {
            right->r = merge(left, right->r, _assending);
            right->r->l = right;
            right->l = nullptr;
            return right;
        }
    }

    node* split(node* head) {
        node* slow = head, *fast = head->r;
        while (fast && fast->r) {
            slow = slow->r;
            fast = fast->r->r;
        }
        node* mid = slow->r;
        slow->r = nullptr;
        if (mid) mid->l = nullptr;
        return mid;
    }

    node* mergeSort(node* head, bool _assending) {
        if(!head || !head->r) return head;

        node *mid = split(head);
        node *left = mergeSort(head, _assending);
        node *right = mergeSort(mid, _assending);
        return merge(left, right, _assending);
    }

  public:
    List() : N(0) {
        front = back = nullptr;
    }

    Iterator begin() { return Iterator(front); }
    Iterator end() { return Iterator(nullptr); }

    ReverseIterator rbegin() { return ReverseIterator(back); }
    ReverseIterator rend() { return ReverseIterator(nullptr); }

    uint32_t Size() const { return N; }

    T Front() { assert(front); return front->val; }
    T Back() { assert(back); return back->val; }
    bool Empty() { return N == 0; }
    void Clear() { while(!Empty()) Pop_back(); }

    List<T> operator=(List<T>& __b) { // O(N)
        Clear();
        for(auto _x : __b) Push_back(_x);
    }

    // Don't use, works in O(N) per call, so O(N^2) for a traverse
    T& operator[](uint32_t __index) {
        assert(__index >= 0 && __index < N);
        node *cur = front;
        for (int i = 0; i < __index; i++) {
            cur = cur->r;
        }
        return cur->val;
    }

    void Print() { // O(N)
        for (auto it = begin(); it != end(); ++it) {
            if(it != begin()) cout << ' ';
            cout << *it;
        }
        if(!Empty()) cout << '\n';
    }

    // Uses MergeSort to sort list in O(NlogN)
    void Sort(bool _assending = true) {
        front = mergeSort(front, _assending);
        back = front;
        while(back && back->r) back = back->r;
    }

    void Push_back(const T& __v) { // O(1)
        node *n = create(__v);
        if(!n) return;
        if(N == 0) {
            front = back = n;
        } else {
            n->l = back;
            back->r = n;
            back = n;
        }
        N++;
    }

    void Push_front(const T& __v) { // O(1)
        node *n = create(__v);
        if(!n) return;
        if(N == 0) {
            front = back = n;
        } else {
            n->r = front;
            front->l = n;
            front = n;
        }
        N++;
    }

    // Returns iterator to the first occurence of Key(__v)
    Iterator Find(const T& __v) { // O(N)
        node *cur = front;
        while(cur) {
            if(cur->val == __v) return Iterator(cur);
            cur = cur->r;
        }
        return Iterator(nullptr);
    }

    // Erases the element at __pos
    int Erase(const Iterator& __pos) { // O(1)
        if(__pos == Iterator(nullptr)) return 0;
        node *cur = __pos.get();
        if(!cur) return 0;
        if(cur->l) cur->l->r = cur->r;
        if(cur->r) cur->r->l = cur->l;
        if(cur == front) front = cur->r;
        if(cur == back) back = cur->l;

        delete cur;
        N--;
        return 1;
    }

    // Erases all occurence of Key (__v) in the list, returns count of numbers erased
    int Erase(const T& __v) { // O(N)
        node *cur = front;
        int32_t _erased = 0;
        while(cur) {
            if(cur->val == __v) {
                if(cur->l) cur->l->r = cur->r;
                if(cur->r) cur->r->l = cur->l;
                if(cur == front) front = cur->r;
                if(cur == back) back = cur->l;

                delete cur;
                N--;
                _erased++;
            }
            cur = cur->r;
        }
        return _erased;
    }

    int Count(const T& __v) { // O(N)
        node *cur = front;
        int32_t _count = 0;
        while(cur) {
            if(cur->val == __v) _count++;
            cur = cur->r;
        }
        return _count;
    }

    int Pop_back() { // O(1)
        assert(N != 0);
        int val = back->val;
        if(N == 1) {
            delete back;
            front = back = nullptr;
        } else {
            node *temp = back;
            back = back->l;
            back->r = nullptr;
            delete temp;
        }
        N--;
        return val;
    }

    int Pop_front() { // O(1)
        assert(N != 0);
        int val = front->val;
        if(N == 1) {
            delete front;
            front = back = nullptr;
        } else {
            node *temp = front;
            front = front->r;
            front->l = nullptr;
            delete temp;
        }
        N--;
        return val;
    }
};

int32_t main() {

    List<int> li;
    li.Push_back(1);
    li.Push_front(2);
    li.Push_back(3);
    li.Print();

    List<string> a;
    a.Push_back("binoy");
    a.Push_back("bhushan");
    a.Push_back("barman");
    a.Push_back("dipu");

    a.Print();
    a.Sort();
    a.Print();

    List<pair<int, int>> b;
    b.Push_back({9, 8});
    b.Push_back({1, 3});
    b.Push_back({6, 2});

    return 0;
}
