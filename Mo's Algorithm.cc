#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;
const int MOD = 1000000007;
const int MAX = 300005;

const int BLOCKS = 750;

struct Query {
	int L, R, id;
	
	pair<int, int> F() const {
		return make_pair(L / BLOCKS, ((L / BLOCKS) & 1) ? -R : +R);
	}
	
	bool operator < (const Query& b) const {
		return F() < b.F();
	}
} queries[MAX];

int n, q;
int a[MAX], ans[MAX], cnt[MAX], freq[MAX];

int answer, len, cur;

int ceil(int l, int d) {
	return (l + d - 1) / d;
}

void ins(int idx) {
	cur += (freq[cnt[a[idx]]] == 1 && cnt[a[idx]] == cur);	
	freq[cnt[a[idx]]]--;
	cnt[a[idx]]++;
	freq[cnt[a[idx]]]++;
	cur = max(cur, cnt[a[idx]]);
}

void rem(int idx) {	
	cur -= (freq[cnt[a[idx]]] == 1 && cnt[a[idx]] == cur);	
	freq[cnt[a[idx]]]--;
	cnt[a[idx]]--;
	freq[cnt[a[idx]]]++;
	cur = max(cur, cnt[a[idx]]);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cin >> n >> q;	
	for(int i = 0; i < n; ++i) {
		cin >> a[i];		
	}
	for(int i = 0; i < q; ++i) {
		int L, R;
		cin >> L >> R;
		--L, --R;
		queries[i] = Query{L, R, i};
	}
	sort(queries, queries + q);
	int l = 0, r = -1;	
	for(int i = 0; i < q; ++i) {
		auto [L, R, id] = queries[i];		
		len = ceil(R - L + 1, 2);		
		while(l > L) ins(--l);
		while(r < R) ins(++r);
		while(l < L) rem(l++);
		while(r > R) rem(r--);				
		answer = max(1, cur - ((R - L + 1) - cur));
		ans[id] = answer;
	}
	for(int i = 0; i < q; ++i) {
		cout << ans[i] << '\n';
	}
	return 0;
}
