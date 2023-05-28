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
    dist[src] = 0;
    pq.push({0, src});
    while(!pq.empty()){
        int cur = pq.top().second; pq.pop();
        for(auto [u, w] : g[cur]){
            if(dist[cur] + w < dist[u]){
                pq.push({-(dist[u] = dist[cur] + w), adj});
            }
        }
    }
    return dist;
}


// Graph without edge weights
template<typename graph>
vector<int> dijkstra2(vector<vector<int> >& g, int src){
    vector<int> dist(g.size(), INF);
    priority_queue<pii> pq;
    dist[src] = 0;
    pq.push({0, src});
    while(!pq.empty()){
        int cur = pq.top().second; pq.pop();
		int d = dist[cur]+1;
        for(int adj : g[cur]){
            if(d < dist[adj]){
                pq.push({-(dist[adj] = d), adj});
            }
        }
    }
    return dist;
}
