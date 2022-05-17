#include <ext/pb_ds/tree_policy.hpp>
#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;

tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> oset;

// order_of_key
// find_by_order

cc_hash_table<int, int> m1;
gp_hash_table<int, int> m2;

// like map, but much faster