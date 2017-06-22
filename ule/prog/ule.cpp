#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
using namespace std;

int n, a, b, h[1000000];
void reverse(stack <pair<int, int> > &s){
	vector <pair <int, int> > tmp;
	while(s.size()){
		tmp.push_back(s.top());
		s.pop();
	}
	for(int i = 0; i < (int)tmp.size(); i++){
		s.push(tmp[i]);
	}
}
int main(){
	//ios_base::sync_with_stdio(0);
	cin >> n >> a >> b;
	a--;b--;

	for(int i = 0; i < n; i++){
		if(a < b){
			cin >> h[i];
		} else {
			cin >> h[n - 1 - i];
		}
	}

	if(a > b){
		swap(a, b);
	}

	stack <pair <int, int> > decr;

	for(int i = a; i <= b; i++){
		while(decr.size() > 0 && decr.top().first < h[i]){
			decr.pop();
		}	
		decr.push(make_pair(h[i], i));
	}

	reverse(decr);

	long long res = 0;

	for(int i = a - 1; i >= 0; i--){
		if(h[i] > decr.top().first){
			continue;
		}
		res += decr.top().first - h[i];
	}

	for(int i = a; (i <= b && decr.size() > 0); i++){
		res += decr.top().first - h[i];
		if(i == decr.top().second){
			decr.pop();
		}
	}

	cout << res << "\n";
}
