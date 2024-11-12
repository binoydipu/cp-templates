#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template <typename T> 
using o_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// order_of_key (k) : Number of items strictly smaller than k . O(logn)
// find_by_order(k) : K-th element in a set (counting from zero). O(logn)
template <typename T, typename R> 
using o_map = tree<T, R, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
