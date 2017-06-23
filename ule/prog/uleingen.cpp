#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <queue>
#include "oi.h"

using namespace std;

// HINT: Uzywamy liczb losowych wylacznie z pakietu oi.h
oi::Random RG(0xC0FFEE);

typedef long long int ll;

inline int rand_range(int a, int b) { return (RG.rand() % (b - a + 1)) + a; }
inline ll rand_range(ll a, ll b) { return (RG.randULL() % (b - a + 1)) + a; }
bool rand_bool(int pr) { return rand_range(1, 100) <= pr; }

int abs(int x){
  return x > 0 ? x : -x;
}
/* ========================================================================== *
                                   structs
 * ========================================================================== */

const int MAX = 500000;
const ll INF = 1e18;

class TestCase {
  public:
    friend ostream& operator << (ostream& out, const TestCase& testCase) {
      out << testCase.n << " " << testCase.a << " " << testCase.b << "\n";
    	for (int i=0; i<(int)testCase.v.size()-1; i++) {
    		out << testCase.v[i] << " ";
    	}
    	out << testCase.v.back() << "\n";
      return out;
    }

    void RandSwap(vector<int>&w){
      swap(w[rand_range(0, w.size() - 1)], w[rand_range(0, w.size() - 1)]);
    }

    vector <int> GenerateVector(int s, int l){
      vector <int> r;
      vector <int> choose;
      for(int i = 0; i <= l; i++){
        choose.push_back(i < s);
      }
      for(int i = 0; i <= 2 * l; i++){
        RandSwap(choose);
      }
      for(int i = 0; i <= l; i++){
        if(choose[i]){
          r.push_back(i);
        }
      }
      return r;
    }

  protected:
    TestCase() {}
    int n, a, b;
	  vector<int> v;
};

class UpHill : public TestCase
{
public:
	UpHill(int nn, int m, int r)
	{
		n=nn;
		v = GenerateVector(nn, m);
    a = rand_range(1, n);
    b = rand_range(1, n);
    for(int i = 0; i < r; i++){
      RandSwap(v);
    }
	}
};

class DownHill : public TestCase
{
public:
  DownHill(int nn, int m, int r)
  {
    n=nn;
    v = GenerateVector(nn, m);
    for(int i = 0; i < n / 2; i++){
      swap(v[i], v[n - 1 - i]);
    }
    a = rand_range(1, n);
    b = rand_range(1, n);
    for(int i = 0; i < r; i++){
      RandSwap(v);
    }
  }
};

class UHill : public TestCase
{
public:
  UHill(int nn, int m, int r)
  {
    n=nn;
    vector <int> t = GenerateVector(nn, m);
    for(int i = 0; i < n; i++){
      v.push_back(0);
    }
    for(int i = 0; i < n; i++){
      int pos;
      if(i % 2 == 0){
        pos = i / 2;
      } else {
        pos = n - 1 - i / 2;
      }
      v[pos] = t[n - 1 - i];
    }
    a = rand_range(1, n);
    b = rand_range(1, n);
    for(int i = 0; i < r; i++){
      RandSwap(v);
    }
  }
};

/* ========================================================================== *
                                 Do not touch
 * ========================================================================== */
void write(const char* filename, const TestCase& testCase)
{
    cout << "Writing " << filename << "..." << endl;
    ofstream file(filename);
    file << testCase;
    file.close();
}

void testGroup(const vector<TestCase>& cases)
{
    static int test_no = 0;
    ++test_no;
    for(int i = 0; i < (int) cases.size(); ++i)
    {
        stringstream ss;
        ss << "ule"; // except here
        ss << test_no;
        if(cases.size() > 1U)
            ss << char('a' + i);
        ss << ".in";
        write(ss.str().c_str(), cases[i]);
    }
}

/* ========================================================================== *
                                     main
 * ========================================================================== */


int main() {
  // HINT: Osobny setSeed przed kazdym testem lub grupa testow!
  // HINT: Nie generujemy testu 0.
  RG.setSeed(1);
  {
    const TestCase t[] = {
      UpHill(10, 20, 2),
      DownHill(10, 20, 2),
      UHill(10, 20, 2),
      UpHill(10, 20, 100),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(2);
  {
    const TestCase t[] = {
      UpHill(97, 200, 10),
      DownHill(98, 200, 10),
      UHill(99, 200, 2),
      UpHill(100, 200, 100),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(3);
  {
    const TestCase t[] = {
      UpHill(100000, 1000000, 5000),
      DownHill(99999, 1000000, 5000),
      UHill(99998, 1000000, 5000),
      UpHill(99997, 1000000, 100000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(4);
  {
    const TestCase t[] = {
      UpHill(250000, 1000000, 10000),
      DownHill(350000, 1000000, 10000),
      UHill(400000, 1000000, 10000),
      UpHill(500000, 1000000, 1000000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(5);
  {
    const TestCase t[] = {
      UpHill(900000, 1000000, 10000),
      DownHill(950000, 1000000, 10000),
      UHill(990000, 1000000, 10000),
      UpHill(1000000, 1000000, 1000000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
}
