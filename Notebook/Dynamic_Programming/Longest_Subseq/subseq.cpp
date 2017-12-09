#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;

//O(n^2)
int lis(vector<ll>& v){
	vector<int> lis(v.size(), 1);

	for(int i=1; i<v.size(); ++i) for(int j=0; j<i; ++j)
		if(v[j] < v[i] && lis[i] < lis[j] + 1) lis[i] = lis[j] + 1;

	int max_len = 0;
	for(int l : lis) if(max_len < l) max_len = l;
	return max_len;
}

//O(nlogn)
int lis2(vector<ll> v){
	if(v.empty()) return 0;
	vector<int> lis(v.size(), 0);

	int last = 1;
	lis[0] = v[0];
	for(int i=1; i<v.size(); ++i){
		if(v[i] < l[0]) lis[0] = v[i];
		else if(lis[last-1] < v[i]) lis[last++] = v[i];
		else *upper_bound(lis.begin(), lis.begin()+last, v[i]) = v[i];
	}
	return last;
}

int main(){
	int n; cin >> n;
	vector<ll> v(n);

	for(int i=0; i<n; ++i) cin >> v[i];

	cout << "1: " << lis (v) << endl;
	cout << "2: " << lis2(v) << endl;
}
