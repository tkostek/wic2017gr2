#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

int tryGame(int n){

	int last = -1, cnt = 0, res;

	while(true){
		cnt ++;
		res = rand() % n;

		if(res == 0 && last == 0){
			return cnt;
		}
		last = res;
	}
}

int main(){
	int n, M = 100000;
	cin >> n;
	long double sum = 0;
	
	for(int i = 0; i < M; i++){
		sum += tryGame(n);
	}

	cout << round(sum / M) << ".000000\n";

}