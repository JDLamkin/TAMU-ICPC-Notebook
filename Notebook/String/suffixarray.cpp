#include <string>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct suffix {
    int rank[2];
    int index;
};

bool cmp(suffix a, suffix b) {
    return a.rank[0] == b.rank[0] ? a.rank[1] < b.rank[1] : a.rank[0] < b.rank[0];
}

struct sarray {
    vector<int> idx, sarr, lcp;
    vector<suffix> suf;
    string t;
    int n;

    sarray(int sz) : idx(sz), suf(sz), sarr(sz), lcp(sz) {}

    void build(string &s) {
        t = s;
        n = s.size();
        for (int i = 0; i < n; ++i) {
            suf[i].index = i;
            suf[i].rank[0] = s[i] - ' ';
            suf[i].rank[1] = (i+1) < n ? s[i+1] - ' ' : -1;
        }
        sort(suf.begin(), suf.begin() + n, cmp);
        for (int len = 4; len < 2*n; len *= 2) {
            int rank = 0, prev_rank = suf[0].rank[0];
            suf[0].rank[0] = rank;
            idx[suf[0].index] = 0;

            for (int i = 1; i < n; ++i) {
                if (suf[i].rank[0] == prev_rank && suf[i].rank[1] == suf[i-1].rank[1]) {
                    suf[i].rank[0] = rank;
                } else {
                    prev_rank = suf[i].rank[0];
                    suf[i].rank[0] = ++rank;
                }
                idx[suf[i].index] = i;
            }

            for (int i = 0; i < n; ++i) {
                int next = suf[i].index + len/2;
                suf[i].rank[1] = next < n ? suf[idx[next]].rank[0] : -1;
            }
            sort(suf.begin(), suf.begin()+n, cmp);
        }

        for (int i = 0; i < n; ++i) {
            sarr[i] = suf[i].index;
        }
    }

    void build_lcp() {
        fill(lcp.begin(), lcp.begin()+n, 0);
        vector<int> inv(n);
        for (int i = 0; i < n; ++i) {
            inv[sarr[i]] = i;
        }

        int len = 0;
        for (int i = 0; i < n; ++i) {
            if (inv[i] == n-1) {
                len = 0;
                continue;
            }
            int j = sarr[inv[i]+1];
            while (i+len < n && j+len < n && t[i+len] == t[j+len]) ++len;
            lcp[inv[i]] = len;
            if (len > 0) --len;
        }
    }

    int& operator[](int pos) {
        return sarr[pos];
    }
};
