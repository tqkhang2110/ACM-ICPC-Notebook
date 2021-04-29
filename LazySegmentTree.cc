#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max();
const int MOD = 1000000007;
const int MAX = 100005;

struct LazySegmentTree 
{
	LazySegmentTree *l = 0, *r = 0;
	
	int low, high;
	int value = INF;
	int mset = INF, madd = 0;
	
	LazySegmentTree(int lo, int hi) : low(lo), high(hi) {}
	
	LazySegmentTree(const vector<int>& vec, int lo, int hi) : low(lo), high(hi) {
		if(low + 1 < high) {
			int mid = low + (high - low) / 2;
			l = new LazySegmentTree(vec, low, mid);
			r = new LazySegmentTree(vec, mid, high);
			value = min(l->value, r->value);
		} else {
			value = vec[low];
		}
	}
	
	int query(int L, int R) {
		if(R <= low || high <= L) return INF;
		if(L <= low && high <= R) return value;
		push();
		return min(l->query(L, R), r->query(L, R));
	}
	
	void set(int L, int R, int x) {
		if(R <= low || high <= L) return;
		if(L <= low && high <= R) {
			mset = value = x, madd = 0;			
		} else {
			push(), l->set(L, R, x), r->set(L, R, x);
			value = min(l->value, r->value);
		}
	}
	
	void add(int L, int R, int x) {
		if(R <= low || high <= L) return;
		if(L <= low && high <= R) {
			if(mset != INF) {
				mset += x;
			} else {
				madd += x;
			}
			value += x;
		} else {
			push(), l->add(L, R, x), r->add(L, R, x);
			value = min(l->value, r->value);
		}
	}
	
	void push() {
		if(!l) {
			int mid = (low + high) / 2;
			l = new LazySegmentTree(low, mid);
			r = new LazySegmentTree(mid, high);
		}
		if(mset != INF) {
			l->set(low, high, mset), r->set(low, high, mset), mset = INF;
		} else if(madd) {
			l->add(low, high, madd), r->add(low, high, madd), madd = 0;
		}
	}
};

struct Solve 
{
	int n, k;	
	int a[MAX];
	
	void work() {
		cin >> n >> k;			
		LazySegmentTree* st = new LazySegmentTree(0, n);
		for(int i = 0; i < n; ++i) {
			cin >> a[i];
			st->set(i, i + 1, a[i]);
		}		
		for(int i = 0; i < n - k + 1; ++i) {
			cout << st->query(i, i + k) << ' ';
		}				
		cout << '\n';
	}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);	
	int t;
	cin >> t;
	while(t--) {
		Solve().work();
	}
	return 0;
}
