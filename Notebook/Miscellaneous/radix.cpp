#include <vector>
#include <algorithm>
using namespace std;

template<class T> void radix_sort(vector<T>& arr) {
	vector<T> temp(arr.size());

	for(int s=numeric_limits<T>::digits; s>=0; --s){
		int j = 0;
		for(int i=0; i<arr.size(); ++i){
			if((bool)s == (arr[i]<<s >= 0)) arr[i-j] = arr[i];
			else temp[j++] = arr[i];
		}
		for(int i=0; i<j; ++i) arr[arr.size()-j+i] = temp[i];
	}
}
