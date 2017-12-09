#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

// Note: Required that v is sorted
ll count_ways(vector<ll>& v, ll val){
	if(v.empty()) return 0;

	vector<ll> table(++val, 0);
	table[0] = 1;

	for(int i=0; i<v.size(); ++i) for(int j=v[i]; j<val; ++j)
		table[j] += table[j-v[i]];

	return table[val-1];
}
bool can_make_change(vector<ll>& v, ll val){
	for(ll e : v) if((val %= e) == 0) return true;
	return false;
}

int main(){
	int n, x;
	cin >> n >> x;
	vector<ll> v(n);
	for(int i=0; i<n; ++i) cin >> v[i];

	sort(v.begin(), v.end());
	cout << count_ways(v, x) << endl;
}
