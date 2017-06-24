//zle rozwiazanie, naiwna Dijkstra - 0 punktow, nie przechodzi nawet testu 0

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define LL long long
using namespace std;

int n, m;
vector <pair <int, int> > g[100000];
LL dist[100000];
bool parz[100000];
priority_queue <pair <LL, int> > Q;
int main(){
	//ios_base::sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		g[a].push_back(make_pair(b, c));
		g[b].push_back(make_pair(a, c));
	}
	for(int i = 0; i < n; i++){
		dist[i] = 1000000000000000LL;
	}
	dist[0] = 0;
	parz[0] = 1;
	Q.push(make_pair(-dist[0], 0));
	while(Q.size()){
		int w = Q.top().second;
		LL reach = -Q.top().first;
		Q.pop();
		
		if(reach != dist[w]){
			continue;
		}

		for(int i = 0; i < g[w].size(); i++){
			int next = g[w][i].first;
			int len = (parz[w] ? 1 : 2) * g[w][i].second;
			if(dist[w] + len < dist[next]){
				dist[next] = dist[w] + len;
				parz[next] = !parz[w];
				Q.push(make_pair(-dist[next], next));
			}
		}
	}
	cout << dist[n - 1] << "\n";
}
