#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;
const int MOD = 1000000007;
const int MAX = 300005;

struct Query {
	int L, R, id;
} queries[MAX];

struct Node {
	int value;
	int counter;
	Node() : value(-INF), counter(0) {}
	Node(int v, int c) : value(v), counter(c) {}	
};

Node operator + (const Node& lhs, const Node& rhs) {
	if(lhs.value == rhs.value) {
		return Node(lhs.value, lhs.counter + rhs.counter);
	} else if(lhs.counter > rhs.counter) {
		return Node(lhs.value, lhs.counter - rhs.counter);
	}
	return Node(rhs.value, rhs.counter - lhs.counter);
}

struct SegmentTree 
{
	vector<Node> st;
	int n;	
	
	SegmentTree(int size) : st(size << 1, Node()) , n(size) {}
	
	void update(int pos, int value) {
		Node v = Node(value, 1);
		for(st[pos += n] = v; pos >>= 1; ) {
			st[pos] = st[pos << 1] + st[pos << 1 | 1];
		}
	}	
	
	Node query(int L, int R) {
		Node ret = Node();
		for(L += n, R += n; L < R; L >>= 1, R >>= 1) {
			if(L & 1) {
				ret = ret + st[L++];
			}
			if(R & 1) {
				ret = st[--R] + ret;
			}
		}
		return ret;
	}
};

int n, q;
int a[MAX];

vector<int> pos[MAX];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;	
	SegmentTree st(n);
	for(int i = 0; i < n; ++i) {
		cin >> a[i];	
		st.update(i, a[i]);	
		pos[a[i]].emplace_back(i);
	}
	for(int i = 0; i < q; ++i) {
		int L, R;
		cin >> L >> R;
		--L;
		queries[i] = Query{L, R, i};
	}
	for(int i = 0; i < q; ++i) {
		auto [L, R, id] = queries[i];
		int val = st.query(L, R).value;	
		int occ = lower_bound(pos[val].begin(), pos[val].end(), R) - lower_bound(pos[val].begin(), pos[val].end(), L);
		int answer = max(1, 2 * occ - (R - L));
		cout << answer << '\n';
	}
	return 0;
}
