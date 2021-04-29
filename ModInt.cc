#include <bits/stdc++.h>

using namespace std;

const int INF = numeric_limits<int>::max() / 2;
const int MOD = 1000000007;
const int MAX = 100010;

template<int MOD> struct ModInt {
   using Mint = ModInt;
   int val;
   ModInt(long long __val = 0) { fix(__val % MOD + MOD); }
   Mint& fix(int __val) { val = __val; if (val >= MOD) val -= MOD; return *this; }
   explicit operator int() { return val; }
   Mint operator + (const Mint &mt) const { return Mint().fix(val + mt.val); }
   Mint operator - (const Mint &mt) const { return Mint().fix(val - mt.val + MOD); }
   Mint operator * (const Mint &mt) const { return Mint().fix((long long)val * mt.val % MOD + MOD); }
   Mint& operator += (const Mint &mt) { return *this = *this + mt; }
   Mint& operator -= (const Mint &mt) { return *this = *this - mt; }
   Mint& operator *= (const Mint &mt) { return *this = *this * mt; }
   Mint pow(int y) const {
      Mint x = *this;
      Mint ans(1);
      for (; y > 0; y >>= 1, x *= x) {
         if (y & 1) ans *= x;
      }
      return ans;
   }
   Mint operator -() const { return Mint().fix(MOD - val); }
   Mint inv() const { return pow(MOD - 2); }
   Mint operator / (const Mint &mt) const { return *this * mt.inv(); }
   Mint& operator /= (const Mint &mt) const { return *this / mt; }
   friend ostream& operator << (ostream& os, const Mint& mt) { return os << mt.val; }
};

using Mint = ModInt<MOD>;

vector<Mint> fact(1, Mint(1));
vector<Mint> inv_fact(1, Mint(1));

Mint C(int n, int k) {
	if(k < 0 || k > n) {
		return Mint(0);
	}
	while((int) fact.size() < n + 1) {
		fact.push_back(fact.back() * Mint((int) fact.size()));
		inv_fact.push_back(Mint(1) / fact.back());
	}
	return fact[n] * inv_fact[k] * inv_fact[n - k];
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout << C(4, 2) << '\n'; // 4 choose 2
	return 0;
}
