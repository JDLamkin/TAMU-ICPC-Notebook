/* Dijkstra's is single-source shortest path that does NOT handle negative edge weights. 
 * Running time: O(E*log(E))
 */

#include <vector>
#include <limits>
#include <map>
#include <queue>

using namespace std;
typedef pair<int, int> pii;

#define INF numeric_limits<int>::max()

// Graph with edge weights
template<typename VI_or_MII> // Either vector<int> or map<int, int>
vector<int> dijkstra1(vector<VI_or_MII>& g, int src){
    vector<int> dist(g.size(), INF);
    priority_queue<pii> pq;
    pq.push({0, src});
    while(!pq.empty()){
        auto [cur, d] = pq.top(); pq.pop();
		if(dist[cur] != INF) continue;
		dist[cur] = -d;
        for(auto [u, w] : g[cur]){
            if(dist[u] == INF) pq.push({d-w, u});
        }
    }
    return dist;
}


// Graph without edge weights
template<typename graph>
vector<int> dijkstra2(vector<vector<int> >& g, int src){
    vector<int> dist(g.size(), INF);
    priority_queue<pii> pq;
    pq.push({0, src});
    while(!pq.empty()){
        auto [cur, d] = pq.top(); pq.pop();
		if(dist[cur] != INF) continue;
		dist[cur] = -d--;
        for(int adj : g[cur]){
            if(dist[adj] == INF) pq.push({d, adj});
        }
    }
    return dist;
}
