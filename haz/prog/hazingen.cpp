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
      return out;
    }

  protected:
    TestCase() {}
    int n;
};

class Number : public TestCase
{
public:
	Number(int nn)
	{
		n=nn;
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
        ss << "haz"; // except here
        ss << test_no;
        if(cases.size() > 1U)
            ss << char('a' + i);
        ss << ".in";
        write(ss.str().c_str(), cases[i]);
    }
}

vector<TestCase> makeVec (int n){
  vector<TestCase> res;
  res.push_back(Number(n));
  return res;
}
/* ========================================================================== *
                                     main
 * ========================================================================== */


int main() {
  // HINT: Osobny setSeed przed kazdym testem lub grupa testow!
  // HINT: Nie generujemy testu 0.
  int t[10] = {3, 19, 31, 45, 63, 79, 85, 93, 99, 100};
  for(int i = 0; i < 10; i++){
    testGroup(makeVec(t[i]));
  }
}
