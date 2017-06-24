#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <utility>
#include <vector>
#include <set>
#include <queue>
#include <map>
#include "oi.h"

using namespace std;

// HINT: Uzywamy liczb losowych wylacznie z pakietu oi.h
oi::Random RG(0xC0FFEE);

typedef long long int ll;

inline int rand_range(int a, int b) { return (RG.rand() % (b - a + 1)) + a; }
inline ll rand_range(ll a, ll b) { return (RG.randULL() % (b - a + 1)) + a; }
bool rand_bool(int pr) { return rand_range(1, 100) <= pr; }
void random_swap(vector <int> &v){
  int x = v.size() - 1;
  swap(v[rand_range(0, x)], v[rand_range(0, x)]);
}
void vectorShuffle(vector <int> &v){
  for(int i = 0; i < 5 + v.size(); i++){
    random_swap(v);
  }
}

int abs(int x){
  return x > 0 ? x : -x;
}
/* ========================================================================== *
                                   structs
 * ========================================================================== */

const int MAX = 500000;
const ll INF = 1e18;
int perm[100000];
map <pair <int, int>, int> edges;

class TestCase {
  public:
    friend ostream& operator << (ostream& out, const TestCase& testCase) {
      out << testCase.n << " " << testCase.m << "\n";
    	for (int i=0; i<(int)testCase.a.size() - 1; i++) {
    		out << testCase.a[i] << " " << testCase.b[i] << " " << testCase.c[i] << "\n";
    	}
    	out << testCase.a.back() << " " << testCase.b.back() << " " << testCase.c.back() << "\n";
      return out;
    }
  protected:
    TestCase() {}
    int n, m;
	  vector<int> a, b, c;

    void mix(){
      for(int i = 0; i < m; i++){
        int x = rand_range(0, m - 1);
        int y = rand_range(0, m - 1);
        swap(a[x], a[y]);
        swap(b[x], b[y]);
        swap(c[x], c[y]);
        if(rand_range(0, 1) == 1){
          swap(a[i], b[i]);
        }
      }
    }
};

class RandomGraph : public TestCase
{
public:
	RandomGraph(int nn, int mm, int lim)
	{
		n = nn;
		m = mm;
    
    for(int i = 0; i < n; i++){
      perm[i] = i;
    }
    edges.clear();
    RG.randomShuffle(perm, perm + n);
    
    for(int i = 1; i < n; i++){
      int prev = perm[rand_range(0, i - 1)];
      edges[make_pair(prev, perm[i])] = 1;
      edges[make_pair(perm[i], prev)] = 1;
      a.push_back(prev + 1);
      b.push_back(perm[i] + 1);
      c.push_back(rand_range(1, lim));
    }

    for(int i = n; i <= m; i++){
      int x = rand_range(0, n - 1);
      int y = rand_range(0, n - 1);
      if(x == y || edges[make_pair(x, y)]){
        i--;
        continue;
      }
      edges[make_pair(x, y)] = 1;
      edges[make_pair(y, x)] = 1;
      a.push_back(x + 1);
      b.push_back(y + 1);
      c.push_back(rand_range(1, lim));
    }
    mix();
  }
};

class LongPath : public TestCase
{
public:
  LongPath(int nn, int path, int lim){
    n = nn;
    m = 0;

    for(int i = 0; i < n; i++){
      perm[i] = i;
    }

    RG.randomShuffle(perm + 1, perm + n - 1);
    swap(perm[path], perm[n - 1]);
    for(int i = 0; i < path; i++){
      a.push_back(perm[i] + 1);
      b.push_back(perm[i + 1] + 1);
      c.push_back(rand_range(1, lim));
    }

    int ind = path + 1;

    while(ind < n){

      int take = rand_range(2, 10);
      if(n - ind < 13){
        take  = n - ind;
      }

      a.push_back(perm[rand_range(0, path)] + 1);
      b.push_back(perm[ind] + 1);
      c.push_back(rand_range(1, 5));

      for(int i = 1; i < take; i++){
        a.push_back(perm[i + ind] + 1);
        b.push_back(perm[i + ind - 1] + 1);
        c.push_back(rand_range(1, 5));
      }

      a.push_back(perm[ind + take - 1] + 1);
      b.push_back(perm[ind + take - 3] + 1);
      c.push_back(rand_range(1, 5));
      ind += take;
    }
    m = a.size();
    mix();
  }
};

class Hamilton : public TestCase
{
public :
  Hamilton(int nn, int mm){
    n = nn;
    m = mm;

    for(int i = 0; i < n; i++){
      perm[i] = i;
    }

    RG.randomShuffle(perm + 1, perm + n - 1);
    edges.clear();
    for(int i = 0; i < n - 1; i++){
      a.push_back(perm[i] + 1);
      b.push_back(perm[i + 1] + 1);
      c.push_back(rand_range(1, 10));
    }

    for(int i = n; i <= m; i++){
      int x = rand_range(0, n - 3);
      int y = x + rand_range(2, n - x - 1);
      int z = y - x;
      x = perm[x];
      y = perm[y];

      if(edges[make_pair(x, y)]){
        i--;
        continue;
      }

      edges[make_pair(x, y)] = 1;
      edges[make_pair(y, x)] = 1;

      a.push_back(x + 1);
      b.push_back(y + 1);
      c.push_back(rand_range(min(4 * z, 1000000), min(15 * z, 1000000)));
    }
    mix();
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
        ss << "mar"; // except here
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
      RandomGraph(19, 50, 10),
      LongPath(20, 10, 1000000),
      Hamilton(21, 24),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(2);
  {
    const TestCase t[] = {
      RandomGraph(199, 500, 100),
      LongPath(200, 50, 1000000),
      Hamilton(201, 300),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(3);
  {
    const TestCase t[] = {
      RandomGraph(499, 1000, 1000),
      LongPath(513, 231, 1000000),
      Hamilton(507, 2014),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(4);
  {
    const TestCase t[] = {
      RandomGraph(5015, 100000, 1000000),
      LongPath(5009, 1352, 1000000),
      Hamilton(5019, 5125),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(5);
  {
    const TestCase t[] = {
      RandomGraph(50132, 60284, 5),
      LongPath(50097, 49129, 1000000),
      Hamilton(50121, 52019),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(6);
  {
    const TestCase t[] = {
      RandomGraph(73143, 157194, 10),
      LongPath(72923, 50135, 1000000),
      Hamilton(71189, 81658),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(7);
  {
    const TestCase t[] = {
      RandomGraph(79123, 147285, 1000),
      LongPath(78193, 75381, 1000000),
      Hamilton(80131, 87184),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(8);
  {
    const TestCase t[] = {
      RandomGraph(86719, 128461, 1000000),
      LongPath(87193, 51748, 1000000),
      Hamilton(86834, 97184),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(9);
  {
    const TestCase t[] = {
      RandomGraph(91847, 147983, 10),
      LongPath(98912, 97214, 1000000),
      Hamilton(92415, 93124),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
  RG.setSeed(10);
  {
    const TestCase t[] = {
      RandomGraph(99812, 150000, 1000000),
      LongPath(98174, 91375, 1000000),
      Hamilton(99174, 150000),
    };
    testGroup(vector<TestCase>(t, t + sizeof(t) / sizeof(TestCase)));
  }
}
