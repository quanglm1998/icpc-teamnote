#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
/*
    change null_type to int if we want to use map instead
    find_by_order(k) returns an iterator to the k-th element (0-indexed)
    order_of_key(k) returns numbers of item being strictly smaller than k
*/
template<typename T = int>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
