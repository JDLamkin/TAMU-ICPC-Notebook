#include <string>
#include <vector>

using namespace std;

vector<int> kmp(string &s, string &p) {
    if (p.empty()) return {};

    vector<int> lps(p.size());
    vector<int> ans;
    for (int i = 1, k = 0; i < p.size(); ++i) {
        while (k > 0 && p[k] != p[i]) k = lps[k-1];
        if (p[k] == p[i]) ++k;
        lps[i] = k;
    }

    for (int i = 0, k = 0; i < s.size(); ++i) {
        while (k > 0 && p[k] != s[i]) k = lps[k-1];
        if (p[k] == s[i]) ++k;
        if (k == p.size()) {
            ans.push_back(i-k+1);
            k = lps[k-1];
        }
    }
    return ans;
}

