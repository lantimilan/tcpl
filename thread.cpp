// thread.cpp
#include <algorithm>
#include <numeric>
#include <iostream>
#include <thread>
#include <vector>
using namespace std;

void f(const vector<double>& v, double *res) {
  *res = accumulate(v.begin(), v.end(), 0);
}

class F {
 public:
  F(const vector<double>& vv, double *p): v{vv}, res{p} {}
  void operator()(); // operator() that takes no arg
 private:
  const vector<double>& v;
  double *res;
};

void F::operator()() {
  *res = accumulate(v.begin(), v.end(), 100);
}

int main()
{
  vector<double> some_vec{1, 3, 5};
  vector<double> vec2{2, 4, 6};

  double res1;
  double res2;

  thread t1{f, some_vec, &res1};
  thread t2{F(vec2, &res2)};

  t1.join();
  t2.join();

  cout << res1 << " " << res2 << endl;
}
