/*
#include <ext/pb_ds/detail/standard_policies.hpp>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
*/

template<typename T>
using ordered_multiset = tree<
T,
null_type,
less_equal<T>,
rb_tree_tag,
tree_order_statistics_node_update>;

template<typename A, typename B>
using ordered_map = tree<
A,
B,
less<A>,
rb_tree_tag,
tree_order_statistics_node_update>;

// functions:
// find_by_order
// order_of_key (lower_bound)
// find
// erase
// insert

