// async.cpp

#include <numeric>
#include <vector>
#include <iostream>
#include <thread>
#include <future>

int accum(const int *begin, const int *end, int init) {
  return std::accumulate(begin, end, 0);
}

void comp(const std::vector<int>& vec, int* result)
{
  auto v0 = &vec[0];
  auto sz = vec.size();
  auto f0 = std::async(accum, v0, v0 + sz/4, 0);
  auto f1 = std::async(accum, v0 + sz/4, v0 + sz/2, 0);
  auto f2 = std::async(accum, v0 + sz/2, v0 + sz*3/4, 0);
  auto f3 = std::async(accum, v0 + sz*3/4, v0 + sz, 0);
  *result = f0.get() + f1.get() + f2.get() + f3.get();
}

int main()
{
  std::vector<int> long_vec(1000);
  for (int i = 0; i < 1000; ++i) {
    long_vec[i] = i+1;
  }

  int result;
  comp(long_vec, &result);
  std::cout << result << std::endl;
}
