#include <bits/stdc++.h>

using namespace std;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
/*
    change null_type to int if we want to use map instead
    find_by_order(k) returns an iterator to the k-th element (0-indexed)
    order_of_key(k) returns numbers of item being strictly smaller than k
*/
using ordered_set = tree<int, null_type, std::less<int>, rb_tree_tag, tree_order_statistics_node_update>;

const int INF = numeric_limits<int>::max();
const int MOD = 1000000007;
const int MAX = 100010;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	
	return 0;
}
