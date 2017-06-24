#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>
#define LL long long
using namespace std;

int n, m;
vector <pair <int, int> > g[200000];
LL dist[200000];
priority_queue <pair <LL, int> > Q;
int main(){
	//ios_base::sync_with_stdio(0);
	cin >> n >> m;
	for(int i = 0; i < m; i++){
		int a, b, c;
		cin >> a >> b >> c;
		a--; b--;
		g[2 * a].push_back(make_pair(2 * b + 1, c));
		g[2 * a + 1].push_back(make_pair(2 * b, 2 * c));
		g[2 * b].push_back(make_pair(2 * a + 1, c));
		g[2 * b + 1].push_back(make_pair(2 * a, 2 * c));
	}
	n = 2 * n;
	for(int i = 0; i < n; i++){
		dist[i] = 1000000000000000LL;
	}
	dist[0] = 0;
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
			if(dist[w] + g[w][i].second < dist[next]){
				dist[next] = dist[w] + g[w][i].second;
				Q.push(make_pair(-dist[next], next));
			}
		}
	}
	if(dist[n - 1] > dist[n - 2]){
		cout << dist[n - 2] << "\n";
	} else {
		cout << dist[n - 1] << "\n";
	}
}
