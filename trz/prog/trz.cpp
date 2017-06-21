#include <iostream>
#include <iomanip>
#include <algorithm>
#include <time.h>
using namespace std;

bool checkDist(long double r, long double p1[2], long double p2[2]){
	return r * r >= (p1[0] - p2[0]) * (p1[0] - p2[0]) + (p1[1] - p2[1]) * (p1[1] - p2[1]);
}

int main(){
	srand(time(NULL));
	long double r;
	long double s[3][2];
	cin >> r;
	for (int i = 0; i < 3; i++){
		for (int j = 0; j < 2; j++){
			cin >> s[i][j];
		}
	}

	int n = 3000, m = 0;

	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			long double p[2] = {(double)i * 10 / n, (double)j * 10 / n};
			m += (checkDist(r, p, s[0]) || checkDist(r, p, s[1]) || checkDist(r, p, s[2]));
		}
	}
	cout << setprecision(1) << fixed << (double) m / (double) (n * n) * 100 <<"\n";
}
