#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;
const int MOD = 1000000007;
const int MAX = 100005;

const int LOG = 20;	

struct LCA 
{
	struct Data {
		int par, max, min, sum;
	};
	
	vector<pair<int, int>> dsk[MAX]; // {weight, to}
	Data up[MAX][LOG];
	int depth[MAX], tin[MAX], tout[MAX];
	int cur = 0;
	
	LCA(int n) {
		for(int i = 0; i < n; ++i) {
			fill(up[i], up[i] + LOG, Data{0, -INF, INF, 0});
		}
	}
	
	int sum(int a, int b) {
		return a + b;
	}
	
	void add_edges(int u, int v, int w) {
		dsk[u].emplace_back(w, v);
		dsk[v].emplace_back(w, u);
	}
	
	void dfs(int a, int parent) {		
		tin[a] = ++cur;
		for(const auto& [w, b] : dsk[a]) {
			if(b == parent) {
				continue;
			}
			depth[b] = depth[a] + 1;
			up[b][0] = Data{a, w, w, w};
			for(int i = 1; i < LOG; ++i) {				
				int x = up[b][i - 1].par;
				up[b][i].par = up[x][i - 1].par;
				up[b][i].min = min(up[b][i - 1].min, up[x][i - 1].min);
				up[b][i].max = max(up[b][i - 1].max, up[x][i - 1].max);
				up[b][i].sum = sum(up[b][i - 1].sum, up[x][i - 1].sum);				
			}
			dfs(b, a);
		}
		tout[a] = ++cur;
	}	
	
	bool is_ancestor(int a, int b) {
		return tin[a] <= tin[b] && tout[b] <= tout[a];
	}
	
	int get_lca(int a, int b) {		
		if(is_ancestor(a, b)) return a;
		if(is_ancestor(b, a)) return b;
		for(int i = LOG - 1; i >= 0; --i) {
			if(not is_ancestor(up[a][i].par, b)) {
				a = up[a][i].par;
			}
		}
		return up[a][0].par;
	}
	
	pair<int, int> query(int a, int b) {
		int lca = get_lca(a, b);				
		pair<int, int> ret{INF, -INF};
		for(int rep = 0; rep < 2; ++rep) {
			for(int i = LOG - 1; i >= 0; --i) {
				if(is_ancestor(lca, up[a][i].par)) {
					ret.first = min(ret.first, up[a][i].min);
					ret.second = max(ret.second, up[a][i].max);
					a = up[a][i].par;
				}
			}
			swap(a, b);
		}
		return ret;
	}
	
	int dist(int a, int b) {
		return depth[a] + depth[b] - 2 * depth[get_lca(a, b)];
	}
};

int main() {	
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	int n;
	cin >> n;
	LCA lca(n);
	for(int i = 0; i < n - 1; ++i) {
		int u, v, w;
		cin >> u >> v >> w;
		--u, --v;
		lca.add_edges(u, v, w);
	}
	lca.dfs(0, 0);
	int q;
	cin >> q;
	while(q--) {
		int a, b;
		cin >> a >> b;
		--a, --b;		
		auto [mn, mx] = lca.query(a, b);
		cout << mn << ' ' << mx << '\n';
	}
	return 0;
}
