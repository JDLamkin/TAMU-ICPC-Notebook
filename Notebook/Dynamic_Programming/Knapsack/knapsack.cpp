/* Standard Knapsack DP. Runs in n*m time. v holds values and w holds weights. Note that v and w are 0 indexed but our dp is 1-indexed.
 */

#include <vector>
#include <algorithm>

using namespace std;

int knapsack(vector<int> &v, vector<int> &w) {
    int n = v.size(), m = w.size();
    vector<vector<int>> dp(n+1, vector<int>(m+1));
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            if (j-w[i] < 0) dp[i][j] = dp[i-1][j];
            else dp[i][j] = max(dp[i-1][j], dp[i-1][j-w[i-1]] + v[i-1]);
        }
    }
    return dp[n][m];
}
