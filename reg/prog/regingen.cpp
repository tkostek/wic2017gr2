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
      out << testCase.n << "\n";
	for (int i=0; i<(int)testCase.v.size()-1; i++) {
		out << testCase.v[i] << " ";
	}
	out << testCase.v.back() << "\n";
      return out;
    }
  protected:
    TestCase() {}
      int n;
	std::vector<ll> v;
};

class MissingCase : public TestCase
{
private:
  int nextNumber(int a, int b){
    vector <int> options;
    for(int i = a - 5; i <= a + 5; i++){
      if(abs(i - b) > 3)
        continue;
      if(i < 0 || i > 100)
        continue;
      options.push_back(i);
    }
    return options[rand_range(0, options.size() - 1)];
  }
public:
	MissingCase(int nn, int m)
	{
		n=nn;
		v.push_back(rand_range(0, 100));
    v.push_back(nextNumber(v[0], v[0]));
    for(int i = 2; i < n; i++)
      v.push_back(nextNumber(v[i - 2], v[i - 1]));
		bool templ[n];
    for(int i = 0; i < n; i++)
      templ[i] = (i < m);
    RG.randomShuffle(templ, templ + n);
    for(int i = 0; i < n; i++){
      if(templ[i])
        v[i] = -1;
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
        ss << "reg"; // except here
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
      MissingCase(6, 2),
      MissingCase(6, 4)
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(3345);
  {
    const TestCase t[] = {
      MissingCase(20, 3),
      MissingCase(20, 16),
      MissingCase(20, 20)
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(876345);
  {
    const TestCase t[] = {
      MissingCase(100, 5),
      MissingCase(100, 75)
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(65657473);
  {
    const TestCase t[] = {
      MissingCase(500, 20),
      MissingCase(500, 450)
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(153);
  {
    const TestCase t[] = {
      MissingCase(999, 100),
      MissingCase(1000, 990)
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
}
