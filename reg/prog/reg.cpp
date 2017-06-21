#include <iostream>
using namespace std;

const int mod = 1000000007;

int abs(int x){
	return x > 0 ? x : -x;
}

int a[1000], n, dp[101][7][7], ndp[101][7][7];
int main(){
	cin >> n;
	for(int i = 0; i < n; i++){
		cin >> a[i];
	}
	for(int k = 0; k <= 100; k++){

		if(a[2] != -1 && k != a[2]){
			continue;
		}

		for(int j = 0; j < 7; j++){
			int back1 = k + 3 - j;
			if((a[1] != -1 && back1 != a[1]) || back1 < 0 || back1 > 100){
				continue;
			}
			for(int l = 0; l < 7; l++){
				int back2 = back1 + 3 - l;
				if((a[0] != -1 && back2 != a[0]) || back2 < 0 || back2 > 100){
					continue;
				}
				if(abs(k - back2) <= 5){
					ndp[k][j][l] = 1;
				}
			}
		}
	}

	for(int i = 3; i < n; i++){
		for(int k = 0; k <= 100; k++){
			for(int j = 0; j < 7; j++){
				for(int l = 0; l < 7; l++){
					dp[k][j][l] = ndp[k][j][l];
					ndp[k][j][l] = 0;
				}
			}
		}
		for(int k = 0; k <= 100; k++){

			if(a[i] != -1 && k != a[i]){
				continue;
			}

			for(int j = 0; j < 7; j++){
				int back1 = k + 3 - j;
				if((a[i - 1] != -1 && back1 != a[i - 1]) || back1 < 0 || back1 > 100){
					continue;
				}
				for(int l = 0; l < 7; l++){
				int back2 = back1 + 3 - l;
					if((a[i - 2] != -1 && back2 != a[i - 2]) || back2 < 0 || back2 > 100){
						continue;
					}
					if(abs(k - back2) <= 5){
						for(int m = 0; m < 7; m++){
							ndp[k][j][l] = (ndp[k][j][l] + dp[back1][l][m]) % mod;
						}
					}
				}
			}
		}
	}

	int res = 0;
	for(int k = 0; k <= 100; k++){
		for(int j = 0; j < 7; j++){
			for(int l = 0; l < 7; l++){
				res = (res + ndp[k][j][l]) % mod;
			}
		}
	}

	cout << res << "\n";
}
