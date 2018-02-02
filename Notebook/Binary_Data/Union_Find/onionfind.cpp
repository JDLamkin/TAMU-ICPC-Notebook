#include <vector>
using namespace std;

template<class T>
struct disjoint_set{
	vector<T> parent, size;

	disjoint_set(size_t n) : parent(n), size(n, 1){
		for(size_t i=0; i<n; ++i) parent[i] = i;
	}
	T root(T pos){
		while(parent[pos] != pos) {
			parent[pos] = parent[parent[pos]];
			pos = parent[pos];
		}
		return pos;
	}
	// Flatten the set
	// WARNING: once this is done, sets can't be separated
	T squish_root(T pos){
		if(parent[pos] == pos) return pos;
		return parent[pos] = squish_root(parent[pos]);
	}
	// Check if two elements are in the same set
	bool find(T p, T q){
		return root(p) == root(q);
	}
	void onion(T p, T q) {
		T rootp = root(p), rootq = root(q);
		if(size[rootp] > size[rootq]){
			parent[rootq] = rootp;
			size[rootp] += size[rootq];
		}
		else{
			parent[rootp] = rootq;
			size[rootq] += size[rootp];
		}
	}
};
