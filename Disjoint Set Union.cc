#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;
const int MOD = 1000000007;
const int MAX = 100010;

struct DSU 
{
	int par[MAX];
	int n;

	DSU(int size) : n(size) {
		iota(par, par + n, 0);
	} 
	
	inline int get(int x) {
		if(x == par[x]) return x;
		return par[x] = get(par[x]);
	}
	
	bool unite(int x, int y) {
		x = get(x);
		y = get(y);
		if(x != y) {
			par[y] = x;
			return true;
		}
		return false;
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n, m;
	cin >> n >> m;
	DSU dsu(n);
	for(int i = 0; i < m; ++i) {
		string op;
		int u, v;
		cin >> op >> u >> v;
		--u, --v;
		if(op[0] == 'u') {
			dsu.unite(u, v);
		} else if(op[0] == 'g') {
			cout << (dsu.get(u) == dsu.get(v) ? "YES" : "NO") << '\n';
		} else assert(false);		
	}
	return 0;
}
